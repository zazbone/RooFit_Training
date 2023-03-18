#include "sampling.hpp"


Int_t fillGaus(TH1D& hist, UInt_t nEntries, Double_t mean, Double_t std, TRandom3& rng) {
	for (UInt_t i = 0; i < nEntries; i++) {
		hist.Fill(rng.Gaus(mean, std));
	}
	return 0;
}

Int_t fillExp(TH1D& hist, UInt_t nEntries, Double_t tau, TRandom3& rng) {
	for (UInt_t i = 0; i < nEntries; i++) {
		hist.Fill(rng.Exp(tau));
	}
	return 0;
}

UPtrRooDataSet generateFrom(RooWorkspace& wksp, TString varName, TString pdfName, int size) {
	auto var = wksp.var(varName);
	auto pdf = wksp.pdf(pdfName);
	return UPtrRooDataSet { pdf->generate(*var, size) };
}