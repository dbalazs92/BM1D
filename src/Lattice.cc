#include "Lattice.hh"


Lattice::Lattice() : _nop(100), _percent(0.2){;}

Lattice::~Lattice(){;}


void Lattice::SetNop(Int_t num){

	_nop = num;
}


void Lattice::SetPercent(Int_t num){

	if((num > 1) && (num <= 100))
		_percent = num/100.0;
	
	else
		std::cout << "Invalid value for percent, set to default" << std::endl;
}


MuSigma Lattice::GetMuSigma(Int_t index){
	
	return ms_vect[index];

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
		
		while(loc_mu <= mumax){
		
		loc_sigma = sigmin;
			
			while(loc_sigma <= sigmax) {
			
				ms_vect.push_back(MuSigma());
				
				ms_vect[i].mu = loc_mu;
				ms_vect[i].sigma = loc_sigma;
								
				i++;
				loc_sigma += ds;
				}
				
			loc_mu += dm;
			
			
			
		}

}







