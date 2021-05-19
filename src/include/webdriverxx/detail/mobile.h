#ifndef RELATIVEBY_H
#define RELATIVEBY_H

#include <string>

namespace webdriverxx {

class ConnectionType {
public:
    ConnectionType(uint64_t mask) : mask_(mask) {}

    void setMask() { mask_ = mask; }
    bool getAirplaneMode() { return (mask_ % 2) == 1; }
    bool getWifi() { return (mask_ % 2) == 1; }
    bool getData() { return (mask_ / 4) > 0; }
private:
    uint64_t mask_;
};

class Mobile {
public:
    Mobile()  {
        // TODO: this is not happy end (͡° ͜ʖ ͡°)
    }
private:
    ConnectionType ALL_NETWORK;
    ConnectionType WIFI_NETWORK;
    ConnectionType DATA_NETWORK;
    ConnectionType AIRPLANE_MODE;
};

} // namespace webdriverxx

#endif // RELATIVEBY_H
