typedef struct{
    float x;
    float y;
    float z;
}vertex;
typedef struct{
    char* name;
    vertex* vertices;
    unsigned int vertexAmount;
    unsigned int* edges[3];
    unsigned int edgeAmount;
    unsigned int** areas;
    unsigned int areAmount;
    vertex center;
    int id;
}object;
typedef struct{
    char* name;
    object* objects;
    unsigned int objectAmount;
    char** objectNames;
}scene;

