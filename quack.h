#ifndef QUACK_H_
#define QUACK_H_

#include <iterator>
#include <list>
#include <tuple>

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
        std::tuple<T, T> poppop();
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
        data.insert(linearSearch(dat), dat);
        //data.insert(binarySearch(dat, data.begin(), data.end()), dat);
    }
}

template <class T>
std::tuple<T, T> Quack<T>::poppop()
{
    if(data.empty())
    {
        throw std::out_of_range("Empty quack");
    }else if(data.size() == 1)
    {
        throw std::range_error("One item left in the quack - Cannot form tuple");
    }else
    {
        std::tuple<T, T> d(data.front(), data.back());
        data.pop_front();
        data.pop_back();
        return d;
    }
    
}

template <class T>
typename std::list<T>::iterator Quack<T>::linearSearch(T toFind)
{
    if(data.empty())
    {
        return data.begin();
    }

    for(iter it = data.begin(); it != data.end();)
    {
        if(toFind > *it)
        {
            it++;
        }else
        {
            return it;
        }
    }
    return data.end();
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
