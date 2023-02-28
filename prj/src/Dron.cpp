#include "Dron.hh"

/**
 * @file Dron.cpp
 * @brief Plik zawierający rozwinięcie metod klasy Dron
 * 
 *  
 */

Dron::Dron(const Wektor3D &Polozenie, const double KatOrientacji)
    : UkladWsp(Polozenie, KatOrientacji),
      _KorpusDrona(Wektor3D{SKALA_KORPUSU},
                   Wektor3D{TRANSLACJA_KORPUS}),
      _RotorDrona{{Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_LEWY_PRZEDNI})},
                  {Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_PRAWY_PRZEDNI})},
                  {Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_LEWY_TYLNY})},
                  {Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_PRAWY_TYLNY})}}
{
    ++NrDrona;
    _NrDrona = NrDrona;
    _KorpusDrona.UstalNazwePliku_BrylaFinalna(SCIEZKA_DO_PLIKU +
                                              std::to_string(NrDrona) +
                                              NAZWA_KORPUSU);
    for (int i = 0; i < 4; i++)
    {
        _RotorDrona[i].UstalNazwePliku_BrylaFinalna(SCIEZKA_DO_PLIKU +
                                                    std::to_string(NrDrona) +
                                                    NAZWA_ROTORA + std::to_string(i + 1) +
                                                    ".dat");
    }
}

bool Dron::TransformujBryle(std::ifstream &Plik_We,
                            std::ofstream &Plik_Wy, const Bryla *Br) const
{
    Wektor3D Wierz;
    assert(Plik_We.good());
    assert(Plik_Wy.good());

    Plik_We >> Wierz;
    while (!Plik_We.fail())
    {
        for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ;
             ++IloscWierzcholkow)
        {
            Wierz = Br->Skaluj(Wierz);
            Wierz = Br->TransfDoUklWspRodzica(Wierz);
            Wierz = TransfDoUklWspRodzica(Wierz);
            Plik_Wy << Wierz << std::endl;
            Plik_We >> Wierz;
            assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ - 1 || !Plik_We.fail());
        }
        Plik_Wy << std::endl;
    }
    return !Plik_Wy.fail();
}

bool Dron::Oblicz_i_Zapisz_WspGlbKorpusu() const
{
    std::ifstream Plik_Wz(_KorpusDrona.WezNazwePliku_BrylaWzorcowa());
    std::ofstream Plik_Finalny(_KorpusDrona.WezNazwePliku_BrylaFinalna());
    if (!Plik_Wz.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << _KorpusDrona.WezNazwePliku_BrylaWzorcowa() << std::endl
                  << std::endl;
        return false;
    }
    if (!Plik_Finalny.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << _KorpusDrona.WezNazwePliku_BrylaFinalna() << std::endl
                  << std::endl;
        return false;
    }
    return TransformujBryle(Plik_Wz, Plik_Finalny, &_KorpusDrona);
}

bool Dron::Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup &Rotor) const
{
    std::ifstream Plik_Wz(Rotor.WezNazwePliku_BrylaWzorcowa());
    std::ofstream Plik_Finalny(Rotor.WezNazwePliku_BrylaFinalna());
    if (!Plik_Wz.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << Rotor.WezNazwePliku_BrylaWzorcowa() << std::endl
                  << std::endl;
        return false;
    }
    if (!Plik_Finalny.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << Rotor.WezNazwePliku_BrylaFinalna() << std::endl
                  << std::endl;
        return false;
    }
    return TransformujBryle(Plik_Wz, Plik_Finalny, &Rotor);
}

bool Dron::Oblicz_i_Zapisz_WspGlbDrona() const
{
    if (!Oblicz_i_Zapisz_WspGlbKorpusu())
        return false;
    for (int i = 0; i < 4; ++i)
        if (!Oblicz_i_Zapisz_WspGlbRotora(_RotorDrona[i]))
            return false;
    return true;
}

void Dron::ObrocRotory()
{
    _RotorDrona[0].DodajKat(-SKOK_OBROTU_ROTOROW_stopnie);
    _RotorDrona[1].DodajKat(SKOK_OBROTU_ROTOROW_stopnie);
    _RotorDrona[2].DodajKat(SKOK_OBROTU_ROTOROW_stopnie);
    _RotorDrona[3].DodajKat(-SKOK_OBROTU_ROTOROW_stopnie);
}

