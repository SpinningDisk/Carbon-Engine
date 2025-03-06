
/* 
Objects shall have a Name, and ID (for reference in Scenes), a type (e.g: solid, camera, light, beziér curve, etc.); 
a list of vertices (or just one, in case of cam, light, ...), a center (for repositioning), and a something I forgot
*/
typedef struct{
    char* Name;
    unsigned int type;
    float[4]* vertices;
}