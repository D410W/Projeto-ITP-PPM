#include <iostream>
#include <string>

#include "includes/header.hpp"

int main(){

  stc::ImageP2 mapa(30,20);
  
  mapa.read("out/teste.ppm");
  
  std::cout << (int)mapa.getValue(2,2) << ' ' << mapa.getMaxVal() << ' ' << mapa.getWidth() << '\n';

  return 0;
}
