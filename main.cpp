#include "process-list.h"
#include <iostream>

int main() {
    std::cout << "=== УПРАВЛЕНИЕ СПИСКОМ ПРОЦЕССОВ ===" << std::endl;
    
    ProcessList processList;
    
    std::cout << "\n2. Добавление процессов в список..." << std::endl;
    
    PCB pcb1(101, "SystemInit", ProcessStatus::RUNNING);
    pcb1.commandCounter = 100;
    pcb1.cpuRegisters[0] = 10; pcb1.cpuRegisters[1] = 20;
    
    PCB pcb2(103, "FileManager", ProcessStatus::WAITING);
    pcb2.commandCounter = 45;
    pcb2.cpuRegisters[0] = 5; pcb2.cpuRegisters[1] = 15;
    
    PCB pcb3(102, "NetworkDaemon", ProcessStatus::RUNNING);
    pcb3.commandCounter = 78;
    pcb3.cpuRegisters[0] = 8; pcb3.cpuRegisters[1] = 12;
    
    PCB pcb4(105, "UserInterface", ProcessStatus::STOPPED);
    pcb4.commandCounter = 23;
    pcb4.cpuRegisters[0] = 3; pcb4.cpuRegisters[1] = 7;
    
    PCB pcb5(104, "SecurityMonitor", ProcessStatus::WAITING);
    pcb5.commandCounter = 56;
    pcb5.cpuRegisters[0] = 6; pcb5.cpuRegisters[1] = 9;
    
    processList.insert(pcb1);
    processList.insert(pcb2);
    processList.insert(pcb3);
    processList.insert(pcb4);
    processList.insert(pcb5);
    
    std::cout << "\n3. Список процессов после добавления:" << std::endl;
    processList.printList();
    
    std::cout << "\n4. Удаление процессов..." << std::endl;
    
    std::cout << "Попытка удалить процесс с ID 102:" << std::endl;
    processList.remove(102);
    
    std::cout << "\nПопытка удалить процесс с ID 104:" << std::endl;
    processList.remove(104);
    
    std::cout << "\n5. Список процессов после удаления:" << std::endl;
    processList.printList();
    
    std::cout << "\n6. Демонстрация ошибочных операций:" << std::endl;
    
    std::cout << "\nа) Попытка вставить дубликат процесса с ID 101:" << std::endl;
    PCB duplicatePCB(101, "DuplicateProcess", ProcessStatus::RUNNING);
    processList.insert(duplicatePCB);
    
    std::cout << "\nб) Попытка удалить несуществующий процесс с ID 999:" << std::endl;
    processList.remove(999);
    
    std::cout << "\nв) Попытка повторно удалить процесс с ID 102:" << std::endl;
    processList.remove(102);
    
    std::cout << "\n7. Финальное состояние списка процессов:" << std::endl;
    processList.printList();
    
    std::cout << "\n8. Дополнительная проверка - вставка нового процесса:" << std::endl;
    PCB pcb6(100, "BootLoader", ProcessStatus::RUNNING);
    pcb6.commandCounter = 1;
    pcb6.cpuRegisters[0] = 0;
    
    processList.insert(pcb6);
    processList.printList();
    
    std::cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА УСПЕШНО ===" << std::endl;
    
    return 0;
}
