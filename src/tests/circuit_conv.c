#include "../simulation/circuit.h"
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

void performTest(Circuit* circuit, bool inputs[], bool outputs[]);
extern Device nand_gate;

int main() {
  
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
  
  printf("Finished making the circuit!\n");

  formList(&not_gate_circuit);

  printf("Finished forming the list\n");

  //Perform 
  printf("Perform A=0...");
  performTest(&not_gate_circuit, (bool[]){false}, (bool[]){true});
  printf("Passed\n");

  printf("Perform A=1...");
  performTest(&not_gate_circuit, (bool[]){true}, (bool[]){false});
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
