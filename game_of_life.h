#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <iostream>
#include <vector>
#include <random>
#include <SDL.h>
#include <ctime>


enum class Point {
    kEmpty,
    kFull
};

class GameOfLife {
public:
    GameOfLife(int h, int w);
    GameOfLife(int h, int w, const std::vector<std::pair<int, int>>& points);

    int Run();

private:
    int h_{};
    int w_{};

    SDL_Window *window_{nullptr};
    SDL_Surface *screenSurface_ {nullptr};

    void CreateWindow();

    std::vector<std::vector<Point>> prev_grid_;
    std::vector<std::vector<Point>> curr_grid_;

    void Initialize(int h, int w);
    void Print() const;
    bool PassOneSession();
};

#endif
