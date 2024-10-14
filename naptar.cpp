#include "naptar.h"
#include <fstream>
#include <iomanip>



UnnepNapok::~UnnepNapok() {
	for (size_t i = 0; i < unnepnapok.gethossz(); i++) {
		delete unnepnapok[i];
	}
}

void UnnepNapok::kilistaz() {
	for (size_t i = 0; i < unnepnapok.gethossz(); i++) {
		std::cout << "\tXXXX" << "." << std::setw(2) << std::setfill('0') << unnepnapok[i]->getHonap() << "." << std::setw(2) << std::setfill('0') << unnepnapok[i]->getNap() << std::endl;
	}
}

void Napok::honapba_kiir(int ev, int honap) {
	std::cout << "Kis utmutato:\n\t\x1B[36mKek\033[0m: Foglalt\n\t\x1B[31mPiros\033[0m: Foglalt\n\t\x1B[35mLila\033[0m: Unnep es Foglalt\n";
	std::cout << "Az Ur " << ev << ". esztendejenek " << honap << ". honapja" << "\n\n";
	int jelenlegi = napSzam(1, honap, ev);
	bool talalt = false;
	bool unnep = false;
	if (jelenlegi == -1) {
		jelenlegi = 6;
	}
	int napokszama = NapSzamolo::getInstance().honapnapszam(honap - 1, ev);
	std::cout << "\n  ------------" << HonapNeve(honap - 1).c_str() << "------------- \n";
	std::cout << "  Het  Ke  Sze  Csu  Pen  Szo   Vas\n";

	int k;
	for (k = 0; k < jelenlegi; k++) {
		std::cout << "     ";
	}

	//keresunk foglaltat
	for (int i = 1; i <= napokszama; i++) {
		for (size_t z = 0; z < napok.gethossz(); z++) {
			Nap a = *napok[z];
			if ((a == Nap(ev, honap, i)) && (a.getFog() == true)) {
				//std::cout << "\x1B[36m" << std::setw(5) << i << "\033[0m";
				talalt = true;
				break;
			}
			else {
				talalt = false;
			}
		}

		//nincs foglalt, kiirjuk pirossal ha unnep, ha nem akkor unnepet flase-nak tekintjuk
		
		for (size_t z = 0; z < UnnepNapok::getInstance().unnepnapok.gethossz(); z++) {
			Nap b = Nap(ev, UnnepNapok::getInstance().unnepnapok[z]->getHonap(), UnnepNapok::getInstance().unnepnapok[z]->getNap());
			if (b == Nap(ev, honap, i)) {	
				unnep = true;
				//std::cout << "\x1B[31m" << std::setw(5) << i << "\033[0m";
				break;
			}
			else {
				unnep = false;
			}
		}

		//talalt, de nem unnep
		if (talalt && !unnep) {
			std::cout << "\x1B[36m" << std::setw(5) << i << "\033[0m";
		}
		else if (!talalt && unnep) {
			std::cout << "\x1B[31m" << std::setw(5) << i << "\033[0m";
		}
		else if (talalt && unnep) {
			std::cout << "\x1B[35m" << std::setw(5) << i << "\033[0m";
		}else if (k == 6 && !unnep) {
			std::cout << "\x1B[31m" << std::setw(5) << i << "\033[0m";
		} 
		else if (!unnep && !talalt) {
			std::cout << std::setw(5) << i;
		}
			
		if (++k > 6) {
			k = 0;
			std::cout << "\n";
		}
	}
	if (k) std::cout << std::endl;
	jelenlegi = k;
}



void Napok::listaz() {

	std::cout << "\n\nA letrehozott napok: \n\n";
	for (size_t i = 0; i < napok.gethossz(); i++){
		std::cout << "\t" << *napok[i] << "\tFoglalas oka (optional): " << napok[i]->getIndok() << std::endl;
	}
	std::cout << "\nEzen feluli unnepnapok, melyek jelolve lehetnek a kiirasnal: \n\n";
	UnnepNapok::getInstance().kilistaz();
	
}

void Napok::listaz(int ev) {

	std::cout << "\n\nA letrehozott napok " << ev << ". evre: \n\n";
	for (size_t i = 0; i < napok.gethossz(); i++) {
		if (napok[i]->getEv() == ev) {
			std::cout << "\t" << *napok[i] << "\tFoglalas oka (optional): " << napok[i]->getIndok() << std::endl;
		}
		
	}
	std::cout << "\nEzen feluli unnepnapok, melyek jelolve lehetnek a kiirasnal: \n\n";
	for (size_t i = 0; i < UnnepNapok::getInstance().unnepnapok.gethossz(); i++){
		std::cout << "\t" << std::setw(2) << std::setfill('0') << UnnepNapok::getInstance().unnepnapok[i]->getHonap() << "." << std::setw(2) << std::setfill('0') << UnnepNapok::getInstance().unnepnapok[i]->getNap() << "\tUnnep neve: " << UnnepNapok::getInstance().unnepnapok[i]->getIndok() << std::endl;
	}

}

void Napok::evbe_kiir(int ev) {
	std::cout << "Kis utmutato:\n\t\x1B[36mKek\033[0m: Foglalt\n\t\x1B[31mPiros\033[0m: Foglalt\n\t\x1B[35mLila\033[0m: Unnep es Foglalt\n";
	std::cout << "Az Ur " << ev << ". esztendejenek eves nezetes naptara" << "\n\n";
	int jelenlegi = napSzam(1, 1, ev);
	bool talalt = false;
	bool unnep = false;
	if (jelenlegi == -1) {
		jelenlegi = 6;
	}
	for (int i = 0; i < 12; i++) {
		int napokszama = NapSzamolo::getInstance().honapnapszam(i, ev);
		std::cout << "\n  ------------" << HonapNeve(i).c_str() << "------------- \n";
		std::cout << "  Het  Ke  Sze  Csu  Pen  Szo   Vas\n";
		int k;
		for (k = 0; k < jelenlegi; k++) {
			std::cout << "     ";
		}
		//keresunk foglaltat
		for (int j = 1; j <= napokszama; j++) {
			for (size_t z = 0; z < napok.gethossz(); z++) {
				Nap a = *napok[z];
				if ((a == Nap(ev, i + 1, j)) && (a.getFog() == true)) {
					talalt = true;
					break;
				}
				else {
					talalt = false;
				}
			}

			//nincs foglalt, kiirjuk pirossal ha unnep, ha nem akkor unnepet flase-nak tekintjuk
			for (size_t z = 0; z < UnnepNapok::getInstance().unnepnapok.gethossz(); z++) {
				Nap b = Nap(ev, UnnepNapok::getInstance().unnepnapok[z]->getHonap(), UnnepNapok::getInstance().unnepnapok[z]->getNap());
				if (b == Nap(ev, i + 1, j)) {
					unnep = true;
					break;
				}
				else {
					unnep = false;
				}
			}

			if (talalt && !unnep) {
				std::cout << "\x1B[36m" << std::setw(5) << j << "\033[0m";
			}
			else if (!talalt && unnep) {
				std::cout << "\x1B[31m" << std::setw(5) << j << "\033[0m";
			}
			else if (talalt && unnep) {
				std::cout << "\x1B[35m" << std::setw(5) << j << "\033[0m";
			}
			else if (k == 6 && !unnep) {
				std::cout << "\x1B[31m" << std::setw(5) << j << "\033[0m";
			}
			else if (!unnep && !talalt) {
				std::cout << std::setw(5) << j;
			}


			if (++k > 6) {
				k = 0;
				std::cout << "\n";
			}
		}
		if (k) std::cout << std::endl;
		jelenlegi = k;
	}
}