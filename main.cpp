#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <windows.h>

const int GRID_SIZE = 40;
const int MAX_ITERATIONS = 100;
const int DELAY = 50;

//����
void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            std::cout << (grid[i][j] ? '*' : ' ') << " ";
        }
        std::cout << std::endl;
    }
}
//��� ������ �����
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
//������� �����
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

    srand(time(nullptr)); //����� ����� ��� ���������

    int grid[GRID_SIZE][GRID_SIZE];

    initializeGrid(grid);

    for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
        printGrid(grid);
        updateGrid(grid);
        Sleep(DELAY);
        if (iteration != MAX_ITERATIONS - 1) {
            system("cls");
        }
    }

    return 0;
}
