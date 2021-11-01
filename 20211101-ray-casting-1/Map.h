/*
 * Map.h
 *
 *  Created on: 1 нояб. 2021 г.
 *      Author: unyuu
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <cmath>

class Map
{
protected:
	int _width {}, _height {};
	double _start_x {}, _start_y {}, _start_dir {};
	std::vector<int> _data {};
public:
	Map(const char *filename);
	virtual ~Map() = default;

	int    width()     const { return _width; }
	int    height()    const { return _height; }
	double start_x()   const { return _start_x; }
	double start_y()   const { return _start_y; }
	double start_dir() const { return _start_dir; }

	bool is_space(int x, int y)
	{
		if (x < 0 or x >= _width or y < 0 or y >= _height)
			return false;
		return _data[y * _width + x] == 0;
	}

	bool is_space(double x, double y)
	{
		return is_space(int(floor(x)), int(floor(y)));
	}
};

#endif /* MAP_H_ */
