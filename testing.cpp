#include <iostream>
#include <string>

#include "includes/header.hpp"

int main(){

  // stc::Paleta thispaleta( 2, { {250,0,0},{0,250,0} }, { 100,200 } );

  // thispaleta.adicionar({0,0,255}, 205);

  // std::cout << (int)thispaleta.getCor(99).r << '\n';

  // thispaleta.read("pal.txt");

  // std::cout << thispaleta.printar();

  stc::ImageP3 imagem(30,30);
  
  stc::Cor thisPixel = imagem.getPixel(2,2);
  
  std::cout << (int)thisPixel.r << ' ' << (int)thisPixel.g << ' ' << (int)thisPixel.b << '\n';
  
  imagem.setPixel(2, 2, stc::Cor(200,180,160));
  
  thisPixel = imagem.getPixel(2,2);
  
  std::cout << (int)thisPixel.r << ' ' << (int)thisPixel.g << ' ' << (int)thisPixel.b << '\n';

  std::string fileName = "teste.ppm";

  imagem.write(fileName);

  return 0;
}
