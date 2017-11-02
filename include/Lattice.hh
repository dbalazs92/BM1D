#ifndef Lattice_h
#define LAttice_h 1

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "TMath.h"


//////////////////////////////////////////////////////////
//							//
//    Create a lattice around the estimated mu, sigma   //
//							//
//////////////////////////////////////////////////////////


typedef struct {
		
		Double_t mu = 0.0;
		Double_t sigma = 0.0;
	}MuSigma;

class Lattice{

public:	
	Lattice();
	~Lattice();
	
	void SetNop(Int_t num);
	void SetPercent(Int_t num);
	
	void SetLattice(Double_t mu_est, Double_t sigma_est);
	
	MuSigma GetMuSigma(Int_t index);
	
	
private:
	Int_t _nop; //number of points in [mu-_percent; mu+_percent]
	Double_t _percent; 
	
	std::vector<MuSigma> ms_vect;
	

};


#endif
