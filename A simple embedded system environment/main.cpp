#include <iostream>
#include <Windows.h>

using namespace std;

// Pin numaralarýný tanýmlama
const int ledPin = 13;
const int motorPin = 10;

// LED'in yanýp sönmesi iþlemi
void toggleLed() {
	while (true) {
		digitalWrite(ledPin, HIGH); // LED'i yak
		Sleep(1000);                // 1 saniye bekle
		digitalWrite(ledPin, LOW);  // LED'i söndür
		Sleep(1000);				// 1 saniye bekle
	}
}

// Motorun dönmesi iþlemi
void rotateMotor() {
	digitalWrite(motorPin, HIGH); // Motoru çalýþtýr
	Sleep(5000);				  // 5 saniye çalýþtýr
	digitalWrite(motorPin, LOW);  // Motoru durdur
}

// Ana program döngüsü
int main() {
	// Pinleri çýkýþ olarak ayarlama
	pinMode(ledPin, OUTPUT);
	pinMode(motorPin, OUTPUT);

	toggleLed(); // LED'in yanýp sönmesini baþlat
	rotateMotor(); // Motorun dönmesini baþlat
	
	return 0;
}