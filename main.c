#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string.h>
#include "game.h"
#include <winsock.h>
#include <mysql.h>




char* start = "START";
char* option = "OPTIONS";
char* hof = "SCORES";
char* quit = "EXIT";

char* composition;
Sint32 cursor;
Sint32 selection_len;
void loadMainMenu();


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Escape from ESGI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);

			//Creating renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Failed to create renderer! SDL_Error: %s\n", SDL_GetError());

				success = false;

			}
			 else 
			{
				// Set size of renderer to the same as window
				SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);


				//Initialisation de SDL_mixer
				if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, STEREO, 4096) == -1)
				{
					return false;
				}
				

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = IMG_Load("res\\fond_menu_1.jpg");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Load the image data into the hardware's memory
	gTexture = SDL_CreateTextureFromSurface(gRenderer, gHelloWorld);
	SDL_FreeSurface(gHelloWorld);
	if (!gTexture)
	{
		printf("Error creating texture. SDL Error: %s\n", SDL_GetError());
		success = false;
	}


	//Load splash image
	gLogo = IMG_Load("res\\logo2.png");
	if (gLogo == NULL)
	{
		printf("Unable to load image. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Load the image data into the hardware's memory
	gLogo_t = SDL_CreateTextureFromSurface(gRenderer, gLogo);
	SDL_FreeSurface(gLogo);
	if (!gLogo_t)
	{
		printf("Error creating texture. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Load button image
	gButton = IMG_Load("res\\blue_button.png");
	if (gButton == NULL)
	{
		printf("Unable to load image. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Load the button image data into the hardware's memory
	gButton_t_start = SDL_CreateTextureFromSurface(gRenderer, gButton);
	gButton_t_option = SDL_CreateTextureFromSurface(gRenderer, gButton);
	gButton_t_hof = SDL_CreateTextureFromSurface(gRenderer, gButton);
	gButton_t_quit = SDL_CreateTextureFromSurface(gRenderer, gButton);
	gButton_t_return = SDL_CreateTextureFromSurface(gRenderer, gButton);

	SDL_SetTextureAlphaMod(gButton_t_start, ALPHA_MEDIUM);
	SDL_SetTextureAlphaMod(gButton_t_option, ALPHA_MEDIUM);
	SDL_SetTextureAlphaMod(gButton_t_hof, ALPHA_MEDIUM);
	SDL_SetTextureAlphaMod(gButton_t_quit, ALPHA_MEDIUM);
	SDL_SetTextureAlphaMod(gButton_t_return, ALPHA_MEDIUM);

	SDL_FreeSurface(gButton);

	if (!gButton_t_start || !gButton_t_option || !gButton_t_hof || !gButton_t_quit || !gButton_t_return)
	{
		printf("Error creating texture. SDL Error: %s\n", SDL_GetError());
		success = false;
	}


	if (TTF_Init() < 0) 
	{
		printf("Error TTF_Init:  %s\n", SDL_GetError());
	}


	//Loading font
	font = TTF_OpenFont("res\\arial.ttf", 25);
	if (!font)
	{
		printf("Error loading font:  %s\n", SDL_GetError());
		return false;
	}


	SDL_Color foreground = { 0, 0, 0 };
	gText = TTF_RenderText_Solid(font, start, foreground);
	if (gText == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	t_Start.w = gText->w;
	t_Start.h = gText->h;
	

	gStart_t = SDL_CreateTextureFromSurface(gRenderer, gText);
	if (gStart_t == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}


	gText = TTF_RenderText_Solid(font, option, foreground);
	if (gText == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	t_Option.w = gText->w;
	t_Option.h = gText->h;


	gOption_t = SDL_CreateTextureFromSurface(gRenderer, gText);
	if (gOption_t == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Text Hof

	gText = TTF_RenderText_Solid(font, hof, foreground);
	if (gText == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	t_Hof.w = gText->w;
	t_Hof.h = gText->h;


	gHof_t = SDL_CreateTextureFromSurface(gRenderer, gText);
	if (gHof_t == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	
	//Text Quit

	gText = TTF_RenderText_Solid(font, quit, foreground);
	if (gText == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	t_Quit.w = gText->w;
	t_Quit.h = gText->h;


	gQuit_t = SDL_CreateTextureFromSurface(gRenderer, gText);
	if (gQuit_t == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Text return

	gText = TTF_RenderText_Solid(font, "BACK", foreground);
	if (gText == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	t_Return.w = gText->w;
	t_Return.h = gText->h;


	gReturn_t = SDL_CreateTextureFromSurface(gRenderer, gText);
	if (gReturn_t == NULL)
	{
		printf("Unable to load font surface. SDL Error: %s\n", SDL_GetError());
		success = false;
	}


	// Load audio files
	blocked = Mix_LoadWAV("res\\blocked.wav");;
	Mix_Volume(-1, MIX_MAX_VOLUME / 4);


	if (blocked == NULL)
	{
		printf("Unable to load sounds. SDL Error: %s\n", SDL_GetError());
		success = false;
	}


	return success;
}

void close()
{
	//Destroy renderer
	SDL_DestroyRenderer(gRenderer);
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_FreeChunk(blocked);
	Mix_CloseAudio();
	SDL_Quit();
}

void loadMainMenu()
{


	//clear the window
	SDL_RenderClear(gRenderer);


	//draw the texture to the window
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


	// Change color to blue!
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);

	// Render our "player"
	SDL_RenderFillRect(gRenderer, &player);


	// Add game logo 
	logo.x = (SCREEN_WIDTH / 2) - (logo.w / 2);
	logo.y = (SCREEN_HEIGHT / 2) - (logo.h);


	// Add buttons 
	button_start.x = (SCREEN_WIDTH / 2) - (button_start.w / 2);
	button_start.y = logo.y + logo.h + 25;

	button_hof.x = button_start.x;
	button_hof.y = button_start.y + button_start.h + 20;

	button_option.x = button_hof.x;
	button_option.y = button_hof.y + button_hof.h + 20;

	button_quit.x = button_option.x;
	button_quit.y = button_option.y + button_option.h + 20;

	t_Start.x = button_start.x + (button_start.w / 2) - (t_Start.w / 2);
	t_Start.y = button_start.y + (button_start.h / 2) - (t_Start.h / 2);


	t_Option.x = button_option.x + (button_option.w / 2) - (t_Option.w / 2);
	t_Option.y = button_option.y + (button_option.h / 2) - (t_Option.h / 2);

	t_Hof.x = button_hof.x + (button_hof.w / 2) - (t_Hof.w / 2);
	t_Hof.y = button_hof.y + (button_hof.h / 2) - (t_Hof.h / 2);

	t_Quit.x = button_quit.x + (button_quit.w / 2) - (t_Quit.w / 2);
	t_Quit.y = button_quit.y + (button_quit.h / 2) - (t_Quit.h / 2);

	SDL_QueryTexture(gLogo_t, NULL, NULL, &logo.w, &logo.h);
	SDL_RenderCopy(gRenderer, gLogo_t, NULL, &logo);

	SDL_QueryTexture(gButton_t_start, NULL, NULL, &button_start.w, &button_start.h);
	SDL_RenderCopy(gRenderer, gButton_t_start, NULL, &button_start);


	SDL_QueryTexture(gButton_t_option, NULL, NULL, &button_option.w, &button_option.h);
	SDL_RenderCopy(gRenderer, gButton_t_option, NULL, &button_option);

	SDL_QueryTexture(gButton_t_hof, NULL, NULL, &button_hof.w, &button_hof.h);
	SDL_RenderCopy(gRenderer, gButton_t_hof, NULL, &button_hof);

	SDL_QueryTexture(gButton_t_quit, NULL, NULL, &button_quit.w, &button_quit.h);
	SDL_RenderCopy(gRenderer, gButton_t_quit, NULL, &button_quit);

	// Add text
	SDL_RenderCopy(gRenderer, gStart_t, NULL, &t_Start);
	SDL_RenderCopy(gRenderer, gHof_t, NULL, &t_Hof);
	SDL_RenderCopy(gRenderer, gOption_t, NULL, &t_Option);
	SDL_RenderCopy(gRenderer, gQuit_t, NULL, &t_Quit);

	SDL_RenderPresent(gRenderer);
}

void loadScores()
{

	//clear the window
	SDL_RenderClear(gRenderer);


	//draw the texture to the window
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


	// Change color to blue!
	//SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);

	// Render our "player"
	//SDL_RenderFillRect(gRenderer, &player);


	// Add game logo 
	logo.x = 0;
	logo.y = 0;
	SDL_QueryTexture(gLogo_t, NULL, NULL, &logo.w, &logo.h);
	SDL_RenderCopy(gRenderer, gLogo_t, NULL, &logo);


	// Add buttons 


	button_return.x = button_option.x;
	button_return.y = button_option.y + button_option.h + 20;


	t_Return.x = button_quit.x + (button_quit.w / 2) - (t_Return.w / 2);
	t_Return.y = button_quit.y + (button_quit.h / 2) - (t_Return.h / 2);




	SDL_QueryTexture(gButton_t_return, NULL, NULL, &button_return.w, &button_return.h);
	SDL_RenderCopy(gRenderer, gButton_t_return, NULL, &button_return);

	// Add text
	SDL_RenderCopy(gRenderer, gReturn_t, NULL, &t_Return);

	SDL_RenderPresent(gRenderer);
}


void show_scores()
{

	printf("clic sur scores\n");


	//MySQL DB connection
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(&mysql, "sql7.freesqldatabase.com", "sql7322744", "IyLIhGrwHC", "sql7322744", 3306, NULL, 0))
	{
		printf("connexion OK\n");


		mysql_close(&mysql);
	}
	else
	{
		printf("Error while connecting to database!");
	}



	bool returnMenu = false;

	int buttonPressed = 0;
	int click = 1;

	SDL_Event e;







	while (!returnMenu)
	{
		SDL_PollEvent(&e);
		switch (e.type)
		{
		case SDL_QUIT:
			returnMenu = true;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				// ....;

					buttonPressed = 1;
					break;

				
			case SDLK_UP:

				break;
			case SDLK_DOWN:
				
				break;
			case SDLK_LEFT:
				
				break;
			case SDLK_RIGHT:
				
				break;
			}
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				// ....;
				if (buttonPressed == 1)
				{
					buttonPressed = 0;
					returnMenu = true;
					break;
				}
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			if (e.motion.x >= button_return.x && e.motion.x <= (button_return.x + button_return.w) && e.motion.y >= button_return.y && e.motion.y <= (button_return.y + button_return.h))
			{
				SDL_SetTextureAlphaMod(gButton_t_return, ALPHA_HIGH);
				break;

			}
			else
			{
				SDL_SetTextureAlphaMod(gButton_t_return, ALPHA_MEDIUM);
				break;

			}
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_return.x && e.motion.x <= (button_return.x + button_return.w) && e.motion.y >= button_return.y && e.motion.y <= (button_return.y + button_return.h))
			{
				click = 1;
				break;
			}
			else
			{
				//Clic outside buttons
			}
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_start.x && e.motion.x <= (button_start.x + button_start.w) && e.motion.y >= button_start.y && e.motion.y <= (button_start.y + button_start.h))
			{
				if (click == 1)
				{
					SDL_SetTextureAlphaMod(gButton_t_return, ALPHA_LOW);
					click = 0;
					returnMenu = true;
					break;
				}
				break;
			}
			else
			{
				//Clic outside buttons
			}
		}

		loadScores();
		SDL_Delay(1000 / 50);

	}

}



int main(int argc, char* args[])
{

	// Initlaize our player
	player.w = 200;
	player.h = 200;
	player.x = 15;
	player.y = 15;




	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;



			//SDL_SetTextInputRect(&button_start);



			//Event handler
			SDL_Event e;


			int click = 1;

			//While application is running
			while (!quit)
			{
				SDL_PollEvent(&e);
				switch (e.type)
				{
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						// ....;
						quit = 0;
						break;
					case SDLK_UP:
						if (player.y > SCREEN_HEIGHT-SCREEN_HEIGHT)
						{
							player.y += -10;
							break;

						}
						else
						{
							if (Mix_PlayChannel(-1, blocked, 0) == -1)
							{
								SDL_Delay(100);
								break;

								//return 1;
							}
						}
						break;
					case SDLK_DOWN:
						if (player.y + player.h < SCREEN_HEIGHT)
						{
							player.y += 10;
							break;

						}
						else
						{
							if (Mix_PlayChannel(-1, blocked, 0) == -1)
							{
								SDL_Delay(100);
								break;

								//return 1;
							}
						}
						break;
					case SDLK_LEFT:
						if (player.x > SCREEN_WIDTH-SCREEN_WIDTH)
						{
							player.x += -10;
							break;

						}
						else
						{
							if (Mix_PlayChannel(-1, blocked, 0) == -1)
							{
								SDL_Delay(100);
								break;

								//return 1;
							}
						}
						break;
					case SDLK_RIGHT:
						if (player.x + player.w < SCREEN_WIDTH)
						{
							player.x += 10;
							break;

						}
						else
						{
							if (Mix_PlayChannel(-1, blocked, 0) == -1)
							{
								SDL_Delay(100);
								break;

								//return 1;
							}
						}
						break;
					}
				case SDL_KEYUP:
					switch (e.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						// ....;
						quit = 1;
						break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (e.motion.x >= button_start.x && e.motion.x <= (button_start.x + button_start.w) && e.motion.y >= button_start.y && e.motion.y <= (button_start.y + button_start.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_start, ALPHA_HIGH);
						break;

					}
					else if (e.motion.x >= button_option.x && e.motion.x <= (button_option.x + button_option.w) && e.motion.y >= button_option.y && e.motion.y <= (button_option.y + button_option.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_option, ALPHA_HIGH);
						break;

					}
					else if (e.motion.x >= button_hof.x && e.motion.x <= (button_hof.x + button_hof.w) && e.motion.y >= button_hof.y && e.motion.y <= (button_hof.y + button_hof.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_hof, ALPHA_HIGH);
						break;


					}
					else if (e.motion.x >= button_quit.x && e.motion.x <= (button_quit.x + button_quit.w) && e.motion.y >= button_quit.y && e.motion.y <= (button_quit.y + button_quit.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_quit, ALPHA_HIGH);
						break;

					}
					else 
					{
						SDL_SetTextureAlphaMod(gButton_t_start, ALPHA_MEDIUM);
						SDL_SetTextureAlphaMod(gButton_t_option, ALPHA_MEDIUM);
						SDL_SetTextureAlphaMod(gButton_t_hof, ALPHA_MEDIUM);
						SDL_SetTextureAlphaMod(gButton_t_quit, ALPHA_MEDIUM);
						break;

					}
				case SDL_MOUSEBUTTONDOWN:
					if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_start.x && e.motion.x <= (button_start.x + button_start.w) && e.motion.y >= button_start.y && e.motion.y <= (button_start.y + button_start.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_start, ALPHA_MAX);
						break;
					}
					else if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_option.x && e.motion.x <= (button_option.x + button_option.w) && e.motion.y >= button_option.y && e.motion.y <= (button_option.y + button_option.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_option, ALPHA_MAX);
						break;

					}
					else if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_hof.x && e.motion.x <= (button_hof.x + button_hof.w) && e.motion.y >= button_hof.y && e.motion.y <= (button_hof.y + button_hof.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_hof, ALPHA_MAX);
						click = 1;
						break;

					}
					else if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_quit.x && e.motion.x <= (button_quit.x + button_quit.w) && e.motion.y >= button_quit.y && e.motion.y <= (button_quit.y + button_quit.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_quit, ALPHA_MAX);
						break;

					}
					else
					{
						//Clic outside buttons
					}
				case SDL_MOUSEBUTTONUP:
					if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_start.x && e.motion.x <= (button_start.x + button_start.w) && e.motion.y >= button_start.y && e.motion.y <= (button_start.y + button_start.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_start, ALPHA_LOW);
						break;

					}
					else if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_option.x && e.motion.x <= (button_option.x + button_option.w) && e.motion.y >= button_option.y && e.motion.y <= (button_option.y + button_option.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_option, ALPHA_LOW);
						break;

					}
					else if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_hof.x && e.motion.x <= (button_hof.x + button_hof.w) && e.motion.y >= button_hof.y && e.motion.y <= (button_hof.y + button_hof.h))
					{
						if (click == 1)
						{
							SDL_SetTextureAlphaMod(gButton_t_hof, ALPHA_LOW);
							click = 0;
							show_scores();
							
							break;
						}
						

					}
					else if (e.button.button == SDL_BUTTON_LEFT && e.motion.x >= button_quit.x && e.motion.x <= (button_quit.x + button_quit.w) && e.motion.y >= button_quit.y && e.motion.y <= (button_quit.y + button_quit.h))
					{
						SDL_SetTextureAlphaMod(gButton_t_quit, ALPHA_LOW);
						SDL_Delay(500);
						quit = 1;
					}
					else
					{
						//Clic outside buttons
					}
				}

				loadMainMenu();

		
				SDL_Delay(1000/50);


			}
		}
	}


	//Free resources and close SDL
	close();

	return 0;
}
