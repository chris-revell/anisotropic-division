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

void GridUpdate(std::vector<cell>& Cells, arma::mat& gridcount, arma::cube& gridcells, const int& Nc, const int& Ng, const float& griddim);

#endif /* GridUpdate_hpp */
