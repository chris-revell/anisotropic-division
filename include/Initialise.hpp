//
//  Initialise.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 13/03/2019.
//
//

#ifndef Initialise_hpp
#define Initialise_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <cell.hpp>
#include <random>

void Initialise(const int& init_flag, std::vector<cell>& Cells, int& Nc, int& NcT,const float& cellradius,const float& cellcycletime,std::ofstream& outfile1,std::ofstream& outfile2);


#endif /* Initialise_hpp */
