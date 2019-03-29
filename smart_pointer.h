#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include "ref_base.h"
#define COMPARE(_op_)                          \
bool operator _op_ (const SmartPointer& p ) {   \
    return m_pointer _op_ p.m_pointer;          \
}                                               \
bool operator _op_ (const T* p ) {              \
    return m_pointer _op_ p;                    \
}                                               \

template <typename T>
class SmartPointer
{
    public:
        SmartPointer() : m_pointer(nullptr) { } 

        SmartPointer(T* p) : m_pointer(p) 
        { 
            if(m_pointer) m_pointer->incRefCount();
        }

        SmartPointer(const SmartPointer& other) : m_pointer(other.m_pointer)
        {
            if(m_pointer) m_pointer->incRefCount();
        }

        SmartPointer& operator = (const SmartPointer& other)
        {
            T* tmp = other.m_pointer;

            if(tmp) tmp->incRefCount();

            if(m_pointer && m_pointer->decRefCount() == 0) {
                 delete m_pointer;
            }
            m_pointer = tmp;
            return *this;
        }
        
        T& operator* () const { return *m_pointer; }

        T* operator-> () const { return m_pointer; }

        /*
        bool operator == (const T* p ) const
        {
            return m_pointer == p;
        } 

        bool operator == (const SmartPointer& other ) const 
        {
            return m_pointer == other.m_pointer;
        }

        bool operator != (const T* p ) const
        {
            return m_pointer != p;
        } 

        bool operator != (const SmartPointer& other ) const 
        {
            return m_pointer != other.m_pointer;
        }
        */
        COMPARE (==);
        COMPARE (!=);

        ~SmartPointer()
        {
            if(m_pointer && m_pointer->decRefCount() == 0) 
                delete m_pointer;
        }

    private:
        T *m_pointer;
}; //class SmartPointer;

#endif
