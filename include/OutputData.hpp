//
//  OutputData.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 19/03/2019.
//
//

#ifndef OutputData_hpp
#define OutputData_hpp

#include <stdio.h>
#include <vector>
#include <armadillo>
#include <cell.hpp>

void OutputData(const std::vector<cell>& Cells, const float& t, const int& Nc, std::ofstream& outfile1, std::ofstream& outfile2);

#endif /* OutputData_hpp */
