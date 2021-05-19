#include <iostream>
#include "PhysicalProperty.h"
#include "Density.h"
#include "Energy.h"
#include "Pressure.h"
#include "SoundSpeed2.h"
#include "Mesh.h"

using namespace std;

// Initialise physical properties for Sod shock tube
void init1DSod(Mesh &mesh,
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
}

