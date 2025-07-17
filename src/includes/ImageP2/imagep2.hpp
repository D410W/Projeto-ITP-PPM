#pragma once

#include <string>
#include <filesystem>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>

#include "../cor.hpp"

namespace stc {
  class ImageP2 { // alocaçao dinamica de um array[linhas*colunas]
  private:
    int height, width;
    unsigned char *pixels = nullptr;
    unsigned char maxValue = 255;
    
    void deepCopy(const ImageP2& other); // helper function for deep copying
    
  public:
    // initializer methods
    ImageP2() : height(0), width(0), maxValue(255), pixels(nullptr) {}

    ImageP2(int w, int h); // inicializador apenas com largura e altura

    ImageP2(int w, int h, int newMax); // init. com largura, altura e valor max.
    // copy methods
    ImageP2(const ImageP2& other) : pixels(nullptr) { // copy initializer ()
      this->deepCopy(other);
    }
    
    ImageP2& operator=(const ImageP2& other); // copy assignment =
    // destructor
    ~ImageP2(){
      delete[] this->pixels;
      this->pixels = nullptr;
    }
    // ------------------
    int getWidth(){ return this->width; }
    int getHeight(){ return this->height; }
    int getMaxVal(){ return this->maxValue; }
    // ------------------
    unsigned char getValue(int x, int y){
      return this->pixels[y * this->width + x];
    }
    
    void setValue(int x, int y, unsigned char newValue){
      this->pixels[y * this->width + x] = newValue;
    }
    // ------------------
    void write(const std::string &fileName);
    // ------------------
    void read(const std::string &fileName);
    // ------------------
    void addDiamSquare(int n, double rough, double ratio, double weight);
    // ------------------
    void amplify();
    // ------------------
  };
}
