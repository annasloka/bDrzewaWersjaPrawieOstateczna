#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

void liscieDrzewa(wezel* korzen,potomkowie*&listaLisci_pHead)
{

	potomkowie* kopiaPotom = korzen->pHeadPotom;
	potomkowie* listaLisci = listaLisci_pHead;
	
	while (kopiaPotom)
	{
		if (kopiaPotom->wezelPotomny)
		if (kopiaPotom->wezelPotomny->pHeadPotom->wezelPotomny)
			liscieDrzewa(kopiaPotom->wezelPotomny, listaLisci_pHead);

		else
		{
			if (!listaLisci)
			{
				listaLisci = new potomkowie{ kopiaPotom->wezelPotomny,nullptr };
				listaLisci_pHead = listaLisci;
			}
			else
			{
				while (listaLisci->pNext)
					listaLisci = listaLisci->pNext;

				listaLisci->pNext = new potomkowie{ kopiaPotom->wezelPotomny,nullptr };

			}

			
			//listaLisci = listaLisci->pNext;
		}
		kopiaPotom = kopiaPotom->pNext;
	}
}
void insert2(wezel*&rodzic, wezel*&node)
{
	if (!node->pHeadKluczy)
	{
		deletePotom(node->pHeadPotom);

		node->gdzieJestWsk->wezelPotomny = nullptr;

		delete node;
		node = nullptr;
	}
	else
	{

		klucz* kluczPoprz = node->kluczPoprz;
		potomkowie* kopiaPotom = rodzic->pHeadPotom;
		klucz* kluczKoniec = nullptr;
		potomkowie* potomekKoniec = node->gdzieJestWsk->pNext;


		if (!kluczPoprz)
		{
			kluczKoniec = rodzic->pHeadKluczy;
			rodzic->pHeadKluczy = node->pHeadKluczy;
			kluczPoprz = rodzic->pHeadKluczy;
		}
		else
		{
			kluczKoniec = kluczPoprz->pNext;

			kluczPoprz->pNext = node->pHeadKluczy;
		}


		if (kopiaPotom == node->gdzieJestWsk)
		{
			rodzic->pHeadPotom = node->pHeadPotom;
			kopiaPotom = node->pHeadPotom;
		}
		else
		{
			while (kopiaPotom->pNext != node->gdzieJestWsk)
			{
				kopiaPotom = kopiaPotom->pNext;
			}
			kopiaPotom->pNext = node->pHeadPotom;
		}


		kopiaPotom = kopiaPotom->pNext;

		while (kluczPoprz->pNext)
		{
			kluczPoprz = kluczPoprz->pNext;
			kopiaPotom = kopiaPotom->pNext;
		}
		 kluczPoprz->pNext = kluczKoniec;
		 kopiaPotom->pNext = potomekKoniec;

		delete node->gdzieJestWsk;
		rodzic->zapelnienie = rodzic->zapelnienie + node->zapelnienie;

	}
}
void zmniejszenie_poziomu(wezel*&korzen, int rzad)
{
	//stworzenie listy lisci drzewa, oraz zapisanie pocz�tku listy do zmiennej listaLisci_pHead
	potomkowie* listaLisci = nullptr;
	potomkowie* listaLisci_pHead = nullptr;

	liscieDrzewa(korzen, listaLisci);
	listaLisci_pHead = listaLisci;
	while (listaLisci)
	{
		//funkcja wstaw wezel do rodzica i ewnetualnie potem dzieli i wstawia dalej
		//pr�ba, czy funkcje dzia�aj�
		wezel* rodzic = listaLisci->wezelPotomny->rodzic;

		insert2(listaLisci->wezelPotomny->rodzic, listaLisci->wezelPotomny);

		

		if (rodzic->zapelnienie > 2*rzad - 1)
		{
			podzial dzielenieWezla = divide(rodzic, rzad);

			if (rodzic->rodzic)
				korzen = insert(rodzic->rodzic, rodzic->kluczPoprz, rodzic->gdzieJestWsk, dzielenieWezla.wartosc, dzielenieWezla.lewy, rzad);

			else
				korzen = createNewTree(korzen, dzielenieWezla.wartosc, dzielenieWezla.lewy);
		}

		//usuwanie wez�a - o ile nie zosta� usuni�ty wcze�niej
		if (listaLisci->wezelPotomny)
		{


			delete listaLisci->wezelPotomny;
			listaLisci->wezelPotomny = nullptr;
		}
		listaLisci = listaLisci->pNext;
	}

	deletePotom(listaLisci_pHead);

}
void usuwanie_z_liscia(wezel*&korzen, wezel* lisc, klucz*& kluczDoUsuniecia, potomkowie*& potomDoUsuniecia, int rzad)
{
	///Funkcja ma za zadanie usuni�cie danego klucza z li�cia.

	if (kluczDoUsuniecia == lisc->pHeadKluczy)
	{
		//usuwanie z poczatku listy
		lisc->pHeadKluczy = lisc->pHeadKluczy->pNext;

		delete kluczDoUsuniecia;
		kluczDoUsuniecia = nullptr;

		if (lisc->zapelnienie == 1) lisc->pHeadKluczy = nullptr;

		delete lisc->pHeadPotom;
		lisc->pHeadPotom = potomDoUsuniecia;
	}
	else
	{
		//skopiowanie warto�ci usuwanych wska�nik�w
		klucz* kopiaKlucza = lisc->pHeadKluczy;
		potomkowie* kopiaPotom = lisc->pHeadPotom;

		//szukanie klucza poprzedzaj�cego klucz do usuni�cia
		while (kopiaKlucza->pNext->wartosc != kluczDoUsuniecia->wartosc)
		{
			kopiaKlucza = kopiaKlucza->pNext;
		}

		//pomini�cie w li�cie kluczy klucza do usuni�cia
		kopiaKlucza->pNext = kopiaKlucza->pNext->pNext;

		//usuni�cie klucza do usuni�cia
		delete kluczDoUsuniecia;
		kluczDoUsuniecia = nullptr;

		//usuni�cie jednego z potomk�w
		lisc->pHeadPotom = lisc->pHeadPotom->pNext;
		delete kopiaPotom;
		kopiaPotom = nullptr;
	}

	lisc->zapelnienie--;
	if (lisc->zapelnienie < rzad - 1)
	{
		zmniejszenie_poziomu(korzen, rzad);
	}

}







