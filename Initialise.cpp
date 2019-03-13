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
#include <cell>

using namespace std;

void Initialise(const int& init_flag, vector<cell>& Cells, int& Nc,const float& cellradius,const float& cellcycletime,const float& cellcycletime,ofstream& outfile1,ofstream& outfile2){
  if (init_flag==1){
    ifstream infile;
    string line;
    float a,b;
    infile.open("input/startstate.txt", ios::in);
    while ( getline(infile,line) )
    {
      a = stof(line.substr(0,8));
      b = stof(line.substr(25,8));
      Cells.push_back(cell(Nc,Nc,a,b,cellradius,cellcycletime,fmod(rand(),cellcycletime)));
      Nc++;
    }
    infile.close();
  }else{
    // Initialise Cells vector with initial cell.
    Cells.push_back(cell(0,0,1,0,cellradius,cellcycletime,0));
    Cells.push_back(cell(1,1,0,1,cellradius,cellcycletime,0));
    Cells.push_back(cell(2,2,0,-1,cellradius,cellcycletime,0));
    Nc=3;
  }

  // Open data output files.
  system("rm output/cellcount.txt");
  system("rm output/cellpositions.txt");
  outfile1.open("output/cellpositions.txt", ios::out);
  outfile2.open("output/cellcount.txt", ios::out);
}
