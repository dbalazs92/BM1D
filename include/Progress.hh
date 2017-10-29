/// BM1D program. Date: 2017-10-29 Creators: Balázs Demeter, Balázs Ujvári, Dávid Baranyai

#ifndef Progress_h
#define Progress_h 1

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
#include "TRandom.h"
#include "TMath.h"
#include "TCanvas.h"

class Progress {

public:

 Progress(Int_t n);
 Progress(Int_t n, Double_t p0_Set);
 Progress(Int_t n, Double_t p0_Set, Double_t startposition);
 ~Progress();
 
 void Count(char a);
 
 Double_t GetP0();
 Int_t GetSteps();
 Double_t GetNext();
 Double_t GetPrevious();
 
 void SetP0(double p0_new);
 
 std::vector<Double_t> GetX();
 std::vector<Double_t> GetY();

private:
 
 TRandom* random1;
 const Int_t n;
 std::vector<Double_t> x;
 std::vector<Double_t> y;
 
 Double_t p0;
 Double_t preVstate;
 Int_t steps;
 
};

#endif


