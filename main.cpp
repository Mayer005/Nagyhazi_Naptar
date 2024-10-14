
#include <iostream>
#include "naptar.h"
#include "gtest_lite.h"
#include "nap.h"



int main() {
	
	/*!
	* Első teszt - Csak létrehozunk egy olyan napot ami nemlétezik,
	* majd egy olyat ami létezik, exception-t várunk a nem létezőnél.
	*/
	TEST(elso, Nemletezonap) {
		EXPECT_THROW(Nap a(2012, 12, 32), std::out_of_range);
		EXPECT_NO_THROW(Nap b(2024, 02, 29));
	} ENDM


	/*!
	* Második teszt -  Generikus dinamikus tömb kezelését, helyességét teszteli
	*/
	TEST(masodik, DinTombhasznalat) {
		Napok adatbazis;
		Nap a(2012, 12, 1);
		adatbazis.add(&a);
		EXPECT_EQ(1, adatbazis.size()) << "Baj van az adatbazis hosszaval" << std::endl;
		EXPECT_NO_THROW(adatbazis.torol(&a));
		EXPECT_THROW(adatbazis.torol(&a), std::length_error);
		Nap b(2016, 10, 18);
		adatbazis.add(&b);
		Nap c(2101, 10, 12);
		adatbazis.add(&b);
		//indexeljunk tul
		EXPECT_THROW(adatbazis[4], std::out_of_range);
		EXPECT_NO_THROW(adatbazis[1]);
		EXPECT_THROW(adatbazis[-1], std::out_of_range);
		
	} ENDM
	/*!
	* Harmadik teszt - év és hónap konstruktorokat is tesztel
	*/
	TEST(harmadik, constructorok_kulon) {
		Ev a;
		Honap b;
		Nap c;
		Nap foglal(2107, 10, 21, "foglalva");
		if (a.getEv() == 1 && b.getEv() == 1 && b.getHonap() == 1 && c.getEv() == 1 && c.getHonap() == 1 && c.getNap() == 1 
			&& foglal.getEv() == 2107 && foglal.getHonap() == 10 && foglal.getNap() == 21 && foglal.getFog() == true) {
			SUCCEED() << "Kontruktor mukodik elemekhez" << std::endl;
		}
		else {
			FAIL() << "Nem jo ertekeket adott at" << std::endl;
		}
	} ENDM

	/*!
	* Negyedik teszt - Napok lefoglalásának helyességét,
	* adataik pontos tárolását teszteli
	*/
	TEST(negyedik, foglalas) {
	Napok adatok;
	Nap a(2013, 12, 1, "Vacsi");
	Nap b(2017, 10, 3, "Koncert");
	Nap c(2020, 2, 12, "Rapleszamolas");
	Nap	d(2023, 2, 23, "Ganghaboru");
	Nap	e;
	e.foglal("Kulonfoglalt");
	adatok.add(&a);
	adatok.add(&b);
	adatok.add(&c);
	adatok.add(&d);
	adatok.add(&e);
	EXPECT_TRUE(e.getFog());
	for (size_t i = 0; i < adatok.size(); i++){
		EXPECT_TRUE(adatok[i].getFog());
	}
	//Egyszerre teszteli a String operator=-t is
	String elso = e.getIndok();
	String masodik = a.getIndok();
	EXPECT_STREQ("Kulonfoglalt", elso.c_str());
	EXPECT_STREQ("Vacsi", masodik.c_str());
	adatok.torol(&b);
	EXPECT_EQ(4, adatok.size());
	adatok.clear(); //foglalások törlése 
	EXPECT_EQ(0, adatok.size());
	
	} ENDM
	

	/*!
	* Ötödik teszteset - Napokkal való számításokat, operátorokat, iterátorokat teszteli
	* 
	*/
	TEST(otodik, szamitasok_es_operatorok) {
		EXPECT_EQ(29, NapSzamolo::getInstance().honapnapszam(2-1, 2024)); //februar csak 0 tol indexel
		EXPECT_EQ(31, NapSzamolo::getInstance().honapnapszam(5-1, 2024));
		EXPECT_EQ(28, NapSzamolo::getInstance().honapnapszam(2-1, 2025));
		Nap a(2024, 05, 02);
		Nap a2(2004, 05, 02);
		Nap a3(2024, 05, 02);
		Nap a4(2023, 1, 1);
		Nap a5(2024, 1, 1);
		String b = a.melyiknap();
		String b2 = a2.melyiknap();
		EXPECT_STREQ("Csutortok", b.c_str());
		EXPECT_STREQ("Vasarnap", b2.c_str());

		//hetfoi elso nap ellenorzese
		String b3 = a4.melyiknap();
		String b4 = a5.melyiknap();
		EXPECT_FALSE(b3.c_str() == b4.c_str());
		//kivonas, egyenloseg
		EXPECT_FALSE(a == a2);
		EXPECT_TRUE(a == a3);
		EXPECT_EQ(7305, a - a2);
		a = a2;
		EXPECT_EQ(a2, a);
		Nap kisebb(2012, 2, 28);
		Nap nagyobb(2012, 2, 28);
		++nagyobb;
		EXPECT_LT(kisebb, nagyobb);
		kisebb++;
		EXPECT_EQ(kisebb, nagyobb);
		--kisebb;
		EXPECT_LT(kisebb, nagyobb);
		nagyobb--;
		EXPECT_EQ(kisebb, nagyobb);
	} ENDM

	/*!
	*	Kiiratasteszteles, ez szemre fog menni
	*/
	Napok gyujtemeny;
	Nap a1(2023, 1, 1, "Szulinap");
	Nap a2(2023, 3, 15, "Ebed-mama");
	Nap a3(2023, 4, 10, "Fesztival");
	Nap a4(2023, 8, 30, "Torlesztes");
	Nap a5(2023, 9, 1, "Susu kezdes");
	Nap a6(2023, 10, 1, "Szulinap2");
	Nap a7(2023, 6, 8, "Melo kezdes");
	Nap a8(2023, 12, 6, "Miki");
	Nap a9(2023, 7, 10, "Nyaralas");
	Nap a11(2001, 1, 1, "Korhazi latogatas");
	Nap a10(2023, 1, 3);
	
	gyujtemeny.honapba_kiir(2024, 2);  //Várunk egy február 29.ei napot
//	gyujtemeny.honapba_kiir(2022, 01); 
	gyujtemeny.evbe_kiir(1969); //Január egy nem hétfő

	/*!
	* Hozzáadunk minden napot gyüjteménybe, hogy kiirhassuk őket.
	*/
	gyujtemeny.add(&a1);
	gyujtemeny.add(&a2);
	gyujtemeny.add(&a3);
	gyujtemeny.add(&a4);
	gyujtemeny.add(&a5);
	gyujtemeny.add(&a6);
	gyujtemeny.add(&a7);
	gyujtemeny.add(&a8);
	gyujtemeny.add(&a9);
	gyujtemeny.add(&a10);
	gyujtemeny.add(&a11);


	gyujtemeny.evbe_kiir(2023); // éves nézet, két nap kell legyen ami lila (Jan 1 és Márc 15)
	gyujtemeny.honapba_kiir(2023, 10); // Csak hónapot írunk, itt 1-je kék plusz 23.-a piros
	gyujtemeny.listaz(); //napok kiírása hogy könnyebb legyen ellenőrizni ( itt lesz egy 2001 es is )
	gyujtemeny.listaz(2023); //Csak a 2023 as létrehozott napok kiírása
	
	//Január egyek nézése (nálam nem hétfő mind, helyesen működik nálam)
	//Uncommenteléssel működőképes lesz

	/*
	std::cout << "\n\nsok ev elso napja, nem hetfo mind: \n" << std::endl;
	Nap a(2024,1,1);
	Nap b(2023,1,1);
	Nap c(2022,1,1);
	Nap d(2021,1,1);
	Nap e(2020,1,1);
	Nap f(2019,1,1);
	Nap g(2018,1,1);
	Nap h(2017,1,1);
	Nap i(2016,1,1);
	Nap j(2015,1,1);
	Nap k(2014,1,1);
	Nap l(2013,1,1);
	Nap m(2012,1,1);
	gyujtemeny.add(&a);
	gyujtemeny.add(&b);
	gyujtemeny.add(&c);
	gyujtemeny.add(&d);
	gyujtemeny.add(&e); 
	gyujtemeny.add(&f); 
	gyujtemeny.add(&g); 
	gyujtemeny.add(&h); 
	gyujtemeny.add(&i);
	gyujtemeny.add(&j);
	gyujtemeny.add(&k);
	gyujtemeny.add(&l);
	gyujtemeny.add(&m);
	Nap n(5, 1, 1);
	Nap o;
	gyujtemeny.add(&n);
	gyujtemeny.add(&o);
	
	for (size_t i = 0; i < gyujtemeny.size(); i++) {
		std::cout << "\t" << gyujtemeny[i] << ": " << gyujtemeny[i].melyiknap() << std::endl;
	}
	*/

	return 0;
}
