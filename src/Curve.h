#include <atomic>

class Curve {

    public:
        virtual ~Curve() = 0;
        

    private:
        std::atomic<unsigned long long> id;
};
