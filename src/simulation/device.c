#include "device.h"

TruthTable newTable(bool outputs[], int n) {

  TruthTable table = {
    .outputs = malloc(sizeof(bool)*n), 
    .noOutputs = n
  };

  for(int i=0;i<n;i++) {
    table.outputs[i] = outputs[i];
  }

  return table;
}

Gate newGate(bool isInput) {
  return (Gate) {
    .isInput = isInput,
    .isActive = false
  };
}

DeviceIO newIO(unsigned short noGates, bool isInput, char *labels) {
  DeviceIO io = (DeviceIO) {
    .noGates = noGates,
    .gates = (Gate*) malloc(sizeof(Gate)*noGates),
    .labels = (char*) malloc(sizeof(char)*noGates)
  };

  for(int i=0;i<noGates;i++) {
    io.gates[i] = newGate(isInput);
    io.labels[i] = labels[i];
  }

  return io;
}

Device newDevice(char* name, DeviceIO input, DeviceIO output, TruthTable* function) {
  if (!verifyIOTableNumbers(input, output, function)) {
    fprintf(stderr, "The numbers don't line up! Check input, output and the truth table\n");
  }
  
  int len = strlen(name);

  Device new = (Device) {
    .name = (char*) malloc(sizeof(char)*len), 
    .function = (TruthTable*) malloc(sizeof(TruthTable)*output.noGates), 
    .deviceInput = input, 
    .deviceOutput = output
  };
  
  for(int i=0;i<len;i++) new.name[i] = name[i];
  for(int i=0;i<output.noGates;i++) new.function[i] = function[i];
  return new;

}

bool verifyIOTableNumbers(DeviceIO input, DeviceIO output, TruthTable* function) {
  for(int i=0;i<output.noGates;i++) {
    if (function[i].noOutputs != (int)pow(2.0, (double)input.noGates)) return false;
  }
  return true;
}

void runDevice(Device *device) {

  int sum = 0;
  for(int i=0; i < device->deviceInput.noGates;i++) {
    sum = sum << 1;
    sum |= (device->deviceInput.gates[i].isActive)? 1 : 0;
  }

  for(int i=0; i < device->deviceOutput.noGates;i++) {
    device->deviceOutput.gates[i].isActive = device->function[i].outputs[sum];
  }
}
