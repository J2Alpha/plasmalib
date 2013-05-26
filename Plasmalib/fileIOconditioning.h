/*
 * fileIOconditioning.h
 *
 *  Created on: Apr 25, 2013
 *      Author: admin
 */

#ifndef FILEIOCONDITIONING_H_
#define FILEIOCONDITIONING_H_

#include <cstdio>
#include <vector>
#include <map>
#include <String>
#include <fstream>
#include <iostream>
#include <typeinfo>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "UserIOConditioning.h"
#include "mpdefs.h"

#include "gas.h"
#include "species.h"
#include "Accelerator.h"
#include "VectorPoint.h"


//TODO: change to class because it has a function, and separate the struct from this file
typedef struct RawStringData{
	std::string filestructure;
	unsigned int keyposition;
	std::vector<std::string> names;
	std::vector<std::string> units;
	std::vector<std::string> SIunits;
	std::vector<std::string> SIfactors;
	std::map<std::string, std::vector<std::string> > data;
	int filler(std::ifstream &inFile, int linemo);
}DataSet;

void GetFileData( RawStringData & newset , std::string filename);
void GetSpeciesData( GAS & gaslist , std::string filename);
void GetAcceleratorData( struct Accelerator & acceltor , std::string filename);

template <class T> std::string DataTypeonKey(std::ifstream &inFile, T keylist);
template <class T> int ModeonKey(std::ifstream &inFile, T &keylist);
template <class T> int LineonKey(std::ifstream &inFile, int linemo, T &newset);


class outfile{
	public:
		outfile(std::string filename,char delim='\n');
		~outfile();
		std::ofstream& target();
	private:
		std::ofstream out;
		std::string filename;
		char delim;
};

template<typename T> void flexfout(std::ofstream& fio, T output,int linetype)
{
	if(linetype==0) {
		fio<<output;//line continues
	}
	if(linetype==1) {
		fio<<output<<std::endl;//line ends
	}
};
/*void flexfout(std::ofstream& fio, VectorPoint output,int linetype)
{
	if(linetype==0) {
		fio<<output[0]<<","<<output[1]<<","<<output[2]<<",";//line continues
	}
	if(linetype==1) {
		fio<<output<<std::endl;//line ends
	}
};*/
#endif /* FILEIOCONDITIONING_H_ */
