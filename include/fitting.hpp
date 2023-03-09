#ifndef FITTING
#define FITTING


#include "TH1.h"


struct GausFitResult {
	Double_t mean;
	Double_t std;
};


GausFitResult fitBump(TH1D& hist);


#endif