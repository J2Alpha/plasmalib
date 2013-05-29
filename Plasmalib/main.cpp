/*
 * main.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: admin
 */
/**
@mainpage
\section introduction
plasmalib was born out of a need for a performant elemental particle trajectory simulator. I started writing this during my graduation at the TUDelft.
None of the existing software I had found fit the bill, was hideously slow, or required me to learn yet another scripting language
and all could not easily be extended or locked the data inside them. I also saw it as an opportunity to learn more of C++.
the result is plasmalib: a single purpose charged particle trajectory simulator able to take:
 	 - a list of particles
 	 - some simple EM-field geometry
 	 - a time interval
 	 - and output acceleration, velocity and position over time.

It is meant as a backend to a higher level language frontend like python, matlab or ruby

\section dependencies
the boost library, especically:
 - boost/lexical_cast
 - boost/multiprecision
 - boost/algorithm

\section compilation
compilation is is done with a c++11 compatible compiler, make sure to set the appropriate flags to enable this.
I compile the program via MinGW's g++ with eclipse juno as ide, I see no reason why this program would not compile on another compiler, but I'm no expert on this.

\section running the program
the program was designed to interoperate with external frontends like bluelight that automate the cmd line instruction and allow for easier reading of the output,
 but can be ran stand-alone
to invoke the program from the command line the following syntax is used

	some/where/plasmalib(.exe) acceleratordata propellantdata targetdata

	where:	acceleratordata: unicode file containing the limits and shape of the accelerator
			propellantdata:  unicode file containing gasdata used as propellant
			targetdata: is the path where the output should be stored

the output of the program is a series of txt files, the txt files are named as the chemical element for which they have calculated the motions

 	 example: 	targetdata = h/e/re
 	 	 	 	propellantdata = somewhere/H_and_O.txt
 	 	 	 	acceleratordata = somewhere/else/limits.txt
 	 	 	 	cmd = some/where/plasmalib acceleratordata propellantdata targetdata
 	 	 	 	output = h/e/re/H.txt and h/e/re/O.txt
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <boost/lexical_cast.hpp> // casting all kinds of stuff into all kinds of stuff at will

#include <sstream>
#include <String>

#include "mpdefs.h"
#include "constants.h"
#include "FileIOConditioning.h"
#include "UserIOConditioning.h"
#include "Field.h"
#include "particlemotion.h"


//std::string UserInputToString(int capturelength=256);
//void UserInputToChar(char* out);
//template<typename T> void flexcout(T output,int linetype = 0);
template<class T> T cross_prod(T A, T B);
template<class T> void printsingedepthsetkeys(T set);
void dialogmode();

int main(int argc, char* args[])
{
	if(argc!=4) return 2;
	GAS testgas;
	//GetSpeciesData(testgas,"C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/testgas.txt");
	GetSpeciesData(testgas,args[2]);
	ACCELERATOR dbg;
	//GetAcceleratorData(dbg,"C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/acc1.txt");
	GetAcceleratorData(dbg,args[1]);
	std::vector<std::vector<std::vector<VectorPoint> > > manysmore;
	for(unsigned int i=0;i<testgas.constituents.size();i++)
	{
		//std::vector<std::vector<VectorPoint> > manys =
	manysmore.push_back( Euler_AllSteps(testgas.constituents[i], dbg.Efield,dbg.Bfield, dbg.v0, dbg.x0, dbg.Dt, dbg.nrost));
	}
	//outfile getout("C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/dbgout.txt",',');
	for(unsigned int j=0;j<testgas.constituents.size();j++)
		{
		outfile getout((std::string)args[3]+"/"+testgas.constituents[j].name+".txt",',');
		for(unsigned int i=0; i<manysmore[j].size();i++){
			flexfout(getout.target(),i,0);
			flexfout(getout.target(),i*dbg.Dt,0);
			flexfout(getout.target(),manysmore[j][i][0],0);
			flexfout(getout.target(),manysmore[j][i][1],0);
			flexfout(getout.target(),manysmore[j][i][2],1);
		}
		flexcout("file written for: ");flexcout(testgas.constituents[j].name);
	}
	flexcout("DONE\n");
	//std::exit(0); //doesn't seem to help with returning some sensible exit code on win7
	return 0;
}
/*!prints first layer of vectors etc. using flexcout!*/
/**
 * @brief printer for single layer of keys
 * templated tool for printing out an iterable list of keys, may have unexpected results if used with nonstandard types
 *
 * @todo to be removed or formalised because it's not realy used
 * @param set input, must be iterable
 */
template<class T> void printsingedepthsetkeys(T set){
for( typename T::const_iterator i = set.begin(); i != set.end(); ++i){
		flexcout(*i,1);
	}
}
