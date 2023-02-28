#ifndef DRON_HH
#define DRON_HH

#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"
#include "lacze_do_gnuplota.hh"
#include <unistd.h>
#include "SpisPlikow.hh"
#include "Sciezka.hh"
/**
 * @file Dron.hh
 * @brief Plik zawiera definicję klasy Dron
 * 
 */

/**
 * @brief Klasa modeluje pojęcie drona
 * 
 */
class Dron : public UkladWsp, public ObiektSc
{
    /**
     * @brief Prostopadłościan, który ma posłużyć jako korpus drona
     * 
     */
    Prostopadloscian _KorpusDrona;
    /**
     * @brief Tablica czteroelementowa graniastosłupów, zawierająca rotory drona
     * 
     */
    Graniastoslup _RotorDrona[4];
    /**
     * @brief Zmienna statyczna zawierająca ilość stworzonych Dronów
     * 
     */
    static int NrDrona;
    /**
     * @brief Zmienna typu int przechowująca numer danego drona
     * 
     */
    int _NrDrona;

    /**
     * @brief Obiekt typu ścieżka zawierający nazwy plików, na których pracuje dron
     * 
     */
    Sciezka _SciezkaDrona;

    /**
     * @brief Metoda pozwala na transformacje bryly do Globalnego Ukladu Współrzędnych
     * 
     * Metoda ma na celu Pobranie z pliku bryły wzorcowej każdy wierzchołek,
     * a następnie po kolei odpowiednio go przeskalować, oraz przetransformować
     * jego współrzędne względem drona, oraz względem sceny. Zmodyfikowane
     * w ten sposób elementy zapisuje do pliku finalnego 
     * 
     * @param Plik_We - Plik, z którego ma zostać pobrana bryła wzorcowa
     * @param Plik_Wy - Plik, w którym mają zostać zapisane współrzędne bryły po konwersji
     * @param Br - Wskaźnik na bryłę, pozwala na użycie funkcji zarówno na prostopadłościanach
     * jak i graniastosłupach
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte
     */
    bool TransformujBryle(std::ifstream &Plik_We,
                          std::ofstream &Plik_Wy, const Bryla *Br) const;

    /**
     * @brief Metoda pozwala na transformację korpusu Drona do Globalnego Układu Współrzędnych
     * 
     * 
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte
     */
    bool Oblicz_i_Zapisz_WspGlbKorpusu() const;

    /**
     * @brief Metoda pozwala na transformację rotorów Drona do Globalnego Układu Współrzędnych 
     * 
     * @param Rotor - Rotor, który ma zostać przetransformowany
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    bool Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup &Rotor) const;

    /**
     * @brief Metoda która pozwala na obrót rotorów poprzez dodanie im kąta rotacji
     * 
     */
    void ObrocRotory();

public:
    /**
     * @brief Konstruktor Drona
     * 
     * Konstruktor ten przekazuje podane Położenie oraz Kąt Orientacji do Drona,
     * a także wywołuje konstruktory brył z odpowiednimi, zdefiniowanymi parametrami,
     * takimi jak skala, czy pozycja względem drona. Konstruktor także przypisuje każdej
     * bryle odpowiednią nazwę pliku, a także przyporządkowuje Dronowi jego numer
     * oraz zwiększa licznik dronów
     * 
     * @param Polozenie - Obiekt typu Wektor3D zawierająćy Położenie Drona względem sceny
     * @param KatOrientacji - Liczba typu double zawierająca kąt orientacji drona w stopniach
     */
    Dron(const Wektor3D &Polozenie, const double KatOrientacji);

    /**
     * @brief Metoda transformująca współrzędne Drona do Sceny
     * 
     * Metoda Otwiera pliki brył wzorcowych, transformuje każdą
     * bryłę zawartą w dronie do jego układu współrzędnych, a następnie do 
     * globalnego układu współrzędnych
     * 
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    bool Oblicz_i_Zapisz_WspGlbDrona() const;

    /**
     * @brief Metoda wyświetla aktualne położenie drona, tj. jego współrzędne X, Y
     * 
     */
    void WyswietlPol()
    {
        std::cout << _NrDrona << " - Polozenie (x,y): ";
        WyswietlWsp();
    }

    /**
     * @brief Metoda wyświetla komunikat, że dany dron jest aktywny
     * 
     */
    void WyswietlAkt()
    {
        std::cout << " <--Dron aktywny";
    }

