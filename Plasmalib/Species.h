/*
 * Species.h
 *
 *  Created on: Apr 18, 2013
 *      Author: admin
 */

#ifndef SPECIES_H_
#define SPECIES_H_

#include "mpdefs.h"
/*
struct SpecieProperties{

};
*/

typedef struct Species {
	std::string name;
	mpelement Charge;//charge in elementary charge [e]
	mpelement Mass;//mass in unified atomic mass unit (Dalton) [u] ([Da])
	unsigned int Concentration;//part gas that is this constituent min-max 0-100% [%]
}SPECIES;

#endif /* SPECIES_H_ */
