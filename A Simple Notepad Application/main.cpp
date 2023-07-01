#include <iostream>
#include <string>
#include "Not.h"
#include "Not_Defteri.h"

using namespace std;

int main() {
	string komut;

	Not_Defteri defter; // not_defteri sýnýfýndan bir nesne oluþtur

	while (true) {
		cout << "Lütfen islem giriniz(notEkle,notSil,notListele) : " << endl;
		cin >> komut;

		if (komut == "çýkýþ") {
			cout << "Program sonlandýrýlýyor. " << endl;
			break;
		}

		if (komut == "notEkle") {
			string metin;
			cout << "Not metnini giriniz: ";
			cin.ignore(); // Önceki giriþten kalan new line karakterini atlamak için
			getline(cin, metin);
			Not yeniNot(metin); // Girilen metinle yeni bir Not nesnesi oluþturulur
			defter.notEkle(yeniNot); // Yeni notu deftere ekler
		}
		else if (komut == "notSil") {
			string metin;
			cout << "Silinecek notun metnini giriniz: ";
			cin.ignore(); // Önceki giriþten kalan new line karakterini atlamak için
			getline(cin, metin);
			Not silinecekNot(metin); // Girilen metinle silinecek bir Not nesnesi oluþturulur
			defter.notSil(silinecekNot); // Silinecek notu defterden çýkarýr
		}
		else if (komut == "notListele") {
			defter.notListele(); // Defterdeki notlarý listeler
		}
		else {
			cout << "Geçersiz islem !" << endl;
		}
	}


	return 0;
}