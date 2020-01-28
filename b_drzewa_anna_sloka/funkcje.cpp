#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

//funkcja do usuni�cia po zako�czeniu projektu
void drukujListeKluczy(klucz* pHead)
{
	if (pHead)
	{
		cout << pHead->wartosc << endl;
		drukujListeKluczy(pHead->pNext);
	}
}
//funkcja tworz�ca nowe drzewo
wezel* createNewTree(wezel* korzen, double wartosc, wezel* lewy)
{
	wezel* nowy_korzen = nullptr;

	klucz* nowyKlucz = new klucz{ wartosc,nullptr };

	potomkowie* nowaListaPotomkow = new potomkowie{ korzen,nullptr };
	nowaListaPotomkow->pNext = new potomkowie{ lewy,nullptr };


	nowy_korzen = new wezel{ nowyKlucz,nowaListaPotomkow,1,nullptr,nullptr,nullptr };


	if (nowaListaPotomkow->wezelPotomny)
	{
		nowaListaPotomkow->wezelPotomny->kluczPoprz = nullptr;
		nowaListaPotomkow->pNext->wezelPotomny->kluczPoprz = nowyKlucz;

		nowaListaPotomkow->wezelPotomny->rodzic = nowy_korzen;
		nowaListaPotomkow->pNext->wezelPotomny->rodzic = nowy_korzen;

		nowaListaPotomkow->wezelPotomny->gdzieJestWsk = nowaListaPotomkow;
		nowaListaPotomkow->pNext->wezelPotomny->gdzieJestWsk = nowaListaPotomkow->pNext;
	}
	return nowy_korzen;
}

