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