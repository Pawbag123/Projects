#include "Scena.hh"

/**
 * @file Scena.cpp
 * @brief Plik zawierający rozwinięcie metod klasy Scena
 * 
 */

Scena::Scena(const Wektor3D &Polozenie1,
             const double KatObrotu1,
             const Wektor3D &Polozenie2,
             const double KatObrotu2)
    : _Pliki()
{
    _ListaDronow.emplace_back(new Dron(Polozenie1, KatObrotu1));
    _ListaDronow.emplace_back(new Dron(Polozenie2, KatObrotu2));
}

void Scena::WyswietlPolozenie()
{
    int nr = 0;
    for (const std::shared_ptr<Dron> &i : _ListaDronow)
    {
        i->WyswietlPol();
        if (_AktDron == nr)
            i->WyswietlAkt();
        std::cout << std::endl;
        ++nr;
    }
}

void Scena::WyswietlAktPolozenie()
{
    std::cout << "Polozenie Drona aktywnego (x,y): ";
    UzyjAktywnegoDrona().WyswietlWsp();
    std::cout << std::endl;
}

void Scena::DodajNazwyPlikow()
{
    UmiescNazwyPlikow();
    for (int i = 0; i <= _Pliki.WezIlosc(); ++i)
        _Lacze.DodajNazwePliku(_Pliki.WezNazwe(i).c_str());
}

bool Scena::InicjalizujScene()
{
    for (const std::shared_ptr<Dron> &i : _ListaDronow)
        if (!i->Oblicz_i_Zapisz_WspGlbDrona())
            return false;
    _Elementy.emplace_back(new Gora_z_Ostr(Wektor3D{SKALA_GORY_Z_OSTRYM_SZCZYTEM2},
                                           Wektor3D{TRANSLACJA_GORA_Z_OSTRYM_SZCZYTEM2}));
    if (!_Elementy.back()->Oblicz_i_Zapisz_WspGlbElementu())
        return false;
    _Elementy.emplace_back(new Gora_z_Ostr(Wektor3D{SKALA_GORY_Z_OSTRYM_SZCZYTEM},
                                           Wektor3D{TRANSLACJA_GORA_Z_OSTRYM_SZCZYTEM}));
    if (!_Elementy.back()->Oblicz_i_Zapisz_WspGlbElementu())
        return false;
    _Elementy.emplace_back(new Gora_z_Dl_Grania(Wektor3D{SKALA_GORY_Z_DLUGA_GRANIA},
                                                Wektor3D{TRANSLACJA_GORA_Z_DLUGA_GRANIA}));
    if (!_Elementy.back()->Oblicz_i_Zapisz_WspGlbElementu())
        return false;

    for (const std::shared_ptr<Dron> &i : _ListaDronow)
        _Obiekty.emplace_back(i);
    for (const std::shared_ptr<ElemPow> &i : _Elementy)
        _Obiekty.emplace_back(i);
    return true;
}

void Scena::InicjalizujLacze()
{
    _Lacze.ZmienTrybRys(PzG::TR_3D);
    _Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.
    _Lacze.UstawZakresX(0, 200);
    _Lacze.UstawZakresY(0, 200);
    _Lacze.UstawZakresZ(0, 120);
    _Lacze.UstawRotacjeXZ(64, 65); // Tutaj ustawiany jest widok
    DodajNazwyPlikow();
    for (std::list<shared_ptr<ElemPow>>::iterator it = _Elementy.begin();
         it != _Elementy.end(); ++it)
        _Lacze.DodajNazwePliku((*it)->WezNazwePliku_BrylaFinalna().c_str());
    _Lacze.Rysuj();
}

bool Scena::LotDrona()
{
    UzyjAktywnegoDrona().UstalPolSciezka();
    if (!UzyjAktywnegoDrona().PlanujPoczatkowaSciezke(_Lacze))
        return false;
    if (!UzyjAktywnegoDrona().WykonajPionowyLot(LOT_PIONOWY, _Lacze))
        return false;
    if (!UzyjAktywnegoDrona().WykonajObrot(_Lacze))
        return false;
    if (!UzyjAktywnegoDrona().WykonajPoziomyLot(_Lacze))
        return false;
    //while (SprawdzCzyZajete())
    while (UzyjAktywnegoDrona().SprawdzCzyZajeteLista(_Obiekty))
    {
        if (!UzyjAktywnegoDrona().DodajFragmentSciezki())
            return false;
        if (!UzyjAktywnegoDrona().WykonajKrotkiPoziomyLot(_Lacze))
            return false;
    }
    if (!UzyjAktywnegoDrona().WykonajPionowyLot(-LOT_PIONOWY, _Lacze))
        return false;
    std::cout << "\nDron wyladowal ...\n";
    UzyjAktywnegoDrona().UsunSciezke(_Lacze);
    return true;
}

void Scena::WybierzDrona()
{
    int idx;
    std::cout << "Wybor aktywnego drona\n\n";
    WyswietlPolozenie();
    std::cout << "\nWprowadz numer aktywnego drona> ";
    std::cin >> idx;
    while (!(idx == 1 || idx == 2) || cin.fail())
    {
        std::cerr << "\nWprowadzono niepoprawny numer!\n";
        std::cout << "\nWprowadz numer aktywnego drona> ";
        cin.clear();
        cin.ignore(9999, '\n');
        std::cin >> idx;
    }
    _AktDron = idx - 1;
    WyswietlAktPolozenie();
    Wektor3D::WyswietlIlosc();
}

