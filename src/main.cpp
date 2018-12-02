

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
#include <string>

using namespace std;
using namespace arma;

int main(){
  vector<cell> Cells;                   // Vector containing cell objects corresponding to all cells in the system
  ofstream outfile1;                    // Data file
  ofstream outfile2;                    // Data file
  float cellradius    = 1;              // Typical cell radius
  float griddim       = 1.5*sqrt(2)*cellradius;   // Spatial size of each background grid location
  int Ng              = 512;            // Dimensions of background grid
  int Nc              = 0;              // Number of cells in the system
  float t             = 0;              // System clock
  float dt            = 0.01;           // Time interval
  float t_max         = 70000;          // Total run time for system
  float cellcycletime = 20000;           // Age of cell when division is triggered
  cube gridcells      = cube(Ng,Ng,500,fill::zeros);// Labels of all cells in each background grid location
  mat gridcount       = mat(Ng,Ng,fill::zeros);     // Array containing the number of cells in each background grid location
  int init_flag       = 1;    // =1 if reading initial state from file, =0 if starting from 1 cell.

  if (init_flag==1){
    ifstream infile;
    string line;
    float a,b;
    infile.open("input/startstate.txt", ios::in);
    while ( getline(infile,line) )
    {
      a = stof(line.substr(0,8));
      b = stof(line.substr(25,8));
      Cells.push_back(cell(a,b));
      Cells[Nc].age = fmod(rand(),cellcycletime);
      Nc++;
    }
    infile.close();
  }else{
    // Initialise Cells vector with initial cell.
    Cells.push_back(cell(0,0));
    Nc=1;
  }

  // Open data output files.
  outfile1.open("output/cellpositions.txt", ios::out);
  outfile2.open("output/cellcount.txt", ios::out);

  while (t<t_max){
    // Divide all cells with age greater than cell cycle time.
    CellDivision(Cells,Nc,cellradius,cellcycletime);

    // Update background grid for identifying nearest neighbours.
    GridUpdate(Cells,gridcount,gridcells,Nc,Ng,griddim);

    // Calculate forces between identified nearest neighbours and hence cell velocities.
    CalculateForces(Cells,gridcount,gridcells,griddim,Ng,Nc,cellcycletime,cellradius,dt);

    // Output cell positions to file every 100s.
    if (fmod(t,100)<(dt-0.0001)){
      cout << t << endl;
      cout << fmod(t,100) << endl;

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
