/*
 * TimeSolver.h
 *
 *  Created on: 3 Feb 2022
 *      Author: maryann
 */

#ifndef TIMESOLVER_H_
#define TIMESOLVER_H_

class TimeSolver {
public:

  virtual ~TimeSolver() {}

  virtual void step(double dt) = 0;

  double getStep();
  double getTime();

};




#endif /* TIMESOLVER_H_ */
