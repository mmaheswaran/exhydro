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
#include <cassert>

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
        calc_nodal_velocity(ndvelocity,mesh,elpressure,eldensity);


        // Calculate timestep - CFL condition

        //Corrector half step


        // Calculate velocity

        // Calculate timestep

        time += dt;

    }

}

/**
 * Half-step in time solver
 */
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
        mesh.update_node_pos(ndvelocity, dt/2, d);
    }

    // Update element/cell volumes
    elvolume.update(mesh);

    // Update densities
    eldensity.update(elmass, elvolume);

    // Smear shocks
    Pressure shockPressure(elpressure);
    try {
        artvisc.dampen_shocks(shockPressure);
    } catch (const std::length_error& e) {
        std::cerr << "Error: unable to smear shock" << std::endl;
        return EXIT_FAILURE;
    }
    // Update energy
    elenergy.update(mesh, shockPressure, ndvelocity, elmass, dt/2);

    // Update pressure
    elpressure.update(eldensity, elenergy);

    // Update sound speed
    elccs2.update(elenergy);

}

/**
 * Calculate nodal velocities
 * @ndvelocity nodal velocity output
 * @mesh
 * @elpressure element-centred pressure
 * @dt timestep
 */
void PredictorCorrector::calc_nodal_velocity(Velocity &ndvelocity,
                                           Mesh &mesh,
                                           Pressure &elpressure,
                                           Density &eldensity) {
    /**
     * Calculate acceleration using:
     * - Forces on nodes
     *  - need nodal area
     * - Mass at nodes
     *  - need nodal volume
     */
    Force ndforce;
    Acceleration ndaccel;
    Mass ndmass;
    Volume ndvolume;

    double densitycut=1.0e-6;

    ndforce.init(mesh.numberNodes, mesh.DIMS, 0.0);
    ndmass.init(mesh.numberNodes, 0.0);


    //Calculate nodal force
    //Calculate nodal mass
    for(int e = 0; e < mesh.numberElements; e++) {
        for(int n = 0; n < mesh.noVertices; n++) {
            //get nodal vector area (Force = Pressure x Area)
            for(int d = 0; d < mesh.DIMS; d++) {
                vector<double> areavector = mesh.calc_nodal_area(e,n);
                ndforce.addto(n, d, areavector[d]*elpressure.get(e));
            }
            double volume = mesh.calc_nodal_volume(e,n);
            ndvolume.add(volume);
            ndmass.addto(n, volume*eldensity.get(e));
        }
    }

    //update nodal acceleration
    ndmass.apply_cut_off(ndvolume, densitycut);
    ndaccel.update(ndforce, ndmass);

    //update nodal velocity
    ndvelocity.update(ndaccel, dt/2, mesh.DIMS);

}

/**
 * Update timestep using Courant-Friendrichs-Lewy (CFL) condition
 */
void PredictorCorrector::update_timestep(Mesh &mesh,
                                         SoundSpeed2 &elccs2,
                                         Velocity &ndvelocity,
                                         Density &density){
    //update Q
    artvisc.calculate(mesh,ndvelocity,elccs2,density);

    //calculate sound speed with artificial viscosity correction
    SoundSpeed2 qcorr_ccs2 = elccs2;
    artvisc.correctSoundSpeed2(qcorr_ccs2, density);

    double mintimestep = minimum_time(mesh, elccs2);

    //Find new timestep using CFL condition
    dt = safetyfactor*mintimestep;

}

/**
 * Find minimum length along cell, which is approximated to be square root
 * of cell with minimum area.  Divide this value by sound speed to estimate
 * minimum timestep.  Approximate minimum length using the square
 * root of the element area
 */
double minimum_time(Mesh &mesh, SoundSpeed2 &elccs2) {

    double minlength = 1e6; //arbitrarily large number
    double mintime = 0.0;
    for(int e = 0; e < mesh.numberElements; e++) {
        double vol = mesh.get_volume(e);
        minlength = vol < minlength ? vol : minlength;
        mintime = minlength/elccs2.get(e);
    }
    assert(mintime > 0 && "ERROR: Minimum time step less than 0.");

    return sqrt(mintime);

}

