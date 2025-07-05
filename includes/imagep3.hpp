#pragma once

#include <string>
#include <filesystem>

#include "cor.hpp"

namespace stc {
  class ImageP3 {
  private:
    int height, width;
    Cor *pixels = nullptr;
    unsigned char maxCol = 255;
    
  public:
    ImageP3(int w, int h) : height(h), width(w), maxCol(255), pixels(new Cor[h*w]) {} // largura (x) e altura (y)
    ImageP3(int w, int h, int maxvalue) : height(h), width(w), maxCol(maxvalue), pixels(new Cor[h*w]) {}

    ~ImageP3(){
      delete[] pixels;
    }
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
  };
}
