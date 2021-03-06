#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauSelectorTight

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoHadTauSelectorTight::RecoHadTauSelectorTight(int era,
                                                 int index,
                                                 bool debug,
                                                 bool set_selection_flags)
  : RecoHadTauSelectorBase(era, index, debug, set_selection_flags)
{ 
  min_pt_                 = 20.;
  max_absEta_             = 2.3;
  max_dz_                 = 0.2;
  apply_decayModeFinding_ = true;
  min_antiElectron_       = -1000;
  min_antiMuon_           = -1000;
  set("dR03mvaLoose");
}

void
RecoHadTauSelectorTight::set_selection_flags(const RecoHadTau & hadTau) const
{
  hadTau.set_isTight();
}

bool
RecoHadTauSelectorTight::operator()(const RecoHadTau & hadTau) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n hadTau: " << hadTau << '\n';
  }
  return RecoHadTauSelectorBase::operator()(hadTau);
}
