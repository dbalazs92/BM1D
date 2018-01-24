#include "Crusher.hh"

Crusher::Crusher(const std::vector<Double_t> & tp, const std::vector<Double_t> & xp, double p0p)
{
	t = tp;
	x = xp;
	p0 = p0p;

	nSteps = t.size();

	const double percent = 0.5;
	BiggerLimit = nSteps * percent;
	
	myBM1DProcess = new BM1DProcess();
}

Crusher::Crusher(const std::vector<Double_t> & tp, const  std::vector<Double_t> & xp)
{
	t = tp;
	x = xp;
	p0 = 0.5;

	nSteps = t.size();

	const double percent = 0.5;
	BiggerLimit = nSteps * percent;

	myBM1DProcess = new BM1DProcess();
}

Crusher::~Crusher()
{
	delete myBM1DProcess;
}

inline bool Crusher::Bigger()
{
	int counterBig = 0;
	//double limit = nSteps * percent;
	const std::vector<Double_t> & refx = myBM1DProcess -> GetX();
	
	for(int i = 0; i < nSteps; i++)
	{
		
		if(refx[i] < x[i]) // reference < origin
		{
			counterBig ++;
		}
	}
	
	
	if(counterBig >= BiggerLimit)
	{
		return true;
	}
	
	else return false;
}

bool Crusher::RunMachine(const int & nRuns, const MuSigma & parameters)
{
		int counter = 0;
		
		multipleRunVectorT.clear();
		multipleRunVectorX.clear();
		
		for(int i = 0; i < nRuns; i++ )
		{
			
			
			myBM1DProcess->Run(1, nSteps, p0, parameters.mu, parameters.sigma);
			
			//std::cout << "paramter mu:" << parameters.mu << "   paramter sigma:" << parameters.sigma << std::endl;
			
			for(int i = 0; i < nSteps; i++)
			{
				multipleRunVectorT.push_back(myBM1DProcess -> GetT()[i]);
				multipleRunVectorX.push_back(myBM1DProcess -> GetX()[i]);
			}
			
			
			if(Bigger())
			{
				counter ++;
			}
			
			
			
		}
		
		std::cout <<"mu:" << parameters.mu << "  sigma:" << parameters.sigma << "  in:" << counter <<std::endl; 
		
		if(!(counter < (0.05 * nRuns) || (nRuns - counter) < (0.05 * nRuns)))
		{
			return true;
		}
		
		else return false;
		
}