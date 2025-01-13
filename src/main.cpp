#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "MusicLibrary.hpp"
#include "FileManager.hpp"
#include "Playlist.hpp"
#include <filesystem>

using namespace std;

MusicLibrary *musicLibrary;
Playlist *selectedPlaylist = 0;
FileManager fM;

void wait_for_enter()
{
    cout << "Druecken Sie Enter um weiter zu kommen." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');        // chatGPT helped
    cin.get();
}

void printLibraryMenu()
{
    cout << "Music Bibliothek Menu" << endl;
    cout << "Bitte geben Sie die Zahl des Menuepunktes ein." << endl;
    cout << "1. Die Default Bibliothek laden" << endl;
    cout << "2. Alle Bibliotheken ausgeben" << endl;
    cout << "3. per Dateinamen laden" << endl;
    cout << "4. Eine neue Bibliothek erstellen" << endl;
    cout << "5. zurueck" << endl;
}

void create_Library()
{
    cout << "Geben sie den Namen der zu erstellenden Bilbiothek oder Abbrechen ein." << endl;
    string input;
    while (true)
    {
        cin >> input;
        if (input == "Abbrechen")
        {
            cout << "Abgebrochen" << endl;
            break;
        }
        ifstream file(input);
        if (file)
        {
            cout << "Die Datei existiert bereits." << endl;
        }
        else
        {
            musicLibrary = new MusicLibrary(input);
            fM.save_to_file(*musicLibrary);
            cout << "neue Bibliothek wurde erstellt und wurde ausgewaehlt." << endl;
            break;
        }
    }
}

int enter_LibraryName()
{
    cout << "Geben Sie den Namen der Bibliothek zum Oeffnen oder Abbrechen ein." << endl;
    string input, yesno;
    do
    {
        cin >> input;
        if (input == "Abbrechen")
        {
            return -1;
        }
        ifstream file(input + ".json");
        if (file)
        {
            musicLibrary = fM.load_from_file(input);
            cout << "Die Bibliothek wurde geladen." << endl;
            return 5;
        }
        cout << "Die angegebene Datei existiert nicht. Neue erstellen?(Ja/Nein)" << endl;
        while (true)
        {
            cin >> yesno;
            if (yesno == "Ja" || yesno == "ja")
            {
                musicLibrary = new MusicLibrary(input);
                fM.save_to_file(*musicLibrary);
                cout << "neue Bibliothek wurde erstellt und wurde ausgewaehlt." << endl;
                return 5;
            }
            else if (yesno == "Nein" || yesno == "nein")
            {
                cout << "Geben Sie einen anderen Dateinamen ein (oder Abbrechen)" << endl;
                break;
            }
            cout << "Geben Sie nur Ja oder Nein ein" << endl;
        }
    } while (input != "exit");
    return -1;
}


void printAllLibraries()
{
    // chatGPT helped
    try
    {
        for (const auto &entry : filesystem::directory_iterator("./"))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".json")
            {
                std::cout << entry.path().filename() << std::endl;
            }
        }
    }
    catch (const filesystem::filesystem_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void showLibraryMenu()
{
    selectedPlaylist = 0;
    int input;
    do
    {
        printLibraryMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "Die Default Bibliothek wird geladen." << endl;
            fM.create_dummy_data();
            musicLibrary = fM.load_from_file("default");
            input = 5;
            break;
        case 2:
            printAllLibraries();
            break;
        case 3:
            input = enter_LibraryName();
            break;
        case 4:
            create_Library();
            input = 5;
            break;
        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein." << endl;
            break;
        }

    } while (input != 5);
}

void printTitelMenu()
{
    cout << "Titel Menu" << endl;
    cout << "Bitte geben Sie die Zahl des Menuepunktes ein." << endl;
    cout << "1. Alle Titel ausgeben" << endl;
    cout << "2. Titel hinzufuegen" << endl;
    cout << "3. Titel bearbeiten/loeschen" << endl;
    cout << "4. Titel suchen" << endl;
    cout << "5. zurueck" << endl;
}

void titelMenu()
{
    int input;
    string hold;
    do
    {
        printTitelMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            musicLibrary->printTracks();
            wait_for_enter();
            break;
        case 2:
            musicLibrary->add_track();
            break;
        case 3:
            musicLibrary->edit_track();
            break;
        case 4:
            musicLibrary->search_track();
            break;
        case 5:
            break;

        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein." << endl;
            break;
        }

    } while (input != 5);
}

void printPlaylistMenu()
{
    cout << "Playlist Menu" << endl;
    cout << "Bitte geben Sie die Zahl des Menuepunktes ein." << endl;
    cout << "1. Playlist auswaehlen." << endl;
    cout << "2. Neue Playlist hinzufuegen" << endl;
    if (selectedPlaylist != 0)
    {
        cout << "Ausgewaehlte Playlist: " << selectedPlaylist->name << endl;
        cout << "3. Playlist loeschen" << endl;
        cout << "4. Playlist bearbeiten" << endl;
    }
    cout << "5. zurueck" << endl;
}

void playlistMenu()
{
    int input;
    string inputS;
    do
    {
        printPlaylistMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            selectedPlaylist = musicLibrary->selectPlaylists();
            break;
        case 2:
            selectedPlaylist = musicLibrary->add_playlist();
            break;
        case 3:
            if (selectedPlaylist != 0)
            {
                cout << "Sicher? ('ja', alles andere bricht das loeschen ab)" << endl;
                cin >> inputS;
                if (inputS == "Ja" || inputS == "ja")
                {
                    musicLibrary->deletePlaylist(selectedPlaylist);
                    selectedPlaylist = 0;
                }
                else
                {
                    cout << "Dann halt nicht" << endl;
                }
            }
            break;
        case 4:
            if (selectedPlaylist != 0)
            {
                selectedPlaylist->editTracksMenu(musicLibrary->get_tracks());
            }
            break;
        case 5:
            cout << "Biss zum naechsten mal" << endl;
            break;
        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein." << endl;
            break;
        }

    } while (input != 5);
}

void printMainMenu()
{
    cout << "Hauptmenu" << endl;
    cout << "Bitte geben Sie die Zahl des Menuepunktes ein." << endl;
    cout << "1. Bibliothek Menu";
    if (musicLibrary != 0)
    {
        cout << " (Derzeit geladen: " + musicLibrary->get_name() + ")";
    }
    cout << endl;
    if (musicLibrary != 0)
    {
        cout << "2. Titel Menu" << endl;
        cout << "3. Playlist Menu" << endl;
        cout << "4. Speichern und Programm schliessen" << endl;
    }
    cout << "5. Programm schliessen" << endl;
}

int mainMenu()
{
    int input;
    do
    {
        printMainMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            showLibraryMenu();
            break;
        case 2:
            if (musicLibrary != 0)
            {
                titelMenu();
            }
            break;
        case 3:
            if (musicLibrary != 0)
            {
                playlistMenu();
            }
            break;
        case 4:
            cout << "Es wird gespeichert." << endl;
            fM.save_to_file(*musicLibrary);
            break;
        case 5:
            cout << "Biss zum naechsten mal" << endl;
            break;

        default:
            cout << "Bitte geben Sie eine gültige Zahl ein." << endl;
            break;
        }

    } while (input != 4 && input != 5);
    return 0;
}

int main()
{
    mainMenu();
    return 0;
}
