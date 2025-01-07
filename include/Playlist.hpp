#pragma once
#include <vector>
#include "Track.hpp"
#include <string>

class Playlist {
    private:
    vector<Track*> track;
    public:
    std::string name;
    void addTrack(Track *toAdd);
    vector<Track*> getTracks();
    void removeTrack(Track *toRemove);
    bool containsTrack(Track *toCheck);
    void printPlaylist();
};