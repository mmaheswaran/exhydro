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

void PredictorCorrector::calcNodalVelocity(Velocity &ndvelocity,
                                           Mesh &mesh,
                                           Pressure &elpressure,
                                           Density &eldensity) {
    /**
            * Calculate acceleration using:
            *        - Forces on nodes
            *          - need nodal area
            *        - Mass at nodes
            *          - need nodal volume
            */
    Force ndforce;
    Acceleration ndaccel;
    Mass ndmass;

    ndforce.init(mesh.numberNodes, mesh.DIMS, 0.0);
    ndmass.init(mesh.numberNodes, 0.0);

    //Calculate area which force is acting (vector) and nodal mass
    for(int e = 0; e < mesh.numberElements; e++) {
        for(int n = 0; n < mesh.noVertices; n++) {
            //get nodal vector area Force = Pressure x Area
            for(int d = 0; d < mesh.DIMS; d++) {
                vector<double> areavector = mesh.calcNodalArea(e,n);
                ndforce.addTo(n, d, areavector[d]*elpressure.get(e));
            }
            double nodalvolume = mesh.calcNodalVolume(e,n);
            ndmass.addTo(n, nodalvolume*eldensity.get(e));
        }
    }

    //Calcuate acceleration
    for(int n = 0; n < mesh.noVertices; n++) {
        vector<double> accel;
        double m = ndmass.get(n);
        for(int d = 0; d < mesh.DIMS; d++) {
            double f = ndforce.get(n,d);
            accel.push_back(f/m);
        }
        ndaccel.add(accel);
    }

}

