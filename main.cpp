

#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include "cell.hpp"

using namespace std;
using namespace arma;

void morseforce(const cell& Cell1,const cell& Cell2){
  float dx,dy,r,F,vx,vy;
  float De = 1;
  float a  = 1;
  float re = 1;
  float expfactor;

  dx = Cell1.pos(0) - Cell2.pos(0);
  dy = Cell2.pos(1) - Cell2.pos(1);
  r = sqrt(pow(dx,2)+pow(dy,2));
  expfactor = exp(-a*(r-re));
  F = 2*a*De*(expfactor-pow(expfactor,2));
  vx = F*dx/r;
  vy = F*dy/r;
  Cell1.v(0) = vx;
  Cell1.v(1) = vy;
  Cell2.v(0) = -vx;
  Cell2.v(1) = -vy;
}

int main(){

  vector<cell> Cells;

  Cells.push_back(cell(0,1));
  Cells.push_back(cell(1,0));

  morseforce(Cells[0],Cells[1]);

  cout << Cells[0].v(0) << " " << Cells[0].v(1) << endl;


  return 0;
}
