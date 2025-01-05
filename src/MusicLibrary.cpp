#include "MusicLibrary.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>


MusicLibrary::MusicLibrary(std::string newname)
{
    name = newname;
}

void MusicLibrary::add_track(Track *track_to_add)
{
    track.push_back(track_to_add);
}

void MusicLibrary::printTracks()
{
    if (track.size() == 0) {
        std::cout << "Keine Songs zu dieser Bibliothek hinzugefuegt." << endl;
    }
    for ( int i = 0; i < track.size();++i) {
        track.at(i)->printTrack(i+1);
    }
}

vector<Track*> MusicLibrary::get_tracks()
{
    return track;
}

std::string MusicLibrary::get_name()
{
    return name;
}

void MusicLibrary::set_name(std::string newname)
{
    name = newname;
}

void MusicLibrary::deleteTrack(Track *todelete)
{
    track.erase(find(track.begin(), track.end(), todelete));
    delete todelete;
}
