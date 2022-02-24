/*
 * InputDeck.h
 *
 *  Created on: 16 Feb 2022
 *      Author: maryann
 */

#ifndef EXHYDRO_INCLUDE_INPUTDECK_H_
#define EXHYDRO_INCLUDE_INPUTDECK_H_

#include <yaml-cpp/yaml.h>

class InputDeck {

public:
    void open(std::string filename);

private:
    YAML::Node root;
};



#endif /* EXHYDRO_INCLUDE_INPUTDECK_H_ */
