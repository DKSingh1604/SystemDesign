#include <iostream>
using namespace std;

//Comman Interface
class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand (){}
};

//Receivers
class Light {
public:
    void on(){
        cout<<"The light is turned ON!"<<endl;
    }

    void off(){
        cout<<"The light is turned OFF"<<endl;
    }
};

class Fan {
public:
    void on(){
        cout<<"The fan is turned ON!"<<endl;
    }

    void off(){
        cout<<"The fan is turned OFF"<<endl;
    }
};

//Concrete command for light
class LightCommand : public ICommand {
private:
    Light* light;

public:
    LightCommand(Light* l){
        light = l;
    }

    void execute() override {
        light -> on();
    }

    void undo() override {
        light -> off();
    }
};

//Concrete command for fan
class FanCommand : public ICommand {
private:
    Fan* fan;

public:
    FanCommand(Fan* f){
        fan = f;
    }

    void execute() override {
        fan -> on();
    }

    void undo() override {
        fan -> off();
    }
};

class RemoteController {
private:
    static const int numButtons = 4;
    ICommand* buttons[numButtons];
    bool buttonPressed[numButtons];

    public:
    RemoteController(){
        for(int i = 0; i < numButtons; i++){
            buttons[i] = NULL;
            buttonPressed[i] = false;
        }
    }

    void setCommand(int idx, ICommand* cmd){
        if(idx >= 0 && idx < numButtons){
            if(buttons[idx] != NULL)
                delete buttons[idx];
            buttons[idx] = cmd;
            buttonPressed[idx] = false;
        }
    }

    void pressButton(int idx){
        if(idx >= 0 && idx < numButtons && buttons[idx] != NULL){
            if(buttonPressed[idx] == false){
                buttons[idx]->execute();
            }
            else{
                buttons[idx]->undo();
            }
            buttonPressed[idx] = !buttonPressed[idx];
        }
        else{
            cout<<"No command assigned at index: "<<idx<<endl;
        }
    }

    ~RemoteController(){
        for(int i = 0; i < numButtons; i++){
            if(buttons[i] != NULL)
                delete buttons[i];
        }
    }
};

int main (){

    Light* livingRoomLight = new Light();
    Fan* ceilingFan = new Fan();

    RemoteController* remote = new RemoteController();

    remote->setCommand(0, new LightCommand(livingRoomLight));
    remote->setCommand(1, new FanCommand(ceilingFan));

    //Simulating button presses
    cout<<"-- Toggling Light Button 0 --"<<endl;
    remote->pressButton(0); //it should be tuned on
    remote->pressButton(0); //it should be turned off

    cout<<"-- Toggling Fan Button 1 --"<<endl;
    remote->pressButton(1); //it should be tuned on
    remote->pressButton(1); //it should be turned off

    cout<<"-- Pressing unassigned button --"<<endl;
    remote->pressButton(2);

    //Clean up
    delete remote;
    delete livingRoomLight;
    delete ceilingFan;

    return 0;

}