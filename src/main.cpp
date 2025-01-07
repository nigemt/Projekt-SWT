#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "MusicLibrary.hpp"
#include "FileManager.hpp"
#include "Playlist.hpp"

using namespace std;

MusicLibrary *musicLibrary;
FileManager fM;

void wait_for_enter()
{
    cout << "Druecken Sie Enter um weiter zu kommen." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // chatGPT helped
    cin.get();
}

void create_dummy_data()
{
    MusicLibrary testdummy("default");
    Track *testTrack = new Track();
    Playlist *testPlaylist = new Playlist();
    testPlaylist->name = "goat";
    testTrack->title = "Never Gonna Give You Up";
    testTrack->album = "Secretly EVERY ALBUM";
    testTrack->duration = 3 * 60;
    testTrack->release = 0;
    testTrack->genere = "EVERYTHING";
    testTrack->artist = "Rick Astley";
    testdummy.add_track(testTrack);
    testPlaylist->addTrack(testTrack);
    testTrack = new Track();
    testTrack->title = "HEYYEYAAEYAAAEYAEYAA";
    testTrack->album = "-";
    testTrack->duration = 2 * 60 + 6;
    testTrack->release = 0;
    testTrack->genere = "-";
    testTrack->artist = "-";
    testdummy.add_track(testTrack);
    testPlaylist->addTrack(testTrack);
    testTrack = new Track();
    testTrack->title = "Song in no Playlist";
    testTrack->album = "-";
    testTrack->duration = 2 * 60 + 6;
    testTrack->release = 0;
    testTrack->genere = "-";
    testTrack->artist = "-";
    testdummy.add_track(testTrack);
    testdummy.add_playlist(testPlaylist);
    fM.save_to_file(testdummy);
}

void printLibraryMenu()
{

    cout << "Music Bibliothek Menu" << endl;
    cout << "Bitte geben Sie die Zahl des Menuepunktes ein." << endl;
    cout << "1. Die Default Bibliothek laden" << endl;
    cout << "2. per Dateinamen laden" << endl;
    cout << "3. Eine neue Bibliothek erstellen" << endl;
    cout << "4. zurueck" << endl;
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
        ifstream file(input);
        if (file)
        {
            musicLibrary = fM.load_from_file(input);
            cout << "Die Bibliothek wurde geladen." << endl;
            return 4;
        }
        cout << "Die angegebene Datei existiert nicht. Neue erstellen?(Ja/Nein)" << endl;
        cin >> yesno;
        while (true)
        {
            if (yesno == "Ja" || yesno == "ja")
            {
                musicLibrary = new MusicLibrary(input);
                fM.save_to_file(*musicLibrary);
                cout << "neue Bibliothek wurde erstellt und wurde ausgewaehlt." << endl;
                return 4;
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

void showLibraryMenu()
{
    int input;
    do
    {
        printLibraryMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "Die Default Bibliothek wird geladen." << endl;
            create_dummy_data();
            musicLibrary = fM.load_from_file("default");
            input = 4;
            break;
        case 2:
            input = enter_LibraryName();
            break;
        case 3:
            create_Library();
            input = 4;
            break;

        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein." << endl;
            break;
        }

    } while (input != 4);
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
    cout << "1. Alle Playlists ausgeben" << endl;
    cout << "2. Playlist hinzufuegen" << endl;
    cout << "3. Playlist loeschen" << endl;
    cout << "4. Playlist bearbeiten" << endl;
    cout << "5. zurueck" << endl;
}

void playlistMenu()
{
    int input;
    vector<Playlist*> toPrint = musicLibrary->get_playlists();
    do
    {
        printPlaylistMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            for (int i = 0; i < toPrint.size(); i++)
            {
                cout << i+1 << " " << toPrint.at(i)->name << endl;
            }
            wait_for_enter();
            break;
        case 2:
            cout << "hier playlist hinzufuegen" << endl;
            break;
        case 3:
            cout << "hier playlist loeschen" << endl;
            break;
        case 4:
            cout << "hier playlist bearbeiten" << endl;
            break;
        case 5:
            cout << "Biss zum naechsten mal" << endl;
            break;
        default:
            cout << "Bitte geben Sie eine gültige Zahl ein." << endl;
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
        case 1:
            showLibraryMenu();
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
