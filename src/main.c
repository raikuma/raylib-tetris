/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "constants.h"

typedef struct Tetromino
{
	int x;
	int y;
	int rotation;
	int type;
} Tetromino;

bool GridContains(int x, int y)
{
	return x >= 0 && x < GRID_COLS && y >= 0 && y < GRID_ROWS;
}

bool CheckCollision(Tetromino* mino, int blocks[GRID_ROWS][GRID_COLS])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (MINOS[mino->type][mino->rotation][i][j] != 0)
			{
				int x = mino->x + j;
				int y = mino->y + i;
				if (x < 0 || x >= GRID_COLS || y >= GRID_ROWS || blocks[y][x] != 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void _DrawMino(int px, int py, int rotation, int type, Color* color, bool texture)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (MINOS[type][rotation][i][j] != 0)
			{
				DrawRectangle(px + (j * GRID_SIZE), py + (i * GRID_SIZE), GRID_SIZE, GRID_SIZE, *color);
			}
		}
	}
}

void DrawMino(Tetromino* mino)
{
	_DrawMino(mino->x * GRID_SIZE, mino->y * GRID_SIZE, mino->rotation, mino->type, MINO_COLORS[mino->type], true);
}

void DrawMinoShadow(Tetromino* mino)
{
	_DrawMino(mino->x * GRID_SIZE, mino->y * GRID_SIZE, mino->rotation, mino->type, MINO_COLORS[mino->type], false);
	Color colorShadow = { 0, 0, 0, 100 };
	_DrawMino(mino->x * GRID_SIZE, mino->y * GRID_SIZE, mino->rotation, mino->type, &colorShadow, false);
}

void DrawMinoDisplay(int type, int px, int py)
{
	_DrawMino(px, py, 0, type, MINO_COLORS[type], true);
}

bool MoveMino(Tetromino* mino, int blocks[GRID_ROWS][GRID_COLS], int dx, int dy)
{
	mino->x += dx;
	mino->y += dy;
	if (CheckCollision(mino, blocks))
	{
		mino->x -= dx;
		mino->y -= dy;
		return false;
	}
	return true;
}

bool RotateMino(Tetromino* mino, int blocks[GRID_ROWS][GRID_COLS], int direction)
{
	if (mino->type == 0) // O
	{
		return false;
	}

	int oldRotation = mino->rotation;
	int oldx = mino->x;
	int oldy = mino->y;
	mino->rotation = (mino->rotation + direction + 4) % 4;

	// 1 -> 0, -1 -> 1
	direction = direction == 1 ? 0 : 1;

	int (*wallkicks)[2];

	if (mino->type == 1) // I
	{
		wallkicks = I_WALLKICKS[direction][oldRotation];
	}
	else // JLSTZ
	{
		wallkicks = JLSTZ_WALL_KICKS[direction][oldRotation];
	}

	for (int i = 0; i < 5; i++)
	{
		mino->x = oldx + wallkicks[i][0];
		mino->y = oldy - wallkicks[i][1];
		if (!CheckCollision(mino, blocks))
		{
			return true;
		}
	}

	mino->rotation = oldRotation;
	mino->x = oldx;
	mino->y = oldy;

	return false;
}

void InitMino(Tetromino* mino, int type)
{
	mino->x = SPAWN_X;
	mino->y = SPAWN_Y;
	mino->rotation = 0;
	mino->type = type;
}

void Shuffle(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		int temp = array[i];
		int randomIndex = GetRandomValue(0, size - 1);
		array[i] = array[randomIndex];
		array[randomIndex] = temp;
	}
}

