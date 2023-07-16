#include <iostream>
#include "NetworkListener.h"

using namespace std;

int main() {
    // A� dinleyici nesnesi olu�turuyoruz ve a� aray�z�n� belirtiyoruz.
    NetworkListener listener("Wi-Fi");

    // Kullan�c�dan filtreleme se�eneklerini alal�m
    int protocolFilter, portFilter;
    char ipFilter[20];

    cout << "Filtrelemek istedi�iniz protokol� girin (TCP: 6, UDP: 17, Filtre yok: -1): ";
    cin >> protocolFilter;
    listener.setProtocolFilter(protocolFilter);

    cout << "Filtrelemek istedi�iniz IP adresini girin (�rne�in: 192.168.1.1, Filtre yok: 0.0.0.0): ";
    cin >> ipFilter;
    listener.setIPFilter(ipFilter);

    cout << "Filtrelemek istedi�iniz port numaras�n� girin (�rne�in: 80, Filtre yok: 0): ";
    cin >> portFilter;
    listener.setPortFilter(portFilter);


    // A� dinleme d�ng�s�n� ba�lat�yoruz.
    listener.startListener();

    // �statistikleri ekrana yazd�r�yoruz.
    listener.printStats();

    // TCP ve UDP toplam veri transferlerini alal�m ve ekrana yazd�ral�m
    long long tcpDataTransfer = listener.getTCPDataTransfer();
    long long udpDataTransfer = listener.getUDPDataTrasnfer();

    cout << "Toplam TCP veri transferi : " << tcpDataTransfer << " bytes" << endl;
    cout << "Toplam UDP veri transferi : " << udpDataTransfer << " bytes" << endl;

    // Zaman damgas�na g�re toplam veri transferini alal�m ve ekrana yazd�ral�m
    const map<int, long long>& transferPerHour = listener.getTransferPerHour();
    for (const auto& entry : transferPerHour) {
        cout << "Saat : " << entry.first << ":00 - " << entry.first << ":59 aras�nda toplam veri transferi: "
            << entry.second << " bytes" << endl;
    }

	return 0;
}