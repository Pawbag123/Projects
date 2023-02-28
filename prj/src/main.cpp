/**
 * @file main.cpp
 * @author Paweł Bagiński
 * @brief Główny plik programu
 * @version 1.0
 * @date 2021-05-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "lacze_do_gnuplota.hh"
#include "Scena.hh"

using namespace std;

int Gora_z_Ostr::_Nr_Gory_z_Ostr = 0;

int Gora_z_Dl_Grania::_Nr_Gory_z_Dl_Grania = 0;

int Plaskowyz::_Nr_Plaskowyzu = 0;

int ElemPow::_IlElem = 0;

int Scena::_AktDron = 0;

int Dron::NrDrona = 0;

int main()
{
  char wyb;
  Wektor3D Wek1{POZYCJA_STARTOWA_1};
  Wektor3D Wek2{POZYCJA_STARTOWA_2};
  Scena Sc(Wek1, 0, Wek2, 90);

  Sc.InicjalizujScene();
  Sc.InicjalizujLacze();

  Sc.WyswietlAktPolozenie();
  cout << endl
       << "a - wybierz aktywnego drona\n";
  cout << "p - zadaj parametry przelotu\n";
  cout << "d - dodaj element powierzchni\n";
  cout << "u - usun element powierzchni\n";
  cout << "m - wyswietl menu\n";
  cout << "\nk - koniec dzialania programu\n";

  while (wyb != 'k')
  {
    cout << "\nTwoj wybor: ";
    cin >> wyb;

    switch (wyb)
    {
    case 'a':
      Sc.WybierzDrona();
      break;

    case 'p':
      if (!Sc.LotDrona())
        cerr << "Blad, Lot nie zostal wykonany!\n";
      Sc.WyswietlAktPolozenie();
      cout << endl;
      Wektor3D::WyswietlIlosc();
      break;

    case 'm':
      Sc.WyswietlAktPolozenie();
      cout << endl
           << "a - wybierz aktywnego drona\n";
      cout << "p - zadaj parametry przelotu\n";
      cout << "d - dodaj element powierzchni\n";
      cout << "u - usun element powierzchni\n";
      cout << "m - wyswietl menu\n";
      cout << "\nk - koniec dzialania programu\n";
      break;

    case 'd':
      if (!Sc.DodajElement())
        cerr << "Blad, dodanie elementu nie powiodlo sie!\n";
      break;

    case 'u':
      Sc.UsunElement();
      break;

    case 'k':
      cout << "\nKoniec dzialania programu Dragonfly\n";
      break;

    default:
      cout << "\nBlad, podano niepoprawna opcje, sprobuj ponownie\n";
      break;
    }
  }
  return 0;
}
