#include <iostream>
#include <Windows.h>

using namespace std;

// Pin numaralar�n� tan�mlama
const int ledPin = 13;
const int motorPin = 10;

// LED'in yan�p s�nmesi i�lemi
void toggleLed() {
	while (true) {
		digitalWrite(ledPin, HIGH); // LED'i yak
		Sleep(1000);                // 1 saniye bekle
		digitalWrite(ledPin, LOW);  // LED'i s�nd�r
		Sleep(1000);				// 1 saniye bekle
	}
}

// Motorun d�nmesi i�lemi
void rotateMotor() {
	digitalWrite(motorPin, HIGH); // Motoru �al��t�r
	Sleep(5000);				  // 5 saniye �al��t�r
	digitalWrite(motorPin, LOW);  // Motoru durdur
}

// Ana program d�ng�s�
int main() {
	// Pinleri ��k�� olarak ayarlama
	pinMode(ledPin, OUTPUT);
	pinMode(motorPin, OUTPUT);

	toggleLed(); // LED'in yan�p s�nmesini ba�lat
	rotateMotor(); // Motorun d�nmesini ba�lat
	
	return 0;
}