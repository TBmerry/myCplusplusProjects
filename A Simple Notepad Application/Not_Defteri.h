#pragma once
#include <iostream>
#include <string>
#include <list> // list kütüphanesini dahil etmek için kullanýlýr
#include "Not.h" 


class Not_Defteri {
	public:

	list<Not> notListesi; // Not sýnýfýnýn elemanlarýný tutmak için bir liste oluþturulur

	void notEkle(Not yeniNot) {
		Not n1("Not 1"); // "Not 1" metniyle yeni bir Not nesnesi oluþturulur

		notListesi.push_back(n1); // n1'i notListesi'ne ekler
		notListesi.push_back(yeniNot); // yeniNot'u notListesi'ne ekler
	}


	void notSil(Not silinecekNot) {
		notListesi.remove(silinecekNot); // silinecekNot'u notListesi'nden kaldýrýr
	}

	void notListele() {
		for (const Not& n : notListesi) {
			cout << n << endl; // notListesi'ndeki her bir Not nesnesini ekrana yazdýrýr
		}
	}

};

