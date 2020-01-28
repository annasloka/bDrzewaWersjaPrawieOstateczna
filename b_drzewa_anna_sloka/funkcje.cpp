#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

//funkcja do usuniêcia po zakoñczeniu projektu
void drukujListeKluczy(klucz* pHead)
{
	if (pHead)
	{
		cout << pHead->wartosc << endl;
		drukujListeKluczy(pHead->pNext);
	}
}
//funkcja tworz¹ca nowe drzewo
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
		
	
	//na koniec, jak coœ nie zadzia³a, to sprawdziæ, czy na pewno funcja search dobrze dzia³a
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
	//tworzenie nowego wêz³a

	lewy = new wezel{ kopiaKluczy->pNext->pNext,kopiaPotom->pNext,zapelnienieNowegoWezla,nullptr,nullptr,nullptr };

	potomkowie* kopiaPotomLewego = kopiaPotom->pNext;

	node->zapelnienie = node->zapelnienie / 2;

	kopiaPotom->pNext = nullptr;
	delete kopiaKluczy->pNext;
	kopiaKluczy->pNext = nullptr;

	
	//zmiana wskaŸnika na rodzica dla potomków now
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


	//przypisanie rodzica nowemu wêz³owi
	if (node->rodzic)
		lewy->rodzic = node->rodzic;

	return { wartosc, node, lewy };

}
wezel* insert(wezel* node, klucz*& kluczPoprz, potomkowie*& potomPoprz, double wartosc, wezel* lewy, int rzad)
{
	klucz* nowyKlucz = nullptr;

	if (!kluczPoprz)
	{
		//wstawianie nowego klucza na pocz¹tek
		//klucz* copy = node->pHeadKluczy;
		node->pHeadKluczy = new klucz{ wartosc,node->pHeadKluczy };
		nowyKlucz = node->pHeadKluczy;
		//node->pHeadKluczy->pNext = copy;

	}
	else
	{
		//wstawienie nowego klucza wewn¹trz lub na koniec listy
		kluczPoprz->pNext = new klucz{ wartosc, kluczPoprz->pNext };
		nowyKlucz = kluczPoprz->pNext;
	}
	//wstawianie nowego wskaŸnika na wêze³ potomny
	potomPoprz->pNext = new potomkowie{ lewy,potomPoprz->pNext };

	//inkrementacja zape³nienia
	node->zapelnienie++;

	//przypisanie wskaŸników na klucz poprzedni i wskaŸnika na potomka,w którym znajduje siê wêze³, jeœli wêze³ istnieje
	if (lewy)
	{
		lewy->gdzieJestWsk = potomPoprz->pNext;
		lewy->kluczPoprz = nowyKlucz;
	}


	//sprawdzenie, czy nie jest przepe³niony
	if (node->zapelnienie == 2 * rzad)
	{
		//wywo³anie funkcji divide zwracaj¹cej strukturê zawieraj¹c¹ wartoœæ do dodania, oraz dwa wêz³y powsta³e w wyniku podzia³u

		podzial dzielenieWezla = divide(node, rzad);

		if (!node->rodzic)

			return createNewTree(dzielenieWezla.prawy, dzielenieWezla.wartosc, dzielenieWezla.lewy);

		else
		{
			insert(node->rodzic, node->kluczPoprz, node->gdzieJestWsk, dzielenieWezla.wartosc, dzielenieWezla.lewy, rzad);
		}
	}
	else {
		//zwraca wskaŸnik na korzeñ po dodaniu
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
			//w przypadku, gdy wartosc istnieje, nie wykona siê dodawanie
		}
		else
		{
			korzen = insert(wynikWysz.wezelMiejsca, wynikWysz.kluczPoprz, wynikWysz.potomPoprz, wartosc, lewy, rzad);
		}
	}
	return korzen;
}






