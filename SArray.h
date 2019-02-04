/*
 * Project 1 -- SArray reallocating array class (CS 401 and 501)	
 ***************************************  	
 *  	
 * Your job is to finish writing this class to suit the
 * set of tests provided. Be sure to read IArray.h and AArray.h 
 * before you begin. Your SArray class should improve on the 	  
 * efficiency of the CArray class by allocating a buffer twice 
 * as large when needed. Look for "TODO"s that you must complete.  	
 *  	
 ****************************************** 
 */ 


#pragma once  	

#include "AArray.h"
#include <string.h>


/*************************************** 	  
 * Honor pledge (please write your name.) 
 *  	
 * I **Matthew Jackson** have completed this code myself, without
 * unauthorized assistance, and have followed the academic honor code.  	
 * 
 * Edit the code below to complete your solution.	
 *
 ******************************************
 */ 	  

 
// This is a simple managed array class that will allocate  	
// new space to grow/shrink its buffer "under the hood"  	
template<typename T> 	  
class SArray  	
    : public AArray<T> 	  
{  	
private: 
    unsigned capacity; 

    // Use a private helper method to resize the current buffer? 
    void reallocate(unsigned cap) 	  
    { 
        // Write a helper method to determine new size?  	
        // cap = nextsize(cap); 
 
        // TODO: Reallocate the current buffer to be
        //       at least twice as large

        int newSize;

        // set cap +1 if empty, else double the capacity
        if(cap == 0){
            newSize = 1;
        }
        else {
            newSize = next_size(cap);
        }

        // indicate the new capacity
        capacity = newSize;

        // create temporary array
        T* temp = new T[newSize];

        // copy contents of old buffer into new sized array
        memcpy( temp, this->buffer, this->size() * sizeof(T) );

        // point to the new sized buffer
        delete [] this->buffer;
        this->buffer = temp;

    }

    // determine new size
    unsigned next_size(unsigned cap){return (cap * 2);}

public: 
    SArray() 
        : capacity(0) 	  
    {  	
    }
 
    SArray(const AArray<T>& other)
        : AArray<T>(other), capacity(0) 	  
    {
    }

    virtual ~SArray()  	
    { 	  
    }
 
    virtual void insert(const T& elem, unsigned pos) 	  
    {  	
        if (pos > this->size()) 	  
            throw IArray<T>::ARRAY_OVERFLOW;

        // TODO: write an insert method

        // make room for new element
        if((this->size() + 1) > capacity){reallocate(this->size());}

        // shift elements right
        memmove(&(this->buffer[pos+1]), &(this->buffer[pos]), sizeof(int) * (this->size() - (pos)));

        // insert the ele
        this->buffer[pos] = elem;

        // increment the size
        ++this->count;
    }  	

    virtual void insert(const IArray<T>& other, unsigned pos) 
    { 
        if (pos > this->size())
            throw IArray<T>::ARRAY_OVERFLOW;

        // account for 0 sized arrays and nulls
        if(!other.size())
            return;


        // TODO: write an insert method

        // make room for new element
        if((this->size() + other.size()) > capacity){reallocate(this->size() + other.size());}

        // shift right over other.size times
        memmove(&(this->buffer[pos+(other.size())]), &(this->buffer[pos]), sizeof(int) * (this->size() - (pos)));

        // insert other's buffer into this buffer
        memcpy(&(this->buffer[pos]), &(other[0]), sizeof(int) * other.size());

        // increment size by the new array's size
        this->count += other.size();
    }

    virtual void remove(unsigned pos, unsigned num = 1)
    { 
        // TODO: write a remove method
        if (pos+num > this->size())
            throw IArray<T>::ARRAY_OVERFLOW;

        // don't allow removing zero elements
        if(num == 0) return;

        // move elements to the left num number of times
        memmove(&(this->buffer[pos]), &(this->buffer[pos+num]), sizeof(int) * (this->size() - (pos)));

        // decrement both our size and total capacity
        this->count -= num;
        this->capacity -= num;
    }  	

    virtual void clear()  	
    {	
        this->AArray<T>::clear(); 	  
        // TODO: is this complete?
        capacity = 0;
    } 

    // An iterator for SArray instances
    class Iter 	  
        : public AArray<T>::Iter 	  
    {
        // TODO: Does more need to be implemented here?
    public:
        Iter(SArray<T>& input){
            AArray<T>::Iter::setArr(input);
            AArray<T>::Iter::setSize(input.size());
        }
    };  	
};