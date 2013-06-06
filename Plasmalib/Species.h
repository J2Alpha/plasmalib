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
/**@struct SPECIES
 * @brief contains single species properties
 *
 *  @brief constructed when needed by gas when loading gaslists from file, should not be used by itself
 *
 */
typedef struct Species {
	std::string name;			/**< chemcal shorthand ex: H  **/
	mpelement Charge;			/**< charge in elementary charge [e]**/
	mpelement Mass;				/**<mass in unified atomic mass unit (Dalton) [u] ([Da])**/
	unsigned int Concentration;	/**<part gas that is this constituent min-max 0-100% [%]**/
}SPECIES;

#endif /* SPECIES_H_ */
