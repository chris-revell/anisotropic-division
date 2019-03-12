//
//  CalculateForces.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 28/11/2018.
//
//

#include <CalculateForces.hpp>
#include <cell.hpp>
#include <vector>
#include <PositionToIndex.hpp>
#include <armadillo>
#include <MorseForce.hpp>
#include <SpringForce.hpp>

using namespace std;
using namespace arma;

// Subroutine to identify neighbouring cells and calculate forces between them.
// For all cells, find corresponding background lattice grid location.
// Find all cells in all surrounding lattice points.
// Apply forces between those cells and the cell under consideration.
// Increment cell age
void CalculateForces(vector<cell>& Cells,const mat& gridcount,const cube& gridcells,const float& griddim,const int& Ng,const int& Nc,const float& dt,const float& k, const float& gamma){
  int ix,iy;      // Background grid indices
  int ii,jj,kk,ll;// Loop counters
  for (int ii=0;ii<Nc;ii++){
    // Find grid indices for position of cell ii
    ix = PositionToIndex(Cells[ii],griddim,Ng,0);
    iy = PositionToIndex(Cells[ii],griddim,Ng,1);
    // Neighbouring cells exist in neighbouring grid locations
    for (int jj=-1;jj<2;jj++){
      for (int kk=-1;kk<2;kk++){
        if (((ix+jj)>=Ng)||((ix+jj)<0)||((iy+kk)>=Ng)||((iy+kk)<0)){ // Exclude lattice edges
        }else{
          for (int ll=0;ll<gridcount(ix+jj,iy+kk);ll++){
            // Loop over all cells in neighbouring grid location. Number of cells at location stored in gridcount, labels stored in gridcells.
            if (gridcells(ix+jj,iy+kk,ll)!=ii){ // Do not attempt to find forces between a cell and itself
              // Calculate forces between cell ii and cells in neighbouring grid locations.
              SpringForce(Cells[ii],Cells[gridcells(ix+jj,iy+kk,ll)],k, gamma);
            }else{}
          }
        }
      }
    }
    // Increment cell age.
    Cells[ii].age = Cells[ii].age+dt;
  }
}
