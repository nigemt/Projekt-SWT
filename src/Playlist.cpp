#include "Playlist.hpp"
#include <iostream>
#include <algorithm>

void Playlist::addTrack(Track *toAdd)
{
    track.push_back(toAdd);
}

vector<Track *> Playlist::getTracks()
{
    return track;
}

void Playlist::removeTrack(Track *toRemove)
{
    track.erase(find(track.begin(), track.end(), toRemove));
}

bool Playlist::containsTrack(Track *toCheck)
{
    for (int i = 0; i < track.size(); i++)
    {
        if (track.at(i) == toCheck)
            return true;
    }
    return false;
}

void Playlist::printPlaylist()
{
    cout << "Playlist: " << name << endl;
    cout << "Lieder:" << endl;
    for (int i = 0; i < track.size(); i++)
    {
        track.at(i)->printTrack(i+1);
    }

}
