#include "FileManager.hpp"
#include "json.hpp"
#include "Track.hpp"
#include <fstream>
#include <iostream>

void FileManager::save_to_file(MusicLibrary musicLibrary)
{
    nlohmann::json complete;
    vector<Track*> mL = musicLibrary.get_tracks();
    for (int i = 0; i < mL.size(); i++)
    {
        Track *currentTrack = mL.at(i);
        nlohmann::json jT = {
            {"titel", currentTrack->title},
            {"album", currentTrack->album},
            {"release", currentTrack->release},
            {"artist", currentTrack->artist},
            {"duration", currentTrack->duration},
            {"genere", currentTrack->genere},
        };
        complete["tracks"].push_back(jT);
    }
    std::ofstream file(musicLibrary.get_name() + ".json");
    if (file.is_open()) {
        file << complete.dump(4);
        file.close();
    } else {
        std::cerr << "Unable to open file for writing" << std::endl;
    }
}

MusicLibrary* FileManager::load_from_file(std::string fileName)
{
    MusicLibrary* libraryToLoad = new MusicLibrary(fileName);

    std::ifstream f(fileName + ".json");
    nlohmann::json j = nlohmann::json::parse(f);
    for (const auto& t : j["tracks"]) {
        Track *currentTrack = new Track();
        currentTrack->title = t["titel"];
        currentTrack->album = t["album"];
        currentTrack->release = t["release"];
        currentTrack->artist = t["artist"];
        currentTrack->duration = t["duration"];
        currentTrack->genere = t["genere"];
        libraryToLoad->add_track(currentTrack);
    }
    return libraryToLoad;
}
