//
//  Initialise.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 13/03/2019.
//
//

#include "Initialise.hpp"
#include <iostream>
#include <string>
#include <cell.hpp>
#include <random>

using namespace std;

void Initialise(const int& init_flag, vector<cell>& Cells, int& Nc, int& NcT,const float& cellradius,const float& cellcycletime,ofstream& outfile1,ofstream& outfile2){
  if (init_flag==1){
    ifstream infile;
    string line;
    float a,b;
    infile.open("input/startstate2.txt", ios::in);
    while ( getline(infile,line) )
    {
      a = stof(line.substr(0,8));
      b = stof(line.substr(25,8));
      Cells.push_back(cell(Nc,Nc,a,b,cellradius,cellcycletime,fmod(rand(),cellcycletime)));
      Nc++;
    }
    infile.close();    
  }else if (init_flag==2){
    // Initialise Cells vector with initial cell.
    Cells.push_back(cell(0,0,1,0,cellradius,cellcycletime,0));
    Cells.push_back(cell(1,1,0,1,cellradius,cellcycletime,0));
    Cells.push_back(cell(2,2,0,-1,cellradius,cellcycletime,0));
    Nc=3;    
  }else if (init_flag==0){
    // Set number of cells such that cell volume roughly fills 50x50 space.
    Nc = 100*100/(M_PI*pow(1.5*cellradius,2));
    
    // The following 0-1 random number generator from https://stackoverflow.com/questions/9878965/rand-between-0-and-1
      std::mt19937_64 rng;
      // initialize the random number generator with time-dependent seed
      uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
      rng.seed(ss);
      // initialize a uniform distribution between 0 and 1
      std::uniform_real_distribution<float> unif(0, 1);
      float posx,posy,ranage;
      // ready to generate random numbers
    //

    for (int i = 0; i < Nc; ++i)
    {
      posx = 100*unif(rng)-50;
      posy = 100*unif(rng)-50;
      ranage = cellcycletime*unif(rng);
      Cells.push_back(cell(i,i,posx,posy,cellradius,cellcycletime,ranage));
    }    
  }
  NcT = Nc;
  
  // Open data output files.
  system("rm output/cellcount.txt");
  system("rm output/cellpositions.txt");
  outfile1.open("output/cellpositions.txt", ios::out);
  outfile2.open("output/cellcount.txt", ios::out);
}
