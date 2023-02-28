#ifndef UKLAD_WSP_HH
#define UKLAD_WSP_HH
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "Definicje.hh"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

/**
 * @file UkladWsp.hh
 * @brief Plik zawierający definicję klasy UkladWsp
 * 
 */
/**
 * @brief Klasa UkladWsp
 * 
 * Klasa modeluje pojecie ukladu wspolrzednych danej bryly lub drona
 * 
 */
class UkladWsp
{
    /**
     * @brief Wektor3D zawierający współrzędne polozenia obiektu
     * 
     */
    Wektor3D _Polozenie;
    /**
     * @brief Liczba typu double przechowujaca dane na temat kata orientacji obiektu
     * 
     */
    double _KatOrientacji_stopnie;

protected:
    /**
     * @brief Konstruktor Ukladu wspolrzednych o dwóch parametrach
     * 
     * @param Polozenie - Polozenie obiektu
     * @param KatOrientacji - Kąt orientacji obiektu
     */
    UkladWsp(const Wektor3D &Polozenie,
             const double KatOrientacji) : _Polozenie(Polozenie),
                                           _KatOrientacji_stopnie(KatOrientacji){};

    /**
     * @brief Konstruktor układu współrzędnych o jednym parametrze
     * 
     * @param Polozenie - Położenie obiektu
     */
    UkladWsp(const Wektor3D &Polozenie) : _Polozenie(Polozenie), _KatOrientacji_stopnie(0){};

    /**
     * @brief Metoda zwracająca kąt orientacji w celu użycia w innych funkcjach
     * 
     * @return double& - Liczba typu double przechowująca wartość kąta orientacji w stopniach
     */
    double &WezKat()
    {
        return _KatOrientacji_stopnie;
    }

    /**
    * @brief Ustalenie kąta orientacji
    * 
    * @param alfa - Liczba typu double, zawierająca kąt, który zostanie przypisany Układowi
    */
    void UstawKat(const double alfa)
    {
        _KatOrientacji_stopnie = alfa;
    }

    /**
     * @brief Metoda zmieniająca współrzędną Z położenia (w celu zmiany wysokości)
     * 
     * @param wys - Liczba typu double która zostanie przypisana współrzędnej Z
     */
    void Wznies(const double wys)
    {
        _Polozenie[2] = wys;
    }

    /**
     * @brief Metoda stworzona w celu animacji przesunięcia Drona o odpowiednie wartości
     * 
     * @param Dl - Tablica liczb typu double, które przechowują współrzędne X,Y
     * wektora, o jaki ma zostać przesunięty Dron 
     * @param CalkDl - Liczba typu double, zawierająca całkowitą długość lotu Drona
     */
    void Przesun(const double Dl[2], const double CalkDl)
    {
        _Polozenie[0] = _Polozenie[0] + Dl[0] / CalkDl;
        _Polozenie[1] = _Polozenie[1] + Dl[1] / CalkDl;
    }

    

public:

    /**
     * @brief Metoda zwracająca położenie układu w celu dalszego działania
     * 
     * @return Wektor3D - Wektor3D zawierający położenie, które zostanie użyte w kolejnych
     * funkcjach
     */
    Wektor3D WezPolozenie() const
    {
        Wektor3D wynik = _Polozenie;
        return wynik;
    }

    /**
     * @brief Zwiększenie kąta orientacji
     * 
     * @param alfa - Liczba typu double, zawierająca kąt, o który zostanie zwiększony kąt
     * zawarty w układzie
     */
    void DodajKat(const double alfa)
    {
        _KatOrientacji_stopnie += alfa;
    }

    /**
     * @brief Wyświetlenie współrzędnych X i Y Układu
     * 
     */
    void WyswietlWsp()
    {
        std::cout << _Polozenie[0] << " " << _Polozenie[1];
    }

    void WyswietlWsp_Dla_Elem()
    {
        std::cout << "(" << _Polozenie[0] << ", " << _Polozenie[1] << ")";
    }

    /**
     * @brief Metoda transformująca wierzchołek bryły do układu współrzędnych rodzica
     * 
     * @param Wierz - Wektor3D zawierający współrzędne wierzchołka
     * @return Wektor3D - Obiekt zawierający współrzędne punktu po jego rotacji
     * o odpowiedni kąt oraz przesunięciu o odpowiedni wektor
     */
    Wektor3D TransfDoUklWspRodzica(const Wektor3D &Wierz) const
    {
        Macierz3x3 rotacja;
        rotacja.setM(_KatOrientacji_stopnie, 'z');
        return (Wierz * rotacja) + _Polozenie;
    }
};

#endif