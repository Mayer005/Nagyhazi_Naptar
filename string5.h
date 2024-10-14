#ifndef STRING_H
#define STRING_H


#include <iostream>
#include "memtrace.h"

class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lezáró nulla nélkül
public:

    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << '|' << std::endl;
    }

    String() :pData(new char[1]), len(0) {
        pData[0] = '\0';
    }

    size_t size() const { return len; }

    const char* c_str() const { return pData;}



    String(const char c);
    String(const char* s);
    String(const String& s);

    String operator=(const String& s);
    String operator+(const char& c) const;
    String operator+(const String& s) const;
    friend String operator+(const char c, const String& s);
    char& operator[](size_t i);
    const char& operator[](size_t i) const;

    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend std::istream& operator>>(std::istream& is, String& s);

    virtual ~String();


}; 








#endif
