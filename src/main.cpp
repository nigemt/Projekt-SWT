#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "MusicLibrary.hpp"
#include "FileManager.hpp"

using namespace std;

MusicLibrary *musicLibrary;
Track *selectedTrack;
FileManager fM;

void create_dummy_data()
{
    MusicLibrary testdummy("default");
    Track *testTrack = new Track();
    testTrack->title = "Never Gonna Give You Up";
    testTrack->album = "Secretly EVERY ALBUM";
    testTrack->duration = 3 * 60;
    testTrack->release = 0;
    testTrack->genere = "EVERYTHING";
    testTrack->artist = "Rick Astley";
    testdummy.add_track(testTrack);
    testTrack = new Track();
    testTrack->title = "HEYYEYAAEYAAAEYAEYAA";
    testTrack->album = "-";
    testTrack->duration = 2 * 60 + 6;
    testTrack->release = 0;
    testTrack->genere = "-";
    testTrack->artist = "-";
    testdummy.add_track(testTrack);
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
    cout << "4. zurueck" << endl;
}

void add_track()
{
    string inputS;
    int inputI;
    Track *toAdd = new Track();
    cout << "Sie koennen jederzeit Abbrechen durch die Eingabe 'Abbrechen' oder '-1'" << endl;
    cout << "Geben Sie den Titel ein." << endl;
    cin >> inputS;
    if (inputS == "Abbrechen")
    {
        cout << "Abgebrochen." << endl;
        return;
    }
    else
        toAdd->title = inputS;
    cout << "Geben Sie den Namen des Albums ein." << endl;
    cin >> inputS;
    if (inputS == "Abbrechen")
    {
        cout << "Abgebrochen." << endl;
        return;
    }
    else
        toAdd->album = inputS;
    cout << "Geben Sie den Kuenstler ein." << endl;
    cin >> inputS;
    if (inputS == "Abbrechen")
    {
        cout << "Abgebrochen." << endl;
        return;
    }
    else
        toAdd->artist = inputS;
    cout << "Geben Sie das Genere ein." << endl;
    cin >> inputS;
    if (inputS == "Abbrechen")
    {
        cout << "Abgebrochen." << endl;
        return;
    }
    else
        toAdd->genere = inputS;
    cout << "Geben Sie das Erscheinungsjahr ein." << endl;
    cin >> inputI;
    // chatGPT helped for wrong input..
    while (cin.fail())
    {
        cout << "Bitte geben Sie eine Zahl ein" << std::endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> inputI;
    }
    if (inputI == -1)
    {
        cout << "Abgebrochen." << endl;
        return;
    }
    else
        toAdd->release = inputI;
    cout << "Geben Sie die Dauer in sekunden ein." << endl;
    cin >> inputI;
    // chatGPT helped for wrong input..
    while (cin.fail())
    {
        cout << "Bitte geben Sie eine Zahl ein" << std::endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> inputI;
    }
    if (inputI == -1)
    {
        cout << "Abgebrochen." << endl;
        return;
    }
    else
    {
        toAdd->duration = inputI;
    }

    musicLibrary->add_track(toAdd);
}

void showEditTrackMenu()
{
    cout << "Bearbeiten von einem Song." << endl;
    if (selectedTrack == 0)
    {
        cout << "1. Song auswaehlen" << endl;
    }
    else
    {
        cout << "1. Ausgewaehlten Song wechseln. (Derzeit ausgewaehlt: '" << selectedTrack->title << "' )" << endl;
        cout << "2. Metadaten bearbeiten" << endl;
        cout << "3. Titel loeschen" << endl;
    }
    cout << "4. zurueck" << endl;
}

void selectTrack()
{
    int inputI;
    musicLibrary->printTracks();
    cout << "Waehlen Sie einen der Songs aus indem Sie die ID (Links vom Titel) eingeben oder -1 zum Abbrechen." << endl;
    vector<Track *> track = musicLibrary->get_tracks();
    do
    {
        cin >> inputI;
        if (inputI > 0 && inputI <= track.size())
        {
            selectedTrack = track.at(inputI - 1);
            cout << "Track ausgewaehlt: " << selectedTrack->title << endl;
            break;
        }
        else if (inputI == -1)
        {
            cout << "abgebrochen" << endl;
        }
    } while (inputI != -1);
}

