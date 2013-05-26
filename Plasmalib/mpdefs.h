/*
 * mpdefs.h
 *
 *  Created on: Apr 18, 2013
 *      Author: admin
 */

#ifndef MPDEFS_H_
#define MPDEFS_H_

#include <vector>

#include <boost/multiprecision/cpp_dec_float.hpp> //high precision floats
//#include <boost/numeric/ublas/vector.hpp> //linear algebra suite
//#include <boost/numeric/ublas/io.hpp>//to print the linalg stuff

//namespace shorthands
namespace multip = boost::multiprecision;
namespace ublas = boost::numeric::ublas;

//variable sizes TODO: make more mpflexible
typedef  multip::number<multip::cpp_dec_float<100> > mpelement; // change this to change prescision;
//typedef  ublas::vector<mpelement> mpvector;//this crapware fails all the time

//typedef std::vector<mpelement> mpvector;

/*template<class T> T cross_prod(T A, T B)
{
	T r(3);
	if(A.size()==3 && B.size()==3)
	{
		r[0] = A[1]*B[2] - A[2]*B[1];
		r[1] = A[2]*B[0] - A[0]*B[2];
		r[2] = A[0]*B[1] - A[1]*B[0];
		return r;
	}
	//doesn't really physically mean a lot if not 3d, and is usually ambiguously defined. 7D exists unambiguously though.
	else{
		return r;
	}
}*/
//todo repair to be dependent on T and not set as an mpelement
/*template<typename T> mpelement dot_prod(T A, T B)
{
	mpelement r("0");
	if(A.size()==B.size())
	{
		for(unsigned int i=0;i<A.size();i++)
		{
			r += A[i]*B[i];
		}
		return r;
	}
	//if A!=B doesn't exsist TODO: error handling
	else{
		return r;
	}
}*/
#endif /* MPDEFS_H_ */
