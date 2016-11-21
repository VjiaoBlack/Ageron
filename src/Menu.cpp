#include "Menu.h"

void Menu::draw(Renderer &renderer) {
    /** Draw menu overlay **/
    SDL_SetRenderDrawBlendMode(renderer.SDLRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer.SDLRenderer, 0, 0, 0, 0xBB);
    
    SDL_Rect windowFrame = {0, 0, K_WINDOW_WIDTH, K_WINDOW_HEIGHT};
    SDL_RenderFillRect(renderer.SDLRenderer, &windowFrame);

    SDL_Rect itemFrame = frame;
    
    for (auto &item : items) {
        int old_w = itemFrame.w;
        item.draw(renderer, textColor, font, itemFrame);
        
        itemFrame.w = max(itemFrame.w, old_w);
        itemFrame.y += itemFrame.h;
        if (itemFrame.y + itemFrame.h > frame.y + frame.h) {
            itemFrame.y = frame.y;
            itemFrame.x += itemFrame.w;
        }
    }    
}

void Menu::MenuItem::draw(Renderer &renderer, SDL_Color color, TTF_Font *font, SDL_Rect layout) {
    renderer.drawText(title, color, font, layout);
}
