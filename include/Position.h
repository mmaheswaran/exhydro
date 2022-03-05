/*
 * Position.h
 *
 *  Created on: 5 Mar 2022
 *      Author: maryann
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "Velocity.h"

class Position : public VectorProperty {

public:

    Position();
    void update(Velocity &velocity, double timestep, int dim);

};

Position::Position() {
    name = "Position";
}

/**
 * Update position using velocities.
 * @param velocity
 * @param timestep
 */
void Position::update(Velocity &velocity, double timestep, int dim) {

    for (int i= 0; i < data.size(); i++) {

        data[i][dim] += velocity.get(i,dim) * timestep;

    }

}



#endif /* POSITION_H_ */
