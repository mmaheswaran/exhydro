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
  void init(double initdt, int initstep, double st, double et);

  const int& getStep() const {return step; }
  void setStep(int newstep);
  virtual void updateStep() = 0;

  const double& getTimeStep() const {return dt; }
  void setTimeStep(int newtimestep);
  virtual void updateTimeStep() = 0;

protected:

  double dt;
  int step;
  double starttime;
  double endtime;

};

void TimeSolver::init(double initdt,
                      int initstep,
                      double st,
                      double et) {

    dt        = initdt;
    step      = initstep;
    starttime = st;
    endtime   = et;

}




#endif /* TIMESOLVER_H_ */
