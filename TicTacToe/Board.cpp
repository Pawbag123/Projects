#include "Board.hh"

using namespace std;

Board::Board(int tab[3])
{
    size = tab[0];
    win = tab[1];
    depth = tab[2];
    fields = new char *[size];
    for (int i = 0; i < size; i++)
    {
        fields[i] = new char[size];
        for (int j = 0; j < size; j++)
        {
            fields[i][j] = 'n';
        }
    }
}

void Board::readMove(int &row, int &column)
{
    while (!(row <= size && column <= size && row > 0 && column > 0) || cin.fail() || fields[row - 1][column - 1] != 'n')
    {
        cerr << "\nWprowadzono niepoprawne dane lub pole jest juz zajete!\n";
        cout << "\nPodaj rzad oraz kolumne: ";
        cin.clear();
        cin.ignore(9999, '\n');
        cin >> row >> column;
    }
}

void Board::move()
{
    int row, column;

    cout << "Podaj rzad oraz kolumne: ";
    cin >> row >> column;
    readMove(row, column);
    fields[row - 1][column - 1] = 'x';
}

void Board::moveAI(int *tab)
{
    fields[tab[0]][tab[1]] = 'o';
}

void Board::showBoard()
{
    string spaceCol = "  ";
    string space = "    ";
    string dot2 = ". ";
    string dot = ".  ";
    string top = "_____";
    string n = "|     |";
    string bottom = "|_____|";
    string O = "|  O  |";
    string X = "|  X  |";

    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            cout << space;
            for (int j = 0; j < size; j++)
                cout << spaceCol << j + 1 << dot << "  ";
            cout << endl;
        }
        cout << space;
        for (int j = 0; j < size; j++)
            cout << " " << top << "  ";
        cout << endl;
        cout << space;
        for (int j = 0; j < size; j++)
            cout << n << " ";
        cout << endl;
        if (i < 9)
            cout << i + 1 << dot;
        else
            cout << i + 1 << dot2;
        for (int j = 0; j < size; j++)
        {
            switch (fields[i][j])
            {
            case 'n':
                cout << n << " ";
                break;

            case 'x':
                cout << X << " ";
                break;

            case 'o':
                cout << O << " ";
                break;
            }
        }
        cout << endl;
        cout << space;
        for (int j = 0; j < size; j++)
            cout << bottom << " ";
        cout << endl;
    }
}

bool Board::checkRightCrossD(const char sign)
{
    int count = 0;
    for (int k = 0; (k + win) <= size; k++)
    {
        for (int i = 0; (i + k) < size; i++)
        {
            {
                if (fields[i + k][i] == sign)
                {
                    count++;
                    if (count == win)
                        return true;
                }
                else
                    count = 0;
            }
        }
    }
    return false;
}

bool Board::checkRightCrossR(const char sign)
{
    int count = 0;
    for (int k = 1; (k + win) <= size; k++)
    {
        for (int i = 0; (i + k) < size; i++)
        {
            {
                if (fields[i][i + k] == sign)
                {
                    count++;
                    if (count == win)
                        return true;
                }
                else
                    count = 0;
            }
        }
    }
    return false;
}

bool Board::checkRightCross(const char sign)
{
    if (checkRightCrossR(sign) || checkRightCrossD(sign))
        return true;
    return false;
}

bool Board::checkLeftCrossD(const char sign)
{
    int count = 0;
    for (int k = 0; (k + win) <= size; k++)
    {
        for (int i = 0; (i + k) < size; i++)
        {
            {
                if (fields[i + k][size - 1 - i] == sign)
                {
                    count++;
                    if (count == win)
                        return true;
                }
                else
                    count = 0;
            }
        }
    }
    return false;
}

bool Board::checkLeftCrossL(const char sign)
{
    int count = 0;
    for (int k = 1; (k + win) <= size; k++)
    {
        for (int i = 0; (i + k) < size; i++)
        {
            {
                if (fields[i][size - 1 - (k + i)] == sign)
                {
                    count++;
                    if (count == win)
                        return true;
                }
                else
                    count = 0;
            }
        }
    }
    return false;
}

bool Board::checkLeftCross(const char sign)
{
    if (checkLeftCrossL(sign) || checkLeftCrossD(sign))
        return true;
    return false;
}
bool Board::checkRows(const char sign)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (fields[i][j] == sign)
            {
                count++;
                if (count == win)
                    return true;
            }
            else
                count = 0;
        }
        count = 0;
    }
    return false;
}

