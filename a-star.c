 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Maze.h"

Node allNodes[ROW][COL];

bool isSafe(int maze[ROW][COL], int row, int col) {
    return (row >= 0 && row < ROW && col >= 0 && col < COL && maze[row][col] == 0);
}

double calculateH(int row, int col, int destRow, int destCol) {
    return (double)(abs(row - destRow) + abs(col - destCol));
}

// Hàm in đường đi (đổi sang định dạng (x, y))
void printPath(Node allNodes[ROW][COL], int destRow, int destCol) {
    int row = destRow;
    int col = destCol;
    while (allNodes[row][col].parent_i != -1 && allNodes[row][col].parent_j != -1) {
        printf("(%d, %d) <- ", col, row); // Đổi chỗ col và row
        int temp_row = allNodes[row][col].parent_i;
        int temp_col = allNodes[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    printf("(%d, %d)\n", col, row); // Đổi chỗ col và row
}

void aStar(int maze[ROW][COL], int startRow, int startCol, int destRow, int destCol) {
    if (maze[startRow][startCol] == 1 || maze[destRow][destCol] == 1) {
        printf("Không thể tìm đường đi.\n");
        return;
    }

    bool closedList[ROW][COL] = {false};
    bool openList[ROW][COL] = {false};

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            allNodes[i][j].f = allNodes[i][j].g = allNodes[i][j].h = 0;
            allNodes[i][j].parent_i = -1;
            allNodes[i][j].parent_j = -1;
        }
    }

    openList[startRow][startCol] = true;
    allNodes[startRow][startCol].g = 0;
    allNodes[startRow][startCol].h = calculateH(startRow, startCol, destRow, destCol);
    allNodes[startRow][startCol].f = allNodes[startRow][startCol].g + allNodes[startRow][startCol].h;

    while (true) {
        double minF = 1e9;
        int currentRow = -1, currentCol = -1;

        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (openList[i][j] && allNodes[i][j].f < minF) {
                    minF = allNodes[i][j].f;
                    currentRow = i;
                    currentCol = j;
                }
            }
        }

        if (currentRow == -1 || currentCol == -1) {
            printf("Không tìm thấy đường đi.\n");
            return;
        }

        if (currentRow == destRow && currentCol == destCol) {
            printf("Đường đi: ");
            printPath(allNodes, destRow, destCol);
            return;
        }

        openList[currentRow][currentCol] = false;
        closedList[currentRow][currentCol] = true;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) == abs(j)) continue;

                int newRow = currentRow + i;
                int newCol = currentCol + j;

                if (isSafe(maze, newRow, newCol) && !closedList[newRow][newCol]) {
                    double gNew = allNodes[currentRow][currentCol].g + 1;
                    if (!openList[newRow][newCol] || gNew < allNodes[newRow][newCol].g) {
                        allNodes[newRow][newCol].g = gNew;
                        allNodes[newRow][newCol].h = calculateH(newRow, newCol, destRow, destCol);
                        allNodes[newRow][newCol].f = allNodes[newRow][newCol].g + allNodes[newRow][newCol].h;
                        allNodes[newRow][newCol].parent_i = currentRow;
                        allNodes[newRow][newCol].parent_j = currentCol;
                        openList[newRow][newCol] = true;
                    }
                }
            }
        }
    }
}

int main() {
    int maze[10][10] = {
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
    };

    int startRow = 0, startCol = 0; // Điểm bắt đầu
    int destRow = 9, destCol = 9;    // Điểm kết thúc

    aStar(maze, startRow, startCol, destRow, destCol);

    return 0;
}
