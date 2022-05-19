#ifndef CONWAYGOL_EXPERIMENTS_TEST_TEXTURE_H_
#define CONWAYGOL_EXPERIMENTS_TEST_TEXTURE_H_

#include <SDL2/SDL_image.h>

class TestTexture {
  public:
    TestTexture(SDL_Renderer* renderer,const char* path);
    ~TestTexture();

    SDL_Texture* getTexture() const;

  private:
    SDL_Texture* texture;
};

#endif
