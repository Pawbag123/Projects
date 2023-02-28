#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#define PI 3.14159265

/**
 * @file Macierz.hh
 * @brief Plik zawiera definicje szablonu Macierz<> oraz jej metod
 *
 */

/*!
 * \brief  Szablon klasy Macierz
 *
 *  Modeluje pojęcie Macierzy o dowolnym rozmiarze
 * 
 */
template <int Wymiar>
class Macierz
{
  /**
   * @brief Tablica dwuwymiarowa typu double zawierajaca odpowiednie wartosci macierzy
   * 
   */
  double _Tab[Wymiar][Wymiar];

public:
  /**
 * @brief Konstruktor domyślny macierzy
 * 
 * Konstruktor domyślny wypełniający macierz zerami
 * 
 */
  Macierz()
  {
    for (int i = 0; i < Wymiar; ++i)
      for (int j = 0; j < Wymiar; ++j)
        _Tab[i][j] = 0;
  }

  /**
   * @brief Konstruktor macierzy z argumentem
   * 
   * Konstruktor macierzy, który wypełnia jej przekątną podaną liczbą
   * ma głównie na celu stworzenie macierzy jednostkowej
   * 
   * @param[in] liczba - liczba którą zostanie wypełniona przekątna
   */
  // Macierz(const int liczba)
  // {
  //   for (int i = 0; i < Wymiar; ++i)
  //     for (int j = 0; j < Wymiar; ++j)
  //       _Tab[i][j] = 0;
  //   for (int i = 0; i < Wymiar; ++i)
  //     _Tab[i][i] = liczba;
  // }

  Macierz(const double alfa)
  {
    _Tab[0][0] = cos(alfa * PI / 180);  //zapisanie cosinusow oraz sinusow
    _Tab[0][1] = -sin(alfa * PI / 180); //z odpowiedniego wzoru przy uzyciu
    _Tab[1][0] = sin(alfa * PI / 180);  //poprawnych funkcji
    _Tab[1][1] = cos(alfa * PI / 180);
    _Tab[2][2] = 1;
  }

  /**
   * @brief Przeciążenie operatora funkcyjnego
   * 
   * 
   * Przeciazenie operatora funkcyjnego w celu odniesienia sie do elementu macierzy
   * @param[in] X - pierwszy indeks tablicy 
   * @param[in] Y - drugi indeks tablicy 
   * @return double - liczba typu double, ktora byla przechowywana w danym miejscu macierzy
   */
  double operator()(const int X, const int Y) const
  {
    return _Tab[X][Y];
  }

  /**
   * @brief Przeciążenie operatora funkcyjnego
   * 
   * 
   * PPrzeciazenie operatora funkcyjnego w celu modyfikacji elementu macierzy
   * @param[in] X - pierwszy indeks tablicy 
   * @param[in] Y - drugi indeks tablicy 
   * @return double - liczba typu double, ktora byla przechowywana w danym miejscu macierzy,
   * jest ona modyfikowalna
   */
  double &operator()(const int X, const int Y)
  {
    return _Tab[X][Y];
  }

  /**
 * @brief Przeciążenie operatora mnożenia macierzy
 * 
 * Przeciążenie operatora mnożenia, które pozwala na wymnożenie ze sobą dwóch macierzy,
 * stworzone, w celu następującej po sobie rotacji przez daną macierz
 * 
 * @param[in] macierz - macierz mnożona 
 * @return Macierz<Wymiar> - macierz wynikowa
 */
  Macierz<Wymiar> operator*(const Macierz<Wymiar> &macierz) const
  {
    Macierz<Wymiar> wynik;
    for (int i = 0; i < Wymiar; i++)
      for (int j = 0; j < Wymiar; j++)
        for (int k = 0; k < Wymiar; k++)
          wynik(i, j) += _Tab[i][k] * macierz(k, j);
    return wynik;
  }

  /**
 * @brief Wyczyszczenie macierzy
 * 
 * Metoda, która wypełnia pola macierzy zerami, stworzona na potrzeby metody
 * Rotacja::UstalKoniec
 * 
 */
  void clear()
  {
    for (int i = 0; i < Wymiar; ++i)
      for (int j = 0; j < Wymiar; ++j)
        _Tab[i][j] = 0;
  }

