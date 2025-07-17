#pragma once

#include <string>
#include <fstream>
#include <algorithm>

#include "../cor.hpp"

namespace stc {
  /**
   * @brief Representa um conjunto de intervalos de cores.
   *
   * Utilizada na conversao de gradiente para Cor RGB.
   *
   * Ex.: Conversao de um mapa de altitudes para uma imagem
   * colorida, de acordo com os intervalos: \n
   * De 0 ate valores[0] = cores[0], \n
   * De valores[0] ate valores[1] = cores[1], \n
   * Etc...
   */
  class Paleta {
  private:
    int quantidade;
    Cor cores[100];
    int valores[100];
    // ----------------
    void trocar(int pos1, int pos2);
    
  public:
    /**
     * @brief Construtor padrao.
     *
     * Inicializa a paleta com 0 cores. 
     */
    Paleta() : quantidade(0) {} // inicializador vazio
    
    /**
     * @brief Construtor com parametros.
     *
     * Inicializa a paleta com as cores e valores especificados.
     * @param newQtd Quantidade de pares (Cor, valor) da paleta.
     * @param newCores Array de inicializaçao das cores respectivas.
     * @param newValores Array de inicializaçao dos valores respectivos.
     */
    Paleta(int newQtd, std::initializer_list<Cor> newCores, std::initializer_list<int> newValores) { // inicializador pronto
      quantidade = newQtd;
      
      int i = 0;
      for(const auto& c : newCores) cores[i++] = c;
      
      i = 0;
      for(const auto& v : newValores) valores[i++] = v;
    }
    // ----------------
    /**
     * @brief Metodo para inserir uma Cor.
     *
     * Insere, na paleta, uma Cor com um valor especificado.
     * @param newCor Cor inserida.
     * @param newValor Valor correspondente.
     */
    void adicionar(Cor newCor, int newValor); // adicionar uma cor
    // ----------------
    /**
     * @brief Metodo para remover uma Cor.
     *
     * Remove, da paleta, uma Cor com um valor especificado.
     * @param pos Posiçao do par (Cor, valor) para ser removida, começando em 1.
     */
    void remover(int pos); // remover a cor na posiçao
    // ----------------
    /**
     * @brief Metodo para consultar a Cor no intervalo correspondente.
     *
     * Retorna a Cor, cujo intervalo contem o valor dado.
     *
     * Ex.: \n
     * De 0 ate valores[0] = cores[0], \n
     * De valores[0] ate valores[1] = cores[1], \n
     * Etc...
     *
     * @param thisValor Valor especificado para que seja retornada a Cor correspondente.
     * @return Retorna a Cor correspondente ao valor dado.
     */
    Cor getCor(int thisValor);
    // ----------------
    /**
     * @brief Consulta a quantidade de cores da Paleta.
     * @return Retorna this->quantidade.
     */
    int getQtd(){
      return this->quantidade;
    }
    // ----------------
    /**
     * @brief Metodo para consultar o estado da Paleta.
     *
     * Retorna uma string com os dados da Paleta. 
     * Criada com o intuito de ser emitida no terminal.
     *
     * @return String com informaçoes da Paleta.
     */
    std::string printar(); // funçao de descriçao
    // ----------------
    /**
     * @brief Metodo para exportar a paleta.
     *
     * Exporta os dados da Paleta para um arquivo .txt especificado.
     *
     * @param dir Caminho do arquivo para exportar, no formato:
     * "paletas/paletadecores.txt"
     */
    void write(std::string dir);
    // ----------------
    /**
     * @brief Metodo para importar uma paleta.
     *
     * Importa os dados da Paleta a partir de um arquivo .txt especificado.
     *
     * @param dir Caminho do arquivo para importar, no formato:
     * "paletas/paletadecores.txt"
     * 
     * @return Retorna 'true' se a leitura foi bem-sucedida, 'false' caso contrario.
     */
    bool read(std::string dir);
    // ----------------
  };
}
