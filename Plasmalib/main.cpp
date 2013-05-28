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

int main()
{
	/*
	flexcout("feel talkative? many, many little dialogs mode (press:0) or load a file (press:1)");
	;if(UserInputToString()=="0") dialogmode();
	else flexcout("not implemented");
	*/
	/*DataSet mendel;
	GetFileData(mendel,"C:/Users/J2Alpha/Documents/GitHub/c++eclipse/PlasmaFront/Debug/tableofelements.txt");
	flexcout("datatype :"); flexcout(mendel.filestructure,1);
	flexcout("keyposition :");flexcout(mendel.keyposition,1);
	flexcout("namessize :");flexcout(mendel.names.size(),1);
	flexcout("unitsize :");flexcout(mendel.units.size(),1);
	flexcout("sunitsize :");flexcout(mendel.SIfactors.size(),1);
	flexcout("datassize :");flexcout(mendel.data.size(),1);
	printsingedepthsetkeys(mendel.units);*/
	GAS testgas;
	GetSpeciesData(testgas,"C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/testgas.txt");
	flexcout("filename :"); flexcout(testgas.filename,1);
	flexcout("setname :");flexcout(testgas.filestructure,1);
	flexcout("gasname :");flexcout(testgas.name,1);
	flexcout("mass? :");flexcout(testgas.constituents[0].Mass,1);
	flexcout("eulertest",1);
	ACCELERATOR dbg;
	GetAcceleratorData(dbg,"C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/acc1.txt");
	flexcout("accelerator name :"); flexcout(dbg.name,1);
	flexcout("x0:");flexcout(dbg.x0,1);
	flexcout("tiemstep :");flexcout(dbg.Dt,1);
	flexcout("tiems :");flexcout(dbg.nrost,1);
	/*VectorPoint E(1,0,0);
	VectorPoint B(0,1,0);
	Field fE=(E);
	Field fB=(B);
	VectorPoint v0(0,0,0);
	VectorPoint x0(0,0,0);
	//flexcout("stepsize, use xE+/-xx format: ");
	mpelement timestep("1E-9");//UserInputToString()) ;
	//test one time
	flexcout("cross prod: ");
	flexcout(E.X(B),1);
	std::vector<VectorPoint> ones = Euler_OneStep(testgas.constituents[0], fE,fB, v0, x0, timestep);
	flexcout("for input:",1);
	flexcout("t: ");flexcout(timestep,1);
	flexcout("E: ");flexcout(fE.at(x0));flexcout(" V/m | B: ");flexcout(fB.at(x0));flexcout(" T",1);
	flexcout("v0: ");flexcout(v0);flexcout(" m/s | x0: ");flexcout(x0);flexcout(" m",1);
	flexcout("c: ");flexcout(testgas.constituents[0].Charge);flexcout(" C | mass: ");flexcout(testgas.constituents[0].Mass);flexcout(" kg",1);
	flexcout("one step of ");flexcout(timestep);flexcout(" is:",1);
	flexcout(" a is: ");flexcout(ones[0],1);
	flexcout(" v is: ");flexcout(ones[1],1);
	flexcout(" x is: ");flexcout(ones[2],1);
	//test many times
	int times=1000;*/
	std::vector<std::vector<VectorPoint> > manys = Euler_AllSteps(testgas.constituents[0], dbg.Efield,dbg.Bfield, dbg.v0, dbg.x0, dbg.Dt, dbg.nrost);
	flexcout("for input:",1);
	flexcout("t: ");flexcout(dbg.Dt,1);
	flexcout("E: ");flexcout(dbg.Efield.at(dbg.x0));flexcout(" V/m | B: ");flexcout(dbg.Bfield.at(dbg.x0));flexcout(" T",1);
	flexcout("v0: ");flexcout(dbg.v0);flexcout(" m/s | x0: ");flexcout(dbg.x0);flexcout(" m",1);
	flexcout("c: ");flexcout(testgas.constituents[0].Charge);flexcout(" C | mass: ");flexcout(testgas.constituents[0].Mass);flexcout(" kg",1);
	flexcout("after ");flexcout(dbg.Dt*dbg.nrost);flexcout(" [s] results are:",1);
	//flexcout(manys.size());
	flexcout(" a is: ");flexcout(manys[dbg.nrost-1][0]);flexcout(" m/s² ",1);
	flexcout(" v is: ");flexcout(manys[dbg.nrost-1][1]);flexcout(" m/s ",1);
	flexcout(" x is: ");flexcout(manys[dbg.nrost-1][2]);flexcout(" m ",1);
	outfile getout("C:/Users/J2Alpha/gitrepos/Plasmalib/Plasmalib/Debug/dbgout.txt",',');
	for(unsigned int i=0; i<manys.size();i++){
		flexfout(getout.target(),i,0);
		flexfout(getout.target(),i*dbg.Dt,0);
		flexfout(getout.target(),manys[i][0],0);
		flexfout(getout.target(),manys[i][1],0);
		flexfout(getout.target(),manys[i][2],1);
	}
	flexcout("eoo");
	//std::exit(0);
	return 0;
}

