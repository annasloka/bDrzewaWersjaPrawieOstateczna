#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "funkcje.h"
#include "struktury.h"

using namespace std;


void dodajFunkcje(listaFunkcji*& pHead, string funkcja, klucz* dane, string nazwa_pliku, bool czy_plus)
{
	/**Funkcja przyjmuje jako parametry wskaŸnik na pierwszy element listy funkcji, oraz dane wczytanej funkcji.
	Dodaje elementy do listy funkcji podczas wczytywania z pliku wejœciowego. **/
	if (pHead) dodajFunkcje(pHead->pNext, funkcja, dane, nazwa_pliku, czy_plus);
	else pHead = new listaFunkcji{ funkcja,dane,nazwa_pliku,czy_plus,nullptr };
}

void dodajElementDoListy(klucz*& pHead, double liczba)
{
	/**Funkcja przyjmuje pierwszy element listy zawieraj¹cej dane oraz liczbê.
	Jest wykorzystywana podczas wczytywania danych z pliku dla funkcji add i remove.**/
	if (pHead)
		dodajElementDoListy(pHead->pNext, liczba);
	else
	{
		pHead = new klucz{ liczba, nullptr };
	}
}

listaFunkcji* wczytaj_z_pliku(string nazwa_pliku, int& rzad)
{
	/**Funkcja przyjmuje nazwê pliku wejœciowego, oraz rz¹d B-drzewa.
	Jest odpowiedzialna za czytanie danych z pliku wejœciowego dolisty funkcji.**/
	ifstream plik;
	string polecenie;
	string nazwa_pliku_do_zapisu;
	int numerznaku_asci = 0;
	double liczba = 0;
	char znak;
	bool czy_plus = 0;
	klucz* pHead = nullptr;
	listaFunkcji* f = nullptr;
	plik.open(nazwa_pliku);
	if (plik)
	{
		plik >> rzad;
		while (!plik.eof())
		{
			klucz* pHead = nullptr;
			plik >> polecenie;
			if (polecenie == "add")
			{
				while (numerznaku_asci != 10)
				{
					plik >> liczba;
					dodajElementDoListy(pHead, liczba);
					plik.get(znak);
					numerznaku_asci = (int)znak;
				}
				dodajFunkcje(f, "add", pHead, "", 0);
				numerznaku_asci = 0;
			}
			else if (polecenie == "remove")
			{
				while (numerznaku_asci != 10)
				{
					plik >> liczba;
					dodajElementDoListy(pHead, liczba);
					plik.get(znak);
					numerznaku_asci = (int)znak;
				}
				dodajFunkcje(f, "remove", pHead, "", 0);
				numerznaku_asci = 0;
			}
			else if (polecenie == "graph")
			{
				plik.get(znak);
				if (znak == ' ')
				{
					plik >> nazwa_pliku_do_zapisu;
					if (nazwa_pliku_do_zapisu == "+")
					{
						czy_plus = 1;
						plik >> nazwa_pliku_do_zapisu;
					}
					dodajFunkcje(f, "graphToFile", nullptr, nazwa_pliku_do_zapisu, czy_plus);
					czy_plus = 0;
				}
				else if ((int)znak == 10) dodajFunkcje(f, "graph", nullptr, "", 0);
			}
			else if (polecenie == "print")
			{
				plik.get(znak);
				if (znak == ' ')
				{
					plik >> nazwa_pliku_do_zapisu;
					if (nazwa_pliku_do_zapisu == "+")
					{
						czy_plus = 1;
						plik >> nazwa_pliku_do_zapisu;
					}
					dodajFunkcje(f, "printToFile", nullptr, nazwa_pliku_do_zapisu, czy_plus);
					czy_plus = 0;
				}
				else if ((int)znak == 10) dodajFunkcje(f, "print", nullptr, "", 0);
			}
		}
		plik.close();
	}
	else cout << "Nie udalo sie otworzyc pliku!" << endl;
	return f;
}