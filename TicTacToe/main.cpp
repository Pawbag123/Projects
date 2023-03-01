#include "Board.hh"

int *Intro();

int main()
{
    Board Tab(Intro());
    Tab.showBoard();
    while (!Tab.checkEnd())
    {
        Tab.move();
        if (Tab.checkEnd())
            break;
        Tab.showBoard();
        Tab.moveAI(Tab.findBestMove());
        Tab.showBoard();
    }
    return 0;
}

int *Intro()
{
    char wyb;
    int size;
    int win;
    int *tab = new int[3];
    int depth[10] = {0, 3, 10, 9, 8, 7, 6, 5, 4, 3};
    cout << "Witaj w grze kolko i krzyzyk!" << endl;
    cout << "Wybierz swoje parametry: \n";

    cout << "Podaj rozmiar planszy: ";
    cin >> size;
    while (!(size >= 3 && size <= 10) || cin.fail())
    {
        cerr << "\nWprowadzono niepoprawny rozmiar! \n";
        cout << "Podaj rozmiar planszy: ";
        cin.clear();
        cin.ignore(9999, '\n');
        cin >> size;
    }
    tab[0] = size;

    cout << "\nPodaj ilosc punktow do wygrania gry: ";
    cin >> win;
    while (!(win >= 1 && win <= size) || cin.fail())
    {
        cerr << "\nWprowadzono niepoprawna ilosc punktow \n";
        cout << "Podaj ilosc punktow do wygrania gry: ";
        cin.clear();
        cin.ignore(9999, '\n');
        cin >> win;
    }
    tab[1] = win;

    cout << "Czy chcesz ustalic glebokosc algorytmu? [t/n]";
    cin >> wyb;
    while (!(wyb == 't' || wyb == 'n') || cin.fail())
    {
        cerr << "\nWprowadzono niepoprawny znak \n";
        cout << "Czy chcesz ustalic glebokosc algorytmu? [t/n]";
        cin.clear();
        cin.ignore(9999, '\n');
        cin >> wyb;
    }

    if (wyb == 'n')
        tab[2] = depth[size - 1];
    if (wyb == 't')
    {
        cout << "\nPodaj glebokosc (z zakresu 1 - 10): ";
        int tmpDepth;
        cin >> tmpDepth;
        while (!(tmpDepth >= 1 && tmpDepth <= 10) || cin.fail())
        {
            cerr << "\nWprowadzono niepoprawna glebokosc! \n";
            cout << "\nPodaj glebokosc (z zakresu 1 - 10): ";
            cin.clear();
            cin.ignore(9999, '\n');
            cin >> tmpDepth;
        }
        tab[2] = tmpDepth;
    }
    return tab;
}