int PopMinoBag(int* bag, int index)
{
	index++;
	if (index >= 7)
	{
		for (int i = 0; i < 7; i++)
		{
			bag[i] = bag[i + 7];
		}
		Shuffle(bag + 7, 7);
		index = 0;
	}
	return index;
}

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	bool isGameOver = false;

	float fallDelay = 0.9f;
	float fallTimer = 0.0f;

	float horTriggerTimer = 0.0f;
	float horMoveTimer = 0.0f;
	float verTriggerTimer = 0.0f;
	float verMoveTimer = 0.0f;
	int lastMoveDirection = 0;

	int blocks[GRID_ROWS][GRID_COLS] = { 0 };

	int minoBag[14] = { 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6 };
	Shuffle(minoBag, 7);
	Shuffle(minoBag + 7, 7);
	int minoBagIndex = 0;

	Tetromino currentMino = { SPAWN_X, SPAWN_Y, 0, minoBag[minoBagIndex] };
	Tetromino shadowMino = currentMino;
	int nextMinoType = minoBag[minoBagIndex + 1];
	int holdMinoType = -1;
	bool canHold = true;

	int score = 0;
	SetWindowTitle(TextFormat("Tetris - Score: %d", score));

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		if (isGameOver)
			ClearBackground(DARKGRAY);
		else
			ClearBackground(BLACK);

		// draw blocks
		for (int i = 0; i < GRID_ROWS; i++)
		{
			for (int j = 0; j < GRID_COLS; j++)
			{
				if (blocks[i][j] != 0)
				{
					DrawRectangle(j * GRID_SIZE, i * GRID_SIZE, GRID_SIZE, GRID_SIZE, *MINO_COLORS[blocks[i][j] - 1]);
				}
			}
		}

		// draw the shadow
		shadowMino = currentMino;
		while (!CheckCollision(&shadowMino, blocks))
		{
			shadowMino.y++;
		}
		shadowMino.y--;
		DrawMinoShadow(&shadowMino);

		// draw the current piece
		DrawMino(&currentMino);

		// draw the grid
		for (int i = 0; i < GRID_ROWS; i++)
		{
			DrawLine(0, i * GRID_SIZE, SCREEN_WIDTH, i * GRID_SIZE, GRAY);
		}
		for (int i = 0; i < GRID_COLS; i++)
		{
			DrawLine(i * GRID_SIZE, 0, i * GRID_SIZE, SCREEN_HEIGHT, GRAY);
		}

		// draw top border
		DrawRectangle(0, 0, SCREEN_WIDTH, GRID_SIZE * 3, BLACK);

		// draw the next mino
		DrawMinoDisplay(nextMinoType, SCREEN_WIDTH - GRID_SIZE * 3.5f, GRID_SIZE * 0.5f);

		// draw the hold mino
		if (holdMinoType != -1)
		{
			DrawMinoDisplay(holdMinoType, GRID_SIZE * 0.5f, GRID_SIZE * 0.5f);
		}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();

		if (!isGameOver)
		{
			// input
			if (IsKeyPressed(KEY_DOWN))
			{
				if (MoveMino(&currentMino, blocks, 0, 1)) {
					fallTimer = 0.0f;
				}
				verTriggerTimer = 0.0f;
				verMoveTimer = 0.0f;
			}
			if (IsKeyPressed(KEY_LEFT))
			{
				MoveMino(&currentMino, blocks, -1, 0);
				horTriggerTimer = 0.0f;
				horMoveTimer = 0.0f;
				lastMoveDirection = -1;
			}
			if (IsKeyPressed(KEY_RIGHT))
			{
				MoveMino(&currentMino, blocks, 1, 0);
				horTriggerTimer = 0.0f;
				horMoveTimer = 0.0f;
				lastMoveDirection = 1;
			}

			if (IsKeyDown(KEY_DOWN))
			{
				verTriggerTimer += GetFrameTime();
				if (verTriggerTimer >= TRIGGER_DELAY)
				{
					verMoveTimer += GetFrameTime();
					if (verMoveTimer >= VER_MOVE_DELAY)
					{
						if (MoveMino(&currentMino, blocks, 0, 1))
						{
							fallTimer = 0.0f;
						}
						verMoveTimer = 0.0f;
					}
				}
			}

			if (IsKeyDown(KEY_LEFT) && lastMoveDirection == -1)
			{
				horTriggerTimer += GetFrameTime();
				if (horTriggerTimer >= TRIGGER_DELAY)
				{
					horMoveTimer += GetFrameTime();
					if (horMoveTimer >= HOR_MOVE_DELAY)
					{
						MoveMino(&currentMino, blocks, -1, 0);
						horMoveTimer = 0.0f;
					}
				}
			}
			else if (IsKeyDown(KEY_RIGHT) && lastMoveDirection == 1)
			{
				horTriggerTimer += GetFrameTime();
				if (horTriggerTimer >= TRIGGER_DELAY)
				{
					horMoveTimer += GetFrameTime();
					if (horMoveTimer >= HOR_MOVE_DELAY)
					{
						MoveMino(&currentMino, blocks, 1, 0);
						horMoveTimer = 0.0f;
					}
				}
			}
			
			if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT))
			{
				horTriggerTimer = 0.0f;
				horMoveTimer = 0.0f;
			}
			if (IsKeyReleased(KEY_DOWN))
			{
				verTriggerTimer = 0.0f;
				verMoveTimer = 0.0f;
			}

			if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X))
			{
				RotateMino(&currentMino, blocks, 1);
			}
			else if (IsKeyPressed(KEY_Z))
			{
				RotateMino(&currentMino, blocks, -1);
			}

			if (IsKeyPressed(KEY_SPACE)) // hard drop
			{
				while (!CheckCollision(&currentMino, blocks))
				{
					currentMino.y++;
				}
				fallTimer = 0.0f;
			}

			if (IsKeyPressed(KEY_C)) // hold
			{
				if (canHold)
				{
					if (holdMinoType != -1)
					{
						int temp = currentMino.type;
						InitMino(&currentMino, holdMinoType);
						holdMinoType = temp;
						canHold = false;
					}
					else
					{
						holdMinoType = currentMino.type;
						minoBagIndex = PopMinoBag(minoBag, minoBagIndex);
						InitMino(&currentMino, minoBag[minoBagIndex]);
						nextMinoType = minoBag[minoBagIndex + 1];
					}
				}
			}

			// update
			fallTimer += GetFrameTime();
			if (fallTimer >= fallDelay)
			{
				fallTimer -= fallDelay;
				currentMino.y++;
			}

			if (CheckCollision(&currentMino, blocks)) // dropped
			{
				currentMino.y--;

				// put the mino in the grid
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (MINOS[currentMino.type][currentMino.rotation][i][j] != 0)
						{
							int x = currentMino.x + j;
							int y = currentMino.y + i;
							if (GridContains(x, y))
							{
								blocks[y][x] = currentMino.type + 1;
							}
						}
					}
				}

				// line clearing
				int r = currentMino.y + 3;
				for (int k = 0; k < 4; k++)
				{
					bool lineFull = false;
					for (int i = 0; i < GRID_COLS; i++)
					{
						if (blocks[r][i] == 0)
						{
							lineFull = false;
							break;
						}
						lineFull = true;
					}
					if (lineFull)
					{
						for (int i = r; i > 0; i--)
						{
							for (int j = 0; j < GRID_COLS; j++)
							{
								blocks[i][j] = blocks[i - 1][j];
							}
						}
						score += 100;
						SetWindowTitle(TextFormat("Tetris - Score: %d", score));
					}
					else
					{
						r--;
					}
				}

				// spawn a new mino
				minoBagIndex = PopMinoBag(minoBag, minoBagIndex);
				InitMino(&currentMino, minoBag[minoBagIndex]);
				nextMinoType = minoBag[minoBagIndex + 1];

				fallTimer = 0.0f;
				canHold = true;

				// check game over
				if (CheckCollision(&currentMino, blocks))
				{
					isGameOver = true;
				}
			}
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			isGameOver = false;
			for (int i = 0; i < GRID_ROWS; i++)
			{
				for (int j = 0; j < GRID_COLS; j++)
				{
					blocks[i][j] = 0;
				}
			}
			Shuffle(minoBag, 7);
			Shuffle(minoBag + 7, 7);
			minoBagIndex = 0;
			InitMino(&currentMino, minoBag[minoBagIndex]);
			nextMinoType = minoBag[minoBagIndex + 1];
			holdMinoType = -1;
			score = 0;
			SetWindowTitle(TextFormat("Tetris - Score: %d", score));
		}
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
