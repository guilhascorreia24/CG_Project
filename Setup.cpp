
#include "Setup.h"

Setup::Setup(){

}
Setup::~Setup(){
    unloadShaders();
}

void Setup::unloadShaders(){
    glUseProgram(0);
}

bool Setup::loadShaders(){

    

    //Create Program Shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
    bool frag = compileShader("shaders/shader.frag",GL_FRAGMENT_SHADER,&fragmentShader);
    bool vert = compileShader("shaders/shader.vert",GL_VERTEX_SHADER,&vertexShader);

    if(!frag || !vert)
        return false;

    //Atach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        errorPrint("Shaders link failed\n Aditional info %s\n",infoLog);
        return false;
    }

    glUseProgram(shaderProgram);
    
    //Free shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
    return true;
}

bool Setup::compileShader(const char* filename, int shaderType, unsigned int *shaderBuffer){
    FILE * file = fopen(filename, "r");
    if( file == NULL ){
        errorPrint("Impossible to open the shader file %s!\n",filename);
        return false;
    }

    int size = getFileSize(file);
    const char * sourceShader = (const char*)calloc(size+1,1);
    if((int)fread((void*)sourceShader,1,size,file)!=(int)size){
        errorPrint("Error reading Shader %s\n",filename);
        fclose(file);
        return false;
    }


    //Create shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(shaderType);

    //Atach shader source and compile
    glShaderSource(vertexShader, 1, &sourceShader, NULL);
    glCompileShader(vertexShader);

    //free((void*)sourceShader);

    //Check Compilation
    int  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        errorPrint("Shader %s compilation failed\n Aditional info %s\n",filename,infoLog);
        fclose(file);
        return false;
    }
    *shaderBuffer=vertexShader;
    fclose(file);
    return true;
}