void showeditMetaDataOfTrackMenu() {
    cout << "Metadaten bearbeiten von folgendem Song: " << endl;
    selectedTrack->printTrack(-1);
    cout << "1. Titel Aendern" << endl;
    cout << "2. Album Aendern" << endl;
    cout << "3. Kuenstler Aendern" << endl;
    cout << "4. Genere Aendern" << endl;
    cout << "5. Erscheinungsjahr Aendern" << endl;
    cout << "6. Dauer in sekunden Aendern" << endl;
    cout << "7. Abbrechen" << endl;
}

void editMetaDataOfTrack() {
    int inputI = 7;
    string inputS;
    do {
        showeditMetaDataOfTrackMenu();
        cin >> inputI;
        switch (inputI)
        {
        case 1:
            cout << "Geben Sie den neuen Titel ein." << endl;
            cin >> inputS;
            selectedTrack->title = inputS;
            break;
        case 2:
            cout << "Geben Sie den neuen Albumnamen ein." << endl;
            cin >> inputS;
            selectedTrack->album = inputS;
            break;
        case 3:
            cout << "Geben Sie den neuen Kuenstler ein." << endl;
            cin >> inputS;
            selectedTrack->artist = inputS;
            break;
        case 4:
            cout << "Geben Sie das neue Genere ein." << endl;
            cin >> inputS;
            selectedTrack->genere = inputS;
            break;
        case 5:
            cout << "Geben Sie das neue Erscheinungsjahr ein." << endl;
            cin >> inputI;
            selectedTrack->release = inputI;
            inputI = -1;
            break;
        case 6:
            cout << "Geben Sie die neue Dauer in Sekunden ein." << endl;
            cin >> inputI;
            selectedTrack->duration = inputI;
            inputI = -1;
            break;
        case 7:
            /* code */
            break;

        default:
            break;
        }
    } while (inputI != 7);
}

void deleteTrack()
{
    cout << "Soll der Track wirklich gelöscht werden? (Ja/Nein)" << endl;
    string inputS;
    while (true)
    {
        cin >> inputS;
        if (inputS == "Ja" || inputS == "ja")
        {
            musicLibrary->deleteTrack(selectedTrack);
            cout << "Song wurde geloescht." << endl;
            selectedTrack = 0;
            break;
        }
        else if (inputS == "Nein" || inputS == "nein")
        {
            cout << "Song wurde nicht geloescht." << endl;
            break;
        }
        cout << "Geben Sie nur Ja oder Nein ein" << endl;
    }
}

void editTrack()
{
    int inputI;
    string inputS;
    do
    {
        showEditTrackMenu();
        cin >> inputI;
        switch (inputI)
        {
        case 1:
            selectTrack();
            break;
        case 2:
            if (selectedTrack != 0)
            {
                editMetaDataOfTrack();
            }
            break;
        case 3:
            if (selectedTrack != 0)
            {
                deleteTrack();
            }
            break;
        case 4:
            /* code */
            break;

        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein." << endl;
            break;
        }
    } while (inputI != 4);
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
            cout << "Enter um zu dem Menue zu springen." << endl;
            // wait for user to hit enter
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        case 2:
            add_track();
            break;
        case 3:
            editTrack();
            break;
        case 4:
            cout << "Biss zum naechsten mal" << endl;
            break;

        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein." << endl;
            break;
        }

    } while (input != 4);
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
    do
    {
        printPlaylistMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "hier alle playlists ausgeben" << endl;

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
    }
    cout << "4. Programm schliessen und speichern" << endl;
    cout << "5. Programm schliessen aber nicht speichern" << endl;
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
void nope()
{
}

int main()
{
    mainMenu();
    nope();
    return 0;
}
