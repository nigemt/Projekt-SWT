
#pragma once
#include "MusicLibrary.hpp"
#include <string>
class MusicLibrary;
class FileManager
{
public:
    void save_to_file(MusicLibrary musicLibrary, std::string filePath);
    MusicLibrary* load_from_file(std::string filePath);
};