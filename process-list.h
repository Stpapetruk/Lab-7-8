#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

#include <string>

enum class ProcessStatus {
    RUNNING,
    WAITING,
    STOPPED
};

struct PCB {
    int processID;
    std::string processName;
    ProcessStatus processStatus;
    int commandCounter;
    int cpuRegisters[4];
    
    PCB(int id, const std::string& name, ProcessStatus status = ProcessStatus::WAITING)
        : processID(id), processName(name), processStatus(status), commandCounter(0) {
        for (int i = 0; i < 4; ++i) {
            cpuRegisters[i] = 0;
        }
    }
};

class ListNode {
public:
    PCB data;
    ListNode* next;
    
    ListNode(const PCB& pcb);
};

class ProcessList {
private:
    ListNode* head;
    
    void clear();
    ListNode* findPrevious(int pid) const;
    
public:
    ProcessList();
    ~ProcessList();
    
    bool insert(const PCB& newPCB);
    bool remove(int pid);
    void printList() const;
    
    ProcessList(const ProcessList&) = delete;
    ProcessList& operator=(const ProcessList&) = delete;
};

#endif
