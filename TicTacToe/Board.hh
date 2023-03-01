#include <iostream>
#include <string>

using namespace std;

/*klasa modeluje pojecie planszy do gry kolka i krzyzyk
zawiera wszystkie niezbedne metody do ukazania planszy, sprawdzenia wyniku oraz algorytm przeciwnika
*/
class Board
{
    int size, win, depth; // zmienne odpowiadajace za rozmiar, ilosc punktow do wygranej oraz glebokosc algorytmu
    char **fields;        // tablica dwuwymiarowa posiadajaca pola planszy

public:
    Board(int tab[3]);                                        // konstruktor parametryczny
    void readMove(int &row, int &column);                     // wczytanie ruchu gracza
    void move();                                              // wykonanie ruchu gracza
    void moveAI(int *tab);                                    // wykonanie ruchu przeciwnika
    void showBoard();                                         // ukazanie planszy
    bool checkRows(const char sign);                          // sprawdzenie, wygranej w rzedach
    bool checkCols(const char sign);                          // sprawdzenie wygranej w kolumnach
    bool checkRightCrossD(const char sign);                   // sprawdzenie wygranej po przekatnej \ w dol od srodka
    bool checkRightCrossR(const char sign);                   // sprawdzenie wygranej po przekatnej \ w prawo od srodka
    bool checkRightCross(const char sign);                    // sprawdzenie wygranej po przekatnej \ .
    bool checkLeftCrossD(const char sign);                    // sprawdzenie wygranej po przekatnej / w dol od srodka
    bool checkLeftCrossL(const char sign);                    // sprawdzenie wygranej po przekatnej / w lewo od srodka
    bool checkLeftCross(const char sign);                     // sprawdzenie wygranej po przekatnej /
    bool checkWin(const char sign);                           // sprawdzenie wygranej dla konkretnej osoby (x lub o)
    bool checkDraw();                                         // sprawdzenie remisu, lub zapelnienia wszystkich pol
    bool checkEnd();                                          // sprawdzenie wygranej lub remisu
    int evaluate();                                           // metoda oceniajaca pozycje dla algorytmu minimax
    int minimax(int depth, bool minMax, int alpha, int beta); // algorytm minimax z zaimplementowanymi alfa beta cieciami
    int *findBestMove();                                      // metoda znajdujaca najlepszy ruch na podstawie algorytmu minimax
};