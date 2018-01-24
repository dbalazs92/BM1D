#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

#include <pthread.h>

#include "Lattice.hh"
#include "Crusher.hh"

#include "TH2.h"
#include "TCanvas.h"
#include "TGraph.h"

typedef void * (*THREADFUNCPTR)(void *);

struct graphArray
 {
   double *X;
   double *Y;
   int size;
};

class Draw2DWorkerThread
{
public:

	Draw2DWorkerThread(int jobOffset_, int jobSize_, const std::vector<Double_t> & x_, const std::vector<Double_t> & t_, int nRuns_, Lattice *myLattice_, TH2D *BM1D_histo_, TH2D *BM1D_histo2_, struct graphArray graphArray_,  pthread_mutex_t *histoMutex_);
 
	~Draw2DWorkerThread();
	
	void WorkerFunction();
 

private:
	//output histo pointers
	TH2D *BM1D_histo;
	TH2D *BM1D_histo2;
	
	//lattice instance pointer
	Lattice *myLattice;
	
	int nRuns;   //Chrusher parameter number of tested "kukac"
	
	//std::vector<Double_t> t;  //original "kukac"
	//std::vector<Double_t> x;
	
	Crusher *myCrusher;
	
	 pthread_mutex_t *histoMutex;
	 
	 //lattice parameters
	double XbinSize;
	double YbinSize;
	double XbinSizePer2;
	double YbinSizePer2;
	int    latticeHeight;
	int    latticeWidth;
	double latticeMuMin;
	double latticeSigmaMin;
	
	int jobOffset;
	int jobSize;
	
	struct graphArray graphArray;
	

};