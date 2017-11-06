#include "Plotter.hh"

unsigned int Plotter::IDCounter = 0;

Plotter::Plotter(bool draw_par = false)
{
draw = draw_par;
ID = IDCounter++;
if(draw)
  {
	char str[30];
	snprintf(str, 30, "Plotter_canvas%d", ID);
	canv = new TCanvas(str, "display",800,400);
  }
mg = new TMultiGraph();
}

Plotter::~Plotter()
{
	
}

TMultiGraph * Plotter::GetTmultiGraph()
{
	return mg;
}


void Plotter::Plot(Int_t numRuns, Int_t nSteps,const  std::vector<Double_t>  & t, const  std::vector<Double_t> & x)
{
  char str[30];
  snprintf(str, 30, "BM1D Plotter canvas%d", ID);
  mg->SetTitle(str);
  
  for(int i= 0; i < numRuns; i++)
  { 
		g1 = new TGraph(nSteps,&t[i*nSteps],&x[i*nSteps]);
		g1->SetLineColor(i%30+1);
		g1->SetLineWidth(2);
		g1->SetMarkerStyle(1);
			
		mg -> Add(g1);	
  }
  
  
  if(draw)
  {
		canv -> cd();
		mg -> Draw("APL");
		std::cout << "Plotter done" << std::endl;
	
  }

}

