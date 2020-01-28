#pragma once
#include <iostream>
#include <fstream>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

void deleteListaF(listaFunkcji*& pHead)
{
	/**Funkcja przyjmuje wska�nik na pierwszy element listy funkcji, jest odpowiedzialna za jej usuni�cie. **/
	if (pHead)
	{
		deleteListaF(pHead->pNext);
		delete pHead;
		pHead = nullptr;
	}
}
void deleteKlucz(klucz*& pHead)
{
	/**Funkcja przyjmuje wska�nik na pierwszy element listy kluczy, jest odpowiedzialna za jej usuni�cie.**/
	if (pHead)
	{
		deleteKlucz(pHead->pNext);
		delete pHead;
		pHead = nullptr;
	}
}
void deletePotom(potomkowie*& pHead)
{
	/**Funkcja przyjmuje wska�nik na pierwszy element listy wska�nik�w do w�z��w potomnych, jest odpowiedzialna za jej usuni�cie.**/
	if (pHead)
	{
		deletePotom(pHead->pNext);
		delete pHead;
		pHead = nullptr;
	}
}
void deleteBTree(wezel*& korzen)
{
	/**Funkcja odpowiada za usuni�cie B-drzewa w celu zwolnienia pami�ci.
	Jej parametrem jest wska�nik na korze� B-drzewa. **/
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