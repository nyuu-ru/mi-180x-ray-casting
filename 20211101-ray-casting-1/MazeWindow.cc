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
	SDL_SetRenderDrawBlendMode(_renderer.get(), SDL_BLENDMODE_BLEND);
	_map = std::make_shared<Map>("level01.txt");
	_player.spawn(_map);
}

void MazeWindow::draw_minimap()
{
	for (int row = 0; row < _map->height(); ++row) {
		for (int col = 0; col < _map->width(); ++col) {
			SDL_Rect cell_rect { col * MINIMAP_CELL_SIZE, row
			        * MINIMAP_CELL_SIZE,
			                     MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE };
			if (_map->is_space(col, row)) {
				SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 63, 127);
			} else {
				SDL_SetRenderDrawColor(_renderer.get(), 196, 196, 196, 127);
			}
			SDL_RenderFillRect(_renderer.get(), &cell_rect);
		}
	}
}

void MazeWindow::draw_player()
{
	SDL_Rect player_rect {
	        int(_player.x() * MINIMAP_CELL_SIZE - PLAYER_DOT_SIZE / 2), int(
	                _player.y() * MINIMAP_CELL_SIZE - PLAYER_DOT_SIZE / 2),
	        PLAYER_DOT_SIZE, PLAYER_DOT_SIZE };
	SDL_SetRenderDrawColor(_renderer.get(), 255, 63, 63, 255);
	SDL_RenderFillRect(_renderer.get(), &player_rect);
	int x1 = int(_player.x() * MINIMAP_CELL_SIZE);
	int y1 = int(_player.y() * MINIMAP_CELL_SIZE);
	int x2 = int(x1 + cos(_player.dir()) * PLAYER_ARROW_SIZE);
	int y2 = int(y1 + sin(_player.dir()) * PLAYER_ARROW_SIZE);
	SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 0, 255);
	SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);
}

void MazeWindow::render()
{
	SDL_Rect sky_rect   { 0, 0,          width(), height()/2 };
	SDL_Rect floor_rect { 0, height()/2, width(), height()/2 };
	SDL_SetRenderDrawColor(_renderer.get(), 190, 213, 255, 255);
	SDL_RenderFillRect(_renderer.get(), &sky_rect);
	SDL_SetRenderDrawColor(_renderer.get(), 106, 106, 106, 255);
	SDL_RenderFillRect(_renderer.get(), &floor_rect);

	double alpha = _player.dir();
	static constexpr double EPS = 0.00001;
	double px = _player.x();
	double py = _player.y();
	double Ds = width() / 2.0 / tan(_player.fov()); // Расстояние до экрана
	double Hw = 1.0; // Высота стены в клетках
	for (int col = 0; col < width(); ++col) {
		double h;
		double rx, ry;
		double dx, dy;
		double Dw, Dv, Dh;
		double gamma = atan2(col - width()/2, Ds);
		double beta  = alpha + gamma;

		if (cos(beta) > EPS) { // в вертикальную вправо
			rx = floor(px) + EPS;
			dx = 1.0;
			dy = tan(beta);
			ry = py - (px - rx) * dy;

			// бросить лучик

			Dv = hypot(rx - px, ry - py);
		} else if (cos(beta) < -EPS) { // в вертикальную влево
			rx = ceil(px) - EPS;
			dx = -1.0;
			dy = tan(-beta);
			ry = py - (rx - px) * dy;

			//бросить лучик

			Dv = hypot(rx - px, ry - py);
		} else { // вдоль вертикальных линий
			Dv = INFINITY;
		}

		// Вычислить Dh

		// Вычислить Dw
		// Вычислить h
		// Нарисовать столбец

	}

	draw_minimap();
	draw_player();
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
