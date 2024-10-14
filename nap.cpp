#include "nap.h"


//! segédfv a táblázatos kiíráshoz, visszaadja hogy egy adott nap hányadik volt a héten

int napSzam(int nap, int honap, int ev) {
	if (honap < 3) {
		honap += 12;
		ev -= 1;
	}
	int c = ev / 100;
	ev = ev % 100;
	int h = (c / 4 - 2 * c + ev + ev / 4 + 13 * (honap + 1) / 5 + nap - 1) % 7;
	return (h + 7) % 7 - 1;
}

//! Visszaadja a hónap nevét
/*!
* \param honap - hónap sorszáma
*/

String HonapNeve(int honap) {
	String honapok[] = { "Januar", "Februar", "Marcius",
					   "Aprilis", "Majus", "Junius",
					   "Julius", "Augusztus", "Szeptember",
					   "Oktober", "November", "December"
	};
	return (honapok[honap]);
}

//! visszaadja a hét nevét

String HetNapja(int nap) {
	String napok[] = { "Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap" };
	return napok[nap];
}

//! visszaadja hogy egy adott hónap előtt hány szökőév volt - segédfv a kivonó operátorhoz.

int szokoevekszama(int ev, int ho) {
	int evek = ev;
	if (ho <= 2)
		evek--;
	return evek / 4
		- evek / 100
		+ evek / 400;
}



String Nap::getIndok() const {
	if (foglalt == false) {
		return String("Az adott nap nem foglalt.");
	}
	else if (indok.size() == 0) {
		return String("Az adott nap foglalt, de nem lett megindokolva.");
	}
	return indok;
}


bool Nap::operator==(const Nap& rhs) const {
	return this->getEv() == rhs.getEv() && nap == rhs.nap && this->getHonap() == rhs.getHonap();
}


bool Nap::operator<(const Nap& rhs) const {
	if (this->getEv() != rhs.getEv()) return this->getEv() < rhs.getEv();
	if (this->getHonap() != rhs.getHonap()) return this->getHonap() < rhs.getHonap();
	return nap < rhs.nap;
}
bool Nap::operator>(const Nap& rhs) const {
	return rhs < *this;
}
bool Nap::operator<=(const Nap& rhs) const {
	return !(rhs < *this);
}
bool Nap::operator>=(const Nap& rhs) const {
	return !(*this < rhs);
}

Nap Nap::operator=(const Nap& rhs) {
	if (*this != rhs) {
		this->setEv(rhs.getEv());
		this->setHonap(rhs.getHonap());
		nap = rhs.getNap();
		foglalt = rhs.getFog();
		indok = rhs.indok;
	}
	return *this;
}

Nap Nap::operator=(const Nap* rhs) {
	if (*this != *rhs) {
		this->setEv(rhs->getEv());
		this->setHonap(rhs->getHonap());
		nap = rhs->getNap();
		foglalt = rhs->getFog();
		indok = rhs->indok;
	}
	return *this;
}

int Nap::operator-(const Nap& rhs){
	const int honapoknapjai[12]
		= { 31, 28, 31, 30, 31, 30,
		   31, 31, 30, 31, 30, 31 };


	long int n1 = this->getEv() * 365 + rhs.getNap();
	for (int i = 0; i < this->getHonap() - 1; i++)
		n1 += honapoknapjai[i];
	n1 += szokoevekszama(this->getEv(), this->getHonap());


	long int n2 = rhs.getEv() * 365 + this->nap;
	for (int i = 0; i < rhs.getHonap() - 1; i++)
		n2 += honapoknapjai[i];
	n2 += szokoevekszama(rhs.getEv(), rhs.getHonap());

	return abs((n2 - n1));
}



bool Nap::operator!=(const Nap& rhs) const {
	return !(*this == rhs);
}

Nap Nap::operator++() {

	if (this->getNap() == NapSzamolo::getInstance().honapnapszam(this->getHonap() - 1, this->getEv())) {
		int temp = this->getHonap() + 1;
		if (temp == 13) {
			temp = 1;
			this->setEv(this->getEv() + 1);
			return *this;
		}
		this->setHonap(temp);
		return *this;
	}
	nap++;
	return *this;
}

Nap Nap::operator++(int) {
	Nap temp = *this;
	operator++();
	return temp;
}

Nap Nap::operator--() {
	if (this->getNap() == 1) {
		if (this->getHonap() == 1) {
			this->setEv(this->getEv() - 1);
			
			return *this;
		}
		int temp = this->getHonap() - 1;
		int napszam = NapSzamolo::getInstance().honapnapszam(temp - 1, this->getEv());
		this->setHonap(temp);
		nap = napszam;
		return *this;
	}
	nap--;
	return *this;
}

Nap Nap::operator--(int){
	Nap temp = *this;
	operator--();
	return temp;
}
String Nap::melyiknap() const {
	int vege = napSzam(this->nap, this->getHonap(), this->getEv());
	if (vege == -1) {
		vege = 6;
	}
	String hetNapja = HetNapja(vege);
	
	return hetNapja;
}