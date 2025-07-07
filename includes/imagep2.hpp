#pragma once

#include <string>
#include <filesystem>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>

#include "cor.hpp"

namespace stc {
  class ImageP2 { // alocaçao dinamica de um array[linhas*colunas]
  private:
    int height, width;
    unsigned char *pixels = nullptr;
    unsigned char maxValue = 255;
    
    void deepCopy(const ImageP2& other) { // helper function for deep copying
        height = other.height;
        width = other.width;
        maxValue = other.maxValue;
        if (other.pixels) { // other.pixels != nullptr
            pixels = new unsigned char[width * height];
            std::copy(other.pixels, other.pixels + (width * height), pixels);
        } else { // other.pixels == nullptr
            pixels = nullptr;
        }
    }
  public:
    // initializer methods
    ImageP2(int w, int h) : height(h), width(w), maxValue(255) { // inicializador apenas com largura e altura
       if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Largura e altura devem ser positivas.");
      }
      this->pixels = new unsigned char[w * h];
    }
    ImageP2(int w, int h, int newMax) : height(h), width(w), maxValue(newMax) { // init. com largura, altura e valor max.
      if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Largura e altura devem ser positivas.");
      }
      this->pixels = new unsigned char[w * h];
    }
    // copy methods
    ImageP2(const ImageP2& other) : pixels(nullptr) { // copy initializer ()
        deepCopy(other);
    }
    ImageP2& operator=(const ImageP2& other){ // copy assignment=
        if(this == &other){
            return *this;
        }

        delete[] pixels;
        pixels = nullptr;

        deepCopy(other);

        return *this;
    }
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
      
      delete[] this->pixels;
      this->pixels = new unsigned char[w*h];
      
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
    void setValue(int x, int y, unsigned char newValue){
      this->pixels[y * this->width + x] = newValue;
    }
    // ------------------
    void addDiamSquare(int n, double rough, double weight){
      if(n > 13 || n < 0){
        throw std::invalid_argument("Valor de n \'perigoso\' na funçao Diamond-Square.");
      }
      int patternLength = (1 << n) + 1;
      
      std::vector<std::vector<unsigned char>> values(patternLength, std::vector<unsigned char>(patternLength));
      
      for(int i = 0; i < patternLength; i++){
        for(int j = 0; j < patternLength; j++){
          values[i][j] = 0;
        }
      }
      
      values[0][0] = std::rand()%256; // corners are set random.
      values[0][patternLength-1] = std::rand()%256;
      values[patternLength-1][0] = std::rand()%256;
      values[patternLength-1][patternLength-1] = std::rand()%256;
      
      int currx, curry, step;
      int currSideSteps, halfSide; // represents 2^ni and 2^(ni-1)
      for(int ni = 1; ni < n+1; ni++){
        currx = 0, curry = 0;
        step = (1 << (n-ni)); // distance from one point to another at the ni-th step.
        currSideSteps = (1 << ni); // represents 2^ni
        halfSide = (1 << (ni - 1)); // represents 2^(ni-1)
        // diamond
        for(int i = 0; i < halfSide; i++){
          for(int j = 0; j < halfSide; j++){
            int toSet = 0;
            
            toSet += values[2*i*step][2*j*step]; // all 4 corners
            toSet += values[2*i*step][2*(j+1)*step];
            toSet += values[2*(i+1)*step][2*j*step];
            toSet += values[2*(i+1)*step][2*(j+1)*step];
            toSet /= 4;
            toSet += ( std::rand()%33 - 16 )*rough;
            
            values[step + 2*i*step][step + 2*j*step] = std::clamp(toSet, 0, 255);
          }
        }
        // square
        for(int id = 0; id < currSideSteps + 1; id++){
          int i = id*step;
          for(int j = (id%2 == 0 ? step : 0); j < patternLength; j += 2*step){
            int toSet = 0;
            int sums = 0;
            
            if(i > 0){
              toSet += values[i - step][j];
              sums++;
            }
            if(i < patternLength - 1){
              toSet += values[i + step][j];
              sums++;
            }
            if(j > 0){
              toSet += values[i][j - step];
              sums++;
            }
            if(j < patternLength - 1){
              toSet += values[i][j + step];
              sums++;
            }
            toSet /= sums;
            toSet += ( std::rand()%33 - 16 )*rough; // from -16 to 16
            
            values[i][j] = std::clamp(toSet, 0, 255);
          }
        }
        
      }
      // return values
      for(int i = 0; i < std::min(patternLength, this->width); i++){
        for(int j = 0; j < std::min(patternLength, this->height); j++){
          this->pixels[j*(this->width) + i] = values[i][j]*weight;
        }
      }
      
      return;
    }
    // ------------------
  };
}
