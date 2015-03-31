#include "bitstring.h"

Bitstring::Bitstring() : bits("")
{
}

Bitstring::Bitstring(std::string bits): bits(bits)
{
}

Bitstring::Bitstring(int decimalValue)
{
    bits = decToBin(decimalValue);
}

int Bitstring::asDecimal() const
{
    int val = 0;
    unsigned int toAdd = 1;

    for(int i = bits.length()-1; i > -1; i--)
    {
        if(bits.at(i) != ' ')
        {
            if(bits.at(i) == '1')
            {
                val += toAdd;
            }

            toAdd *= 2;
        }
    }

    return val;
}

int Bitstring::at(int index)
{
    if(index < 0 || index >= bits.length())
    {
        throw "Index out of range";
    }
    return (bits.at(index) == '0' ? 0 : 1);
}

std::string Bitstring::decToBin(int dec, std::string bin) const
{
    bin += (dec % 2 == 0 ? '0' : '1');
    if(dec <= 1)
    {
        return bin;
    }

    return decToBin(dec/2, bin);
}


/************************ Operators ****************************/
/************************ Arithmetic ***************************/
Bitstring operator+(Bitstring lhs, const Bitstring& rhs)
{
    lhs += rhs;
    return lhs;
}

Bitstring operator-(Bitstring lhs, const Bitstring& rhs)
{
    lhs -= rhs;
    return lhs;
}

Bitstring operator+(Bitstring lhs, const int& rhs)
{
    lhs += rhs;
    return lhs;
}

Bitstring operator-(Bitstring lhs, const int& rhs)
{
    lhs -= rhs;
    return lhs;
}

/************************ Boolean ****************************/
bool operator==(const Bitstring& lhs, const Bitstring& rhs)
{
    return lhs.asDecimal() == rhs.asDecimal();
}

bool operator!=(const Bitstring& lhs, const Bitstring& rhs)
{
    return !operator==(lhs,rhs);
}

bool operator< (const Bitstring& lhs, const Bitstring& rhs)
{
    return lhs.asDecimal() < rhs.asDecimal();
}

bool operator> (const Bitstring& lhs, const Bitstring& rhs)
{
    return operator<(rhs, lhs);
}

bool operator>=(const Bitstring& lhs, const Bitstring& rhs)
{
    return !operator<(lhs, rhs);
}

bool operator<=(const Bitstring& lhs, const Bitstring& rhs)
{
    return !operator>(lhs, rhs);
}
