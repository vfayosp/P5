#ifndef SENO
#define SENO

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class Seno: public upc::Instrument {
    EnvelopeADSR adsr;
    float index;
	  float A;
    float f0; //frecuencia de la nota que se quiere tocar
    float paso; //paso del index para conseguir tocar f0
    std::vector<float> tbl;
  public:
    Seno(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif
