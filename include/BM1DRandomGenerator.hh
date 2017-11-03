#ifndef BM1DRandomGenerator_h
    #define BM1DRandomGenerator_h 1
#endif

#include "TRandom3.h"
#include "TF1.h"

class BM1DRandomGenerator: public TRandom3 
{
    public:
        BM1DRandomGenerator();
//        ~BM1DRandomGenerator();
        //void SetTF1();
        void SetTF1();
        void CallTF1();

        void SetJump(Double_t min_, Double_t max_); //set limits

        Double_t Jump(Double_t mu, Double_t sigma, Double_t mu_jump, Double_t sigma_jump, Double_t rat);
    //Double_t Cauchy();
    private:
        TF1* tf1;
};
