

#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include "cell.hpp"

using namespace std;
using namespace arma;

// Subroutine to calculate the force exerted by the Morse potential between two given cells.
void MorseForce(cell& Cell1,cell& Cell2){
  float dx,dy,r,F,vx,vy;
  float De    = 1; // Morse potential parameters
  float a     = 1; //
  float re    = 1; //
  float gamma = 1; // Drag factor
  float expfactor;

  // Calculate x and y displacements between the 2 given cells
  dx = Cell1.pos(0) - Cell2.pos(0);
  dy = Cell1.pos(1) - Cell2.pos(1);
  // Calculate distance between cells from x and y displacements
  r = sqrt(pow(dx,2)+pow(dy,2));
  // Use distance to evaluate derivative of Morse potential to give force F
  expfactor = exp(-a*(r-re));
  F = 2*a*De*(expfactor-pow(expfactor,2));
  // Overdamped Langevin => velocity = drag factor * force
  vx = gamma*F*dx/r;
  vy = gamma*F*dy/r;
  Cell1.v(0) = Cell1.v(0)+vx; // Velocity components from forces between different cells sum linearly
  Cell1.v(1) = Cell1.v(1)+vy;
  Cell2.v(0) = Cell2.v(0)-vx;
  Cell2.v(1) = Cell2.v(1)-vy;
}

// Function to return index of a given cell position in a given dimension (dim) within the background lattice of size Ng and width Ng*griddim
int PositionToIndex(const cell& Cell,const float& griddim,const int& Ng,const int& dim){
  int index;
  index = floor((Cell.pos(dim)+(Ng*griddim)/2)/griddim);
  return index;
}

// Subroutine to test all cells in vector Cells and determine whether any are older than the cell cycle time.
// Any cells older than the cell cycle time undergo division. The two daughter cells have age=0
// and are always separated by 2* typical cell radius.
void CellDivision(vector<cell>& Cells,int& Nc,const float& cellradius,const float& cellcycletime){
  float theta;
  for (int ii=0;ii<Nc;ii++){
    if (Cells[ii].age>cellcycletime){
      theta = 2*M_PI*rand()/RAND_MAX;
      Cells.push_back(cell(Cells[ii].pos(0)+cellradius*cos(theta),Cells[ii].pos(1)+cellradius*sin(theta)));
      Cells[ii].pos(0) = Cells[ii].pos(0)-cellradius*cos(theta);
      Cells[ii].pos(1) = Cells[ii].pos(1)-cellradius*sin(theta);
      Cells[ii].age = 0;
    }else{}
  }
  Nc=Cells.size();
}

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
  float dt            = 1;              // Time interval
  float t_max         = 100;            // Total run time for system
  float cellcycletime = 10;             // Age of cell when division is triggered
  cube gridcells      = cube(Ng,Ng,100,fill::zeros);// Labels of cells in each backkground grid location
  mat gridcount       = mat(Ng,Ng,fill::zeros);     // Array containing the number of cells in each background grid location

  // Open data output files.
  outfile1.open("output/cellpositions.txt", ofstream::out);
  outfile2.open("output/cellcount.txt", ofstream::out);

  // Initialise Cells vector with initial cell.
  Cells.push_back(cell(0,0));


  while (t<t_max){
    // Divide all cells with age greater than cell cycle time.
    CellDivision(Cells,Nc,cellradius,cellcycletime);

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

    // Update all cell positions according to cell velocities and write positions to file
    for (int ii=0;ii<Nc;ii++){
      Cells[ii].pos = Cells[ii].pos+dt*Cells[ii].v;
      outfile1 << Cells[ii].pos(0) << " " << Cells[ii].pos(1) << endl;
    }
    // Write cell count at this time interval to file
    outfile2 << Nc << endl;
    // Increment time and write time to command line
    t=t+dt;
    cout << t << endl;
  }

  return 0;
}
