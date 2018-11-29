//
//  GridUpdate.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 28/11/2018.
//
//

#ifndef GridUpdate_hpp
#define GridUpdate_hpp

#include <cell.hpp>
#include <PositionToIndex.hpp>

// Subroutine to find the number of cells within each background grid location.
// Number of cells stored in gridcount array, labels of corresponding cells stored in gridcells array. 
void GridUpdate(std::vector<cell>& Cells, arma::mat& gridcount, arma::cube& gridcells, const int& Nc, const int& Ng, const float& griddim);

#endif /* GridUpdate_hpp */
