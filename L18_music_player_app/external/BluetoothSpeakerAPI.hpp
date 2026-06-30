#pragma once
#include <iostream>
#include <string>
using namespace std;

class BluetoothSpeakerAPI {
public:
    void playSoundViaBluetooth(const string& data){
        cout<<"BLuetooth Speaker is playing: "<<data<<endl;
        //mimics music
    }

};