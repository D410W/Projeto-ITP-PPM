#include <iostream>
#include <string>

#include "includes/header.hpp"

void drawBox(stc::ImageP3 &imagem, int x0, int y0, int x1, int y1, stc::Cor newColor){
  for(int x = x0; x <= x1; x++){
    for(int y = y0; y <= y1; y++){
      imagem.setPixel(x, y, newColor);
    }
  }
}

int main(){

  stc::ImageP3 bandeira(30,20);
  
  drawBox(bandeira, 0, 0, 9, 19, stc::Cor(255,0,0));
  drawBox(bandeira, 10, 0, 19, 19, stc::Cor(255,255,255));
  drawBox(bandeira, 20, 0, 29, 19, stc::Cor(0,0,255));
  
  bandeira.write("teste.ppm");

  return 0;
}
