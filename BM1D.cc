/// BM1D program. Date: 2017-10-29 Creators: Balázs Demeter, Balázs Ujvári, Dávid Baranyai

#include <iostream>
#include "Progress.hh"
#include "TApplication.h"
#include "TGraph.h"

using namespace std;

void OpenRootFile()
{
		TFile *fIn = TFile::Open("Plot1.root", "READ");
		fIn->ls();
		TGraph *Ga;
		TGraph *Gb;
		fIn->GetObject("1", Ga);
		fIn->GetObject("2", Gb);
		Ga->Draw();
		Gb->Draw("same");
		delete fIn;
}


int main(int argc, char* argv[])
{
	Int_t n = 1000;
	
	TApplication App("tapp", &argc, argv);
	TCanvas* Canv = new TCanvas("c10","Live display",800,400);
	
	if(argc==2)
	{
		OpenRootFile();
	}
	else
	{
		
		Progress* Pr1 = new Progress(n);
		Progress* Pr2 = new Progress(n);
		
		Pr1->Count('u');
		Pr2->Count('g');
		
		vector<Double_t> x1 = Pr1->GetX();
		vector<Double_t> y1 = Pr1->GetY();
		vector<Double_t> x2 = Pr2->GetX();
		vector<Double_t> y2 = Pr2->GetY();
		
		TGraph* G1 = new TGraph(n,&x1[0],&y1[0]);
		TGraph* G2 = new TGraph(n,&x2[0],&y2[0]);
		
		TFile* fOut = new TFile("Plot1.root", "RECREATE");
		
		G1->SetLineColor(1);
		G1->SetLineWidth(1);
		G1->SetMarkerColor(1);
		G1->SetMarkerStyle(0);
		G1->SetTitle("Brownian Movement D=1");
		G1->GetXaxis()->SetTitle("X");
		G1->GetYaxis()->SetTitle("Time");
		G2->SetLineColor(2);
		G2->SetLineWidth(1);
		G2->SetMarkerColor(2);
		G2->SetMarkerStyle(0);
		G2->SetTitle("Brownian Movement D=1");
		G2->GetXaxis()->SetTitle("X");
		G2->GetYaxis()->SetTitle("Time");
		
		G1->Draw();
		G2->Draw("same");
		G1->Write("1");
		G2->Write("2");
		
		fOut->Close();
		
	}
	
	App.Run();
	return 0;

}
