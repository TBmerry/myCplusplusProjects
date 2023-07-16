#pragma once
#include <iostream>
#include <pcap.h>
#include <map>
#include <ctime>
#include <string> // string i�in
#include <cstring> // memset i�in
#include <winsock2.h>
#include <ws2tcpip.h> // Bu ba�l�k, inet_pton i�levini i�erir

class NetworkListener
{
public : 
	NetworkListener(const char* dev) : agrid(nullptr) {
		// A� aray�z� �zerinden pcap handle'�n� olu�turuyoruz.
		agrid = pcap_open_live(dev, BUFSIZ, 1, 1000, errBuf);
		if (agrid == nullptr) {
			// A� aray�z�n� a�amazsak hata mesaj� yazd�r�yoruz.
			cerr << "A� aray�z� a��lamad� !! " << errBuf << endl;
		}
	}

	~NetworkListener() {
		if (agrid != nullptr) {
			// A� dinleyicinin destructor'�nda pcap handle'�n� kapat�yoruz.
			pcap_close(agrid);
		}
	}

	void startListener() {
		if (agrid != nullptr) {
			// A� dinleme d�ng�s�n� ba�lat�yoruz.
			// Yakalanan paketleri "AgDinleyici::packetHandler" fonksiyonuna iletiyoruz.
			pcap_loop(agrid, 0, &NetworkListener::packetHandler, nullptr);
		}
		else {
			cerr << "A� dinleme ba�lat�lmad� !! " << endl;
		}
	}

	void printStats() {
        cout << "TCP paket say�s� : " << tcpPacketCount << endl;
        cout << "TCP ortalama paket boyutu : " << calculateAveragePacketSize(tcpPacketCount, tcpTotalPacketSize) << " bytes" << endl;
        cout << "UDP paket say�s� : " << udpPacketCount << endl;
        cout << "UDP ortalama paket boyutu : " << calculateAveragePacketSize(udpPacketCount, udpTotalPacketSize) << " bytes" << endl;
    }

	// Toplam TCP veri transferini d�nd�ren fonksiyon
	long long getTCPDataTransfer() const {
		return tcpTotalPacketSize;
	}

	// Toplam UDP veri transferini d�nd�ren fonksiyon
	long long getUDPDataTrasnfer() const {
		return udpTotalPacketSize;
	}

	// Zaman damgas�na g�re toplam veri transferini d�nd�ren fonksiyon
	const map<int, long long>& getTransferPerHour() const {
		return transferPerHour;
	}

	// Filtreleme se�eneklerini belirleyen fonksiyonlar
	void setProtocolFilter(int protocol) {
		protocolFilter = protocol;
	}

	void setIPFilter(const char* ip) {
		if (ip) {
			// Yeni IP adresini uint32_t t�r�ne d�n��t�rmek i�in inet_pton kullan�yoruz
			if (inet_pton(AF_INET, ip, &ipFilter) != 1) {
				std::cerr << "Ge�ersiz IP adresi format�: " << ip << std::endl;
				// Hatal� bir IP adresi girildi�inde, 0.0.0.0 IP adresini varsay�lan olarak kabul edebiliriz.
				ipFilter = 0;
			}
		}
	}

	void setPortFilter(uint16_t port) {
		portFilter = htons(port);
	}


private :
	pcap_t* agrid;
	char errBuf[PCAP_ERRBUF_SIZE];

	int tcpPacketCount = 0;
	int udpPacketCount = 0;
	long long tcpTotalPacketSize = 0;
	long long udpTotalPacketSize = 0;

	// Paketin yakaland��� zaman� tutacak de�i�ken
	map<int, long long> transferPerHour;

	// Filtreleme se�enekleri i�in de�i�kenler
	int protocolFilter = -1; // -1: Filtre yok, 6: TCP, 17: UDP
	uint32_t ipFilter = 0; // 0: Filtre yok
	uint16_t portFilter = 0; // 0: Filtre yok

	static void packetHandler(unsigned char* userData, const struct pcap_pkthdr* pkthdr, const unsigned char* packet) {
		NetworkListener* listener = reinterpret_cast<NetworkListener*>(userData);
		
		// Paket uzunlu�unu pcap_pkthdr yap�s�ndan al�yoruz.
		int packetLength = pkthdr->len;

		// Ethernet ba�l���n� atlayarak IP ba�l���n� elde ediyoruz.
		const unsigned char* ipHeader = packet + 14; // 14 byte Ethernet ba�l�k uzunlu�u

		// IP ba�l���ndan protokol numaras�n� al�yoruz.
		int protocol = static_cast<int>(ipHeader[9]);

		// Protokol numaras�na g�re paketleri ayr��t�r�yoruz.
		switch (protocol) {
		case 6: // TCP protokol�
			listener->tcpPacketCount++;
			listener->tcpTotalPacketSize += packetLength;
			break;
		case 17: // UDP protokol�
			listener->udpPacketCount++;
			listener->udpTotalPacketSize += packetLength;
			break;
		default:
			// Di�er protokoller i�in burada gerekli i�lemler yap�labilir.
			break;
		}

		// Paketi ekrana yazd�r�yoruz.
		cout << "Yakalanan paket uzunlu�u : " << packetLength << "bytes" << endl;

		// Paketin yakaland��� zaman damgas�n� al�yoruz
		time_t now = time(nullptr);
		tm* localTime = localtime(&now);
		int hour = localTime->tm_hour;

		// Paketin i�eri�ini heksadesimal format�nda ekrana yazd�r�yoruz.
		for (int i = 0; i < packetLength; i++) {
			cout << hex << static_cast<int>(packet[i]) << " ";
			if ((i + 1) % 16 == 0) {
				cout << endl;
			}
		}
		cout << dec << endl;

		// Filtreleri kontrol ediyoruz
		if (!listener->checkFilter(packet)) {
			return;
		}

		// Zaman damgas� saatine g�re toplam veri transferini g�ncelliyoruz
		listener->transferPerHour[hour] += packetLength;
	}

	// Filtreleri kontrol eden �zel fonksiyon
	bool checkFilter(const unsigned char* packet) {
		// E�er filtre yoksa, t�m paketler ge�erli
		if (protocolFilter == -1 && ipFilter == 0 && portFilter == 0) {
			return true;
		}

		// Protokol filtresi kontrol�
		if (protocolFilter != -1) {
			const unsigned char* ipHeader = packet + 14;
			int protocol = static_cast<int>(ipHeader[9]);
			if (protocol != protocolFilter) {
				return false;
			}
		}

		// IP adresi filtresi kontrol�
		if (ipFilter != 0) {
			const unsigned char* ipHeader = packet + 14;
			uint32_t sourceIP = *reinterpret_cast<const uint32_t*>(&ipHeader[12]);
			if (sourceIP != ipFilter) {
				return false;
			}
		}

		// Port numaras� filtresi kontrol� (sadece TCP veya UDP i�in)
		if (protocolFilter == 6 || protocolFilter == 17) {
			const unsigned char* ipHeader = packet + 14;
			const unsigned char* transportHeader = ipHeader + (4 * (ipHeader[0] & 0x0F));
			uint16_t sourcePort = *reinterpret_cast<const uint16_t*>(&transportHeader[0]);
			uint16_t destPort = *reinterpret_cast<const uint16_t*>(&transportHeader[2]);
			if (sourcePort != portFilter && destPort != portFilter) {
				return false;
			}
		}

		return true;
	}
	
	double calculateAveragePacketSize(int packetCount, long long totalPacketSize) {
			return (packetCount > 0) ? static_cast<double>(totalPacketSize) / packetCount : 0.0;
		}

};

