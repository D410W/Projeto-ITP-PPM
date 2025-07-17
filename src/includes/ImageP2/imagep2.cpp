#include <string>
#include <filesystem>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>

#include "../cor.hpp"
#include "imagep2.hpp"

namespace stc {
// private methods:
  void ImageP2::deepCopy(const ImageP2& other) { // helper function for deep copying
    this->height = other.height;
    this->width = other.width;
    this->maxValue = other.maxValue;
    if (other.pixels) { // other.pixels != nullptr
      this->pixels = new unsigned char[width * height];
      std::copy(other.pixels, other.pixels + (this->width * this->height), this->pixels); // inicio do array, fim do array, array do outro
    } else { // other.pixels == nullptr
      this->pixels = nullptr;
    }
  }
// public methods:
  ImageP2::ImageP2(int w, int h) : height(h), width(w), maxValue(255) { // inicializador apenas com largura e altura
    if (w <= 0 || h <= 0) {
      throw std::invalid_argument("Largura e altura devem ser positivas.");
    }
    this->pixels = new unsigned char[w * h]();
  }

  ImageP2::ImageP2(int w, int h, int newMax) : height(h), width(w), maxValue(newMax) { // init. com largura, altura e valor max.
    if (w <= 0 || h <= 0) {
      throw std::invalid_argument("Largura e altura devem ser positivas.");
    }
    this->pixels = new unsigned char[w * h]();
  }
  // ------------------
  ImageP2& ImageP2::operator=(const ImageP2& other){ // copy assignment =
    if(this == &other){
      return *this;
    }

    delete[] this->pixels;
    this->pixels = nullptr;

    this->deepCopy(other);

    return *this;
  }
  // ------------------
  void ImageP2::write(const std::string &fileName){
    if(!( std::filesystem::exists("out") && std::filesystem::is_directory("out") )){ // guardar arquivos na pasta 'out'
      std::filesystem::create_directory("out");
      std::cout << "Criando diretorio de saida 'out/'." << std::endl;
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
  void ImageP2::read(const std::string &fileName){
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
  void ImageP2::addDiamSquare(int n, double rough = 1, double ratio = 1, double weight = 1){
    if(n > 13 || n < 0){
      throw std::invalid_argument("Valor de n \'perigoso\' na funçao Diamond-Square.");
    }
    int patternLength = (1 << n) + 1;
    
    unsigned char **values = new unsigned char *[patternLength];
    
    for(int i = 0; i < patternLength; i++){
      values[i] = new unsigned char[patternLength];
    }
    
    // std::vector<std::vector<unsigned char>> values(patternLength, std::vector<unsigned char>(patternLength));
    
    for(int i = 0; i < patternLength; i++){
      for(int j = 0; j < patternLength; j++){
        values[i][j] = 0;
      }
    }
    
    values[0][0] = std::rand()%256; // corners are set random.
    values[0][patternLength-1] = std::rand()%256;
    values[patternLength-1][0] = std::rand()%256;
    values[patternLength-1][patternLength-1] = std::rand()%256;
    
    int step;
    int currSideIterations, halfSideIterations; // represents 2^ni and 2^(ni-1)
    for(int ni = 1; ni <= n; ni++){
      step = (1 << (n-ni)); // distance from one point to another at the ni-th step.
      currSideIterations = (1 << ni); // represents 2^ni
      halfSideIterations = (1 << (ni - 1)); // represents 2^(ni-1)
      // diamond
      for(int i = 0; i < halfSideIterations; i++){
        for(int j = 0; j < halfSideIterations; j++){
          int toSet = 0;
          
          int uppLeftCornerx = 2*i*step;
          int uppLeftCornery = 2*j*step;
          
          toSet += values[uppLeftCornerx][uppLeftCornery]; // all 4 corners
          toSet += values[uppLeftCornerx][uppLeftCornery + 2*step];
          toSet += values[uppLeftCornerx + 2*step][uppLeftCornery];
          toSet += values[uppLeftCornerx + 2*step][uppLeftCornery + 2*step];
          toSet /= 4;
          toSet += ( std::rand()%33 - 16 )*rough; // from -16*rough to 16*rough
          
          values[step + uppLeftCornerx][step + uppLeftCornery] = std::clamp(toSet, 0, 255);
        }
      }
      // square
      for(int id = 0; id < currSideIterations + 1; id++){
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
      
      rough /= ratio;
    }
    // return values
    for(int i = 0; i < std::min(patternLength, this->width); i++){
      for(int j = 0; j < std::min(patternLength, this->height); j++){
        this->setValue( i, j, values[i][j]*weight );
      }
    }
    
    for(int i = 0; i < patternLength; i++){
      delete[] values[i];
    }
    delete[] values;
    
    return;
  }
  // ------------------
  void ImageP2::amplify(){
    int minimumValue = 256, maximumValue = -1;
    
    for(int i = 0; i < this->width; i++){
      for(int j = 0; j < this->height; j++){
        if(this->getValue(i, j) < minimumValue) minimumValue = this->getValue(i, j);
        if(this->getValue(i, j) > maximumValue) maximumValue = this->getValue(i, j);
      }
    }
    
    double newRatio = 255.0/(double)(maximumValue-minimumValue);

    for(int i = 0; i < this->width; i++){
      for(int j = 0; j < this->height; j++){
        // std::cout << (int)this->getValue(i, j) << '\n';
        this->setValue( i, j, (int)( (this->getValue(i, j)-minimumValue )*newRatio) );
        // std::cout << (int)this->getValue(i, j) << '\n';
      }
    }
  }
  // ------------------
}
