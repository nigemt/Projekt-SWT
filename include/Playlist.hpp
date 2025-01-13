#pragma once
#include <vector>
#include "Track.hpp"
#include <string>
//Playlist Klasse für Track Verwaltung
class Playlist
{
private:
    vector<Track *> track;

    void printEditTracksMenu();
public:
    std::string name;
    void addTrack(Track *toAdd);
    vector<Track *> getTracks();
    void removeTrack(Track *toRemove);
    void removeTrack();
    bool containsTrack(Track *toCheck);
    void printPlaylist();
    void addTrackMenu(vector<Track *> selectableTrack);
    void editTracksMenu(vector<Track *> availableTracks);
    void wait_for_enter();
};
