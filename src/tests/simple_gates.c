#include "../simulation/device.h"
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

void performTest(Device* gate, bool inputs[], bool outputs[]);
extern Device makeNandGate();

int main() {
  // DeviceIO input = newIO(2, true, (char[]){'A', 'B'});
  // DeviceIO output = newIO(1, false, (char[]){'Y'});
  // TruthTable nand = newTable((bool[]) {true, true, true, false}, 4);
  // 
  // Device nand_gate = newDevice("NAND", input, output, (TruthTable[]){nand});
  Device nand_gate = makeNandGate();

  //Perform 
  printf("Perform A=0, B=0...");
  performTest(&nand_gate, (bool[]){false, false}, (bool[]){true});
  usleep(500000);
  printf("Passed\n");

  printf("Perform A=0, B=1...");
  performTest(&nand_gate, (bool[]){false, true}, (bool[]){true});
  usleep(500000);
  printf("Passed\n");

  printf("Perform A=1, B=0...");
  performTest(&nand_gate, (bool[]){true, false}, (bool[]){true});
  usleep(500000);
  printf("Passed\n");

  printf("Perform A=1, B=1...");
  performTest(&nand_gate, (bool[]){true, true}, (bool[]){false});
  usleep(500000);
  printf("Passed\n");

}

void performTest(Device* gate, bool inputs[], bool outputs[]) {
  for(int input=0;input<gate->deviceInput.noGates;input++) {
    gate->deviceInput.gates[input].isActive = inputs[input];
  }

  runDevice(gate);
  
  for(int output=0;output<gate->deviceOutput.noGates;output++) {
    assert(gate->deviceOutput.gates[output].isActive == outputs[output]);
  }
}
