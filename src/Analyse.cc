#include "Analyse.hh"

Analyse::Analyse() : _p0(0), _mu(0), _sigma(0) {}

Analyse::~Analyse() {;}


Double_t Analyse::GetP0() { 
		
		return _p0;
	}
	
	
Double_t Analyse::GetMu(){
		
		return _mu;
	}
	
	
Double_t Analyse::GetSigma(){

		return _sigma;
	}

void Analyse::AnalyseGaus(std::vector<Double_t> t, std::vector<Double_t> x){
	
	
	Double_t dx = 0.0;
	Double_t q = 10000;
	Double_t max =  std::numeric_limits<int>::min();
	Double_t min = std::numeric_limits<int>::max();
	
	for (int i = 1; i < t.size(); i++) dx += TMath::Abs(x[i]-x[i-1]);
	
	dx/=t.size();
	dx/=q;
	
		
	for (int i = 1; i < t.size(); i++){
		
		if(TMath::Abs(x[i]-x[i-1]) < dx) _p0 += 1.0;
	}
	
	//std::cout << "t.size " << t.size() << std::endl;
	
	_p0 /= (Double_t)t.size();
	
	//std::cout << "p0 = " << _p0 << std::endl;
	
	
	std::vector<Double_t> deltax;
	

	deltax.push_back(x[0]);	
	
	for (int i = 1; i < t.size(); i++) {
	
		if(TMath::Abs(x[i]-x[i-1]) > dx){
		
			deltax.push_back(x[i]-x[i-1]);

		}
		
		
		//std::cout << deltax[i-1] << std::endl;
	}
	
		
	for (int i = 0; i < deltax.size(); i++){
		
		Double_t loc_dx = deltax[i];
		
		max = (loc_dx > max) ? loc_dx : max;
		min = (loc_dx < min) ? loc_dx : min;
		
	}
	
	
	Int_t nbin = (max-min)/0.1;
	
	//std::cout << nbin << std::endl;	
	
	TH1D* dxhisto = new TH1D("dxhisto","dxhisto", nbin, min+0.1*min,max+0.1*max);
	
	for (int i = 0; i < deltax.size(); i++) dxhisto->Fill(deltax[i]);
	
	dxhisto->Fit("gaus");
	
	dxhisto->Draw();

	
	//std::cout << dxhisto->GetFunction("gaus")->GetParameter(1) <<std::endl;
	
	_mu = dxhisto->GetFunction("gaus")->GetParameter(1);
	_sigma = dxhisto->GetFunction("gaus")->GetParameter(2);
	
	
	std::cout << "p0 = " << _p0 << std::endl;
	std::cout << "mu = " << _mu << std::endl;
	std::cout << "sigma = " << _sigma << std::endl; 
	
		
}
