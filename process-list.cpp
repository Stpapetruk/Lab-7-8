#include "process-list.h"
#include <iostream>
#include <iomanip>

ListNode::ListNode(const PCB& pcb) : data(pcb), next(nullptr) {}

ProcessList::ProcessList() : head(nullptr) {}

ProcessList::~ProcessList() {
    clear();
}

void ProcessList::clear() {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

ListNode* ProcessList::findPrevious(int pid) const {
    ListNode* current = head;
    ListNode* previous = nullptr;
    
    while (current != nullptr && current->data.processID < pid) {
        previous = current;
        current = current->next;
    }
    
    return previous;
}

bool ProcessList::insert(const PCB& newPCB) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->data.processID == newPCB.processID) {
            std::cout << "Ошибка: процесс с ID " << newPCB.processID << " уже существует!" << std::endl;
            return false;
        }
        current = current->next;
    }
    
    ListNode* newNode = new ListNode(newPCB);
    
    if (head == nullptr) {
        head = newNode;
        return true;
    }
    
    if (newPCB.processID < head->data.processID) {
        newNode->next = head;
        head = newNode;
        return true;
    }
    
    ListNode* previous = head;
    while (previous->next != nullptr && previous->next->data.processID < newPCB.processID) {
        previous = previous->next;
    }
    
    newNode->next = previous->next;
    previous->next = newNode;
    return true;
}

bool ProcessList::remove(int pid) {
    if (head == nullptr) {
        std::cout << "Ошибка: список процессов пуст!" << std::endl;
        return false;
    }
    
    if (head->data.processID == pid) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        std::cout << "Процесс с ID " << pid << " успешно удален." << std::endl;
        return true;
    }
    
    ListNode* previous = head;
    while (previous->next != nullptr && previous->next->data.processID != pid) {
        previous = previous->next;
    }
    
    if (previous->next != nullptr && previous->next->data.processID == pid) {
        ListNode* temp = previous->next;
        previous->next = previous->next->next;
        delete temp;
        std::cout << "Процесс с ID " << pid << " успешно удален." << std::endl;
        return true;
    }
    
    std::cout << "Ошибка: процесс с ID " << pid << " не найден!" << std::endl;
    return false;
}

void ProcessList::printList() const {
    if (head == nullptr) {
        std::cout << "Список процессов пуст." << std::endl;
        return;
    }
    
    std::cout << "\n=== ТЕКУЩИЙ СПИСОК ПРОЦЕССОВ ===" << std::endl;
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Имя" 
              << std::setw(15) << "Статус" 
              << std::setw(10) << "Счетчик" 
              << "Регистры" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    ListNode* current = head;
    while (current != nullptr) {
        const PCB& pcb = current->data;
        
        std::string statusStr;
        switch (pcb.processStatus) {
            case ProcessStatus::RUNNING: statusStr = "Running"; break;
            case ProcessStatus::WAITING: statusStr = "Waiting"; break;
            case ProcessStatus::STOPPED: statusStr = "Stopped"; break;
        }
        
        std::string registersStr = "[";
        for (int i = 0; i < 4; ++i) {
            registersStr += std::to_string(pcb.cpuRegisters[i]);
            if (i < 3) registersStr += ", ";
        }
        registersStr += "]";
        
        std::cout << std::left << std::setw(10) << pcb.processID
                  << std::setw(20) << pcb.processName
                  << std::setw(15) << statusStr
                  << std::setw(10) << pcb.commandCounter
                  << registersStr << std::endl;
        
        current = current->next;
    }
    std::cout << std::endl;
}
