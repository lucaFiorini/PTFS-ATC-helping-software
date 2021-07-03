//HOW TO USE:
//TODO: ADD DOCUMENTATION

#pragma once

#include <vector>


class SelectorController2D {
    const unsigned int MaxSizeX, MaxSizeY;
public:
    std::vector<std::vector<char>> Visualizer;
    unsigned int SelectionX{ 0 };
    unsigned int SelectionY{ 0 };
    SelectorController2D(unsigned int, unsigned int);
    SelectorController2D(unsigned int, unsigned int, unsigned int, unsigned int);
    bool BumpUp();
    bool BumpDown();
    bool BumpLeft();
    bool BumpRight();
};