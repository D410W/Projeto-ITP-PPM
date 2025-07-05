#pragma once

#include <string>
#include <filesystem>

#include "cor.hpp"

namespace stc {
  class ImageP2 { // alocaçao dinamica de um array[linhas*colunas]
  private:
    int height, width;
    unsigned char *pixels = nullptr;
    unsigned char maxValue = 255;
    
  public:
    ImageP2(int w, int h) : height(h), width(w), maxValue(255), pixels(new unsigned char[w*h]) {} // largura (x) e altura (y)
    ImageP2(int w, int h, int newMax) : height(h), width(w), maxValue(newMax), pixels(new unsigned char[w*h]) {}

    ~ImageP2(){
      delete[] pixels;
    }
    // ------------------
    int getWidth(){ return this->width; }
    int getHeight(){ return this->height; }
    int getMaxVal(){ return this->maxValue; }
    // ------------------
    void write(const std::string &fileName){
      if(!( std::filesystem::exists("out") && std::filesystem::is_directory("out") )){ // guardar arquivos na pasta 'out'
        std::filesystem::create_directory("out");
      }
      
      std::ofstream outputFile("out/"+fileName);

      outputFile << "P2\n" << this->width << ' ' << this->height << "\n" + std::to_string(this->maxValue) + "\n";
      for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
          outputFile << (int)this->pixels[i*width + j];

          if(j == this->width-1) outputFile << '\n';
          else outputFile << ' ';
        }
      }
      
      outputFile.close();
      return;
    }
    // ------------------
    void read(const std::string &fileName){
      std::ifstream inputFile(fileName);

      std::string type;
      inputFile >> type; // P2
      
      if(type != "P2"){
        throw std::runtime_error("Arquivo nao identificado como PPM tipo P2.");
      }
      
      int value, w, h, mv;
      inputFile >> w >> h >> mv;
      
      this->width = w;
      this->height = h;
      this->maxValue = mv;
      
      for(int i = 0; i < (this->height * this->width); i++){
        inputFile >> value;
        this->pixels[i] = value;
      }
      
      inputFile.close();
      return;
    }
    // ------------------
    unsigned char getValue(int x, int y){
      return this->pixels[y * this->width + x];
    }
    // ------------------
    void setValue(int x, int y, unsigned char newValue){
      this->pixels[y * this->width + x] = newValue;
    }
    // ------------------
    void applyDiamSquare(int n, double rough, double weight){
    
    }
    // ------------------
  };
}
