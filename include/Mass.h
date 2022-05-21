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
	void apply_cut_off(Volume &volume, double densitycut);

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

/**
 * Apply cutoff to mass, using minimum density cutoff.
 * @param volume around mass centres
 * @param densitycut density cut off limit
 */
void Mass::apply_cut_off(Volume &volume, double densitycut) {

    for (int i= 0; i < data.size(); i++) {

        double minmass = densitycut * volume.get(i);
        data[i] = data[i] > minmass ? data[i]  : 0.0;
    }
}


#endif /* MASS_H_ */
