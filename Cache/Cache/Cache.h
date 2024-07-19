#ifndef Cache_h
#define Cache_h
#include <memory>

class Cache {
public:
    typedef HttpResponse Content;
    typedef std::string Key;

    virtual ~Cache() {};
    
    virtual std::optional<Content> item(const Key & key) = 0;
    virtual void setItem(const Content & item, const Key & key) = 0;
    virtual void remove(const Key & key) = 0;
};

typedef std::shared_ptr<Cache> SptrCache;

#endif /* Cache_h */
