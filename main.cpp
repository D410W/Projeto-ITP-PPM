#include <fstream>
#include <iostream>

#include "paleta.hpp"
#include "imagep3.hpp"

int main(){

  // stc::Paleta thispaleta( 2, { {250,0,0},{0,250,0} }, { 100,200 } );

  // thispaleta.adicionar({0,0,255}, 205);

  // std::cout << (int)thispaleta.getCor(99).r << '\n';

  // thispaleta.read("pal.txt");

  // std::cout << thispaleta.printar();

  stc::ImageP3 *imagem = new stc::ImageP3(30,30);

  (*imagem).exportf("teste");

  return 0;
}
