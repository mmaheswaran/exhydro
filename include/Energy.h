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
#include "Pressure.h"

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

    void update(Pressure &pressure,
            Mass &mass,
            Velocity &velocity,
            double timestep);

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
    for (int el= 0; el < data.size(); el++) {
        for (int v = 0; v < nvertices; v++) {

            int node = el2nodmap[el][v];
            double m = max(mass.get(el), masscut);

            data[el] += -(force.get(node,dim) * velocity.get(node,dim)) * timestep / m;
        }
    }

}

/**
 * Updates energy using standard PdV method
 */
void Energy::update(Mesh &mesh,
        Pressure &pressure,
        Velocity &velocity,
        Mass &mass,
        double timestep) {

    // find divergence of velocity field
    divvel = mesh.calcDiv(velocity);

    for (int el= 0; el < data.size(); el++) {
        assert(mass.get(el) > 0 && "ERROR: mass 0 or negative.");
        data[el] += 0.5*timestep * pressure.get(el) * divvel[el]/mass.get(el);

    }

}



#endif /* PHYSICS_ENERGY_H_ */
