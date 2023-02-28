#include "Gora_z_Ostr.hh"

/**
 * @file Gora_z_Ostr.cpp
 * 
 * @brief Plik zawierający rozwinięcie metod klasy Gora_z_Ostr
 * 
 */

Gora_z_Ostr::Gora_z_Ostr(const Wektor3D &Skala,
                         const Wektor3D &Polozenie)
    : ElemPow(PLIK_WZORCOWEGO_SZESCIANU_POW,
              Skala,
              Polozenie)
{
    ZwiekszIlElem();
    PrzypiszNrElem();
    ++_Nr_Gory_z_Ostr;
    UstalNazwePliku_BrylaFinalna(
        SCIEZKA_DO_PLIKU_ELEMENT +
        std::to_string(WezNrElem()) +
        PLIK_GORY_Z_OSTR +
        std::to_string(_Nr_Gory_z_Ostr) + ".dat");
}

bool Gora_z_Ostr::TransformujElement(std::ifstream &Plik_We,
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
                Wierz[0] = Wierz[1] = 0;
            }
            else if (Wierz[2] == 0.5)
            {
                Wierz[0] /= 2;
                Wierz[1] /= 2;
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

bool Gora_z_Ostr::SprawdzCzyZajete(ObiektSc *Obiekt)
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
