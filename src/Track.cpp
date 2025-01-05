#include "Track.hpp"
#include <iostream>

void Track::printTrack(int id)
{
    if (id != -1)
        std::cout << id << ": ";
    std::cout << title << std::endl;
    std::cout << "\tAlbum:" << album << " Kuenstler: " << artist << " Erscheinungsjahr: " << release << endl;
    std::cout << "\tDauer:" << duration << " Genere: " << genere << endl;
}