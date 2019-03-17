//
//  ReadParameters.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 15/03/2019.
//
//

#include "ReadParameters.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void ReadParameters(float& cellradius,float& k,float& gamma,float& dt,float& cellcycletime,float& t_max,float& interactionthreshold,float& zeta_mag,int& init_flag,int& output_flag,float& output_interval){
	static const std::streamsize max = std::numeric_limits<std::streamsize>::max();
	std::vector<float> values;
	string input;
	float value;
	ifstream infile("input/parameters.txt");

	while(infile.ignore(max,' ') >> input >> value)
	{
		values.push_back(value);
	}

	cellradius = values[0];
	k = values[1];
	gamma = values[2];
	dt = values[3];
	cellcycletime = values[4];
	t_max = values[5];
	interactionthreshold = values[6];
	zeta_mag = values[7];
	init_flag = values[8];
	output_flag = values[9];
	output_interval = values[10];

	cout << "cellradius " << cellradius << endl;
  cout << "k " << k << endl;
  cout << "gamma " << gamma << endl;
  cout << "dt " << dt << endl;
  cout << "cellcycletime " << cellcycletime << endl;
  cout << "t_max " << t_max << endl;
  cout << "interactionthreshold " << interactionthreshold << endl;
  cout << "zeta_mag " << zeta_mag << endl;
  cout << "init_flag " << init_flag << endl;
  cout << "output_flag " << output_flag << endl;
  cout << "output_interval " << output_interval << endl;

}
