#include "Sciezka.hh"

/**
 * @file Sciezka.cpp
 * @brief Plik zawierający rozwinięcie metod klasy Sciezka
 * 
 */

bool Sciezka::NarysujSciezke(PzG::LaczeDoGNUPlota &Lacze,
                             const Wektor3D &Start,
                             const double KatDrona)
{
    std::ofstream StrmWy(PLIK_TRASY_PRZELOTU);
    UstalSciezke(Start, KatDrona);
    if (!StrmWy.is_open())
    {
        std::cerr << std::endl
                  << " Nie mozna otworzyc do zapisu pliku: "
                  << PLIK_TRASY_PRZELOTU << std::endl
                  << std::endl;
        return false;
    }
    for (size_t i = 0; i < _PunktySciezki.size(); ++i)
    {
        StrmWy << _PunktySciezki[i] << std::endl;
    }

    Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
    return !StrmWy.fail();
}

void Sciezka::UstalSciezke(const Wektor3D &Start, const double KatDrona)
{
    DodajStart(Start);
    DodajPion(Start);
    UstalKatObrotu(KatDrona);
    UstalDlugoscLotu();
    DodajPoziom(Start);
    DodajKoniec();
}

void Sciezka::DodajPoziom(const Wektor3D &Start)
{
    Macierz3x3 Rotacja;
    Rotacja.setZ(_KatRotacji);
    Wektor3D tmp = Start;
    tmp[2] = tmp[2] + LOT_PIONOWY;
    Wektor3D temp = _LotPoz * Rotacja;
    tmp = tmp + temp;
    _DlXY[0] = temp[0];
    _DlXY[1] = temp[1];
    _PunktySciezki.push_back(tmp);
}

void Sciezka::UstalKatObrotu(const double KatDrona)
{
    double Kat;
    std::cout << "Podaj kierunek lotu (kat w stopniach)> ";
    std::cin >> Kat;
    while (std::cin.fail())
    {
        std::cerr << "\nWprowadzono niepoprawna wartosc kata!\n";
        std::cout << "\nPodaj kierunek lotu (kat w stopniach)> ";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin >> Kat;
    }
    _KatRotacji = Kat + KatDrona;
}

void Sciezka::UstalDlugoscLotu()
{
    double Dl;
    std::cout << "Podaj dlugosc lotu> ";
    std::cin >> Dl;
    while (std::cin.fail())
    {
        std::cerr << "\nWprowadzono niepoprawna wartosc dlugosci lotu!\n";
        std::cout << "\nPodaj dlugosc lotu> ";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin >> Dl;
    }
    _LotPoz[0] = Dl;
    _DlLotu = Dl;
}

void Sciezka::DodajFragmentSciezki()
{
    _PunktySciezki.clear();
    DodajStart(_PolDrona);
    DodajPion(_PolDrona);
    DodajFragmentLotu();
    DodajPoziom(_PolDrona);
    DodajKoniec();
}

bool Sciezka::DorysujSciezke()
{
    std::ofstream StrmWy(PLIK_TRASY_PRZELOTU);
    DodajFragmentSciezki();
    if (!StrmWy.is_open())
    {
        std::cerr << std::endl
                  << " Nie mozna otworzyc do zapisu pliku: "
                  << PLIK_TRASY_PRZELOTU << std::endl
                  << std::endl;
        return false;
    }
    for (size_t i = 0; i < _PunktySciezki.size(); ++i)
    {
        StrmWy << _PunktySciezki[i] << std::endl;
    }
    return !StrmWy.fail();
}