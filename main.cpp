#include <iostream>
#include <SDL.h>
#include "game_of_life.h"

int main(int argc, char* args[]) {

    int TypeOfPaint = 0, h = 0, w = 0, PointsNum = 0, x = 0, y = 0;
    bool  SizesAreCorrect = false;
    bool  TypeIsCorrect = false;
    std::vector<std::pair<int, int>> points;

    std::cout << "Enter height and width" << std::endl;

    while(!SizesAreCorrect) {
        std::cin >> h >> w;
        if (h <= 0 || w <= 0) {
            std::cout << "Height or width cannot be non-positive, try again, try again" << std::endl;
        } else {
            SizesAreCorrect = true;
        }
    }

    std::cout << "Choose the type of filling: 0 - pseudo-random, 1 - manually" << std::endl;

    while(!TypeIsCorrect) {
        std::cin >> TypeOfPaint;
        if (TypeOfPaint != 0 && TypeOfPaint != 1) {
            std::cout << std::endl;
            std::cout << "try again" << std::endl;
        } else {
            TypeIsCorrect = true;
        }
    }

    if(TypeOfPaint == 0) {
        GameOfLife gm(h, w);
        gm.Run();
    } else {
        std::cout << "Enter points coordinates::" << std::endl;
        while(true) {
            std::cin >> x >> y;
            if(x < 0 || y < 0) {
                break;
            }
            points.emplace_back(x, y);
            PointsNum++;
        }
        GameOfLife gm(h, w, points);
        gm.Run();
    }
    return 0;
}
