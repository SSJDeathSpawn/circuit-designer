#include "circuit.h"
#include <string.h>

bool ifExists(SimList* head, SimObjectType type, SimObject obj) {
  SimList* ptr = head;
  while(ptr != NULL) {
    if(ptr->type == type) {
      if(
        (type == DEVICE && obj.dev == ptr->obj.dev) || 
        (type == CONNECTION && obj.conn == ptr->obj.conn)
      ) 
        return true; 
    }
    ptr = ptr->next;
  }
  return false;
}

void removeAppendSimList(SimList **head, SimObjectType type, SimObject obj) {
  SimList* elem = (SimList*) malloc(sizeof(SimList));
  elem->type = type;
  elem->obj = obj;
  if(*head == NULL) {
    *head = elem;
  } else {
    SimList* ptr = *head;
    while(ptr->next != NULL) {
      if (ptr->type == type) {
        if(
          (type == DEVICE && obj.dev == ptr->obj.dev) || 
          (type == CONNECTION && obj.conn == ptr->obj.conn)
        ) {
          SimList* temp = ptr->next;
          ptr->next = ptr->next->next;
          free(temp);
        }
      }
      ptr = ptr->next;
    }
    ptr->next = elem;
  }
}

void appendSimList(SimList** head, SimObjectType type, SimObject obj) {
  SimList* elem = (SimList*) malloc(sizeof(SimList));
  elem->type = type;
  elem->obj = obj;
  if(*head == NULL) {
    *head = elem;
  } else {
    SimList* ptr = *head;
    while(ptr->next != NULL) ptr = ptr->next;
    ptr->next = elem;
  }
}

void formList(Circuit* circuit) {
  for(int i=0;i<circuit->inputCount;i++) {

    for(int j=0;j<circuit->board.numConnections;j++) {
      Connection* currConn = &(circuit->board.conns[j]);
      if(currConn->from == &(circuit->inputs[i])) {
        appendSimList(&(circuit->listHead), CONNECTION, (SimObject){.conn = currConn});
      }
    }
  }

  SimList* ptr = circuit->listHead;
  while(ptr != NULL) {
    if (ptr->type == DEVICE) {
      //Find connections from the gates of the devices
      Device* currDevice = ptr->obj.dev;
      for(int gate=0; gate<currDevice->deviceOutput.noGates; gate++) {
        Gate* currGate = &(currDevice->deviceOutput.gates[gate]);
        for(int conn=0; conn<circuit->board.numConnections; conn++) {
          Connection* currConn = &(circuit->board.conns[conn]);
          if(currConn->from == currGate && !ifExists(circuit->listHead, CONNECTION, ptr->obj)) {
            appendSimList(&(circuit->listHead), CONNECTION, (SimObject){.conn = currConn});
          }
        }
      }
    } else if(ptr->type == CONNECTION) {
      Connection *currConn = ptr->obj.conn;
      for(int dev=0;dev<circuit->board.deviceCount;dev++) {
        Device *currDevice = &(circuit->board.devices[dev]);
        for(int gate=0; gate<currDevice->deviceInput.noGates; gate++) {
          Gate* currGate = &(currDevice->deviceInput.gates[gate]);
          if(currGate == currConn->to) {
            removeAppendSimList(&(circuit->listHead), DEVICE, (SimObject){.dev = currDevice});
          }
        }
      }
    }
    ptr = ptr->next;
  }
}


Board newBoard(Device devices[], int devCount, Connection conns[], int numConns) {
  Board board = {
    .devices = (Device*) malloc(sizeof(Device)*devCount), 
    .deviceCount = devCount, 
    .conns = (Connection*) malloc(sizeof(Connection)*numConns), 
    .numConnections = numConns
  };

  for(int i=0;i<devCount;i++) {
    board.devices[i] = devices[i];
  }

  for(int i=0;i<numConns;i++) {
    board.conns[i] = conns[i];
  }

  return board;
}

Circuit newCircuit(Gate inputGates[], char inputLabels[], int inputs, Board board, Gate outputGates[], char outputLabels[], int outputs) {
  Circuit circuit = {
    .inputs = (Gate*) malloc(sizeof(Gate)*inputs), 
    .inputLabels = (char*) malloc(sizeof(char)*inputs), 
    .inputCount = inputs, 
    .board = board, 
    .listHead = NULL, 
    .outputs = (Gate*) malloc(sizeof(Gate)*outputs), 
    .outputLabels = (char*) malloc(sizeof(char)*outputs), 
    .outputCount = outputs
  };

  for(int i=0;i<inputs;i++) {
    circuit.inputs[i] = inputGates[i];
    circuit.inputLabels[i] = inputLabels[i];
  }

  for(int i=0;i<outputs;i++) {
    circuit.outputs[i] = outputGates[i];
    circuit.outputLabels[i] = outputLabels[i];
  }

  return circuit;
}

void simulateCircuit(Circuit* circuit) {
  SimList* ptr = circuit->listHead;
  while(ptr != NULL) {
    if (ptr->type == CONNECTION) {
      ptr->obj.conn->to->isActive = ptr->obj.conn->from->isActive;
    } else {
      runDevice(ptr->obj.dev);
    }
    ptr = ptr->next;
  }
}

Device makeDeviceFromCircuit(Circuit circuit, char name[]) {
  DeviceIO inputs = newIO(circuit.inputCount, true, circuit.inputLabels);
  DeviceIO outputs = newIO(circuit.outputCount, false, circuit.outputLabels);
  
  int count = (int)pow(2,circuit.inputCount);

  bool function_outs[circuit.outputCount][count];
  
  formList(&circuit);

  for(int i=0;i<count;i++) {
    int cur_input = i;
    for(int j=circuit.inputCount-1;j>=0;j--) {
      circuit.inputs[j].isActive = (bool)(cur_input & 1);
      cur_input = cur_input >> 1;
    }
    printf("Set input 0 to %s\n", (circuit.inputs[0].isActive)?"true":"false");

    simulateCircuit(&circuit);

    printf("Output 0 set to %s\n", (circuit.outputs[0].isActive)?"true":"false");

    for(int j=0;j<=circuit.outputCount;j++) {
      function_outs[j][i] = circuit.outputs[j].isActive;
    }
  }

  TruthTable function[circuit.outputCount];
  for(int i=0;i<circuit.outputCount;i++) {
    function[i] = newTable(function_outs[i], count);
  }

  return newDevice(name, inputs, outputs, function);
}
