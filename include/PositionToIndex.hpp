//
//  PositionToIndex.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 27/11/2018.
//
//

#ifndef PositionToIndex_hpp
#define PositionToIndex_hpp

#include <cell.hpp>
// Function to return index of a given cell position in a given dimension (dim) within the background lattice of size Ng and width Ng*griddim
int PositionToIndex(const cell& Cell,const float& griddim,const int& Ng,const int& dim);

#endif /* PositionToIndex_hpp */
