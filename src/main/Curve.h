#include <atomic>

class Curve {

public:
    virtual ~Curve() = 0;
    virtual unsigned long long getID() = 0;
    

private:
    std::atomic<unsigned long long> id;
};
