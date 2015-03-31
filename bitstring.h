#pragma once

#include <string>

class Bitstring
{
    private:
        std::string bits;
    public:
        Bitstring();
        Bitstring(std::string bits);
        Bitstring(int decimalValue);

        int asDecimal() const;
        int at(int index);

        inline int length() const {return bits.length();};
        inline std::string asString() const{return bits;};

        char& operator[](int idx){return bits.at(idx);};
        const char& operator[](int idx) const{return bits.at(idx);};

        Bitstring& operator+=(const Bitstring& rhs)
        {
            bits = decToBin(asDecimal() + rhs.asDecimal());
            return *this;
        }
        Bitstring& operator+=(const int rhs)
        {
            bits = decToBin(asDecimal() + rhs);
            return *this;
        }
        Bitstring& operator-=(const Bitstring& rhs)
        {
            bits = decToBin(asDecimal() - rhs.asDecimal());
            return *this;
        }
        Bitstring& operator-=(const int rhs)
        {
            bits = decToBin(asDecimal() - rhs);
            return *this;
        }

    private:
        std::string decToBin (int dec, std::string bin="") const;
};
