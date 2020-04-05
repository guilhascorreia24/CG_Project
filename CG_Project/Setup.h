#include "utils.h"

class Setup{
    
    
    public:
        Setup();
        ~Setup();

        bool loadShaders();
        void unloadShaders(); //Don't need to call, automatically done on destruction
        
    private:

        bool compileShader(const char* filename, int shaderType, unsigned int *shaderBuffer);
};