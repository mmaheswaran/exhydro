#include <iostream>
<<<<<<< HEAD
#include "PhysicalProperty.h"
#include "Density.h"
#include "Energy.h"
#include "Pressure.h"
#include "SoundSpeed2.h"
#include "Mesh.h"
=======
//#include "PhysicalProperty.h"
//#include "Density.h"
//#include "Energy.h"
//#include "Pressure.h"
//#include "SoundSpeed2.h"
#include "Mesh.h"
#include <fstream> // for file-access
#include <string>
>>>>>>> develop

using namespace std;

// Initialise physical properties for Sod shock tube
<<<<<<< HEAD
void init1DSod(Mesh &mesh,
=======
/*void init1DSod(Mesh &mesh,
>>>>>>> develop
			 Density &density,
			 Energy &energy,
			 Pressure &pressure,
			 SoundSpeed2 &ccs2)
{

	//add 2 regions
	int meshsize [2] = {50,50};
	double problemsize [2]= {50.0, 50.0};
	double origin [2]= {0.0, 50.0};
	mesh.addRegion(meshsize[0], problemsize[0], origin[0], 1);
	mesh.addRegion(meshsize[1], problemsize[1], origin[1], 2);

    int noElements = mesh.numberElements;

    //initialise physical arrays
    density.init(noElements,0.0);
    energy.init(noElements,0.0);
    pressure.init(noElements,0.0);
	ccs2.init(noElements,0.0);

	const vector<int> &regionInfo = mesh.getRegionData();
	density.setRegion(regionInfo, 1, 1.0);
	energy.setRegion(regionInfo, 1, 2.5);

	density.setRegion(regionInfo, 2, 0.125);
	energy.setRegion(regionInfo, 2, 2.0);

	pressure.updatePressure(density.getData(), energy.getData());
	ccs2.updateSoundSpeed(energy.getData());

<<<<<<< HEAD
}

int main(int argc, char **argv) {

	int noDimensions = 2;
	Density density;
	Energy energy;
	Pressure pressure;
	SoundSpeed2 ccs2;
	Mesh mesh(noDimensions);
	//mesh.printNodePos();

	init1DSod(mesh,density,energy,pressure,ccs2);

	pressure.print();
	ccs2.print();

	return 0;
=======
}*/

//read input file to get problem specifications
void readInput(char *inputDeck) {

  ifstream infile(inputDeck); //open the file

  if (infile.is_open() && infile.good()) {
    std::cout << "File echo:\n";
    string line = "";
    while (getline(infile, line)){
      std::cout << line << '\n';
    }

  } else {
    std::cout << "Failed to open file..";
  }


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
  int noDimensions = 2; //default 2D
  /**
   * mesh type flag can be either:
   * finite element [1]
   * finite difference [2]
   */
  int mesh_type = 1; //default finite element
  /**
   * time solver flag can be either:
   * predictor-corrector [1]
   * Runge-Kutta [2]
   */
  int time_solver = 1; //default predictor-corrector temporal solver
  int noRegions = 1;


  //read in input file
  if (argc > 1) {
    std::cout << "input deck = " << argv[1] << endl;
  } else {
    std::cout << "No input file provided. Exiting...";
    return -1;
  }

  readInput(argv[1]);

  //Setup physical properties
  //Density density;
  //Energy energy;
  //Pressure pressure;
  //SoundSpeed2 ccs2;


  //Mesh mesh(20);
  //mesh.printNodePos();


  //init1DSod(mesh,density,energy,pressure,ccs2);

  //pressure.print();
  //ccs2.print();

  return 0;
>>>>>>> develop
}

