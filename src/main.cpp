

#include <cmath>
#include <armadillo>
#include <vector>
#include <iostream>
#include "cell.hpp"

using namespace std;
using namespace arma;

void MorseForce(cell& Cell1,cell& Cell2){
  float dx,dy,r,F,vx,vy;
  float De = 1;
  float a  = 1;
  float re = 1;
  float expfactor;

  dx = Cell1.pos(0) - Cell2.pos(0);
  dy = Cell1.pos(1) - Cell2.pos(1);
  r = sqrt(pow(dx,2)+pow(dy,2));
  expfactor = exp(-a*(r-re));
  F = 2*a*De*(expfactor-pow(expfactor,2));
  vx = F*dx/r;
  vy = F*dy/r;
  Cell1.v(0) = Cell1.v(0)+vx;
  Cell1.v(1) = Cell1.v(1)+vy;
  Cell2.v(0) = Cell2.v(0)-vx;
  Cell2.v(1) = Cell2.v(1)-vy;
}

int PositionToIndex(const cell& Cell,const float& griddim,const int& Ng,const int& dim){
  int index;
  index = floor((Cell.pos(dim)+(Ng*griddim)/2)/griddim);
  return index;
}

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

  vector<cell> Cells;
  ofstream outfile1;
  ofstream outfile2;
  float cellradius    = 1;
  float r_int_max     = 1.5*cellradius;
  float griddim       = r_int_max;
  int Ng              = 258;
  int Nc              = 1;
  int ix,iy;
  float t             = 0;
  float dt            = 1;
  float t_max         = 100;
  float cellcycletime = 10;
  cube gridcells      = cube(Ng,Ng,100,fill::zeros);
  mat gridcount       = mat(Ng,Ng,fill::zeros);

  outfile1.open("output/cellpositions.txt", ofstream::out);
  outfile2.open("output/cellcount.txt", ofstream::out);

  Cells.push_back(cell(0,0));

  while (t<t_max){
    CellDivision(Cells,Nc,cellradius,cellcycletime);
    gridcount.zeros();
    for (int ii=0;ii<Nc;ii++){
      ix = PositionToIndex(Cells[ii],griddim,Ng,0);
      iy = PositionToIndex(Cells[ii],griddim,Ng,1);
      gridcells(ix,iy,gridcount(ix,iy))=ii;
      gridcount(ix,iy)++;
      Cells[ii].v.zeros();
    }
    for (int ii=0;ii<Nc;ii++){
      ix = PositionToIndex(Cells[ii],griddim,Ng,0);
      iy = PositionToIndex(Cells[ii],griddim,Ng,1);
      for (int jj=-1;jj<2;jj++){
        for (int kk=-1;kk<2;kk++){
          if (((ix+jj)>=Ng)||((ix+jj)<0)||((iy+kk)>=Ng)||((iy+kk)<0)){
          }else{
            for (int ll=0;ll<gridcount(ix+jj,iy+kk);ll++){
              if (gridcells(ix+jj,iy+kk,ll)!=ii){
                MorseForce(Cells[ii],Cells[gridcells(ix+jj,iy+kk,ll)]);
              }else{}
            }
          }
        }
      }
      Cells[ii].age = Cells[ii].age+dt;
    }
    for (int ii=0;ii<Nc;ii++){
      Cells[ii].pos = Cells[ii].pos+dt*Cells[ii].v;
      outfile1 << Cells[ii].pos(0) << " " << Cells[ii].pos(1) << endl;
    }
    outfile2 << Nc << endl;

    t=t+dt;
    cout << t << endl;
  }

  return 0;
}
