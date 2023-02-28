#ifndef GORA_Z_DL_GRANIA_HH
#define GORA_Z_DL_GRANIA_HH

#include "ElemPow.hh"
#include "iostream"

/**
 * @file Gora_z_Dl_Grania.hh
 * 
 * @brief Plik zawiera definicje klasy Gora_z_Dl_Grania oraz jej metod
 * 
 */

/**
 * @brief Klasa modeluje pojecie Góry z długą Granią
 * 
 */
class Gora_z_Dl_Grania : public ElemPow
{
    /**
     * @brief Licznik stworzonych obiektów typu Gora_z_Dl_Grania
     * 
     */
    static int _Nr_Gory_z_Dl_Grania;

protected:
    /**
     * @brief Metoda transformująca bryłę wzorcową w górę z długą granią
     * 
     * Metoda ma na celu przetransformowanie wierzchołków z pliku zawierającego
     * bryłę wzorcową na górę z ostrą granią, a następnie zapisanie utworzonych
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
     * @brief Konstruktor parametryczny obiektu Gora_z_Dl_Grania
     * 
     * @param Skala - Wektor3D zawierający dane odnośnie skali obiektu
     * @param Polozenie - Wektor3D zawierający dane odnośnie położenia obiektu 
     */
    Gora_z_Dl_Grania(const Wektor3D &Skala, const Wektor3D &Polozenie);

    /**
     * @brief Metoda wypisująca nazwę elementu oraz jej współrzędne na standardowym wyjściu
     * 
     */
    void WypiszElement() override
    {
        WyswietlWsp_Dla_Elem();
        std::cout << " Gora z dluga grania";
    }

    /**
     * @brief Metoda ustalająca parametry potrzebne do sprawdzenia kolizji dla klasy
     *  Gora_z_Dl_Grania
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
     * @brief Metoda sprawdzająca kolizję Drona z obiektem klasy Gora_z_Dl_Grania
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
        std::cout << ":( Wykryto element powierzchni typu: Gora z Dluga Grania\n";
    }
};

#endif