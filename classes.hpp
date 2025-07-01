#pragma once

namespace stc {

  struct Cor {
    unsigned char r = 0, g = 0, b = 0;
  };

  class Paleta {
    int quantidade;
    Cor cores[100];
    int valores[100];
  public:
    Paleta(){
      
    }
    
  };
  
}
