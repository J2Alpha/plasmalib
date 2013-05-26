/*
 * Field.h
 *
 *  Created on: 12-mei-2013
 *      Author: admin
 */

#ifndef FIELD_H_
#define FIELD_H_

#include "VectorPoint.h"
#include "mpdefs.h"


class Field {
public:
	Field();
	Field(VectorPoint v);
	virtual ~Field();
	VectorPoint at(VectorPoint Xi);
private:
	VectorPoint value;
};

#endif /* FIELD_H_ */
