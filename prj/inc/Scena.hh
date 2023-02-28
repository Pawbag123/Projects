#ifndef SCENA_HH
#define SCENA_HH

#include "Dron.hh"
#include "Gora_z_Ostr.hh"
#include "Gora_z_Dl_Grania.hh"
#include "Plaskowyz.hh"
/**
 * @file Scena.hh
 * @brief Plik zawierający definicję klasy Scena
 * 
 */

/**
 * @brief Klasa modeluje pojęcie Sceny
 * 
 */
class Scena
{
    /**
     * @brief Lista zawierająca wskaźniki na obiekty typu Dron
     * 
     */
    std::list<shared_ptr<Dron>> _ListaDronow;

    /**
     * @brief Obiekt typu LaczeDoGNUPlota
     * 
     */
    PzG::LaczeDoGNUPlota _Lacze;

    /**
     * @brief Obiekt typu SpisPlikow zawierajacy nazwy plikow
     * 
     */
    SpisPlikow _Pliki;

    /**
     * @brief Lista zawierająca wskaźniki współdzielone na elementy powierzchni
     * 
     */
    std::list<shared_ptr<ElemPow>> _Elementy;


    /**
     * @brief Lista zawierająca wskaźniki współdzielone na obiekty sceny
     * 
     */
    std::list<shared_ptr<ObiektSc>> _Obiekty;

    /**
     * @brief Zmienna statyczna służąca do wybrania aktywnego drona
     * 
     */
    static int _AktDron;

    /**
     * @brief Metoda umieszczająca nazwy plików obu dronów w obiekcie SpisPlikow
     * 
     */
    void UmiescNazwyPlikow()
    {
        for (const std::shared_ptr<Dron> &i : _ListaDronow)
            i->DodajNazwyPlikow(_Pliki);
    }

    /**
     * @brief Metoda pozwalająca na użycie aktywnego drona
     * 
     * @return Dron& - Aktywny dron
     */
    Dron &UzyjAktywnegoDrona()
    { 
        if (_AktDron == 0)
            return *_ListaDronow.front();
        else
            return *_ListaDronow.back();
    }

    /**
     * @brief Metoda wyświetlająca aktualne położenie dronóœ
     * 
     */
    void WyswietlPolozenie();

    /**
     * @brief Metoda dodająca nazwy plików do łącza
     * 
     */
    void DodajNazwyPlikow();

    /**
     * @brief Metoda wczytująca dane elementu, który ma zostać stworzony
     * 
     * @param Skala - Wektor3D przechowujący skalę elementu
     * @param Polozenie - Wektor3D przechowujący położenie elementu
     */
    void WczytajDaneElementu(Wektor3D &Skala, Wektor3D &Polozenie) const;

    /**
     * @brief Metoda pozwalająca na wybranie rodzaju tworzonego elementu
     * 
     * @return int - zmienna odpowiadająca za numer elementu
     */
    int WybierzElement() const;

    /**
     * @brief Metoda pozwalająca na wyświetlenie elementów wraz z ich współrzędnymi
     * 
     * @return int - Ilość istniejących elementów
     */
    int WyswietlElementy();


    /**
     * @brief Metoda sprawdzajaca czy miejsce lądowania drona jest już zajęte
     * 
     * @return true - gdy jest zajęte
     * @return false - w wypadku przeciwnym
     */
    bool SprawdzCzyZajete();

public:
    /**
     * @brief Konstruktor Sceny
     * 
     * @param Polozenie1 - Położenie pierwszego drona
     * @param KatObrotu1 - kąt obrotu pierwszego drona
     * @param Polozenie2 - Położenie drugiego drona
     * @param KatObrotu2 - kąt obrotu drugiego drona
     */
    Scena(const Wektor3D &Polozenie1,
          const double KatObrotu1,
          const Wektor3D &Polozenie2,
          const double KatObrotu2);

    /**
     * @brief Metoda pozwalająca na wybranie aktywnego drona
     * 
     */
    void WybierzDrona();

    /**
     * @brief Metoda pozwalająca na wyświetlenie położenia aktywnego drona
     * 
     */
    void WyswietlAktPolozenie();

    /**
     * @brief Metoda inicjalizująca scenę
     * 
     * Metoda ma na celu zapisanie współrzędnych początkowych dronów do układu globalnego
     * 
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli nastąpi problem z otwarciem plików
     */
    bool InicjalizujScene();

    /**
     * @brief Metoda inicjalizująca łącze
     * 
     * Metoda ma na celu skonfigurowanie łącza oraz narysowanie początkowej pozycji dronóœ
     * 
     */
    void InicjalizujLacze();

    /**
     * @brief Metoda pozwalająca na lot drona
     * 
     * Metoda ma na celu wykonanie operacji związanych z lotem drona, tj. pobranie
     * odpowiednich parametrów, narysowanie ścieżki, a następnie lot pionowy,
     * obrót, lot poziomy, oraz opadanie.
     * 
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli nastąpi problem z otwarciem plików
     */
    bool LotDrona();

    /**
     * @brief Metoda, której zadaniem jest dodanie elementu powierzchni
     * 
     * Metoda ma na celu wykonanie operacji związanych z utworzeniem elementu, tj. pobranie od
     * użytkownika danych na temat elementu, a następnie utworzenie go, umieszczenie na końcu
     * listy oraz dodanie jego pliku do łącza
     * 
     * @return true - Gdy operacja się powiedzie
     * @return false - Gdy nastąpi problem z otwarciem plików
     */
    bool DodajElement();

    /**
     * @brief Metoda, której zadaniem jest usunięcie elementu powierzchni
     * 
     * Metoda ma na celu wykonanie operacji związanych z usunięciem elementu, tj. 
     * pobranie od użytkownika numeru elementu, który ma zostać usunięty,
     * usunięcie go z listy, oraz usunięcie jego pliku z łącza
     * 
     */
    void UsunElement();

    /**
     * @brief Metoda wyswietlajaca nazwy obiektów znajdujących się na liście
     * 
     */
    void WyswietlNazwy()
    {
        for (const std::shared_ptr<ObiektSc> &i : _Obiekty)
        i->DajNazwe();    
    }

};

#endif