#pragma once
#include <iostream>
#include <pcap.h>
#include <map>
#include <ctime>
#include <string> // string için
#include <cstring> // memset için
#include <winsock2.h>
#include <ws2tcpip.h> // Bu baþlýk, inet_pton iþlevini içerir

class NetworkListener
{
public : 
	NetworkListener(const char* dev) : agrid(nullptr) {
		// Að arayüzü üzerinden pcap handle'ýný oluþturuyoruz.
		agrid = pcap_open_live(dev, BUFSIZ, 1, 1000, errBuf);
		if (agrid == nullptr) {
			// Að arayüzünü açamazsak hata mesajý yazdýrýyoruz.
			cerr << "Að arayüzü açýlamadý !! " << errBuf << endl;
		}
	}

	~NetworkListener() {
		if (agrid != nullptr) {
			// Að dinleyicinin destructor'ýnda pcap handle'ýný kapatýyoruz.
			pcap_close(agrid);
		}
	}

	void startListener() {
		if (agrid != nullptr) {
			// Að dinleme döngüsünü baþlatýyoruz.
			// Yakalanan paketleri "AgDinleyici::packetHandler" fonksiyonuna iletiyoruz.
			pcap_loop(agrid, 0, &NetworkListener::packetHandler, nullptr);
		}
		else {
			cerr << "Að dinleme baþlatýlmadý !! " << endl;
		}
	}

	void printStats() {
        cout << "TCP paket sayýsý : " << tcpPacketCount << endl;
        cout << "TCP ortalama paket boyutu : " << calculateAveragePacketSize(tcpPacketCount, tcpTotalPacketSize) << " bytes" << endl;
        cout << "UDP paket sayýsý : " << udpPacketCount << endl;
        cout << "UDP ortalama paket boyutu : " << calculateAveragePacketSize(udpPacketCount, udpTotalPacketSize) << " bytes" << endl;
    }

	// Toplam TCP veri transferini döndüren fonksiyon
	long long getTCPDataTransfer() const {
		return tcpTotalPacketSize;
	}

	// Toplam UDP veri transferini döndüren fonksiyon
	long long getUDPDataTrasnfer() const {
		return udpTotalPacketSize;
	}

	// Zaman damgasýna göre toplam veri transferini döndüren fonksiyon
	const map<int, long long>& getTransferPerHour() const {
		return transferPerHour;
	}

	// Filtreleme seçeneklerini belirleyen fonksiyonlar
	void setProtocolFilter(int protocol) {
		protocolFilter = protocol;
	}

	void setIPFilter(const char* ip) {
		if (ip) {
			// Yeni IP adresini uint32_t türüne dönüþtürmek için inet_pton kullanýyoruz
			if (inet_pton(AF_INET, ip, &ipFilter) != 1) {
				std::cerr << "Geçersiz IP adresi formatý: " << ip << std::endl;
				// Hatalý bir IP adresi girildiðinde, 0.0.0.0 IP adresini varsayýlan olarak kabul edebiliriz.
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

	// Paketin yakalandýðý zamaný tutacak deðiþken
	map<int, long long> transferPerHour;

	// Filtreleme seçenekleri için deðiþkenler
	int protocolFilter = -1; // -1: Filtre yok, 6: TCP, 17: UDP
	uint32_t ipFilter = 0; // 0: Filtre yok
	uint16_t portFilter = 0; // 0: Filtre yok

	static void packetHandler(unsigned char* userData, const struct pcap_pkthdr* pkthdr, const unsigned char* packet) {
		NetworkListener* listener = reinterpret_cast<NetworkListener*>(userData);
		
		// Paket uzunluðunu pcap_pkthdr yapýsýndan alýyoruz.
		int packetLength = pkthdr->len;

		// Ethernet baþlýðýný atlayarak IP baþlýðýný elde ediyoruz.
		const unsigned char* ipHeader = packet + 14; // 14 byte Ethernet baþlýk uzunluðu

		// IP baþlýðýndan protokol numarasýný alýyoruz.
		int protocol = static_cast<int>(ipHeader[9]);

		// Protokol numarasýna göre paketleri ayrýþtýrýyoruz.
		switch (protocol) {
		case 6: // TCP protokolü
			listener->tcpPacketCount++;
			listener->tcpTotalPacketSize += packetLength;
			break;
		case 17: // UDP protokolü
			listener->udpPacketCount++;
			listener->udpTotalPacketSize += packetLength;
			break;
		default:
			// Diðer protokoller için burada gerekli iþlemler yapýlabilir.
			break;
		}

		// Paketi ekrana yazdýrýyoruz.
		cout << "Yakalanan paket uzunluðu : " << packetLength << "bytes" << endl;

		// Paketin yakalandýðý zaman damgasýný alýyoruz
		time_t now = time(nullptr);
		tm* localTime = localtime(&now);
		int hour = localTime->tm_hour;

		// Paketin içeriðini heksadesimal formatýnda ekrana yazdýrýyoruz.
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

		// Zaman damgasý saatine göre toplam veri transferini güncelliyoruz
		listener->transferPerHour[hour] += packetLength;
	}

	// Filtreleri kontrol eden özel fonksiyon
	bool checkFilter(const unsigned char* packet) {
		// Eðer filtre yoksa, tüm paketler geçerli
		if (protocolFilter == -1 && ipFilter == 0 && portFilter == 0) {
			return true;
		}

		// Protokol filtresi kontrolü
		if (protocolFilter != -1) {
			const unsigned char* ipHeader = packet + 14;
			int protocol = static_cast<int>(ipHeader[9]);
			if (protocol != protocolFilter) {
				return false;
			}
		}

		// IP adresi filtresi kontrolü
		if (ipFilter != 0) {
			const unsigned char* ipHeader = packet + 14;
			uint32_t sourceIP = *reinterpret_cast<const uint32_t*>(&ipHeader[12]);
			if (sourceIP != ipFilter) {
				return false;
			}
		}

		// Port numarasý filtresi kontrolü (sadece TCP veya UDP için)
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

