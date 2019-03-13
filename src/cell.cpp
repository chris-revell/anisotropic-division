//
//  cell.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 19/11/2018.
//
//

#include "cell.hpp"
#include <armadillo>

using namespace std;
using namespace arma;

cell::cell(const int& celllabel,const int& parentclone,const float& initialx,const float& initialy,const float& radius,const float& cycletime,const float& initialage) {
  pos = vec(2,fill::zeros);
  v = vec(2,fill::zeros);
  typicalcellradius = radius;
  cellcycletime = cycletime;
  age = initialage;
  cellradius = radius*sqrt(1+initialage/cycletime);
  pos(0) = initialx;
  pos(1) = initialy;
  label = celllabel;
  clone = parentclone;
}

void cell::currentRadius(void){
  cellradius = typicalcellradius*sqrt(1+age/cellcycletime);
}

cell::~cell() {}
