#ifndef OBIEKT_SC_HH
#define OBIEKT_SC_HH

#include <iostream>
#include "Wektor3D.hh"

/**
 *  @file ObiektSc.hh
 * 
 *  @brief Plik zawiera definicję klasy ObiektSc oraz jej metod
 * 
 */

/**
 * @brief Klasa definiuje pojęcie obiektu sceny
 * 
 */
class ObiektSc
{
protected: 
    /**
     * @brief Obiekt typu Wektor3D przechowujacy środek położenia obiektu
     * 
     */
    Wektor3D _SrodekObiektu;

    /**
     * @brief liczba typu double przechowująca promień okręgu, w którym jest wrysowany Dron
     * 
     */
    double _Promien;

    /**
     * @brief Liczba typu double przechowująca połowę wartości boku X elementu powierzchni
     * 
     */
    double _BokX;

    /**
     * @brief Liczba typu double przechowująca połowę wartości boku Y elementu powierzchni
     * 
     */
    double _BokY;

public:
    
    /**
     * @brief Metoda pozwalajaca na uzyskanie srodka obiektu
     * 
     * @return Wektor3D - Wektor3D zawierajacy srodek polozenia obiektu
     */
    Wektor3D WezSrodek() const
    {
        return _SrodekObiektu;
    }

    /**
     * @brief Metoda pozwalająca na uzyskanie promienia Drona
     * 
     * @return double - liczba przechowująca promień drona
     */
    double WezPromien() const
    {
        return _Promien;
    }

    /**
     * @brief Metoda wirtualna, sprawdzająca czy Dron koliduje z obiektem
     * 
     * @param Obiekt - wskaźnik na drona, który ma wylądować
     * @return true - jeżeli następuje kolizja
     * @return false - w wypadku przeciwnym
     */
    virtual bool SprawdzCzyZajete(ObiektSc *Obiekt) = 0;

    /**
     * @brief Metoda ustalająca odpowiednie paramery obiektu w celu sprawdzenia kolizji
     * 
     */
    virtual void UstalParametry() = 0;

    /**
     * @brief Metoda, która w wypadku kolizji wypisuje nazwę przeszkody
     * 
     */
    virtual void DajNazwe() = 0;
};

#endif