/*
 * particlemotion.h
 *
 *  Created on: 10-mei-2013
 *      Author: admin
 */

#ifndef PARTICLEMOTION_H_
#define PARTICLEMOTION_H_

#include <vector>

#include "mpdefs.h"
#include "Field.h"
#include "Species.h"
#include "VectorPoint.h"

#include "UserIOConditioning.h"

//EULER

VectorPoint Euler_accelerationstep(Species sp, Field Efield, Field Bfield, VectorPoint Vi, VectorPoint Xi);
VectorPoint Euler_velocitystep(VectorPoint A, mpelement timestep);
VectorPoint Euler_distancestep(VectorPoint V, mpelement timestep);

std::vector<VectorPoint> Euler_OneStep(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep);
std::vector< std::vector<VectorPoint > > Euler_OneStep_SplitField(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep);

std::vector<std::vector<VectorPoint > > Euler_AllSteps(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep,unsigned int nr_of_steps);
std::vector<std::vector<std::vector<VectorPoint > > > Euler_AllSteps_SplitField(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep,int nr_of_steps);

//TODO RK
#endif /* PARTICLEMOTION_H_ */
