#ifndef RELATIVEBY_H
#define RELATIVEBY_H

#include "types.h"
#include <string>

namespace webdriverxx {

class ConnectionType {
public:
    ConnectionType(uint64_t mask) : mask_(mask) {}

    void setMask() { mask_ = mask; }
	uint64_t getMask() { return mask_; }
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

	ConnectionType getNetworkConnection() {
		//return ConnectionType(resource_->GetString("getNetworkConnection"));
	}

	ConnectionType setNetworkConnection(ConnectionType network) {
		std::string mode = std::to_string(network.getMask());
		//mode = is_instance(network) ? : network;
		// test pls
		//return
	}
private:
    ConnectionType ALL_NETWORK;
    ConnectionType WIFI_NETWORK;
    ConnectionType DATA_NETWORK;
    ConnectionType AIRPLANE_MODE;
};

} // namespace webdriverxx

#endif // RELATIVEBY_H
