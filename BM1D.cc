#include <iostream>
#include "BM1DProcess.hh"
#include "Plotter.hh"
#include "TApplication.h"
#include "Analyse.hh"

using namespace std;

int main(int argc, char* argv[])
{
    Int_t nSteps, nRuns;
	Double_t p0,p1,x1,x2;
    Double_t mu1, mu2, sigma1, sigma2;
    string fileName="input.root";
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
        random_type=argv[13][0];
        vis=atoi(argv[14]); if((vis!=0)||(vis!=1)){vis=0;}
        typeOfRun=atoi(argv[15]); if((typeOfRun!=0)||(typeOfRun!=1)||(typeOfRun!=2)){typeOfRun=0;}
    }
    else
    {
        //default runs with less parameters
		random_type = 'g';
		nSteps = 1000;
		nRuns = 1;
		p0 = 0.5;
		p1 = 0;
		x1 = 0;
		x2 = 0;
		mu1 = 1;
		mu2 = 0;
		sigma1 = 2;
		sigma2 = 0;
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
        default:
            cout<<"ERROR! Wrong parameter for type of random generator! \n No run!"<<endl;
            break;
    }

  Plotter* myPlotter = new Plotter(vis==1);
  myPlotter->Plot(nRuns, nSteps, myBM1DProcess->GetT(), myBM1DProcess->GetX()); 
  
  Analyse *myAnalyse = new Analyse();
  myAnalyse->AnalyseGaus(myBM1DProcess->GetT(),myBM1DProcess->GetX());

  App.Run();
  return 0;
}
