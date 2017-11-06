#include "Crusher.hh"

Crusher::Crusher(std::vector<Double_t> tp, std::vector<Double_t> xp, double p0p)
{
	nSteps = tp.size();
	t = tp;
	x = xp;
	p0 = p0p;
	
	myBM1DProcess = new BM1DProcess();
	
}

Crusher::Crusher(std::vector<Double_t> tp, std::vector<Double_t> xp)
{
	nSteps = tp.size();
	t = tp;
	x = xp;
	p0 = 0.5;
	
	myBM1DProcess = new BM1DProcess();
}

Crusher::~Crusher()
{
	delete myBM1DProcess;
}

bool Crusher::Bigger(double percent)
{
	int counterBig = 0;
	double limit = nSteps * percent;
	
	for(int i = 0; i < nSteps; i++)
	{
		
		if(myBM1DProcess -> GetX()[i] < x[i]) // reference < origin
		{
			counterBig ++;
		}
	}
	
	
	if(counterBig >= limit)
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
			
			
			if(Bigger(0.5))
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