/*
 * PredictorCorrector.cpp
 *
 *
 *
 *  Created on: 5 Feb 2022
 *      Author: maryann
 */

#include "PredictorCorrector.h"
#include <math.h>

void PredictorCorrector::solve(Mesh &mesh,
                               Density &density,
                               Energy &energy,
                               Pressure &pressure,
                               SoundSpeed2 &ccs2) {

    double time = starttime;

    while (time < endtime) {

        //Predictor half step
        halfstep(mesh,density,energy,pressure,ccs2,velocity,dt/2);

        // Calculate velocity

        // Calculate timestep

        //Corrector half step


        // Calculate velocity

        // Calculate timestep

        time += dt;

    }

}

void PredictorCorrector::halfstep(Mesh &mesh,
                                  Density &density,
                                  Energy &energy,
                                  Pressure &pressure,
                                  SoundSpeed2 &ccs2,
                                  Velocity &velocity,
                                  double timestep) {

    // Calculate new mesh coordinates using velocities and timestep


    // Calculate element/cell volumes

    // Calculate densities

    // Calculate energy

    // Calculate pressure

    // Calculate sound speed



}

