#include "Platform.h"


Platform::Platform(SDL_Rect r) {
	pos.x = r.x;
	pos.y = r.y;
	collider = r;
}

void Platform::draw() {
	SDL_Rect fillRect = { static_cast<int>(pos.x), static_cast<int>(pos.y), collider.w, collider.h};
	SDL_SetRenderDrawColor( SDLGI::gRenderer, 0x00, 0x00, 0x00, 0xFF );		
	SDL_RenderDrawRect( SDLGI::gRenderer, &fillRect );
}