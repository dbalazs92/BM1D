#include "BM1DProcess.hh"

BM1DProcess::BM1DProcess() 
{
  randomGenerator = new TRandom3();
  randomGenerator -> SetSeed();
  randomGeneratorGauss = new TRandom3();
  randomGeneratorGauss -> SetSeed();
  std::cout << "seed:" << randomGeneratorGauss -> GetSeed() << std::endl;
  
  //jump = new TF1("jump","gaus(0)+gaus(3)",-30,30);
}

BM1DProcess::~BM1DProcess()
{
  delete randomGenerator;
  delete randomGeneratorGauss;
//  delete jump;
}


void BM1DProcess::Run(const int & nRuns, const int & nSteps, const  double & p0, const double & p1)
{
	t.clear();
	x.clear();
	
	for(int i = 0; i < nRuns; i++) //multiple runs
		{
			t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
			x.push_back(0.0);
			
			for(int ii = 1; ii < nSteps ; ii++)
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



void BM1DProcess::Run(const int & nRuns, const int & nSteps, const  double & p0, const double & mu, const double & sigma)
{
	
	t.clear();
	x.clear();
	
	for(int i = 0; i < nRuns; i++) //multiple runs
		{
			t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
			x.push_back(0.0);
			
			for(int ii = 1; ii < nSteps ; ii++)
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

void BM1DProcess::Run(const int & nRuns, const int & nSteps, const double & p0, const double & x1, const double & x2, const double & mu1, const double & sigma1, const double &mu2, const double & sigma2)
{
	t.clear();
	x.clear();
	
	for(int i = 0; i < nRuns; i++) //multiple runs
		{
			t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
			x.push_back(0.0);
			
			double randGauss;
			
			for(int ii = 1; ii < nSteps ; ii++)
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


void BM1DProcess::Run(const int & nRuns, const int & nSteps, const double & p0, const double & x1, const double & x2, const double & mu1, const double & sigma1, const double &mu2, const double & sigma2, const double & j_mu1, const double & j_sigma1, const double  & rat)
{
	t.clear();
	x.clear();
    BM1DRandomGenerator* jump = new BM1DRandomGenerator(); 
    Double_t minim = (mu1-5*sigma1  < j_mu1-5*j_sigma1) ? mu1-5*sigma1 : j_mu1-5*j_sigma1; 
    Double_t maxim = (mu1+5*sigma1  > j_mu1+5*j_sigma1) ? mu1+5*sigma1 : j_mu1+5*j_sigma1; 
    jump->SetJump(minim, maxim);

	for(int i = 0; i < nRuns; i++) //multiple runs
		{
			t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
			x.push_back(0.0);
			
			double randJ;
			
			for(int ii = 1; ii < nSteps ; ii++)
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
//                                    par[1] = mu2;  par[2] = sigma2;
//                                    jump->SetParameters(par);
    //									randJ = jump->GetRandom();
                                        randJ=jump->Jump(mu2, sigma2, j_mu1, j_sigma1, rat );
								}
							else 
						    {
//	                                par[1] = mu1;  par[2] = sigma1;
//                                    jump->SetParameters(par);
//									randJ = jump->GetRandom();
									randJ=jump->Jump(mu1, sigma1, j_mu1, j_sigma1, rat );
							}	
						
							t.push_back(t.back() + 1);
							x.push_back(x.back() + randJ); //one step right
						}
				}						
		}
}
