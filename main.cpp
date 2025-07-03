#include <fstream>
#include <iostream>
#include "classes.hpp"

int main(){

  stc::Paleta thispaleta( 2, { {255,0,0},{0,255,0} }, { 100,200 } );

  thispaleta.adicionar({0,0,255}, 205);

  std::cout << thispaleta.atribuir(105).r << '\n';

  std::cout << thispaleta.printar();

  return 0;
}
