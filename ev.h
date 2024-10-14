#ifndef EV_H
#define EV_

#include <iostream>
#include "napszamlalo.h"
#include "memtrace.h"

//! Év osztály, csak az évszámot tárolja
/*!
*	Bazis leszármazotta, bár ennek haszna csak majd a Nap osztályban lesz
*/

class Ev{
	int ev;
public:
	//! konstruktor
	Ev(int evszam = 1): ev(evszam) {}
	//! Év getter
	int getEv() const { return ev; }
	//! Év setter
	void setEv(int a) { ev = a; }
	//! Destruktor
	~Ev() {}
};





#endif
