/*
 * MazeWindow.h
 *
 *  Created on: 1 нояб. 2021 г.
 *      Author: unyuu
 */

#ifndef MAZEWINDOW_H_
#define MAZEWINDOW_H_

#include <memory>
#include "Window.h"
#include "Map.h"

class MazeWindow final : public Window
{
private:
	std::shared_ptr<Map> _map {};
	static constexpr int WINDOW_WIDTH = 1920;
	static constexpr int WINDOW_HEIGHT = 1080;

	static constexpr int MINIMAP_CELL_SIZE = 64;
protected:
	virtual void render() override;

public:
	MazeWindow();
	virtual ~MazeWindow() = default;
};

#endif /* MAZEWINDOW_H_ */
