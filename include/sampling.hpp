#ifndef SAMPLING
#define SAMPLING


#include "TH1.h"
#include "TRandom3.h"


Int_t fillGaus(TH1D& hist, UInt_t nEntries, Double_t mean, Double_t std, TRandom3& rng);

Int_t fillExp(TH1D& hist, UInt_t nEntries, Double_t tau, TRandom3& rng);


#endif