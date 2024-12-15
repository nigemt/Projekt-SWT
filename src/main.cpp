#include <iostream>
#include <string>

using namespace std;

void printTitelMenu() {
    cout << "Titel Menue" << endl;
    cout << "Bitte wählen Sie aus was sie tun wollen." << endl;
    cout << "1. Alle Titel ausgeben" << endl;
    cout << "2. Titel hinzufügen" << endl;
    cout << "3. Titel loeschen" << endl;
    cout << "4. Titel bearbeiten" << endl;
    cout << "5. zurueck" << endl;
}


void titelMenu() {
    int input;
    do {
        printTitelMenu();
        cin >> input;
        switch (input)
        {
            case 1:
                cout << "Alle ausgeben" << endl;
                break;
            case 2:
                cout << "hinzufügen" << endl;
                break;
            case 3:
                cout << "löschen" << endl;
                break;
            case 4:
                cout << "bearbeiten" << endl;
                break;
            case 5:
                cout << "Bis zum nächsten mal" << endl;
                break;
            
            default:
                cout << "Bitte gültige Zahl eingeben" << endl;
                break;
        
    }
} while (input !=5);
}

void printPlaylistMenu() {
    cout << "Playlist Menue" << endl;
    cout << "Bitte wählen Sie aus was sie tun wollen." << endl;
    cout << "1. Alle Playlists augeben" << endl;
    cout << "2. Playlist hinzufügen" << endl;
    cout << "3. Playlist löschen" << endl;
    cout << "4. Playlist bearbeiten" << endl;
    cout << "5. zurueck" << endl;
}

void playlistMenu() {
    int input;
    do {
        printTitelMenu();
        cin >> input;
        switch (input)
        {
            case 1:
                cout << "Alle ausgeben" << endl;
                break;
            case 2:
                cout << "hinzufügen" << endl;
                break;
            case 3:
                cout << "löschen" << endl;
                break;
            case 4:
                cout << "bearbeiten" << endl;
                break;
            case 5:
                cout << "Bis zum nächsten mal" << endl;
                break;
            
            default:
                cout << "Bitte gültige Zahl eingeben" << endl;
                break;
        
    }
} while (input !=5);
}

void printMainMenu() {
    cout << "Hauptmenue" << endl;
    cout << "Bitte wählen Sie aus was sie tun wollen." << endl;
    cout << "1. Titel Menue" << endl;
    cout << "2. Playlist Menue" << endl;
    cout << "3. Programm schließen" << endl;
}

int mainMenu() {
    int input;
    do{
        printMainMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            titelMenu();
            break;
        case 2:
            playlistMenu();
            break;
        case 3:
            cout << "Bis zum nächsten mal" << endl;
               break;

        default:
            cout << "Bitte geben Sie eine gültige Zahl ein" << endl;
            break;
        }

    } while (input != 3);
    return 0;
}

int main() {
    mainMenu();
    return 0;
}