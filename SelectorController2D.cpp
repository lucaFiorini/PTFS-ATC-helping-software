#include "SelectorController2D.h"

SelectorController2D::SelectorController2D(unsigned int maxXin, unsigned  int maxYin
)
    : MaxSizeY{ maxYin }, MaxSizeX{ maxXin }
{
    Visualizer.resize(MaxSizeX, std::vector<char>(MaxSizeY, ' '));

    Visualizer[SelectionX][SelectionY] = '>';
}


SelectorController2D::SelectorController2D(unsigned int MaxXin, unsigned int MaxYin, unsigned int selXin, unsigned int selYin)
    : MaxSizeX{ MaxXin }, MaxSizeY{ MaxYin }, SelectionX{ selXin }, SelectionY{ selYin }
{

    Visualizer.resize(MaxSizeX, std::vector<char>(MaxSizeY, ' '));

    Visualizer[SelectionX][SelectionY] = '>';
}

bool SelectorController2D::BumpUp() {

    if (SelectionY < MaxSizeY - 1) {
        Visualizer[SelectionX][SelectionY] = ' ';
        SelectionY++;
        Visualizer[SelectionX][SelectionY] = '>';
        return true;
    }
    return false;
}

bool SelectorController2D::BumpDown() {

    if (SelectionY > 0) {
        Visualizer[SelectionX][SelectionY] = ' ';
        SelectionY--;
        Visualizer[SelectionX][SelectionY] = '>';
        return true;
    }
    return false;
}

bool SelectorController2D::BumpRight() {

    if (SelectionX < MaxSizeX - 1) {
        Visualizer[SelectionX][SelectionY] = ' ';
        SelectionX++;
        Visualizer[SelectionX][SelectionY] = '>';
        return true;
    }
    return false;
}

bool SelectorController2D::BumpLeft() {

    if (SelectionX > 0) {
        Visualizer[SelectionX][SelectionY] = ' ';
        SelectionX--;
        Visualizer[SelectionX][SelectionY] = '>';
        return true;
    }
    return false;
}