  /**
   * @brief Ustalenie macierzy obrotu
   * 
   * Metoda tworząca macierz rotacji na podstawie podanego kąta
   * oraz znaku odpowiadającego osi rotacji
   * 
   * 
   * @param[in] alfa - Liczba typu double zawierająca wartość kąta 
   * @param[in] os - znak typu char przechowujący znak osi rotacji 
   */
  void setM(const double alfa, const char &os)
  {
    if (os == 'x')
      setX(alfa);
    else if (os == 'y')
      setY(alfa);
    else if (os == 'z')
      setZ(alfa);
  }

  /**
 * @brief Utworzenie macierzy obrotu wokół osi X
 * 
 * Metoda ustalająca odpowiednie wartości macierzy, aby na jej
 * podstawie była możliwa rotacja prostopadłościanu o zadany kąt alfa
 * wokół osi X
 * 
 * @param[in] alfa - Liczba typu double zawierająca wartość kąta
 */
  void setX(const double alfa)
  {
    _Tab[1][1] = cos(alfa * PI / 180);  //zapisanie cosinusow oraz sinusow
    _Tab[1][2] = -sin(alfa * PI / 180); //z odpowiedniego wzoru przy uzyciu
    _Tab[2][1] = sin(alfa * PI / 180);  //poprawnych funkcji
    _Tab[2][2] = cos(alfa * PI / 180);
    _Tab[0][0] = 1;
  }

  /**
 * @brief Utworzenie macierzy obrotu wokół osi Y
 * 
 * Metoda ustalająca odpowiednie wartości macierzy, aby na jej
 * podstawie była możliwa rotacja prostopadłościanu o zadany kąt alfa
 * wokół osi Y
 * 
 * @param[in] alfa - Liczba typu double zawierająca wartość kąta
 */
  void setY(const double alfa)
  {
    _Tab[0][0] = cos(alfa * PI / 180);  //zapisanie cosinusow oraz sinusow
    _Tab[2][0] = -sin(alfa * PI / 180); //z odpowiedniego wzoru przy uzyciu
    _Tab[0][2] = sin(alfa * PI / 180);  //poprawnych funkcji
    _Tab[2][2] = cos(alfa * PI / 180);
    _Tab[1][1] = 1;
  }

  /**
 * @brief Utworzenie macierzy obrotu wokół osi Z
 * 
 * Metoda ustalająca odpowiednie wartości macierzy, aby na jej
 * podstawie była możliwa rotacja prostopadłościanu o zadany kąt alfa
 * wokół osi Z
 * 
 * @param[in] alfa - Liczba typu double zawierająca wartość kąta
 */
  void setZ(const double alfa)
  {
    _Tab[0][0] = cos(alfa * PI / 180);  //zapisanie cosinusow oraz sinusow
    _Tab[0][1] = -sin(alfa * PI / 180); //z odpowiedniego wzoru przy uzyciu
    _Tab[1][0] = sin(alfa * PI / 180);  //poprawnych funkcji
    _Tab[1][1] = cos(alfa * PI / 180);
    _Tab[2][2] = 1;
  }
};

/*Przeciazenie operatora bitowego w celu wyswietlenia macierzy 
(funkcja nie zostala uzyta w programie. sluzyla jako pomoc w trakcie pracy)
Parametry:
out - Strumien wyjsciowy na ktorym ma zostac wyswietlona macierz
macierz - macierz ktora ma zostac wyswietlona
Wartosc zwrocona:
Strumien wyjsciowy */
/**
 * @brief Przeciążenie operatora bitowego
 * 
 * Przeciazenie operatora bitowego w celu wyswietlenia macierzy rotacji
 * 
 * 
 * 
 * @tparam Wymiar - Rozmiar macierzy
 * @param out - Strumien wyjsciowy
 * @param macierz - macierz rotacji, ktora ma zostać wyświetlona
 * @return std::ostream& - Strumień wyjściowy
 */
template <int Wymiar>
std::ostream &operator<<(std::ostream &out, Macierz<Wymiar> const &macierz)
{
  for (int i = 0; i < Wymiar; i++)
  {
    out << "| ";
    for (int j = 0; j < Wymiar; ++j)
    {
      out << std::setw(16) << std::fixed << std::setprecision(10) << macierz(i, j) << " ";
    }
    out << "|" << std::endl;
  }
  return out;
}

#endif
