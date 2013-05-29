/*
 * main.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: admin
 */

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

template<class T> void printsingedepthsetkeys(T set){
for( typename T::const_iterator i = set.begin(); i != set.end(); ++i){
		flexcout(*i,1);
	}
}
