#ifndef BRYLA_HH
#define BRYLA_HH

#include "UkladWsp.hh"
#include "ObiektSc.hh"
#include <list>
#include <memory>
/**
 * @file Bryla.hh 
 * 
 *
 * @brief Plik zawiera definicję klasy Bryla
 * 
 */

/**
 * @brief Klasa modeluje pojęcie bryły
 * 
 */
class Bryla : public UkladWsp
{
    /**
     * @brief Obiekt typu string zawierajacy ścieżkę do pliku zawierającego bryłę wzorcową
     * 
     */
    std::string _NazwaPliku_BrylaWzorcowa;
    /**
     * @brief Obiekt typu string zawierajacy ścieżkę do pliku zawierającego bryłę finalną
     * 
     */
    std::string _NazwaPliku_BrylaFinalna;
    /**
     * @brief Obiekt typu Wektor3D zawierający skalę bryły
     * 
     */
    Wektor3D _Skala;

protected:
    /**
     * @brief Konstruktor Bryły
     * 
     * @param NazwaPlikuBrylaWzorcowa - Nazwa Pliku zawierającego bryłę wzorcową
     * @param Skala - Obiekt typu Wektor3D zawierający skalę bryły
     * @param Polozenie - Obiekt typu Wektor3D zawierający położenie bryły
     */
    Bryla(const std::string &NazwaPlikuBrylaWzorcowa,
          const Wektor3D &Skala,
          const Wektor3D &Polozenie)
        : UkladWsp(Polozenie),
          _NazwaPliku_BrylaWzorcowa(NazwaPlikuBrylaWzorcowa),
          _Skala(Skala){};

    // Bryla(const std::string &NazwaPlikuBrylaWzorcowa,
    //       const std::string &NazwaPlikuBrylaFinalna,
    //       const Wektor3D &Skala, const Wektor3D &Polozenie,
    //       const double KatOrientacji) : UkladWsp(Polozenie, KatOrientacji),
    //                                     _NazwaPliku_BrylaWzorcowa(NazwaPlikuBrylaWzorcowa),
    //                                     _NazwaPliku_BrylaFinalna(NazwaPlikuBrylaFinalna),
    //                                     _Skala(Skala){};

public:
    /**
     * @brief Metoda, która służy do skalowania wierzchołków bryły
     * 
     * @param Wierz - Obiekt typu Wektor3D zawierający wierzchołek bryły
     * @return Wektor3D - Obiekt typu Wektor3D zawierający wierzchołek po skalowaniu
     */
    Wektor3D Skaluj(const Wektor3D &Wierz) const
    {
        Wektor3D Wynik;
        for (int i = 0; i < 3; ++i)
            Wynik[i] = Wierz[i] * _Skala[i];
        return Wynik;
    };

    Wektor3D WezSkale() const
    {
        return _Skala;
    }

    /**
     * @brief Metoda zwracająca nazwę pliku zawierającego bryłę wzorcową
     * 
     * @return const std::string& - nazwa pliku zawierającego bryłę wzorcową
     */
    const std::string &WezNazwePliku_BrylaWzorcowa() const
    {
        return _NazwaPliku_BrylaWzorcowa;
    };

    /**
     * @brief Metoda zwracająca nazwę pliku zawierającego bryłę finalną
     * 
     * @return const std::string& - nazwa pliku zawierającego bryłę finalną
     */
    const std::string &WezNazwePliku_BrylaFinalna() const
    {
        return _NazwaPliku_BrylaFinalna;
    };

    /**
     * @brief Metoda ustalająca nazwę pliku zawierającego bryłę finalną
     * 
     * @param Nazwa - Nazwa pliku zawierającego bryłę finalną
     */
    void UstalNazwePliku_BrylaFinalna(const std::string &Nazwa)
    {
        _NazwaPliku_BrylaFinalna = Nazwa;
    }

    /**
     * @brief Destruktor obiektu Bryla, usuwa plik finalny zmodyfikowanej bryly
     * 
     */
    ~Bryla()
    {
        std::remove(WezNazwePliku_BrylaFinalna().c_str());
    }
};

#endif