#ifndef RingBuffer_hpp
#define RingBuffer_hpp
#include <array>

template <typename T, size_t Capacity>
class RingBuffer {
public:
    class Iterator;
    
    bool add(T item);
    
    void remove(size_t index);
    
    Iterator begin();
    Iterator end();
    
    class Iterator {
    public:
        Iterator(RingBuffer<T, Capacity> & container);
        
        Iterator & operator ++();
        friend bool operator == (const Iterator & it1, const Iterator & it2);
        friend bool operator != (const Iterator & it1, const Iterator & it2);
        T & operator *();
    private:
        RingBuffer<T, Capacity> & data;
    };
    
private:
    size_t startIndex;
    size_t size;
    
    std::array<T, Capacity> data;
};

#endif /* RingBuffer_hpp */
