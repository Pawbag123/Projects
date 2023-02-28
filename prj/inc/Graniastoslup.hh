#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include "Bryla.hh"

/**
 * @file Graniastoslup.hh
 * @brief Plik zawiera definicję klasy Graniastosłup
 * 
 */

/**
 * @brief Klasa modelująca pojęcie graniastosłupa
 * 
 */
class Graniastoslup : public Bryla
{

public:
    /**
     * @brief Konstruktor Graniastoslupa
     * 
     * @param Skala - Obiekt typu Wektor3D zawierający skalę graniastosłupa
     * @param Polozenie - Obiekt typu Wektor3D zawierający Położenie graniastosłupa
     */
    Graniastoslup(const Wektor3D &Skala, const Wektor3D &Polozenie)
        : Bryla(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, Skala, Polozenie){};

    // Graniastoslup(
    //     const std::string &NazwaPlikuFinalnego,
    //     const Wektor3D &Skala, const Wektor3D &Polozenie,
    //     const double KatOrientacji) : Bryla(PLIK_WZORCOWEGO_GRANIASTOSLUPA6,
    //                                         NazwaPlikuFinalnego, Skala,
    //                                         Polozenie, KatOrientacji){};
};

#endif