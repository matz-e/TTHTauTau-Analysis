// vim: et:sta:sw=4:ts=4
// Author: Nil Valls <nvallsve@nd.edu>

#include "boost/lexical_cast.hpp"

#include "../interface/Ntuplizer.h"
#include "../interface/OmniFiller.h"
#include "../interface/EventFiller.h"
#include "../interface/GenTauFiller.h"
#include "../interface/GenJetFiller.h"
#include "../interface/VertexFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
Ntuplizer::Ntuplizer(const ParameterSet& config) :
    params_(config),
    _filename(config.getParameter<string>("outputFileName")),
    _use_event_veto(config.getParameter<bool>("useEventVeto"))
{
	// Necessary to propagate config 
	jobConfig						= new ParameterSet(config);

	_DebugLevel						= config.getParameter<unsigned int>("DebugLevel");
	_EraRelease						= config.getParameter<string>("EraRelease");
    _UsePfLeptons                   = ( config.exists("UsePfLeptons") ) ? config.getParameter<bool>("UsePfLeptons") : true;
    _DataRange                      = ( config.exists("DataRange") ) ? config.getParameter<string>("DataRange") : "All";
    _RunExtraBEANhelpers            = ( config.exists("RunExtraBEANhelpers") ) ? config.getParameter<bool>("RunExtraBEANhelpers") : false;

	// Skim trigger
	_ApplySkimTriggerRequirements	= config.getParameter<bool>("ApplySkimTriggerRequirements");
	_SkimTriggerSource				= config.getParameter<InputTag>("SkimTriggerSource");
	_SkimTriggerRequirements		= config.getParameter<vector<string> >("SkimTriggerRequirements");
    
    // required for TTL event check
    _RecoTauSource                  = config.getParameter<InputTag>("RecoTauSource");
    _RecoMuonSource                 = config.getParameter<InputTag>("RecoMuonSource");
    _RecoElectronSource             = config.getParameter<InputTag>("RecoElectronSource");
    _RecoJetSource                  = config.getParameter<InputTag>("RecoJetSource");

    _an_type = config.getParameter<bool>("isDilepton") ? analysisType::TauDIL : analysisType::TauLJ;

    if (_an_type == analysisType::TauDIL) {
        std::cout << ">> Running in dilepton mode <<" << std::endl;
    } else {
        std::cout << ">> Running in single lepton mode <<" << std::endl;
    }

    std::string sysTypeString       = config.getUntrackedParameter<std::string>("SysType");
    _sysType = sysType::NA;
    if( sysTypeString.compare("NA") == 0 ) _sysType = sysType::NA;
    if( sysTypeString.compare("JERup") == 0 ) _sysType = sysType::JERup;
    if( sysTypeString.compare("JERdown") == 0 ) _sysType = sysType::JERdown;
    if( sysTypeString.compare("JESup") == 0 ) _sysType = sysType::JESup;
    if( sysTypeString.compare("JESdown") == 0 ) _sysType = sysType::JESdown;
    if( sysTypeString.compare("TESup") == 0 ) _sysType = sysType::TESup;
    if( sysTypeString.compare("TESdown") == 0 ) _sysType = sysType::TESdown;
}

// === Destructor === //
Ntuplizer::~Ntuplizer(){
	delete jobConfig; jobConfig = NULL;	
}

