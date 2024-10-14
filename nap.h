#ifndef NAP_H
#define NAP_H

#include "honap.h"
#include "string5.h"
#include <stdexcept>
#include <array>
#include <iomanip>

int napSzam(int nap, int honap, int ev);
String HonapNeve(int honap);
String HetNapja(int nap);
int szokoevekszama(int ev, int ho);



//! Nap osztály
/*!
*	Tárol egy naptári nap adatait és tárolja hogy az 
*	adott nap foglalt-e, ha igen akkor azt is hogy miért.
*/

class Nap : public Honap {
	int nap;
	bool foglalt;
	String indok;
public:
	//! konstruktor, ami nem lefoglalt napot hoz létre
	/*!
	*	Hibát dob, ha olyan napot akar létrehozni, 
	*	amely nem létezik a Gergely-naptárban.
	*/
	Nap(int ev = 1, int honap = 1, int nap = 1) : Honap(ev, honap), nap(nap), foglalt(false), indok() {
		if (honap > 12 || nap > NapSzamolo::getInstance().honapnapszam(honap - 1, ev) || honap < 1 || nap < 1) {
			throw std::out_of_range("Nem letezik ilyen nap");
		}
	}
	//! Konstruktor, ami lefoglalt napot hoz létre
	Nap(int ev, int honap, int nap, String indok ) : Honap(ev, honap), nap(nap), foglalt(true), indok(indok) {
		if (honap > 12 || nap > NapSzamolo::getInstance().honapnapszam(honap - 1, ev) || honap < 1 || nap < 1) {
			throw std::out_of_range("Nem letezik ilyen nap");
		}
	}

	//! inline fv, nem lefoglalt nap lefoglalására
	/*!
	*	\param rhs - lefoglalás indoka.
	*/

	inline void foglal(const char* rhs) {
		foglalt = true;
		indok = rhs;
	}
	//! Másoló konstruktor
	Nap(const Nap& rhs) : Honap(rhs.getEv(), rhs.getHonap()) {
		nap = rhs.getNap();
		foglalt = rhs.getFog();
		indok = rhs.indok;
	}
	//! Nap getter
	int getNap() const { 
		return nap; 
	}
	//! Foglalás tényének a getterje
	bool getFog() const { 

		return foglalt; 
	}

	//! Foglalás indokának a getterje.
	String getIndok() const;

	//! Egyenlőséget eldöntő operátor
	/*!
	* \param rhs - Nap referencia amivel hasonlítunk
	*/
	bool operator==(const Nap& rhs) const;

	//! kisebb operátor
	/*!
	* \param rhs - Nap referencia amivel hasonlítunk
	*/
	bool operator<(const Nap& rhs) const;
	//! nagyobb operátor
	/*!
	* \param rhs - Nap referencia amivel hasonlítunk
	*/
	bool operator>(const Nap& rhs) const;
	//! kisebb-egyenlő op
	/*!
	* \param rhs - Nap referencia amivel hasonlítunk
	*/
	bool operator<=(const Nap& rhs) const;

	//! nagyobb-egyenlő op
	/*!
	* \param rhs - Nap referencia amivel hasonlítunk
	*/

	bool operator>=(const Nap& rhs) const;
	//! kivonás operátor
	/*!
	* \param rhs - Nap referencia amelyiket kivonjuk
	* \return - a két nap között eltelt napok száma.
	*/
	int operator-(const Nap& rhs);

	//! nem egyenlő operátor
	bool operator!=(const Nap& rhs) const;

	//! egyenlőség op
	Nap operator=(const Nap& rhs);
	//! egyenlőség op
	Nap operator=(const Nap* rhs);
	//! pre inkremens
	Nap operator++();
	//! post inkremens
	Nap operator++(int);
	//! pre dekremens
	Nap operator--();
	//! post dekremens
	Nap operator--(int);

	//! Kiíró operátor
	/*!
	* \param os - ostream, amelyre kiír
	* \param rhs - Nap referencia, amit kiír
	*/
	friend std::ostream& operator<<(std::ostream& os, const Nap& rhs) {
		os << std::setw(4) << std::setfill('0') <<rhs.getEv() << "." << std::setw(2) << std::setfill('0') << rhs.getHonap() << "." << std::setw(2) << std::setfill('0') << rhs.nap;
		return os;
	}

	//! Fv amely megadja hogy az adott nap milyen napra esett.
	String melyiknap() const;
};



#endif

