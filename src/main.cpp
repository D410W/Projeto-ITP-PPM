#include <iostream>
#include <string>
#include <cmath>

#include <random>
#include <ctime>

#include "includes/header.hpp"

std::string p2Name = "Empty";
stc::ImageP2 p2;

std::string p3Name = "Empty";
stc::ImageP3 p3;

std::string palName = "Empty";
stc::Paleta pal;

void alterarP2(){
  std::cout << "\nImageP2 - " << p2Name << "\n";
  std::cout << "\n [1] Importar arquivo \n [2] Exportar para arquivo \n [3] Criar nova imagem \n"
            << " [4] Aplicar Diamond-Square noise \n [5] Voltar\n";
  
  int op;
  std::cin >> op;
  
  switch(op){
  case 1: {
    std::cout << "Caminho do arquivo: ";
  
    std::string theFile = "";
    std::cin >> theFile;
    
    p2Name = theFile;
    
    p2.read(theFile);
    break;
  }
  case 2: {
    std::cout << "Nome do arquivo: out/";
    
    std::string theFile = "";
    std::cin >> theFile;
    
    p2.write(theFile);
    break;
  }
  case 3: {
    std::cout << "Insira largura e altura: ";
    
    int l, a;
    std::cin >> l >> a;
    p2 = stc::ImageP2(l,a);
    
    p2Name = "Nova Imagem P2";
    
    break;
  }
  case 4: {
    std::cout << "Insira 'n', 'roughness' e 'ratio': ";
    
    int n, rough, ratio;
    std::cin >> n >> rough >> ratio;
    
    p2.addDiamSquare(n, rough, ratio, 1);
    
    break;
  }
  case 5:
    break;
  }
  std::cout << "\n\n------------------\n\n";
}
void alterarP3(){
  std::cout << "\nImageP3 - " << p3Name << "\n";
  std::cout << "\n [1]  \n [2] Exportar para arquivo \n [3] Criar a partir de P2 e Paleta \n"
            << " [4] Aplicar sombreamento a partir de P2 \n [5] Voltar\n";
  
  int op;
  std::cin >> op;
  
  switch(op){
  case 1: {
    // std::cout << "Caminho do arquivo: ";
  
    // std::string theFile = "";
    // std::cin >> theFile;
    
    // p3Name = theFile;
    
    // p3.read(theFile);
    break;
  }
  case 2: {
    std::cout << "Nome do arquivo: out/";
    
    std::string theFile = "";
    std::cin >> theFile;
    
    p3.write(theFile);
    break;
  }
  case 3: {
    p3 = stc::ImageP3(p2.getWidth(), p2.getHeight());
    p3.fromImageP2(p2, pal);
    
    p3Name = "Nova Imagem P3";
    
    break;
  }
  case 4: {
    std::cout << "Digite a intensidade do sombreamento, e '1' ou '0' se deseja que seja proporcional, ou nao a diferença de altura.\n";
    
    int intens;
    int prop;
    
    std::cin >> intens >> prop;
    
    p3.addShadow(p2, intens, (bool)prop);
    
    break;
  }
  case 5:
    break;
  }
  std::cout << "\n\n------------------\n\n";
}
void alterarPal(){
  std::cout << "\nPaleta - " << palName << "\n"
            << pal.printar();
  std::cout << "\n [1] Importar arquivo \n [2] Exportar para arquivo \n [3] Adicionar cor \n"
            << " [4] Remover cor \n [5] Voltar\n";
  
  int op;
  std::cin >> op;
  
  switch(op){
  case 1: {
    std::cout << "Caminho do arquivo: ";
  
    std::string theFile = "";
    std::cin >> theFile;
    
    palName = theFile;
    
    pal.read(theFile);
    break;
  }
  case 2: {
    std::cout << "Nome do arquivo: ";
    
    std::string theFile = "";
    std::cin >> theFile;
    
    pal.write(theFile);
    break;
  }
  case 3:
    std::cout << "Insira o valor, e a cor em 'R', 'G' e 'B': ";
    
    int val, r, g, b;
    std::cin >> val >> r >> g >> b;
    
    pal.adicionar(stc::Cor(r,g,b), val);
    break;
  case 4:
    std::cout << "Insira a posiçao da cor que sera removida: ";
    
    int pos;
    std::cin >> pos;
    
    pal.remover(pos-1);
    break;
  case 5:
    break;
  }
  std::cout << "\n\n------------------\n\n";
}

int main(){
  std::srand(std::time(0));
  
  // std::cout << "Insira 'n' para o tamanho das imagens quadradas em '2^n + 1'\n";
  
  // int n;
  // std::cin >> n;
  
  while(true){
    std::cout << "[1] ImageP2 --- \n Nome: " << p2Name << "\n Tamanho: " << p2.getWidth() << ", " << p2.getHeight()
              << "\n\n"
              << "[2] ImageP3 --- \n Nome: " << p3Name << "\n Tamanho: " << p3.getWidth() << ", " << p3.getHeight()
              << "\n\n"
              << "[3] Paleta --- \n Nome: " << palName << "\n Tamanho: " << pal.getQtd()
              << "\n\n"
              << "[4] Fechar programa\n\n";
              
    std::cout << "Escolha a imagem que deseja modificar/exportar:\n";
    
    int op;
    std::cin >> op;
    
    switch(op){
    case 1:
      std::cout << "\n------------------\n";
      alterarP2();
      break;
    case 2:
      std::cout << "\n------------------\n";
      alterarP3();
      break;
    case 3:
      std::cout << "\n------------------\n";
      alterarPal();
      break;
    case 4:
      return 0;
    }
    
  }
  
  return 0;
}
