#include "TemplateCache.hpp"
#include "../HttpResponse.h"
#include <optional>

std::optional<Cache::Content> RingBufferCache::item(const Key & key) {
    
    // this solution does not scale very well
    // to make it more scalable we can take advantage from multithreading
    // keep buffer size small and search through many of them at the same time
    for (auto & buffer : buffers) {
        for (const auto & item : buffer) {
            if (key == item.first) return std::make_optional(item.second);
        }
    }
    
    return std::nullopt;
}

void RingBufferCache::remove(const Key & key) {
    
    for (auto & buffer : buffers) {
        for (auto it = buffer.begin(); it != buffer.end(); ++it) {
            
            
            if ((*it).first == key) {
                buffer.remove(it);
                return;
            }
        }
    }
}

void RingBufferCache::setItem(const Content & response, const Key &key) {
    
    if (item(key) != std::nullopt) return;
    
    for (auto & buffer : buffers) {
        if (buffer.add(std::make_pair(key, response))) return;
    }
    
    Buffer buffer;
    buffer.add(std::make_pair(key, response));
    buffers.push_back(buffer);
}
