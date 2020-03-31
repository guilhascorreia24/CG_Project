#include "stdio.h"





int main(){
unsigned int vertexIndex[3], normalIndex[3];
int matches = scanf("%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
if (matches != 6){
    printf("File can't be read by the parser, Try exporting with other options , value = %d\n",matches);
    return false;
}
printf("SUCCESS\n");
}