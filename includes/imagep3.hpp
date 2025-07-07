#pragma once

#include <string>
#include <filesystem>

#include "cor.hpp"
#include "imagep2.hpp"

namespace stc {
  class ImageP3 { // alocaçao dinamica de um array[linhas*colunas]
  private:
    int height, width;
    Cor *pixels = nullptr;
    unsigned char maxCol = 255;
    
    void deepCopy(const ImageP3& other) { // helper function for deep copying
        this->height = other.height;
        this->width = other.width;
        this->maxCol = other.maxCol;
        if (other.pixels) { // other.pixels != nullptr
            this->pixels = new Cor[width * height];
            std::copy(other.pixels, other.pixels + (this->width * this->height), this->pixels);
        } else { // other.pixels == nullptr
            this->pixels = nullptr;
        }
    }
  public:
    ImageP3() : height(0), width(0), maxCol(255), pixels(nullptr) {}
    ImageP3(int w, int h) : height(h), width(w), maxCol(255), pixels(new Cor[h*w]) {} // largura (x) e altura (y)
    ImageP3(int w, int h, int newMax) : height(h), width(w), maxCol(newMax), pixels(new Cor[h*w]) {}
    ImageP3& operator=(const ImageP3& other){ // copy assignment=
        if(this == &other){
            return *this;
        }

        delete[] pixels;
        pixels = nullptr;

        deepCopy(other);

        return *this;
    }

    ~ImageP3(){
      delete[] pixels;
    }
    // ------------------
    int getWidth(){ return this->width; }
    int getHeight(){ return this->height; }
    int getMaxCol(){ return this->maxCol; }
    // ------------------    
    void write(const std::string &fileName){
      if(!( std::filesystem::exists("out") && std::filesystem::is_directory("out") )){ // guardar arquivos na pasta 'out'
        std::filesystem::create_directory("out");
      }
      
      std::ofstream outputFile("out/"+fileName);

      outputFile << "P3\n" << this->width << ' ' << this->height << "\n" + std::to_string(this->maxCol) + "\n";
      for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
          outputFile << (int)this->pixels[i*width + j].r << ' ' << (int)this->pixels[i*width + j].g << ' ' << (int)this->pixels[i*width + j].b;

          if(j == this->width-1) outputFile << '\n';
          else outputFile << ' ';
        }
      }
      
      outputFile.close();
      return;
    }
    // ------------------
    Cor getPixel(int x, int y){
      return this->pixels[y * this->width + x];
    }
    // ------------------
    void setPixel(int x, int y, const Cor &newColor){
      this->pixels[y * this->width + x] = newColor;
    }
    // ------------------
    void fromImageP2(ImageP2 &heightMap, Paleta &pallet){
      if(this->height != heightMap.getHeight() or this->width != heightMap.getWidth()){
        throw std::invalid_argument("ImageP3 e ImageP2 possuem dimensoes diferentes.");
      }
      
      int mapH = heightMap.getHeight(), mapW = heightMap.getWidth();
      for(int i = 0; i < mapW; i++){
        for(int j = 0; j < mapH; j++){
          this->setPixel( i, j, pallet.getCor( heightMap.getValue(i,j) ) );
        }
      }
    }
    // ------------------
  };
}
