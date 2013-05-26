/*
 * Field.cpp
 *
 *  Created on: 12-mei-2013
 *      Author: admin
 */

#include "Field.h"

Field::Field(){
	value=VectorPoint(mpelement("0"),mpelement("0"),mpelement("0"));
}

Field::Field(VectorPoint v):value(v) {
}

Field::~Field() {
	// TODO Auto-generated destructor stub
}
//TODO: nonhomogeneous fields
VectorPoint Field::at(VectorPoint Xi){
 return value;
}
