#ifndef PLASKOWYZ_HH
#define PLASKOWYZ_HH

#include "ElemPow.hh"
#include "iostream"

/**
 * @file Plaskowyz.hh
 * 
 * @brief Plik zawiera definicje klasy Plaskowyz oraz jej metod
 * 
 */

/**
 * @brief Klasa modeluje pojęcie Płaskowyżu
 * 
 */
class Plaskowyz : public ElemPow
{
    /**
     * @brief Licznik obiektów typu Plaskowyz
     * 
     */
    static int _Nr_Plaskowyzu;

protected:
    /**
     * @brief Metoda transformująca bryłę wzorcową w płaskowyż
     * 
     * Metoda ma na celu przetransformowanie wierzchołków z pliku zawierającego
     * bryłę wzorcową na płaskowyż, a następnie zapisanie utworzonych
     * wierzchołków w pliku wynikowym
     * 
     * @param Plik_We - Plik zawierający bryłę wzorcową
     * @param Plik_Wy - Plik wynikowy
     * @return true - Gdy operacja się powiedzie
     * @return false - Gdy wystąpi błąd przy otwarciu plików
     */
    bool TransformujElement(std::ifstream &Plik_We,
                            std::ofstream &Plik_Wy) const override;

public:
    /**
     * @brief Konstruktor parametryczny obiektu Plaskowyz
     * 
     * @param Skala - Wektor3D zawierający dane odnośnie skali obiektu
     * @param Polozenie - Wektor3D zawierający dane odnośnie położenia obiektu 
     */
    Plaskowyz(const Wektor3D &Skala, const Wektor3D &Polozenie);

    /**
     * @brief Metoda wypisująca nazwę elementu oraz jej współrzędne na standardowym wyjściu
     * 
     */
    void WypiszElement() override
    {
        WyswietlWsp_Dla_Elem();
        std::cout << " Plaskowyz";
    }

    /**
     * @brief Metoda ustalająca parametry potrzebne do sprawdzenia kolizji dla klasy Plaskowyz
     * 
     */
    void UstalParametry() override
    {
        Wektor3D Skala = WezSkale();
        _SrodekObiektu = WezPolozenie();
        _BokX = (0.5 * Skala[0]);
        _BokY = (0.5 * Skala[1]);
    }

    /**
     * @brief Metoda sprawdzająca kolizję Drona z obiektem klasy Plaskowyz
     * 
     * @param Obiekt - Wskaźnik na drona
     * @return true - jeżeli występuje kolizja
     * @return false - w wypadku przeciwnym
     */
    bool SprawdzCzyZajete(ObiektSc *Obiekt) override;

    /**
     * @brief Metoda wypisująca nazwę klasy w wypadku kolizji jej obiektu z dronem
     * 
     */
    void DajNazwe() override
    {
        std::cout << "\n:( Ladowisko niedostepne!\n";
        std::cout << ":( Wykryto element powierzchni typu: Plaskowyz\n";
    }
};

#endif