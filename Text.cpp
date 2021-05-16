#include "Text.h"

Text::Text(SDL_Renderer* _renderer, std::string _fontFile, std::string _text, int _fontSize, SDL_Colour _colour, int _x, int _y)	// constructor
{
	txt = _text;	// updates text being displayed

	char* fontFile = &_fontFile[0];
	char* charText = &_text[0];

	renderer = _renderer;
	font = TTF_OpenFont(fontFile, _fontSize);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, charText, _colour);	// getting text surface
	text = SDL_CreateTextureFromSurface(renderer, textSurface);	// creating text texture

	colour = _colour;	// storing the text colour

	rect.x = _x;	// setting text position
	rect.y = _y;
	SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);	// getting text dimensions

	SDL_FreeSurface(textSurface);	// freeing memory
}

Text::~Text()
{
	SDL_DestroyTexture(text);	// freeing memory
}

void Text::Draw()
{
	SDL_RenderCopy(renderer, text, NULL, &rect);	// draws text
}

void Text::SetText(std::string _text)
{
	if (_text != txt)	// updates text being displayed
	{
		SDL_DestroyTexture(text);	// freeing memory

		txt = _text;

		char* charText = &_text[0];

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, charText, colour);	// getting text surface
		text = SDL_CreateTextureFromSurface(renderer, textSurface);	// creating text texture

		SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);	// getting text dimensions

		SDL_FreeSurface(textSurface);	// freeing memory
	}
}
