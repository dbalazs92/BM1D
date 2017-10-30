#include "Plotter.hh"

Plotter::Plotter()
{
  ;
}
void Plotter::Plot(Int_t n, std::vector<Double_t> t, std::vector<Double_t> x){
  fOut = new TFile("result.root", "RECREATE");
  g1 = new TGraph(n,&t[0],&x[0]);
  canv = new TCanvas("canc","display",800,400);
  TTree *BM1DTree = new TTree("BM1DTree","BM1DTree");
  
  g1->Draw();
  g1->SetLineColor(1);
  g1->SetLineWidth(1);
  g1->SetMarkerColor(1);
  g1->SetMarkerStyle(0);
  g1->SetTitle("Brownian Movement D=1");
  g1->GetYaxis()->SetTitle("X");
  g1->GetXaxis()->SetTitle("Time");
  
  BM1DTree->Branch("tl",&tl, "tl/D");
  BM1DTree->Branch("xl",&xl, "xl/D");
  for (unsigned int i = 0; i < t.size(); i++){
    tl = t[i];
    xl = x[i];
    BM1DTree->Fill();
  }
  
  g1->Write();
  BM1DTree->Write();
  fOut->Close();
  
}