void search(wezel* korzen, double wartosc, searchResult& wynik)
{
	klucz* kopiaKluczy = korzen->pHeadKluczy;
	potomkowie* kopiaPotom = korzen->pHeadPotom;
	//najpierw w danym wezle wyszukuje

	 if (wartosc < kopiaKluczy->wartosc)
	{
		kopiaKluczy = nullptr;
	}
	else
	{
		kopiaPotom = kopiaPotom->pNext;
		//a teraz wykonuje sie przeszukiwanie w wezle, klucz jest jest przesuwany
		while ((kopiaKluczy->pNext) && (wartosc >= kopiaKluczy->pNext->wartosc))
		{
			kopiaKluczy = kopiaKluczy->pNext;
			kopiaPotom = kopiaPotom->pNext;
		}
	}
	
		if (
				(kopiaPotom->wezelPotomny)

				&&
			
				((!kopiaKluczy)||(wartosc!=kopiaKluczy->wartosc))
			)
			search(kopiaPotom->wezelPotomny, wartosc, wynik);

		else
		{
			wynik.wezelMiejsca = korzen;
			wynik.kluczPoprz = kopiaKluczy;
			wynik.potomPoprz = kopiaPotom;
		}
		
	
	//na koniec, jak co� nie zadzia�a, to sprawdzi�, czy na pewno funcja search dobrze dzia�a
}
void redukcja_poziomu()
{

}
podzial divide(wezel*& node, int rzad)
{
	double wartosc = 0;
	int zapelnienieNowegoWezla = 0;

	klucz* kopiaKluczy = node->pHeadKluczy;

	potomkowie* kopiaPotom = node->pHeadPotom->pNext;

	wezel* lewy = nullptr;

	for (int i = 1; i < node->zapelnienie / 2; i++)
	{
		kopiaKluczy = kopiaKluczy->pNext;
		kopiaPotom = kopiaPotom->pNext;
	}
	wartosc = kopiaKluczy->pNext->wartosc;

	//zapelnienie nowego wezla
	if (node->zapelnienie % 2 == 0)
		zapelnienieNowegoWezla = node->zapelnienie / 2 - 1;
	else
		zapelnienieNowegoWezla = node->zapelnienie / 2;
	//tworzenie nowego w�z�a

	lewy = new wezel{ kopiaKluczy->pNext->pNext,kopiaPotom->pNext,zapelnienieNowegoWezla,nullptr,nullptr,nullptr };

	potomkowie* kopiaPotomLewego = kopiaPotom->pNext;

	node->zapelnienie = node->zapelnienie / 2;

	kopiaPotom->pNext = nullptr;
	delete kopiaKluczy->pNext;
	kopiaKluczy->pNext = nullptr;

	
	//zmiana wska�nika na rodzica dla potomk�w now
	if (kopiaPotomLewego->wezelPotomny)
		kopiaPotomLewego->wezelPotomny->kluczPoprz = nullptr;

	while (kopiaPotomLewego)
	{
		if (kopiaPotomLewego->wezelPotomny)
		{
			
			kopiaPotomLewego->wezelPotomny->rodzic = lewy;

		}
		kopiaPotomLewego = kopiaPotomLewego->pNext;
	}


	//przypisanie rodzica nowemu w�z�owi
	if (node->rodzic)
		lewy->rodzic = node->rodzic;

	return { wartosc, node, lewy };

}
wezel* insert(wezel* node, klucz*& kluczPoprz, potomkowie*& potomPoprz, double wartosc, wezel* lewy, int rzad)
{
	klucz* nowyKlucz = nullptr;

	if (!kluczPoprz)
	{
		//wstawianie nowego klucza na pocz�tek
		//klucz* copy = node->pHeadKluczy;
		node->pHeadKluczy = new klucz{ wartosc,node->pHeadKluczy };
		nowyKlucz = node->pHeadKluczy;
		//node->pHeadKluczy->pNext = copy;

	}
	else
	{
		//wstawienie nowego klucza wewn�trz lub na koniec listy
		kluczPoprz->pNext = new klucz{ wartosc, kluczPoprz->pNext };
		nowyKlucz = kluczPoprz->pNext;
	}
	//wstawianie nowego wska�nika na w�ze� potomny
	potomPoprz->pNext = new potomkowie{ lewy,potomPoprz->pNext };

	//inkrementacja zape�nienia
	node->zapelnienie++;

	//przypisanie wska�nik�w na klucz poprzedni i wska�nika na potomka,w kt�rym znajduje si� w�ze�, je�li w�ze� istnieje
	if (lewy)
	{
		lewy->gdzieJestWsk = potomPoprz->pNext;
		lewy->kluczPoprz = nowyKlucz;
	}


	//sprawdzenie, czy nie jest przepe�niony
	if (node->zapelnienie == 2 * rzad)
	{
		//wywo�anie funkcji divide zwracaj�cej struktur� zawieraj�c� warto�� do dodania, oraz dwa w�z�y powsta�e w wyniku podzia�u

		podzial dzielenieWezla = divide(node, rzad);

		if (!node->rodzic)

			return createNewTree(dzielenieWezla.prawy, dzielenieWezla.wartosc, dzielenieWezla.lewy);

		else
		{
			insert(node->rodzic, node->kluczPoprz, node->gdzieJestWsk, dzielenieWezla.wartosc, dzielenieWezla.lewy, rzad);
		}
	}
	else {
		//zwraca wska�nik na korze� po dodaniu
		wezel* kNode = node;
		while (kNode->rodzic)
		{
			kNode = kNode->rodzic;
		}
		return kNode;
	}
}
wezel* add(wezel*& korzen, double wartosc, wezel*& lewy, int rzad)
{
	if (!korzen)
	{
		korzen = createNewTree(korzen, wartosc, lewy);
	}
	else if (!lewy)
	{
		searchResult wynikWysz = { nullptr,nullptr, nullptr };

		search(korzen, wartosc, wynikWysz);

		if ((wynikWysz.kluczPoprz) && (wynikWysz.kluczPoprz->wartosc == wartosc))
		{
			//w przypadku, gdy wartosc istnieje, nie wykona si� dodawanie
		}
		else
		{
			korzen = insert(wynikWysz.wezelMiejsca, wynikWysz.kluczPoprz, wynikWysz.potomPoprz, wartosc, lewy, rzad);
		}
	}
	return korzen;
}






