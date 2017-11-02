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
	
	void SetNop(Int_t num); //set the width of the lattice
	void SetPercent(Int_t num); //set the interval of mu, sigma
	
	void SetLattice(Double_t mu_est, Double_t sigma_est); //set the lattice around mu_est, sigma_est
	
	MuSigma GetMuSigma(Int_t index);
	
	Int_t GetLatticeSize(); //number of points in the lattice
	Int_t GetWidth(); //number of mu values
	Int_t GetHeight(); //number of sigma values
	
	
private:
	Int_t _nop; //number of points in [mu-_percent; mu+_percent]
	Double_t _percent; 
	
	std::vector<MuSigma> ms_vect;
	
	Int_t _width;
	Int_t _height;
	

};


/***********************************************************************	
	example in BM1D.cc 
	
	Lattice *myLattice = new Lattice();
 	myLattice->SetPercent(15);
  	myLattice->SetNop(10);
  	myLattice->SetLattice(myAnalyse->GetMu(), myAnalyse->GetSigma());
  	
  	mu_value = myLattice->GetMuSigma(i).mu;
  	sigma_value = myLattice->GetMuSigma(i).sigma;
  	
************************************************************************/

#endif