void Scena::WczytajDaneElementu(Wektor3D &Skala, Wektor3D &Polozenie) const
{
    double OX, OY, OZ, wspX, wspY;
    std::cout << "Podaj skale wzdlux kolejnych osi OX, OY, OZ\n";
    std::cout << "Wprowadz skale: OX OY OZ> ";
    std::cin >> OX >> OY >> OZ;
    while (std::cin.fail() || OX < 0 || OY < 0 || OZ < 0)
    {
        std::cerr << "\nWprowadzono niepoprawna wartosc skali\n";
        std::cout << "\nWprowadz skale: OX OY OZ> ";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin >> OX >> OY >> OZ;
    }
    Wektor3D tmp{OX, OY, OZ};
    std::cout << "\nPodaj wspolrzedne srodka podstawy x, y.";
    std::cout << "\nWprowadz wspolrzedne: x y> ";
    std::cin >> wspX >> wspY;
    while (std::cin.fail())
    {
        std::cerr << "\nWprowadzono niepoprawna wartosc wspolrzednych\n";
        std::cout << "\nWprowadz wspolrzedne: x y> ";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin >> wspX >> wspY;
    }
    Wektor3D temp{wspX, wspY, 0};
    Skala = tmp;
    Polozenie = temp;
}

int Scena::WybierzElement() const
{
    int wyb;
    std::cout << "\nWybierz rodzaj powierzchniowego elementu\n";
    std::cout << "\n 1 - Gora z ostrym szczytem";
    std::cout << "\n 2 - Gora z grania";
    std::cout << "\n 3 - Plaskowyz\n";
    std::cout << "\n Wprowadz numer typu elementu> ";
    std::cin >> wyb;
    while (std::cin.fail() || !(wyb == 1 || wyb == 2 || wyb == 3))
    {
        std::cerr << "\nWprowadzono niepoprawny numer";
        std::cout << "\nWybierz rodzaj powierzchniowego elementu\n";
        std::cout << "\n 1 - Gora z ostrym szczytem";
        std::cout << "\n 2 - Gora z grania";
        std::cout << "\n 3 - Plaskowyz\n";
        std::cout << "\n Wprowadz numer typu elementu> ";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin >> wyb;
    }
    return wyb;
}

int Scena::WyswietlElementy()
{
    int nr = 0;
    for (std::list<shared_ptr<ElemPow>>::iterator it = _Elementy.begin();
         it != _Elementy.end(); ++it)
    {
        if (nr == 0)
            ++nr;
        std::cout << nr << " - ";
        (*it)->WypiszElement();
        std::cout << endl;
        ++nr;
    }
    return nr;
}

bool Scena::DodajElement()
{
    int wyb = WybierzElement();
    Wektor3D Skala, Polozenie;
    WczytajDaneElementu(Skala, Polozenie);
    if (wyb == 1)
    {
        _Elementy.emplace_back(new Gora_z_Ostr(Skala, Polozenie));
        _Obiekty.emplace_back(new Gora_z_Ostr(Skala, Polozenie));
    }
    else if (wyb == 2)
    {
        _Elementy.emplace_back(new Gora_z_Dl_Grania(Skala, Polozenie));
        _Obiekty.emplace_back(new Gora_z_Dl_Grania(Skala, Polozenie));
    }
    else if (wyb == 3)
    {
        _Elementy.emplace_back(new Plaskowyz(Skala, Polozenie));
        _Obiekty.emplace_back(new Plaskowyz(Skala, Polozenie));
    }
    if (!_Elementy.back()->Oblicz_i_Zapisz_WspGlbElementu())
        return false;
    _Lacze.DodajNazwePliku(_Elementy.back()->WezNazwePliku_BrylaFinalna().c_str());
    _Lacze.Rysuj();
    return true;
}

void Scena::UsunElement()
{
    int Nr = 1;
    int NrOb = -1;
    int NrElem;
    int Max = WyswietlElementy();
    if (Max > 0)
    {
        std::cout << "\n\nPodaj numer elementu> ";
        std::cin >> NrElem;
        while (std::cin.fail() || NrElem >= Max)
        {
            std::cerr << "\nWprowadzono niepoprawny numer";
            std::cout << "\nPodaj numer elementu> ";
            std::cin.clear();
            std::cin.ignore(9999, '\n');
            std::cin >> NrElem;
        }
        for (std::list<shared_ptr<ElemPow>>::iterator it = _Elementy.begin();
             it != _Elementy.end(); ++it)
        {
            if (Nr == NrElem)
            {
                _Lacze.UsunNazwePliku((*it)->WezNazwePliku_BrylaFinalna().c_str());
                it = _Elementy.erase(it);
            }
            ++Nr;
        }
        for (std::list<shared_ptr<ObiektSc>>::iterator it = _Obiekty.begin();
             it != _Obiekty.end(); ++it)
        {
            if (NrOb == NrElem)
                it = _Obiekty.erase(it);
            ++NrOb;
        }
        _Lacze.Rysuj();
    }
    else
        std::cerr << "\nScena nie zawiera Elementow\n";
}

bool Scena::SprawdzCzyZajete()
{
    int licz = 0;
    for (const std::shared_ptr<ObiektSc> &i : _Obiekty)
        if (i->SprawdzCzyZajete(&UzyjAktywnegoDrona()))
        {
            ++licz;
            if (licz > 1)
                i->DajNazwe();
        }
    return licz >= 2;
}