#pragma once

#include <string>
#include <filesystem>

#include "../cor.hpp"
#include "../ImageP2/imagep2.hpp"
#include "../Paleta/paleta.hpp"

namespace stc {
  class ImageP3 { // alocaçao dinamica de um array[linhas*colunas]
  private:
    int height, width;
    Cor *pixels = nullptr;
    unsigned char maxCol = 255;
    
    void deepCopy(const ImageP3& other); // helper function for deep copying

  public:
    ImageP3() : width(0), height(0), maxCol(255), pixels(nullptr) {}

    ImageP3(int w, int h); // largura (x) e altura (y)

    ImageP3(int w, int h, int newMax);
    
    ImageP3(const ImageP3& other) : pixels(nullptr) { // copy initializer ()
      this->deepCopy(other);
    }

    ImageP3& operator=(const ImageP3& other); // copy assignment=
    
    ~ImageP3(){
      delete[] this->pixels;
      this->pixels = nullptr;
    }
    // ------------------
    int getWidth(){ return this->width; }
    int getHeight(){ return this->height; }
    int getMaxCol(){ return this->maxCol; }
    // ------------------
    Cor getPixel(int x, int y){
      return this->pixels[y * this->width + x];
    }
    
    void setPixel(int x, int y, const Cor &newColor){
      this->pixels[y * this->width + x] = newColor;
    }
    // ------------------    
    void write(const std::string &fileName);
    // ------------------
    void fromImageP2(ImageP2 &heightMap, Paleta &pallet);
    // ------------------
    void addShadow(ImageP2 p2, double intensity, bool proportional);
    // ------------------
  };
}
