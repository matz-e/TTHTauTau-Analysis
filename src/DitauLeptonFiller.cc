// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/DitauLeptonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DitauLeptonFiller::DitauLeptonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DitauLeptonFiller::DitauLeptonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
DitauLeptonFiller::~DitauLeptonFiller(){}

// ------------ method called to for each event  ------------
void DitauLeptonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DitauLeptonFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("TTL_NumTaus",&_NumTaus);
	_Tree->Branch("TTL_NumMuons",&_NumMuons);
	_Tree->Branch("TTL_NumElectrons",&_NumElectrons);
	_Tree->Branch("TTL_NumLeptons",&_NumLeptons);
	_Tree->Branch("TTL_NumCombos",&_NumCombos);
	_Tree->Branch("TTL_MomentumRank",&_MomentumRank);

	// === Tau1 === //
	_Tree->Branch("TTL_Tau1MomentumRank", &_Tau1MomentumRank);
	_Tree->Branch("TTL_Tau1Pt", &_Tau1Pt);
	_Tree->Branch("TTL_Tau1Eta", &_Tau1Eta);
	_Tree->Branch("TTL_Tau1Phi", &_Tau1Phi);
	_Tree->Branch("TTL_Tau1NProngs", &_Tau1NProngs);
	_Tree->Branch("TTL_Tau1NSignalGammas", &_Tau1NSignalGammas);
	_Tree->Branch("TTL_Tau1NSignalNeutrals", &_Tau1NSignalNeutrals);
	_Tree->Branch("TTL_Tau1DecayMode", &_Tau1DecayMode);
	_Tree->Branch("TTL_Tau1EmFraction", &_Tau1EmFraction);
	_Tree->Branch("TTL_Tau1IsInTheCracks", &_Tau1IsInTheCracks);
	_Tree->Branch("TTL_Tau1HPSagainstElectronLoose", &_Tau1HPSagainstElectronLoose);
	_Tree->Branch("TTL_Tau1HPSagainstElectronMVA", &_Tau1HPSagainstElectronMVA);
	_Tree->Branch("TTL_Tau1HPSagainstElectronMedium", &_Tau1HPSagainstElectronMedium);
	_Tree->Branch("TTL_Tau1HPSagainstElectronTight", &_Tau1HPSagainstElectronTight);
	_Tree->Branch("TTL_Tau1HPSagainstMuonLoose", &_Tau1HPSagainstMuonLoose);
	_Tree->Branch("TTL_Tau1HPSagainstMuonMedium", &_Tau1HPSagainstMuonMedium);
	_Tree->Branch("TTL_Tau1HPSagainstMuonTight", &_Tau1HPSagainstMuonTight);
	_Tree->Branch("TTL_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau1HPSdecayModeFinding", &_Tau1HPSdecayModeFinding);
	_Tree->Branch("TTL_Tau1LTPt", &_Tau1LTPt);
	_Tree->Branch("TTL_Tau1Charge", &_Tau1Charge);
	_Tree->Branch("TTL_Tau1LTvalid", &_Tau1LTvalid);
	_Tree->Branch("TTL_Tau1LTIpVtdxy", &_Tau1LTIpVtdxy);
	_Tree->Branch("TTL_Tau1LTIpVtdz", &_Tau1LTIpVtdz);
	_Tree->Branch("TTL_Tau1LTIpVtdxyError", &_Tau1LTIpVtdxyError);
	_Tree->Branch("TTL_Tau1LTIpVtdzError", &_Tau1LTIpVtdzError);
	_Tree->Branch("TTL_Tau1LTvx", &_Tau1LTvx);
	_Tree->Branch("TTL_Tau1LTvy", &_Tau1LTvy);
	_Tree->Branch("TTL_Tau1LTvz", &_Tau1LTvz);
	_Tree->Branch("TTL_Tau1LTValidHits", &_Tau1LTValidHits);
	_Tree->Branch("TTL_Tau1LTNormChiSqrd", &_Tau1LTNormChiSqrd);

	_Tree->Branch("TTL_Tau1GenMatchDaughter0Id", &_Tau1GenMatchDaughter0Id);
	_Tree->Branch("TTL_Tau1GenMatchDaughter1Id", &_Tau1GenMatchDaughter1Id);
	_Tree->Branch("TTL_Tau1GenMatchId", &_Tau1GenMatchId);
	_Tree->Branch("TTL_Tau1GenMatchMother0Id", &_Tau1GenMatchMother0Id);
	_Tree->Branch("TTL_Tau1GenMatchMother1Id", &_Tau1GenMatchMother1Id);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother00Id", &_Tau1GenMatchGrandmother00Id);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother01Id", &_Tau1GenMatchGrandmother01Id);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother10Id", &_Tau1GenMatchGrandmother10Id);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother11Id", &_Tau1GenMatchGrandmother11Id);
	_Tree->Branch("TTL_Tau1GenMatchDaughter0Status", &_Tau1GenMatchDaughter0Status);
	_Tree->Branch("TTL_Tau1GenMatchDaughter1Status", &_Tau1GenMatchDaughter1Status);
	_Tree->Branch("TTL_Tau1GenMatchStatus", &_Tau1GenMatchStatus);
	_Tree->Branch("TTL_Tau1GenMatchMother0Status", &_Tau1GenMatchMother0Status);
	_Tree->Branch("TTL_Tau1GenMatchMother1Status", &_Tau1GenMatchMother1Status);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother00Status", &_Tau1GenMatchGrandmother00Status);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother01Status", &_Tau1GenMatchGrandmother01Status);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother10Status", &_Tau1GenMatchGrandmother10Status);
	_Tree->Branch("TTL_Tau1GenMatchGrandmother11Status", &_Tau1GenMatchGrandmother11Status);

	// === Tau2 === //
	_Tree->Branch("TTL_Tau2MomentumRank", &_Tau2MomentumRank);
	_Tree->Branch("TTL_Tau2Pt", &_Tau2Pt);
	_Tree->Branch("TTL_Tau2Eta", &_Tau2Eta);
	_Tree->Branch("TTL_Tau2Phi", &_Tau2Phi);
	_Tree->Branch("TTL_Tau2NProngs", &_Tau2NProngs);
	_Tree->Branch("TTL_Tau2NSignalGammas", &_Tau2NSignalGammas);
	_Tree->Branch("TTL_Tau2NSignalNeutrals", &_Tau2NSignalNeutrals);
	_Tree->Branch("TTL_Tau2DecayMode", &_Tau2DecayMode);
	_Tree->Branch("TTL_Tau2EmFraction", &_Tau2EmFraction);
	_Tree->Branch("TTL_Tau2IsInTheCracks", &_Tau2IsInTheCracks);
	_Tree->Branch("TTL_Tau2HPSagainstElectronLoose", &_Tau2HPSagainstElectronLoose);
	_Tree->Branch("TTL_Tau2HPSagainstElectronMVA", &_Tau2HPSagainstElectronMVA);
	_Tree->Branch("TTL_Tau2HPSagainstElectronMedium", &_Tau2HPSagainstElectronMedium);
	_Tree->Branch("TTL_Tau2HPSagainstElectronTight", &_Tau2HPSagainstElectronTight);
	_Tree->Branch("TTL_Tau2HPSagainstMuonLoose", &_Tau2HPSagainstMuonLoose);
	_Tree->Branch("TTL_Tau2HPSagainstMuonMedium", &_Tau2HPSagainstMuonMedium);
	_Tree->Branch("TTL_Tau2HPSagainstMuonTight", &_Tau2HPSagainstMuonTight);
	_Tree->Branch("TTL_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTL_Tau2HPSdecayModeFinding", &_Tau2HPSdecayModeFinding);
	_Tree->Branch("TTL_Tau2LTPt", &_Tau2LTPt);
	_Tree->Branch("TTL_Tau2Charge", &_Tau2Charge);
	_Tree->Branch("TTL_Tau2LTvalid", &_Tau2LTvalid);
	_Tree->Branch("TTL_Tau2LTIpVtdxy", &_Tau2LTIpVtdxy);
	_Tree->Branch("TTL_Tau2LTIpVtdz", &_Tau2LTIpVtdz);
	_Tree->Branch("TTL_Tau2LTIpVtdxyError", &_Tau2LTIpVtdxyError);
	_Tree->Branch("TTL_Tau2LTIpVtdzError", &_Tau2LTIpVtdzError);
	_Tree->Branch("TTL_Tau2LTvx", &_Tau2LTvx);
	_Tree->Branch("TTL_Tau2LTvy", &_Tau2LTvy);
	_Tree->Branch("TTL_Tau2LTvz", &_Tau2LTvz);
	_Tree->Branch("TTL_Tau2LTValidHits", &_Tau2LTValidHits);
	_Tree->Branch("TTL_Tau2LTNormChiSqrd", &_Tau2LTNormChiSqrd);

	_Tree->Branch("TTL_Tau2GenMatchDaughter0Id", &_Tau2GenMatchDaughter0Id);
	_Tree->Branch("TTL_Tau2GenMatchDaughter1Id", &_Tau2GenMatchDaughter1Id);
	_Tree->Branch("TTL_Tau2GenMatchId", &_Tau2GenMatchId);
	_Tree->Branch("TTL_Tau2GenMatchMother0Id", &_Tau2GenMatchMother0Id);
	_Tree->Branch("TTL_Tau2GenMatchMother1Id", &_Tau2GenMatchMother1Id);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother00Id", &_Tau2GenMatchGrandmother00Id);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother01Id", &_Tau2GenMatchGrandmother01Id);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother10Id", &_Tau2GenMatchGrandmother10Id);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother11Id", &_Tau2GenMatchGrandmother11Id);
	_Tree->Branch("TTL_Tau2GenMatchDaughter0Status", &_Tau2GenMatchDaughter0Status);
	_Tree->Branch("TTL_Tau2GenMatchDaughter1Status", &_Tau2GenMatchDaughter1Status);
	_Tree->Branch("TTL_Tau2GenMatchStatus", &_Tau2GenMatchStatus);
	_Tree->Branch("TTL_Tau2GenMatchMother0Status", &_Tau2GenMatchMother0Status);
	_Tree->Branch("TTL_Tau2GenMatchMother1Status", &_Tau2GenMatchMother1Status);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother00Status", &_Tau2GenMatchGrandmother00Status);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother01Status", &_Tau2GenMatchGrandmother01Status);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother10Status", &_Tau2GenMatchGrandmother10Status);
	_Tree->Branch("TTL_Tau2GenMatchGrandmother11Status", &_Tau2GenMatchGrandmother11Status);

	// === Lepton === //
	_Tree->Branch("TTL_MuonMomentumRank", &_MuonMomentumRank);
	_Tree->Branch("TTL_ElectronMomentumRank", &_ElectronMomentumRank);
	_Tree->Branch("TTL_LeptonMomentumRank", &_LeptonMomentumRank);
	_Tree->Branch("TTL_LeptonIsMuon", &_LeptonIsMuon);
	_Tree->Branch("TTL_LeptonIsElectron", &_LeptonIsElectron);
	_Tree->Branch("TTL_LeptonPt", &_LeptonPt);
	_Tree->Branch("TTL_LeptonEta", &_LeptonEta);
	_Tree->Branch("TTL_LeptonPhi", &_LeptonPhi);
	_Tree->Branch("TTL_LeptonRelIso", &_LeptonRelIso);
	_Tree->Branch("TTL_LeptonIsLoose", &_LeptonIsLoose);
	_Tree->Branch("TTL_LeptonIsTight", &_LeptonIsTight);
	_Tree->Branch("TTL_NumLooseMuons",&_NumLooseMuons);
	_Tree->Branch("TTL_NumExLooseMuons",&_NumExLooseMuons);
	_Tree->Branch("TTL_NumTightMuons",&_NumTightMuons);
	_Tree->Branch("TTL_NumLooseElectrons",&_NumLooseElectrons);
	_Tree->Branch("TTL_NumExLooseElectrons",&_NumExLooseElectrons);
	_Tree->Branch("TTL_NumTightElectrons",&_NumTightElectrons);
	_Tree->Branch("TTL_LeptonEventWeight",&_LeptonEventWeight);
	_Tree->Branch("TTL_LeptonGenMatchDaughter0Id", &_LeptonGenMatchDaughter0Id);
	_Tree->Branch("TTL_LeptonGenMatchDaughter1Id", &_LeptonGenMatchDaughter1Id);
	_Tree->Branch("TTL_LeptonGenMatchId", &_LeptonGenMatchId);
	_Tree->Branch("TTL_LeptonGenMatchMother0Id", &_LeptonGenMatchMother0Id);
	_Tree->Branch("TTL_LeptonGenMatchMother1Id", &_LeptonGenMatchMother1Id);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother00Id", &_LeptonGenMatchGrandmother00Id);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother01Id", &_LeptonGenMatchGrandmother01Id);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother10Id", &_LeptonGenMatchGrandmother10Id);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother11Id", &_LeptonGenMatchGrandmother11Id);
	_Tree->Branch("TTL_LeptonGenMatchDaughter0Status", &_LeptonGenMatchDaughter0Status);
	_Tree->Branch("TTL_LeptonGenMatchDaughter1Status", &_LeptonGenMatchDaughter1Status);
	_Tree->Branch("TTL_LeptonGenMatchStatus", &_LeptonGenMatchStatus);
	_Tree->Branch("TTL_LeptonGenMatchMother0Status", &_LeptonGenMatchMother0Status);
	_Tree->Branch("TTL_LeptonGenMatchMother1Status", &_LeptonGenMatchMother1Status);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother00Status", &_LeptonGenMatchGrandmother00Status);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother01Status", &_LeptonGenMatchGrandmother01Status);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother10Status", &_LeptonGenMatchGrandmother10Status);
	_Tree->Branch("TTL_LeptonGenMatchGrandmother11Status", &_LeptonGenMatchGrandmother11Status);

	// === Combo === //
	_Tree->Branch("TTL_DitauVisibleMass", &_DitauVisibleMass);
	_Tree->Branch("TTL_DitauMETMass", &_DitauMETMass);
	_Tree->Branch("TTL_DitauCosDeltaPhi", &_DitauCosDeltaPhi);
	_Tree->Branch("TTL_DitauDeltaR", 	&_DitauDeltaR);
	_Tree->Branch("TTL_Tau1LeptonDeltaR", &_Tau1LeptonDeltaR);
	_Tree->Branch("TTL_Tau2LeptonDeltaR", &_Tau2LeptonDeltaR);
	_Tree->Branch("TTL_HT", &_HT);
	_Tree->Branch("TTL_NumCSVLbtagJets", &_NumCSVLbtagJets);
	_Tree->Branch("TTL_NumCSVMbtagJets", &_NumCSVMbtagJets);
	_Tree->Branch("TTL_NumCSVTbtagJets", &_NumCSVTbtagJets);
	_Tree->Branch("TTL_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
	_Tree->Branch("TTL_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
	_Tree->Branch("TTL_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
}

// === Clear vectors that will be used to fill ntuple === //
void DitauLeptonFiller::ClearVectors(){

	_NumTaus										= 0;
	_NumLeptons										= 0;
	_NumMuons										= 0;
	_NumElectrons									= 0;
	_NumCombos										= 0;	
	_MomentumRank									.clear();

	// === Tau1 === //
	_Tau1MomentumRank								.clear();
	_Tau1Pt											.clear();
	_Tau1Eta										.clear();
	_Tau1Phi										.clear();
	_Tau1NProngs									.clear();
	_Tau1NSignalGammas								.clear();
	_Tau1NSignalNeutrals							.clear();
	_Tau1DecayMode									.clear();
	_Tau1EmFraction									.clear();
	_Tau1IsInTheCracks								.clear();
	_Tau1HPSagainstElectronLoose					.clear();
	_Tau1HPSagainstElectronMVA						.clear();
	_Tau1HPSagainstElectronMedium					.clear();
	_Tau1HPSagainstElectronTight					.clear();
	_Tau1HPSagainstMuonLoose						.clear();
	_Tau1HPSagainstMuonMedium						.clear();
	_Tau1HPSagainstMuonTight						.clear();
	_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSdecayModeFinding						.clear();
	_Tau1LTPt										.clear();
	_Tau1Charge										.clear();
	_Tau1LTvalid									.clear();
	_Tau1LTIpVtdxy									.clear();
	_Tau1LTIpVtdz									.clear();
	_Tau1LTIpVtdxyError								.clear();
	_Tau1LTIpVtdzError								.clear();
	_Tau1LTvx										.clear();
	_Tau1LTvy										.clear();
	_Tau1LTvz										.clear();
	_Tau1LTValidHits								.clear();
	_Tau1LTNormChiSqrd								.clear();
	_Tau1GenMatchDaughter0Id						.clear();
	_Tau1GenMatchDaughter1Id						.clear();
	_Tau1GenMatchId									.clear();
	_Tau1GenMatchMother0Id							.clear();
	_Tau1GenMatchMother1Id							.clear();
	_Tau1GenMatchGrandmother00Id					.clear();
	_Tau1GenMatchGrandmother01Id					.clear();
	_Tau1GenMatchGrandmother10Id					.clear();
	_Tau1GenMatchGrandmother11Id					.clear();
	_Tau1GenMatchDaughter0Status					.clear();
	_Tau1GenMatchDaughter1Status					.clear();
	_Tau1GenMatchStatus								.clear();
	_Tau1GenMatchMother0Status						.clear();
	_Tau1GenMatchMother1Status						.clear();
	_Tau1GenMatchGrandmother00Status				.clear();
	_Tau1GenMatchGrandmother01Status				.clear();
	_Tau1GenMatchGrandmother10Status				.clear();
	_Tau1GenMatchGrandmother11Status				.clear();

	// === Tau2 === //
	_Tau2MomentumRank								.clear();
	_Tau2Pt											.clear();
	_Tau2Eta										.clear();
	_Tau2Phi										.clear();
	_Tau2NProngs									.clear();
	_Tau2NSignalGammas								.clear();
	_Tau2NSignalNeutrals							.clear();
	_Tau2DecayMode									.clear();
	_Tau2EmFraction									.clear();
	_Tau2IsInTheCracks								.clear();
	_Tau2HPSagainstElectronLoose					.clear();
	_Tau2HPSagainstElectronMVA						.clear();
	_Tau2HPSagainstElectronMedium					.clear();
	_Tau2HPSagainstElectronTight					.clear();
	_Tau2HPSagainstMuonLoose						.clear();
	_Tau2HPSagainstMuonMedium						.clear();
	_Tau2HPSagainstMuonTight						.clear();
	_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSdecayModeFinding						.clear();
	_Tau2LTPt										.clear();
	_Tau2Charge										.clear();
	_Tau2LTvalid									.clear();
	_Tau2LTIpVtdxy									.clear();
	_Tau2LTIpVtdz									.clear();
	_Tau2LTIpVtdxyError								.clear();
	_Tau2LTIpVtdzError								.clear();
	_Tau2LTvx										.clear();
	_Tau2LTvy										.clear();
	_Tau2LTvz										.clear();
	_Tau2LTValidHits								.clear();
	_Tau2LTNormChiSqrd								.clear();
	_Tau2GenMatchDaughter0Id						.clear();
	_Tau2GenMatchDaughter1Id						.clear();
	_Tau2GenMatchId									.clear();
	_Tau2GenMatchMother0Id							.clear();
	_Tau2GenMatchMother1Id							.clear();
	_Tau2GenMatchGrandmother00Id					.clear();
	_Tau2GenMatchGrandmother01Id					.clear();
	_Tau2GenMatchGrandmother10Id					.clear();
	_Tau2GenMatchGrandmother11Id					.clear();
	_Tau2GenMatchDaughter0Status					.clear();
	_Tau2GenMatchDaughter1Status					.clear();
	_Tau2GenMatchStatus								.clear();
	_Tau2GenMatchMother0Status						.clear();
	_Tau2GenMatchMother1Status						.clear();
	_Tau2GenMatchGrandmother00Status				.clear();
	_Tau2GenMatchGrandmother01Status				.clear();
	_Tau2GenMatchGrandmother10Status				.clear();
	_Tau2GenMatchGrandmother11Status				.clear();

	// === Lepton === //
	_MuonMomentumRank								.clear();
	_ElectronMomentumRank							.clear();
	_LeptonMomentumRank								.clear();
	_LeptonPt										.clear();
	_LeptonEta										.clear();
	_LeptonPhi										.clear();
    _LeptonRelIso									.clear();
    _LeptonIsTight									.clear();
    _LeptonIsLoose									.clear();
	_NumLooseMuons									.clear();
	_NumExLooseMuons								.clear();
	_NumTightMuons									.clear();
	_NumLooseElectrons								.clear();
	_NumExLooseElectrons							.clear();
	_NumTightElectrons								.clear();
	_LeptonEventWeight								.clear();
	_LeptonGenMatchDaughter0Id						.clear();
	_LeptonGenMatchDaughter1Id						.clear();
	_LeptonGenMatchId								.clear();
	_LeptonGenMatchMother0Id						.clear();
	_LeptonGenMatchMother1Id						.clear();
	_LeptonGenMatchGrandmother00Id					.clear();
	_LeptonGenMatchGrandmother01Id					.clear();
	_LeptonGenMatchGrandmother10Id					.clear();
	_LeptonGenMatchGrandmother11Id					.clear();
	_LeptonGenMatchDaughter0Status					.clear();
	_LeptonGenMatchDaughter1Status					.clear();
	_LeptonGenMatchStatus							.clear();
	_LeptonGenMatchMother0Status					.clear();
	_LeptonGenMatchMother1Status					.clear();
	_LeptonGenMatchGrandmother00Status				.clear();
	_LeptonGenMatchGrandmother01Status				.clear();
	_LeptonGenMatchGrandmother10Status				.clear();
	_LeptonGenMatchGrandmother11Status				.clear();

	// === Combo === //
	_DitauVisibleMass								.clear();
	_DitauMETMass									.clear();
	_DitauCosDeltaPhi								.clear();
	_DitauDeltaR									.clear();
	_Tau1LeptonDeltaR								.clear();
	_Tau2LeptonDeltaR								.clear();
	_HT												.clear();
	_NumCSVLbtagJets								.clear();
	_NumCSVMbtagJets								.clear();
	_NumCSVTbtagJets								.clear();
	_NumNonCSVLbtagJets								.clear();
	_NumNonCSVMbtagJets								.clear();
	_NumNonCSVTbtagJets								.clear();
}

// === Fill ntuple === //
void DitauLeptonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();

	// Leptons
	BNelectronCollection looseElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
	BNelectronCollection tightElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronTight);
	BNelectronCollection exLooseElectrons	= beanHelper->GetDifference(looseElectrons, tightElectrons);
	BNmuonCollection looseMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonLoose);
	BNmuonCollection tightMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);
	BNmuonCollection exLooseMuons			= beanHelper->GetDifference(looseMuons, tightMuons);

	// Select leptons (tight)
	BNmuonCollection selectedMuons			= tightMuons;
	BNelectronCollection selectedElectrons	= tightElectrons;

	// Make sure we can at least make one TTL combo
	if(_BNtaus.size() < 2 || (selectedMuons.size() + selectedElectrons.size()) < 1){ return; }

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus1		= 0;
	unsigned int theNumberOfTaus2		= 0;
	unsigned int theNumberOfMuons		= 0;
	unsigned int theNumberOfElectrons	= 0;
	unsigned int theNumberOfLeptons		= 0;

	// Start loop over Taus so select two (if applicable) that form a good (and heaviest) pair
	_NumTaus = _BNtaus.size();
	theNumberOfTaus1 = 0;
	for ( BNtauCollection::const_iterator Tau1 = _BNtaus.begin(); Tau1 != _BNtaus.end(); ++Tau1 ) {
		theNumberOfTaus1++;

		theNumberOfTaus2 = theNumberOfTaus1 + 1;
		for ( BNtauCollection::const_iterator Tau2 = (Tau1 + 1); Tau2 != _BNtaus.end(); ++Tau2 ) {
			theNumberOfTaus2++;

			if( theNumberOfTaus2 <= theNumberOfTaus1 ){ continue; }// Make sure we don't double-count: only compare pairs in which the tau2 iterator is larger than the tau 1 iterator, else skip combo


			// BNtauCollection should be sorted by pT in descending order, but let's make sure, and if not, flip them so Tau1 has the largest pT
			if (Tau1->pt < Tau2->pt){
				BNtauCollection::const_iterator TauTemp = Tau1;
				Tau1 = Tau2;
				Tau2 = TauTemp;
			}

			if(Tau1->pt < _RecoTauMinPt){ continue; }
			if(Tau2->pt < _RecoTauMinPt){ continue; }
			if(fabs(Tau1->eta) > _RecoTauMaxAbsEta ){ continue; }
			if(fabs(Tau2->eta) > _RecoTauMaxAbsEta ){ continue; }
			if(_RecoTauRequireDMF && !(Tau1->HPSdecayModeFinding)){ continue; }
			if(_RecoTauRequireDMF && !(Tau2->HPSdecayModeFinding)){ continue; }


			// Count leptons
			unsigned int numLooseMuons			= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, looseMuons,			0.15);
			unsigned int numExLooseMuons		= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, exLooseMuons,		0.15);
			unsigned int numTightMuons			= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, tightMuons,			0.15);
			unsigned int numLooseElectrons		= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, looseElectrons,		0.15);
			unsigned int numExLooseElectrons	= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, exLooseElectrons,	0.15);
			unsigned int numTightElectrons		= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, tightElectrons,		0.15);


			// Initialize lepton iterators
			BNmuonCollection::const_iterator Muon			= selectedMuons.begin();
			BNelectronCollection::const_iterator Electron	= selectedElectrons.begin();

			_NumMuons		= selectedMuons.size();
			_NumElectrons	= selectedElectrons.size();
			_NumLeptons		= _NumMuons + _NumElectrons;

			theNumberOfMuons		= 0;
			theNumberOfElectrons	= 0;
			theNumberOfLeptons		= 0;
			
			// Lepton loop
			while(Muon != selectedMuons.end() || Electron != selectedElectrons.end()){
				bool useMuon; // Is this a muon or electron?
				if(Muon == selectedMuons.end()){ useMuon = false; } // If no muons, don't use muon
				else{
					if(Electron == selectedElectrons.end()){ useMuon = true;	} // If no electrons, use muon
					else{ useMuon = (Muon->pt > Electron->pt);					} // If both, use highest pT object
				}

				// Prevent overlap with taus
				if(useMuon){ // Lepton is a muon: fill for muon
					if(deltaR(Tau1->eta, Tau1->phi, Muon->eta, Muon->phi) < 0.15){ ++Muon; continue; }
					if(deltaR(Tau2->eta, Tau2->phi, Muon->eta, Muon->phi) < 0.15){ ++Muon; continue; }
				}else{	// Lepton is an electron: fill for electron
					if(deltaR(Tau1->eta, Tau1->phi, Electron->eta, Electron->phi) < 0.15){ ++Electron; continue; }
					if(deltaR(Tau2->eta, Tau2->phi, Electron->eta, Electron->phi) < 0.15){ ++Electron; continue; }
				}
				
				// Jets and MET and related quantities
				// Correct for jet pT
				BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets, _sysType);
				// Apply kinematic requirements on corrected jets
				BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
				vector<TLorentzVector> tausAndLepton; // Clean jets from taus and muon
				tausAndLepton.push_back(TLorentzVector(Tau1->px, Tau1->py, Tau1->pz, Tau1->energy));
				tausAndLepton.push_back(TLorentzVector(Tau2->px, Tau2->py, Tau2->pz, Tau2->energy));

				_MomentumRank.push_back(_MomentumRank.size());
				_NumCombos++;
				theNumberOfLeptons++;

				// Count leptons
				_NumLooseMuons			.push_back(numLooseMuons);
				_NumExLooseMuons		.push_back(numExLooseMuons);
				_NumTightMuons			.push_back(numTightMuons);
				_NumLooseElectrons		.push_back(numLooseElectrons);
				_NumExLooseElectrons	.push_back(numExLooseElectrons);
				_NumTightElectrons		.push_back(numTightElectrons);

				// Fill leading tau
				_Tau1MomentumRank.push_back(theNumberOfTaus1-1);
				FillTau1(*Tau1);

				// Fill subleading tau
				_Tau2MomentumRank.push_back(theNumberOfTaus2-1);
				FillTau2(*Tau2);

				// Fill lepton
				_LeptonMomentumRank.push_back(theNumberOfLeptons-1);
				if(useMuon){ // Lepton is a muon: fill for muon
					theNumberOfMuons++;	
					_MuonMomentumRank.push_back(theNumberOfMuons-1);
					_ElectronMomentumRank.push_back(-1);
					FillMuon(*Muon);
					FillDitauLepton(*Tau1, *Tau2, *Muon);
					tausAndLepton.push_back(TLorentzVector(Muon->px, Muon->py, Muon->pz, Muon->energy));
					
				}else{	// Lepton is an electron: fill for electron
					theNumberOfElectrons++;
					_MuonMomentumRank.push_back(-1);
					_ElectronMomentumRank.push_back(theNumberOfElectrons-1);
					FillElectron(*Electron);
					FillDitauLepton(*Tau1, *Tau2, *Electron);
					tausAndLepton.push_back(TLorentzVector(Electron->px, Electron->py, Electron->pz, Electron->energy));
				
				} // End of muon/electron if-statement

				BNjetCollection cleanSelCorrJets						= beanHelper->GetCleanJets(selCorrJets, tausAndLepton, 0.25);

				// Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
				BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets), _sysType);

				if(useMuon){	_HT.push_back(Tau1->pt + Tau2->pt + Muon->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets)); }
				else{			_HT.push_back(Tau1->pt + Tau2->pt + Electron->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets)); }

				_DitauMETMass		.push_back(GetComboMassBN(*Tau1, *Tau2, correctedMET));

				_NumCSVLbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'L'));
				_NumCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'M'));
				_NumCSVTbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'T'));
				_NumNonCSVLbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'L'));
				_NumNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'M'));
				_NumNonCSVTbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'T'));

				// Move to the next lepton
				if(useMuon){ ++Muon; }
				else{ ++Electron; }
			
			} // End of lepton while-loop

		} // end of tau2 loop
	} // end of tau1 loop
		
}


