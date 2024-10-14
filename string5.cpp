/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelő
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetőknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 *
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterből (createString)
///                egy nullával lezárt char sorozatból (createString)

String::String(const char c) {
	len = 1;
	pData = new char[len + 1];
	pData[0] = c;
	pData[1] = '\0';

}

String::String(const char* s) {
	len = strlen(s);
	pData = new char[len + 1];
	strcpy(pData, s);
}

/// Másoló konstruktor: String-ből készít (createString)

String::String(const String& s) {
	
	len = s.size();
	pData = new char[len + 1];
	strcpy(pData, s.c_str());
}

/// operator=

String String::operator=(const String& s) {
	if (this != &s) {
		delete[] pData;
		len = s.size();
		pData = new char[len + 1];
		strcpy(pData, s.c_str());
	}
	return *this;
}

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
	
String String::operator+(const char& c) const{
	String uj;
	uj.~String();
	uj.len = len + 1;
	uj.pData = new char[uj.size() + 1];
	strcpy(uj.pData, pData);
	uj.pData[len] = c;
	uj.pData[len + 1] = '\0';
	return uj;
}

///                 String-hez String-et ad (addString)

String String::operator+(const String& s) const {
	String uj;
	uj.~String();
	uj.len = len + s.size();
	uj.pData = new char[uj.size()+1];
	strcpy(uj.pData, pData);
	strcat(uj.pData, s.c_str());
	return uj;
}


String operator+(const char c, const String& s) {
	String uj;
	uj.~String();
	uj.len = s.size() + 1;
	uj.pData = new char[uj.size() + 1];
	uj.pData[0] = c;
	strcpy(uj.pData + 1, s.c_str());
	return uj;
}


/// Destruktor (disposeString)

String::~String() {
	delete[] pData;
}

/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!


char& String::operator[](size_t i) {
	if (i >= len)
		throw "CBYHDN";
	return pData[i];
}

const char& String::operator[](size_t i) const {
	if (i >= len)
		throw "CBYHDN";
	return pData[i];
}


/// << operator, ami kiír az ostream-re

std::ostream& operator<<(std::ostream& os, const String& s) {
	os << s.c_str();
	return os;
}


/// >> operátor, ami beolvas az istream-ről egy szót

std::istream& operator>>(std::istream& is, String& s) {
	is.flags(std::ios_base::skipws);
	char i;
	//bool olvas = false;
	while (is.get(i).flags(std::ios_base::skipws)) {
		if (i == ' ')
			break;
		else
			s = s + i;
	}
	/*while (is.get(i)) {
		if (!olvas && !std::isspace(i)) {
			s = s + i;
			olvas = true;
		}
		else if (olvas && std::isspace(i))
			break;
		else if (olvas && !std::isspace(i))
			s = s + i;
	}
		*/
	return is;
}


