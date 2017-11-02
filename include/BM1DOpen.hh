//  Created by Baranyai David on 2017. 11. 02.

#ifndef BM1DOpen_h
#define BM1DOpen_h 1

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"

class BM1DOpen {
public:
    BM1DOpen();
    ~BM1DOpen();
    void OpenfromTree(const char* filename);
    std::vector<Double_t> GetT();    
    std::vector<Double_t> GetX();
    Double_t GetMu1();
    Double_t GetMu2();
    Double_t GetSigma1();
    Double_t GetSigma2();
    Double_t Getx1();
    Double_t Getx2();
    Int_t GetP0();
    Int_t GetP1();
    Int_t GetSteps();
    Int_t GetnRuns();
private:
    TFile* fIn;
    TTree *T2, *T3;
    Long64_t nentries;
    std::vector<Double_t> t;
    std::vector<Double_t> x;
    Double_t InnerMean,ExternalMean,InnerSigma,ExternalSigma,tl,xl,x1,x2;
    Double_t P0, P1, Steps, NumberofRuns,BottomLayer,UpperLayer;
};
#endif
