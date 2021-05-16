#include <iostream>
#include "PhysicalProperty.h"
#include "Density.h"
#include "Energy.h"
#include "Pressure.h"
#include "SoundSpeed2.h"
#include "Mesh.h"

using namespace std;

void init1DSod(Mesh &mesh,
			 Density &density,
			 Energy &energy,
			 Pressure &pressure,
			 SoundSpeed2 &ccs2);


int main(int argc, char **argv) {

	Density density;
	Energy energy;
	Pressure pressure;
	SoundSpeed2 ccs2;
	Mesh mesh(101,100,1);
	//mesh.printNodePos();

	init1DSod(mesh,density,energy,pressure,ccs2);

	pressure.print();
	ccs2.print();

	return 0;
}

// Initialise physical properties for Sod shock tube
void init1DSod(Mesh &mesh,
			 Density &density,
			 Energy &energy,
			 Pressure &pressure,
			 SoundSpeed2 &ccs2)
{
	double tubeLength = 100.0;
	int nel = mesh.numberElements;
	int nnod = mesh.numberNodes;
	density.init(nel, 1.0);
	energy.init(nel, 2.5);

	pressure.init(nel,0.0);
	ccs2.init(nel,0.0);

	double dx = tubeLength / nel;
	int el = 0;
	for(int n=0; n < nnod-1; n++) {
		double xpos1 = n*dx;
		double xpos2 = (n+1)*dx;
		double elx = (xpos1 + xpos2)*0.5;
		mesh.nodePositions(n,0,xpos1);
		if(elx >= 50.0) {
			//Region 2
			density.set(el, 0.125);
			energy.set(el,2.0);
			mesh.region[el] = 1;
		}
		el++;
	}

	pressure.updatePressure(density.getData(), energy.getData());
	ccs2.updateSoundSpeed(energy.getData());

}
