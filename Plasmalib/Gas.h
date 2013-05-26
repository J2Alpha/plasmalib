/*
 * Gas.h
 *
 *  Created on: Apr 19, 2013
 *      Author: admin
 */

#ifndef GAS_H_
#define GAS_H_

#include <String>
#include <vector>
//#include <iostream>
#include <fstream>
#include <stdexcept> //out of range exception


#include "constants.h"
#include "mpdefs.h"
#include "species.h"

#include "UserIOConditioning.h"

typedef struct Gas
{
	std::string filename;
	std::string filestructure;
	std::string name;
	std::vector<Species> constituents;
	int filler(std::ifstream &inFile, int linemo);
}GAS;

#endif /* GAS_H_ */
