#include <iostream>
#include <array>
#include <time.h>
#include <stdlib.h>
#include <string>

const int HEIGHT{ 10 };
const int WIDTH{ 10 };
const int CELL_SIZE{ 3 };
const int WIDTH_PX{ WIDTH * CELL_SIZE + 1 };
const int HEIGHT_PX{ HEIGHT * CELL_SIZE + 1 };

const char CELL_EMPTY{ ' ' };
const char CELL_WALL_HORIZONTAL{ '-' };
const char CELL_WALL_VERTICAL{ '|' };
int I;

using namespace std;

void clearMap(array<array<char, WIDTH_PX>, HEIGHT_PX> &map)
{
    for (int j = 0; j < WIDTH_PX; j++)
    {
        if (j % CELL_SIZE == 0)
        {
            map[0][j] = CELL_EMPTY;
            map[HEIGHT_PX - 1][j] = CELL_EMPTY;
        }
        else
        {
            map[0][j] = CELL_WALL_HORIZONTAL;
            map[HEIGHT_PX - 1][j] = CELL_WALL_HORIZONTAL;
        }
    }

    for (int j = 0; j < HEIGHT_PX; j++)
    {
        if (j % CELL_SIZE == 0)
        {
            map[j][0] = CELL_EMPTY;
            map[j][WIDTH_PX - 1] = CELL_EMPTY;
        }
        else
        {
            map[j][0] = CELL_WALL_VERTICAL;
            map[j][WIDTH_PX - 1] = CELL_WALL_VERTICAL;
        }
    }

    for (int i = 1; i < WIDTH_PX - 1; i++)
    {
        for (int j = 1; j < HEIGHT_PX - 1; j++)
        {
            map[i][j] = CELL_EMPTY;
        }
    }
}

void printMap(const array<array<char, WIDTH_PX>, HEIGHT_PX> &map)
{
    for (int i = 0; i < WIDTH_PX; i++)
    {
        for (int j = 0; j < HEIGHT_PX; j++)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

void createNewWall(int x, int y, int width, int height,
    array<array<char, WIDTH_PX>, HEIGHT_PX> &map)
{
    if (width <= 1 || height <= 1)
    {
        return;
    }

    bool isWallHorizontal = true;
    if (width > height)
    {
        isWallHorizontal = false;
    }

    int wallStart = isWallHorizontal ? x * CELL_SIZE : y * CELL_SIZE;
    int wallEnd = isWallHorizontal ? (x + width) * CELL_SIZE : (y + height) * CELL_SIZE;

    int wallCoordinate;
    int wallEmpty;

    if (isWallHorizontal)
    {
        wallCoordinate = (rand() % (height - 1) + 1 + y) * CELL_SIZE;
        wallEmpty = (x + rand() % width) * CELL_SIZE;
    }
    else
    {
        wallCoordinate = (rand() % (width - 1) + 1 + x) * CELL_SIZE;
        wallEmpty = (y + rand() % height) * CELL_SIZE;
    }

    for (int i = wallStart; i < wallEnd; i++)
    {
        if ((i < wallEmpty || i >= wallEmpty + CELL_SIZE) && i % CELL_SIZE != 0)
        {
            if (isWallHorizontal)
            {
                map[wallCoordinate][i] = CELL_WALL_HORIZONTAL;
            }
            else
            {
                map[i][wallCoordinate] = CELL_WALL_VERTICAL;
            }
        }
    }
    I++;
    cout << I << endl;
    //printMap(map);
    //int newWidth, newHeight, newX, newY;
    if (isWallHorizontal)
    {
        createNewWall(x, y, width, wallCoordinate / CELL_SIZE - y, map);
        createNewWall(x, wallCoordinate / CELL_SIZE, width, height - wallCoordinate / CELL_SIZE, map);
    }
    else
    {
        createNewWall(x, y, wallCoordinate / CELL_SIZE - x, height, map);
        createNewWall(wallCoordinate / CELL_SIZE, y, width - wallCoordinate / CELL_SIZE, height, map);
    }
    I--;
    cout << I << endl;
}

int main()
{
    srand(time(NULL));

    std::array<std::array<char, WIDTH_PX>, HEIGHT_PX> map;

    clearMap(map);

    createNewWall(0, 0, WIDTH, HEIGHT, map);

    printMap(map);

    //system("pause");
    return 0;
}
