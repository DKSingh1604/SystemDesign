#pragma once
#include <iostream>
#include "../models/Playlist.hpp"
#include "PlayStrategy.hpp"
using namespace std;

class RandomPlayStrategy : public PlayStrategy {
private:
    Playlist* currentPlaylist;
    vector<Song*> remainingSongs;
    stack<Song*> history;

public:
    RandomPlayStrategy(){
        currentPlaylist = NULL;
        srand((unsigned)time(NULL));
    }

    void setPlaylist(Playlist* playlist) override {
        currentPlaylist = playlist; 
        remainingSongs.clear();
        while(!history.empty()){
            history.pop();
        }

        if(!currentPlaylist || currentPlaylist->getSize() == 0) return;

        remainingSongs = currentPlaylist->getSongs();
    }
    
    bool hasNext() override {
        return currentPlaylist && !remainingSongs.empty();
    }

    Song* next() override {
        if(!currentPlaylist || currentPlaylist->getSize() == 0){
            throw runtime_error("No playlist loaded or playlist is empty!");
        }

        if(remainingSongs.empty()){
            throw runtime_error("No songs left to play!");
        }

        int idx = rand() % remainingSongs.size();
        Song* selectedSong = remainingSongs[idx];

        //Remove the selected song from the list. (Swap and pop to remove in O(1))
        swap(remainingSongs[idx], remainingSongs.back());
        remainingSongs.pop_back();

        history.push(selectedSong);
        return selectedSong;
    }

    bool hasPrevious () override {
        return history.size() > 0;
    }

    Song* previous () override {
        if(history.empty()){
            throw runtime_error("No previous song available!");
        }

        Song* song = history.top();
        history.pop();
        return song;
    }
};

