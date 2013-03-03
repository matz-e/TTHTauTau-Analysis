// -*- C++ -*-
//
// Package:    BEANskimmer
// Class:      BEANskimmer
// 

// user include files
#include "TTHTauTau/Analysis/plugins/BEANskimmer.h"

//
// constructors and destructor
//
BEANskimmer::BEANskimmer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  if( iConfig.exists("config") ) 
    cfg_ = iConfig.getUntrackedParameter<std::string>("config");
  else
    edm::LogError ("BEANskimmer::BEANskimmer") << " parameter 'config' must be configured! Exiting...";

  CSV_WP_L_ = 0.244;
  CSV_WP_M_ = 0.679;
  CSV_WP_T_ = 0.898;
  minNumLooseBtags_ = 0;
  minNumMediumBtags_ = 0;
  minNumTightBtags_ = 0;
  minNumJets_ = 0;
  minNumBaseTaus_ = 0;
  
  if( cfg_.size() > 0 ) minNumJets_ = atoi(cfg_.substr(0,1).c_str());
  if( cfg_.size() > 1 ) minNumLooseBtags_ = atoi(cfg_.substr(1,1).c_str());
  if( cfg_.size() > 2 ) minNumMediumBtags_ = atoi(cfg_.substr(2,1).c_str());
  if( cfg_.size() > 3 ) minNumTightBtags_ = atoi(cfg_.substr(3,1).c_str());
  if( cfg_.size() > 4 ) minNumBaseTaus_ = atoi(cfg_.substr(4,1).c_str());

}


BEANskimmer::~BEANskimmer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
BEANskimmer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;

  edm::Handle<BNjetCollection> jetsHandle;
  iEvent.getByLabel("BNproducer","selectedPatJetsPFlow", jetsHandle);
  BNjetCollection const &pfjets = *jetsHandle;

  int numLooseTags = 0;
  int numMediumTags = 0;
  int numTightTags = 0;
  int numJets = int(pfjets.size());
  for( int i=0; i<int(pfjets.size()); i++ ){
    double csv = pfjets.at(i).btagCombinedSecVertex;
    if( csv > CSV_WP_T_ ) numTightTags++; 
    if( csv > CSV_WP_M_ ) numMediumTags++; 
    if( csv > CSV_WP_L_ ) numLooseTags++;
  }
  
  if( numLooseTags < minNumLooseBtags_ )
    return false;
  if( numMediumTags < minNumMediumBtags_ )
    return false;
  if( numTightTags < minNumTightBtags_ )
    return false;
  if( numJets < minNumJets_ )
    return false;

  int numBaseTaus = 0;
  edm::Handle<BNtauCollection> tausHandle;
  iEvent.getByLabel("BNproducer","selectedPatTaus", tausHandle);
  BNtauCollection const &taus = *tausHandle;

  for( int i=0; i<int(taus.size()); i++ ) {
    BNtau tau = taus.at(i);
    if( tau.pt > 20 &&
        tau.HPSdecayModeFinding > 0 &&
        tau.leadingTrackPt > 5 &&
        tau.leadingTrackValid > 0 &&
        tau.HPSagainstElectronLoose > 0 &&
        tau.HPSagainstMuonLoose > 0 ) numBaseTaus++;
  }
  if( numBaseTaus < minNumBaseTaus_ )
    return false;
  return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
BEANskimmer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BEANskimmer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
BEANskimmer::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
BEANskimmer::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
BEANskimmer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
BEANskimmer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BEANskimmer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(BEANskimmer);