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

  void set_timestep(int newtimestep);
  void set_step(int newstep);

  const int& get_step() const {return step; }
  const double& get_timestep() const {return dt; }

  virtual void update_step() = 0;
  virtual void update_timestep() = 0;

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
