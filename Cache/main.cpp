#include <iostream>
#include "RingBuffer/RingBuffer.hpp"
#include <assert.h>

void ringBufferTests() {
    RingBuffer<int, 6> buffer;
    
    assert(buffer.add(0));
    assert(buffer.add(1));
    assert(buffer.add(2));
    assert(buffer.add(3));
    assert(buffer.add(4));
    assert(buffer.add(5));
    assert(!buffer.add(6));
    
    for (auto it = buffer.begin(); it != buffer.end(); ++it) std::cout << *it;
    std::cout << std::endl;
    
    buffer.remove(1);
    buffer.add(1);
    buffer.remove(5);
    buffer.remove(2);
    buffer.remove(3);
    
    for (auto item : buffer) std::cout << item;
    std::cout << std::endl;
    
    assert(buffer.add(0));
    assert(buffer.add(1));
    assert(buffer.add(2));
    
    for (auto item : buffer) std::cout << item;
    std::cout << std::endl;
        
    buffer.eraseItems(1);
    
    for (auto item : buffer) std::cout << item;
    std::cout << std::endl;
    
    buffer.add(1);
    
    for (auto item : buffer) std::cout << item;
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ringBufferTests();
    return 0;
}


