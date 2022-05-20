#ifndef CONWAYGOL_EXPERIMENTS_TEST_TEXTURE_H_
#define CONWAYGOL_EXPERIMENTS_TEST_TEXTURE_H_

#include <SDL2/SDL_image.h>

#include <memory>

class TestTexture {
 public:
  TestTexture(std::shared_ptr<SDL_Renderer> renderer, const char* path);
  ~TestTexture();

  SDL_Texture* getTexture() const;

 private:
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
};

#endif