bool Board::checkCols(const char sign)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (fields[j][i] == sign)
            {
                count++;
                if (count == win)
                    return true;
            }
            else
                count = 0;
        }
        count = 0;
    }
    return false;
}

bool Board::checkWin(const char sign)
{
    if (checkRows(sign) || checkCols(sign) || checkRightCross(sign) || checkLeftCross(sign))
        return true;
    return false;
}

bool Board::checkDraw()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (fields[i][j] == 'n')
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::checkEnd()
{
    if (checkWin('x'))
    {
        cout << "Wygrana gracza!\n";
        return true;
    }
    if (checkWin('o'))
    {
        cout << "Wygrana komputera :(\n";
        return true;
    }
    if (checkDraw())
    {
        cout << "Remis \n";
        return true;
    }
    return false;
}

int Board::evaluate()
{
    if (checkWin('x'))
        return -10;
    if (checkWin('o'))
        return 10;
    return 0;
}

int Board::minimax(int depth, bool minMax, int alpha, int beta)
{
    int score = evaluate();
    if (depth == this->depth) // sprawdzenie glebokosci, zwrocenie oceny
    {
        if (minMax)
            return score - depth;
        if (!minMax)
            return score + depth;
        if (checkDraw())
            return 0;
    }
    if (score == 10 || score == -10)
        return score;
    if (checkDraw())
        return 0;

    if (minMax == 1) // sprawdzenie dla ktorego uzytkownika wyszukujemy ruch
    {
        int best = -1000;

        for (int i = 0; i < size; i++) // przejscie przez plansze
        {
            for (int j = 0; j < size; j++)
            {
                if (fields[i][j] == 'n') // sprawdzenie czy pole nie jest zajete
                {
                    fields[i][j] = 'o';                                         // wykonanie ruchu
                    best = max(best, minimax(depth + 1, !minMax, alpha, beta)); // wywolanie minimax rekurencyjnie oraz wybranie wartosci najwiekszej
                    alpha = max(alpha, best);                                   // ustalenie wspolczynnika alfa
                    fields[i][j] = 'n';                                         // cofniecie ruchu
                    if (alpha >= beta)                                          // wykonanie ciec alfa/beta
                        break;
                }
                if (alpha >= beta)
                    break;
            }
        }
        return best;
    }

    else
    {
        int best = 1000;
        for (int i = 0; i < size; i++) // przejscie przez plansze
        {
            for (int j = 0; j < size; j++)
            {
                if (fields[i][j] == 'n') // sprawdzenie czy pole nie jest zajete
                {
                    fields[i][j] = 'x';                                         // wykonanie ruchu
                    best = min(best, minimax(depth + 1, !minMax, alpha, beta)); // rekurencyjne wykorzystanie metody w celu znalezienia wyniku minimalnego
                    beta = min(beta, best);                                     // ustalenie wspolczynnika beta
                    fields[i][j] = 'n';                                         // cofniecie ruchu
                    if (alpha >= beta)                                          // wykonanie ciec alfa/beta
                        break;
                }
                if (alpha >= beta)
                    break;
            }
        }
        return best;
    }
}

int *Board::findBestMove()
{
    int bestVal = -1000;        // poczatkowa wartosc najlepszego ruchu
    int *bestMove = new int[2]; // tablica przechowujaca pole najlepszego ruchu
    bestMove[0] = -1;
    bestMove[1] = -1;

    for (int i = 0; i < size; i++) // wywolanie algorytmu minimax dla kazdego pustego pola
    {
        for (int j = 0; j < size; j++)
        {
            if (fields[i][j] == 'n') // sprawdzenie czy pole nie jest zajete
            {
                fields[i][j] = 'o';                           // wykonanie ruchu
                int moveVal = minimax(0, false, -1000, 1000); // wykonanie oceny obecnego ruchu
                fields[i][j] = 'n';                           // cofniecie ruchu
                if (moveVal > bestVal)                        // Jezeli ocena naszego obecnego ruchu jest lepsza niz dotychczas najlepszego, nalezy go zastapic
                {
                    bestMove[0] = i;
                    bestMove[1] = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    cout << "Ruch przeciwnika: \n";
    return bestMove; // zwrocenie najlepszego ruchu
}
