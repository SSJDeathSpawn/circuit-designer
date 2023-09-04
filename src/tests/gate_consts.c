#include "../simulation/device.h"


Device makeNandGate() {
  DeviceIO input = newIO(2, true, (char[]){'A', 'B'});
  DeviceIO output = newIO(1, false, (char[]){'Y'});
  TruthTable nand = newTable((bool[]) {true, true, true, false}, 4);

  return newDevice("NAND", input, output, (TruthTable[]){nand});
}
