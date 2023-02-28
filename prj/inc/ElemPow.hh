#ifndef ELEM_POW_HH
#define ELEM_POW_HH

#include "Bryla.hh"
#include <fstream>
/**
 * @file ElemPow.hh
 * 
 * @brief Plik zawiera definicje klasy ElemPow oraz jej metod
 * 
 */

/**
 * @brief Klasa modeluje pojecie elementu powierzchni
 * 
 */
class ElemPow : public Bryla, public ObiektSc
{
    /**
     * @brief Zmienna oznaczajaca ilosc stworzonych elementow
     * 
     */
    static int _IlElem;

    /**
     * @brief Zmienna stworzona w celu przypisania numeru elementu
     * 
     */
    int _NrElem;

protected:
    /**
     * @brief Konstruktor parametryczny Elementu powierzchni
     * 
     * @param NazwaPlikuBrylaWzorcowa - Nazwa pliku bryły wzorcowej
     * @param Skala - Wektor3D zawierający dane odnośnie skali obiektu
     * @param Polozenie - Wektor3D zawierający dane odnośnie położenia obiektu
     */
    ElemPow(const std::string &NazwaPlikuBrylaWzorcowa,
            const Wektor3D &Skala,
            const Wektor3D &Polozenie) : Bryla(NazwaPlikuBrylaWzorcowa,
                                               Skala, Polozenie){};

    /**
     * @brief Metoda zwiekszajaca licznik ilosci elementow
     * 
     */
    static void ZwiekszIlElem()
    {
        ++_IlElem;
    }

    /**
     * @brief Metoda przypisujaca Elementowi jego numer
     * 
     */
    void PrzypiszNrElem()
    {
        _NrElem = _IlElem;
    }

    /**
     * @brief Metoda zwracajaca prywatny atrybut Elementu powierzchni
     * 
     * @return int - numer elementu
     */
    int WezNrElem()
    {
        return _NrElem;
    }

    /**
     * @brief Metoda transformujaca element
     * 
     * Metoda wirtualna, ktora ma na celu przeksztalcenie danych wejsciowych pobranych
     * z pliku bryl wzorcowych na odpowiednie elementy powierzchni
     * 
     * @param Plik_We - plik zawierajacy bryle wzorcowa
     * @param Plik_Wy - plik zawierajacy stworzony element
     * @return true - gdy operacja sie powiedzie
     * @return false - gdy nastapi problem w otwarciu plikow
     */
    virtual bool TransformujElement(std::ifstream &Plik_We,
                                    std::ofstream &Plik_Wy) const = 0;

public:
    /**
     * @brief Metoda zapisujaca element w pliku
     * 
     * @return true - gdy operacja sie powiedzie
     * @return false - jezeli nastapi problem z otwarciem plikow
     */
    bool Oblicz_i_Zapisz_WspGlbElementu() const;

    /**
     * @brief Metoda wypisująca nazwę elementu oraz jej współrzędne na standardowym wyjściu
     * 
     */
    virtual void WypiszElement() = 0;

    /**
     * @brief Destruktor obiektu ElemPow, usuwa plik finalny elementu powierzchni
     * 
     */
    virtual ~ElemPow()
    {
        std::remove(WezNazwePliku_BrylaFinalna().c_str());
    }
};

#endif