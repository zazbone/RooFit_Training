#ifndef SAMPLING
#define SAMPLING

#include "RooAbsPdf.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "TH1.h"
#include "TRandom3.h"
#include "TString.h"

#include <memory>


using UPtrRooDataSet = std::unique_ptr<RooDataSet>;


Int_t fillGaus(TH1D& hist, UInt_t nEntries, Double_t mean, Double_t std, TRandom3& rng);

Int_t fillExp(TH1D& hist, UInt_t nEntries, Double_t tau, TRandom3& rng);

UPtrRooDataSet generateFrom(RooWorkspace& wksp, TString varName, TString pdfName, int size);

#endif