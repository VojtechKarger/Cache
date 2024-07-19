#ifndef CacheImpl_hpp
#define CacheImpl_hpp
#include "../RingBuffer/RingBuffer.hpp"
#include "../HttpResponse.h"
#include "Cache.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <optional>

constexpr size_t capacity = 10;

class RingBufferCache: public Cache {
    typedef RingBuffer<std::pair<Key, Content>, capacity> Buffer;
    
public:
    
    std::optional<Content> item(const Key & key) override;
    void setItem(const Content & item, const Key & key) override;
    void remove(const Key & key) override;
    
private:
    std::vector<Buffer> buffers;
};

#endif /* CacheImpl_hpp */
