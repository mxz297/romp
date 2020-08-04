#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "PfqRWLock.h"
#include "Record.h"

namespace romp {

enum AccessHistoryFlag {
  eDataRaceFound = 0x1,
  eMemoryRecycled = 0x2,
};

class AccessHistory {

public: 
  AccessHistory() : _state(0) { pfqRWLockInit(&_lock); }
  PfqRWLock& getLock();
  std::vector<Record>* getRecords();
  std::vector<Record>* peekRecords();   
  void setFlag(AccessHistoryFlag flag);
  void clearFlags();
  void clearFlag(AccessHistoryFlag flag);
  bool dataRaceFound() const;
  bool memIsRecycled() const;
  uint64_t getState() const;
private:
  void _initRecords();
private:
  PfqRWLock _lock;
  uint64_t _state;  
  std::unique_ptr<std::vector<Record>> _records; 

};

}
