#include <iostream>
#include <fstream>
#include <string>
#include "funkcje.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "struktury.h"


using namespace std;

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	string nazwa_pliku = "plik_zrodlowyWiele.txt";
	int rzad = 0;

	listaFunkcji* lista = wczytaj_z_pliku(nazwa_pliku, rzad);
	listaFunkcji* pPrev = nullptr;
	klucz* kPrev = nullptr;
	wezel* korzen = nullptr;
	ofstream plik;
	while (lista)
	{
		while (lista->dane)
		{
			if (lista->funkcja == "add")
			{
				wezel* wskLewy = nullptr;
				add(korzen, lista->dane->wartosc, wskLewy, rzad);
				//pamietac, zeby zmienic na nowy wezel...
			}
			else if ((lista->funkcja == "remove")&&(korzen))
			{

					korzen = remove(korzen, lista->dane->wartosc, rzad);

			}
			kPrev = lista->dane;
			lista->dane = lista->dane->pNext;
			delete kPrev;
			kPrev = nullptr;
		}

		if (korzen)
		{
			if (lista->funkcja == "graphToFile")
			{
				if (lista->czy_plus == 1)
					plik.open(lista->nazwa_pliku, ios::app);
				else
					plik.open(lista->nazwa_pliku, ios::out);

				graphToFile(korzen, 0, plik);

				plik.close();
			}
			else if (lista->funkcja == "printToFile")
			{
				if (lista->czy_plus == 1)
					plik.open(lista->nazwa_pliku, ios::app);
				else
					plik.open(lista->nazwa_pliku, ios::out);

				printToFile(korzen, plik);

				plik.close();
			}
			else if (lista->funkcja == "graph")
			{
				graph(korzen, 0);
			}
			else if (lista->funkcja == "print")
			{
				print(korzen);
			}
		}
		pPrev = lista;
		lista = lista->pNext;
		delete pPrev;
		pPrev = nullptr;
	}
	deleteBTree(korzen);


	return 0;
}
