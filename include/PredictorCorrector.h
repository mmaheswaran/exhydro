/*
 * PredictorCorrector.h
 *
 * Implements a predictor-corrector time solve and an artificial viscosity
 * for shock management.
 *
 *  Created on: 3 Feb 2022
 *      Author: maryann
 */
#include <stdlib.h>
#include "TimeSolver.h"
#include "Mesh.h"
#include "Density.h"
#include "Energy.h"
#include "Pressure.h"
#include "ScalarProperty.h"
#include "SoundSpeed2.h"
#include "Velocity.h"
#include "Volume.h"
#include "MonotonicScalar.h"

#ifndef PREDICTORCORRECTOR_H_
#define PREDICTORCORRECTOR_H_


class PredictorCorrector : public TimeSolver {

public:

  void solve(Mesh &mesh,
             Density &eldensity,
             Energy &elenergy,
             Pressure &elpressure,
             SoundSpeed2 &elccs2,
             Velocity &ndvelocity,
             Volume &elvolume,
             Mass &elmass);



private:

  void halfstep(Mesh &mesh,
                Density &density,
                Energy &energy,
                Pressure &pressure,
                SoundSpeed2 &ccs2,
                Velocity &velocity);

  void update_timestep(Mesh &mesh,
                       SoundSpeed2 &ccs2,
                       Velocity &velocity);

  void calc_nodal_velocity(Velocity &ndvelocity,
                           Mesh &mesh,
                           Pressure &elpressure,
                           Density &eldensity);

  MonotonicScalar artvisc;

  double safetyfactor; // for timestep growth stability



};




#endif /* PREDICTORCORRECTOR_H_ */
