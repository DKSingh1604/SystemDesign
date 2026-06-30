#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Song.hpp"
using namespace std;

class Playlist {
private:
    string playlistName;
    vector<Song*> songList;

public:
    Playlist(string name){
        playlistName = name;
    }
    string getPlaylistName(){
        return playlistName;
    }

    const vector<Song*> getSongs(){
        return songList;
    }

    int getSize(){
        return (int)songList.size();
    }

    void addSongToPlaylist(Song* song){
        if(song == NULL){
            throw runtime_error("Cannot add null song to playlist!");
        }
        songList.push_back(song);
    }

};
