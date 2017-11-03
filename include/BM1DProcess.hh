#ifndef BM1DProcess_h
#define BM1DProcess_h 1

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "TRandom.h"
#include "TF1.h"
#include "BM1DRandomGenerator.hh"

class BM1DProcess {
public:
  BM1DProcess(); 
  ~BM1DProcess();
  
  void Run(int nSteps, int nRuns, double p0, double p1);
  void Run(int nSteps, int nRuns, double p0, double mu, double sigma);
  void Run(int nSteps, int nRuns, double p0, double x1, double x2, double mu1, double sigma1, double mu2,  double sigma2);
  void Run(int nRuns, int nSteps, double p0, double x1, double x2, double mu1, double sigma1, double mu2, double sigma2, double j_mu1, double j_sigma1, double rat);

  std::vector<Double_t> GetT(){return t;}
  std::vector<Double_t> GetX(){return x;}

 private:
  TRandom* randomGenerator;
  TRandom* randomGeneratorGauss;
  //TF1* jump;
  Double_t rand1;
  std::vector<Double_t> t;
  std::vector<Double_t> x;
};
  
#endif  
 
