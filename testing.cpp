#include <iostream>
#include <string>
#include <cmath>

#include <random>
#include <ctime>

#include "includes/header.hpp"

int main(){
  std::srand(std::time(0));
  
  int n;
  double rough, ratio;
  std::cin >> n >> rough >> ratio;

  stc::ImageP2 mapa(std::pow(2, n)+1, std::pow(2, n)+1);
  
  mapa.addDiamSquare(n, rough, ratio, 1);
  
  mapa.write("diamond.ppm");

  return 0;
}
