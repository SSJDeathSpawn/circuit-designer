#include "../simulation/device.h"
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

void performTest(Device* gate, bool A, bool B, bool Y);

int main() {
  DeviceIO input = newIO(2, true, (char[]){'A', 'B'});
  DeviceIO output = newIO(1, false, (char[]){'Y'});
  TruthTable nand = newTable((bool[]) {true, true, true, false}, 4);
  
  Device nand_gate = newDevice("NAND", input, output, (TruthTable[]){nand});

  //Perform 
  printf("Perform A=0, B=0...");
  performTest(&nand_gate, false, false, true);
  usleep(500000);
  printf("Passed\n");

  printf("Perform A=0, B=1...");
  performTest(&nand_gate, false, true, true);
  usleep(500000);
  printf("Passed\n");

  printf("Perform A=1, B=0...");
  performTest(&nand_gate, true, false, true);
  usleep(500000);
  printf("Passed\n");

  printf("Perform A=1, B=1...");
  performTest(&nand_gate, true, true, false);
  usleep(500000);
  printf("Passed\n");

}

void performTest(Device* gate, bool A, bool B, bool Y) {
  gate->deviceInput.gates[0].isActive = A;
  gate->deviceInput.gates[1].isActive = B;
  runDevice(gate);

  if (Y) assert(gate->deviceOuput.gates[0].isActive);
  else assert(!gate->deviceOuput.gates[0].isActive);
}
