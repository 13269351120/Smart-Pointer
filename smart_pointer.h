#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include "ref_base.h"

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

        ~SmartPointer()
        {
            if(m_pointer && m_pointer->decRefCount() == 0) 
                delete m_pointer;
        }

    private:
        T *m_pointer;
}; //class SmartPointer;

#endif
