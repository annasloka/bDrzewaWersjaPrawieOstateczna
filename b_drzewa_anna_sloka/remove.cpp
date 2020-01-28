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
	//stworzenie listy lisci drzewa, oraz zapisanie pocz¹tku listy do zmiennej listaLisci_pHead
	potomkowie* listaLisci = nullptr;
	potomkowie* listaLisci_pHead = nullptr;

	liscieDrzewa(korzen, listaLisci);
	listaLisci_pHead = listaLisci;
	while (listaLisci)
	{
		//funkcja wstaw wezel do rodzica i ewnetualnie potem dzieli i wstawia dalej
		//próba, czy funkcje dzia³aj¹
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

		//usuwanie wez³a - o ile nie zosta³ usuniêty wczeœniej
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
	///Funkcja ma za zadanie usuniêcie danego klucza z liœcia.

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
		//skopiowanie wartoœci usuwanych wskaŸników
		klucz* kopiaKlucza = lisc->pHeadKluczy;
		potomkowie* kopiaPotom = lisc->pHeadPotom;

		//szukanie klucza poprzedzaj¹cego klucz do usuniêcia
		while (kopiaKlucza->pNext->wartosc != kluczDoUsuniecia->wartosc)
		{
			kopiaKlucza = kopiaKlucza->pNext;
		}

		//pominiêcie w liœcie kluczy klucza do usuniêcia
		kopiaKlucza->pNext = kopiaKlucza->pNext->pNext;

		//usuniêcie klucza do usuniêcia
		delete kluczDoUsuniecia;
		kluczDoUsuniecia = nullptr;

		//usuniêcie jednego z potomków
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

	//usuniêcie pierwszego elementu w liœciu
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
			//w przypadku, gdy wartoœæ do usuniêcia znajduje siê w liœciu, zostanie ona usuniêta i nast¹pi sprawdzenie, czy liœæ nie ma zbyt ma³ego zape³nienia
			//jeœli ma zbyt ma³e zape³nienie, nast¹pi po³¹czenie

			if (wynikWysz.wezelMiejsca->pHeadPotom->wezelPotomny == nullptr)
			{
				//funkcja usuwaj¹ca klucz z liœcia
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
