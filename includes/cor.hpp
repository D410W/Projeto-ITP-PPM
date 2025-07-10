#pragma once

#include <algorithm>

namespace stc {
  struct Cor {
    unsigned char r = 0, g = 0, b = 0;

    Cor() : r(0), g(0), b(0) {}
    Cor(int r1, int g1, int b1)
            : r(std::clamp(r1, 0, 255)),
              g(std::clamp(g1, 0, 255)),
              b(std::clamp(b1, 0, 255)) {}
              
    // Cor - Cor
    Cor operator-(const Cor& other) const {
        return Cor(
            int(std::clamp(int(r) - int(other.r), 0, 255)),
            int(std::clamp(int(g) - int(other.g), 0, 255)),
            int(std::clamp(int(b) - int(other.b), 0, 255))
        );
    }
    
    // Cor - int
    Cor operator-(int other) const {
        return Cor(
            int(std::clamp(int(r) - int(other), 0, 255)),
            int(std::clamp(int(g) - int(other), 0, 255)),
            int(std::clamp(int(b) - int(other), 0, 255))
        );
    }
    
    // Cor * double
    Cor operator*(double other) const {
        return Cor(
            int(std::clamp(int(r * other), 0, 255)),
            int(std::clamp(int(g * other), 0, 255)),
            int(std::clamp(int(b * other), 0, 255))
        );   
    }
    
    // Cor += Cor
    Cor& operator+=(const Cor& other) {
        r = std::clamp(int(r) + int(other.r), 0, 255);
        g = std::clamp(int(g) + int(other.g), 0, 255);
        b = std::clamp(int(b) + int(other.b), 0, 255);
        return *this;
    }
    
    // Cor -= Cor
    Cor& operator-=(const Cor& other) {
        r = std::clamp(int(r) - int(other.r), 0, 255);
        g = std::clamp(int(g) - int(other.g), 0, 255);
        b = std::clamp(int(b) - int(other.b), 0, 255);
        return *this;
    }
    
    // Cor -= int
    Cor& operator-=(int other) {
        r = std::clamp(int(r) - int(other), 0, 255);
        g = std::clamp(int(g) - int(other), 0, 255);
        b = std::clamp(int(b) - int(other), 0, 255);
        return *this;
    }
  };

  // int - Cor
  inline Cor operator-(int value, const Cor& p) {
    return Cor(
        std::clamp(value - int(p.r), 0, 255),
        std::clamp(value - int(p.g), 0, 255),
        std::clamp(value - int(p.b), 0, 255)
    );
  }
}
