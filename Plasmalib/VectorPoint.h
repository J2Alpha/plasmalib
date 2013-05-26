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


/*
 * these are cleaner when not defined inside class body
 * friend defs need to be here or template linking goes wrong
 * because it assumes they are non template friends
 * see: http://www.parashift.com/c%2B%2B-faq-lite/template-friends.html
 * for a pretty good explanation
*/
class VectorPoint;
std::istream& operator >>(std::istream &is,VectorPoint&obj);
std::ostream& operator <<(std::ostream &os,const VectorPoint &obj);

/*
 * VectorPoint is a point that has its operators overloaded to behaves as a vector.
 * the template can take any type, including multi precision types that themselves behaves as an int.
 */
//todo: find out how to force the inverses for * and /, like coerce in ruby
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
		//the completely undocumented little <> template function indicators need to stay because friendship is linker magic, see above!
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
