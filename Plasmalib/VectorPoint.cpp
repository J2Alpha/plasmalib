/*
 * VectorPoint.cpp
 *
 *  Created on: 14-mei-2013
 *      Author: admin
 */

#include "VectorPoint.h"

VectorPoint::VectorPoint()
{
	coordinate.resize(3);	//3D
	coordinate[0]=0;
	coordinate[1]=0;
	coordinate[2]=0;
	D=3;
}
VectorPoint::VectorPoint(mpelement x,mpelement y,mpelement z)
{
	coordinate.resize(3);	//3D
	coordinate[0]=x;
	coordinate[1]=y;
	coordinate[2]=z;
	D=3;
}
VectorPoint::~VectorPoint() {
	coordinate.clear();
}
std::vector<mpelement> VectorPoint::getVector(){
	return coordinate;
}
unsigned int VectorPoint::size(){
	return D;
}
//copy is'nt needed now because we dont have resources that suffer from shallow copy behaviour
/*VectorPoint& VectorPoint::operator=(const VectorPoint &rhs) {

    // Only do assignment if RHS is a different object from this.
    if (this != &rhs) {
      return VectorPoint(coordinate[0],coordinate[1],coordinate[2]);
    }

    return *this;
  }*/
VectorPoint& VectorPoint::operator+=(const VectorPoint &rhs){
	if (this != &rhs) {
	std::vector<mpelement> A = rhs.coordinate;
	coordinate[0]+=A[0];coordinate[1]+=A[1];coordinate[2]+=A[2];
	}
	else {
		coordinate[0]*=2;coordinate[1]*=2;coordinate[2]*=2;
	}
	return *this;
}
VectorPoint& VectorPoint::operator-=(const VectorPoint &rhs){
	if (this != &rhs) {
	std::vector<mpelement> A = rhs.coordinate;
	coordinate[0]-=A[0];coordinate[1]-=A[1];coordinate[2]-=A[2];
	}
	else {
		coordinate[0]=0;coordinate[1]=0;coordinate[2]=0;
	}
	return *this;
}
VectorPoint VectorPoint::operator+(const VectorPoint &other){
	VectorPoint result = *this;     // copy
	result += other;            //reuse += to add to copy
	return result;
}
VectorPoint VectorPoint::operator-(const VectorPoint &other){
	VectorPoint result = *this; //copy
	result -= other;
	return result;
}
VectorPoint& VectorPoint::operator*=(const mpelement &rhs){
	coordinate[0]*=rhs;coordinate[1]*=rhs;coordinate[2]*=rhs;
	return *this;
}
VectorPoint& VectorPoint::operator/=(const mpelement &rhs){
	coordinate[0]/=rhs;coordinate[1]/=rhs;coordinate[2]/=rhs;
	return *this;
}
VectorPoint VectorPoint::operator*(const mpelement &other){
	VectorPoint result = *this; //copy
	result *= other;
	return result;
}
VectorPoint VectorPoint::operator/(const mpelement &other){
	VectorPoint result = *this; //copy
	result /= other;
	return result;
}
mpelement VectorPoint::operator[](unsigned int index){
    return coordinate[index];
 }
bool VectorPoint::operator==(const VectorPoint &other) const
{
	std::vector<mpelement> A = other.coordinate;
	if(coordinate[0]==A[0] && coordinate[1]==A[1] &&coordinate[2]==A[2])return true;
	return false;
}
bool VectorPoint::operator!=(const VectorPoint &other) const
{
    return !(*this == other);
}
VectorPoint VectorPoint::X(VectorPoint other)
{

	if(other.size()==3 && this->size()==3)
	{
	    mpelement X = coordinate[1]*other[2] - coordinate[2]*other[1];
	    mpelement Y = coordinate[2]*other[0] - coordinate[0]*other[2];
	    mpelement Z = coordinate[0]*other[1] - coordinate[1]*other[0];
		//flexcout(r);
	    VectorPoint r(X,Y,Z);
	    return r;

	}
	//doesn't really physically mean a lot if not 3d, and is usually ambiguously defined. 7D exists unambiguously though.
	else{
		VectorPoint r(0,0,0);
		return r;
	}
}
mpelement VectorPoint::dot(VectorPoint other){
	mpelement r("0");
	if(this->size()==other.size())
	{
		for(unsigned int i=0;i<this->size();i++)
		{
			r += coordinate[i]*other[i];
		}
		return r;
	}
	//if A!=B doesn't exsist TODO: error handling
	else
	{
		return r;
	}
}

std::istream& operator>> (std::istream &is,VectorPoint &obj){
	//todo: not supported
	return is;
}
std::ostream& operator<< (std::ostream &os,const VectorPoint &obj){
	os<<"["<<obj.D<<"]:[";
		for(unsigned int i=0;i<(obj.D - 1);i++)
		{
			os<<obj.coordinate[i]<<", ";
		}
		os<<obj.coordinate[obj.D-1]<<" "<<"]";
	return os;
}