// ------------ method called once each job just before starting event loop  ------------
void
Ntuplizer::beginJob()
{
    _file = new TFile(_filename.c_str(), "RECREATE");
    if (!_file->IsOpen()) {
        edm::LogError("Ntuplizer") << "Can't open file '" << _filename << "' for writing!" << std::endl;
        throw;
    }
    _file->cd();

    _EventsRead = new TH1I(("EventsRead" + _filename).c_str(), "EventsRead",1,0,1);
    _Tree = new TTree("TTbarHTauTau", "TTbarHTauTau");
    // FIXME Set the flushing threshold to a lower level.  With the default
    // setting of ROOT 5.32 (CMSSW 5_3_8), the basket size of the tree
    // grows significantly after a while and does not decrease.  This
    // causes jobs to fail, as they exceed 2.3 GB RSS memory and get killed
    // by the crab watchdog.
    _Tree->SetAutoFlush(1000);

    _numFailedTauEventCheck = 0;


	// Instantiate and set up beanHelper
	string eraForBEANhelper = (params_.get_era() == "2011") ? params_.get_era() : (params_.get_era() + "_" + _EraRelease);
	beanHelper.SetUp(eraForBEANhelper, // 2011, 2012_52x, 2012_53x
            params_.get_sample_number(), // sample number
            _an_type,
            params_.is_data(), // is data
            std::string("SingleMu"), // data set
            false, // do CSV reshaping
            _UsePfLeptons, 
            _DataRange // 2012A_13July,2012A_06Aug,2012B_13July,2012C_PR,2012C_24Aug,2012D_PR,All,all
    );
    map<string,BEANhelper*> beanHelpers;
    beanHelpers["2012ABCD"] = &beanHelper;
    if(_RunExtraBEANhelpers) {
        beanHelpers["2012A"] = new BEANhelper();
        beanHelpers["2012A"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012A_13July,2012A_06Aug")
        );
        beanHelpers["2012AB"] = new BEANhelper();
        beanHelpers["2012AB"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012A_13July,2012A_06Aug,2012B_13July")
        );
        beanHelpers["2012B"] = new BEANhelper();
        beanHelpers["2012B"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012B_13July")
        );
        beanHelpers["2012C"] = new BEANhelper();
        beanHelpers["2012C"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012C_PR,2012C_24Aug")
        );
        beanHelpers["2012ABC"] = new BEANhelper();
        beanHelpers["2012ABC"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012A_13July,2012A_06Aug,2012B_13July,2012C_PR,2012C_24Aug")
        );
        beanHelpers["2012BC"] = new BEANhelper();
        beanHelpers["2012BC"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012B_13July,2012C_PR,2012C_24Aug")
        );
        beanHelpers["2012D"] = new BEANhelper();
        beanHelpers["2012D"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012D_PR")
        );
        beanHelpers["2012CD"] = new BEANhelper();
        beanHelpers["2012CD"]->SetUp(eraForBEANhelper,
            params_.get_sample_number(),
            _an_type,
            params_.is_data(),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012C_PR,2012C_24Aug,2012D_PR")
        );
    }

    // Declare and store here NtupleFillers
    ntupleFillers = {
        new EventFiller(*jobConfig, _Tree, beanHelpers),
        new VertexFiller(*jobConfig, _Tree, &beanHelper),
        new EventFiller(*jobConfig, _Tree, beanHelpers),
        new VertexFiller(*jobConfig, _Tree, &beanHelper),
        new GenTauFiller(*jobConfig, _Tree, &beanHelper),
        new GenJetFiller(*jobConfig, _Tree, &beanHelper),
        new OmniFiller(*jobConfig, _Tree, &beanHelper)
    };
}

// === Method called once each job just after ending the event loop === //
void
Ntuplizer::endJob()
{
    if( _RunExtraBEANhelpers )
        for (auto& pair: beanHelpers)
            delete pair.second;
    for (auto& filler: ntupleFillers)
       delete filler;

    LogWarning("TauNtuplizer") << _numFailedTauEventCheck << " events failed BEANhelper::IsTauEvent" << endl;

    _file->WriteObject(_Tree, "TTbarHTauTau");
    delete _Tree;
    _file->WriteObject(_EventsRead, "EventsRead");
    _file->Close();

    delete _file;
}



// ------------ method called to for each event  ------------
void Ntuplizer::analyze(const Event& iEvent, const EventSetup& iSetup) {

    //std::cout << "<Ntuplizer::analyze>: enter function" << std::endl;

	/*// Generic event info (commented out, but available if needed here)
	double eventNum		= iEvent.id().event();
	double lumiBlock	= iEvent.id().luminosityBlock();
	double runNum		= iEvent.id().run();//*/


	// Fill histogram that keeps track of the number of events read
	_EventsRead->Fill(0);

    // Remove non-TTL events
    Handle<BNelectronCollection>			hBNelectrons;
    Handle<BNmuonCollection>				hBNmuons;
    Handle<BNtauCollection>					hBNtaus;
    Handle<BNjetCollection>					hBNjets;
    
    iEvent.getByLabel(_RecoElectronSource,	hBNelectrons);
    iEvent.getByLabel(_RecoMuonSource, 		hBNmuons);
    iEvent.getByLabel(_RecoTauSource, 		hBNtaus);
    iEvent.getByLabel(_RecoJetSource, 		hBNjets);
    
    BNelectronCollection BNelectrons	= *(hBNelectrons.product());
    BNmuonCollection BNmuons			= *(hBNmuons.product());
    BNtauCollection BNtaus				= *(hBNtaus.product());
    BNjetCollection BNjets				= *(hBNjets.product());

    if (_use_event_veto) {
        if ((params_.get_lepton_count() == 1 && !beanHelper.IsTauTauLeptonEvent(BNtaus, BNjets, BNelectrons, BNmuons, _sysType)) ||
            (params_.get_lepton_count() == 2 && !beanHelper.IsTauLeptonLeptonEvent(BNtaus, BNjets, BNelectrons, BNmuons, _sysType))) {
            _numFailedTauEventCheck++;
            return;
        } else if (!params_.get_lepton_count() > 2) {
            throw;
        }
    }

	// Analyze and fill ntuple
	for(unsigned int n=0; n<ntupleFillers.size(); n++){
		if(_DebugLevel>0){ cout << "[DEBUG]\t" << ntupleFillers.at(n)->GetName() << "->FillNtuple" << endl; }
        ntupleFillers.at(n)->FillNtuple(iEvent, iSetup);
	}

	// Write to tree
	_Tree->Fill();
}

//define this as a plug-in
DEFINE_FWK_MODULE(Ntuplizer);
