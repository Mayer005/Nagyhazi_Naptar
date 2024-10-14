#ifndef NAPTAR_H
#define NAPTAR_H

#include "nap.h"
#include "dintomb.h"

//! Singleton ünnepnapok, amely az ünnepnapokat tárolja


class UnnepNapok {

	//! Konsturktor - privát

	UnnepNapok() {

		unnepnapok.hozzaad(new Nap(1, 1, 1, "Ujev"));
		unnepnapok.hozzaad(new Nap(1, 3, 15, "1848-as forradalom"));
		unnepnapok.hozzaad(new Nap(1, 5, 1, "A munka unnepe"));
		unnepnapok.hozzaad(new Nap(1, 8, 20, "Az allamalapitas unnepe"));
		unnepnapok.hozzaad(new Nap(1, 10, 23, "1956-os forradalom"));
		unnepnapok.hozzaad(new Nap(1, 11, 1, "Mindenszentek"));
		unnepnapok.hozzaad(new Nap(1, 11, 2, "Halottak napja"));
		unnepnapok.hozzaad(new Nap(1, 12, 25, "Karacsony"));

	}

	//! Memtrace miatt ismét ezek is = delete helyett csak privátak
	//! másoló konstruktor
	UnnepNapok(const UnnepNapok& rhs);
	//! egyenlőség op
	void operator=(const UnnepNapok&);

public:
	DinTomb<Nap*> unnepnapok;
	static UnnepNapok& getInstance() {
		static UnnepNapok instance;
		return instance;
	}

	//! Ünnepnapokat kilistázza cout-ra
	void kilistaz();
	~UnnepNapok();
};

//! Napok osztály, amely a létrehozott napokat tárolja
//! Tárolja az unnepnapok Singleton egyetlen példányát is könnyebb elérés érdekében

class Napok {
	DinTomb<Nap*> napok;

public:

	//! konstruktor
	Napok() {}
	//! Nap hozzáadása
	void add(Nap* rhs) {
		napok.hozzaad(rhs);
	}


	//! töröl egy létrehozott napot a tömbből
	void torol(Nap* rhs) {
		napok.torol(rhs);
	}
	//! visszatér a letrehozott napok számával
	inline size_t size() {
		return napok.gethossz();
	}
	//! indexelő operátor
	Nap& operator[](int idx) {
		return *napok[idx];
	}
	//! konstans indexelő operátor
	const Nap& operator[](int idx) const {
		return *napok[idx];
	}
	//! fv amely kiír táblázatos nézetben egy adott hónapot
	void honapba_kiir(int ev, int honap);
	//! fv amely kiír táblázatos nézetben egy adott évet
	void evbe_kiir(int ev);
	//! kiírja az összes napokt
	void listaz();
	//! kiírja az összes napot az adott évben
	void listaz(int ev);
	//! kiűríti az összes adatot;
	void clear() {
		napok.urit();
	}
	//! destruktor
	~Napok() {

	};
};

#endif