void kompensacja(wezel*&korzen, wezel* node, klucz* kluczDoZmiany, potomkowie* potomekPoKluczu, int rzad)
{
	wezel* lisc = potomekPoKluczu->wezelPotomny;

	while (lisc->pHeadPotom->wezelPotomny)
	{
		lisc = lisc->pHeadPotom->wezelPotomny;
	}
	//zamiana wartosci
	kluczDoZmiany->wartosc = lisc->pHeadKluczy->wartosc;

	//usuni�cie pierwszego elementu w li�ciu
	klucz* kluczDoUsuniecia = lisc->pHeadKluczy;
	lisc->pHeadKluczy = lisc->pHeadKluczy->pNext;
	delete kluczDoUsuniecia;

	potomkowie* potomDoUsuniecia = lisc->pHeadPotom;
	lisc->pHeadPotom = lisc->pHeadPotom->pNext;
	delete potomDoUsuniecia;
	 


	lisc->zapelnienie--;


	if (lisc->zapelnienie < rzad - 1)
	{
		zmniejszenie_poziomu(korzen,rzad);
	}
}





wezel* remove(wezel*korzen, double wartosc, int rzad)
{
	if (korzen)
	{
		searchResult wynikWysz = { nullptr, nullptr, nullptr };

		search(korzen, wartosc, wynikWysz);

		klucz* kluczDoUsuniecia = wynikWysz.kluczPoprz;
		potomkowie* potomekPoKluczu = wynikWysz.potomPoprz;
		/*if ((!korzen->pHeadKluczy->pNext) && (kluczDoUsuniecia->wartosc == wartosc))
		{
			deleteBTree(korzen);
			korzen = nullptr;
		}
		else*/ if ((kluczDoUsuniecia) && (kluczDoUsuniecia->wartosc == wartosc))
		{
			//w przypadku, gdy warto�� do usuni�cia znajduje si� w li�ciu, zostanie ona usuni�ta i nast�pi sprawdzenie, czy li�� nie ma zbyt ma�ego zape�nienia
			//je�li ma zbyt ma�e zape�nienie, nast�pi po��czenie

			if (wynikWysz.wezelMiejsca->pHeadPotom->wezelPotomny == nullptr)
			{
				//funkcja usuwaj�ca klucz z li�cia
				usuwanie_z_liscia(korzen, wynikWysz.wezelMiejsca, kluczDoUsuniecia, potomekPoKluczu,rzad);

			}
			else
			{
				
				kompensacja(korzen, wynikWysz.wezelMiejsca, kluczDoUsuniecia, potomekPoKluczu, rzad);
				//graph(korzen, 0);
			}
			
		}
		
		
	}
	if (!korzen->pHeadKluczy)
	{
		deletePotom(korzen->pHeadPotom);
		delete korzen;
		korzen = nullptr;
	}
	return korzen;
}
