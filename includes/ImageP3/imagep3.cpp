#include <string>
#include <filesystem>

#include "../cor.hpp"
#include "../ImageP2/imagep2.hpp"
#include "../Paleta/paleta.hpp"
#include "imagep3.hpp"

namespace stc {
// private methods:
  void ImageP3::deepCopy(const ImageP3& other) { // helper function for deep copying
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
// public methods:
  ImageP3& ImageP3::operator=(const ImageP3& other){ // copy assignment=
    if(this == &other){
      return *this;
    }

    delete[] pixels;
    pixels = nullptr;

    deepCopy(other);

    return *this;
  }
  // ------------------
  void ImageP3::write(const std::string &fileName){
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
  void ImageP3::fromImageP2(ImageP2 &heightMap, Paleta &pallet){
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
  void ImageP3::addShadow(ImageP2 p2, double intensity, bool proportional = true){
    for(int i = 1; i < this->width; i++){
      for(int j = 1; j < this->height; j++){
        int diff = p2.getValue(i-1, j-1) - p2.getValue(i, j);
        
        if(diff <= 0) continue;
        
        if(proportional){
          this->setPixel(i, j, this->getPixel(i, j) - diff*intensity );
        } else {
          this->setPixel(i, j, this->getPixel(i, j) - (int)intensity );
        }
      }
    } 
  }
  // ------------------
}
