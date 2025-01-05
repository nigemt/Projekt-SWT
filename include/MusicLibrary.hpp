
#pragma once
#include <vector>
#include "Track.hpp"
class FileManager;
class MusicLibrary
{
private:
    vector<Track*> track;
    std::string name;
public:

    MusicLibrary(std::string newname);
    void add_track(Track *track_to_add);
    void printTracks();
    vector<Track*> get_tracks();
    std::string get_name();
    void set_name(std::string newname);
    void deleteTrack(Track *todelete);
};