/*
 * Energy.h
 *
 *  Created on: 13 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */

#include "ScalarProperty.h"
#include "Force.h"
#include "Velocity.h"
#include "Mass.h"

#ifndef PHYSICS_ENERGY_H_
#define PHYSICS_ENERGY_H_

class Energy : public ScalarProperty {

public:

    Energy();
	void update(Force &force,
				Velocity &velocity,
				Mass &mass,
			    double masscut,
				double timestep,
			    int nvertices,
			    int dim,
				vector< vector<int> > &el2nodmap);
	void print();

};

Energy::Energy() {
    name  = "Energy";
}

/**
 * Updates the energy using compatible hydro scheme.
 * @param force - node centred
 * @param velocity - node centred
 * @param mass - element centred
 * @param masscut - mass cutoff, avoid divide by zero
 * @param timestep
 * @param nvertices - number of vertices in an element
 * @param el2nodmap - map element number to node number
 */
void Energy::update(Force &force,
                    Velocity &velocity,
                    Mass &mass,
                    double masscut,
                    double timestep,
                    int nvertices,
                    int dim,
                    vector< vector<int> > &el2nodmap)
{
	for (int el= 0; el < mass.size(); el++) {
		for (int v = 0; v < nvertices; v++) {

			int node = el2nodmap[el][v];
			double m = max(mass.get(el), masscut);

			data[el] += -(force.get(node,dim) * velocity.get(node,dim)) * timestep / m;
		}
	}

}

#endif /* PHYSICS_ENERGY_H_ */