bool Dron::WykonajPionowyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze)
{
    if (DlugoscLotu >= 0)
    {
        std::cout << std::endl
                  << "Wznoszenie ... " << std::endl;
        for (double wys = 0; wys <= DlugoscLotu; wys += 2)
        {
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            Wznies(wys);
            ObrocRotory();
            usleep(40000); // 0.1 ms
            Lacze.Rysuj();
        }
        return true;
    }
    else
    {
        std::cout << std::endl
                  << "Opadanie ... " << std::endl;
        for (double wys = -DlugoscLotu; wys >= -2; wys -= 2)
        {
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            Wznies(wys);
            ObrocRotory();
            usleep(40000); // 0.1 ms
            Lacze.Rysuj();
        }
        return true;
    }
    return false;
}

bool Dron::WykonajPoziomyLot(PzG::LaczeDoGNUPlota &Lacze)
{
    std::cout << "Lot do przodu ... " << std::endl;
    for (double dl = 0; dl <= _SciezkaDrona.WezDl(); ++dl)
    {
        if (!Oblicz_i_Zapisz_WspGlbDrona())
            return false;
        Przesun(_SciezkaDrona.WezDlXY(), _SciezkaDrona.WezDl());
        ObrocRotory();
        usleep(30000);
        Lacze.Rysuj();
    }
    return true;
}

bool Dron::WykonajKrotkiPoziomyLot(PzG::LaczeDoGNUPlota &Lacze)
{
    Wektor3D Dl{20, 0, 0};
    Macierz3x3 Rotacja;
    Rotacja.setZ(_SciezkaDrona.WezKat());
    Dl = Dl * Rotacja;
    double DlXY[2]{Dl[0], Dl[1]};
    std::cout << "Napotkano przeszkode, omijanie ... " << std::endl;
    for (double dl = 0; dl <= 20; ++dl)
    {
        if (!Oblicz_i_Zapisz_WspGlbDrona())
            return false;
        Przesun(DlXY, 20);
        ObrocRotory();
        usleep(30000);
        Lacze.Rysuj();
    }
    return true;
}

bool Dron::WykonajObrot(PzG::LaczeDoGNUPlota &Lacze)
{
    std::cout << "Zmiana orientacji ... " << std::endl;
    if (WezKat() <= _SciezkaDrona.WezKat())
    {
        for (double KatOb = WezKat(); KatOb <= _SciezkaDrona.WezKat(); KatOb += 5)
        {
            UstawKat(KatOb);
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            ObrocRotory();
            usleep(60000);
            Lacze.Rysuj();
        }
        return true;
    }
    if (WezKat() > _SciezkaDrona.WezKat())
    {
        for (double KatOb = WezKat(); KatOb >= _SciezkaDrona.WezKat(); KatOb -= 5)
        {
            UstawKat(KatOb);
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            ObrocRotory();
            usleep(60000);
            Lacze.Rysuj();
        }
        return true;
    }
    return false;
}

void Dron::UstalParametry()
{
    Wektor3D Pol = _RotorDrona[0].WezPolozenie();
    Wektor3D Skala = _RotorDrona[0].WezSkale();
    _SrodekObiektu = WezPolozenie();
    _Promien = sqrt((Pol[0] + Skala[0] * 0.5) * (Pol[0] + Skala[0] * 0.5) +
                    (Pol[1] + Skala[1] * 0.5) * (Pol[1] + Skala[1] * 0.5));
}

bool Dron::SprawdzCzyZajete(ObiektSc *Obiekt)
{
    Obiekt->UstalParametry();
    UstalParametry();
    Wektor3D Sr = Obiekt->WezSrodek();
    return sqrt((_SrodekObiektu[0] - Sr[0]) * (_SrodekObiektu[0] - Sr[0]) +
                (_SrodekObiektu[1] - Sr[1]) * (_SrodekObiektu[1] - Sr[1])) <=
           (_Promien + Obiekt->WezPromien());
}

bool Dron::SprawdzCzyZajeteLista(const std::list<shared_ptr<ObiektSc>> &ListaObiektow)
{
    int licz = 0;
    for (const std::shared_ptr<ObiektSc> &Ob : ListaObiektow)
        if (Ob->SprawdzCzyZajete(this))
        {
            ++licz;
            if (licz > 1)
                Ob->DajNazwe();
        }
    return licz >= 2;
}
