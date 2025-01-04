#include "MusicLibrary.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>


MusicLibrary::MusicLibrary(std::string newname)
{
    name = newname;
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
    Track *currentTrack;
    for ( int i = 0; i < track.size();++i) {
        currentTrack = &track.at(i);
        std::cout << i+1 << ": " << currentTrack->title << std::endl;
        std::cout << "\tAlbum:" << currentTrack->album << " Kuenstler: " << currentTrack->artist << " Erscheinungsjahr: " << currentTrack->release << endl;
        std::cout << "\tDauer:" << currentTrack->duration << " Genere: " << currentTrack->genere << endl;
    }
}

vector<Track> MusicLibrary::get_tracks()
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
