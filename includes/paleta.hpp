#pragma once

#include <string>
#include <fstream>

#include "cor.hpp"

namespace stc {

  class Paleta {
  private:
    int quantidade;
    Cor cores[100];
    int valores[100];
  public:
    Paleta() : quantidade(0) {} // inicializador vazio
    // ----------------
    Paleta(int newQtd, std::initializer_list<Cor> newCores, std::initializer_list<int> newValores) { // inicializador pronto
      quantidade = newQtd;
      
      int i = 0;
      for (const auto& c : newCores) cores[i++] = c;
      
      i = 0;
      for (const auto& v : newValores) valores[i++] = v;
    }
    // ----------------
    void adicionar(Cor newCor, int newValor){ // adicionar uma cor no final
      cores[quantidade] = newCor;
      valores[quantidade] = newValor;
      quantidade++;
    }
    // ----------------
    Cor getCor(int thisValor){
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
    void write(std::string dir){
      std::ofstream file(dir);

      file << quantidade << '\n';

      for(int i = 0; i < quantidade; i++){
        file << valores[i] << ' ' << (int)cores[i].r << ' ' << (int)cores[i].g << ' ' << (int)cores[i].b << '\n';
      }

      file.flush();
      file.close();
    }
    // ----------------
    void read(std::string dir){
      std::ifstream file(dir);

      if(!file.is_open()){
        throw std::runtime_error("Arquivo \'" + dir + "\' nao encontrado.");
      }
      
      file >> quantidade;

      int r, g, b;
      for(int i = 0; i < quantidade; i++){
        file >> valores[i] >> r >> g >> b;
        cores[i].r = static_cast<unsigned char>(r);
        cores[i].g = static_cast<unsigned char>(g);
        cores[i].b = static_cast<unsigned char>(b);
      }

      file.close();
    }
    // ----------------
  };
}
