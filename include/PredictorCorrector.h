/*
 * PredictorCorrector.h
 *
 *  Created on: 3 Feb 2022
 *      Author: maryann
 */

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
             Density &density,
             Energy &energy,
             Pressure &pressure,
             Velocity &velocity,
             SoundSpeed2 &ccs2);

  void halfstep(Mesh &mesh,
                Density &density,
                Energy &energy,
                Pressure &pressure,
                SoundSpeed2 &ccs2,
                Velocity &velocity,
                double timestep);
private:

  MonotonicScalar artvisc;



};




#endif /* PREDICTORCORRECTOR_H_ */
