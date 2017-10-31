#include "BM1DProcess.hh"

BM1DProcess::BM1DProcess() 
{
  randomGenerator = new TRandom();
  randomGeneratorGauss = new TRandom();
}

BM1DProcess::~BM1DProcess()
{
  delete randomGenerator;
  delete randomGeneratorGauss;
}


void BM1DProcess::Run(int nRuns, int nSteps, double p0, double p1)
{
	for(int i = 0; i < nRuns; i++) //multiple runs
		{
			t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
			x.push_back(0.0);
			
			for(int ii = 0; ii < nSteps ; ii++)
				{
				
					rand1 = randomGenerator->Uniform();
						
					if(rand1 < p0)	//step in time, but no step in x
						{  
							t.push_back(t.back() + 1);
							x.push_back(x.back());
						}
					
					else	//step left or right
						{	
							if(rand1 < p0 + p1)
								{
									t.push_back(t.back()+1);
									x.push_back(x.back()+1); //one step right
								}
							else
								{
									t.push_back(t.back() + 1);
									x.push_back(x.back() - 1); //one step left
								}			
						}
				}						
		}
}

void BM1DProcess::Run(int nRuns, int nSteps, double p0, double mu, double sigma)
{
	for(int i = 0; i < nRuns; i++) //multiple runs
		{
			t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
			x.push_back(0.0);
			
			for(int ii = 0; ii < nSteps ; ii++)
				{
					rand1 = randomGenerator->Uniform();
						
					if(rand1 < p0)	//step in time, but no step in x
						{  
							t.push_back(t.back() + 1);
							x.push_back(x.back());
						}
					
					else	//step left or right
						{	
							double randGauss = randomGeneratorGauss -> Gaus(mu,sigma);
							t.push_back(t.back() + 1);
							x.push_back(x.back() + randGauss); //one step right
						}
				}						
		}
}

void BM1DProcess::Run(int nRuns, int nSteps, double p0, double x1, double x2, double mu1, double sigma1, double mu2, double sigma2)
{
	for(int i = 0; i < nRuns; i++) //multiple runs
		{
			t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
			x.push_back(0.0);
			
			double randGauss;
			
			for(int ii = 0; ii < nSteps ; ii++)
				{
					rand1 = randomGenerator->Uniform();
					
					if(rand1 < p0)	//step in time, but no step in x
						{  
							t.push_back(t.back() + 1);
							x.push_back(x.back());
						}
					
					else	//step left or right
						{	
							if(x.back() < x2 && x.back() > x1)
								{
									randGauss = randomGeneratorGauss -> Gaus(mu1,sigma1);
								}
							else 
								{
									randGauss = randomGeneratorGauss -> Gaus(mu2,sigma2);
								}	
						
							t.push_back(t.back() + 1);
							x.push_back(x.back() + randGauss); //one step right
						}
				}						
		}
}