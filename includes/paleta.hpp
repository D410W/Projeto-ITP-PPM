#pragma once

#include <string>
#include <fstream>
#include <algorithm>

#include "cor.hpp"

namespace stc {

  class Paleta {
  private:
    int quantidade;
    Cor cores[100];
    int valores[100];
    // ----------------
    void trocar(int pos1, int pos2){
      if(pos1 < 0 or pos2 < 0) throw std::invalid_argument("Posiçao negativa na troca de cores de Paleta");
      
      std::swap(this->cores[pos1], this->cores[pos2]);
      std::swap(this->valores[pos1], this->valores[pos2]);
    }
  public:
    Paleta() : quantidade(0) {} // inicializador vazio
    Paleta(int newQtd, std::initializer_list<Cor> newCores, std::initializer_list<int> newValores) { // inicializador pronto
      quantidade = newQtd;
      
      int i = 0;
      for (const auto& c : newCores) cores[i++] = c;
      
      i = 0;
      for (const auto& v : newValores) valores[i++] = v;
    }
    // ----------------
    void adicionar(Cor newCor, int newValor){ // adicionar uma cor
      for(int i = 0; i < this->quantidade; i++){
        if(this->valores[i] > newValor){
          
          for(int j = this->quantidade - 1; j >= i; j--){
            this->trocar(j+1, j);
          }
          
          this->valores[i] = newValor;
          this->cores[i] = newCor;
          
          break;
        }
      }
      quantidade++;
    }
    // ----------------
    void remover(int pos){ // remover a cor na posiçao
      for(int i = pos; i < this->quantidade; i++){
        this->trocar(i, i+1);
      }
      quantidade--;
    }
    // ----------------
    Cor getCor(int thisValor){
      for(int i = 0; i < quantidade; i++){
        if(thisValor < valores[i]) return cores[i];
      }
      return {0,0,0};
    }
    // ----------------
    int getQtd(){
      return this->quantidade;
    }
    // ----------------
    std::string printar(){ // funçao de debug
      std::string toOut = "Quantidade de cores: " + std::to_string(quantidade) + "\nValor - (r, g, b):\n";
      for(int i = 0; i < quantidade; i++){
        toOut += std::to_string(valores[i]) + " - "
            "" + std::to_string(cores[i].r) + ", " +
                  std::to_string(cores[i].g) + ", " +
                  std::to_string(cores[i].b) + "\n";
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
