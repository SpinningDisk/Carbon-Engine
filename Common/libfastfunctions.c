float fastCos(float deg){
    float rad = deg * (3.1415927410125732421875f/180.0f);
    
    const float c1 = 0.99940307f;
    const float c2 = -0.49558072f;
    const float c3 = 0.03679168f;
    float rad2 = rad * rad;
    return c1 + rad2 * (c2 + c3 * rad2);
}
float fastSin(float deg){
    deg = 90.0f-deg;
    float rad = deg * (3.1415927410125732421875f/180.0f);
    const float c1 = 0.99940307f;
    const float c2 = -0.49558072f;
    const float c3 = 0.03679168f;
    float rad2 = rad * rad;
    return c1 + rad2 * (c2 + c3 * rad2);
}
float fastTan(float deg){
    return fastSin(deg)/fastCos(deg);
}
