#pragma once
#include <iostream>
#include <fstream>
#include "funkcje.h"
#include "struktury.h"

using namespace std;
struct listaFunkcji;
struct wezel;
struct klucz;
struct potomkowie;
struct listaFunkcji;
listaFunkcji* wczytaj_z_pliku(string nazwa_pliku, int& rzad);
wezel* add(wezel*& korzen, double wartosc, wezel*& wskLewy, int rzad);
void deleteListaF(listaFunkcji*& pHead);
void deleteKlucz(klucz*& pHead);
void deletePotom(potomkowie*& pHead);
void deleteBTree(wezel*& korzen);
void graph(wezel* korzen, int wciecie);
void drukujListeKluczy(klucz* pHead);
void graphToFile(wezel* korzen, int wciecie, ofstream&plik);
void print(wezel* korzen);
void printToFile(wezel* korzen, ofstream& plik);
wezel* remove(wezel* korzen, double wartosc, int rzad);
void search(wezel* korzen, double wartosc, searchResult& wynik);
wezel* createNewTree(wezel* korzen, double wartosc, wezel* lewy);
podzial divide(wezel*& node, int rzad);
wezel* insert(wezel* node, klucz*& kluczPoprz, potomkowie*& potomPoprz, double wartosc, wezel* lewy, int rzad);