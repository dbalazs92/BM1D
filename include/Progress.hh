/// BM1D program. Date: 2017-10-29 Creators: Balázs Demeter, Balázs Ujvári 

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
 ~Progress();
 
 void Count(char a);
 
 std::vector<Double_t> GetX();
 std::vector<Double_t> GetY();

private:
 
 TRandom* random1;
 const Int_t n;
 std::vector<Double_t> x;
 std::vector<Double_t> y;
 
};

#endif


