/*
 * Coordinate.h
 *
 *  Created on: 12-mei-2013
 *      Author: admin
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "mpdefs.h"


/**@class generalized point class
 * @brief original parent class for vectorpoint which was split off because of compiler issues
 */
template<typename T>
class Point{
public:
	Point(T x);//1D
	Point(T x,T y);//2D
	Point(T x,T y,T z);//3D
	virtual ~Point();
private:
	unsigned int D;
	std::vector<T> coordinate;
};
//storage element replaces ublas vector because terrible crap happens when Ublas is used for actual computation

#endif /* COORDINATE_H_ */
