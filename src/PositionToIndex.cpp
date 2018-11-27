//
//  PositionToIndex.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 27/11/2018.
//
//

#include <PositionToIndex.hpp>
#include <cell.hpp>

using namespace std;
using namespace arma;

// Function to return index of a given cell position in a given dimension (dim) within the background lattice of size Ng and width Ng*griddim
int PositionToIndex(const cell& Cell,const float& griddim,const int& Ng,const int& dim){
  int index;
  index = floor((Cell.pos(dim)+(Ng*griddim)/2)/griddim);
  return index;
}
