//  Created by Baranyai David on 2017. 11. 02.

#include "BM1DOpen.hh"

BM1DOpen::BM1DOpen()
{
    
}
BM1DOpen::~BM1DOpen()
{
    
}


void BM1DOpen::OpenfromTree(const char *filename)
{
    fIn = new TFile(filename,"READ");
    if (fIn->IsZombie())
    {
        std::cout << "Error opening file" << std::endl;
        exit(-1);
    }

    T2 = (TTree*)fIn->Get("BM1DTree");
    T3 = (TTree*)fIn->Get("DataTree");

    T2->SetBranchAddress("xl",&xl);
    T2->SetBranchAddress("tl",&tl);

    T3->SetBranchAddress("P0",&P0);
    T3->SetBranchAddress("P1",&P1);
    T3->SetBranchAddress("Steps",&Steps);
    T3->SetBranchAddress("NumberofRuns",&NumberofRuns);
    T3->SetBranchAddress("BottomLayer",&BottomLayer);
    T3->SetBranchAddress("UpperLayer",&UpperLayer);
    T3->SetBranchAddress("InnerMean",&InnerMean);
    T3->SetBranchAddress("ExternalMean",&ExternalMean);
    T3->SetBranchAddress("InnerSigma",&InnerSigma);
    T3->SetBranchAddress("ExternalSigma",&ExternalSigma);

    nentries = T2->GetEntries();

    for (Long64_t i=0;i<nentries;i++)
    {
            T2->GetEntry(i);
            t.push_back(tl);
            x.push_back(xl);
    }

    nentries = T3->GetEntries();
    for (Long64_t i=0;i<nentries;i++)
    {
            T3->GetEntry(i);
    }

    fIn->Close();
    
}

std::vector<Double_t> BM1DOpen::GetT()
{
    return t;
}

std::vector<Double_t> BM1DOpen::GetX()
{
    return x;
}

Double_t BM1DOpen::GetMu1()
{
    return InnerMean;
}

Double_t BM1DOpen::GetMu2()
{
    return ExternalMean;
}

Double_t BM1DOpen::GetSigma1()
{
    return InnerSigma;
}

Double_t BM1DOpen::GetSigma2()
{
    return ExternalMean;
}

Double_t BM1DOpen::Getx1()
{
    return BottomLayer;
}

Double_t BM1DOpen::Getx2()
{
    return UpperLayer;
}

Int_t BM1DOpen::GetP0()
{
    return (Int_t)P0;
}

Int_t BM1DOpen::GetP1()
{
    return (Int_t)P1;
}

Int_t BM1DOpen::GetSteps()
{
    return (Int_t)Steps;
}

Int_t BM1DOpen::GetnRuns()
{
    return (Int_t)NumberofRuns;
}
