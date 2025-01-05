#pragma once
#include <string>

using namespace std;

class Track
{
private:

public:
    string title;
    string artist;
    int release;
    string album;
    string genere;
    int duration;

    void printTrack(int id);
};