#ifndef Plotter_h
#define Plotter_h 1

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
#include "TCanvas.h"
#include "TGraph.h"
#include "TTree.h"

class Plotter {
public:
  Plotter();
  void Plot(Int_t n, std::vector<Double_t> t, std::vector<Double_t> x);
private:
  TGraph* g1;
  TFile* fOut;
  TCanvas* canv;
  TTree *BM1DTree;
  Double_t tl,xl;
};
#endif
