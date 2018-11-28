

#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include <cell.hpp>
#include <MorseForce.hpp>
#include <PositionToIndex.hpp>
#include <CellDivision.hpp>
#include <GridUpdate.hpp>

using namespace std;
using namespace arma;

int main(){
  vector<cell> Cells;                   // Vector containing cell objects corresponding to all cells in the system
  ofstream outfile1;                    // Data file
  ofstream outfile2;                    // Data file
  float cellradius    = 1;              // Typical cell radius
  float r_int_max     = 1.5*cellradius; // Maximum interaction radius for inter-cell forces
  float griddim       = r_int_max;      // Spatial size of each background grid location
  int Ng              = 258;            // Dimensions of background grid
  int Nc              = 1;
  int ix,iy;                            // Background grid indices
  float t             = 0;              // System clock
  float dt            = 0.1;            // Time interval
  float t_max         = 100;            // Total run time for system
  float cellcycletime = 10;             // Age of cell when division is triggered
  cube gridcells      = cube(Ng,Ng,500,fill::zeros);// Labels of cells in each backkground grid location
  mat gridcount       = mat(Ng,Ng,fill::zeros);     // Array containing the number of cells in each background grid location

  // Open data output files.
  outfile1.open("output/cellpositions.txt", ofstream::out);
  outfile2.open("output/cellcount.txt", ofstream::out);

  // Initialise Cells vector with initial cell.
  Cells.push_back(cell(0,0));


  while (t<t_max){
    // Divide all cells with age greater than cell cycle time.
    CellDivision(Cells,Nc,cellradius,cellcycletime);

    GridUpdate(Cells,gridcount,gridcells,Nc,Ng,griddim);

    // For all cells, find corresponding background lattice grid location.
    // Find all cells in all surrounding lattice points.
    // Apply forces between those cells and the cell under consideration.
    // Increment cell age
    for (int ii=0;ii<Nc;ii++){
      ix = PositionToIndex(Cells[ii],griddim,Ng,0);
      iy = PositionToIndex(Cells[ii],griddim,Ng,1);
      for (int jj=-1;jj<2;jj++){
        for (int kk=-1;kk<2;kk++){
          if (((ix+jj)>=Ng)||((ix+jj)<0)||((iy+kk)>=Ng)||((iy+kk)<0)){ // Exclude lattice edges
          }else{
            for (int ll=0;ll<gridcount(ix+jj,iy+kk);ll++){
              if (gridcells(ix+jj,iy+kk,ll)!=ii){ // Do not attempt to find forces between a cell and itself
                MorseForce(Cells[ii],Cells[gridcells(ix+jj,iy+kk,ll)]);
              }else{}
            }
          }
        }
      }
      Cells[ii].age = Cells[ii].age+dt;
    }

    if (fmod(t,5)<dt){
      cout << t << " " << fmod(t,10.0) << endl;
      // Update all cell positions according to cell velocities and write positions to file
      for (int ii=0;ii<Nc;ii++){
        Cells[ii].pos = Cells[ii].pos+dt*Cells[ii].v;
        outfile1 << Cells[ii].pos(0) << " " << Cells[ii].pos(1) << endl;
      }
      // Write cell count at this time interval to file
      outfile2 << Nc << endl;
    }

    // Increment time and write time to command line
    t=t+dt;
    //cout << t << endl;
  }

  return 0;
}
