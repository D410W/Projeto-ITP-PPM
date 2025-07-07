#include <iostream>
#include <string>
#include <cmath>

#include <random>
#include <ctime>

#include "includes/header.hpp"

int main(){
  std::srand(std::time(0));
  
  int n = 8;

  stc::ImageP2 mapa(std::pow(2, n)+1, std::pow(2, n)+1);
  mapa.addDiamSquare(n, 16, 2, 1);
  
  stc::Paleta pallet;
  pallet.read("pal.txt");
  
  stc::ImageP3 imagem(std::pow(2, n)+1, std::pow(2, n)+1);
  imagem.fromImageP2(mapa, pallet);
  
  imagem.write("imageColor.ppm");

  return 0;
}
