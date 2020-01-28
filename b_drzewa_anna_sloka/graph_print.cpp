#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

potomkowie* reverse(potomkowie* pHead)
{
	potomkowie* newElement = nullptr;
	while (pHead)
	{
		newElement = new potomkowie{ pHead->wezelPotomny,newElement };
		pHead = pHead->pNext;
	}
	pHead = newElement;
	newElement = nullptr;
	return pHead;
}
klucz* reverse2(klucz* pHead)
{
	klucz* newElement = nullptr;
	while (pHead)
	{
		newElement = new klucz{ pHead->wartosc,newElement };
		pHead = pHead->pNext;
	}
	pHead = newElement;
	newElement = nullptr;
	return pHead;
}
void graph(wezel* korzen, int wciecie)
{
	//tutaj dorobi� to wy�wietlanie nawias�w kwadratowych i do tego drukowa� B-drzewo od ty�u
	klucz* kopiaKluczy = reverse2(korzen->pHeadKluczy);
	potomkowie* kopiaPotom = reverse(korzen->pHeadPotom);

	//stworzenie kopii wska�nik�w na pocz�tek odwr�conych list w celu usuni�cia na ko�cu
	klucz* kopiaKluczy2 = kopiaKluczy;
	potomkowie* kopiaPotom2 = kopiaPotom;
	while (kopiaPotom)
	{
		if (kopiaPotom->wezelPotomny)

			graph(kopiaPotom->wezelPotomny, wciecie + 12);

		if (kopiaKluczy)
		{
			cout << setw(wciecie);

			if (!kopiaKluczy->pNext) cout << "[";

			cout << kopiaKluczy->wartosc;

			if (kopiaKluczy == kopiaKluczy2) cout << "]";

		}
		kopiaPotom = kopiaPotom->pNext;
		cout << endl;
		if (kopiaKluczy) kopiaKluczy = kopiaKluczy->pNext;
	}
	deleteKlucz(kopiaKluczy2);
	deletePotom(kopiaPotom2);

}
void graphToFile(wezel* korzen, int wciecie, ofstream&plik)
{
	//tutaj dorobi� to wy�wietlanie nawias�w kwadratowych i do tego drukowa� B-drzewo od ty�u
	klucz* kopiaKluczy = reverse2(korzen->pHeadKluczy);
	potomkowie* kopiaPotom = reverse(korzen->pHeadPotom);

	//stworzenie kopii wska�nik�w na pocz�tek odwr�conych list w celu usuni�cia na ko�cu
	klucz* kopiaKluczy2 = kopiaKluczy;
	potomkowie* kopiaPotom2 = kopiaPotom;
	while (kopiaPotom)
	{
		if (kopiaPotom->wezelPotomny)

			graphToFile(kopiaPotom->wezelPotomny, wciecie + 12,plik);

		if (kopiaKluczy)
		{
			plik << setw(wciecie);

			if (!kopiaKluczy->pNext) plik << "[";

			plik << kopiaKluczy->wartosc;

			if (kopiaKluczy == kopiaKluczy2) plik << "]";

		}
		kopiaPotom = kopiaPotom->pNext;
		plik << endl;
		if (kopiaKluczy) kopiaKluczy = kopiaKluczy->pNext;
	}
	deleteKlucz(kopiaKluczy2);
	deletePotom(kopiaPotom2);
}
void print(wezel* korzen)
{
	klucz* pKluczeKopia = korzen->pHeadKluczy;
	potomkowie* pPotomKopia = korzen->pHeadPotom;

	while (pPotomKopia)
	{
		if (pPotomKopia->wezelPotomny)

			print(pPotomKopia->wezelPotomny);

		if (pKluczeKopia)
		{

			cout << pKluczeKopia->wartosc << endl;

		}
		pPotomKopia= pPotomKopia->pNext;
		if (pKluczeKopia) pKluczeKopia = pKluczeKopia->pNext;
	}
}
void printToFile(wezel* korzen, ofstream &plik)
{
	klucz* pKluczeKopia = korzen->pHeadKluczy;
	potomkowie* pPotomKopia = korzen->pHeadPotom;

	while (pPotomKopia)
	{
		if (pPotomKopia->wezelPotomny)

			printToFile(pPotomKopia->wezelPotomny,plik);

		if (pKluczeKopia)
		{

			plik << pKluczeKopia->wartosc << endl;

		}
		pPotomKopia = pPotomKopia->pNext;
		if (pKluczeKopia) pKluczeKopia = pKluczeKopia->pNext;
	}
}