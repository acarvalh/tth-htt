#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

hadTauGenMatchEntry::hadTauGenMatchEntry(const std::string & name,
                                         int idx,
                                         int numGenMatchedHadTaus,
                                         int numGenMatchedElectrons,
                                         int numGenMatchedMuons,
                                         int numGenMatchedJets)
  : name_(name)
  , idx_(idx)
  , numGenMatchedHadTaus_(numGenMatchedHadTaus)
  , numGenMatchedElectrons_(numGenMatchedElectrons)
  , numGenMatchedMuons_(numGenMatchedMuons)
  , numGenMatchedJets_(numGenMatchedJets)
{}

std::vector<hadTauGenMatchEntry>
getHadTauGenMatch_definitions_1tau(bool apply_hadTauGenMatching)
{
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions;
  if(apply_hadTauGenMatching)
  {
    hadTauGenMatch_definitions = {
      { "1t0e0m0j", kGen_1t0e0m0j, 1, 0, 0, 0 },
      { "0t1e0m0j", kGen_0t1e0m0j, 0, 1, 0, 0 },
      { "0t0e1m0j", kGen_0t0e1m0j, 0, 0, 1, 0 },
      { "0t0e0m1j", kGen_0t0e0m1j, 0, 0, 0, 1 }
    };
  }
  else
  {
    hadTauGenMatch_definitions = { { "all", kGen_HadTauAll1, -1, -1, -1, -1 } };
  }
  return hadTauGenMatch_definitions;
}

std::vector<hadTauGenMatchEntry>
getHadTauGenMatch_definitions_2tau(bool apply_hadTauGenMatching)
{
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions;
  if(apply_hadTauGenMatching)
  {
    hadTauGenMatch_definitions = {
      { "2t0e0m0j", kGen_2t0e0m0j, 2, 0, 0, 0 },
      { "1t1e0m0j", kGen_1t1e0m0j, 1, 1, 0, 0 },
      { "1t0e1m0j", kGen_1t0e1m0j, 1, 0, 1, 0 },
      { "1t0e0m1j", kGen_1t0e0m1j, 1, 0, 0, 1 },
      { "0t2e0m0j", kGen_0t2e0m0j, 0, 2, 0, 0 },
      { "0t1e1m0j", kGen_0t1e1m0j, 0, 1, 1, 0 },
      { "0t1e0m1j", kGen_0t1e0m1j, 0, 1, 0, 1 },
      { "0t0e2m0j", kGen_0t0e2m0j, 0, 0, 2, 0 },
      { "0t0e1m1j", kGen_0t0e1m1j, 0, 0, 1, 1 },
      { "0t0e0m2j", kGen_0t0e0m2j, 0, 0, 0, 2 }
    };
  }
  else
  {
    hadTauGenMatch_definitions = { { "all", kGen_HadTauAll2, -1, -1, -1, -1 } };
  }
  return hadTauGenMatch_definitions;
}

std::vector<hadTauGenMatchEntry>
getHadTauGenMatch_definitions_3tau(bool apply_hadTauGenMatching)
{
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions;
  if(apply_hadTauGenMatching)
  {
    hadTauGenMatch_definitions = {
      { "3t0e0m0j", kGen_3t0e0m0j, 3, 0, 0, 0 },
      { "2t1e0m0j", kGen_2t1e0m0j, 2, 1, 0, 0 },
      { "2t0e1m0j", kGen_2t0e1m0j, 2, 0, 1, 0 },
      { "2t0e0m1j", kGen_2t0e0m1j, 2, 0, 0, 1 },
      { "1t2e0m0j", kGen_1t2e0m0j, 1, 2, 0, 0 },
      { "1t1e1m0j", kGen_1t1e1m0j, 1, 1, 1, 0 },
      { "1t1e0m1j", kGen_1t1e0m1j, 1, 1, 0, 1 },
      { "1t0e2m0j", kGen_1t0e2m0j, 1, 0, 2, 0 },
      { "1t0e1m1j", kGen_1t0e1m1j, 1, 0, 1, 1 },
      { "1t0e0m2j", kGen_1t0e0m2j, 1, 0, 0, 2 },
      { "0t3e0m0j", kGen_0t3e0m0j, 0, 3, 0, 0 },
      { "0t2e1m0j", kGen_0t2e1m0j, 0, 2, 1, 0 },
      { "0t2e0m1j", kGen_0t2e0m1j, 0, 2, 0, 1 },
      { "0t1e2m0j", kGen_0t1e2m0j, 0, 1, 2, 0 },
      { "0t1e1m1j", kGen_0t1e1m1j, 0, 1, 1, 1 },
      { "0t1e0m2j", kGen_0t1e0m2j, 0, 1, 0, 2 },
      { "0t0e3m0j", kGen_0t0e3m0j, 0, 0, 3, 0 },
      { "0t0e2m1j", kGen_0t0e2m1j, 0, 0, 2, 1 },
      { "0t0e1m2j", kGen_0t0e1m2j, 0, 0, 1, 2 },
      { "0t0e0m3j", kGen_0t0e0m3j, 0, 0, 0, 3 }
    };
  }
  else
  {
    hadTauGenMatch_definitions = { { "all", kGen_HadTauAll3, -1, -1, -1, -1 } };
  }
  return hadTauGenMatch_definitions;
}

