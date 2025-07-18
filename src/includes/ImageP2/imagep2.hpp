#pragma once

#include <string>
#include <filesystem>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>

#include "../cor.hpp"

namespace stc {
  /**
   * @brief Representa uma imagem em tons de cinza.
   *
   * Armazena uma matriz de pixels cinzas com valores dentro do
   * intervalo [0, 255]. Pode também ser interpretada como
   * uma matriz de altitudes.\n
   * Contém altura, largura, e valor máximo.
   */
  class ImageP2 { // alocaçao dinamica de um array[linhas*colunas]
  private:
    int height, width;
    unsigned char *pixels = nullptr; // null pointer
    unsigned char maxValue = 255;
    
    /**
     * @brief Função auxiliar para cópias.
     *
     * Recebe os valores de outra 'ImageP2' e copia-os para si.
     * @param other Outra instância de 'ImageP2' para copiar os valores.
     */
    void deepCopy(const ImageP2& other); // helper function for deep copying
    
  public:
    // initializer methods
    /**
     * @brief Construtor padrão.
     */
    ImageP2() : height(0), width(0), maxValue(255), pixels(nullptr) {}

    /**
     * @brief Construtor com largura e altura.
     *
     * @param w Largura da matriz.
     * @param h Altura da matriz.
     */
    ImageP2(int w, int h); // inicializador apenas com largura e altura

    /**
     * @brief Construtor com largura, altura e valor máximo.
     *
     * Adiciona como parâmetro o valor máximo dos elementos da
     * matriz. Útil para exportação da imagem no formato PPM.
     *
     * @param w Largura da matriz.
     * @param h Altura da matriz.
     * @param newMax altura máxima 
     */
    ImageP2(int w, int h, int newMax); // init. com largura, altura e valor max.
    
    // copy methods
    /**
     * @brief Construtor de cópia.
     *
     * Inicializa uma 'ImageP2' com dados iguais aos de
     * outra 'ImageP2'.
     *
     * @param other Outra 'ImageP2' a ter os dados copiados.
     */
    ImageP2(const ImageP2& other) : pixels(nullptr) { // copy initializer ()
      this->deepCopy(other);
    }
    
    /**
     * @brief Operador de cópia.
     *
     * Modifica os dados da 'ImageP2' a esquerda, recebendo
     * os dados da 'ImageP2' a direita.
     *
     * @param other 'ImageP2' a ser copiada.
     */
    ImageP2& operator=(const ImageP2& other); // copy assignment = 
    
    // destructor
    /**
     * @brief Destrutor da 'ImageP2'.
     *
     * Desaloca a matriz de altitudes.
     */
    ~ImageP2(){
      delete[] this->pixels;
      this->pixels = nullptr;
    }
    // ------------------
    /**
     * @brief Método para consultar largura.
     *
     * Retorna a largura da 'ImageP2'.
     */
    int getWidth(){ return this->width; }
    /**
     * @brief Método para consultar altura.
     *
     * Retorna a altura da 'ImageP2'.
     */
    int getHeight(){ return this->height; }
    /**
     * @brief Método para consultar o valor máximo.
     *
     * Retorna o valor máximo da 'ImageP2'.
     */
    int getMaxVal(){ return this->maxValue; }
    // ------------------
    
    /**
     * @brief Método para consultar um valor.
     *
     * Retorna o valor da matriz na posição x,y dada,
     * ambas no intervalo de 0 até (largura - 1) ou
     * (altura - 1), respectivamente.
     * 
     * @param x Índice X da matriz, começando em 0.
     * @param y Índice Y da matriz, começando em 0.
     */
    unsigned char getValue(int x, int y){
      return this->pixels[y * this->width + x];
    }
    
    /**
     * @brief Método para mudar um valor.
     *
     * Modifica o valor da matriz na posição x,y dada,
     * ambas no intervalo de 0 até (largura - 1) ou
     * (altura - 1), respectivamente.
     * 
     * @param x Índice X da matriz, começando em 0.
     * @param y Índice Y da matriz, começando em 0.
     * @param newValue Valor cuja posição x,y receberá.
     */
    void setValue(int x, int y, unsigned char newValue){
      this->pixels[y * this->width + x] = newValue;
    }
    // ------------------
    /**
     * @brief Metodo para exportar a 'ImageP2'.
     *
     * Exporta os dados da 'ImageP2' para um arquivo especificado,
     * dentro da pasta 'out'. Recomenda-se utilizar o formato '.ppm'.
     *
     * @param fileName Caminho do arquivo para exportar, no formato:
     * "imagem.etc"
     */
    void write(const std::string &fileName);
    // ------------------
    /**
     * @brief Metodo para importar uma Imagem PPM P2.
     *
     * Importa os dados de um arquivo PPM tipo P2 a partir
     * de um arquivo .ppm especificado.
     *
     * @pre `fileName` Arquivo deve existir e estar no formato PPM tipo P2.
     *
     * @param fileName Caminho do arquivo para importar, no formato:
     * "imagem.ppm"
     * 
     * @return Retorna 'true' se a leitura foi bem-sucedida, 'false' caso contrario.
     */
    bool read(const std::string &fileName);
    // ------------------
    /**
     * @brief Metodo para adicionar noise Diamond-Square à 'ImageP2'.
     *
     * Gera uma imagem quadrada de acordo com `n`, para ter seus
     * valores de acordo com o algoritmo "Diamond-Square", e atualiza
     * a 'ImageP2' com os valores do algoritmo.
     *
     * @param n Valor de 'n' utilizado no comprimento da matriz
     * quadrada (2^n + 1).
     * @param rough Rugosidade da imagem. (recomenda-se 16 como padrão)
     * @param ratio Normalização da rugosidade. A cada iteração
     * do algoritmo "Diamond-Square", divide-se a rugosidade `rough` por uma
     * razão `ratio`. (recomenda-se 2 como padrão)
     * @param weight Opacidade da aplicação do noise gerado à 'ImageP2'.
     */
    void addDiamSquare(int n, double rough, double ratio, double weight);
    // ------------------
    /**
     * @brief Metodo para amplificar os valores da 'ImageP2'.
     *
     * Modifica todos os valores da matriz de valores, para que
     * o menor valor seja 0 e o maior valor seja 255, mantendo
     * a proporção original.
     */
    void amplify();
    // ------------------
  };
}
