#include <iostream>
#include <string>
#include <cmath>

#include <random>
#include <ctime>

#include "includes/header.hpp"

int main(){
  std::srand(std::time(0));
  
  int n;
  double rough;
  std::cin >> n >> rough;

  stc::ImageP2 mapa((1 << n) + 1, (1 << n)+ 1);
  
  mapa.addDiamSquare(n, rough, 1);
  
  mapa.write("diamond.ppm");

  return 0;
}
