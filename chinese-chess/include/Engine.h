#pragma once

#include <cmath>
#include <string>
#include <float.h>
#include <utility>

#include <SDL.h>
#include <SDL_TTF.h>

#include "defines.h"

SDL_Texture* LoadTexture(string configFile, SDL_Renderer* renderer);
bool MouseIsInRect(int2 coor, SDL_Rect rect);
bool collRectRect(SDL_Rect a, SDL_Rect b);
bool checkInOffBounds(SDL_Rect rect, int screenWidth, int screenHeight);
float lerp(float start, float target, float f);
int2 centerOfRect(SDL_Rect rect);