void DitauLeptonFiller::FillTau1(const BNtau& Tau){
				_Tau1Pt											.push_back(Tau.pt);
				_Tau1Eta										.push_back(Tau.eta);
				_Tau1Phi										.push_back(Tau.phi);
				_Tau1NProngs									.push_back(Tau.numProngs);
				_Tau1NSignalGammas								.push_back(Tau.numSignalGammas);
				_Tau1NSignalNeutrals							.push_back(Tau.numSignalNeutrals);
				_Tau1DecayMode									.push_back(Tau.decayMode);
				_Tau1EmFraction									.push_back(Tau.emFraction);
				_Tau1IsInTheCracks								.push_back(Tau.inTheCracks);
				_Tau1HPSagainstElectronMVA						.push_back(Tau.HPSagainstElectronMVA);
				_Tau1HPSagainstElectronLoose					.push_back(Tau.HPSagainstElectronLoose);
				_Tau1HPSagainstElectronMedium					.push_back(Tau.HPSagainstElectronMedium);
				_Tau1HPSagainstElectronTight					.push_back(Tau.HPSagainstElectronTight);
				_Tau1HPSagainstMuonLoose						.push_back(Tau.HPSagainstMuonLoose);
				_Tau1HPSagainstMuonMedium						.push_back(Tau.HPSagainstMuonMedium);
				_Tau1HPSagainstMuonTight						.push_back(Tau.HPSagainstMuonTight);
				_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
				_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr);
				_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr);
				_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr);
				_Tau1HPSdecayModeFinding						.push_back(Tau.HPSdecayModeFinding);
			
				// Leading track variables
				_Tau1LTPt			.push_back(Tau.leadingTrackPt);
				_Tau1Charge			.push_back(Tau.charge);
				_Tau1LTvalid		.push_back(Tau.leadingTrackValid);
				_Tau1LTIpVtdxy		.push_back(Tau.leadingTrackIpVtdxy);
				_Tau1LTIpVtdz		.push_back(Tau.leadingTrackIpVtdz);
				_Tau1LTIpVtdxyError	.push_back(Tau.leadingTrackIpVtdxyError);
				_Tau1LTIpVtdzError	.push_back(Tau.leadingTrackIpVtdzError);
				_Tau1LTvx			.push_back(Tau.leadingTrackVx);
				_Tau1LTvy			.push_back(Tau.leadingTrackVy);
				_Tau1LTvz			.push_back(Tau.leadingTrackVz);
				_Tau1LTValidHits	.push_back(Tau.leadingTrackValidHits);
				_Tau1LTNormChiSqrd	.push_back(Tau.leadingTrackNormChiSqrd);

				// Provenance
				vector<int> undesiredIDs;
				undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
				undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
				undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
				undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
				//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
				undesiredIDs.push_back(25);									// No H
				//undesiredIDs.push_back(21);									// No g

				BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
				BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);

				BNmcparticle tauGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Tau, 0.25);
				_Tau1GenMatchDaughter0Id			.push_back(tauGenMatch.daughter0Id);
				_Tau1GenMatchDaughter1Id			.push_back(tauGenMatch.daughter1Id);
				_Tau1GenMatchId						.push_back(tauGenMatch.id);
				_Tau1GenMatchMother0Id				.push_back(tauGenMatch.mother0Id);
				_Tau1GenMatchMother1Id				.push_back(tauGenMatch.mother1Id);
				_Tau1GenMatchGrandmother00Id		.push_back(tauGenMatch.grandMother00Id);
				_Tau1GenMatchGrandmother01Id		.push_back(tauGenMatch.grandMother01Id);
				_Tau1GenMatchGrandmother10Id		.push_back(tauGenMatch.grandMother10Id);
				_Tau1GenMatchGrandmother11Id		.push_back(tauGenMatch.grandMother11Id);
				_Tau1GenMatchDaughter0Status		.push_back(tauGenMatch.daughter0Status);
				_Tau1GenMatchDaughter1Status		.push_back(tauGenMatch.daughter1Status);
				_Tau1GenMatchStatus					.push_back(tauGenMatch.status);
				_Tau1GenMatchMother0Status			.push_back(tauGenMatch.mother0Status);
				_Tau1GenMatchMother1Status			.push_back(tauGenMatch.mother1Status);
				_Tau1GenMatchGrandmother00Status	.push_back(tauGenMatch.grandMother00Status);
				_Tau1GenMatchGrandmother01Status	.push_back(tauGenMatch.grandMother01Status);
				_Tau1GenMatchGrandmother10Status	.push_back(tauGenMatch.grandMother10Status);
				_Tau1GenMatchGrandmother11Status	.push_back(tauGenMatch.grandMother11Status);

}


