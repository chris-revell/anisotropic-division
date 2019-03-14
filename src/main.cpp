

#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include <cell.hpp>
#include <SpringForce.hpp>
#include <CellDivision.hpp>
#include <CalculateForces.hpp>
#include <Initialise.hpp>
#include <delaunator.hpp>
#include <CalculateNoise.hpp>

using namespace std;
using namespace arma;

int main(){
  // Parameters of system
  float cellradius           = 1;               // Typical cell radius (ie Equilibrium separation for inter-cell interaction of cell with age 0)
  float k                    = 0.0000010;       // Interaction spring constant
  float gamma                = 10;               // Overdamped Langevin equation drag factor
  float dt                   = 1;               // Time interval  
  float cellcycletime        = 5000;            // Age of cell when division is triggered
  float t_max                = 50*cellcycletime;// Total run time for system
  float interactionthreshold = 1.4;             // Distance threshold for interactions as a proportion of equilibrium distance
  float zeta_mag             = 10.0;             // Magnitude of stochastic component
  // Control flags
  int init_flag              = 0;               // =1 if reading initial state from file, =0 if starting from 1 cell.
  int output_flag            = 1;               // if =0 data output only at final state, otherwise at every output_interval.
  float output_interval      = t_max/10;
  // Other variable definitions
  float t                    = 0;               // System clock
  int Nc                     = 0;               // Number of cells in the system
  vector<cell> Cells;                           // Vector containing cell objects corresponding to all cells in the system
  ofstream outfile1,outfile2;                   // Data file

  // Initialise system
  Initialise(init_flag,Cells,Nc,cellradius,cellcycletime,outfile1,outfile2);

  while (t<t_max){

    // Divide all cells with age greater than cell cycle time.
    //CellDivision(Cells,Nc);

    // Calculate forces between identified nearest neighbours and hence cell velocities.
    vector<double> coords;
    for (int ii=0;ii<Nc;ii++){
      coords.push_back(static_cast<double>(Cells[ii].pos(0)));
      coords.push_back(static_cast<double>(Cells[ii].pos(1)));
    }
    delaunator::Delaunator triangulation(coords);
    CalculateForces(Cells,triangulation.triangles,Nc,dt,k,gamma,interactionthreshold);

    CalculateNoise(Cells,zeta_mag);

    // Update all cell positions according to cell velocities and increment cell age
    for (int ii=0;ii<Nc;ii++){
      Cells[ii].pos = Cells[ii].pos+dt*Cells[ii].v;      
      Cells[ii].age = Cells[ii].age+dt;
    }

    // Output cell positions to file every 100s.
    if ((fmod(t,output_interval)<(dt-0.0001)) && (output_flag==1)){
      cout << t << endl;
      // Write positions to file
      for (int ii=0;ii<Nc;ii++){
        outfile1 << Cells[ii].pos(0) << " " << Cells[ii].pos(1) << " " << Cells[ii].clone << endl;
      }
      // Write cell count at this time interval to file
      outfile2 << Nc << endl;
    }

    // Increment time and write time to command line
    t=t+dt;

  }

  // Final data output
  cout << t << endl;
  // Write positions to file
  for (int ii=0;ii<Nc;ii++){
    outfile1 << Cells[ii].pos(0) << " " << Cells[ii].pos(1) << " " << Cells[ii].clone << endl;
  }
  // Write cell count at this time interval to file
  outfile2 << Nc << endl;
  
  return 0;
}

