#ifndef SCIEZKA_HH
#define SCIEZKA_HH

#include <iostream>
#include <fstream>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "lacze_do_gnuplota.hh"
#include "Definicje.hh"

/**
 * @file Sciezka.hh 
 * 
 *
 * @brief Plik zawierający definicję klasy Sciezka
 * 
 */

/**
 * @brief Klasa modelująca pojęcie ścieżki lotu drona
 * 
 */
class Sciezka
{
    /**
     * @brief Szablon vector zawierający punkty ścieżki zapisane jako obiekty klasy Wektor3D
     * 
     */
    std::vector<Wektor3D> _PunktySciezki;

    /**
     * @brief Liczba typu double zawierająca kąt rotacji ścieżki
     * 
     */
    double _KatRotacji;

    /**
     * @brief Obiekt typu Wektor3D zawierający dane o locie Poziomym, który zostanie
     * użyty do wyznaczenia ścieżki
     * 
     */
    Wektor3D _LotPoz;

    /**
     * @brief Obiekt typu Wektor3D zawierający początkowe położenie drona, w celu dodania
     * fragmentu lotu
     * 
     */
    Wektor3D _PolDrona;

    /**
     * @brief Liczba typu double przechowująca wartość długości lotu
     * 
     */
    double _DlLotu;

    /**
     * @brief Tablica liczb typu double przechowująca wspolrzedne X i Y wektora przesuniecia
     * w locie poziomym
     * 
     */
    double _DlXY[2];

    /**
    * @brief Metoda umieszczająca pozycję startową drona
    * na początku punktow sciezki
    * 
    * @param Start - obiekt typu Wektor3D przechowujacy polozenie drona
    */
    void DodajStart(const Wektor3D &Start)
    {
        Wektor3D tmp = Start;
        _PunktySciezki.push_back(tmp);
    }

    /**
    * @brief Metoda umieszczajaca pozycje po wzniesieniu drona w gore
    * na odpowiednim miejscu punktow sciezki
    * 
    * @param Start - obiekt typu Wektor3D przechowujacy polozenie drona
    */
    void DodajPion(const Wektor3D &Start)
    {
        Wektor3D tmp = Start;
        tmp[2] = tmp[2] + LOT_PIONOWY;
        _PunktySciezki.push_back(tmp);
    }

    /**
    * @brief Metoda ustalajaca kąt obrotu ścieżki oraz drona
    * 
    */
    void UstalKatObrotu(const double KatDrona);

    /**
    * @brief Metoda ustalająca długość lotu drona oraz parametry z nią związane
    * 
    */
    void UstalDlugoscLotu();

    /**
    * @brief Metoda umieszczająca pozycję drona po locie poziomym na odpowiednim
    * miejscu punktów ścieżki
    * 
    * @param Start - obiekt typu Wektor3D przechowujacy polozenie drona 
    */
    void DodajPoziom(const Wektor3D &Start);

    /**
     * @brief Metoda umieszczająca końcową pozycję drona na odpowiednim miejscu punktów
     * ścieżki
     * 
     */
    void DodajKoniec()
    {
        Wektor3D tmp = _PunktySciezki[2];
        tmp[2] = tmp[2] - 80;
        _PunktySciezki.push_back(tmp);
    }

    /**
    * @brief Metoda ustalająca ścieżkę drona za pomocą stworzonych wcześniej metod
    * 
    * @param Start - obiekt typu Wektor3D przechowujacy polozenie drona
    */
    void UstalSciezke(const Wektor3D &Start, const double KatDrona);

    /**
     * @brief Metoda tworząca nową ścieżkę drona wydłużoną o fragment
     *  potrzebny do ominięcia przeszkody
     * 
     */
    void DodajFragmentSciezki();

    /**
     * @brief Metoda wydłużająca długość lotu o wartość potrzebną do ominięcia przeszkody
     * 
     */
    void DodajFragmentLotu()
    {
        _LotPoz[0] = _LotPoz[0] + 20;
    }

public:
    /**
     * @brief Metoda zwracająca odpowiednie wartości współrzędnych wektora przesunięcia
     * 
     * @return const double* - Tablica liczb typu double przechowująca
     * odpowiednie wartości współrzędnych
     */
    const double *WezDlXY() const
    {
        return _DlXY;
    }

    /**
     * @brief Metoda zwracająca długość lotu drona
     * 
     * @return double& - Liczba typu double przechowująca długość lotu
     */
    double WezDl() const
    {
        return _DlLotu;
    }

    /**
     * @brief Metoda zwracająca kąt rotacji ścieżki oraz drona
     * 
     * @return double& - Liczba typu double przechowująca kąt rotacji w stopniach
     */
    double WezKat() const
    {
        return _KatRotacji;
    }

    /**
     * @brief Metoda która pozwala na narysowanie ścieżki lotu
     * 
     * @param Lacze - Łącze, które posłuży do wyświetlenia ścieżki
     * @param Start - obiekt typu Wektor3D przechowujacy polozenie drona
     * @return true - Gdy operacja się uda
     * @return false - Gdy nastąpi problem z otwarciem odpowiedniego pliku
     */
    bool NarysujSciezke(PzG::LaczeDoGNUPlota &Lacze,
                        const Wektor3D &Start,
                        const double KatDrona);

    /**
     * @brief Metoda, która usuwa ścieżkę z łącza do GNUPlota
     * 
     * @param Lacze - Łącze, które służyło do wyświetlenia ścieżki
     */
    void UsunSciezke(PzG::LaczeDoGNUPlota &Lacze)
    {
        Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
        Lacze.Rysuj();
        _PunktySciezki.clear();
    }

    /**
     * @brief Metoda która na nowo rysuje ścieżkę drona poprawioną po kolizji
     * 
     * @return true 
     * @return false 
     */
    bool DorysujSciezke();

    /**
     * @brief Metoda ustalająca początkowe położenie Drona
     * 
     * @param Polozenie - Wektor3D zawierający Położenie Drona
     */
    void UstalPolDrona(const Wektor3D &Polozenie)
    {
        _PolDrona = Polozenie;
    }
};

#endif