void DitauLeptonFiller::FillTau2(const BNtau& Tau){
				_Tau2Pt											.push_back(Tau.pt);
				_Tau2Eta										.push_back(Tau.eta);
				_Tau2Phi										.push_back(Tau.phi);
				_Tau2NProngs									.push_back(Tau.numProngs);
				_Tau2NSignalGammas								.push_back(Tau.numSignalGammas);
				_Tau2NSignalNeutrals							.push_back(Tau.numSignalNeutrals);
				_Tau2DecayMode									.push_back(Tau.decayMode);
				_Tau2EmFraction									.push_back(Tau.emFraction);
				_Tau2IsInTheCracks								.push_back(Tau.inTheCracks);
				_Tau2HPSagainstElectronMVA						.push_back(Tau.HPSagainstElectronMVA);
				_Tau2HPSagainstElectronLoose					.push_back(Tau.HPSagainstElectronLoose);
				_Tau2HPSagainstElectronMedium					.push_back(Tau.HPSagainstElectronMedium);
				_Tau2HPSagainstElectronTight					.push_back(Tau.HPSagainstElectronTight);
				_Tau2HPSagainstMuonLoose						.push_back(Tau.HPSagainstMuonLoose);
				_Tau2HPSagainstMuonMedium						.push_back(Tau.HPSagainstMuonMedium);
				_Tau2HPSagainstMuonTight						.push_back(Tau.HPSagainstMuonTight);
				_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
				_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr);
				_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr);
				_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr);
				_Tau2HPSdecayModeFinding						.push_back(Tau.HPSdecayModeFinding);
			
				// Leading track variables
				_Tau2LTPt										.push_back(Tau.leadingTrackPt);
				_Tau2Charge										.push_back(Tau.charge);
				_Tau2LTvalid									.push_back(Tau.leadingTrackValid);
				_Tau2LTIpVtdxy									.push_back(Tau.leadingTrackIpVtdxy);
				_Tau2LTIpVtdz									.push_back(Tau.leadingTrackIpVtdz);
				_Tau2LTIpVtdxyError								.push_back(Tau.leadingTrackIpVtdxyError);
				_Tau2LTIpVtdzError								.push_back(Tau.leadingTrackIpVtdzError);
				_Tau2LTvx										.push_back(Tau.leadingTrackVx);
				_Tau2LTvy										.push_back(Tau.leadingTrackVy);
				_Tau2LTvz										.push_back(Tau.leadingTrackVz);
				_Tau2LTValidHits								.push_back(Tau.leadingTrackValidHits);
				_Tau2LTNormChiSqrd								.push_back(Tau.leadingTrackNormChiSqrd);

				// Provenance
				vector<int> undesiredIDs;
				undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
				undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
				undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
				undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
				//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
				undesiredIDs.push_back(25);									// No H
				//undesiredIDs.push_back(21);									// No g

				BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
				BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);
				BNmcparticle tauGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Tau, 0.25);
				_Tau2GenMatchDaughter0Id			.push_back(tauGenMatch.daughter0Id);
				_Tau2GenMatchDaughter1Id			.push_back(tauGenMatch.daughter1Id);
				_Tau2GenMatchId						.push_back(tauGenMatch.id);
				_Tau2GenMatchMother0Id				.push_back(tauGenMatch.mother0Id);
				_Tau2GenMatchMother1Id				.push_back(tauGenMatch.mother1Id);
				_Tau2GenMatchGrandmother00Id		.push_back(tauGenMatch.grandMother00Id);
				_Tau2GenMatchGrandmother01Id		.push_back(tauGenMatch.grandMother01Id);
				_Tau2GenMatchGrandmother10Id		.push_back(tauGenMatch.grandMother10Id);
				_Tau2GenMatchGrandmother11Id		.push_back(tauGenMatch.grandMother11Id);
				_Tau2GenMatchDaughter0Status		.push_back(tauGenMatch.daughter0Status);
				_Tau2GenMatchDaughter1Status		.push_back(tauGenMatch.daughter1Status);
				_Tau2GenMatchStatus					.push_back(tauGenMatch.status);
				_Tau2GenMatchMother0Status			.push_back(tauGenMatch.mother0Status);
				_Tau2GenMatchMother1Status			.push_back(tauGenMatch.mother1Status);
				_Tau2GenMatchGrandmother00Status	.push_back(tauGenMatch.grandMother00Status);
				_Tau2GenMatchGrandmother01Status	.push_back(tauGenMatch.grandMother01Status);
				_Tau2GenMatchGrandmother10Status	.push_back(tauGenMatch.grandMother10Status);
				_Tau2GenMatchGrandmother11Status	.push_back(tauGenMatch.grandMother11Status);
}

