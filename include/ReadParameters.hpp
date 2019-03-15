//
//  ReadParameters.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 15/03/2019.
//
//

#ifndef ReadParameters_hpp
#define ReadParameters_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void ReadParameters(float& cellradius,float& k,float& gamma,float& dt,float& cellcycletime,float& t_max,float& interactionthreshold,float& zeta_mag,int& init_flag,int& output_flag,float& output_interval);

#endif /* ReadParameters_hpp */
