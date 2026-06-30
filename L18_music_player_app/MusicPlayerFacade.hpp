#pragma once
#include "core/AudioEngine.hpp"
#include "models/Playlist.hpp"
#include "models/Song.hpp"
#include "strategies/PlayStrategy.hpp"
#include "enums/DeviceType.hpp"
#include "enums/PlayStartegy.hpp"
#include "managers/DeviceManager.hpp"
#include "managers/PlaylistManager.hpp"
#include "managers/StrategyManager.hpp"
using namespace std;

class MusicPlayerFacade
{
private:
    static MusicPlayerFacade *instance;
    AudioEngine *audioEngine;
    Playlist *loadedPlaylist;
    PlayStrategy *playStrategy;

    MusicPlayerFacade()
    {
        loadedPlaylist = NULL;
        playStrategy = NULL;
        audioEngine = new AudioEngine();
    }

public:
    static MusicPlayerFacade *getInstance()
    {
        if (!instance)
        {
            instance = new MusicPlayerFacade();
        }
        return instance;
    }

    void connectDevice(DeviceType deviceType)
    {
        DeviceManager::getInstance()->connect(deviceType);
    }

    void setStrategy(PlayStartegyType strategyType)
    {
        playStrategy = StrategyManager::getInstance()->getStrategy(strategyType);
    }

    void loadPlaylist(const string &name)
    {

        loadedPlaylist = PlaylistManager::getInstance()->getPlaylist(name);
        if (!playStrategy)
        {
            throw runtime_error("Play Strategy not set before loading!");
        }

        playStrategy->setPlaylist(loadedPlaylist);
    }

    void playSong(Song *song)
    {
        if (!DeviceManager::getInstance()->hasOutputDevice())
        {
            throw runtime_error("No audio device connected!");
        }
        IAudioOutputDevice *device = DeviceManager::getInstance()->getOutputDevice();
        audioEngine->play(device, song);
    }

    void pauseSong(Song *song)
    {
        if (audioEngine->getCurrentSongTitle() != song->getTitle())
        {
            throw runtime_error("Cannot pause: " + song->getTitle() + ", as it is not playing!");
        }
        audioEngine->pause();
    }

    void playAllTracks()
    {
        if (!loadedPlaylist)
        {
            throw runtime_error("No playlist loaded!");
        }
        while (playStrategy->hasNext())
        {
            Song *nextSong = playStrategy->next();
            IAudioOutputDevice *device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        cout << "Completed Playlist: " << loadedPlaylist->getPlaylistName() << endl;
    }

    void playNextTrack()
    {
        if (!loadedPlaylist)
        {
            throw runtime_error("No Playlist loaded!");
        }

        if (playStrategy->hasNext())
        {
            Song *nextSong = playStrategy->next();
            IAudioOutputDevice *device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        else
        {
            cout << "Completed Playlist: " << loadedPlaylist->getPlaylistName() << endl;
        }
    }

    void playPreviousTrack(){
        if(!loadedPlaylist){
            throw runtime_error("No playlist loaded!");
        }
        if (playStrategy->hasPrevious())
        {
            Song *prevSong = playStrategy->previous();
            IAudioOutputDevice *device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, prevSong);
        }
        else{
            cout << "Completed Playlist: " << loadedPlaylist->getPlaylistName() << endl;

        }
    }

    void enqueueNext(Song* song){
        playStrategy->addToNext(song);
    }
};
MusicPlayerFacade* MusicPlayerFacade::instance = NULL;
