#include "MusicLibrary.hpp"
#include "json.hpp"
#include <fstream>
#include <limits>
#include <iostream>

using namespace std;

void MusicLibrary::showEditTrackMenu()
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

void MusicLibrary::selectTrack()
{
    int inputI;
    printTracks();
    cout << "Waehlen Sie einen der Songs aus indem Sie die ID (Links vom Titel) eingeben oder -1 zum Abbrechen." << endl;
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

void MusicLibrary::showeditMetaDataOfTrackMenu()
{
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

void MusicLibrary::editMetaDataOfTrack()
{
    int inputI = 7;
    string inputS;
    do
    {
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

void MusicLibrary::print_search_track_menu()
{
    cout << "Suche." << endl;
    cout << "1. Suche nach Titel" << endl;
    cout << "2. Suche nach Album" << endl;
    cout << "3. Suche nach Kuenstler" << endl;
    cout << "4. Suche nach Genere" << endl;
    cout << "5. Suche nach Erscheinungsjahr" << endl;
    cout << "6. Suche nach Dauer in sekunden" << endl;
    cout << "7. Abbrechen" << endl;
}

void MusicLibrary::wait_for_enter()
{
    cout << "Druecken Sie Enter um weiter zu kommen." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void MusicLibrary::delete_Track_prompt()
{

    cout << "Soll der Track wirklich gelöscht werden? (Ja/Nein)" << endl;
    string inputS;
    while (true)
    {
        cin >> inputS;
        if (inputS == "Ja" || inputS == "ja")
        {
            deleteTrack(selectedTrack);
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

Track *MusicLibrary::get_selected_track()
{
    return selectedTrack;
}

bool MusicLibrary::has_selected_track()
{
    return selectedTrack != 0;
}

MusicLibrary::MusicLibrary(string newname)
{
    name = newname;
    selectedTrack = 0;
}

void MusicLibrary::add_track()
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
        cout << "Bitte geben Sie eine Zahl ein" << endl;
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
        cout << "Bitte geben Sie eine Zahl ein" << endl;
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
    track.push_back(toAdd);
    cout << "folgender Song wurde hinzugefuegt:" << endl;
    toAdd->printTrack(-1);
}

void MusicLibrary::add_playlist(Playlist *toAdd)
{
    playlist.push_back(toAdd);
}

void MusicLibrary::add_track(Track *trackToAdd)
{
    track.push_back(trackToAdd);
}

void MusicLibrary::printTracks()
{
    if (track.size() == 0)
    {
        std::cout << "Keine Songs zu dieser Bibliothek hinzugefuegt." << endl;
    }
    for (int i = 0; i < track.size(); ++i)
    {
        track.at(i)->printTrack(i + 1);
    }
}

vector<Track *> MusicLibrary::get_tracks()
{
    return track;
}

vector<Playlist *> MusicLibrary::get_playlists()
{
    return playlist;
}

std::string MusicLibrary::get_name()
{
    return name;
}

void MusicLibrary::set_name(std::string newname)
{
    name = newname;
}

void MusicLibrary::deleteTrack(Track *todelete)
{
    track.erase(find(track.begin(), track.end(), todelete));

    delete todelete;
}

void MusicLibrary::edit_track()
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
                delete_Track_prompt();
            }
            break;
        case 4:
            selectedTrack = 0;
            break;

        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein." << endl;
            break;
        }
    } while (inputI != 4);
}

void MusicLibrary::search_track()
{
    int inputI = 7;
    bool foundSomething;
    string inputS;
    Track *currentTrack;
    do
    {
        foundSomething = false;
        print_search_track_menu();
        cin >> inputI;
        switch (inputI)
        {
        case 1:
            cout << "Geben Sie einen Titel ein den Sie suchen wollen." << endl;
            cin >> inputS;
            for (int i = 0; i < track.size(); i++)
            {
                currentTrack = track.at(i);
                // find returns npos if the input does not appear in the title variable (ChatGPT told me)
                if (currentTrack->title.find(inputS) != string::npos)
                {
                    currentTrack->printTrack(i + 1);
                    foundSomething = true;
                }
            }
            if (!foundSomething)
                cout << "Leider wurde nichts gefunden" << endl;
            wait_for_enter();
            break;
        case 2:
            cout << "Geben Sie ein Album ein nach dem Sie suchen wollen." << endl;
            cin >> inputS;
            for (int i = 0; i < track.size(); i++)
            {
                currentTrack = track.at(i);
                // find returns npos if the input does not appear in the title variable (ChatGPT told me)
                if (currentTrack->album.find(inputS) != string::npos)
                {
                    currentTrack->printTrack(i + 1);
                    foundSomething = true;
                }
            }
            if (!foundSomething)
                cout << "Leider wurde nichts gefunden" << endl;
            wait_for_enter();
            break;
        case 3:
            cout << "Geben Sie einen Kuenstler ein den Sie suchen wollen." << endl;
            cin >> inputS;
            for (int i = 0; i < track.size(); i++)
            {
                currentTrack = track.at(i);
                // find returns npos if the input does not appear in the title variable (ChatGPT told me)
                if (currentTrack->artist.find(inputS) != string::npos)
                {
                    currentTrack->printTrack(i + 1);
                    foundSomething = true;
                }
            }
            if (!foundSomething)
                cout << "Leider wurde nichts gefunden" << endl;
            wait_for_enter();
            break;
        case 4:
            cout << "Geben Sie ein Genere ein nach dem Sie suchen wollen." << endl;
            cin >> inputS;
            for (int i = 0; i < track.size(); i++)
            {
                currentTrack = track.at(i);
                // find returns npos if the input does not appear in the title variable (ChatGPT told me)
                if (currentTrack->genere.find(inputS) != string::npos)
                {
                    currentTrack->printTrack(i + 1);
                    foundSomething = true;
                }
            }
            if (!foundSomething)
                cout << "Leider wurde nichts gefunden" << endl;
            wait_for_enter();
            break;
        case 5:
            cout << "Geben Sie ein Erscheinungsjahr ein nach dem Sie suchen wollen." << endl;
            cin >> inputI;
            for (int i = 0; i < track.size(); i++)
            {
                currentTrack = track.at(i);
                // find returns npos if the input does not appear in the title variable (ChatGPT told me)
                if (currentTrack->release = inputI)
                {
                    currentTrack->printTrack(i + 1);
                    foundSomething = true;
                }
            }
            if (!foundSomething)
                cout << "Leider wurde nichts gefunden" << endl;
            wait_for_enter();
            break;
        case 6:
            cout << "Geben Sie eine Dauer in sekunden ein nach der Sie suchen wollen." << endl;
            cin >> inputI;
            for (int i = 0; i < track.size(); i++)
            {
                currentTrack = track.at(i);
                // find returns npos if the input does not appear in the title variable (ChatGPT told me)
                if (currentTrack->duration = inputI)
                {
                    currentTrack->printTrack(i + 1);
                    foundSomething = true;
                }
            }
            if (!foundSomething)
                cout << "Leider wurde nichts gefunden" << endl;
            wait_for_enter();
            break;
        case 7:

            break;

        default:
            cout << "Bitte geben Sie eine gueltige Zahl ein" << endl;
            break;
        }
    } while (inputI != 7);
}
