#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "InstrumentoConfigurable.h"
#include "keyvalue.h"

using namespace upc;
using namespace std;

instrumentoConfigurable::instrumentoConfigurable(const std::string &param) : adsr(SamplingRate, param) {
      bActive = false;
      x.resize(BSIZE);
      KeyValue kv(param);

//Predeterminados
      if(!kv.to_float("N1", N1)) {
            N1 = 1;
      }
      if(!kv.to_float("N2", N2)) {
            N2 = 1;
      }
      if(!kv.to_float("I", I)) {
            I = 1;
      }
      fase1 = 0;
      fase2 = 0;
}

void instrumentoConfigurable::command(long cmd, long note, long vel) {
      if (cmd == 0) {
            adsr.end();
      } else if (cmd == 8) {
            adsr.stop();
      } else if (cmd == 9) {
            bActive = true;
            adsr.start();

            f0 = (pow(2, (note - 69)/12.))*440;
            printf("%f\n", vel);
            paso1 = 2*M_PI*f0/SamplingRate;
            paso2 = 2*M_PI*N2*f0/N1/SamplingRate;

            v = vel/127;
      }
}

const vector<float> & instrumentoConfigurable::synthesize() {
      if (not adsr.active()) {
            x.assign(x.size(), 0);
            bActive = false;
            return x;
      }
      else if (not bActive){
            return x;
      } else {
            v = 1;
            for(int i = 0; i < x.size(); i++) {
                  x[i] = 1*v*sin(fase1 + I*sin(fase2));
                  fase1 += paso1;
                  fase2 += paso2;
                  printf("fase1: %f\t fase2: %f\t paso1: %f\t paso2: %f\t velocidad: %f\t Intensidad: %f N1: %f\t N2: %f\n", fase1, fase2, paso1, paso2, v, I, N1, N2);
            
                  while (fase1 >= 2*M_PI) {
                        fase1 -= 2*M_PI;
                  }
                  while (fase2 >= 2*M_PI) {
                        fase2 -= 2*M_PI;
                  }
            }
            adsr(x);

            return x;
      }
}