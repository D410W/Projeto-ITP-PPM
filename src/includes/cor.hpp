#pragma once

#include <algorithm>

namespace stc {
  /**
   * @brief Representa uma cor RGB, com valores RED, GREEN e BLUE.
   */
  struct Cor {
    unsigned char r = 0, g = 0, b = 0;
    /**
     * @brief Construtor padrao.
     *
     * Inicializa a cor como preto (0, 0, 0).
     */
    Cor() : r(0), g(0), b(0) {}
    
    /**
     * @brief Construtor com parametros.
     *
     * Inicializa a cor com valores especificados de RED, GREEN e BLUE.
     *
     * @param r1 O valor do componente RED (0-255).
     * @param g1 O valor do componente GREEN (0-255).
     * @param b1 O valor do componente BLUE (0-255).
     */
    Cor(int r1, int g1, int b1)
            : r(std::clamp(r1, 0, 255)),
              g(std::clamp(g1, 0, 255)),
              b(std::clamp(b1, 0, 255)) {}
              
    /// Cor - Cor
    Cor operator-(const Cor& other) const {
        return Cor(
            int(std::clamp(int(r) - int(other.r), 0, 255)),
            int(std::clamp(int(g) - int(other.g), 0, 255)),
            int(std::clamp(int(b) - int(other.b), 0, 255))
        );
    }
    
    /// Cor - int
    Cor operator-(int other) const {
        return Cor(
            int(std::clamp(int(r) - int(other), 0, 255)),
            int(std::clamp(int(g) - int(other), 0, 255)),
            int(std::clamp(int(b) - int(other), 0, 255))
        );
    }
    
    /// Cor * double
    Cor operator*(double other) const {
        return Cor(
            int(std::clamp(int(r * other), 0, 255)),
            int(std::clamp(int(g * other), 0, 255)),
            int(std::clamp(int(b * other), 0, 255))
        );   
    }
    
    /// Cor += Cor
    Cor& operator+=(const Cor& other) {
        r = std::clamp(int(r) + int(other.r), 0, 255);
        g = std::clamp(int(g) + int(other.g), 0, 255);
        b = std::clamp(int(b) + int(other.b), 0, 255);
        return *this;
    }
    
    /// Cor -= Cor
    Cor& operator-=(const Cor& other) {
        r = std::clamp(int(r) - int(other.r), 0, 255);
        g = std::clamp(int(g) - int(other.g), 0, 255);
        b = std::clamp(int(b) - int(other.b), 0, 255);
        return *this;
    }
    
    /// Cor -= int
    Cor& operator-=(int other) {
        r = std::clamp(int(r) - int(other), 0, 255);
        g = std::clamp(int(g) - int(other), 0, 255);
        b = std::clamp(int(b) - int(other), 0, 255);
        return *this;
    }
  };

  /// int - Cor
  inline Cor operator-(int value, const Cor& p) {
    return Cor(
        std::clamp(value - int(p.r), 0, 255),
        std::clamp(value - int(p.g), 0, 255),
        std::clamp(value - int(p.b), 0, 255)
    );
  }
}
