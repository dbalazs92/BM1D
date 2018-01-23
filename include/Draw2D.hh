#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

#include <pthread.h>


#include "Analyse.hh"
#include "Lattice.hh"
#include "Crusher.hh"
#include "Plotter.hh"
#include "Draw2DWorkerThread.hh"

#include "TH2.h"
#include "TCanvas.h"
#include "TGraph.h"




class Draw2D
{
	public:
		
		Draw2D(int nop, double percent, int nRunsp, std::vector<Double_t> tp, std::vector<Double_t> xp, int nThreads_);
        ~Draw2D();
		
		void Histo2D();
		
	private:
		std::vector<Double_t> t;
		std::vector<Double_t> x;
		int nRuns;
		
		int nThreads;
		
		Analyse *myAnalyse;
		Crusher *myCrusher;
		Lattice *myLattice;
		TCanvas* canvasB;
		TCanvas* canvasB2;
		TH2D *BM1D_histo;
		TH2D *BM1D_histo2;
		TGraph *gr;
		
		struct graphArray graphArray;
		
		
};