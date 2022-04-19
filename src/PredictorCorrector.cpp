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
                               SoundSpeed2 &ccs2,
                               Velocity &velocity,
                               Volume &volume,
                               Mass &mass) {

    double time = starttime;

    while (time < endtime) {

        //Predictor half step
        halfstep(mesh,density,energy,pressure,ccs2,velocity,volume,mass,artvisc,dt/2);

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
                                  Volume &volume,
                                  Mass &mass,
                                  MonotonicScalar artvisc,
                                  double timestep) {

    // Calculate new mesh coordinates using velocities and timestep
    for(int d = 0; d < mesh.DIMS; d++) {
        mesh.updateNodePos(velocity, timestep, d);
    }

    // Calculate element/cell volumes
    volume.update(mesh);

    // Calculate densities
    density.update(mass, volume);

    // Calculate energy
    energy.update(mesh, pressure, artvisc, velocity, mass, timestep);

    // Calculate pressure
    pressure.update(density, energy);

    // Calculate sound speed
    ccs2.update(energy);



}

