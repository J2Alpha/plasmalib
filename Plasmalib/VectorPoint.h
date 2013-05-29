/*
 * VectorPoint.h
 *
 *  Created on: 14-mei-2013
 *      Author: admin
 */

#ifndef VECTORPOINT_H_
#define VECTORPOINT_H_

//#include "Point.h"
//rplaces ublas vector cause i hate it
//todo add exceptions to the operators
#include <iostream>

#include "mpdefs.h"
#include "UserIOconditioning.h"


class VectorPoint;
/**@fn operator>>
 * @brief stream ops are cleaner when not defined inside class body
 *
 * see: http://www.parashift.com/c%2B%2B-faq-lite/template-friends.html for a pretty good explanation
 *
 * @param is
 * @param obj
 * @return ref to self
 **/
std::istream& operator >>(std::istream &is,VectorPoint&obj);
/**@fn operator<<
 * @brief stream ops are cleaner when not defined inside class body
 *
 * see: http://www.parashift.com/c%2B%2B-faq-lite/template-friends.html for a pretty good explanation
 * short version: friendship is linker magic
 *
 * @param is
 * @param obj
 * @return ref to self
 **/
std::ostream& operator <<(std::ostream &os,const VectorPoint &obj);

/**@class VectorPoint
 * @brief an appropriately mathematical vector also used
 *
 * @todo find out how to force the inverses for * and /, like coerce in ruby
 */
class VectorPoint//: public Point
{
public:
	 	VectorPoint();
		VectorPoint(mpelement x,mpelement y,mpelement z);//3D
		~VectorPoint();
		std::vector<mpelement> getVector();
		unsigned int size();
		//VectorPoint& operator=(const VectorPoint &rhs);// doesn't have to be overloaded now
		VectorPoint& operator+=(const VectorPoint &rhs);
		VectorPoint& operator-=(const VectorPoint &rhs);
		VectorPoint operator+(const VectorPoint &rhs);
		VectorPoint operator-(const VectorPoint &rhs);
		VectorPoint& operator*=(const mpelement &rhs);
		VectorPoint& operator/=(const mpelement &rhs);
		VectorPoint operator*(const mpelement &rhs);
		VectorPoint operator/(const mpelement &rhs);
		friend std::istream& operator>> (std::istream &is,VectorPoint &obj);
		friend std::ostream& operator<< (std::ostream &os,const VectorPoint &obj);

		mpelement operator[](const unsigned int);
		bool operator==(const VectorPoint &other) const;
		bool operator!=(const VectorPoint &other) const;
		VectorPoint X(VectorPoint other);
		mpelement dot(VectorPoint other);


private:
		unsigned int D;
	protected:
		std::vector<mpelement> coordinate;

};




#endif /* VECTORPOINT_H_ */
