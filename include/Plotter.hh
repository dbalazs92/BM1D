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
#include "TMultiGraph.h"

class Plotter
{
public:
  Plotter(bool draw);
  ~Plotter();
  void Plot(Int_t numRuns, Int_t nSteps, std::vector<Double_t> t, std::vector<Double_t> x);
  TMultiGraph * GetTmultiGraph();
  
  static unsigned int IDCounter;
  
private:
  bool draw;
  TMultiGraph *mg;
  TGraph* g1;
  TCanvas* canv;
  Double_t tl,xl;
  unsigned int ID;
};
#endif
