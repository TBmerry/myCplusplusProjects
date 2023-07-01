#pragma once
#include <iostream>
#include <string>

using namespace std;

class Not {
public:

	string metin;

	// Yapýcý fonksiyon, metin özelliðini alarak atar
	Not(const string& metin) : metin(metin) {
	}

	// Çýkýþ akýþ operatörü aþýrý yüklemesi, metin özelliðini ostream'e yazdýrýr
	friend ostream& operator<<(ostream& os, const Not& n) {
		os << n.metin; // metin üyesini ostream'e yazdýr
		return os;
	}

	// Eþitlik operatörü aþýrý yüklemesi, metin özelliklerini karþýlaþtýrýr
	bool operator==(const Not& other) const {
		return metin == other.metin;
	}

};