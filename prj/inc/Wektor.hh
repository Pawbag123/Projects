#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include "Macierz.hh"
#include <cassert>
#include "Licznik.hh"

/*!
 * @file Wektor.hh
 * @brief Plik zawierający definicję szablon Wektor<>
 *
 * 
 */

/*!
 * \brief Szablon klasy Wektor
 * 
 *  Szablon, który modeluje pojęcie klasy Wektor o dowolnym rozmiarze
 */
template <int Wymiar>
class Wektor : public Licznik<Wektor<3>>
{
  /**
   * @brief Tablica typu double przechowujaca wartosci obiektu
   * 
   */
  double _wsp[Wymiar];

public:
  /**
 * @brief Konstruktor bezparametrowy
 * 
 * Konstruktor tworzy obiekt typu Wektor, a następnie wypełnia go zerami
 * 
 */
  Wektor()
  {
    for (double &wsp_i : _wsp)
      wsp_i = 0;
  }

  /**
 * @brief Konstruktor Dla szablonu Wektor
 * 
 * @param LWartosci - Wartosci typu double, które maja zostać umieszczone w obiekcie
 */
  Wektor(const std::initializer_list<double> &LWartosci)
  {
    assert(LWartosci.size() <= Wymiar);
    int idx = -1;
    for (double Wart : LWartosci)
      (*this)[++idx] = Wart;

  }

  /**
   * @brief Przeciążenie operatora indeksowania
   * 
   * przeciazenie operatora w celu uzycia w funkcjach bez modyfikacji elementu
   * 
   * @param[in] i  - liczba typu int oznaczająca indeks
   * @return double - Liczba typu double znajdujaca sie w Tablicy klasy Wektor o podanym indeksie
   */
  double operator[](const int i) const
  {
    return _wsp[i];
  }

  /*przeciazenie operatora w celu uzycia w funkcjach modyfikujacych element
  Parametry:
  i - liczba typu int oznaczajaca indeks
  Wartosc zwrocona:
  Liczba typu double znajdujaca sie w Tablicy klasy Wektor o podanym indeksie
  wartosc modyfikowalna*/
  /**
   * @brief Przeciążenie operatora indeksowania
   * 
   * przeciazenie operatora w celu uzycia w funkcjach modyfikujacych element
   * 
   * @param[in] i - liczba typu int oznaczająca indeks
   * @return double& - Liczba typu double znajdujaca sie w Tablicy klasy Wektor
   *  o podanym indeksie, wartosc modyfikowalna
   */
  double &operator[](const int i)
  {
    return _wsp[i];
  }

  /**
   * @brief Przeciążenie operatora dodawania
   * 
   * Przeciazenie operatora dodawania dla wektorow w celu przesuniecia 
   * 
   * @param[in] Skl2 - Skladnik dodawania
   * @return Wektor<Wymiar> - Wektor bedacy suma Wektora wykorzystanego
   *  w metodzie oraz zawartego jako parametr
   */
  Wektor<Wymiar> operator+(const Wektor<Wymiar> &Skl2) const
  {
    Wektor<Wymiar> Wynik;
    for (int i = 0; i < Wymiar; ++i)
      Wynik[i] = _wsp[i] + Skl2[i];
    return Wynik;
  }

  /**
   * @brief Przeciążenie operatora odejmowania
   * 
   * Przeciążenie operatora odejmowania wektorów w celu wyznaczenia długości boków
   * 
   * @param Skl2 - Składnik odejmowania
   * @return Wektor<Wymiar> - Wektor będący różnicą wektora wykorzystanego w metodzie oraz
   * zawartego jako parametr
   */
  Wektor<Wymiar> operator-(const Wektor<Wymiar> &Skl2) const
  {
    Wektor<Wymiar> Wynik;
    for (int i = 0; i < Wymiar; ++i)
      Wynik[i] = fabs(_wsp[i] - Skl2[i]); //wartosc bezwzgledna roznicy wspolrzednych
    return Wynik;
  }

