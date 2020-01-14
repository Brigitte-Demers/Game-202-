/*
Name: Brigitte Demers.
Course: Game 202.
Prof: Majid Moghadam.
Title of Program: Game Programming.
Date: January 13th, 2020.
*/


// Includes SDL libraries.
#include "SDL.h"
// Includes the random number generating library.
#include <cstdlib>

//
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//
SDL_Renderer *renderer;

/*
*BRIGITTE'S CHANGES* New global variable added.
*/
SDL_Event event;

// Mouse coordinates;
int mouse_x, mouse_y;
int speed_x, speed_y;
// Balls speed.
int direction[2] = { -1, 1 };

// 
bool running = true;

//
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect Ball;
/*
*BRIGITTE'S CHANGES* Added line object. 
*/
SDL_Rect Middle;

bool check_collision(SDL_Rect A, SDL_Rect B)
{
	// The sides of the rectangles.
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rectangle A.
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	// Calculate the sides of rectangle B.
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	// If any of the sides from A are outside of B.
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	// If none of the sides from A are outside of B.
	return true;
}

/*
Purpose of the LoadGamer function:
*/
void LoadGame()
{
	speed_x = -1;
	speed_y = -1;

	//
	SDL_Window *window;

	//
	window = SDL_CreateWindow("Basic SDL Sprites",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window) {
		return;
	}

	//
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		return;
	}

	//
	PlayerPaddle.x = 20;
	PlayerPaddle.y = 250;
	PlayerPaddle.h = 100;
	PlayerPaddle.w = 20;

	//
	AIPaddle.x = 760;
	AIPaddle.y = 250;
	AIPaddle.h = 100;
	AIPaddle.w = 20;

	//
	Ball.x = 370;
	Ball.y = 290;
	Ball.w = 20;
	Ball.h = 20;

	/* 
	*BRIGITTE"S CHANGES* Added the placement of the line.
	*/
	Middle.x = 395;
	Middle.y = 5;
	Middle.w = 10;
	Middle.h = 590;
}

/*
Purpose of the Input function:
*/
// Get user input.
void Input()
{
	// Queing events.
	while (SDL_PollEvent(&event))
	{
		// Track mouse movement.
		if (event.type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&mouse_x, &mouse_y);

		// Clicking 'x' or pressing 'F4'.
		if (event.type == SDL_QUIT)
			running = false;

		// Pressing a key.
		if (event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym)
			{
				// Pressing 'ESC' exits from the game.
			case SDLK_ESCAPE:
				running = false;
				break;
			}
	}
}


/*
Purpose of Update function:
*/
void Update()
{
	PlayerPaddle.y = mouse_y;
	Ball.x += speed_x;
	Ball.y += speed_y;
	SDL_Delay(10);

	// Ball goes out on sides, left and right, then it will be reset to the centre of the screen.
	if (Ball.x < 0 || Ball.x > WINDOW_WIDTH)
	{
		Ball.x = WINDOW_WIDTH / 2;
		Ball.y = WINDOW_HEIGHT / 2;
		// This expression produces random numbers -1, -2, 1 and 2.
		speed_x = (rand() % 2 + 1) * direction[rand() % 2];
		speed_y = (rand() % 2 + 1) * direction[rand() % 2];
	}
	if (Ball.y < 0 || Ball.y > (WINDOW_HEIGHT - Ball.h))
	{
		speed_y =  -speed_y;
	}

	// AIPaddle y position.
	AIPaddle.y = Ball.y - AIPaddle.h / 2 + Ball.h / 2;

	if (check_collision(Ball, AIPaddle) || check_collision(Ball, PlayerPaddle))
	{
		speed_x = -speed_x;

		if (speed_x > 0)
		{
			speed_x += 1;
		}
		else
		{
			speed_x -= 1;
		}
		if (speed_y > 0)
		{
			speed_y += 1;
		}
		else
		{
			speed_y -= 1;
		}
	}
}

/*
Purpose of the DrawScreen function;
*/
void DrawScreen()
{
	//
	SDL_RenderClear(renderer);

	//
	SDL_Rect background = { 0, 0, 800, 600 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &background);

	//
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &PlayerPaddle);
	SDL_RenderFillRect(renderer, &AIPaddle);

	//
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &Ball);

	/*
	*BRIGITTE'S CHANGES* Drawing the line in the middle of the screen.
	*/
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &Middle);


	//
	SDL_RenderPresent(renderer);
}


/*
Purpose of the Quit function:
*/
void Quit()
{
	//
	SDL_Quit();
}

/*
Purpose of Main function:
*/
int main(int argc, char *argv[])
{
	//
	LoadGame();

	//
	while (running == true)
	{
		Input();         //
		Update();        //  
		DrawScreen();    //
	}

	//
	Quit();

	return 0;
}