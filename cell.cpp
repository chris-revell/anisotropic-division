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

cell::cell(const float& initialx,const float& initialy) {
  pos = vec(2,fill::zeros);
  v = vec(2,fill::zeros);
  pos(0) = initialx;
  pos(1) = initialy;
  age = 0;
}
cell::~cell() {}
