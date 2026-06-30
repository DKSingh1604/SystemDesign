#pragma once
#include "../models/Song.hpp"
#include "IAudioOutputDevice.hpp"
#include "../external/BluetoothSpeakerAPI.hpp"
using namespace std;

class BluetoothSpeakerAdapter : public IAudioOutputDevice {
private:
    BluetoothSpeakerAPI* bluetoothAPI;
public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* api){
        bluetoothAPI = api;
    }

    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist() + ".";
        bluetoothAPI->playSoundViaBluetooth(payload);
    }
};