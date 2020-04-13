#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "instrumentoFM.h"
#include "keyvalue.h"

using namespace upc;
using namespace std;

instrumentoFM::instrumentoFM(const std::string &param) : adsr(SamplingRate, param) {
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

void instrumentoFM::command(int cmd, int note, int vel) {
      switch (cmd) {
            case 0:
                  adsr.end();
            break;

            case 8:
                  adsr.stop();
            break;
            
            case 9:
                  bActive = true;
                  adsr.start();
                  
                  f0 = (pow(2, (note - 69)/12.))*440;

                  paso1 = 2*M_PI*f0/SamplingRate;
                  paso2 = 2*M_PI*N2*f0/N1/SamplingRate;

                  v = vel/127;
            break;
            default:
            break;
      }
}

const vector<float> & instrumentoFM::synthesize() {
      if (not adsr.active()) {
            x.assign(x.size(), 0);
            bActive = false;
            return x;
      }
      else if (not bActive){
            return x;
      } else {
            for(int i = 0; i < x.size(); i++) {
                  x[i] = 1*v*sin(fase1 + I*sin(fase2));
                  fase1 += paso1;
                  fase2 += paso2;

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