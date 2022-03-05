/*
 * Force.h
 *
 * Class to manage the A. Barlow's compatible hydro force array.
 *
 *  Created on: 12 Apr 2021
 *      Author: Mary-Ann Maheswaran
 */
#include "ScalarProperty.h"
#include "Pressure.h"

#ifndef FORCE_H_
#define FORCE_H_

class Force : public VectorProperty {

public:

    Force();
    void update(Pressure &pressure, const vector<double> &area,
            int nvertices, const vector< vector<int> > &el2nodmap);
    void print();

};

Force::Force() {
    name = "Force";
}

/**
 * Updates the force using pressure and area.
 * @param pressure - element centred
 * @param area - nodal area
 * @param el2nodmap - element number to node number map
 */
void Force::update(Pressure &pressure,
        vector<double> &area,
        int nvertices,
        const vector< vector<int> > &el2nodmap,
        int dim) {

    for (int el= 0; el < pressure.size(); el++) {
        for (int v = 0; v < nvertices; v++) {
            int node = el2nodmap[el][v];
            data[node][dim] = pressure.get(el) * area[node];
        }

    }
}



#endif /* FORCE_H_ */
