#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "TCanvas.h"

#include "fitting.hpp"

#include <memory>


namespace rf = RooFit;


const char* ENERGY = "E";
const char* BUMP_MEAN = "mubump";
const char* BUMP_STD = "sigbump";
const char* BKG_TAU = "bkgtau";
const char* N_SIGNAL = "nsignal";
const char* N_BKG = "nbkg";


GausFitResult fitBump(TH1D& hist) {
	UInt_t nEntries = hist.GetEntries();
	// Observable
	RooRealVar measure(ENERGY, "E_{mes} (GeV)", 0., 20.);
	// Signal distribution parameters
	RooRealVar bumbMean(BUMP_MEAN, "\\mu_{bump}", 8., 10.);
	RooRealVar bumbStd(BUMP_STD, "\\sigma_{bump}", 0., .4);
	// Signal model
	RooGaussian signalModel("signal", "signal PDF (Gaus)", measure, bumbMean, bumbStd);
	// Background distribution parameters
	RooRealVar bkgTau(BKG_TAU, "\\tau_{bkg}", -1., .0);
	RooExponential bkgModel("background", "background PDF (Exp)", measure, bkgTau);

	// Sample fraction
	Double_t frac = 0.01;
	RooRealVar nSignal(N_SIGNAL, "n signal entries", UInt_t(frac * nEntries) / 2, UInt_t(frac * nEntries) * 2);
	RooRealVar nBkg(N_BKG, "n signal entries", UInt_t((1. - frac) * nEntries) / 2, UInt_t((1. - frac) * nEntries) * 2);
	// Model definition
	RooAddPdf model("model", "model PDF (Gaus + Exp)", RooArgList(signalModel, bkgModel), RooArgList(nSignal, nBkg));

	// Load the data from hist
	RooDataHist binnedData("data", "number of measure (#(GeV))", measure, rf::Import(hist));
	// Fit !
	model.fitTo(binnedData);

	// For now just save plot
	// Plot toy data and composite PDF overlaid:
	std::unique_ptr<RooPlot> frame = std::unique_ptr<RooPlot>(measure.frame());
	binnedData.plotOn(frame.get());
	model.plotOn(frame.get());
	model.plotOn(frame.get(), rf::Components(bkgModel), rf::LineStyle(ELineStyle::kDashed));

	UInt_t width = 2048;
	UInt_t height = width / 1.62;
	TCanvas c("canvas", "RooFit canvas", width, height);
	frame->Draw();
	c.SaveAs("test.jpg");

	return { 0, 1. };
}