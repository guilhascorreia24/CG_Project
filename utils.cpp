#include "utils.h"


AngleRotation::AngleRotation(float x_angle,float y_angle, float z_angle){
        setXRotation(x_angle);
        setYRotation(y_angle);
        setZRotation(z_angle);
}

bool loadObj(const char* filename, std::vector<glm::vec3>* vertices,std::vector<glm::vec2>* uvs,std::vector<glm::vec3>* normals){
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    FILE * file = fopen(filename, "r");
    if( file == NULL ){
        errorPrint("Impossible to open the file !\n");
        return false;
    }
    int s = 0;
    int line = 0;

    while(true){
        line++;
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        if ( strcmp( lineHeader, "s" ) == 0 ){
            int s_file = 0;
            int matches = fscanf(file, "%d\n", &s_file);
            if(matches == 1){
                s = s_file;
            }else{s = 0;}
        }else if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

            if(s == 0){
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if (matches != 9){
                    errorPrint("Error parsing, s = 1 line = %d\n",line);
                    fclose(file); 
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }else if(s == 1){
                int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
                if (matches != 6){
                    errorPrint("Error parsing, s = 1 line = %d\n",line);
                    fclose(file);
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }else{
                errorPrint("File can't be read by the parser s!= 1 and s!= 0: ( Try exporting with other options\n");
                return false;
            }
        }
    }

    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        vertices->push_back(vertex);
    }

    for( unsigned int i=0; i<uvIndices.size(); i++ ){
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 vertex = temp_uvs[ uvIndex-1 ];
        uvs->push_back(vertex);
    }

    for( unsigned int i=0; i<normalIndices.size(); i++ ){
        unsigned int uvIndex = normalIndices[i];
        glm::vec3 vertex = temp_normals[ uvIndex-1 ];
        normals->push_back(vertex);
    }
        debugPrint("Model %s with %d vertices\n",filename,vertices->size());
    fclose(file);
    return true;
}

int getFileSize(FILE * file){
    int curr = (int)fseek(file, 0, SEEK_CUR);
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek ( file , 0 , curr);
    return size;
}

void debugPrint(const char* format, ...){
    if(!PRINT_DEBUG){
        return;
    }
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
}

void errorPrint(const char* format, ...){
    if(!PRINT_ERRORS){
        return;
    }
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
}