    /**
     * @brief Metoda wykonująca rotację Drona
     * 
     * Metoda ma na celu animację obrotu Drona, w celu przemierzenia ustalonej ścieżki,
     * w tym celu posłuży się metodą UkladWsp::UstalKat, która pozwala zmienić
     * kąt rotacji układu
     * 
     * @param Lacze - Łącze, które posłuży do ukazania rotacji
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte  
     */
    bool WykonajObrot(PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda wykonująca pionowy lot Drona
     * 
     * Metoda ma na celu wykonanie pionowego lotu Drona o zadaną, zdefiniowaną
     * długość lotu. w tym celu posłuży się metodą UkladWsp::Wznies, która
     * pozwala zmienić współrzędną 'Z' Układu
     * 
     * @param DlugoscLotu - Liczba typu double przechowująca wartość długości lotu
     * @param Lacze - Łącze, które posłuży do ukazania lotu
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte
     */
    bool WykonajPionowyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda wykonująca poziomy lot Drona
     * 
     * Metoda ma na celu animację poziomego lotu Drona o zadaną długość,
     * pod zadanym kątem. Dane te, są pobrane z ustalonej wcześniej ścieżki lotu drona.
     * W tym celu posłuży się metodą UkladWsp::Przesun która pozwala na przesunięcie
     * Drona o dane współrzędne X i Y.
     * 
     * @param Lacze - Łącze, które posłuży do ukazania lotu
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    bool WykonajPoziomyLot(PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda planująca oraz rysująca ścieżkę Drona
     * 
     * Metoda ma na celu pobranie od użytkownika kąta rotacji ścieżki oraz jej
     * długość, a następnie na podstawie tych parametrów narysowanie ścieżki
     * w programie GNUPlot przy pomocy łącza
     * 
     * @param Lacze - Łącze, które posłuży do ukazania ścieżki
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    bool PlanujPoczatkowaSciezke(PzG::LaczeDoGNUPlota &Lacze)
    {
        return _SciezkaDrona.NarysujSciezke(Lacze, WezPolozenie(), WezKat());
    }

    /**
     * @brief Metoda , majaca na celu dorysowanie dalszej sciezki drona w wypadku kolizji
     * 
     * @return true - Gdy operacja sie powiedzie
     * @return false - Jeżeli nastąpi problem z otwarciem pliku
     */
    bool DodajFragmentSciezki()
    {
        return _SciezkaDrona.DorysujSciezke();
    }

    /**
     * @brief Metoda przekazujaca polozenie drona w celu dorysowania sciezki
     * 
     */
    void UstalPolSciezka()
    {
        _SciezkaDrona.UstalPolDrona(WezPolozenie());
    }

    /**
     * @brief Metoda usuwająca ścieżkę
     * 
     * Metoda ma na celu usunięcie pliku zawierającego ścieżkę drona z łącza,
     * oraz wyczyszczenie szablonu vector<Wektor3D> zawierającego punkty ścieżki,
     * aby było możliwe ponowne jego zapełnienie
     * 
     * @param Lacze - Łącze, które posłużyło do ukazania ścieżki
     */
    void UsunSciezke(PzG::LaczeDoGNUPlota &Lacze)
    {
        _SciezkaDrona.UsunSciezke(Lacze);
    }

    /**
     * @brief Metoda dodająca nazwy plików finalnych Drona
     *  
     * Metoda ma na celu dodanie do obiektu klasy SpisPlikow nazw 
     * plików finalnych niezbędnych w celu wyświetlenia Drona 
     * w programie GNUPlot
     * 
     * @param Nazwy - Obiekt typu SpisPlikow zawierający nazwy plików
     */
    void DodajNazwyPlikow(SpisPlikow &Nazwy) const
    {
        Nazwy.DodajNazwe(_KorpusDrona.WezNazwePliku_BrylaFinalna());
        for (int i = 0; i < 4; i++)
            Nazwy.DodajNazwe(_RotorDrona[i].WezNazwePliku_BrylaFinalna());
    }

    /**
     * @brief Metoda ustalajaca parametry Drona w celu detekcji kolizji
     * 
     */
    void UstalParametry() override;

    /**
     * @brief Metoda sprawdzajaca czy dron nie koliduje z innym dronem
     * 
     * @param Obiekt - wskaźnik na drona, który ma lądować
     * @return true - gdy miejsce lądowania jest zajęte przez innego drona 
     * @return false - w wypadku przeciwnym
     */
    bool SprawdzCzyZajete(ObiektSc *Obiekt) override;

    /**
     * @brief Metoda umożliwiająca dodatkowy przelot nad przeszkodą
     * 
     * @param Lacze - Lacze, które pozwoli na animacje lotu
     * @return true - Gdy operacja sie powiedzie
     * @return false - W wypadku przeciwnym
     */
    bool WykonajKrotkiPoziomyLot(PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda wypisujaca nazwe obiektu klasy kolidującej z dronem
     * 
     */
    void DajNazwe() override
    {
        std::cout << "\n:( Ladowisko niedostepne!\n";
        std::cout << ":( Wykryto element powierzchni typu: Dron\n";
    }

    /**
     * @brief Metoda sprawdzajaca czy zaden z obiektow nie lezy na terenie ladowiska drona
     * 
     * @param ListaObiektow - Lista wspoldzielonych wskaznikow na obiekty sceny
     * @return true - jezeli nastapi kolizja
     * @return false - w wypadku przeciwnym
     */
    bool SprawdzCzyZajeteLista(const std::list<shared_ptr<ObiektSc>> &ListaObiektow);
};

#endif