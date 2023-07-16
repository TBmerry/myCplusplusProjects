#include <iostream>
#include "NetworkListener.h"

using namespace std;

int main() {
    // Að dinleyici nesnesi oluþturuyoruz ve að arayüzünü belirtiyoruz.
    NetworkListener listener("Wi-Fi");

    // Kullanýcýdan filtreleme seçeneklerini alalým
    int protocolFilter, portFilter;
    char ipFilter[20];

    cout << "Filtrelemek istediðiniz protokolü girin (TCP: 6, UDP: 17, Filtre yok: -1): ";
    cin >> protocolFilter;
    listener.setProtocolFilter(protocolFilter);

    cout << "Filtrelemek istediðiniz IP adresini girin (Örneðin: 192.168.1.1, Filtre yok: 0.0.0.0): ";
    cin >> ipFilter;
    listener.setIPFilter(ipFilter);

    cout << "Filtrelemek istediðiniz port numarasýný girin (Örneðin: 80, Filtre yok: 0): ";
    cin >> portFilter;
    listener.setPortFilter(portFilter);


    // Að dinleme döngüsünü baþlatýyoruz.
    listener.startListener();

    // Ýstatistikleri ekrana yazdýrýyoruz.
    listener.printStats();

    // TCP ve UDP toplam veri transferlerini alalým ve ekrana yazdýralým
    long long tcpDataTransfer = listener.getTCPDataTransfer();
    long long udpDataTransfer = listener.getUDPDataTrasnfer();

    cout << "Toplam TCP veri transferi : " << tcpDataTransfer << " bytes" << endl;
    cout << "Toplam UDP veri transferi : " << udpDataTransfer << " bytes" << endl;

    // Zaman damgasýna göre toplam veri transferini alalým ve ekrana yazdýralým
    const map<int, long long>& transferPerHour = listener.getTransferPerHour();
    for (const auto& entry : transferPerHour) {
        cout << "Saat : " << entry.first << ":00 - " << entry.first << ":59 arasýnda toplam veri transferi: "
            << entry.second << " bytes" << endl;
    }

	return 0;
}