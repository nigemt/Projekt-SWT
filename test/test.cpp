#define CATCH_CONFIG_MAIN
#include "FileManager.hpp"
#include "MusicLibrary.hpp"
#include <catch.hpp>
#include <fstream>
#include <iostream>

TEST_CASE("default.json Tests")
{
    FileManager fm;
    std::remove("default.json");
    ifstream file("default.json");
    REQUIRE(!file);

    SECTION("Erstellen der default.json")
    {
        MusicLibrary *mL;
        fm.create_dummy_data();
        ifstream file2("default.json");
        REQUIRE(file2);

        SECTION("Einlesen der default.json")
        {
            mL = fm.load_from_file("default");
            REQUIRE(mL->get_playlists().size() == 1);
            REQUIRE(mL->get_tracks().size() == 3);
        }

        SECTION("Speichern mit zusaetzlichem Track")
        {
            Track *T = new Track();
            T->title = "zum Test";
            mL = fm.load_from_file("default");
            mL->add_track(T);
            fm.save_to_file(*mL);

            mL = fm.load_from_file("default");
            REQUIRE(mL->get_playlists().size() == 1);
            REQUIRE(mL->get_tracks().size() == 4);
        }
    }
    // cleanup
    std::remove("default.json");
}

TEST_CASE("Bibliothek Tests")
{
    MusicLibrary testLibrary("irrelevant");
    Track *t = new Track();
    Playlist *p = new Playlist();

    SECTION("Track hinzufuegen")
    {
        REQUIRE(testLibrary.get_tracks().size() == 0);
        testLibrary.add_track(t);
        REQUIRE(testLibrary.get_tracks().size() == 1);

        SECTION("Track entfernen")
        {
            testLibrary.deleteTrack(t);
            REQUIRE(testLibrary.get_tracks().size() == 0);
        }
    }

    SECTION("Playlist hinzufuegen")
    {
        REQUIRE(testLibrary.get_playlists().size() == 0);
        testLibrary.add_playlist(p);
        REQUIRE(testLibrary.get_playlists().size() == 1);

        SECTION("Playlist entfernen")
        {
            testLibrary.deletePlaylist(p);
            REQUIRE(testLibrary.get_playlists().size() == 0);
        }
    }
}

TEST_CASE("Playlist Tests")
{
    Track *t = new Track();
    Playlist *p = new Playlist();

    SECTION("Track hinzufuegen")
    {
        REQUIRE(p->getTracks().size() == 0);
        p->addTrack(t);
        REQUIRE(p->getTracks().size() == 1);

        SECTION("Track enthalten?")
        {
            REQUIRE(p->containsTrack(t));
            Track *n = new Track();
            REQUIRE(!p->containsTrack(n));
        }

        SECTION("Track entfernen")
        {
            p->removeTrack(t);
            REQUIRE(p->getTracks().size() == 0);
        }
    }
}
