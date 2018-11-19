//
//  cell.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 19/11/2018.
//
//

#ifndef cell_hpp
#define cell_hpp

#include <armadillo>

class cell {
private:
public:
  cell(const float& initialx,const float& initialy);
  arma::mat pos;
  arma::mat v;
  float     age;
  ~cell();
protected:

};


#endif /* cell_hpp */
