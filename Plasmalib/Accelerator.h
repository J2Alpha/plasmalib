/*
 * Accelerator.h
 *
 *  Created on: 21-mei-2013
 *      Author: admin
 */

#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_
//todo: split reading into fileioconditionings somehow with empty object or such
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept> //out of range exception

//#include <boost/algorithm/string/split.hpp>

#include "mpdefs.h"
#include "fileIOconditioning.h"
#include "VectorPoint.h"
#include "field.h"
#include "UserIOConditioning.h"


typedef struct Accelerator{
	std::string filestructure;
	std::string name;//0
	Field Efield;
	Field Bfield;
	VectorPoint x0;//3
	VectorPoint v0;
	mpelement Dt;
	unsigned int nrost;
	int filler(std::ifstream &inFile, int linemo);
}ACCELERATOR;

#endif /* ACCELERATOR_H_ */
