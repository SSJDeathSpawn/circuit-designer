#include "../simulation/circuit.h"
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

void performTest(Circuit* circuit, bool inputs[], bool outputs[]);
void performTestOnDevice(Device* gate, bool inputs[], bool outputs[]);
extern Device makeNandGate();

int main() {
  Device nand_gate = makeNandGate();
  Device devices_not_gate[] = {nand_gate};
  Connection conns_not_gate[] = {
    (Connection) {.to = &(nand_gate.deviceInput.gates[0])},
    (Connection) {.to = &(nand_gate.deviceInput.gates[1])},
    (Connection) {.from = &(nand_gate.deviceOutput.gates[0])}
  };

  Board not_gate_board = newBoard(devices_not_gate, 1, conns_not_gate, 3);
  
  Gate inputs[] = {(Gate) {}};
  Gate outputs[] = {(Gate) {}};

  Circuit not_gate_circuit = newCircuit(inputs, "A", 1, not_gate_board, outputs, "Y", 1);
  not_gate_circuit.board.conns[0].from = &(not_gate_circuit.inputs[0]);
  not_gate_circuit.board.conns[1].from = &(not_gate_circuit.inputs[0]);
  not_gate_circuit.board.conns[2].to = &(not_gate_circuit.outputs[0]);
  
  Device not_gate = makeDeviceFromCircuit(not_gate_circuit, "NOT");
  
  assert(not_gate.deviceInput.noGates == 1);
  assert(not_gate.deviceOutput.noGates == 1);

  //Perform 
  printf("Perform A=0...");
  performTestOnDevice(&not_gate, (bool[]){false}, (bool[]){true});
  usleep(500000);
  printf("Passed\n");

  printf("Perform A=1...");
  performTestOnDevice(&not_gate, (bool[]){true}, (bool[]){false});
  usleep(500000);
  printf("Passed\n");
}

void performTest(Circuit* circuit, bool inputs[], bool outputs[]) {
  for(int input=0;input<circuit->inputCount;input++) {
    circuit->inputs[input].isActive = inputs[input];
  }

  simulateCircuit(circuit);
  
  for(int output=0;output<circuit->outputCount;output++) {
    assert(circuit->outputs[output].isActive == outputs[output]);
  }

}

void performTestOnDevice(Device* gate, bool inputs[], bool outputs[]) {
  for(int input=0;input<gate->deviceInput.noGates;input++) {
    gate->deviceInput.gates[input].isActive = inputs[input];
  }

  runDevice(gate);
  
  for(int output=0;output<gate->deviceOutput.noGates;output++) {
    assert(gate->deviceOutput.gates[output].isActive == outputs[output]);
  }
}
