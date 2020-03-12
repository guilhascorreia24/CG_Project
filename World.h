#include <vector>
#include "Object.h"

class World{
    public:
        Object* getMainObject();

    private:
        std::vector<Object> objects;
};