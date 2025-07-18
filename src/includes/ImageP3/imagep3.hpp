#pragma once

#include <string>
#include <filesystem>

#include "../cor.hpp"
#include "../ImageP2/imagep2.hpp"
#include "../Paleta/paleta.hpp"

namespace stc {
  /**
   * @brief Representa uma imagem colorida no formato PPM P3.
   *
   * Armazena uma matriz de pixels coloridos (Cor) com valores dentro do
   * intervalo [0, 255] para cada componente RGB.
   * Contém altura, largura e valor máximo de cor.
   */
  class ImageP3 { // alocaçao dinamica de um array[linhas*colunas]
  private:
    int height, width;
    Cor *pixels = nullptr;
    unsigned char maxCol = 255;
    
    /**
     * @brief Função auxiliar para cópias.
     *
     * Recebe os valores de outra 'ImageP3' e copia-os para si.
     * @param other Outra instância de 'ImageP3' para copiar os valores.
     */
    void deepCopy(const ImageP3& other); // helper function for deep copying

  public:
    /**
     * @brief Construtor padrão.
     */
    ImageP3() : width(0), height(0), maxCol(255), pixels(nullptr) {}

    /**
     * @brief Construtor com largura e altura.
     *
     * @param w Largura da matriz (eixo X).
     * @param h Altura da matriz (eixo Y).
     */
    ImageP3(int w, int h); // largura (x) e altura (y)

    /**
     * @brief Construtor com largura, altura e valor máximo de cor.
     *
     * Adiciona como parâmetro o valor máximo dos elementos de cor da
     * matriz. Útil para exportação da imagem no formato PPM.
     *
     * @param w Largura da matriz.
     * @param h Altura da matriz.
     * @param newMax Valor máximo para os componentes de cor (ex.: 255).
     */
    ImageP3(int w, int h, int newMax);
    
    /**
     * @brief Construtor de cópia.
     *
     * Inicializa uma 'ImageP3' com dados iguais aos de
     * outra 'ImageP3'.
     *
     * @param other Outra 'ImageP3' a ter os dados copiados.
     */
    ImageP3(const ImageP3& other) : pixels(nullptr) { // copy initializer ()
      this->deepCopy(other);
    }
    
    /**
     * @brief Operador de cópia.
     *
     * Modifica os dados da 'ImageP3' à esquerda, recebendo
     * os dados da 'ImageP3' à direita.
     *
     * @param other 'ImageP3' a ser copiada.
     * @return Uma referência para a 'ImageP3' modificada.
     */
    ImageP3& operator=(const ImageP3& other); // copy assignment=
    
    /**
     * @brief Destrutor da 'ImageP3'.
     *
     * Desaloca a matriz de pixels.
     */
    ~ImageP3(){
      delete[] this->pixels;
      this->pixels = nullptr;
    }
    // ------------------
    /**
     * @brief Método para consultar largura.
     *
     * Retorna a largura da 'ImageP3'.
     * @return A largura da imagem.
     */
    int getWidth(){ return this->width; }
    /**
     * @brief Método para consultar altura.
     *
     * Retorna a altura da 'ImageP3'.
     * @return A altura da imagem.
     */
    int getHeight(){ return this->height; }
    /**
     * @brief Método para consultar o valor máximo de cor.
     *
     * Retorna o valor máximo permitido para os componentes de cor da 'ImageP3'.
     * @return O valor máximo de cor.
     */
    int getMaxCol(){ return this->maxCol; }
    // ------------------
    /**
     * @brief Método para consultar um pixel.
     *
     * Retorna a cor do pixel na posição x,y dada,
     * ambas no intervalo de 0 até (largura - 1) ou
     * (altura - 1), respectivamente.
     *
     * @param x Índice X da matriz, começando em 0.
     * @param y Índice Y da matriz, começando em 0.
     * @return A cor do pixel na posição especificada.
     */
    Cor getPixel(int x, int y){
      return this->pixels[y * this->width + x];
    }
    
    /**
     * @brief Método para mudar um pixel.
     *
     * Modifica a cor do pixel na posição x,y dada,
     * ambas no intervalo de 0 até (largura - 1) ou
     * (altura - 1), respectivamente.
     *
     * @param x Índice X da matriz, começando em 0.
     * @param y Índice Y da matriz, começando em 0.
     * @param newColor Novo valor de cor para o pixel na posição x,y.
     */
    void setPixel(int x, int y, const Cor &newColor){
      this->pixels[y * this->width + x] = newColor;
    }
    // ------------------    
    /**
     * @brief Método para exportar a 'ImageP3'.
     *
     * Exporta os dados da 'ImageP3' para um arquivo especificado,
     * dentro da pasta 'out'. Recomenda-se utilizar o formato '.ppm'.
     *
     * @param fileName Caminho do arquivo para exportar, no formato:
     * "imagem.etc"
     */
    void write(const std::string &fileName);
    // ------------------
    /**
     * @brief Converte uma ImageP2 (mapa de alturas) em ImageP3 (colorida).
     *
     * Preenche os pixels da 'ImageP3' com cores baseadas nos valores
     * de altitude da 'ImageP2' fornecida, utilizando uma paleta de cores.
     *
     * @param heightMap Uma instância de 'ImageP2' representando o mapa de alturas.
     * @param pallet Uma instância de 'Paleta' contendo as cores a serem usadas.
     */
    void fromImageP2(ImageP2 &heightMap, Paleta &pallet);
    // ------------------
    /**
     * @brief Adiciona sombreamento à imagem.
     *
     * Aplica um efeito de sombreamento aos pixels da 'ImageP3' com base
     * em um mapa de alturas ('ImageP2'), simulando iluminação.
     *
     * @param p2 Uma instância de 'ImageP2' usada como mapa de alturas para o sombreamento.
     * @param intensity Intensidade do sombreamento.
     * @param proportional Se 'true', a intensidade é aplicada proporcionalmente.
     */
    void addShadow(ImageP2 p2, double intensity, bool proportional);
    // ------------------
  };
}
