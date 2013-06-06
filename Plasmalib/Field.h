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

/**@struct FIELD
 * @brief contains field properties
 *
 * @todo should be improved to interpolate or calculate a better field instead of using constants,
 * this should be done carefully to avoid increasing sim time since the @fn at(x) is used 2 times per time step
 *
 **/
class Field {
public:
	Field();
	Field(mpelement x,mpelement y,mpelement z);
	Field(VectorPoint v);
	virtual ~Field();
	VectorPoint at(VectorPoint Xi);
private:
	VectorPoint value;
};

#endif /* FIELD_H_ */
