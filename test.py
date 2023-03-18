import ROOT
from random import random

# Model Definition
wksp = ROOT.RooWorkspace("main", False)

wksp.factory("x[2, 20]")

wksp.factory("mean_gauss1[4, 2, 10]")
wksp.factory("sigma_gauss1[0.1, 0.0001, 3]")
wksp.factory("Gaussian::gauss1(x, mean_gauss1, sigma_gauss1)");

wksp.factory("mean_gauss2[6, 2, 10]")
wksp.factory("sigma_gauss2[0.5, 0.0001, 3]")
wksp.factory("Gaussian::gauss2(x, mean_gauss2, sigma_gauss2)")

wksp.factory("gauss_frac[0.2, 0, 1]")
wksp.factory("SUM::model(gauss_frac * gauss1, gauss2)")

# Generate fake data

x = wksp.var("x")
model = wksp.pdf("model")
measure = model.generate(x, 1e7);



# Shuffle params

mean_gauss1 = wksp.var("mean_gauss1")
mean_gauss1.setVal(random() * 8 + 2)
mean_gauss2 = wksp.var("mean_gauss2")
mean_gauss2.setVal(random() * 8 + 2)
sigma_gauss1 = wksp.var("sigma_gauss1")
sigma_gauss1.setVal(random() * 3)
sigma_gauss2 = wksp.var("sigma_gauss2")
sigma_gauss2.setVal(random() * 3)

# Fit

model.fitTo(measure)

frame = x.frame()
measure.plotOn(frame)
model.plotOn(frame)

frame.Draw()