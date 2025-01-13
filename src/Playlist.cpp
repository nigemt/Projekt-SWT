#include "Playlist.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

//Verwaltung Playlist

using namespace std;

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

void Playlist::removeTrack()
{
    cout << "Die Songs in der Playliste werden nun ausgegeben, geben Sie die ID/Zahl (Links vom Titel) ein um den SOng "
            "zu entfernen. -1 zum Abbrechen"
         << endl;
    int inputI;
    do
    {
        printPlaylist();
        cin >> inputI;
        if (inputI > 0 && inputI <= track.size())
        {
            removeTrack(track.at(inputI - 1));
        }
    } while (inputI != -1);
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
        track.at(i)->printTrack(i + 1);
    }
}

void Playlist::addTrackMenu(vector<Track *> selectableTrack)
{
    cout << "Es werden jetzt alle Songs ausgegeben, die hinzugefuegt werden koennen." << endl;
    cout << "Geben Sie die ID/Zahl links vom Titel ein um den Song hinzuzufuegen. -1 um Abzubrechen." << endl;
    int inputI;
    Track *currentTrack;
    bool hasSongsToAdd;
    do
    {
        hasSongsToAdd = false;
        for (int i = 0; i < selectableTrack.size(); i++)
        {
            currentTrack = selectableTrack.at(i);
            if (!containsTrack(currentTrack))
            {
                currentTrack->printTrack(i + 1);
                hasSongsToAdd = true;
            }
        }
        if (!hasSongsToAdd)
        {
            cout << "Sieht so aus als ob die Playlist bereits alle Songs beinhaltet." << endl;
            return;
        }
        cin >> inputI;
        if (inputI > 0 && inputI <= selectableTrack.size())
        {
            currentTrack = selectableTrack.at(inputI - 1);
            if (!containsTrack(currentTrack))
            {
                addTrack(currentTrack);
                cout << currentTrack->title << " hinzugefuegt." << endl;
                wait_for_enter();
            }
        }
        else if (inputI == -1)
        {
            cout << "Abgebrochen" << endl;
        }
        else
        {
            cout << "Bitte eine gueltige Zahl eingeben." << endl;
        }
    } while (inputI != -1);
}

void Playlist::printEditTracksMenu()
{
    cout << "Playlist bearbeiten" << endl;
    cout << "1. Playlist nochmal ausgeben." << endl;
    cout << "2. Namen Aendern (" << name << ")" << endl;
    cout << "3. Songs hinzufuegen" << endl;
    cout << "4. Songs entfernen" << endl;
    cout << "5. Abbrechen" << endl;
}

void Playlist::editTracksMenu(vector<Track *> availableTracks)
{
    int inputI;
    string inputS;
    do
    {
        printEditTracksMenu();
        cin >> inputI;
        switch (inputI)
        {
        case 1:
            printPlaylist();
            break;
        case 2:
            cout << "Geben Sie den neuen Namen ein oder Abbrechen." << endl;
            cin >> inputS;
            if (inputS == "Abbrechen")
            {
                cout << "Name nicht geaendert" << endl;
                break;
            }
            name = inputS;
            break;
        case 3:
            addTrackMenu(availableTracks);
            break;
        case 4:
            removeTrack();
            break;
        case 5:
            /* code */
            break;

        default:
            break;
        }
    } while (inputI != 5);
}

void Playlist::wait_for_enter()
{
    cout << "Druecken Sie Enter um weiter zu kommen." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
