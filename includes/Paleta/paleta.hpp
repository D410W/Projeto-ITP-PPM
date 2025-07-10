#pragma once

#include <string>
#include <fstream>
#include <algorithm>

#include "../cor.hpp"

namespace stc {

  class Paleta {
  private:
    int quantidade;
    Cor cores[100];
    int valores[100];
    // ----------------
    void trocar(int pos1, int pos2);
    
  public:
    Paleta() : quantidade(0) {} // inicializador vazio
    Paleta(int newQtd, std::initializer_list<Cor> newCores, std::initializer_list<int> newValores) { // inicializador pronto
      quantidade = newQtd;
      
      int i = 0;
      for(const auto& c : newCores) cores[i++] = c;
      
      i = 0;
      for(const auto& v : newValores) valores[i++] = v;
    }
    // ----------------
    void adicionar(Cor newCor, int newValor); // adicionar uma cor
    // ----------------
    void remover(int pos); // remover a cor na posiçao
    // ----------------
    Cor getCor(int thisValor);
    // ----------------
    int getQtd(){
      return this->quantidade;
    }
    // ----------------
    std::string printar(); // funçao de descriçao
    // ----------------
    void write(std::string dir);
    // ----------------
    void read(std::string dir);
    // ----------------
  };
}
