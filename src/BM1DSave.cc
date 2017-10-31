#include "BM1DSave.hh"

BM1DSave::BM1DSave()
{

}
BM1DSave::~BM1DSave()
{
    
}


void BM1DSave::SaveToTree(TMultiGraph *mg, Int_t p0, Int_t p1, Int_t nSteps, Int_t nRuns, Double_t x1, Double_t x2, Double_t mu1, Double_t mu2, Double_t sigma1, Double_t sigma2, std::vector<Double_t> t, std::vector<Double_t> x, const char* filename)
{
  fOut = new TFile(filename, "RECREATE");
  TTree *BM1DTree = new TTree("BM1DTree","BM1DTree");
  TTree *DataTree = new TTree("DataTree","DataTree");
  
  BM1DTree->Branch("tl",&tl, "tl/D");
  BM1DTree->Branch("xl",&xl, "xl/D");

  DataTree->Branch("P0", &p0, "p0/D");
  DataTree->Branch("P1", &p1, "p1/D");
  DataTree->Branch("Steps", &nSteps, "nSteps/D");
  DataTree->Branch("NumberofRuns", &nRuns, "nRuns/D");
  DataTree->Branch("BottomLayer", &x1, "x1/D");
  DataTree->Branch("UpperLayer", &x2, "x2/D");
  DataTree->Branch("InnerMean", &mu1, "mu1/D");
  DataTree->Branch("ExternalMean", &mu2, "mu2/D");
  DataTree->Branch("InnerSigma", &sigma1, "sigma1/D");
  DataTree->Branch("ExternalSigma", &sigma2, "sigma2/D");

  DataTree->Fill();

  mg->Write();

  for (int i = 0; i < nSteps*nRuns; i++)
  {
    tl = t[i];
    xl = x[i];
    BM1DTree->Fill();
  }
  BM1DTree->Write();
  DataTree->Write();
  fOut->Close();
  
}