/*
 * Mass.h
 *
 * Class to manage the mass arrays in the simulation.
 *
 *  Created on: 24 Mar 2021
 *      Author: Mary-Ann Maheswaran
 */
#include "ScalarProperty.h"
#include "Density.h"
#include "Volume.h"

#ifndef MASS_H_
#define MASS_H_

class Mass : public ScalarProperty {

public:

    Mass();
	void update(Density &density, Volume &volume);
	void print();

};

Mass::Mass() {
    name = "Mass";
}

/**
 * Updates the masses.
 * @param density
 * @param volume
 */
void Mass::update(Density &density, Volume &volume) {

	for (int i= 0; i < data.size(); i++) {
		data[i] = density.get(i) * volume.get(i);
	}
}



#endif /* MASS_H_ */
