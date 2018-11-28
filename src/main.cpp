

#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include <cell.hpp>
#include <MorseForce.hpp>
#include <PositionToIndex.hpp>
#include <CellDivision.hpp>
#include <GridUpdate.hpp>
#include <CalculateForces.hpp>

using namespace std;
using namespace arma;

int main(){
  vector<cell> Cells;                   // Vector containing cell objects corresponding to all cells in the system
  ofstream outfile1;                    // Data file
  ofstream outfile2;                    // Data file
  float cellradius    = 1;              // Typical cell radius
  //float r_int_max     = 1.5*cellradius; // Maximum interaction radius for inter-cell forces
  float griddim       = 2*cellradius;//r_int_max;      // Spatial size of each background grid location
  int Ng              = 512;            // Dimensions of background grid
  int Nc;                               // Number of cells in the system
  float t             = 0;              // System clock
  float dt            = 0.01;           // Time interval
  float t_max         = 1000;           // Total run time for system
  float cellcycletime = 100;            // Age of cell when division is triggered
  cube gridcells      = cube(Ng,Ng,500,fill::zeros);// Labels of all cells in each background grid location
  mat gridcount       = mat(Ng,Ng,fill::zeros);     // Array containing the number of cells in each background grid location

  // Open data output files.
  outfile1.open("output/cellpositions.txt", ofstream::out);
  outfile2.open("output/cellcount.txt", ofstream::out);

  // Initialise Cells vector with initial cell.
  Cells.push_back(cell(0,0));
  Nc=1;

  while (t<t_max){
    // Divide all cells with age greater than cell cycle time.
    CellDivision(Cells,Nc,cellradius,cellcycletime);

    GridUpdate(Cells,gridcount,gridcells,Nc,Ng,griddim);

    CalculateForces(Cells,gridcount,gridcells,griddim,Ng,Nc,cellcycletime,cellradius,dt);

    if (fmod(t,1)<dt){
      cout << t << endl;
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

  }

  return 0;
}
