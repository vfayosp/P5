
#ifndef INSTRUMENTOFM
#define INSTRUMENTOFM

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
      class instrumentoFM: public upc::Instrument {
            EnvelopeADSR adsr;
            unsigned int index;
            std::vector<float> tbl;
            float f0;
            float I;
            float N1, N2;
            float Pond;
            float paso1, paso2;
            float fase1, fase2;
            float v;
            FILE *senyal;
      public:
            instrumentoFM(const std::string &param = "");
            void command(long cmd, long note, long vel = 0);
            const std::vector<float> & synthesize();
            bool is_active() const {
                  return bActive;
            }
      };
}

#endif