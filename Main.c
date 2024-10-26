#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 16
#define HEIGHT 16
#define INF 1000000

typedef struct {
    int x, y;
} Node;

// Hàm tính khoảng cách Manhattan (hàm heuristic)
int heuristic(Node a, Node b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Hàm so sánh cho hàng đợi ưu tiên
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Kiểm tra nếu tọa độ nằm trong mê cung
bool in_bounds(int x, int y) {
    return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

// Các hàm kiểm tra tường
bool check_wall_top(int x, int y);
bool check_wall_left(int x, int y);
bool check_wall_right(int x, int y);
bool check_wall_bottom(int x, int y);

// Hàm triển khai A*
Node* astar(Node start, Node goal, int *path_length) {
    int g_score[WIDTH][HEIGHT];
    int f_score[WIDTH][HEIGHT];
    Node came_from[WIDTH][HEIGHT];
    bool open_set[WIDTH][HEIGHT] = {false};

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            g_score[i][j] = INF;
            f_score[i][j] = INF;
        }
    }

    g_score[start.x][start.y] = 0;
    f_score[start.x][start.y] = heuristic(start, goal);
    open_set[start.x][start.y] = true;

    Node *path = malloc(WIDTH * HEIGHT * sizeof(Node));
    int path_index = 0;

    while (1) {
        // Tìm ô có f_score nhỏ nhất
        int min_f = INF;
        Node current = {-1, -1};
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                if (open_set[i][j] && f_score[i][j] < min_f) {
                    min_f = f_score[i][j];
                    current = (Node){i, j};
                }
            }
        }

        // Nếu không tìm thấy đường đi hoặc đã tới đích
        if (current.x == -1 || (current.x == goal.x && current.y == goal.y)) {
            break;
        }

        open_set[current.x][current.y] = false;

        // Các hướng có thể di chuyển
        Node neighbors[4];
        int neighbor_count = 0;
        if (!check_wall_top(current.x, current.y) && in_bounds(current.x, current.y - 1))
            neighbors[neighbor_count++] = (Node){current.x, current.y - 1};
        if (!check_wall_left(current.x, current.y) && in_bounds(current.x - 1, current.y))
            neighbors[neighbor_count++] = (Node){current.x - 1, current.y};
        if (!check_wall_right(current.x, current.y) && in_bounds(current.x + 1, current.y))
            neighbors[neighbor_count++] = (Node){current.x + 1, current.y};
        if (!check_wall_bottom(current.x, current.y) && in_bounds(current.x, current.y + 1))
            neighbors[neighbor_count++] = (Node){current.x, current.y + 1};

        for (int i = 0; i < neighbor_count; i++) {
            Node neighbor = neighbors[i];
            int tentative_g_score = g_score[current.x][current.y] + 1;

            if (tentative_g_score < g_score[neighbor.x][neighbor.y]) {
                came_from[neighbor.x][neighbor.y] = current;
                g_score[neighbor.x][neighbor.y] = tentative_g_score;
                f_score[neighbor.x][neighbor.y] = tentative_g_score + heuristic(neighbor, goal);

                if (!open_set[neighbor.x][neighbor.y]) {
                    open_set[neighbor.x][neighbor.y] = true;
                }
            }
        }
    }

    // Truy ngược lại đường đi
    Node current = goal;
    while (current.x != start.x || current.y != start.y) {
        path[path_index++] = current;
        current = came_from[current.x][current.y];
    }
    path[path_index++] = start;

    *path_length = path_index;
    return path;
}

int main() {
    Node start = {0, 0};
    Node goal = {15, 15};
    int path_length;
    Node *path = astar(start, goal, &path_length);

    printf("Path:\n");
    for (int i = path_length - 1; i >= 0; i--) {
        printf("(%d, %d) ", path[i].x, path[i].y);
    }

    free(path);
    return 0;
}