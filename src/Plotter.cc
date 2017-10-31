#include "Plotter.hh"

Plotter::Plotter(bool draw_par = false)
{
draw = draw_par;
if(draw)
  {
	canv = new TCanvas("canc","display",800,400);
  }
mg = new TMultiGraph();
}
void Plotter::Plot(Int_t numRuns, Int_t nSteps, std::vector<Double_t> t, std::vector<Double_t> x)
{
  mg->SetTitle("BM1D");
  
  for(int i= 0; i < numRuns; i++)
  { 
		g1 = new TGraph(nSteps,&t[i*nSteps],&x[i*nSteps]);
		
		g1->SetLineColor(i+1);
		g1->SetTitle("Brownian Movement");
		g1->GetYaxis()->SetTitle("X");
		g1->GetXaxis()->SetTitle("Time");
		g1->SetLineWidth(1);
		g1->SetMarkerColor(1);
		g1->SetMarkerStyle(1);
			
		mg -> Add(g1);	
  }
  
  if(draw)
  {
		g1->Draw();
		mg -> Draw();
  }

}

