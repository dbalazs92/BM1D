#include "Lattice.hh"


Lattice::Lattice() : _nop(10), _percent(0.2), _width(10), _height(10){;}

Lattice::~Lattice(){;}


void Lattice::SetNop(Int_t num){

	_nop = num;
}


void Lattice::SetPercent(Double_t num){

	if((num > 1) && (num <= 100))
		_percent = num/100.0;
	else{
		_percent = num;
		std::cout << "Invalid value for percent, set to default" << std::endl;
		}
}


const MuSigma & Lattice::GetMuSigma(Int_t index){
	
	return ms_vect[index];

}

Int_t Lattice::GetLatticeSize(){
	
	return ms_vect.size();

}

const Int_t & Lattice::GetWidth(){
	
	return _width;

}

const Int_t & Lattice::GetHeight(){
	
	return _height;

}

const double & Lattice::GetMuMin()
{
	return ms_vect[0].mu;
}

const double & Lattice::GetMuMax()
{
	return ms_vect[ _height * (_width-1)].mu;
}

const double & Lattice::GetSigmaMin()
{
	return ms_vect[0].sigma;
}

const double & Lattice::GetSigmaMax()
{
	return ms_vect[_height -1].sigma;
}

void Lattice::SetLattice(Double_t mu_est, Double_t sigma_est){

		Double_t loc_sigma, loc_mu;
		
		Double_t sigmin, sigmax, mumin, mumax;
		
		Double_t ds, dm;
		
		mumax = mu_est + mu_est*_percent;
		mumin = mu_est - mu_est*_percent;
		sigmax = sigma_est + sigma_est*_percent;
		sigmin = sigma_est - sigma_est*_percent;
		
		dm = (mumax-mumin) / _nop;
		ds = (sigmax-sigmin) / _nop;
		
		loc_mu = mumin;
		loc_sigma = sigmin;
			
		int i = 0;
		
		_width = 0;
		_height = 0;
		
		while(loc_mu <= mumax){
		
		loc_sigma = sigmin;
		
		
			
			while(loc_sigma <= sigmax) {
			
			
				ms_vect.push_back(MuSigma());
				
				ms_vect[i].mu = loc_mu;
				ms_vect[i].sigma = loc_sigma;
				
				//std::cout << "i :  " << ms_vect[i].mu << " " << ms_vect[i].sigma << std::endl;
			
				i++;
				loc_sigma += ds;
				
				if(!_width) _height++;
				
				}
				
			loc_mu += dm;
			_width++;	
			
		}
		
		std::cout << "Width " << _width << " Height " << _height << std::endl;
	
}