  /**
   * @brief Przeciążenie operatora mnożenia
   * 
   * Przeciążenie operatora mnożenia dla wektora i macierzy, w celu rotacji
   * wierzchołków prostopadłościanu
   * 
   * @param[in] macierz - Macierz rotacji
   * @return Wektor<Wymiar> - Obiekt typu Wektor zawierający nowe współrzędne punktu
   */
  Wektor<Wymiar> operator*(const Macierz<Wymiar> &macierz) const
  {
    Wektor<Wymiar> wynik; //mnozenie macierzy z podanego w instrukcji wzoru
    for (int i = 0; i < Wymiar; ++i)
      for (int j = 0; j < Wymiar; ++j)
        wynik[i] += _wsp[j] * macierz(i, j);
    return wynik;
  }

  /* Metoda ustalajaca parametry Wektora uzyta w metodzie prostokata Inicjalizuj
  Parametry:
  X - liczba typu double, ktora zostanie umieszczona jako pierwsza wspolrzedna wektora
  Y - liczba typu double ktora zostanie umieszczona jako druga wspolrzedna wektora
  Wartosc zwrocona:
  Metoda typu void, modyfikuje obiekt klasy Wektor2D */

  /**
   * @brief Ustalenie Wektora
   * 
   * Metoda ustalajaca parametry Wektora uzyta w metodzie Prostopadloscian::Inicjalizuj
   * 
   * @param X - Liczba typu double, która zostanie umieszczona
   * jako pierwsza współrzędna wektora
   * @param Y  - Liczba typu double, która zostanie umieszczona
   * jako druga współrzędna wektora
   * @param Z - Liczba typu double, która zostanie umieszczona
   * jako trzecia współrzędna wektora
   */
  void setW(const double X, const double Y, const double Z)
  {
    _wsp[0] = X;
    _wsp[1] = Y;
    _wsp[2] = Z;
  }

  static void WyswietlIlosc()
  {
    int IlAkt=WezAkt();
    int Suma=WezSume();
    std::cout << "Aktualna ilosc obiektow Wektor3D: " << IlAkt << std::endl;
    std::cout << "Laczna ilosc obiektow Wektor3D: " << Suma << std::endl;
  }

};

/**
 * @brief Przeciążenie operatora bitowego wczytania Wektora
 * 
 * Przeciazenie operatora bitowego w celu wczytania wektora podanego przez uzytkownika
Funkcja wczytuje dwie liczby typu double, oddzielone spacja a nastepnie zapisuje je do wektora
 *
 * @tparam Wymiar - Wymiar Wektora 
 * @param in - Strumień wejściowy służący do wczytania danych 
 * @param wektor - obiekt klasy Wektor który zostanie zmodyfikowany po wczytaniu
 * odpowiednich wartości
 * @return std::istream& - Strumień wyjściowy 
 */
template <int Wymiar>
std::istream &operator>>(std::istream &in, Wektor<Wymiar> &wektor)
{
  double wsp[Wymiar]; //wczytanie obu liczb skladowych oddzielonych spacja
  for (int i = 0; i < Wymiar; ++i)
    in >> wsp[i]; //po poprawnym wczytaniu zapisanie do wektora
  if (in.fail())
    return in;
  for (int i = 0; i < Wymiar; ++i)
    wektor[i] = wsp[i];
  return in;
}

/**
 * @brief Przeciążenie operatora bitowego wyświetlania Wektora
 * 
 * Przeciazenie operatora bitowego w celu wyswietlenia Wektora
 * Funkcja zostala stworzona na potrzeby wyswietlenia wierzcholkow prostokata
 * Wyswietla ona wartosci wektora. Dane sa odpowiednio sformatowane,
 * tzn. przyjęto notację stałoprzecinkową z dokładnością do 10 miejsca po przecinku.
 * Szerokość wyświetlanego pola to 16 miejsc, sposób wyrównywania - do prawej strony.
 * 
 * @tparam Wymiar - Wymiar Wektora
 * @param out - Strumień wyjściowy, na którym ma zostać wyświetlony Wektor
 * @param wektor - Wektor, który ma zostać wyświetlony
 * @return std::ostream& - Strumień wyjściowy
 */
template <int Wymiar>
std::ostream &operator<<(std::ostream &out, const Wektor<Wymiar> &wektor)
{
  for (int i = 0; i < Wymiar; ++i)
    out << std::setw(16) << std::fixed << std::setprecision(10) << wektor[i];
  return out;
}

#endif
