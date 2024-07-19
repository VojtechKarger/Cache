#ifndef RingBuffer_hpp
#define RingBuffer_hpp
#include <array>
#include <iostream>
#include <optional>

template <typename T, size_t Capacity>
class RingBuffer {
public:
    
    RingBuffer() = default;
    ~RingBuffer() = default;
        
    class Iterator;
    
    bool add(T item) {
        if (size >= Capacity) return false;
        data[(startIndex + size++ % Capacity)] = item;
        return true;
    };
    
    T & first() {
        return data[startIndex];
    }
    
    bool isEmpty() const {
        return size == 0;
    }
   
    void rotate() {
        startIndex++;
    }
    
    void remove(size_t index) {
        remove(Iterator(*this, (startIndex + index) % Capacity));
    };
    
    void remove(const Iterator & it) {
        
        if (it.currentIndex == startIndex) {
            startIndex = (startIndex + 1) % Capacity;
            size--;
            return;
        }
        
        if (it.currentIndex == (startIndex + size - 1) % Capacity) {
            size--;
            return;
        }
        
        for (size_t index = it.currentIndex; index < startIndex + size; index++) {
            data[index % Capacity] = data[(index + 1) % Capacity];
        }

        size--;
        return;
    }
    
    Iterator begin() { return Iterator(*this, startIndex, size > 0); };
    Iterator end() { return Iterator(*this, (startIndex + size) % Capacity); };
    
    class Iterator {
    public:
        Iterator(RingBuffer<T, Capacity> & container, size_t currentIndex, bool isFirst = false) : data(container), currentIndex(currentIndex), isFirst(isFirst) {};
        
        Iterator & operator ++() {
            currentIndex = (currentIndex + 1) % Capacity;
            isFirst = false;
            return *this;
        };
        
        friend bool operator == (const Iterator & it1, const Iterator & it2) {
            return it1.currentIndex == it2.currentIndex && it1.isFirst == it2.isFirst;
        };
        
        friend bool operator != (const Iterator & it1, const Iterator & it2) { return !(it1 == it2); };
        
        T & operator *() { return data.data[currentIndex % Capacity]; };
        
        size_t currentIndex;
        bool isFirst;
    private:
        RingBuffer<T, Capacity> & data;
    };
    
private:
    size_t startIndex = 0;
    size_t size = 0;
    
    std::array<T, Capacity> data;
};

#endif /* RingBuffer_hpp */
