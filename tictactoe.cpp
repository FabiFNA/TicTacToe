#include <iostream>
#include <cstring>
#include <random>
using namespace std;

char feld[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; // 65 = A  32 = leerzeichen
char possibleTurns[10] = { '0', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A' };
bool gewonnen = false;

bool gewonnen1 = false;
bool gewonnen2 = false;

int player = 1;
bool falscheEingabe = false;
int runs = 2;
int eingabe = 0;

int suggestedTurn = 0;
int lastTurn = 0;
bool erstesMal = true;

bool KI = false;
int bestTurn = 0;

bool beenden = false;

string spieler1;
string spieler2;

int zufallsZahl = 0;

int zahlGenerieren()
{
    // VON CHATGPT:

    // Erstelle einen Zufallszahlengenerator
    random_device rd;
    mt19937 generator(rd()); // Mersenne Twister-Engine mit random_device initialisieren

    // Definiere die Verteilung für Zahlen zwischen 1 und 9
    uniform_int_distribution<> generieren(1, 9);

    // Generiere eine Zufallszahl zwischen 1 und 9
    return zufallsZahl = generieren(generator);
}

void resetSuggestions()
{
    for (int i = 1; i < 10; i++)
    {
        possibleTurns[i] = 'A';
    }
}

void draw_spielfeld(char x[10])
{
    system("cls");

    cout << endl;

    cout << "    0   1   2 " << endl << endl;
    cout << "0   " << x[1] << " | " << x[2] << " | " << x[3] << endl; // variablen einsetzen
    cout << "   ---+---+---" << endl;
    cout << "1   " << x[4] << " | " << x[5] << " | " << x[6] << endl; // variablen einsetzen
    cout << "   ---+---+---" << endl;
    cout << "2   " << x[7] << " | " << x[8] << " | " << x[9] << endl; // variablen einsetzen

    if (falscheEingabe == true)
    {
        cout << endl << "Falsche Eingabe! " << endl;
    }

    cout << endl;
}

int input()
{
    if (player == 1)
    {
        cout << spieler1 << " ( X ) - Eingabe: ";
        cin >> eingabe;
        lastTurn = eingabe;

        if (eingabe < 1 || eingabe > 9 || feld[eingabe] == 'X' || feld[eingabe] == 'O')
        {
            falscheEingabe = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            feld[eingabe] = 'X';
            falscheEingabe = false;
        }
    }

    if (player == 2)
    {
        if (KI == false)
        {
            cout << spieler2 << " ( O ) - Eingabe: ";
            cin >> eingabe;

            if (eingabe < 1 || eingabe > 9 || feld[eingabe] == 'X' || feld[eingabe] == 'O')
            {
                falscheEingabe = true;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                feld[eingabe] = 'O';
                falscheEingabe = false;
            }
        }
        else if (KI == true)
        {
            if (runs == 3)
            {
                zahlGenerieren();

                if (feld[zufallsZahl] == 'X' || feld[zufallsZahl] == 'O')
                {
                    falscheEingabe = true;
                    zahlGenerieren();
                }
                else
                {
                    feld[zufallsZahl] = 'O';
                    cout << "\n\nERSTER ZUG (ZUFALLSGENERIERT)\n\n" << endl;
                    falscheEingabe = false;
                    erstesMal = false;
                }
            }
            else
            {
                // prüft ob auf dem possibleTurns-feld platziert werden kann (isOccupied by 'X' or 'O' && ist eine zahl zwischen 1 und 9 (feld bezeichner))
                for (int i = 0; i < 10; i++)
                {
                    cout << "\nInput-KI durchlauf: " << i << endl;
                    if (possibleTurns[i] == 'B')
                    {
                        //cout << "\n\nPOSSIBLE TURN AT " << i << "\n\n";
                        if (feld[i] != 'X' && feld[i] != 'O')
                        {
                            feld[i] = 'O';
                            cout << "\n\nVORGESCHLAGENER ZUG\n\n";
                            //resetSuggestions();
                            erstesMal = false;
                            beenden = false;
                            break;
                        }

                    }

                    if (i == 9)
                    {
                        cout << "\n\n\n[WICHTIG] i hat 9 erreicht\n\n\n";
                        beenden = false;
                        while (beenden == false)
                        {
                            zahlGenerieren();

                            cout << "\n\n\n[WICHTIG] while schleife in KI erreicht\n\n\n";

                            if (feld[zufallsZahl] == 'X' || feld[zufallsZahl] == 'O')
                            {
                                cout << "\n\nUNZULAESSIGE ZUFALLSZAHL\n\n";
                                falscheEingabe = true;
                                erstesMal = false;
                                zahlGenerieren();
                                continue;
                            }
                            else
                            {
                                feld[zufallsZahl] = 'O';
                                cout << "\n\nSPAETERER ZUG (ZUFALLSGENERIERT)\n\n";
                                falscheEingabe = false;
                                erstesMal = false;
                                beenden = true;
                                break;
                            }
                        }
                        continue;
                    }
                }
            }
        }
    }
    return player;
}

bool checkwin(char x[10])
{
    if (x[1] == x[2] && x[2] == x[3])
    {
        if (x[2] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[2] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else if (x[4] == x[5] && x[5] == x[6])
    {
        if (x[5] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[5] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else if (x[7] == x[8] && x[8] == x[9])
    {
        if (x[8] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[8] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else if (x[1] == x[4] && x[4] == x[7])
    {
        if (x[4] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[4] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else if (x[2] == x[5] && x[5] == x[8])
    {
        if (x[5] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[5] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else if (x[3] == x[6] && x[6] == x[9])
    {
        if (x[6] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[6] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else if (x[1] == x[5] && x[5] == x[9])
    {
        if (x[5] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[5] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else if (x[3] == x[5] && x[5] == x[7])
    {
        if (x[5] == 'X')
        {
            gewonnen1 = true;
        }
        if (x[5] == 'O')
        {
            gewonnen2 = true;
        }
        gewonnen = true;
        return true;
    }
    else
    {
        gewonnen = false;
        return false;
    }
}

int setplayer() // wechselt den spieler nach einer runde wenn die eingabe richtig ist
{
    int pruef = runs % 2;

    if (pruef == 0)
    {
        player = 2;
    }
    else if (pruef == 1)
    {
        player = 1;
    }
    return player;
}


/* ALTER CODE  ---  ALTER CODE  ---  ALTER CODE  ---  ALTER CODE  ---  ALTER CODE  ---  ALTER CODE



void turnCalc(char x[])
{
    bool zweiInFolge = false;

    if (runs > 2)
    {
        for (int i = 1; i <= 9; i++)
        {
            if (x[i] == 'X')
            {





                cout << i << " ist ein X" << endl;

                if (x[i + 1] == 'X')
                {
                    cout << "TESTESTESTZwei +X in folge\n";

                    if ((i - 1 == 2) || (i + 1 == 2))
                    {
                        if (x[i - 1] == 'X' && zweiInFolge == false)
                        {
                            zweiInFolge = true;
                            suggestedTurn = 1;
                            cout << "SUGGESTEDTURN = " << suggestedTurn << endl;
                        }
                        if (x[i + 1] == 'X' && zweiInFolge == false)
                        {
                            zweiInFolge = true;
                            suggestedTurn = 3;
                        }
                    }

                    cout << "SuggestedTurn: " << suggestedTurn << endl; // hier ist suggestedTurn 0 weil die vorherige if-schleife nicht getriggert wurde, also standartwert nach definition 0
                }
                if (x[i - 1] == 'X')
                {
                    cout << "Zwei -X in folge\n";

                    if ((i - 1 == 2) || (i + 1 == 2))
                    {
                        if (x[i - 1] == 'X')
                        {
                            suggestedTurn = 1;
                        }
                        if (x[i + 1] == 'X')
                        {
                            suggestedTurn = 3;
                        }
                    }

                    cout << "SuggestedTurn: " << suggestedTurn << endl;
                }



                if (x[i + 1] == 'X')
                {
                    cout << "Zwei +X in folge\n";

                    if ((i - 1 == 5) || (i + 1 == 5))
                    {
                        if (x[i - 1] == 'X')
                        {
                            suggestedTurn = 4;
                        }
                        if (x[i + 1] == 'X')
                        {
                            suggestedTurn = 6;
                        }
                    }

                    cout << "SuggestedTurn: " << suggestedTurn << endl; // hier ist suggestedTurn 0 weil die vorherige if-schleife nicht getriggert wurde, also standartwert nach definition 0
                }
                if (x[i - 1] == 'X')
                {
                    cout << "Zwei -X in folge\n";

                    if ((i - 1 == 5) || (i + 1 == 5))
                    {
                        if (x[i - 1] == 'X')
                        {
                            suggestedTurn = 4;
                        }
                        if (x[i + 1] == 'X')
                        {
                            suggestedTurn = 6;
                        }
                    }

                    cout << "SuggestedTurn: " << suggestedTurn << endl;
                }

                // prüft ob auf dem suggestedTurn-feld platziert werden kann (isOccupied by 'X' or 'O')
                if ((x[suggestedTurn] >= 49 && x[suggestedTurn] <= 57) && !(x[suggestedTurn] == 'X' || x[suggestedTurn] == 'O'))
                {
                    cout << "\n\n\nAUF FELD " << suggestedTurn << " KANN PLATZIERT WERDEN\n\n\n";
                }





            }
        }
    }
}


*/ // ALTER CODE --- ALTER CODE --- ALTER CODE --- ALTER CODE --- ALTER CODE --- ALTER CODE


void turnCalc(char x[])
{
    if (runs > 2)
    {
        // horizontal
        if (x[2] == 'X')
        {
            if (x[1] == 'X')
            {
                //cout << "(HORIZONTAL) Zwei in folge auf 1 & 2\n";
                if (x[3] >= '1' && x[3] <= '9')
                {
                    suggestedTurn = 3;
                    possibleTurns[3] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[3] == 'X')
            {
                //cout << "(HORIZONTAL) Zwei in folge auf 2 & 3\n";
                if (x[1] >= '1' && x[1] <= '9')
                {
                    suggestedTurn = 1;
                    possibleTurns[1] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
        }
        if (x[5] == 'X')
        {
            if (x[4] == 'X')
            {
                //cout << "(HORIZONTAL) Zwei in folge auf 4 & 5\n";
                if (x[6] >= '1' && x[6] <= '9')
                {
                    suggestedTurn = 6;
                    possibleTurns[6] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[6] == 'X')
            {
                //cout << "(HORIZONTAL) Zwei in folge auf 5 & 6\n";
                if (x[4] >= '1' && x[4] <= '9')
                {
                    suggestedTurn = 4;
                    possibleTurns[4] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
        }
        if (x[8] == 'X')
        {
            if (x[7] == 'X')
            {
                //cout << "(HORIZONTAL) Zwei in folge auf 7 & 8\n";
                if (x[9] >= '1' && x[9] <= '9')
                {
                    suggestedTurn = 9;
                    possibleTurns[9] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[9] == 'X')
            {
                //cout << "(HORIZONTAL) Zwei in folge auf 8 & 9\n";
                if (x[7] >= '1' && x[7] <= '9')
                {
                    suggestedTurn = 7;
                    possibleTurns[7] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
        }
        if (x[1] == 'X' && x[3] == 'X')
        {
            if (x[2] >= '1' && x[2] <= '9')
            {
                suggestedTurn = 2;
                possibleTurns[2] = 'B';
            }
        }
        if (x[4] == 'X' && x[6] == 'X')
        {
            if (x[5] >= '1' && x[5] <= '9')
            {
                suggestedTurn = 5;
                possibleTurns[5] = 'B';
            }
        }
        if (x[7] == 'X' && x[9] == 'X')
        {
            if (x[8] >= '1' && x[8] <= '9')
            {
                suggestedTurn = 8;
                possibleTurns[8] = 'B';
            }
        }


        // vertikal
        if (x[4] == 'X')
        {
            if (x[1] == 'X')
            {
                //cout << "(VERTIKAL) Zwei in folge auf 1 & 4\n";
                if (x[7] >= '1' && x[7] <= '9')
                {
                    suggestedTurn = 7;
                    possibleTurns[7] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[7] == 'X')
            {
                //cout << "(VERTIKAL) Zwei in folge auf 4 & 7\n";
                if (x[1] >= '1' && x[1] <= '9')
                {
                    suggestedTurn = 1;
                    possibleTurns[1] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
        }
        if (x[5] == 'X')
        {
            if (x[2] == 'X')
            {
                //cout << "(VERTIKAL) Zwei in folge auf 2 & 5\n";
                if (x[8] >= '1' && x[8] <= '9')
                {
                    suggestedTurn = 8;
                    possibleTurns[8] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[8] == 'X')
            {
                //cout << "(VERTIKAL) Zwei in folge auf 5 & 8\n";
                if (x[2] >= '1' && x[2] <= '9')
                {
                    suggestedTurn = 2;
                    possibleTurns[2] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
        }
        if (x[6] == 'X')
        {
            if (x[3] == 'X')
            {
                //cout << "(VERTIKAL) Zwei in folge auf 3 & 6\n";
                if (x[9] >= '1' && x[9] <= '9')
                {
                    suggestedTurn = 9;
                    possibleTurns[9] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[9] == 'X')
            {
                //cout << "(VERTIKAL) Zwei in folge auf 6 & 9\n";
                if (x[3] >= '1' && x[3] <= '9')
                {
                    suggestedTurn = 3;
                    possibleTurns[3] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
        }
        if (x[1] == 'X' && x[7] == 'X')
        {
            if (x[4] >= '1' && x[4] <= '9')
            {
                suggestedTurn = 4;
                possibleTurns[4] = 'B';
            }
        }
        if (x[2] == 'X' && x[8] == 'X')
        {
            if (x[5] >= '1' && x[5] <= '9')
            {
                suggestedTurn = 5;
                possibleTurns[5] = 'B';
            }
        }
        if (x[3] == 'X' && x[9] == 'X')
        {
            if (x[6] >= '1' && x[6] <= '9')
            {
                suggestedTurn = 6;
                possibleTurns[6] = 'B';
            }
        }


        // diagonal
        if (x[5] == 'X')
        {
            if (x[1] == 'X')
            {
                //cout << "(DIAGONAL) Zwei in folge auf 1 & 5\n";
                if (x[9] >= '1' && x[9] <= '9')
                {
                    suggestedTurn = 9;
                    possibleTurns[9] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[3] == 'X')
            {
                //cout << "(DIAGONAL) Zwei in folge auf 3 & 5\n";
                if (x[7] >= '1' && x[7] <= '9')
                {
                    suggestedTurn = 7;
                    possibleTurns[7] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[7] == 'X')
            {
                //cout << "(DIAGONAL) Zwei in folge auf 5 & 7\n";
                if (x[3] >= '1' && x[3] <= '9')
                {
                    suggestedTurn = 3;
                    possibleTurns[3] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
            if (x[9] == 'X')
            {
                //cout << "(DIAGONAL) Zwei in folge auf 5 & 9\n";
                if (x[1] >= '1' && x[1] <= '9')
                {
                    suggestedTurn = 1;
                    possibleTurns[1] = 'B';
                }
                //cout << "suggestedTurn: " << suggestedTurn << endl;
            }
        }
        if (x[1] == 'X' && x[9] == 'X')
        {
            if (x[5] >= '1' && x[5] <= '9')
            {
                suggestedTurn = 5;
                possibleTurns[5] = 'B';
            }
        }
        if (x[3] == 'X' && x[7] == 'X')
        {
            if (x[8] >= '1' && x[5] <= '9')
            {
                suggestedTurn = 5;
                possibleTurns[5] = 'B';
            }
        }

        // prüft ob auf dem possibleTurns-feld platziert werden kann (isOccupied by 'X' or 'O' && ist eine zahl zwischen 1 und 9 (feld bezeichner))
        for (int i = 0; i < 10; i++)
        {
            if (possibleTurns[i] == 'B' && (feld[i] >= 49 && feld[i] <= 57) && !(feld[i] == 'X' || feld[i] == 'O'))
            {
                //cout << "\n\n\nFELD " << i << " KANN PLATZIERT WERDEN\n\n\n";
            }
        }
    }
}


int main()
{
    cout << "Willkommen zu TicTacToe!\n\n" <<
        "Geben Sie nun die Namen der zwei Spieler ein.\n" <<
        "(Tipp: Name von Spieler 2 als 'KI' aktiviert den KI Modus.)\n\n";

    cout << "Spieler 1 Name eingeben: ";
    cin >> spieler1;

    cout << "\nSpieler 2 Name eingeben: ";
    cin >> spieler2;

    if (spieler2 == "KI")
    {
        KI = true;
    }

    while (gewonnen == false)
    {
        if (runs == 12)
        {
            cout << "Unentschieden!\n";
            return 0;
        }

        cout << endl << endl << endl << endl << endl << endl << endl << endl;

        draw_spielfeld(feld);

        //cout << "\n\nRUNS: " << runs << endl << endl; //% 2 << " \n\n"; // Prüft den rest der runs geteilt durch 2 um den aktuellen spieler zu ermitteln

        if (checkwin(feld) == true)
        {
            /*
            if (player == 1)
            {
                cout << spieler2 << " hat gewonnen!" << endl;
            }
            else if (player == 2)
            {
                cout << spieler1 << " hat gewonnen!" << endl;
            }
            */
            if (gewonnen1 == true)
            {
                cout << spieler1 << " hat gewonnen!" << endl;
            }
            else if (gewonnen2 == true)
            {
                cout << spieler2 << " hat gewonnen!" << endl;
            }

            return 0;
            break;
        }

        //cout << "Runs: " << runs << endl;
        input();

        if (falscheEingabe == false)
        {
            setplayer();
            runs++;
        }

        for (int i = 1; i < 10; i++)
        {
            //cout << "\n\n[CHECKWIN schleife] i ist aktuell: " << i << "\n\n";
            //cout << "\n\n[CHECKWIN schleife] feld an stelle i ist belegt mit: " << feld[i] << "\n\n";

            if (feld[i] == 'X' || feld[i] == 'O')
            {
                if (i == 9)
                {
                    //cout << "\n\n[CHECKWIN schleife] i hat 10 erreicht!\n\n";

                    cout << "Unentschieden!\n";

                    return 0;
                }

                //cout << "\n\n[CHECKWIN schleife] i = " << i << endl << endl;
                continue;
            }
            else
            {
                //cout << "\n\n[CHECKWIN schleife] BREAK\n\n";
                break;
            }
        }

        turnCalc(feld);

        //cout << endl << endl;

        for (int i = 0; i < 10; i++)
        {
            //cout << possibleTurns[i] << " an index: " << i << endl;;
        }
    }
}
