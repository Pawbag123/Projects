#include "Gora_z_Dl_Grania.hh"

/**
 * @file Gora_z_Dl_Grania.cpp
 * 
 * @brief Plik zawierający rozwinięcie metod klasy Gora_z_Dl_Grania
 * 
 */

Gora_z_Dl_Grania::Gora_z_Dl_Grania(const Wektor3D &Skala,
                                   const Wektor3D &Polozenie)
    : ElemPow(PLIK_WZORCOWEGO_SZESCIANU_POW,
              Skala,
              Polozenie)
{
    ZwiekszIlElem();
    PrzypiszNrElem();
    ++_Nr_Gory_z_Dl_Grania;
    UstalNazwePliku_BrylaFinalna(
        SCIEZKA_DO_PLIKU_ELEMENT +
        std::to_string(WezNrElem()) +
        PLIK_GORY_Z_DLUGA_GRANIA +
        std::to_string(_Nr_Gory_z_Dl_Grania) + ".dat");
}

bool Gora_z_Dl_Grania::TransformujElement(std::ifstream &Plik_We,
                                          std::ofstream &Plik_Wy) const
{
    assert(Plik_We.good());
    assert(Plik_Wy.good());

    Wektor3D Wierz;

    for (unsigned int Ind_krawedz = 0; Ind_krawedz < 5; ++Ind_krawedz)
    {
        for (unsigned int Ind_wierz = 0; Ind_wierz < 4; ++Ind_wierz)
        {
            Plik_We >> Wierz;
            if (Plik_We.fail())
                return false;

            if (Wierz[2] > 0.5)
            { // Tutaj realizowana jest deformacja
                if (Wierz[0] < 0)
                    Wierz[0] = fabs(Wierz[0]);
            }

            Wierz = Skaluj(Wierz);
            Wierz = TransfDoUklWspRodzica(Wierz);

            Plik_Wy << Wierz << std::endl;
            if (Plik_Wy.fail())
                return false;
        }
        Plik_Wy << std::endl; // Dodatkowa linia oddzielająca krawędzie
    }
    return !Plik_Wy.fail();
}

bool Gora_z_Dl_Grania::SprawdzCzyZajete(ObiektSc *Obiekt)
{
    UstalParametry();
    Obiekt->UstalParametry();
    Wektor3D Sr = Obiekt->WezSrodek();
    double Pr = Obiekt->WezPromien();
    double DlX = fabs(Sr[0] - _SrodekObiektu[0]);
    double DlY = fabs(Sr[1] - _SrodekObiektu[1]);
    if (DlX > (_BokX + Pr))
        return false;
    if (DlY > (_BokY + Pr))
        return false;
    if (DlX <= (_BokX))
        return true;
    if (DlY <= (_BokY))
        return true;

    double OdlWierzch = (DlX - _BokX) * (DlX - _BokX) +
                        (DlY - _BokY) * (DlY - _BokY);

    return (OdlWierzch <= (Pr * Pr));
}