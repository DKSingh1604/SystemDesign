#pragma once
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include <string>
#include <iostream>
using namespace std;

class AudioEngine {
private:
    Song* currentSong;
    bool songIsPaused;
public:
    AudioEngine(){
        currentSong = NULL;
        songIsPaused = false;
    }
    string getCurrentSongTitle () const{
        if(currentSong){
            return currentSong->getTitle();
        }
        return "";
    }
    bool isPaused() const {
        return songIsPaused;
    }

    void play(IAudioOutputDevice* aod, Song* song){
        if(song == NULL){
            throw runtime_error("Song can't be null!");
        }
        //Resume if song is paused
        if(songIsPaused && song == currentSong){
            songIsPaused = false;
            cout<<"Resuming song: "<<song->getTitle()<<endl;
            aod->playAudio(song);
            return;
        }

        currentSong = song;
        songIsPaused = false;
        cout<<"Playing song: "<<song->getTitle()<<endl;
        aod->playAudio(song);
    }

    void pause(){
       if(currentSong == NULL){
            throw runtime_error("No currently playing song!");
       } 
       if(songIsPaused){
        throw runtime_error("The song is already paused!");
       }
       songIsPaused = true;
       cout<<"Song: "<<currentSong->getTitle()<<" is paused!"<<endl;
    }

};