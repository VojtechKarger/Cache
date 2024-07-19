#ifndef CacheImpl_hpp
#define CacheImpl_hpp
#include "../RingBuffer/RingBuffer.hpp"
#include "../HttpResponse.h"
#include "Cache.h"
#include <vector>
#include <string>
#include <optional>
#include <time.h>

constexpr size_t capacity = 10;
constexpr time_t cashableTimeInterval = 100;

class RingBufferCache: public Cache {
    
    struct Item {
        Item() = default;
        Item(Key key, Content content, std::time_t timestamp) : key(key), content(content), timestamp(timestamp) {}
        
        Key key;
        Content content;
        std::time_t timestamp; 
        
        bool isValid() const;
    };
    
    typedef RingBuffer<Item, capacity> Buffer;
    
public:
   
    RingBufferCache() = default;
    ~RingBufferCache() override = default;
    
    std::optional<Content> item(const Key & key) override;
    void setItem(const Content & item, const Key & key) override;
    void remove(const Key & key) override;
    
private:
    std::vector<Buffer> buffers;
};

#endif /* CacheImpl_hpp */
