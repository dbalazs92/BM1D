#include <iostream>
#include "BM1DProcess.hh"
#include "Plotter.hh"
#include "TApplication.h"
#include "Analyse.hh"
#include "BM1DSave.hh"
#include "Draw2D.hh"

using namespace std;

int main(int argc, char* argv[])
{
    Int_t nSteps, nRuns;
	Double_t p0,p1,x1,x2;
    Double_t mu1, mu2, sigma1, sigma2, percent;
	
	Double_t j_mu1, j_sigma1;//////////////////////
	Double_t rat;//////////////////////
	
	int nGenerated, nop;
	
	const char* fileName="input.root";
    char random_type='u';
    Int_t vis, typeOfRun;
	

    nSteps=nRuns=vis=typeOfRun=0;
    mu1=mu2=sigma1=sigma2=p0=p1=x1=x2=0.0;
    if(argc==15)
    {
        nSteps=atoi(argv[1]);
        nRuns=atoi(argv[2]);
        p0=atof(argv[3]);
        p1=atof(argv[4]);
        x1=atof(argv[5]);
        x2=atof(argv[6]);
        mu1=atof(argv[7]);
        mu2=atof(argv[8]);
        sigma1=atof(argv[9]);
        sigma2=atof(argv[10]);
        fileName=argv[11];
        random_type=argv[12][0];
        vis=atoi(argv[13]); if((vis!=0)&&(vis!=1)){vis=0;}
        typeOfRun=atoi(argv[14]); if((typeOfRun!=0)&&(typeOfRun!=1)&&(typeOfRun!=2)){typeOfRun=0;}
		//todo fix  parameters
		percent = 0.99; 
		nGenerated = 7000;
		nop = 30;
		
		j_mu1=-25; 
        j_sigma1=0.3;
        rat=0.9;
    }
    else
    {
        //default runs with less parameters
		random_type = 'g';
		nSteps = 2000;
		nRuns = 1;
		p0 = 0.5;
		p1 = 0;
		x1 = 0;
		x2 = 0;
		mu1 = 1;
		mu2 = 0;
		sigma1 = 10;
		sigma2 = 0;
		
		j_mu1=-25; 
        j_sigma1=0.3;
        rat=0.9;

		percent = 0.99; 
		nGenerated = 8000;
		nop = 40;
		
		vis = 1;
		typeOfRun = 1;
    }


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
            break;
        default:
            cout<<"ERROR! Wrong parameter for type of random generator! \n No run!"<<endl;
            break;
    }
	
	/*
	TH1D *hJump = new TH1D("h", "test", 100, -30., 30.);                         
  hJump->Sumw2();                                                          
  std::vector<Double_t> x = myBM1DProcess->GetX();                                                   
  hJump->Fill(0);
  for(int i=1; i<x.size(); i++){
    hJump->Fill(x[i]-x[i-1]);
  }    
  hJump->Draw();
	*/
	
	
	Plotter* myPlotter = new Plotter(vis==1);
	myPlotter->Plot(nRuns, nSteps, myBM1DProcess->GetT(), myBM1DProcess->GetX()); 
  
  int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
  std::cout <<"cpus:"<<numCPU <<std::endl;
  
  Draw2D *myDraw2D = new Draw2D(nop, percent, nGenerated, myBM1DProcess->GetT(), myBM1DProcess->GetX(),numCPU); //nop percent nruns
  
  switch(random_type){
  	case 'g' :
		Analyse *myAnalyse = new Analyse();
		myAnalyse->AnalyseGaus(myBM1DProcess->GetT(),myBM1DProcess->GetX());
		myDraw2D -> Histo2D();
  }
  BM1DSave *save = new BM1DSave();
  save->SaveToTree(myPlotter->GetTmultiGraph(), p0, p1, nSteps, nRuns, x1, x2, mu1, mu2, sigma1, sigma2, myBM1DProcess->GetT(), myBM1DProcess->GetX(),fileName);
  App.Run();
  return 0;
}
