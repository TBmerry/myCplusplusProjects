#include <iostream>
#include <string>
#include "Not.h"
#include "Not_Defteri.h"

using namespace std;

int main() {
	string komut;

	Not_Defteri defter; // not_defteri s�n�f�ndan bir nesne olu�tur

	while (true) {
		cout << "L�tfen islem giriniz(notEkle,notSil,notListele) : " << endl;
		cin >> komut;

		if (komut == "��k��") {
			cout << "Program sonland�r�l�yor. " << endl;
			break;
		}

		if (komut == "notEkle") {
			string metin;
			cout << "Not metnini giriniz: ";
			cin.ignore(); // �nceki giri�ten kalan new line karakterini atlamak i�in
			getline(cin, metin);
			Not yeniNot(metin); // Girilen metinle yeni bir Not nesnesi olu�turulur
			defter.notEkle(yeniNot); // Yeni notu deftere ekler
		}
		else if (komut == "notSil") {
			string metin;
			cout << "Silinecek notun metnini giriniz: ";
			cin.ignore(); // �nceki giri�ten kalan new line karakterini atlamak i�in
			getline(cin, metin);
			Not silinecekNot(metin); // Girilen metinle silinecek bir Not nesnesi olu�turulur
			defter.notSil(silinecekNot); // Silinecek notu defterden ��kar�r
		}
		else if (komut == "notListele") {
			defter.notListele(); // Defterdeki notlar� listeler
		}
		else {
			cout << "Ge�ersiz islem !" << endl;
		}
	}


	return 0;
}