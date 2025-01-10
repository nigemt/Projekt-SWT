#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "MusicLibrary.hpp"
#include "FileManager.hpp"
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




