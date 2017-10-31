#include <iostream>
#include "BM1DProcess.hh"
#include "Plotter.hh"
#include "TApplication.h"

using namespace std;

int main(int argc, char* argv[])
{
    Int_t nSteps, nRuns, p0,p1,p2,p3;
    Double_t mu1, mu2, sigma1, sigma2;
    string fileName="input.root";
    string random_type="u";
    Int_t vis, typeOfRun;

    nSteps=nRuns=p0=p1=p2=p3=vis=typeOfRun=0;
    mu1=mu2=sigma1=sigma2=0.0;
    if(argc==15)
    {
        nSteps=atoi(argv[1]);
        nRuns=atoi(argv[2]);
        p0=atoi(argv[3]);
        p1=atoi(argv[4]);
        p2=atoi(argv[5]);
        p3=atoi(argv[6]);
        mu1=atof(argv[7]);
        mu2=atof(argv[8]);
        sigma1=atof(argv[9]);
        sigma2=atof(argv[10]);
        fileName=argv[11];
        random_type=argv[12];
        vis=atoi(argv[1]); if((vis!=0)||(vis!=1)){vis=0;}
        typeOfRun=atoi(argv[2]); if((typeOfRun!=0)||(typeOfRun!=1)||(typeOfRun!=2)){typeOfRun=0;}
    }
    else
    {
        //default runs with less parameters
    }


  TApplication App("tapp", &argc, argv);
  Int_t n = 1000;
  BM1DProcess *myBM1DProcess = new BM1DProcess(n);
  myBM1DProcess->Init();
  myBM1DProcess->Run();
  Plotter* myPlotter = new Plotter();
  myPlotter->Plot(n, myBM1DProcess->GetT(), myBM1DProcess->GetX());

  App.Run();
  return 0;
}
