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