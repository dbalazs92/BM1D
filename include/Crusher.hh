#ifndef Crusher_h
#define Crusher_h 1

#include <iostream>


#include "BM1DProcess.hh"
#include "Analyse.hh"
#include "Lattice.hh"

class Crusher
{
	public:
		Crusher(const std::vector<Double_t> & tp, const std::vector<Double_t> & xp, double p0p);
		Crusher(const std::vector<Double_t> & tp, const std::vector<Double_t> & xp);
		

		~Crusher();
		
		bool RunMachine(const int & nRunsm, const MuSigma & parameters);
		
		const std::vector<Double_t> & GetMulT() {return multipleRunVectorT;}
		const std::vector<Double_t> & GetMulX() {return multipleRunVectorX;}
		
	private:
		int nSteps;
		double p0;
		double BiggerLimit;
		std::vector<Double_t>  t;
		std::vector<Double_t>  x;
		
		BM1DProcess *myBM1DProcess;
		Analyse *myAnalyse;
		
		inline bool Bigger();
		
		std::vector<Double_t> multipleRunVectorT;
		std::vector<Double_t> multipleRunVectorX;
};
#endif