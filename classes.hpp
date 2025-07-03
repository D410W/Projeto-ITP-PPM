#pragma once

#include <string>
#include <fstream>

namespace stc {

  struct Cor {
    unsigned char r = 0, g = 0, b = 0;
  };

  class Paleta {
  private:
    int quantidade;
    Cor cores[100];
    int valores[100];
  public:
    Paleta(){ // inicializador vazio
      quantidade = 0;
    }
    // ----------------
    Paleta(int newQtd, std::initializer_list<Cor> cs, std::initializer_list<int> vs) { // inicializador pronto
      quantidade = newQtd;
      
      int i = 0;
      for (const auto& c : cs) cores[i++] = c;
      
      i = 0;
      for (const auto& v : vs) valores[i++] = v;
    }
    // ----------------
    void adicionar(Cor newCor, int newValor){ // adicionar uma cor no final
      cores[quantidade] = newCor;
      valores[quantidade] = newValor;
      quantidade++;
    }
    // ----------------
    Cor consultarCor(int thisValor){
      for(int i = 0; i < quantidade; i++){
        if(thisValor < valores[i]) return cores[i];
      }
      return {0,0,0};
    }
    // ----------------
    std::string printar(){ // funçao de debug
      std::string toOut = "Quantidade de cores: " + std::to_string(quantidade) + "\nCores:\n";
      for(int i = 0; i < quantidade; i++){
        toOut += "{" + std::to_string(cores[i].r) + " " +
                  std::to_string(cores[i].g) + " " +
                  std::to_string(cores[i].b) + "}\n";
      }

      toOut += "Valores:\n";
      for(int i = 0; i < quantidade; i++){
        toOut += std::to_string(valores[i]) + "\n";
      }

      return toOut;
    }
    // ----------------
    void writePaleta(std::string ){

    }
    // ----------------
    void readPaleta(std::string ){

    }

  };
  
}
