#ifndef DEVICE_H
#define DEVICE_H

#include "arch/x64/processor.hh"
#include "drivers/pci.hh"
#include <ostream>
#include <unordered_map>

using namespace processor;

class Device {
public:
    Device(u16 id, u16 vid) :_id(id), _vid(vid) {};

    bool isPresent();
    u16 getStatus();
    void setStatus(u16 s);
    void dumpConfig() const;
    u16 getid() const {return _id;};
    u16 getvid() const {return _vid;};
    u8 getBus() const {return _bus;};
    void setBus(u8 bus) {_bus = bus;};
    u8 getSlot() const {return _slot;};
    void setSlot(u8 slot) {_slot=slot;};
    u8 getFunc() const {return _func;};
    void setFunc(u8 func) {_func=func;};

    friend std::ostream& operator <<(std::ostream& out, const Device &d);
    struct equal {
      bool operator()(const Device* d1, const Device* d2) const
      {
        return (d1->_id == d2->_id && d1->_vid == d2->_vid);
      }
    };

    struct hash : std::unary_function< const Device*, std::size_t> {
        std::size_t operator() ( const Device* const key ) const {
           return (size_t)(key->_id + key->_vid);
        }
    };


private:
    u16 _id;
    u16 _vid;
    u8 _bus, _slot, _func;
};

#endif