std::string
getHadTauGenMatch_string(const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions,
                         int hadTauGenMatch_int)
{
  const hadTauGenMatchEntry * hadTauGenMatch = nullptr;
  for(const hadTauGenMatchEntry & hadTauGenMatch_definition: hadTauGenMatch_definitions)
  {
    if(hadTauGenMatch_definition.idx_ == hadTauGenMatch_int)
    {
      hadTauGenMatch = &hadTauGenMatch_definition;
    }
  }
  if(! hadTauGenMatch)
  {
    throw cmsException(__func__, __LINE__)
      << "Invalid parameter 'hadTauGenMatch_int' = " << hadTauGenMatch_int;
  }
  return hadTauGenMatch->name_;
}

int
getHadTauGenMatch_int(const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions,
                      const std::string & hadTauGenMatch_string)
{
  const hadTauGenMatchEntry * hadTauGenMatch = nullptr;
  for(const hadTauGenMatchEntry & hadTauGenMatch_definition: hadTauGenMatch_definitions)
  {
    if(hadTauGenMatch_definition.name_ == hadTauGenMatch_string)
    {
      hadTauGenMatch = &hadTauGenMatch_definition;
    }
  }
  if(! hadTauGenMatch)
    throw cmsException(__func__, __LINE__)
      << "Invalid parameter 'hadTauGenMatch_string' = " << hadTauGenMatch_string;
  return hadTauGenMatch->idx_;
}

namespace
{
  void
  countHadTauGenMatches(const RecoHadTau * hadTau,
                        int & numGenMatchedHadTaus,
                        int & numGenMatchedElectrons,
                        int & numGenMatchedMuons,
                        int & numGenMatchedJets)
  {
    if     (hadTau->genHadTau()                                                ) ++numGenMatchedHadTaus;
    else if(hadTau->genLepton() && std::abs(hadTau->genLepton()->pdgId()) == 11) ++numGenMatchedElectrons;
    else if(hadTau->genLepton() && std::abs(hadTau->genLepton()->pdgId()) == 13) ++numGenMatchedMuons;
    else                                                                         ++numGenMatchedJets;
  }

  bool constexpr
  matches(int nSel,
          int nMatches)
  {
    return nSel == -1 || nSel == nMatches;
  }

  const hadTauGenMatchEntry &
  getHadTauGenMatch(const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions,
                    int numGenMatchedHadTaus,
                    int numGenMatchedElectrons,
                    int numGenMatchedMuons,
                    int numGenMatchedJets)
  {
    const hadTauGenMatchEntry * hadTauGenMatch = nullptr;
    for(const hadTauGenMatchEntry & hadTauGenMatch_definition: hadTauGenMatch_definitions)
    {
      if(matches(hadTauGenMatch_definition.numGenMatchedHadTaus_,   numGenMatchedHadTaus)   &&
         matches(hadTauGenMatch_definition.numGenMatchedElectrons_, numGenMatchedElectrons) &&
         matches(hadTauGenMatch_definition.numGenMatchedMuons_,     numGenMatchedMuons)     &&
         matches(hadTauGenMatch_definition.numGenMatchedJets_,      numGenMatchedJets)       )
      {
        hadTauGenMatch = &hadTauGenMatch_definition;
      }
    }
    if(! hadTauGenMatch)
    {
      throw cmsException(__func__, __LINE__)
        << "Failed to compute 'hadTauGenMatch' for numGenMatched:"
           " hadTaus = "   << numGenMatchedHadTaus << ","
           " electrons = " << numGenMatchedElectrons << ","
           " muons = "     << numGenMatchedMuons << ","
           " jets = "      << numGenMatchedJets
      ;
    }
    return *hadTauGenMatch;
  }
}

const hadTauGenMatchEntry &
getHadTauGenMatch(const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions,
                  const RecoHadTau * hadTau_lead,
                  const RecoHadTau * hadTau_sublead,
                  const RecoHadTau * hadTau_third)
{
  int numGenMatchedHadTaus = 0;
  int numGenMatchedElectrons = 0;
  int numGenMatchedMuons = 0;
  int numGenMatchedJets = 0;

  const auto countHadTauGenMatches_local = [&](const RecoHadTau * hadTau) -> void
  {
    return countHadTauGenMatches(
      hadTau, numGenMatchedHadTaus, numGenMatchedElectrons, numGenMatchedMuons, numGenMatchedJets
    );
  };

  assert(hadTau_lead);
  countHadTauGenMatches_local(hadTau_lead);
  if(hadTau_sublead)
  {
    countHadTauGenMatches_local(hadTau_sublead);
  }
  if(hadTau_third)
  {
    countHadTauGenMatches_local(hadTau_third);
  }

  return getHadTauGenMatch(
    hadTauGenMatch_definitions, numGenMatchedHadTaus, numGenMatchedElectrons, numGenMatchedMuons, numGenMatchedJets
  );
}

std::ostream &
operator<<(std::ostream & stream,
           const hadTauGenMatchEntry & hadTauGenMatch_definition)
{
  stream << " hadTauGenMatch #" << hadTauGenMatch_definition.idx_
         << ": "                << hadTauGenMatch_definition.name_
         << '\n';
  return stream;
}

std::ostream &
operator<<(std::ostream & stream,
           const std::vector<hadTauGenMatchEntry> & hadTauGenMatch_definitions)
{
  for(const hadTauGenMatchEntry & hadTauGenMatch_definition: hadTauGenMatch_definitions)
  {
    stream << hadTauGenMatch_definition;
  }
  return stream;
}
