#include <iostream>
#include "BM1DProcess.hh"
#include "Plotter.hh"
#include "TApplication.h"
#include "Analyse.hh"
#include "BM1DSave.hh"

using namespace std;

int main(int argc, char* argv[])
{
    Int_t nSteps, nRuns;
	Double_t p0,p1,x1,x2;
    Double_t mu1, mu2, sigma1, sigma2;
	Double_t j_mu1, j_sigma1;//////////////////////
	Double_t rat;//////////////////////
    const char* fileName="input.root";
    char random_type='j';
    Int_t vis, typeOfRun;

    nSteps=nRuns=vis=typeOfRun=0;
        //default runs with less parameters
		random_type = 'j';
		nSteps = 1000;
		nRuns = 5;
		p0 = 0;
		p1 = 0;
		x1 = 200000;
		x2 = 200000;
		mu1 = 1;
		mu2 = -6;
		sigma1 = 0.8;
		sigma2 = 0.2;
		vis = 1;
		typeOfRun = 1;
        j_mu1=-25; 
        j_sigma1=0.3;
        rat=0.9;     

  TApplication App("tapp", &argc, argv);
  BM1DProcess *myBM1DProcess = new BM1DProcess();
    switch(random_type){
        case 'u':
            myBM1DProcess->Run(nRuns, nSteps, p0, p1);
            break;
        case 'g':
            myBM1DProcess->Run(nRuns, nSteps, p0, mu1, sigma1);
            break;
        case 'l':
            myBM1DProcess->Run(nRuns, nSteps, p0, x1, x2, mu1, sigma1, mu2, sigma2);
            break;
        case 'j':
            myBM1DProcess->Run(nRuns, nSteps, p0, x1, x2, mu1, sigma1, mu2, sigma2, j_mu1, j_sigma1, rat);
            //cout << "\nOK\n";
            break;
        default:
            cout<<"ERROR! Wrong parameter for type of random generator! \n No run!"<<endl;
            break;
    }

  
  TH1D *hJump = new TH1D("h", "test", 100, -30., 30.);                         
  hJump->Sumw2();                                                          
  std::vector<Double_t> x = myBM1DProcess->GetX();                                                   
  hJump->Fill(0);
  for(int i=1; i<x.size(); i++){
    hJump->Fill(x[i]-x[i-1]);
  }    
  hJump->Draw();

 // std::cout << "Pontok szama: "<< x.size() << "\n";
  
  
  Plotter* myPlotter = new Plotter(vis==1);
  myPlotter->Plot(nRuns, nSteps, myBM1DProcess->GetT(), myBM1DProcess->GetX()); 





 // Analyse *myAnalyse = new Analyse();
  
 // switch(random_type){
 // 	case 'g' :
 // 	  myAnalyse->AnalyseGaus(myBM1DProcess->GetT(),myBM1DProcess->GetX());
//  }
//  BM1DSave *save = new BM1DSave();
//  save->SaveToTree(myPlotter->GetTmultiGraph(), p0, p1, nSteps, nRuns, x1, x2, mu1, mu2, sigma1, sigma2, myBM1DProcess->GetT(), myBM1DProcess->GetX(),fileName);
  App.Run();
  return 0;
}
