#ifndef NAPSZAMLALO_H
#define NAPSZAMLALO_H



#include <iostream>



//! NapSzamolo osztály - singleton
//! Abban fog segíteni, hogy megadja hogy mely hónap hány napos egy évben.

class NapSzamolo {
private:
	int honapoknapjai[12] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	//! privát konstruktor
	NapSzamolo() {}
	//! Segédfv amely eldöti egy évről hogy szökőév-e
	/*!
	* \param ev - az adott év amiről el kell dönteni, hogy szökőév-e
	*/
	bool szokoev(const int ev) {
		return ev % 400 == 0 || (ev % 4 == 0 && ev % 100 != 0);
	}


	//! Privát másoló konstruktor
	//! Ezek azért privátak és nem = delete, mert a memtrace felüldefiniálja a deletet, így ha van memtrace az nem jó
	NapSzamolo(NapSzamolo& rhs);
	//! privát egyenlőség op
	void operator=(const NapSzamolo&);

public:
	
	//! statikus Instance getter singletonhoz
	static NapSzamolo& getInstance() {
		static NapSzamolo instance;
		return instance;
	}
	//! fv amely megadja adott hónapról hogy hány napos
	/*!
	* \param honap - hónap sorszáma - 1
	* \param ev - év amelyben nézzük
	*/
	int honapnapszam(int honap, int ev) {
		if (honap == 1 && szokoev(ev)) {
			return 29;
		}
		return honapoknapjai[honap];
	}
};



#endif

