#include "ElemPow.hh"

/**
 * @file ElemPow.cpp
 * 
 * @brief Plik zawierający rozwinięcie metod klasy ElemPow
 * 
 */

bool ElemPow::Oblicz_i_Zapisz_WspGlbElementu() const
{
    std::ifstream Plik_Wz(WezNazwePliku_BrylaWzorcowa());
    std::ofstream Plik_Finalny(WezNazwePliku_BrylaFinalna());
    if (!Plik_Wz.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << WezNazwePliku_BrylaWzorcowa() << std::endl
                  << std::endl;
        return false;
    }
    if (!Plik_Finalny.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << WezNazwePliku_BrylaFinalna() << std::endl
                  << std::endl;
        return false;
    }
    return TransformujElement(Plik_Wz, Plik_Finalny);
}