template<class T> void printsingedepthsetkeys(T set){
for( typename T::const_iterator i = set.begin(); i != set.end(); ++i){
		flexcout(*i,1);
	}
}
void dialogmode()
{
	flexcout(mu0);
	flexcout("electrode gap in [m]:");
	mpelement Egap(UserInputToString());
	flexcout("potential difference in [V]:");
	mpelement potV(UserInputToString());
	mpelement Eu = potV/Egap;//fieldstrength
	flexcout("Electric fieldstrengt if assumed uniform in gap = ");flexcout(Eu);flexcout("V/m",1);
	//H-fieldstrength
	flexcout("magnetic fieldstrength determined by: holding force  [kg] (press: 0) or magnetic remanence [T] (press: 1)");
	mpelement B0;
	char uchose[256];
	UserInputToChar(uchose);
	if(uchose[0]=='0'){
		flexcout("holding force in [kg]:");
		mpelement Fkg(UserInputToString());
		flexcout("surface area of magnet in [m^2]:");
		mpelement Amag(UserInputToString());
		//B0=sqrt(Fkg*g0*2*mu0/Amag);
		flexcout("assuming 2 parallel aligned magnets at opposite sides of gap",1);
		flexcout("Magnetic fieldstrength if assumed uniform in gap = ");flexcout(2*B0);flexcout("T",1);
	}
	if(uchose[0]=='1'){
		flexcout("remanence in [T]:");
		B0=mpelement(UserInputToString());
		flexcout("assuming 2 parallel aligned magnets at opposite sides of gap",1);
		flexcout("Magnetic fieldstrength if assumed uniform in gap = ");flexcout(2*B0);flexcout("T",1);
	}
	//mpelement B=0.136;
	//limits to geometries ltube, ltotal and times dt, tend
	flexcout("length of accelerator [m]:");
	mpelement Lacc(UserInputToString());
	flexcout("length to stop calculating at[m]:");
	mpelement Lstop(UserInputToString());
	flexcout("maximum timestep [dt]:");
	mpelement Tstep(UserInputToString());
	//mpvector E;
	//mpvector B;
	//mpvector v;
	//mpvector a;
	//mpvector x;


	//get initial values for a,v,z
	//std::cout<<gap<<std::endl;
	/*mpvector t1(3);
	t1(0)= 1;
	t1(1)= 2;
	t1(2)= 3;
	mpvector t2(3);
	t2(0)= 3;
	t2(1)= 4;
	t2(2)= 5;
	mpvector st = cross_prod(t1,t2);
	flexcout(st);*/
	// split E into parts parrallel and normal to B at each point
    //get v, E and B at time ti, loc xi,yi
	//episode 1
	//apply F = q ( E + v cross B) for each species
	//get a=F/m for each species
	//episode 2
	//use a*dt to get vt+1
	//use a*dt*dt=v*dt+1 to get xt+1
	//repeat from episode 1
}
