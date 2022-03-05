#include <iostream>
#include "Density.h"
#include "Energy.h"
#include "Pressure.h"
#include "SoundSpeed2.h"
#include "Velocity.h"
#include "Mesh.h"
#include "PredictorCorrector.h"
#include <fstream> // for file-access
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include "../include/ScalarProperty.h"

//#include <bits/stdc++.h>

using namespace std;

// Initialise physical properties for Sod shock tube
void init2DSod(Mesh &mesh,
			   Density &density,
			   Energy &energy,
			   Pressure &pressure,
			   SoundSpeed2 &ccs2,
               Velocity &nvelocity,
			   double initdt)
{

	//add 2 regions
    double reg1_length [2] = { 50.0, 1.0 };
    double reg2_length [2] = { 50.0, 1.0 };

    double reg1_origins [2] = {  0.0, 0.0 };
    double reg2_origins [2] = { 50.0, 0.0 };

	int reg1_mesh_size [2] = { 50, 1 };
	int reg2_mesh_size [2] = { 50, 1 };


	mesh.addRegion(reg1_mesh_size, reg1_length, reg1_origins, 1);
	mesh.addRegion(reg2_mesh_size, reg2_length, reg2_origins, 2);

    int noElements = mesh.numberElements;
    int noNodes = mesh.numberNodes;

    //initialise physical arrays
    density.init(noElements,0.0);
    energy.init(noElements,0.0);
    pressure.init(noElements,0.0);
	ccs2.init(noElements,0.0);
	nvelocity.init(noNodes,0.0);


	const vector<int> &regionInfo = mesh.getRegionData();
	density.setRegion(regionInfo, 1, 1.0);
	energy.setRegion(regionInfo, 1, 2.5);

	density.setRegion(regionInfo, 2, 0.125);
	energy.setRegion(regionInfo, 2, 2.0);

	pressure.updatePressure(density.getData(), energy.getData());
	ccs2.updateSoundSpeed(energy.getData());


    initdt =  1e-4; //initial timestep


}



/**
 * mesh size specification for each region
 * initial value for physical properties
 *
 */

//initialise physical properties

//start time solver


int main(int argc, char **argv) {

    //Problem specifications
    int nodimensions = 2; //default 2D
    /**
     * mesh type flag can be either:
     * finite element [1]
     * finite difference [2]
     */
    int meshtype = 1; //default finite element
    /**
     * time solver flag can be either:
     * predictor-corrector [1]
     * Runge-Kutta [2]
     */
    int timesolver   = 1;    //default predictor-corrector temporal solver
    int startstep    = 0;
    double initdt    = 1e-4; //initial timestep
    double starttime = 0.0;
    double endtime   = 20.0;

    //Setup physical properties
    Density density;
    Energy energy;
    Pressure pressure;
    SoundSpeed2 ccs2;


    //read in input file
    if (argc > 1) {
        cout << "input deck = " << argv[1] << endl;
    } else {
        cout << "No input file provided. Exiting...";
        return -1;
    }


    Mesh mesh(nodimensions);


    init2DSod(mesh,density,energy,pressure,ccs2,initdt);

    if (timesolver==1) {
        PredictorCorrector solver;
        solver.init(initdt, startstep, starttime, endtime);
        solver.solve(mesh, density, energy, pressure, ccs2);

    }



    pressure.print();
    ccs2.print();

    return 0;
}

