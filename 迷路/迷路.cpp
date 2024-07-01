#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 
    const int WIDTH = 960, HEIGHT = 704; 

    SetWindowText("?L?????N?^?[?????A?????????"); 
    SetGraphMode(WIDTH, HEIGHT, 32); 
    ChangeWindowMode(TRUE); 
    if (DxLib_Init() == -1) return -1; 
    SetBackgroundColor(0, 0, 0);
    SetDrawScreen(DX_SCREEN_BACK); 

    // 
    const int MAZE_PIXEL = 64; // 
    const int MAZE_W = 15; 
    const int MAZE_H = 11; // 
    char maze[MAZE_H][MAZE_W] = { 
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,0,0,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,0,1,0,1,1,1,0,1,0,1},
        {1,0,0,0,1,0,1,1,1,0,1,0,1,0,1},
        {1,0,1,1,1,0,1,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,1,1,0,1,0,1},
        {1,0,1,1,1,0,1,0,1,0,1,1,1,0,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int chip[2] = { 
        LoadGraph("image/floor.png"),
        LoadGraph("image/wall.png")
    };
    int player[4] = { 
        LoadGraph("image/robot_u.png"),
        LoadGraph("image/robot_d.png"),
        LoadGraph("image/robot_l.png"),
        LoadGraph("image/robot_r.png")
    };

    //
    int playerX = 96; // 
    int playerY = 96; // 
    int playerD = 1; 

    while (1) 
    {
        ClearDrawScreen(); 

        // 
        int x, y, sx, sy;
        for (y = 0; y < MAZE_H; y++)
        {
            for (x = 0; x < MAZE_W; x++)
            {
                sx = x * MAZE_PIXEL; // 
                sy = y * MAZE_PIXEL; //
                DrawGraph(sx, sy, chip[maze[y][x]], FALSE); // 
            }
        }

        //
        int newX = playerX, newY = playerY; // 
        if (CheckHitKey(KEY_INPUT_UP)) { newY = playerY - 2;  playerD = 0; } // 
        else if (CheckHitKey(KEY_INPUT_DOWN)) { newY = playerY + 2;  playerD = 1; } // 
        else if (CheckHitKey(KEY_INPUT_LEFT)) { newX = playerX - 2;  playerD = 2; } // 
        else if (CheckHitKey(KEY_INPUT_RIGHT)) { newX = playerX + 2;  playerD = 3; } //
        int mx1 = (newX - 20) / MAZE_PIXEL, my1 = (newY - 20) / MAZE_PIXEL; // 
        int mx2 = (newX + 19) / MAZE_PIXEL, my2 = (newY - 20) / MAZE_PIXEL; // 
        int mx3 = (newX - 20) / MAZE_PIXEL, my3 = (newY + 19) / MAZE_PIXEL; // 
        int mx4 = (newX + 19) / MAZE_PIXEL, my4 = (newY + 19) / MAZE_PIXEL; // 
        if (maze[my1][mx1] == 0 && maze[my2][mx2] == 0 && maze[my3][mx3] == 0 && maze[my4][mx4] == 0)
        {
            playerX = newX; // 
            playerY = newY; // 
        }
        DrawGraph(playerX - 20, playerY - 20, player[playerD], TRUE); 

        ScreenFlip(); 
        WaitTimer(16);
        if (ProcessMessage() == -1) break; 
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; 
    }

    DxLib_End(); 
    return 0; 
}