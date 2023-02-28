#ifndef LICZNIK_HH
#define LICZNIK_HH

#include <iostream>

/**
 * @file Licznik.hh
 * @brief Plik zawierający definicję szablonu licznik
 * 
 */

/**
 * @brief Szablon licznik modelujący pojęcie licznika elementów danej klasy
 * 
 * @tparam Klasa - Oznacza klasę obiektów zliczanych 
 */

template <class Klasa>
class Licznik
{
    /**
     * @brief Zmienna statyczna ukazująca całkowitą ilość stworzonych obiektów
     * 
     */
    static int _licz_suma;
    /**
     * @brief Zmienna statyczna ukazująca ilość aktualnie istniejących obiektów
     * 
     */
    static int _licz_akt;

public:
    /**
     * @brief Konstruktor zwiększający ilości
     * 
     */
    Licznik()
    {
        ++_licz_suma;
        ++_licz_akt;
    }

    /**
     * @brief Konstruktor kopiujący zwiększający ilości
     * 
     */
    Licznik(const Licznik &)
    {
        ++_licz_suma;
        ++_licz_akt;
    }

    /**
     * @brief Destruktor zmniejszający ilość aktualnych elementów
     * 
     */
    ~Licznik()
    {
        --_licz_akt;
    }

    /**
     * @brief Metoda statyczna zwracająca liczbę wszystkich utworzonych obiektów
     * 
     * @return int - liczba wszystkich utworzonych obiektów
     */
    static int WezSume()
    {
        return _licz_suma;
    }

    /**
     * @brief Metoda statyczna zwracająca liczbę aktualnie istniejących obiektów
     * 
     * @return int - liczba aktualnie istniejących obiektów
     */
    static int WezAkt()
    {
        return _licz_akt;
    }
};

/**
 * @brief Inicjalizacja zmiennej statycznej licz_akt
 * 
 */
template <class klasa>
int Licznik<klasa>::_licz_akt;
/**
 * @brief Inicjalizacja zmiennej statycznej licz_suma
 *  
 */
template <class klasa>
int Licznik<klasa>::_licz_suma;
/**
 * @brief Inicjalizacja zmiennej statycznej _AktDron
 * 
 */

#endif