void DitauLeptonFiller::FillMuon(const BNmuon& Muon){
	_LeptonIsMuon.push_back(true);
	_LeptonIsElectron.push_back(false);
	_LeptonPt.push_back(Muon.pt);
	_LeptonEta.push_back(Muon.eta);
	_LeptonPhi.push_back(Muon.phi);
	_LeptonRelIso.push_back(beanHelper->GetMuonRelIso(Muon));
	_LeptonIsLoose.push_back(beanHelper->IsLooseMuon(Muon));
	_LeptonIsTight.push_back(beanHelper->IsTightMuon(Muon));
	_LeptonEventWeight.push_back(beanHelper->GetMuonSF(Muon));

	// Provenance
	vector<int> undesiredIDs;
	undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
	undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
	undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
	undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
	//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
	undesiredIDs.push_back(25);									// No H
	//undesiredIDs.push_back(21);									// No g

	BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
	BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);
	BNmcparticle muonGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Muon, 0.25);
	_LeptonGenMatchDaughter0Id			.push_back(muonGenMatch.daughter0Id);
	_LeptonGenMatchDaughter1Id			.push_back(muonGenMatch.daughter1Id);
	_LeptonGenMatchId					.push_back(muonGenMatch.id);
	_LeptonGenMatchMother0Id			.push_back(muonGenMatch.mother0Id);
	_LeptonGenMatchMother1Id			.push_back(muonGenMatch.mother1Id);
	_LeptonGenMatchGrandmother00Id		.push_back(muonGenMatch.grandMother00Id);
	_LeptonGenMatchGrandmother01Id		.push_back(muonGenMatch.grandMother01Id);
	_LeptonGenMatchGrandmother10Id		.push_back(muonGenMatch.grandMother10Id);
	_LeptonGenMatchGrandmother11Id		.push_back(muonGenMatch.grandMother11Id);
	_LeptonGenMatchDaughter0Status		.push_back(muonGenMatch.daughter0Status);
	_LeptonGenMatchDaughter1Status		.push_back(muonGenMatch.daughter1Status);
	_LeptonGenMatchStatus				.push_back(muonGenMatch.status);
	_LeptonGenMatchMother0Status		.push_back(muonGenMatch.mother0Status);
	_LeptonGenMatchMother1Status		.push_back(muonGenMatch.mother1Status);
	_LeptonGenMatchGrandmother00Status	.push_back(muonGenMatch.grandMother00Status);
	_LeptonGenMatchGrandmother01Status	.push_back(muonGenMatch.grandMother01Status);
	_LeptonGenMatchGrandmother10Status	.push_back(muonGenMatch.grandMother10Status);
	_LeptonGenMatchGrandmother11Status	.push_back(muonGenMatch.grandMother11Status);
}

