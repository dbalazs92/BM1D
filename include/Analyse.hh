#ifndef Analyse_h
#define Analyse_h 1

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <limits>

#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"


class Analyse{
	
public:
	Analyse();
	~Analyse();

	Double_t GetP0();
	Double_t GetMu();
	Double_t GetSigma();
	
	void AnalyseGaus(std::vector<Double_t> t, std::vector<Double_t> x);
	
private:
	Double_t _p0;
	Double_t _mu;
	Double_t _sigma;
	TCanvas* canvA;

};

#endif
