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
                               Density &eldensity,
                               Energy &elenergy,
                               Pressure &elpressure,
                               SoundSpeed2 &elccs2,
                               Velocity &ndvelocity,
                               Volume &elvolume,
                               Mass &elmass) {

    double time = starttime;

    while (time < endtime) {

        //Predictor half step
        halfstep(mesh,eldensity,elenergy,elpressure,elccs2,ndvelocity,elvolume,elmass);


        // Calculate nodal velocities
        /**
         * Calculate acceleration using:
         *        - Forces on nodes
         *          - need nodal area
         *        - Mass at nodes
         *          - need nodal volume
         */

        // Calculate timestep

        //Corrector half step


        // Calculate velocity

        // Calculate timestep

        time += dt;

    }

}

void PredictorCorrector::halfstep(Mesh &mesh,
                                  Density &eldensity,
                                  Energy &elenergy,
                                  Pressure &elpressure,
                                  SoundSpeed2 &elccs2,
                                  Velocity &ndvelocity,
                                  Volume &elvolume,
                                  Mass &elmass) {

    // Update new mesh coordinates using velocities and timestep
    for(int d = 0; d < mesh.DIMS; d++) {
        mesh.updateNodePos(ndvelocity, timestep, d);
    }

    // Update element/cell volumes
    elvolume.update(mesh);

    // Update densities
    eldensity.update(elmass, elvolume);

    // Smear shocks
    Pressure shockPressure(elpressure);
    try {
        artvisc.smearShocks(shockPressure);
    } catch (const std::length_error& e) {
        std::cerr << "Error: unable to smear shock" << std::endl;
        return EXIT_FAILURE;
    }
    // Update energy
    elenergy.update(mesh, shockPressure, ndvelocity, elmass, timestep);

    // Update pressure
    elpressure.update(eldensity, elenergy);

    // Update sound speed
    elccs2.update(elenergy);

}

