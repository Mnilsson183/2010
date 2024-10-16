#include <ncurses.h>
#include <stdlib.h>
#include <vector>

#ifndef FUNC_H
#define FUNC_H

#define LIVE "X"
typedef std::vector<std::vector<bool>> Mat;

void runGOL(int height, int width, int timeout_time);
#endif
