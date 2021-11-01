/*
 * MazeWindow.cc
 *
 *  Created on: 1 нояб. 2021 г.
 *      Author: unyuu
 */

#include "MazeWindow.h"

MazeWindow::MazeWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	_map = std::make_shared<Map>("level01.txt");
}

void MazeWindow::render()
{
	for (int row = 0; row < _map->height(); ++row) {
		for (int col = 0; col < _map->width(); ++col) {
			SDL_Rect cell_rect {
				col * MINIMAP_CELL_SIZE, row * MINIMAP_CELL_SIZE,
				MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE };
			if (_map->is_space(col, row)) {
				SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 63, 255);
			} else {
				SDL_SetRenderDrawColor(_renderer.get(), 196, 196, 196, 255);
			}
			SDL_RenderFillRect(_renderer.get(), &cell_rect);
		}
	}
}
