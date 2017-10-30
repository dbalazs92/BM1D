/// BM1D program. Date: 2017-10-29 Creators: Balázs Demeter, Balázs Ujvári, Dávid Baranyai

#include "Progress.hh"

Progress::Progress(Int_t nP) : 
n (nP), p0(1), preVstate(0), steps(0)
{
	random1 = new TRandom();
}

Progress::Progress(Int_t nP, Double_t p0_Set) : 
n (nP), p0(p0_Set), preVstate(0), steps(0)
{
	random1 = new TRandom();
}

Progress::Progress(Int_t nP, Double_t p0_Set, Double_t startposition) : 
n (nP), p0(p0_Set), preVstate(startposition), steps(0)
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
            x.push_back(p0);
            y.push_back(0.0);
        }
        
        x.push_back(GetNext(a));
		y.push_back(steps);
    }
}

Double_t Progress::GetNext(char a)
{
		switch(a){
			case 'u':
			preVstate+=random1->Uniform(-p0,p0);
			break;
			
			case 'g':
			preVstate+=random1->Gaus(-p0,p0);
			break;
			
			default:
			std::cout<<"Invalid argument!"<<std::endl;
			preVstate+=0.0;
			break;
		}
        
        steps++;
        return preVstate;
}
    
Double_t Progress::GetPrevious()
{
        return preVstate;
}
    
void Progress::SetP0(Double_t p0_new)
{
        p0=p0_new;
}
    
Double_t Progress::GetP0()
{
        return p0;
}
    
Int_t Progress::GetSteps()
{
        return steps;
}
    
std::vector<Double_t> Progress::GetX()
{
	return x;
}

std::vector<Double_t> Progress::GetY()
{
	return y;
}