void DitauLeptonFiller::FillElectron(const BNelectron& Electron){
	_LeptonIsMuon.push_back(false);
	_LeptonIsElectron.push_back(true);
	_LeptonPt.push_back(Electron.pt);
	_LeptonEta.push_back(Electron.eta);
	_LeptonPhi.push_back(Electron.phi);
	_LeptonRelIso.push_back(beanHelper->GetElectronRelIso(Electron));
	_LeptonIsLoose.push_back(beanHelper->IsLooseElectron(Electron));
	_LeptonIsTight.push_back(beanHelper->IsTightElectron(Electron));
	_LeptonEventWeight.push_back(beanHelper->GetElectronSF(Electron));

	// Provenance
	vector<int> undesiredIDs;
	undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
	undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
	undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
	undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
	//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
	undesiredIDs.push_back(25);									// No H
	//undesiredIDs.push_back(21);									// No g

	BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
	BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);
	BNmcparticle electronGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Electron, 0.25);
	_LeptonGenMatchDaughter0Id			.push_back(electronGenMatch.daughter0Id);
	_LeptonGenMatchDaughter1Id			.push_back(electronGenMatch.daughter1Id);
	_LeptonGenMatchId					.push_back(electronGenMatch.id);
	_LeptonGenMatchMother0Id			.push_back(electronGenMatch.mother0Id);
	_LeptonGenMatchMother1Id			.push_back(electronGenMatch.mother1Id);
	_LeptonGenMatchGrandmother00Id		.push_back(electronGenMatch.grandMother00Id);
	_LeptonGenMatchGrandmother01Id		.push_back(electronGenMatch.grandMother01Id);
	_LeptonGenMatchGrandmother10Id		.push_back(electronGenMatch.grandMother10Id);
	_LeptonGenMatchGrandmother11Id		.push_back(electronGenMatch.grandMother11Id);
	_LeptonGenMatchDaughter0Status		.push_back(electronGenMatch.daughter0Status);
	_LeptonGenMatchDaughter1Status		.push_back(electronGenMatch.daughter1Status);
	_LeptonGenMatchStatus				.push_back(electronGenMatch.status);
	_LeptonGenMatchMother0Status		.push_back(electronGenMatch.mother0Status);
	_LeptonGenMatchMother1Status		.push_back(electronGenMatch.mother1Status);
	_LeptonGenMatchGrandmother00Status	.push_back(electronGenMatch.grandMother00Status);
	_LeptonGenMatchGrandmother01Status	.push_back(electronGenMatch.grandMother01Status);
	_LeptonGenMatchGrandmother10Status	.push_back(electronGenMatch.grandMother10Status);
	_LeptonGenMatchGrandmother11Status	.push_back(electronGenMatch.grandMother11Status);
}

void DitauLeptonFiller::FillDitauLepton(const BNtau& Tau1, const BNtau& Tau2, const BNmuon& Muon){
	_DitauVisibleMass	.push_back(GetComboMassBN(Tau1, Tau2));
	_DitauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi - Tau2.phi))));
	_DitauDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Tau2.eta, Tau2.phi));
	_Tau1LeptonDeltaR	.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Muon.eta, Muon.phi));
	_Tau2LeptonDeltaR	.push_back(reco::deltaR(Tau2.eta, Tau2.phi, Muon.eta, Muon.phi));
}

void DitauLeptonFiller::FillDitauLepton(const BNtau& Tau1, const BNtau& Tau2, const BNelectron& Electron){
	_DitauVisibleMass	.push_back(GetComboMassBN(Tau1, Tau2));
	_DitauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi - Tau2.phi))));
	_DitauDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Tau2.eta, Tau2.phi));
	_Tau1LeptonDeltaR	.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Electron.eta, Electron.phi));
	_Tau2LeptonDeltaR	.push_back(reco::deltaR(Tau2.eta, Tau2.phi, Electron.eta, Electron.phi));
}
