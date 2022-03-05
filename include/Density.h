/*
 * Density.h
 *
 * Class to manage the density arrays in the simulation.
 *
 *  Created on: 30 Mar 2021
 *      Author: Mary-Ann Maheswaran
 */

#include "ScalarProperty.h"
#include "Mass.h"
#include "Volume.h"

#ifndef DENSITY_H_
#define DENSITY_H_

class Density : public ScalarProperty {

public:

    Density();
	void update(Mass &mass, Volume &volume);
	void print();

};

Density::Density() {
    name = "Density";
}

/**
 * Updates the masses.
 * @param mass
 * @param volume
 */
void Density::update(Mass &mass, Volume &volume) {

	for (int i= 0; i < data.size(); i++) {
		data[i] = mass.get(i) / volume.get(i);
	}
}



#endif /* DENSITY_H_ */
