//
//  SpringForce.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 12/03/2019.
//
//

#ifndef SpringForce_hpp
#define SpringForce_hpp

#include <armadillo>
#include <cell.hpp>

void SpringForce(cell& Cell1,cell& Cell2,const float& k, const float& gamma);

#endif /* MorseForce_hpp */
