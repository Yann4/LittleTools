#ifndef QUACK_H_
#define QUACK_H_

#include <iterator>
#include <list>
#include <algorithm>
#include <array>

#include <stdexcept>

#include <iostream>

template <class T>
class Quack
{
    private:
        std::list<T> data;
        typedef typename std::list<T>::iterator iter;

    public:
        Quack();

        void insert(T dat);
        std::array<T, 2u> poppop();
void print();
        inline bool empty(){return data.empty();};
    private:
        iter binarySearch(T toFind, iter min, iter max);
        iter linearSearch(T toFind);
};


template <class T>
void Quack<T>::print()
{
    for(iter i = data.begin(); i != data.end(); i++)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}

template <class T>
Quack<T>::Quack()
{
}

template <class T>
void Quack<T>::insert(T dat)
{
    if(data.empty())
    {
        data.push_back(dat);
    }
    else
    {
        data.insert(std::lower_bound(data.begin(), data.end(), dat), dat);
    }
}

template <class T>
std::array<T, 2u> Quack<T>::poppop()
{
    if(data.empty())
    {
        throw std::out_of_range("Empty quack");
    }else if(data.size() == 1)
    {
        throw std::range_error("One item left in the quack - Cannot form tuple");
    }else
    {
        std::array<T, 2u> d{{data.front(), data.back()}};
        data.pop_front();
        data.pop_back();
        return d;
    }
    
}

template <class T>
typename std::list<T>::iterator Quack<T>::linearSearch(T toFind)
{
    return std::find(data.begin(), data.end(), toFind);
}

template <class T>
typename std::list<T>::iterator Quack<T>::binarySearch(T toFind, iter min, iter max)
{
    if(data.empty())
    {
        return data.begin();
    }

    int length = std::distance(min, max);
    length /= 2;

    iter midpoint = min;
    std::advance(midpoint, length);

    if(midpoint == data.begin())
    {
        if(toFind > *midpoint)
        {
            return ++midpoint;
        }else
        {
            return midpoint;
        }
    }

    if(*midpoint > toFind)
    {
        iter temp = midpoint;
        temp--;
        if(*temp < toFind)
        {
            return midpoint;
        }
        if(midpoint != data.end())
        {
            midpoint--;
        }
        return binarySearch(toFind, min, midpoint);
    }else if(*midpoint < toFind)
    {
        iter temp = midpoint;
        temp++;
        if(*temp > toFind || temp == data.end())
        {
            return temp;
        }
        if(midpoint != data.begin())
        {
            midpoint++;
        }
        return binarySearch(toFind, midpoint, max);
        
    }else
    {
        return midpoint;
    }
}
#endif //QUACK_H_
