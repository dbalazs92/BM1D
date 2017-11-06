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
  
  void Run(const int & nRuns, const int & nSteps, const  double & p0, const double & p1);
  void Run(const int & nRuns, const int & nSteps, const  double & p0, const double & mu, const double & sigma);
  void Run(const int & nRuns, const int & nSteps, const double & p0, const double & x1, const double & x2, const double & mu1, const double & sigma1, const double &mu2, const double & sigma2);
  void Run(const int & nRuns, const int & nSteps, const double & p0, const double & x1, const double & x2, const double & mu1, const double & sigma1, const double &mu2, const double & sigma2, const double & j_mu1, const double & j_sigma1, const double  & rat);

  const std::vector<Double_t> & GetT(){return t;}
  const std::vector<Double_t> & GetX(){return x;}

 private:
  TRandom3* randomGenerator;
  TRandom3* randomGeneratorGauss;
  //TF1* jump;
  Double_t rand1;
  std::vector<Double_t> t;
  std::vector<Double_t> x;
};
  
#endif  
 
