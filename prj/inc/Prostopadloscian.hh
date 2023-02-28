#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include "Bryla.hh"
/**
 * @file Prostopadloscian.hh
 * @brief Plik zawiera definicję klasy Prostopadloscian
 * 
 */

/**
 * @brief Klasa modelująca pojęcie Prostopadłościanu
 * 
 */
class Prostopadloscian : public Bryla
{
public:
    /**
     * @brief Konstruktor Prostopadłościanu
     * 
     * @param Skala - Obiekt typu Wektor3D zawierający skalę Prostopadłościanu
     * @param Polozenie - Obiekt typu Wektor3D zawierający Położenie Prostopadłościanu
     */
    Prostopadloscian(const Wektor3D &Skala, const Wektor3D &Polozenie)
        : Bryla(PLIK_WZORCOWEGO_SZESCIANU, Skala, Polozenie){};

    // Prostopadloscian(
    //     const std::string &NazwaPlikuFinalnego,
    //     const Wektor3D &Skala, const Wektor3D &Polozenie,
    //     const double KatOrientacji) : Bryla(PLIK_WZORCOWEGO_SZESCIANU,
    //                                         NazwaPlikuFinalnego, Skala,
    //                                         Polozenie, KatOrientacji){};
};
#endif