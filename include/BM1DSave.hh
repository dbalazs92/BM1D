#ifndef BM1DSave_h
#define BM1DSave_h 1

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "TROOT.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TMultiGraph.h"

class BM1DSave {
public:
    BM1DSave();
    ~BM1DSave();
    void SaveToTree(TMultiGraph *mg, Int_t p0, Int_t p1, Int_t nSteps, Int_t nRuns, Double_t x1, Double_t x2, Double_t mu1, Double_t mu2, Double_t sigma1, Double_t sigma2, std::vector<Double_t> t, std::vector<Double_t> x, const char* filename);
private:
  TFile* fOut;

  TTree *BM1DTree;
  TTree *DataTree;

  Double_t tl,xl;
};
#endif