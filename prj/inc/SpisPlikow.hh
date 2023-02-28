#ifndef SPIS_PLIKOW_HH
#define SPIS_PLIKOW_HH

#include <iostream>
#include <cstring>
#include <vector>
#include "Dron.hh"
#include "lacze_do_gnuplota.hh"
using namespace std;
/**
 * @file SpisPlikow.hh
 * @brief Plik zawiera definicję klasy SpisPlikow
 * 
 */

/**
 * @brief Klasa modeluje pojęcie spisu plików wykorzystanych w celu rysowania figur
 * 
 */
class SpisPlikow
{
    /**
     * @brief Szablon vector przechowujący nazwy plików
     * 
     */
    vector<string> _NazwyPlikow;

public:
    /**
     * @brief Konstruktor klasy SpisPlikow, dodaje nazwe pliku płaszczyzny
     * 
     */
    SpisPlikow()
    {
        DodajNazwe(PLIK_PLASZCZYZNY);
    }

    /**
     * @brief Metoda dodająca nazwę pliku, wykorzystana w innych funkcjach
     * 
     * @param Nazwa - Nazwa pliku, który ma zostać dodany
     */
    void DodajNazwe(const string &Nazwa)
    {
        _NazwyPlikow.push_back(Nazwa);
    }

    /**
     * @brief Metoda zwracająca nazwę pliku znajdującą się w danym miejscu
     * 
     * @param idx - Numer nazwy pliku
     * @return string - Nazwa pliku
     */
    string WezNazwe(const int idx) const
    {
        return _NazwyPlikow[idx];
    }

    /**
     * @brief Metoda zwracająca całkowitą ilość plików
     * 
     * @return int - ilość nazw plików
     */
    int WezIlosc() const
    {
        return _NazwyPlikow.size();
    }

    /**
     * @brief Metoda wyświetlająca wszystkie nazwy dodanych plików
     * 
     */
    void Wyswietl() const
    {
        for (int i = 0; i <= WezIlosc(); ++i)
            cout << WezNazwe(i) << endl;
    }
};

#endif