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
I made a python frontend named bluelight, based on matplotlib and am building one on ruby named redlight

\section dependencies
the boost library, especically:
 - boost/lexical_cast
 - boost/multiprecision
 - boost/algorithm

\section compilation
compilation is is done with a c++11 compatible compiler, make sure to set the appropriate flags to enable this.
I compile the program via MinGW's g++ with eclipse juno as ide, I see no reason why this program would not compile on another compiler,
but I'm no expert on this, due to the flakyness of compiler support for the newer features of C++11 it could that your specific compiler will not work.
I ran into some of this malarky myself while building perfectly legal code according to book and net.

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
\section small nimble todos
some additonal functionality that shouldn't take more that a day or two to do:
	- fix the time format so its actually readable withouth magic
	- prealocate the big ass vector memory, is sure to be faster
	- test the in_pieces variant of Euler_(all)step(s) can yield more insight into behaviour
	- instead of one huge write to file, write sequentially, measure if thats faster
	- complete the documentation, natch
\section big honking todos
want something big to do well here you go:
	- expose the vector directly to python or ruby or such to avoid having to write those huge ass files and increase interaction
	- stop storing wrappers around a vector in vectors of vectors of vectors, interface to a database, hey that rimes, boost has some good interfaces for this they say
	- make the frontend in sdl, turn this lib into a one stop solution
	- use ruby on rails (thats what i'd do) to offload computation somewhere else over the network, so a netbook could run epic sims
	- threading: the writing and the calculating could run parrallel especially if the list of particle types is a long as your arm
	- threading: could even be used to run all the particles in parallel, not on this laptop it couldn't but it could on serious multicore systems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <boost/lexical_cast.hpp> // casting all kinds of stuff into all kinds of stuff at will
#include "C:/Users/J2Alpha/sqlite-amalgamation-3071700/sqlite3.h"

#include <sstream>
#include <String>

#include "mpdefs.h"
#include "constants.h"
#include "FileIOConditioning.h"
#include "UserIOConditioning.h"
#include "Field.h"
#include "particlemotion.h"
#include "Sqlitedb.h"

//std::string UserInputToString(int capturelength=256);
//void UserInputToChar(char* out);
//template<typename T> void flexcout(T output,int linetype = 0);
template<class T> T cross_prod(T A, T B);
template<class T> void printsingedepthsetkeys(T set);
void dialogmode();

int filemode(char* args[]);
int dbmode(char* args[]);

bool DBMODE=false;
bool FILEMODE=false;

int main(int argc, char* args[])
{
	if(argc==2) DBMODE = true;
	if(argc==4) FILEMODE = true;
	else
	{
		return 2;
	}

	if(FILEMODE)
	{
		filemode(args);
	}
	if(DBMODE)
	{
		dbmode(args)	;
	}
	flexcout("DONE\n");
	//std::exit(0); //doesn't seem to help with returning some sensible exit code on win7
	return 0;
}

int filemode(char* args[])
{
	GAS testgas;
	ACCELERATOR dbg;
	GetSpeciesData(testgas,args[2]);//GetSpeciesData(testgas,"C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/testgas.txt");
	GetAcceleratorData(dbg,args[1]);//GetAcceleratorData(dbg,"C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/acc1.txt");

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
				flexfout(getout,i,0);
				flexfout(getout,i*dbg.Dt,0);
				flexfout(getout,manysmore[j][i][0],0);
				flexfout(getout,manysmore[j][i][1],0);
				flexfout(getout,manysmore[j][i][2],1);
			}
			flexcout("file written for: ");flexcout(testgas.constituents[j].name);
		}
		return 0;
}
int dbmode(char* args[])
{
	Sqlitedb maindb(args[1]);
	GAS testgas;
	ACCELERATOR dbg;
	GetSpeciesData_DB(testgas,maindb);
	GetAcceleratorData_DB(dbg,maindb);

		std::vector<std::vector<std::vector<VectorPoint> > > manysmore;
		Euler_AllSteps_DB(testgas, dbg, maindb);

		flexcout("DONE")

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
