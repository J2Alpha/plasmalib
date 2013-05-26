/*
 * constants.h
 *  //contains all constants
 *  Created on: Apr 18, 2013
 *      Author: admin
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <boost/math/constants/constants.hpp>
#include <String>
#include "mpdefs.h"

namespace bconst = boost::math::constants;
//what a hack to get accurate pi's
//tdo eliminate this hack, pimaster
//done but leaving the template here for the future( not used = not compiled for templates, right?)
template <class T>
T pimaker(T)
{
   return boost::math::constants::pi<T>();
};
//mpelement pi=(bconst::pi<mpelement>());//gives unfathomably not-funny, like impossible to solve, errors

const mpelement pi("3.14159265358979323846264338327950288419716939937510");
const mpelement g0("9.81");//gravity [m/s^2]
const mpelement mu0=((mpelement)("0.0000004"))*pi;//magnetic field constant, still a hack but alas
const mpelement e("1.602E-19");//elementary charge, Coulomb
const mpelement u("1.661E-27");//elementary mass, Dalton [Da]

#endif /* CONSTANTS_H_ */
