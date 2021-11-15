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
	_player.spawn(_map);
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

	SDL_Rect player_rect {
		int(_player.x() * MINIMAP_CELL_SIZE - PLAYER_DOT_SIZE/2),
		int(_player.y() * MINIMAP_CELL_SIZE - PLAYER_DOT_SIZE/2),
		PLAYER_DOT_SIZE,
		PLAYER_DOT_SIZE };
	SDL_SetRenderDrawColor(_renderer.get(), 255, 63, 63, 255);
	SDL_RenderFillRect(_renderer.get(), &player_rect);

	int x1 = int(_player.x() * MINIMAP_CELL_SIZE);
	int y1 = int(_player.y() * MINIMAP_CELL_SIZE);
	int x2 = int(x1 + cos(_player.dir()) * PLAYER_ARROW_SIZE);
	int y2 = int(y1 + sin(_player.dir()) * PLAYER_ARROW_SIZE);
	SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 0, 255);
	SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);
}

void MazeWindow::handle_keys(const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_E]) _player.turn_right();
	if (keys[SDL_SCANCODE_Q]) _player.turn_left();
	if (keys[SDL_SCANCODE_W]) _player.walk_forward();
	if (keys[SDL_SCANCODE_S]) _player.walk_backward();
	if (keys[SDL_SCANCODE_D]) _player.shift_right();
	if (keys[SDL_SCANCODE_A]) _player.shift_left();
}
