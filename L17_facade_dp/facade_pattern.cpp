#include <iostream>
using namespace std;

//Subsystems
class PowerSupply {
public:
    void providePower(){
        cout<<"Power Supply: Providing power..."<<endl;
    }
};

class CoolingSystem {
public:
    void startFans(){
        cout<<"Cooling System: Fans started..."<<endl;
    }
};
class CPU {
public:
    void initialize(){
        cout<<"CPU: Initialize started..."<<endl;
    }
};

class Memory {
public:
    void selfTest(){
        cout<<"Memory: Initialization started..."<<endl;
    }
};

class HardDrive {
public:
    void spinUp(){
        cout<<"HardDrive: spinning up...."<<endl;
    }
};

class BIOS {
public:
    void boot(CPU& cpu, Memory& memory) {
        cout<<"Booting up: CPU and Memory checks.."<<endl;
        cpu.initialize();
        memory.selfTest();
    }
};

class OperatingSystem {
public:
    void load() {
        cout<<"Operating System: loading into memory..."<<endl;
    }
};

//Facade
class ComputerFacade {
private:
    PowerSupply powerSupply;
    CoolingSystem coolingSystem;
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;
    BIOS bios;
    OperatingSystem operatingSystem;

public:
    void startComputer (){
        cout<<"----Starting Computer----"<<endl;
        powerSupply.providePower();
        coolingSystem.startFans();
        cpu.initialize();
        memory.selfTest();
        hardDrive.spinUp();
        bios.boot(cpu, memory);
        operatingSystem.load();
        cout<<"----Computer Turned ON----"<<endl;
    }
};

//Client
int main(){
    ComputerFacade compFacade;
    compFacade.startComputer();
    return 0;
}

