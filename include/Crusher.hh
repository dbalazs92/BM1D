#ifndef Crusher_h
#define Crusher_h 1

#include <iostream>


#include "BM1DProcess.hh"
#include "Analyse.hh"
#include "Lattice.hh"

class Crusher
{
	public:
		Crusher(std::vector<Double_t> tp, std::vector<Double_t> xp, double p0p);
		Crusher(std::vector<Double_t> tp, std::vector<Double_t> xp);
		~Crusher();
		
		bool RunMachine(const int & nRunsm, const MuSigma & parameters);
		
		const std::vector<Double_t> & GetMulT() {return multipleRunVectorT;}
		const std::vector<Double_t> & GetMulX() {return multipleRunVectorX;}
		
	private:
		int nSteps;
		double p0;
		std::vector<Double_t> t;
		std::vector<Double_t> x;
		
		BM1DProcess *myBM1DProcess;
		Analyse *myAnalyse;
		
		bool Bigger(double percent);
		
		std::vector<Double_t> multipleRunVectorT;
		std::vector<Double_t> multipleRunVectorX;
};
#endif