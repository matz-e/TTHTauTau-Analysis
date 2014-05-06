// vim: et:sta:sw=4:ts=4
// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _NtupleFiller_h
#define _NtupleFiller_h

#include <algorithm>

#include "boost/lexical_cast.hpp"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/normalizedPhi.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"

// Headers for the BEAN data items
#include "BEAN/Collections/interface/BNevent.h"
#include "BEAN/Collections/interface/BNjet.h"
#include "BEAN/Collections/interface/BNgenjet.h"
#include "BEAN/Collections/interface/BNmcparticle.h"
#include "BEAN/Collections/interface/BNmet.h"
#include "BEAN/Collections/interface/BNelectron.h"
#include "BEAN/Collections/interface/BNmuon.h"
#include "BEAN/Collections/interface/BNlepton.h"
#include "BEAN/Collections/interface/BNleptonCollection.h"
#include "BEAN/Collections/interface/BNtau.h"
#include "BEAN/Collections/interface/BNphoton.h"
#include "BEAN/Collections/interface/BNsupercluster.h"
#include "BEAN/Collections/interface/BNtrack.h"
#include "BEAN/Collections/interface/BNtrigger.h"
#include "BEAN/Collections/interface/BNskimbits.h"
#include "BEAN/Collections/interface/BNtrigobj.h"
#include "BEAN/Collections/interface/BNprimaryvertex.h"

#include <TTree.h>

#include "Parameters.h"

using namespace std;
using namespace edm;

typedef reco::Candidate::LorentzVector LorentzVector;
typedef std::vector< reco::Candidate::LorentzVector > LVCollection;

class NtupleFiller : public EDAnalyzer {
	public:
		explicit NtupleFiller();
		explicit NtupleFiller(const ParameterSet&, BEANhelper*);
		~NtupleFiller();
		string GetName();
		virtual bool FillNtuple(const Event&, const EventSetup&);
		virtual void ClearVectors();

	protected:
		// === Core functions === //
		virtual void analyze(const Event&, const EventSetup&);
		virtual void SetupBranches();
		virtual void GetCollections(const Event&, const EventSetup&);

		// === Helper functions === //
		template <typename BNObject1, typename BNObject2, typename BNCollection> unsigned int GetNumberOfUnmatchedLeptons(const BNObject1&, const BNObject2&, const BNCollection&, const double);
		template <typename BNObject, typename BNCollection> unsigned int GetNumberOfUnmatchedLeptons(const BNObject&, const BNCollection&, const double);
		template <typename BNObject, typename BNCollection> BNCollection GetUnmatchedLeptons(const BNObject&, const BNCollection&, const double);
		template <typename BNObject1, typename BNObject2> double GetComboMassBN(const BNObject1&, const BNObject2&);
		template <typename BNObject1, typename BNObject2, typename MetObject> double GetComboMassBN(const BNObject1&, const BNObject2&, const MetObject&);
		bool IsInTheCracks(float);
		
	protected:
        Parameters params_;
		unsigned int _DebugLevel;
		string _FillerName;
		TTree* _Tree;

		BEANhelper* helper;

		string _AnalysisType;
		string _Era;
		sysType::sysType _sysType;

		// === Generator level Inputs === //
		InputTag _GenParticleSource;
		InputTag _GenJetSource;

		// === Tau and Leptons Inputs === //
		InputTag _RecoTauSource;
		InputTag _RecoMuonSource;
		InputTag _RecoElectronSource;
		bool _UseHeepInfo;
		InputTag _RecoParticleFlowSource;
		double _RecoTauMinPt;
		double _RecoTauMaxAbsEta;
		bool _RecoTauRequireDMF;

		// === Jet Inputs === //
		InputTag _RecoJetSource;
		double _RecoJetMinPt;
		double _RecoJetMinAbsEta;
		double _RecoJetMaxAbsEta;
		double _JetAntiMatchingDeltaR;
		double _CSVlooseWP;
		double _CSVmediumWP;
		double _CSVtightWP;

		// === Vertex Inputs === //
		InputTag _RecoVertexSource;
		double _RecoVertexMaxZposition;
		double _RecoVertexTrackWeight;
		int _RecoVertexMinTracks;

        // === HLT input === //
        InputTag _HLTriggerSource;

		// === Topology Inputs
		InputTag _RecoPATMetSource;
		InputTag _RecoPFMetSource;


		// === Collections === //
		BNeventCollection				_BNevents;
		BNmcparticleCollection			_BNmcparticles;
		BNgenjetCollection				_BNgenjets;
		BNelectronCollection			_BNelectrons;
		BNmuonCollection				_BNmuons;
		BNtauCollection					_BNtaus;
		BNjetCollection					_BNjets;
		BNmetCollection					_BNmets;
		BNprimaryvertexCollection		_BNvertices;
		BNtriggerCollection				_BNtrigger;
};


template <typename BNObject1, typename BNObject2, typename BNCollection> unsigned int NtupleFiller::GetNumberOfUnmatchedLeptons(const BNObject1& iObject1, const BNObject2& iObject2, const BNCollection& iCollection, const double iMinDeltaR){
	unsigned int result = 0;
	for(typename BNCollection::const_iterator It = iCollection.begin(); It != iCollection.end(); ++It){
		if(	deltaR(It->eta, It->phi, iObject1.eta, iObject1.phi) > iMinDeltaR &&
			deltaR(It->eta, It->phi, iObject2.eta, iObject2.phi) > iMinDeltaR ){ result++; }
	}
	return result;
}

template <typename BNObject, typename BNCollection> unsigned int NtupleFiller::GetNumberOfUnmatchedLeptons(const BNObject& iObject, const BNCollection& iCollection, const double iMinDeltaR){
	unsigned int result = 0;
	for(typename BNCollection::const_iterator It = iCollection.begin(); It != iCollection.end(); ++It){
		if(	deltaR(It->eta, It->phi, iObject.eta, iObject.phi) > iMinDeltaR ){ result++; }
	}
	return result;
}

template <typename BNObject, typename BNCollection> BNCollection NtupleFiller::GetUnmatchedLeptons(const BNObject& iObject, const BNCollection& iCollection, const double iMinDeltaR){
	BNCollection result;
	for(typename BNCollection::const_iterator It = iCollection.begin(); It != iCollection.end(); ++It){
		if(	deltaR((*It)->eta, (*It)->phi, iObject.eta, iObject.phi) > iMinDeltaR ){ result.push_back((*It)); }
	}
	return result;
}

template <typename BNObject1, typename BNObject2, typename MetObject> double NtupleFiller::GetComboMassBN(const BNObject1& bnObject1, const BNObject2& bnObject2, const MetObject& metObject){
	reco::Candidate::LorentzVector object1p4(bnObject1.px, bnObject1.py, bnObject1.pz, bnObject1.energy);
	reco::Candidate::LorentzVector object2p4(bnObject2.px, bnObject2.py, bnObject2.pz, bnObject2.energy);
	//reco::Candidate::LorentzVector object1p4(0,0,0,0);
	//reco::Candidate::LorentzVector object2p4(0,0,0,0);
	double px = object1p4.px() + object2p4.px() + metObject.px;
	double py = object1p4.py() + object2p4.py() + metObject.py;
	double pz = object1p4.pz() + object2p4.pz();
	double e = 0;
//	double e = bnObject1.energy + bnObject2.energy + TMath::Sqrt((metObject.px * metObject.px) + (metObject.py * metObject.py));
	reco::Candidate::LorentzVector The_LorentzVect(px, py, pz, e); 
	return The_LorentzVect.M();
}

#endif
