#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <windows.h>

const int GRID_SIZE = 40;
const int MAX_ITERATIONS = 200;
const int DELAY = 50;

const int COLOR_WHITE = 15;
const int COLOR_BLUE = 9;

//инит
void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    COORD position;
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position); 

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
                std::cout <<"` ";
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_BLUE);
                std::cout << "[]";
            }
        }
        std::cout << std::endl;
    }
}

//для правил бытия
int countNeighbors(int grid[GRID_SIZE][GRID_SIZE], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

//правила бытия
void updateGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    int newGrid[GRID_SIZE][GRID_SIZE] = { 0 };

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            int neighbors = countNeighbors(grid, i, j);
            if (grid[i][j]) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            }
            else {
                newGrid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int main() {

    srand(time(nullptr)); //новое зерно для генерации

    int grid[GRID_SIZE][GRID_SIZE];

    initializeGrid(grid);

    for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
        printGrid(grid);
        updateGrid(grid);
        Sleep(DELAY);
    }

    return 0;
}
