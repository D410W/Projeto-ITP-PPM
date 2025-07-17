#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

#include <thread>
#include <chrono>

#include "../cor.hpp"
#include "paleta.hpp"

namespace stc {
// private methods:
  void Paleta::trocar(int pos1, int pos2){
    if(pos1 < 0 or pos2 < 0) throw std::invalid_argument("Posiçao negativa na troca de cores de Paleta");
    
    std::swap(this->cores[pos1], this->cores[pos2]);
    std::swap(this->valores[pos1], this->valores[pos2]);
  }
// public methods:
  void Paleta::adicionar(Cor newCor, int newValor){ // adicionar uma cor
    if( (quantidade == 0) or (newValor > this->valores[this->quantidade-1]) ){
    
      this->cores[this->quantidade] = newCor;
      this->valores[this->quantidade] = newValor;
      this->quantidade++;
      
      return;
    }
    
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
    this->quantidade++;
  }
  // ----------------
  void Paleta::remover(int pos){ // remover a cor na posiçao
    for(int i = pos; i < this->quantidade; i++){
      this->trocar(i, i+1);
    }
    quantidade--;
  }
  // ----------------
  Cor Paleta::getCor(int thisValor){
    for(int i = 0; i < quantidade; i++){
      if(thisValor < valores[i]) return cores[i];
    }
    return {0,0,0};
  }
  // ----------------
  std::string Paleta::printar(){ // funçao de descriçao
    std::string toOut = "Quantidade de cores: " + std::to_string(this->quantidade) + "\nValor - (r, g, b):\n";
    for(int i = 0; i < this->quantidade; i++){
      toOut += std::to_string(this->valores[i]) + " - "
          "" + std::to_string(this->cores[i].r) + ", " +
               std::to_string(this->cores[i].g) + ", " +
               std::to_string(this->cores[i].b) + "\n";
    }

    return toOut;
  }
  // ----------------
  void Paleta::write(std::string dir){
    std::ofstream file(dir);

    file << quantidade << '\n';

    for(int i = 0; i < quantidade; i++){
      file << valores[i] << ' ' << (int)cores[i].r << ' ' << (int)cores[i].g << ' ' << (int)cores[i].b << '\n';
    }

    file.flush();
    file.close();
  }
  // ----------------
  bool Paleta::read(std::string dir){
    std::ifstream file(dir);

    if(!file.is_open()){
      // throw std::runtime_error("Arquivo \'" + dir + "\' nao encontrado.");
      std::cout << "Arquivo \'" + dir + "\' nao encontrado." << '\n';
      std::this_thread::sleep_for(std::chrono::seconds(1));
      return false;
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
    return true;
  }
  // ----------------
}
