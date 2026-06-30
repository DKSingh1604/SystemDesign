#pragma once
#include <iostream>
#include "../models/Playlist.hpp"
#include "../models/Song.hpp"
using namespace std;

class PlayStrategy {
public:
    virtual ~PlayStrategy(){}
    virtual void setPlaylist(Playlist* playlist) {}
    virtual Song* next() = 0;
    virtual bool hasNext() = 0;
    virtual Song* previous() = 0;
    virtual bool hasPrevious() = 0;
    virtual void addToNext(Song* song){}  
};