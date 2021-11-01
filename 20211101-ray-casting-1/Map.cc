/*
 * Map.cc
 *
 *  Created on: 1 нояб. 2021 г.
 *      Author: unyuu
 */

#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Map.h"

Map::Map(const char *filename)
{
	std::ifstream mapfile { filename };
	if (not mapfile)
		throw std::runtime_error(
				std::string("Не могу открыть файл карты ") +
				std::string(filename));

	std::string line;
	if (std::getline(mapfile, line)) {
		std::stringstream ss { line };
		ss >> _width >> _height >> _start_x >> _start_y >> _start_dir;
	}

	_data.resize(_width * _height);
	for (unsigned row = 0; row < _height; ++row) {
		std::getline(mapfile, line);
		for (unsigned col = 0; col < _width; ++col) {
			int result = 1;
			if (line[col] == ' ') result = 0;
			_data[_width * row + col] = result;
		}
	}

	mapfile.close();
}
