//
//  OutputData.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 19/03/2019.
//
//

#include "OutputData.hpp"
#include <vector>
#include <armadillo>
#include <cell.hpp>

using namespace std;
using namespace arma;

void OutputData(const vector<cell>& Cells, const float& t, const int& Nc, ofstream& outfile1, ofstream& outfile2){

  float xmax = 40.0;
  float xmin = -40.0;
  int printedCounter=0;

  cout << t << endl;
  // Write positions to file
  for (int ii=0;ii<Nc;ii++){
    if (Cells[ii].pos(0) > xmin && Cells[ii].pos(0) < xmax && Cells[ii].pos(1) > xmin && Cells[ii].pos(1) < xmax){
      outfile1 << Cells[ii].pos(0) << " " << Cells[ii].pos(1) << " " << Cells[ii].clone << endl;
      printedCounter++;
    }
  }
  // Write cell count at this time interval to file
  outfile2 << printedCounter << endl;
}
