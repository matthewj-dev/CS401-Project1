/* 	  
 * Project 1 -- AArray abstract class	
 *************************************** 	  
 *
 * This is an abstract class defining behaviors (methods, member functions) 	  
 * and properties (fields, data members) that our arrays will have in common.
 * Look for instances of "TODO" and finish this class.  	
 * 	  
 ****************************************** 	  
 */  	


#pragma once 

#include "IArray.h" 

 
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


// This is an abstract class we can extend
// on which to base AArray subclasses
template<typename T>
class AArray
    : public IArray<T> 	  
{ 
protected:  	
    T* buffer;  	
    unsigned count; 	  

public: 	  
    // A default constructor 
    AArray() 
        : buffer(0), count(0)  	
    {  	
    }  	

    // A copy constructor 	  
    AArray(const AArray<T>& other) 
        : buffer(0), count(0) 
    { 
        insert(other,0); 
    } 	  

    // A virtual destructor 
    virtual ~AArray()
    {
        // Clear the array  	
        clear();  	
    } 

    // Member functions for inserting an element/array at a given index
    virtual void insert(const T& elem, unsigned pos) = 0; 	  
    virtual void insert(const IArray<T>&, unsigned pos) = 0;  	

    // Member function for appending a new element to the front
    virtual void push_front(const T& elem)  	
    { 	  
        insert(elem,0); 	  
    }  	

    // Member function for appending a new element to the back 	  
    virtual void push_back(const T& elem) 	  
    {  	
        insert(elem,size());	
    }  	
  	
    // A method for looking up an existing value in the array
    virtual int find(const T& elem) const  	
    {  	
        for (unsigned i = 0; i < size(); ++i)	
            if ((*this)[i] == elem)  	
                return i;
        return -1; 	  
    } 	  

    // A method for returning if an element exists in the array  	
    virtual bool contains(const T& elem) const 	  
    { 	  
        if (find(elem) >= 0) 
            return true; 	  
        else
            return false; 	  
    } 

    // Methods for erasing by position/number  	
    virtual void remove(unsigned pos, unsigned num) = 0; 

    // Method for getting a reference to an element at a particular index
    virtual T& operator [](unsigned pos) 
    { 
        if (!buffer || pos >= size()) 
            throw IArray<T>::ARRAY_OVERFLOW; 	  
        return buffer[pos];  	
    }  	

    // Method for getting a const reference to an element at a particular index
    virtual const T& operator [](unsigned pos) const 	  
    {
        if (!buffer || pos >= size())
            throw IArray<T>::ARRAY_OVERFLOW;
        return buffer[pos]; 	  
    } 	  
 	  
    // Method for assigning to an exisitng Array	
    virtual void operator =(const IArray<T>& other)  	
    {
        clear();  	
        insert(other,0);
    } 	  

    // Method for clearing an existing array and setting size=0 
    virtual void clear()  	
    {  	
        if (buffer) 	  
            delete [] buffer; 
        buffer = 0;  	
        count = 0; 	  
    }

    // Method for determining equality of two arrays
    virtual bool operator ==(const IArray<T>& other) const 	  
    { 	  
        for (unsigned i = 0; i < other.size(); ++i)
            if ((*this)[i] != other[i]) 	  
                return false;
        return true;
    }
 	  
    // Method for determining inequality of two arrays  	
    virtual bool operator !=(const IArray<T>& other) const
    {  	
        // calls == and returns the inverse 
        // This is the same as !((*this) == other)  	
        return !this->operator ==(other);  	
    }  	

    // A method for reporting the current number of elements in the array 	  
    virtual unsigned size() const
    {
        return count;	
    } 	  

    // An iterator for AArray instances
    class Iter
        : public IArray<T>::Iter
    {
        // TODO: write an iterator for AArrays;
        //       fully or partly implement it here?

    protected:
        AArray<T>* arr;
        int mark;
        int size;

    public:
        Iter():mark(0), size(0){}

        virtual void setArr(AArray<T>& input){
            arr = &input;
        }

        virtual void setSize(int length){
            size = length;
        }

        // Casting to bool reports if there are more values
        virtual operator bool() const {
            if(mark >= size){
                return false;
            }
            else {
                return true;
            }
        }

        // Operator prefix ++ increments the iterator
        virtual AArray<T>::Iter& operator ++(){
//            std::cout << mark << std::endl;
            mark++;
            return *this;
        }

        // Dereferencing an iterator will yield its current element
        virtual T& operator *()
        {
//            std::cout << mark << " " << arr->buffer[mark] << std::endl;
            return arr->buffer[mark];

        }
    }; 
};	



