
#pragma once
#include <vector>
#include "Track.hpp"
#include "FileManager.hpp"
class FileManager;
class MusicLibrary
{
private:
    vector<Track> track;
public:
    static const FileManager fileManager;

    MusicLibrary();
    void add_track(Track track_to_add);
    void printTracks();
    vector<Track> get_tracks();
};