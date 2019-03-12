

#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include <cell.hpp>
#include <SpringForce.hpp>
#include <CellDivision.hpp>
#include <CalculateForces.hpp>
#include <string>
#include <delaunator.hpp>

using namespace std;
using namespace arma;

int main(){
  vector<cell> Cells;                   // Vector containing cell objects corresponding to all cells in the system
  ofstream outfile1;                    // Data file
  ofstream outfile2;                    // Data file
  float cellradius    = 1;              // Typical cell radius
  int Ng              = 512;            // Dimensions of background grid
  int Nc              = 0;              // Number of cells in the system
  float k             = 0.0000001;
  float gamma         = 1;
  float t             = 0;              // System clock
  float dt            = 0.01;           // Time interval
  float t_max         = 5000;           // Total run time for system
  float cellcycletime = 1000;           // Age of cell when division is triggered
  vec zeta = vec(2,fill::randn);
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
      Cells.push_back(cell(a,b,cellradius,cellcycletime,fmod(rand(),cellcycletime)));
      Nc++;
    }
    infile.close();
  }else{
    // Initialise Cells vector with initial cell.
    Cells.push_back(cell(1,0,cellradius,cellcycletime,0));
    Cells.push_back(cell(0,1,cellradius,cellcycletime,0));
    Cells.push_back(cell(0,-1,cellradius,cellcycletime,0));
    Nc=3;
  }

  // Open data output files.
  system("rm output/cellcount.txt");
  system("rm output/cellpositions.txt");
  outfile1.open("output/cellpositions.txt", ios::out);
  outfile2.open("output/cellcount.txt", ios::out);

  while (t<t_max){

    // Divide all cells with age greater than cell cycle time.
    CellDivision(Cells,Nc);

    // Calculate forces between identified nearest neighbours and hence cell velocities.
    vector<double> coords;
    for (int ii=0;ii<Nc;ii++){
      coords.push_back(static_cast<double>(Cells[ii].pos(0)));
      coords.push_back(static_cast<double>(Cells[ii].pos(1)));
    }
    delaunator::Delaunator triangulation(coords);
    CalculateForces(Cells,triangulation.triangles,Nc,dt,k,gamma);

    // Update all cell positions according to cell velocities and increment cell age
    for (int ii=0;ii<Nc;ii++){
      Cells[ii].pos = Cells[ii].pos+dt*Cells[ii].v;//+zeta.randn()/10000.0;
      Cells[ii].age = Cells[ii].age+dt;
    }

    // Output cell positions to file every 100s.
    if (fmod(t,100)<(dt-0.0001)){
      cout << t << endl;
      // Write positions to file
      for (int ii=0;ii<Nc;ii++){
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
