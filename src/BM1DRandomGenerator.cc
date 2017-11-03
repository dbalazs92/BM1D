#include "BM1DRandomGenerator.hh"

BM1DRandomGenerator::BM1DRandomGenerator(): TRandom3(){
    tf1 = new TF1("jump","gaus(0)+gaus(3)",-30,30);
}

void BM1DRandomGenerator::SetJump(Double_t min_, Double_t max_){ //set limits
    tf1 = new TF1("jump","gaus(0)+gaus(3)", min_, max_);
}



Double_t BM1DRandomGenerator::Jump(Double_t mu, Double_t sigma, Double_t mu_jump, Double_t sigma_jump, Double_t rat){
    Double_t par[6];
    par[0] = rat; par[1]=mu; par[2]=sigma; par[3]=1-rat; par[4]=mu_jump; par[5]=sigma_jump;
    tf1->SetParameters(par);
    return tf1->GetRandom();
}
