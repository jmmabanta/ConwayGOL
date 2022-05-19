#include "test_texture.h"

#include <iostream>

TestTexture::TestTexture(SDL_Renderer* renderer, const char* path)
    : texture(nullptr, SDL_DestroyTexture) {
  SDL_Surface* loadedSurface = IMG_Load(path);

  if (loadedSurface == NULL) {
    std::cerr << "Unable to load image at: " << path
              << " | ERROR: " << SDL_GetError() << '\n';
  } else {
    texture.reset(SDL_CreateTextureFromSurface(renderer, loadedSurface));
    if (texture == NULL) {
      std::cerr << "Unable to create texture from: " << path
                << " | ERROR: " << SDL_GetError() << '\n';
    }
    SDL_FreeSurface(loadedSurface);
  }
}

TestTexture::~TestTexture() { std::cout << "Destroying Test Texture...\n"; }

SDL_Texture* TestTexture::getTexture() const { return texture.get(); }
