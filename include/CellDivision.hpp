//
//  CellDivision.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 27/11/2018.
//
//

#ifndef CellDivision_hpp
#define CellDivision_hpp

#include <vector>
#include <cell.hpp>

// Subroutine to test all cells in vector Cells and determine whether any are older than the cell cycle time.
void CellDivision(std::vector<cell>& Cells,int& Nc);

#endif /* CellDivision_hpp */
