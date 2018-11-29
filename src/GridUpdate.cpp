//
//  GridUpdate.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 28/11/2018.
//
//

#include <GridUpdate.hpp>
#include <cell.hpp>
#include <PositionToIndex.hpp>

using namespace std;
using namespace arma;

// Subroutine to find the number of cells within each background grid location.
// Number of cells stored in gridcount array, labels of corresponding cells stored in gridcells array. 
void GridUpdate(vector<cell>& Cells, mat& gridcount, cube& gridcells, const int& Nc, const int& Ng, const float& griddim){
  int ix,iy; // Background grid indices
  // Refresh the gridcount array
  gridcount.zeros();
  // For each cell, find the background lattice location corresponding to its position
  // Add the cell label to the corresponding matrix component and increment the count of cells at that location
  for (int ii=0;ii<Nc;ii++){
    ix = PositionToIndex(Cells[ii],griddim,Ng,0);
    iy = PositionToIndex(Cells[ii],griddim,Ng,1);
    gridcells(ix,iy,gridcount(ix,iy))=ii;
    gridcount(ix,iy)++;
    Cells[ii].v.zeros(); // Set all cell velocities to zero while we're at it
  }
}
