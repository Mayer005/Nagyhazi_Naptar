#ifndef HONAP_H
#define HONAP_H

#include "ev.h"

//! Hónap osztály már rendelkezik az évvel és hónappal is

class Honap : public Ev {
	int honap;
public:
	//! Konstrukto

	Honap(int ev = 1, int honap = 1) : Ev(ev), honap(honap) {}
	//! Hónap getterje

	int getHonap() const { return honap; }
	//! Hónap setter

	void setHonap(int a) { honap = a; }
	//! Destruktor
	~Honap() {}


};

#endif
