#include <cassert>
#include <iomanip>

#include <CoinUtilsConfig.h>
#include <OsiConfig.h>
#include <CbcConfig.h>
#include "CoinPragma.hpp"
#include "OsiClpSolverInterface.hpp"
#include "CoinPackedVector.hpp"
#include "CbcModel.hpp"

int main(int argc, const char *argv[]) {
  std::cout << "coinutils version: " << COINUTILS_VERSION << std::endl;
  std::cout << "osi version: " << OSI_VERSION << std::endl;
  std::cout << "cbc version: " << CBC_VERSION << std::endl;

  OsiClpSolverInterface model;

  CoinBigIndex start[] = { 0, 1, 2 };
  int index[] = { 0, 0 };
  double values[] = { 1.0, 2.0 };
  double collb[] = { 0.0, 0.0 };
  double colub[] = { 10.0, 10.0 };
  double obj[] = { 1.0, 1.0 };
  double rowlb[] = { 0.0 };
  double rowub[] = { 3.9 };

  // obj: Max x0 + x1
  //  st. x0 + 2 x1 <= 3.9
  //          0 <= x0 <= 10 and integer
  //          0 <= x1 <= 10
  model.loadProblem(2, 1, start, index, values, collb, colub, obj, rowlb, rowub);
  model.setInteger(0);
  model.setObjSense(-1.0);
  //bool optimal;
  {
    CbcModel model2(model);
    model2.branchAndBound();
    //optimal = model2.isProvenOptimal();
    const double *val = model2.getColSolution(); // x0 = 3, x1 = 0.45
    printf("Solution %g %g\n", val[0], val[1]);
  }

  const int rowCols[] = { 0 };
  const double rowElements = { 1.0 };

  // add x0 <= 2, and solve once again.
  CoinPackedVector v(1, rowCols, rowElements);
  model.addRow(v, 0.0, 2.0);
 {
    CbcModel model2(model);
    model2.branchAndBound();
    //optimal = model2.isProvenOptimal(); // should be x0 = 2, x1 = 0.95
    const double *val = model2.getColSolution();
    printf("Solution %g %g\n", val[0], val[1]);
  }
  return 0;
}
