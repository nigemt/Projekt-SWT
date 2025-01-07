
#pragma once
#include <vector>
#include "Track.hpp"
#include "Playlist.hpp"
class MusicLibrary
{
private:
    vector<Track *> track;
    vector<Playlist*> playlist;
    std::string name;
    Track *selectedTrack;

    void showEditTrackMenu();
    void selectTrack();
    void showeditMetaDataOfTrackMenu();
    void editMetaDataOfTrack();
    void print_search_track_menu();
    void wait_for_enter();
void delete_Track_prompt();
public:
    Track *get_selected_track();
    bool has_selected_track();
    MusicLibrary(std::string newname);
    void add_track();
    void add_playlist(Playlist *toAdd);
    void add_track(Track *trackToAdd);
    void printTracks();
    vector<Track *> get_tracks();
    vector<Playlist *> get_playlists();
    std::string get_name();
    void set_name(std::string newname);
    void deleteTrack(Track *todelete);
    void edit_track();
    void search_track();
};