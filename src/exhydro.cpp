#include <iostream>
#include "PhysicalProperty.h"
#include "Density.h"
#include "Energy.h"
#include "Pressure.h"
#include "SoundSpeed2.h"
#include "Mesh.h"
#include <fstream> // for file-access
#include <string>
#include <sstream>
#include <queue>
//#include <bits/stdc++.h>

using namespace std;

// Initialise physical properties for Sod shock tube
/*void init1DSod(Mesh &mesh,
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
}*/

/**
 * Get settings in input deck, using a keyword.
 * @param infile input deck
 * @param keyword
 * @return
 */
queue<string> getsettings(ifstream &infile, string keyword) {

    infile.clear();
    infile.seekg(0);
    queue<string> settings;

    string line, word;

    while (getline(infile,line)) {

        istringstream iss{line};

        size_t found = line.find(keyword);
        if (found != string::npos) {
            iss >> word;
            while (iss >> word) {
              word.erase(std::remove(word.begin(), word.end(), ','), word.end());
              settings.push(word);
            }
            break;
        }
    }

    return settings;
}

void print_queue(std::queue<string> q)
{
  while (!q.empty())
  {
    cout << q.front() << " ";
    q.pop();
  }
  cout << endl;
}

//read input file to get problem specifications
void readinput(char *inputdeck) {/*,
               int nodims,
               int meshtype,
               int timesolver,

               Mesh &mesh) {*/

    ifstream infile (inputdeck); //open the file

    if (infile.is_open () && infile.good ()) {

        //Look for number of dimensions requested
        queue<string> settings;
        settings = getsettings(infile, "dimensions");
        print_queue(settings);

        //Look for mesh type
        settings = getsettings(infile, "mesh_type");
        print_queue(settings);

        //Look for time solver
        settings = getsettings(infile, "time_solver");
        print_queue(settings);

        //Look for the extent of each region in each dimension
        settings = getsettings(infile, "reg_length_x");
        print_queue(settings);
        settings = getsettings(infile, "reg_length_y");
        print_queue(settings);
        settings = getsettings(infile, "reg_length_z");
        print_queue(settings);

        //Look for origin of each region
        settings = getsettings(infile, "reg_origin_x");
        print_queue(settings);
        settings = getsettings(infile, "reg_origin_y");
        print_queue(settings);
        settings = getsettings(infile, "reg_origin_z");
        print_queue(settings);

        //Look for size of mesh in each region per dimension
        settings = getsettings(infile, "reg_mesh_x");
        print_queue(settings);
        settings = getsettings(infile, "reg_mesh_y");
        print_queue(settings);
        settings = getsettings(infile, "reg_mesh_z");
        print_queue(settings);

        //Look for initialisation of regions' physical properties
        settings = getsettings(infile, "init_reg_density");
        print_queue(settings);
        settings = getsettings(infile, "init_reg_energy");
        print_queue(settings);
        settings = getsettings(infile, "init_reg_pressure");
        print_queue(settings);
        settings = getsettings(infile, "init_reg_velocity");
        print_queue(settings);
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
    int timesolver = 1; //default predictor-corrector temporal solver
    int noregions = 1;

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

    readinput(argv[1]);


    Mesh mesh(2);
    //mesh.printNodePos();


    //init1DSod(mesh,density,energy,pressure,ccs2);

    //pressure.print();
    //ccs2.print();

    return 0;
}

