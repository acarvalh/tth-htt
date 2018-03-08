#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_1l_2tau_h

/** \class EvtHistManager_1l_2tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 1l_2tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

class EvtHistManager_1l_2tau
  : public HistManagerBase
{
 public:
  EvtHistManager_1l_2tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_1l_2tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
    double mvaOutput_1l_2tau_ttbar,
    double mvaOutput_1l_2tau_ttbar_Old,
<<<<<<< HEAD
    double mvaOutput_1l_2tau_ttbar_HTTLepID,
    double mvaOutput_1l_2tau_ttbar_OldVar,
    double mvaOutput_1l_2tau_ttbar_OldVarHTT,
    double mvaOutput_1l_2tau_ttV, double mvaDiscr_1l_2tau, double mTauTauVis,
    //////////////
    double mvaOutput_sum_HTT_T,
    double mvaOutput_sum_noHTT_T,
    double mvaOutput_sum_HTT_VT,
    double mvaOutput_sum_noHTT_VT,
    /////////////
    double mvaOutput_ttbar_HTT,
    double mvaOutput_ttbar_noHTT,
    double mvaOutput_ttV_noHTT,
    double mvaOutput_ttV_HTT,
    double mvaOutput_ttbar_OldVar,
    double mvaOutput_1B_HTT,
    double mvaOutput_1B_noHTT,
    double mvaOutput_1B_HTT_T,
    double mvaOutput_1B_noHTT_T,
    double mvaOutput_1B_HTT_VT,
    double mvaOutput_1B_noHTT_VT,
    /////////////
=======
    double mvaOutput_1l_2tau_ttV,
    double mvaDiscr_1l_2tau,
    double mTauTauVis,
>>>>>>> 0b2420ef3aba978a760b35fcc50abdc4d44791e2
    double evtWeight);

  const TH1* getHistogram_EventCounter() const { return histogram_EventCounter_; }

 private:
  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH2* histogram_numBJets_loose_vs_numJets_;  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  TH2* histogram_numBJets_medium_vs_numJets_; //     to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)

  TH1* histogram_mvaOutput_1l_2tau_ttbar_;
  TH1* histogram_mvaOutput_1l_2tau_ttbar_Old_;
  TH1* histogram_mvaOutput_1l_2tau_ttbar_Old_5bins_;
<<<<<<< HEAD
  TH1* histogram_mvaOutput_1l_2tau_ttbar_HTTLepID_;
  TH1* histogram_mvaOutput_1l_2tau_ttbar_OldVar_;
  TH1* histogram_mvaOutput_1l_2tau_ttbar_OldVarHTT_;

  /////////////
  TH1* histogram_mvaOutput_ttbar_HTT_;
  TH1* histogram_mvaOutput_ttbar_noHTT_;

  /////////////
  TH1* histogram_mvaOutput_sum_HTT_T_;
  TH1* histogram_mvaOutput_sum_noHTT_T_;

  TH1* histogram_mvaOutput_sum_HTT_VT_;
  TH1* histogram_mvaOutput_sum_noHTT_VT_;

  TH1* histogram_mvaOutput_ttV_noHTT_;
  TH1* histogram_mvaOutput_ttV_HTT_;
  TH1* histogram_mvaOutput_ttbar_OldVar_;

  TH1* histogram_mvaOutput_1B_HTT_;
  TH1* histogram_mvaOutput_1B_noHTT_;

  TH1* histogram_mvaOutput_1B_HTT_T_;
  TH1* histogram_mvaOutput_1B_noHTT_T_;

  TH1* histogram_mvaOutput_1B_HTT_VT_;
  TH1* histogram_mvaOutput_1B_noHTT_VT_;
  /////////////
=======
>>>>>>> 0b2420ef3aba978a760b35fcc50abdc4d44791e2

  TH1* histogram_mvaOutput_1l_2tau_ttV_;
  TH1* histogram_mvaDiscr_1l_2tau_;

  TH1* histogram_mTauTauVis_;

  TH1* histogram_EventCounter_;

};

#endif
