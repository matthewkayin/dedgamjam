#include "texture.hpp"

Texture::Texture(){

    image = nullptr;
    width = 0;
    height = 0;
}

Texture::~Texture(){

    free();
}

bool Texture::import(SDL_Renderer* renderer, std::string path){

    free();
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){

        std::cout << "Unable to load image! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if(newTexture == nullptr){

        std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    width = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    image = newTexture;
    return image != nullptr;
}

bool Texture::import(SDL_Renderer* renderer, std::string text, std::string path, int size, SDL_Color c){

    free();

    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), c);

    if(font == nullptr){

        std::cout << "Failed to load font! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    textSurface = TTF_RenderText_Solid(font, text.c_str(), c);

    if(textSurface == nullptr){

        std::cout << "Unable to render text to surface! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    width = textSurface->w;
    height = textSurface->h;

    newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if(newTexture == nullptr){

        std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);

    image = newTexture;
    return image != nullptr;
}

void Texture::free(){

    if(image != nullptr){

        width = 0;
        height = 0;
        SDL_DestroyTexture(image);
        image = nullptr;
    }
}

SDL_Texture* Texture::getImage() const{

    if(image == nullptr){

        std::cout << "Error! Tried to access image of an uninitialized texture!" << std::endl;
        return nullptr;
    }

    return image;
}

int Texture::getWidth() const{

    return width;
}

int Texture::getHeight() const{

    return height;
}
