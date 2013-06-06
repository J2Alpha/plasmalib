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

#include "C:/Users/J2Alpha/sqlite-amalgamation-3071700/sqlite3.h"

#include "UserIOConditioning.h"
#include "mpdefs.h"

#include "gas.h"
#include "species.h"
#include "Accelerator.h"
#include "VectorPoint.h"
#include "Sqlitedb.h"

//TODO: change to class because it has a function, and separate the struct from this file

void GetSpeciesData( GAS & gaslist , std::string filename);
void GetAcceleratorData( struct Accelerator & acceltor , std::string filename);

void GetSpeciesData_DB( GAS & gaslist , Sqlitedb & db);
void GetAcceleratorData_DB( struct Accelerator & acceltor , Sqlitedb & db);

template <class T> std::string DataTypeonKey(std::ifstream &inFile, T keylist);
template <class T> int ModeonKey(std::ifstream &inFile, T &keylist);
template <class T> int LineonKey(std::ifstream &inFile, int linemo, T &newset);


class outfile{
	public:
		outfile(std::string filename,char delim='\n');
		~outfile();
		std::ofstream& target();
		char delimit();
	private:
		std::ofstream out;
		std::string filename;
		char delim;
};
/**@fn flexfout
 * @brief output to file if the input supports the outputstream operator (<<)
 *
 * @param fio reference to output file
 * @param output the object to write to file, must have << operator defined for it
 * @param linetype 0 to continue the line or 1 to insert an std::endl
 */
template<typename T> void flexfout(outfile& of, T output,int linetype)
{
	std::ofstream& fio= of.target();
	char delim = of.delimit();
	if(linetype==0) {
		fio<<output<<delim;//line continues
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
