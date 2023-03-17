#include "workspace.hpp"


RooWorkspace SimpleResModel::defineModel(TString wkspName) {
    RooWorkspace wksp {wkspName, false};
    
    wksp.factory("x[2, 20]");

    wksp.factory("mean_gauss1[2, 10]");
    wksp.factory("sigma_gauss1[0, 3]");
    wksp.factory("Gaussian::gauss1(x, mean_gauss1, sigma_gauss1)");

    wksp.factory("mean_gauss2[2, 10]");
    wksp.factory("sigma_gauss2[0, 3]");
    wksp.factory("Gaussian::gauss2(x, mean_gauss2, sigma_gauss2)");

    wksp.factory("gauss_frac[0, 1]");
    wksp.factory("SUM::model(gauss_frac * gauss1, (1 - gauss_frac) * gauss2)");

    return wksp;
}