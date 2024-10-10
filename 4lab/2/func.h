#include <ncurses.h>
#include <stdlib.h>
#include <vector>

#ifndef FUNC_H
#define FUNC_H

#define HEIGHT 40
#define WIDTH 90
typedef std::vector<std::vector<bool>> Mat;

void generation(const Mat& last, Mat& next);
void printDisplay(const Mat& display, int gen);
void init_board(Mat& mat);
#endif