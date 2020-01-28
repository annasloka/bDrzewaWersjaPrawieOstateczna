#pragma once
#include <iostream>
#include <fstream>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

void deleteListaF(listaFunkcji*& pHead)
{
	/**Funkcja przyjmuje wskaŸnik na pierwszy element listy funkcji, jest odpowiedzialna za jej usuniêcie. **/
	if (pHead)
	{
		deleteListaF(pHead->pNext);
		delete pHead;
		pHead = nullptr;
	}
}
void deleteKlucz(klucz*& pHead)
{
	/**Funkcja przyjmuje wskaŸnik na pierwszy element listy kluczy, jest odpowiedzialna za jej usuniêcie.**/
	if (pHead)
	{
		deleteKlucz(pHead->pNext);
		delete pHead;
		pHead = nullptr;
	}
}
void deletePotom(potomkowie*& pHead)
{
	/**Funkcja przyjmuje wskaŸnik na pierwszy element listy wskaŸników do wêz³ów potomnych, jest odpowiedzialna za jej usuniêcie.**/
	if (pHead)
	{
		deletePotom(pHead->pNext);
		delete pHead;
		pHead = nullptr;
	}
}
void deleteBTree(wezel*& korzen)
{
	/**Funkcja odpowiada za usuniêcie B-drzewa w celu zwolnienia pamiêci.
	Jej parametrem jest wskaŸnik na korzeñ B-drzewa. **/
	klucz* kPrev = nullptr;
	potomkowie* pPrev = nullptr;
	if (korzen)
	{
		while (korzen->pHeadPotom)
		{
			if (korzen->pHeadPotom->wezelPotomny) deleteBTree(korzen->pHeadPotom->wezelPotomny);
			pPrev = korzen->pHeadPotom;
			korzen->pHeadPotom = korzen->pHeadPotom->pNext;
			delete pPrev;
			pPrev = nullptr;
			if (korzen->pHeadKluczy)
			{
				kPrev = korzen->pHeadKluczy;
				korzen->pHeadKluczy = korzen->pHeadKluczy->pNext;
				delete kPrev;
				kPrev = nullptr;
			}
		}
		korzen->kluczPoprz = nullptr;
		korzen->rodzic = nullptr;
		delete korzen;
		korzen = nullptr;
	}
}