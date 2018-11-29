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
  cell(const float& initialx,const float& initialy); // Constructor takes initial cell position in x and y dimensions
  arma::mat pos;     // Cell position
  arma::mat v;       // Cell velocity
  float     age;     // Cell age
  ~cell();           // Destructor
protected:

};


#endif /* cell_hpp */
