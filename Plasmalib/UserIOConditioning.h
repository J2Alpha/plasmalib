/*
 * UserIOConditioning.h
 *  various format converters,
 *  mostly to turn user input to variables or output variables to screen
 *  Created on: Apr 21, 2013
 *      Author: admin
 */

#ifndef USERIOCONDITIONING_H_
#define USERIOCONDITIONING_H_
#include <stdio.h>
#include <iostream>
#include <boost/algorithm/string.hpp> // stringy algorithms, use <boost/Algorithm/string_regex.hpp> if simple regex is needed
//#include <boost/numeric/ublas/io.hpp>
#include <sstream>
#include <String>
#include <vector>
#include <ios>

extern std::vector<std::string> split(const std::string &s, char delim);//split a string
extern std::string UserInputToString(int capturelength = 256);//get a string from cin
extern void UserInputToChar(char* out);//get to char[]
//keyword export not defined in mingw
//to simplify outputting to std::cout for debugging.
//a bit like a macro but more flexible
//TODO: definition needs to be here? or not?
template<typename T> void flexcout(T output,int linetype = 0)
{
	if(linetype==0) {
		std::cout<<output;//line continues
	}
	if(linetype==1) {
		std::cout<<output<<std::endl;//line ends
	}
};

template <typename T> std::string NumberToString ( T Number );
template <typename T> T StringToNumber ( const std::string &Text );

#endif /* USERIOCONDITIONING_H_ */
