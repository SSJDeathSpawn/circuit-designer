#ifndef DEVICE_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

typedef struct Gate {
  bool isInput;
  bool isActive;
} Gate;

typedef struct DeviceIO {
  unsigned short int noGates;
  Gate* gates;
  char* labels;
} DeviceIO;

typedef struct TruthTable {
  int noOutputs;
  bool* outputs;
} TruthTable;

typedef struct Device {
  char* name;
  DeviceIO deviceInput;
  DeviceIO deviceOuput;
  TruthTable* function;
} Device;

int getNumInputs(Device self);
int getNumOutputs(Device self);

TruthTable newTable(bool outputs[], int n);
Gate newGate(bool isInput);
DeviceIO newIO(unsigned short int noGates, bool isInput, char labels[]);
Device newDevice(char* name, DeviceIO input, DeviceIO output, TruthTable function[]);
bool verifyIOTableNumbers(DeviceIO input, DeviceIO output, TruthTable* function);

#endif // !DEVICE_H
