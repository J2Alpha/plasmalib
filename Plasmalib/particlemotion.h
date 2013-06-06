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
/**@fn Euler_accelerationstep
 *
 * @brief calculates the acceleration of a particle
 *
 * first step in a forward Euler calculation of the motion of a particle under applied fields using
 *
 * @param sp particle object
 * @param Efield field object describing electric field
 * @param Bfield field object describing magnetic field
 * @param Vi current velocity of particle
 * @param Xi current position of particle
 * @return new acceleration vector
 **/
VectorPoint Euler_accelerationstep(Species sp, Field Efield, Field Bfield, VectorPoint Vi, VectorPoint Xi);
/**@fn Euler_velocityste
 *
 * @brief second step calculate velocity based on acceleration
 *
 * @param A current acceleration Ai
 * @param V previous velocity Vi-1
 * @param timestep stepsize dt
 * @return Vi=Ai*dt+Vi-1
 **/
VectorPoint Euler_velocitystep(VectorPoint A, mpelement timestep);
/**@fn Euler_distancestep
 *
 * @brief third calculation step
 *
 * @param V current velocity Vi
 * @param X previous velocity Xi-1
 * @param timestep dt
 * @return Xi=Vi*dt+Xi-1
 **/
VectorPoint Euler_distancestep(VectorPoint V, mpelement timestep);
/**@fn Euler_OneStep
 *
 * @brief one whole timestep
 *
 * completes the three steps to calculate the whole motion for one timestep using forward euler
 *
 * @param sp chemical element object
 * @param Efield field object describing electric field
 * @param Bfield field object describing magnetic field
 * @param V0 current velocity of particle
 * @param X0 current velocity of particle
 * @param timestep stepsize
 * @return one line containing the motion
 **/
std::vector<VectorPoint> Euler_OneStep(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep);
/**@fn Euler_OneStep_SplitField
 * @brief same as @fn Euler_OneStep but splits the E field into perpendicular and parrallel parts first
 *
 * splits the fields up according to Jahn then completes the three steps to calculate the whole motion
 * for one timestep for each subfield using forward euler
 *
 * E=E parallel to B + E perpendicular to B
 * V=V parallel to EB plane + V perpendicular to EB plane
 *
 * @param sp chemical element object
 * @param Efield field object describing electric field
 * @param Bfield field object describing magnetic field
 * @param V0 current velocity of particle
 * @param X0 current velocity of particle
 * @param timestep stepsize
 * @return one line containing the motion caused by each sub field
 **/
std::vector< std::vector<VectorPoint > > Euler_OneStep_SplitField(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep);
/**@fn Euler_AllSteps
 *
 * @brief repeats Euler_OneStep for a set amount of steps
 *
 * @param sp chemical element object
 * @param Efield field object describing electric field
 * @param Bfield field object describing magnetic field
 * @param V0 current velocity of particle
 * @param X0 current velocity of particle
 * @param timestep stepsize
 * @param nr_of_steps amount of steps
 * @return
 **/
std::vector<std::vector<VectorPoint > > Euler_AllSteps(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep,unsigned int nr_of_steps);
/**@fn Euler_AllSteps
 *
 * @brief same as \fn Euler_AllSteps but for \fn Euler_OneStep_SplitField
 *
 * @param sp chemical element object
 * @param Efield field object describing electric field
 * @param Bfield field object describing magnetic field
 * @param V0 current velocity of particle
 * @param X0 current velocity of particle
 * @param timestep stepsize
 * @param nr_of_steps amount of steps
 * @return
 **/
std::vector<std::vector<std::vector<VectorPoint > > > Euler_AllSteps_SplitField(Species sp, Field Efield, Field Bfield, VectorPoint V0, VectorPoint X0, mpelement timestep,int nr_of_steps);
/**@brief same as \fn Euler_AllSteps but for \fn a database in stead of a set of files
 *
 * @param testgas
 * @param dbg
 * @param maindb
 * @return
 */
int Euler_AllSteps_DB(GAS & testgas, ACCELERATOR & dbg, Sqlitedb & maindb);
//TODO RK
#endif /* PARTICLEMOTION_H_ */
