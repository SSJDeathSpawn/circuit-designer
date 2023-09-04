#ifndef CIRCUIT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "device.h"

typedef struct Connection {
  Gate* from;
  bool isActive;
  Gate* to;
} Connection;

typedef union SimObject {
  Connection* conn;
  Device* dev;
} SimObject;

typedef enum SimObjectType {
  CONNECTION=0,
  DEVICE
} SimObjectType;

typedef struct SimList {
  SimObjectType type;
  SimObject obj;
  struct SimList* next;
} SimList;

typedef struct Board {
  Device* devices;
  int deviceCount;
  Connection* conns;
  int numConnections;
} Board;

typedef struct Cicruit {
  Gate* inputs;
  char* inputLabels;
  int inputCount;
  Board board;
  SimList* listHead;
  Gate* outputs;
  char* outputLabels;
  int outputCount;
} Circuit;

void appendSimList(SimList** head, SimObjectType type, SimObject obj);
void removeAppendSimList(SimList** head, SimObjectType type, SimObject obj);
void formList(Circuit* circuit);
Board newBoard(Device devices[], int devCount, Connection conns[], int numConns);
void freeBoard(Board board);
Circuit newCircuit(Gate inputGates[], char inputLabels[], int inputs, Board board, Gate outputGates[], char outputLabels[], int outputs);
void freeCiruit(Circuit circuit);
void simulateCircuit(Circuit* circuit);
Device makeDeviceFromCircuit(Circuit circuit, char name[]); // TODO

#endif // !CIRCUIT_H
