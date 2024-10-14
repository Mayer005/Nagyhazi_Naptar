#ifndef DINTOMB_H
#define DINTOMB_H

#include <iostream>
#include "memtrace.h"
#include "nap.h"

//!	generikus dinamikus tomb osztály, a napok lefoglalásához.
	
template <typename T>
class DinTomb {
	T* adatok;
	size_t db;
public:
	//! konsturktor
	DinTomb() : adatok(nullptr), db(0) {}
	//! destruktor
	virtual ~DinTomb() {
		delete[] adatok;
		db = 0;
	}
	//! másoló konstruktor
	DinTomb(const DinTomb<T>& rhs){
		db = rhs.db;
		adatok = new T[db];
		for (int i = 0; i < db; i++)
			adatok[i] = rhs.adatok[i];
	}

	 
	//! Tömb végére fűz
	/*!
	* \param rhs -  Napra mutató pointer, ezt adja hozzá a tombhoz.
	*/
	void hozzaad(Nap* rhs) {


		T *ujadatok = new T[db + 1];
		for (size_t i = 0; i < db; i++) {
			ujadatok[i] = adatok[i];
		}
		ujadatok[db] = rhs;
		db++;
		delete[] adatok;
		adatok = ujadatok;
	}
	//! Tömbből adott elemet töröl
	/*!
	*  \param rhs -  törlendő nap pointere
	*/
	void torol(Nap* rhs) {
		if (db == 0) {
			throw std::length_error("Ures a tomb");
		}

		T* ujtomb = new T[db - 1];
		
		
		int regi = 0;

		for (size_t i = 0; i < db; i++){
			if (adatok[i] != rhs){
				ujtomb[regi++] = adatok[i];
			}
		}
		db--;
		delete[] adatok;
		adatok = ujtomb;
	}

	//! Indexelő operátor
	/*!
	*	\param rhs - unsigned int, index
	*/
	T& operator[](const size_t rhs) {
		if (rhs < 0 || rhs >= db) {
			throw std::out_of_range("Index kivul esik a tombon!");
		}
		return adatok[rhs];
	}
	//! konstans indexelő
	const T& operator[](const size_t rhs) const {
		if (rhs < 0 || rhs >= db) {
			throw std::out_of_range("Index kivul esik a tombon!");
		}
		return adatok[rhs];
	}

	//! Tömböt kiírja std::cout-ra
	void kiir() const {
		for (size_t i = 0; i < db; i++) {
			std::cout << adatok[i] << std::endl;
		}
	}
	//! visszaadja a tömb méretét
	size_t gethossz() { return db; }

	void urit() {
		delete[] adatok;
		adatok = nullptr;
		db = 0;
	}
};



#endif
