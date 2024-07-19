#include "RingBufferCache.hpp"
#include "../HttpResponse.h"
#include <optional>

std::optional<Cache::Content> RingBufferCache::item(const Key & key) {
   
    for (auto & buffer : buffers) {
        size_t invalidCnt = 0;
        for (const auto & item : buffer) {
            if (item.isValid()) break;
            invalidCnt++;
        }
        buffer.eraseItems(invalidCnt);
    }
    
    
    // this solution does not scale very well
    // to make it more scalable we can take advantage from multithreading
    // keep buffer size small and search through many of them at the same time
    for (auto & buffer : buffers) {
        for (const auto & item : buffer) {
            if (key == item.key) return std::make_optional(item.content);
        }
    }
    
    return std::nullopt;
}

void RingBufferCache::remove(const Key & key) {
    
    for (auto & buffer : buffers) {
        for (auto it = buffer.begin(); it != buffer.end(); ++it) {
            
            if ((*it).key == key) {
                buffer.remove(it);
                return;
            }
        }
    }
}

void RingBufferCache::setItem(const Content & response, const Key &key) {
    
    if (item(key) != std::nullopt) return;
    Item newItem = Item(key, response, std::time(nullptr) + cashableTimeInterval);
    
    // if there is space in the buffer or the last element is invalid add
    // the new element to that buffer if not than continue to the next buffer
    for (auto & buffer : buffers) {
        if (buffer.add(newItem)) return;
        if (buffer.isEmpty()) continue;
        
        Item & lastItem = buffer.first();
        if (lastItem.isValid()) continue;
        
        lastItem = newItem;
        buffer.rotate();
        return;
    }
    
    // if all the buffers have valid elements and are full then create new buffer
    Buffer buffer;
    buffer.add(newItem);
    buffers.push_back(buffer);
}

bool RingBufferCache::Item::isValid() const {
    return std::time(nullptr) < timestamp;
}
