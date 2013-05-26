/*
 * particlemotion.cpp
 *
 *  Created on: 13-mei-2013
 *      Author: admin
 */

#include "particlemotion.h"

//euler method: the first step: determine acceleration
VectorPoint Euler_accelerationstep(Species sp, Field Efield, Field Bfield, VectorPoint Vi, VectorPoint Xi)
{
/*       10        20        30        40        50        60        70
12345678901234567890123456789012345678901234567890123456789012345678901234*/
	VectorPoint A=( ( Efield.at(Xi) ) + Vi.X( Bfield.at(Xi) ) )/sp.Mass*sp.Charge;
	/*flexcout("",1);
	flexcout("in accstep :",1);
	flexcout("charge,is :");flexcout(sp.Charge,1);
	flexcout("mass,is :");flexcout(sp.Mass,1);
	flexcout("X,is :");flexcout(Xi,1);
	flexcout("Bf,is :");flexcout(Bfield.at(Xi),1);
	flexcout("Ef,is :");flexcout(Efield.at(Xi),1);
	flexcout("V,is :");flexcout(Vi,1);
	flexcout("A,is :");flexcout(A,1);
	flexcout("VxB is :");flexcout((Vi.X(Bfield.at(Xi))),1);
	flexcout("total F is :");flexcout((Efield.at(Xi)*sp.Charge),1);
	flexcout("total A is :");flexcout((Efield.at(Xi)/sp.Mass*sp.Charge),1);
	flexcout("",1);*/
	return A;
}
//euler method: second step: determine velocity
VectorPoint Euler_velocitystep(VectorPoint A, VectorPoint V, mpelement timestep)
{
	return V+= A*timestep;
}
//euler method: third step: determine position from velocity
VectorPoint Euler_distancestep(VectorPoint V, VectorPoint X, mpelement timestep)
{
	return X+= V*timestep;
}
//euler method: all steps once: determine one timestep
std::vector<VectorPoint> Euler_OneStep(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep){
	std::vector<VectorPoint > one;
	one.push_back(Euler_accelerationstep(sp,Efield,Bfield,V0, X0));

	one.push_back(Euler_velocitystep(one[0], V0, timestep));

	one.push_back(Euler_distancestep(one[1], X0, timestep));

	return one;
}
//euler method: all steps once: split vectors: determine one timestep
//computationally more intensive method but allows viewing the influence of the different fields better
std::vector< std::vector<VectorPoint > > Euler_OneStep_SplitField(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep)
{
	//make necessary vectors see Jahn p71
	VectorPoint Vector0(0,0,0);
	Field Field0= Field(Vector0);
	VectorPoint B_here = Bfield.at(X0);
	VectorPoint B1_here = Bfield.at(X0);
	VectorPoint B2_here = Bfield.at(X0);
	VectorPoint B3_here = Bfield.at(X0);
	VectorPoint E_here = Efield.at(X0);
	VectorPoint B_t = B_here*B1_here[1];
	VectorPoint E_para = (B_here*(
			E_here.dot(B1_here)
			/(B2_here.dot(B3_here))));
	VectorPoint E_perp = E_here-E_para;
	VectorPoint V_wavy_dir = B_here.X(E_perp);
	VectorPoint V_wavy = (V_wavy_dir*(V0.dot(V_wavy_dir)/V_wavy_dir.dot(V_wavy_dir)));
	VectorPoint V_acce = V0-V_wavy;
	//do the thing for each component set
	std::vector<std::vector<VectorPoint > > splitone;
	splitone.push_back(Euler_OneStep(sp,E_para,Field0,X0,Vector0,timestep));
	splitone.push_back(Euler_OneStep(sp,E_perp,Field0,X0,Vector0,timestep));
	splitone.push_back(Euler_OneStep(sp,Field0,Bfield,X0,V_acce,timestep));
	splitone.push_back(Euler_OneStep(sp,Field0,Bfield,X0,V_wavy,timestep));
	return splitone;
}
//euler method: determine a series of timesteps
std::vector<std::vector<VectorPoint > > Euler_AllSteps(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep,unsigned int nr_of_steps)
{
	std::vector<std::vector<VectorPoint > > many;
	//many.resize(nr_of_steps);//don't fucks up iterator
	//first intiating
	many.push_back(Euler_OneStep(sp, Efield, Bfield, V0, X0, timestep));
	//int j=0;//then in loop
	for(unsigned int i=1;i<=nr_of_steps;i++)
	{
		//flexcout(i);
		many.push_back(Euler_OneStep(sp, Efield, Bfield, many[i-1][1], many[i-1][2], timestep));
		/*std::cout.seekp(-1, std::ios_base::cur);//todo: again, whats up with ios and cout
		if(j==0){
			flexcout("-");
			i=1;
		}
		if(j==1){
			flexcout("/");
			i=2;
		}
		if(j==2){
			flexcout("|");
			i=3;
		}
		if(j==3){
			flexcout("\\");
			i=0;
		}
		std::cout.seekp(-1, std::ios_base::cur);*/
	}
	return many;
}
//euler method: determine a series of steps and split the fields as in physics of E-prop
//computationally more intensive method but allows viewing the influence of the different fields better
std::vector<std::vector<std::vector<VectorPoint > > > Euler_AllSteps_SplitField(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep,int nr_of_steps)
{
	std::vector<std::vector<std::vector<VectorPoint > > > many_in_pieces;
	many_in_pieces.resize(nr_of_steps);
	for(int i=0;i<=nr_of_steps;i++)
	{
		many_in_pieces.push_back(Euler_OneStep_SplitField(sp, Efield, Bfield, V0, X0, timestep));
	}
	return many_in_pieces;
}

