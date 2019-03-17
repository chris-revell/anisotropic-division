//
//  CellDeath.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 17/03/2019.
//
//

#ifndef CellDeath_hpp
#define CellDeath_hpp

#include <stdio.h>
#include <random>
#include <chrono>
#include <cell.hpp>
#include <vector>

void CellDeath(std::vector<cell>& Cells, int& Nc,const float& dt, const float& cellcycletime);


#endif /* CellDeath_hpp */
