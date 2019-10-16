#ifndef PLEXI_HELPER_HPP
#define PLEXI_HELPER_HPP

class PlexiGFXBackend {

public:
    virtual bool isSupported();

    virtual bool initBackend();
};

#endif