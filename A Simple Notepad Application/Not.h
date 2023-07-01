#pragma once
#include <iostream>
#include <string>

using namespace std;

class Not {
public:

	string metin;

	// Yap�c� fonksiyon, metin �zelli�ini alarak atar
	Not(const string& metin) : metin(metin) {
	}

	// ��k�� ak�� operat�r� a��r� y�klemesi, metin �zelli�ini ostream'e yazd�r�r
	friend ostream& operator<<(ostream& os, const Not& n) {
		os << n.metin; // metin �yesini ostream'e yazd�r
		return os;
	}

	// E�itlik operat�r� a��r� y�klemesi, metin �zelliklerini kar��la�t�r�r
	bool operator==(const Not& other) const {
		return metin == other.metin;
	}

};