#ifndef tthAnalysis_HiggsToTauTau_lutAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_lutAuxFunctions_h

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include <type_traits> // std::enable_if<>, std::is_arithmetic<>

// forward declarations
class TFile;
class TH1;
class TH2;
class TF1;
class TGraph;

namespace lut
{
  enum { kXpt, kXeta, kXabsEta, kXptYpt, kXptYeta, kXptYabsEta, kXetaYpt, kXabsEtaYpt };
}

// define auxiliary functions
TFile *
openFile(const LocalFileInPath & fileName);

TH1 *
loadTH1(TFile * inputFile,
        const std::string & histogramName);

TH2 *
loadTH2(TFile * inputFile,
        const std::string & histogramName);

TGraph *
loadTGraph(TFile * inputFile,
           const std::string & graphName);

TF1 *
loadTF1(TFile * inputFile,
        const std::string & functionName);

double
getSF_from_TH1(TH1 * lut,
               double x);

double
getSF_from_TH2(TH2 * lut,
               double x,
               double y);

double
getSF_from_TH2Poly(TH2 * lut,
                   double x,
                   double y);

double
getSF_from_TGraph(TGraph * lut,
                  double x);

class lutWrapperBase
{
public:
  lutWrapperBase();
  lutWrapperBase(const std::string & lutName,
                 int lutType,
                 double xMin = -1.,
                 double xMax = -1.,
                 double yMin = -1.,
                 double yMax = -1.);
  lutWrapperBase(std::map<std::string, TFile *> & inputFiles,
                 const std::string & inputFileName,
                 const std::string & lutName,
                 int lutType,
                 double xMin = -1.,
                 double xMax = -1.,
                 double yMin = -1.,
                 double yMax = -1.);
  virtual ~lutWrapperBase() {}

  double
  getSF(double pt,
        double eta);

  const std::string & inputFileName() const;
  const std::string & lutName() const;

protected:
  void initialize(int lutType);
  enum { kUndefined, kPt, kEta, kAbsEta };

  std::string inputFileName_;
  TFile * inputFile_;
  std::string lutName_;
  int lutTypeX_;
  int lutTypeY_;
  double xMin_;
  double xMax_;
  double yMin_;
  double yMax_;
private:
  virtual double getSF_private(double x,
                               double y) = 0;
};

typedef std::vector<lutWrapperBase *> vLutWrapperBase;
double
get_from_lut(const vLutWrapperBase & corrections,
             double pt,
             double eta,
             bool isDEBUG = false);

class lutWrapperTH1
  : public lutWrapperBase
{
public:
  lutWrapperTH1(std::map<std::string, TFile *> & inputFiles,
                const std::string & inputFileName,
                const std::string & lutName,
                int lutType,
                double xMin = -1.,
                double xMax = -1.,
                double yMin = -1.,
                double yMax = -1.);
private:
  double getSF_private(double x,
                       double y) override;
  TH1 * lut_;
};

class lutWrapperTH2
  : public lutWrapperBase
{
public:
  lutWrapperTH2(std::map<std::string, TFile *> & inputFiles,
                const std::string & inputFileName,
                const std::string & lutName,
                int lutType,
                double xMin = -1.,
                double xMax = -1.,
                double yMin = -1.,
                double yMax = -1.);
private:
  double getSF_private(double x,
                       double y) override;
  TH2 * lut_;
};

class lutWrapperTH2Poly
  : public lutWrapperBase
{
public:
  lutWrapperTH2Poly(std::map<std::string, TFile *> & inputFiles,
                    const std::string & inputFileName,
                    const std::string & lutName,
                    int lutType,
                    double xMin = -1.,
                    double xMax = -1.,
                    double yMin = -1.,
                    double yMax = -1.);
private:
  double getSF_private(double x,
                       double y) override;
  TH2 * lut_;
};

class lutWrapperTGraph
  : public lutWrapperBase
{
public:
  lutWrapperTGraph(std::map<std::string, TFile *> & inputFiles,
                   const std::string & inputFileName,
                   const std::string & lutName,
                   int lutType,
                   double xMin = -1.,
                   double xMax = -1.,
                   double yMin = -1.,
                   double yMax = -1.);
 private:
  double getSF_private(double x,
                       double y) override;
  TGraph * lut_;
};

class lutWrapperCrystalBall
  : public lutWrapperBase
{
public:
  lutWrapperCrystalBall(const std::string & lutName,
                        const edm::ParameterSet & cfg,
                        int lutType,
                        double xMin = -1.,
                        double xMax = -1.,
                        double yMin = -1.,
                        double yMax = -1.);
private:
  double getSF_private(double x,
                       double y) override;
  double m0_;
  double sigma_;
  double alpha_;
  double n_;
  double norm_;
};

class lutWrapperData_to_MC
  : public lutWrapperBase
{
public:
  lutWrapperData_to_MC(lutWrapperBase * lutData,
                       lutWrapperBase * lutMC);
  ~lutWrapperData_to_MC();
private:
  double getSF_private(double x,
                       double y) override;
  lutWrapperBase * lutData_;
  lutWrapperBase * lutMC_;
};

#endif // tthAnalysis_HiggsToTauTau_lutAuxFunctions_h
