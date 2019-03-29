#ifndef REF_BASE_H
#define REF_BASE_H

class RefBase
{
    public:
        RefBase() : m_count(0) { }

        void incRefCount(){
            m_count++;
        }

        int decRefCount(){ //由于经常要判断-1后是否为0，所以直接返回--m_count比较方便
            return --m_count;
        }

        int getRefCount(){
            return m_count;
        }

        virtual ~RefBase() {}
        
    private:
        int m_count;        

};// class RefBase;

#endif
