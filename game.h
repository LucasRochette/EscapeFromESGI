#ifndef _GAME_H
#define _GAME_H

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


// Audio settings
const uint8_t MONO = 1;
const uint8_t STEREO = 2;
static Uint8* audio_chunk;
static Uint32 audio_len;
static Uint8* audio_pos;
Mix_Chunk* blocked = NULL;

//Alpha settings
const uint8_t ALPHA_MAX = 255;
const uint8_t ALPHA_HIGH = 200;
const uint8_t ALPHA_MEDIUM = 150;
const uint8_t ALPHA_LOW = 100;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


void show_scores();
void loadScores();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//The image we will load and show on the screen
SDL_Surface* gLogo = NULL;

//The buttons image surface we will load and show on the screen
SDL_Surface* gButton = NULL;

//The text we will load and show on the screen
SDL_Surface* gText = NULL;

//The surface will be converted as texture
SDL_Texture* gStart_t = NULL;
SDL_Texture* gOption_t = NULL;
SDL_Texture* gHof_t = NULL;
SDL_Texture* gQuit_t = NULL;
SDL_Texture* gReturn_t = NULL;

//The surface will be converted as texture
SDL_Texture* gTexture = NULL;

//The surface will be converted as texture
SDL_Texture* gLogo_t = NULL;

//The surface will be converted as texture
SDL_Texture* gButton_t_start = NULL;
SDL_Texture* gButton_t_option = NULL;
SDL_Texture* gButton_t_hof = NULL;
SDL_Texture* gButton_t_quit = NULL;
SDL_Texture* gButton_t_return = NULL;


//The player we will move on the screen
SDL_Rect player;

//The audio spec
SDL_AudioSpec audioBufferSpec;

//Game logo
SDL_Rect logo;

//Game buttons
SDL_Rect button_start;
SDL_Rect button_option;
SDL_Rect button_hof;
SDL_Rect button_quit;
SDL_Rect button_return;

//Text
SDL_Rect t_Start;
SDL_Rect t_Option;
SDL_Rect t_Hof;
SDL_Rect t_Quit;
SDL_Rect t_Return;

//The renderer
SDL_Renderer* gRenderer = NULL;

TTF_Font* font = NULL;


#endif 