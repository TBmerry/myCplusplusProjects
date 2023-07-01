#pragma once
#include <iostream>
#include <string>
#include <list> // list k�t�phanesini dahil etmek i�in kullan�l�r
#include "Not.h" 


class Not_Defteri {
	public:

	list<Not> notListesi; // Not s�n�f�n�n elemanlar�n� tutmak i�in bir liste olu�turulur

	void notEkle(Not yeniNot) {
		Not n1("Not 1"); // "Not 1" metniyle yeni bir Not nesnesi olu�turulur

		notListesi.push_back(n1); // n1'i notListesi'ne ekler
		notListesi.push_back(yeniNot); // yeniNot'u notListesi'ne ekler
	}


	void notSil(Not silinecekNot) {
		notListesi.remove(silinecekNot); // silinecekNot'u notListesi'nden kald�r�r
	}

	void notListele() {
		for (const Not& n : notListesi) {
			cout << n << endl; // notListesi'ndeki her bir Not nesnesini ekrana yazd�r�r
		}
	}

};

