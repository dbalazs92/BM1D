#include "BM1DProcess.hh"

BM1DProcess::BM1DProcess(Int_t nP) : 
  nSteps (nP), p0(0.5), p1(0.3)
{
  randomGenerator = new TRandom();
}

BM1DProcess::~BM1DProcess()
{
  ;
}

void BM1DProcess::Init(){
  t.push_back(0.0);  //let's start at t=0, x=0, you can change it if you vant, please use Set methods
  x.push_back(0.0);
}

void BM1DProcess::Run(){
  for (Int_t i = 1;i < nSteps;i++)
    {
      rand1 = randomGenerator->Uniform();
	if(rand1 < p0) {  //step in time, but no step in x
	  t.push_back(t[i-1] + 1);
	  x.push_back(x[i-1]);
	}
	else {//step left or right
	  if(rand1 < p0 + p1)
	    {
	      t.push_back(t[i-1]+1);
	      x.push_back(x[i-1]+1); //one step right
	    }
	  else
	    {
	      t.push_back(t[i-1]+1);
	      x.push_back(x[i-1]-1); //one step left
	    }
	}
    }
}
