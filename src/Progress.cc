/// BM1D program. Date: 2017-10-29 Creators: Balázs Demeter, Balázs Ujvári 

#include "Progress.hh"

Progress::Progress(Int_t nP) : 
n (nP)
{
	random1 = new TRandom();
}

Progress::~Progress()
{

}

void Progress::Count(char a)
{
	for (Int_t i=0;i<n;i++)
    {
        if(i==0)
        {
            x.push_back(0.0);
            y.push_back(0.0);
        }

        y.push_back((Double_t)i);
        
        switch(a)
        {
			case 'u':
			if(random1->Uniform()>=0.5)
			{
            x.push_back(x[i-1]-0.1);
			}
			else
			{
            x.push_back(x[i-1]+0.1);
			}
			break;
			
			case 'g':
			if(random1->Gaus()>=0.5)
			{
            x.push_back(x[i-1]-0.1);
			}
			else
			{
            x.push_back(x[i-1]+0.1);
			}
			break;
			
			default:
			std::cout<<"Invalid argument!"<<std::endl;
			break;
		}
    }
}

std::vector<Double_t> Progress::GetX()
{
	return x;
}

std::vector<Double_t> Progress::GetY()
{
	return y;
}
