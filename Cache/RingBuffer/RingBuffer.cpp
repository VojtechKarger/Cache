#include "RingBuffer.hpp"

template <typename T, size_t Capacity>
bool RingBuffer<T, Capacity>::add(T item) {
    if (size == Capacity) return false;
    
    data[startIndex + size % Capacity] = item;
    size++;
}
