#include "MusicLibrary.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>


MusicLibrary::MusicLibrary()
{
    
}

void MusicLibrary::add_track(Track track_to_add)
{
    track.push_back(track_to_add);
}

void MusicLibrary::printTracks()
{
    if (track.size() == 0) {
        std::cout << "Keine Songs zu dieser Bibliothek hinzugefuegt." << endl;
    }
    for ( int i = 0; i < track.size();++i) {
        std::cout << i << ": " << track.at(i).title << std::endl;
    }
}

vector<Track> MusicLibrary::get_tracks()
{
    return track;
}
