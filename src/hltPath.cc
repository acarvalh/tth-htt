#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h"

#include <TTree.h> // TTree

#include <iostream> // std::ostream
#include <algorithm> // std::any_of()
#include <cassert> // assert()

hltPath::hltPath(const std::string & branchName,
                 double minPt,
                 double maxPt,
                 const std::string & label)
  : branchName_(branchName)
  , value_(-1)
  , minPt_(minPt)
  , maxPt_(maxPt)
  , label_(label)
{}

void
hltPath::setBranchAddress(TTree * tree)
{
  tree->SetBranchAddress(branchName_.data(), &value_);
}

void
hltPath::setBranchAddresses(TTree * tree)
{
  return setBranchAddress(tree);
}

const std::string &
hltPath::getBranchName() const
{
  return branchName_;
}

Int_t
hltPath::getValue() const
{
  assert(value_ == 0 || value_ == 1);
  return value_;
}

double
hltPath::getMinPt() const
{
  return minPt_;
}

double
hltPath::getMaxPt() const
{
  return maxPt_;
}

const std::string &
hltPath::getLabel() const
{
  return label_;
}

std::vector<hltPath *>
create_hltPaths(const std::vector<std::string> & branchNames,
                const std::string & label)
{
  std::vector<hltPath *> hltPaths;
  for(const std::string & branchName: branchNames)
  {
    hltPaths.push_back(new hltPath(branchName, -1., -1., label));
  }
  return hltPaths;
}

void
hltPaths_setBranchAddresses(TTree * tree,
                            const std::vector<hltPath *> & hltPaths)
{
  for(hltPath * const & path: hltPaths)
  {
    path->setBranchAddress(tree);
  }
}

bool
hltPaths_isTriggered(const std::vector<hltPath *> & hltPaths,
                     bool verbose)
{
  return std::any_of(
    hltPaths.cbegin(), hltPaths.cend(),
    [verbose](hltPath * const & path) -> bool
    {
      const bool passes = path->getValue() >= 1;
      if(verbose)
      {
        std::cout << "  " << path->getLabel() << ": " << *path;
      }
      return passes;
    }
  );
}

void
hltPaths_delete(const std::vector<hltPath *> & hltPaths)
{
  for(hltPath * path: hltPaths)
  {
    delete path;
    path = nullptr;
  }
}

std::ostream &
operator<<(std::ostream & stream,
           const hltPath & hltPath_iter)
{
  stream << "hltPath = " << hltPath_iter.getBranchName() << ": "
            "value = "   << hltPath_iter.getValue()
         << " (minPt = " << hltPath_iter.getMinPt() << ", "
              "maxPt = " << hltPath_iter.getMaxPt() << ")\n";
  return stream;
}
