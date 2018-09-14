#include <atomic>
#include <vector>

#include "Curve.h"

class Layer {

    public:
        Layer();
        //Layer(std::vector<Layer*> children = , std::vector<Curve*> curves = );
        ~Layer();

        unsigned long long getID() { return this->id; };
        

    private:
        static std::atomic<unsigned long long> nextID;
        unsigned long long id;
        std::vector<Layer*> children;
        std::vector<Curve*> curves;
};
