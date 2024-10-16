// Copyright 2024 Morgan Nilsson
#include "./func.h"

int main(int argc, char** argv) {
	if (argc == 1) runGOL(0, 0, 0);
	else if (argc == 3) runGOL(atoi(argv[1]), atoi(argv[2]), 0);
	else if (argc == 4) runGOL(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	else return printf("Please enter a correct value of args");
	return 0;
}
