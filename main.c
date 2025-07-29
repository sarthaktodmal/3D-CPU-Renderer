#include"Core.h"
#include<stdio.h>
#include<math.h>
#include <time.h>
#include<stdlib.h>

const uint32 width = 600;
const uint32 height = 600;

//Square
Vector pos[] = 
{
    {-0.5,0.5,-0.5},
    {0.5,0.5,-0.5},
    {0.5,-0.5,-0.5},
    {-0.5,-0.5,-0.5},

    {-0.5,0.5,0.5},
    {0.5,0.5,0.5},
    {0.5,-0.5,0.5},
    {-0.5,-0.5,0.5}
};

uint32 indices[] = {
    // Back face (-Z)
    0, 2, 1,
    0, 3, 2,
    // Right face (+X)
    1, 6, 5,
    1, 2, 6,
    // Top face (+Y)
    0, 5, 4,
    0, 1, 5,
    // Left face (-X)
    3, 4, 7,
    3, 0, 4,
    // Bottom face (-Y)
    2, 7, 6,
    2, 3, 7,
    // Front face (+Z)
    5, 7, 4,
    5, 6, 7
};
/*
//sphere

Vector pos[] = {
    { -0.525731f, 0.000000f, 0.850651f },
    { 0.525731f, 0.000000f, 0.850651f },
    { -0.525731f, 0.000000f, -0.850651f },
    { 0.525731f, 0.000000f, -0.850651f },
    { 0.000000f, 0.850651f, 0.525731f },
    { 0.000000f, 0.850651f, -0.525731f },
    { 0.000000f, -0.850651f, 0.525731f },
    { 0.000000f, -0.850651f, -0.525731f },
    { 0.850651f, 0.525731f, 0.000000f },
    { -0.850651f, 0.525731f, 0.000000f },
    { 0.850651f, -0.525731f, 0.000000f },
    { -0.850651f, -0.525731f, 0.000000f },
    { -0.309017f, 0.500000f, 0.809017f },
    { 0.309017f, 0.500000f, 0.809017f },
    { 0.000000f, 0.000000f, 1.000000f },
    { -0.809017f, 0.309017f, 0.500000f },
    { -0.500000f, 0.809017f, 0.309017f },
    { -0.500000f, 0.809017f, -0.309017f },
    { 0.000000f, 1.000000f, 0.000000f },
    { 0.500000f, 0.809017f, -0.309017f },
    { 0.500000f, 0.809017f, 0.309017f },
    { 0.809017f, 0.309017f, 0.500000f },
    { 1.000000f, 0.000000f, 0.000000f },
    { 0.809017f, -0.309017f, 0.500000f },
    { 0.809017f, 0.309017f, -0.500000f },
    { 0.809017f, -0.309017f, -0.500000f },
    { 0.309017f, 0.500000f, -0.809017f },
    { -0.309017f, 0.500000f, -0.809017f },
    { 0.000000f, 0.000000f, -1.000000f },
    { -0.309017f, -0.500000f, -0.809017f },
    { 0.309017f, -0.500000f, -0.809017f },
    { 0.500000f, -0.809017f, -0.309017f },
    { 0.000000f, -1.000000f, 0.000000f },
    { 0.500000f, -0.809017f, 0.309017f },
    { -0.500000f, -0.809017f, -0.309017f },
    { -0.500000f, -0.809017f, 0.309017f },
    { -0.809017f, -0.309017f, 0.500000f },
    { -0.309017f, -0.500000f, 0.809017f },
    { 0.309017f, -0.500000f, 0.809017f },
    { -1.000000f, 0.000000f, 0.000000f },
    { -0.809017f, -0.309017f, -0.500000f },
    { -0.809017f, 0.309017f, -0.500000f },
};
uint32 indices[] = {
    0, 12, 14,
    4, 13, 12,
    1, 14, 13,
    12, 13, 14,
    0, 15, 12,
    9, 16, 15,
    4, 12, 16,
    15, 16, 12,
    9, 17, 16,
    5, 18, 17,
    4, 16, 18,
    17, 18, 16,
    4, 18, 20,
    5, 19, 18,
    8, 20, 19,
    18, 19, 20,
    4, 20, 13,
    8, 21, 20,
    1, 13, 21,
    20, 21, 13,
    8, 22, 21,
    10, 23, 22,
    1, 21, 23,
    22, 23, 21,
    8, 24, 22,
    3, 25, 24,
    10, 22, 25,
    24, 25, 22,
    5, 26, 19,
    3, 24, 26,
    8, 19, 24,
    26, 24, 19,
    5, 27, 26,
    2, 28, 27,
    3, 26, 28,
    27, 28, 26,
    2, 29, 28,
    7, 30, 29,
    3, 28, 30,
    29, 30, 28,
    7, 31, 30,
    10, 25, 31,
    3, 30, 25,
    31, 25, 30,
    7, 32, 31,
    6, 33, 32,
    10, 31, 33,
    32, 33, 31,
    7, 34, 32,
    11, 35, 34,
    6, 32, 35,
    34, 35, 32,
    11, 36, 35,
    0, 37, 36,
    6, 35, 37,
    36, 37, 35,
    0, 14, 37,
    1, 38, 14,
    6, 37, 38,
    14, 38, 37,
    6, 38, 33,
    1, 23, 38,
    10, 33, 23,
    38, 23, 33,
    9, 15, 39,
    0, 36, 15,
    11, 39, 36,
    15, 36, 39,
    9, 39, 41,
    11, 40, 39,
    2, 41, 40,
    39, 40, 41,
    9, 41, 17,
    2, 27, 41,
    5, 17, 27,
    41, 27, 17,
    7, 29, 34,
    2, 40, 29,
    11, 34, 40,
    29, 40, 34,
};


//Character
Vector pos[] = {
    // Torso cube (centered)
    {-0.5, -0.5, -0.2}, {0.5, -0.5, -0.2}, {0.5, 0.5, -0.2}, {-0.5, 0.5, -0.2},
    {-0.5, -0.5, 0.2},  {0.5, -0.5, 0.2},  {0.5, 0.5, 0.2},  {-0.5, 0.5, 0.2},

    // Head cube (above torso)
    {-0.3, 0.5, -0.2}, {0.3, 0.5, -0.2}, {0.3, 0.9, -0.2}, {-0.3, 0.9, -0.2},
    {-0.3, 0.5, 0.2},  {0.3, 0.5, 0.2},  {0.3, 0.9, 0.2},  {-0.3, 0.9, 0.2},

    // Left arm cube (left side)
    {-0.8, -0.4, -0.15}, {-0.5, -0.4, -0.15}, {-0.5, 0.4, -0.15}, {-0.8, 0.4, -0.15},
    {-0.8, -0.4, 0.15},  {-0.5, -0.4, 0.15},  {-0.5, 0.4, 0.15},  {-0.8, 0.4, 0.15},

    // Right arm cube (right side)
    {0.5, -0.4, -0.15}, {0.8, -0.4, -0.15}, {0.8, 0.4, -0.15}, {0.5, 0.4, -0.15},
    {0.5, -0.4, 0.15},  {0.8, -0.4, 0.15},  {0.8, 0.4, 0.15},  {0.5, 0.4, 0.15},

    // Left leg cube (below torso)
    {-0.4, -0.9, -0.15}, {-0.1, -0.9, -0.15}, {-0.1, -0.5, -0.15}, {-0.4, -0.5, -0.15},
    {-0.4, -0.9, 0.15},  {-0.1, -0.9, 0.15},  {-0.1, -0.5, 0.15},  {-0.4, -0.5, 0.15},

    // Right leg cube (below torso)
    {0.1, -0.9, -0.15}, {0.4, -0.9, -0.15}, {0.4, -0.5, -0.15}, {0.1, -0.5, -0.15},
    {0.1, -0.9, 0.15},  {0.4, -0.9, 0.15},  {0.4, -0.5, 0.15},  {0.1, -0.5, 0.15},
};

#define CUBE(i) \
    i+0,i+1,i+2, i+0,i+2,i+3, \
    i+4,i+7,i+6, i+4,i+6,i+5, \
    i+0,i+4,i+5, i+0,i+5,i+1, \
    i+1,i+5,i+6, i+1,i+6,i+2, \
    i+2,i+6,i+7, i+2,i+7,i+3, \
    i+4,i+0,i+3, i+4,i+3,i+7

uint32 indices[] = {
    CUBE(0),    // Torso
    CUBE(8),    // Head
    CUBE(16),   // Left Arm
    CUBE(24),   // Right Arm
    CUBE(32),   // Left Leg
    CUBE(40),   // Right Leg
};
*/


float ar = (float)width / (float)height;
float ff = 1.0;

Vector Perspective_Projection(Vector* toaply)
{
    Vector ret;
    ret.x = (toaply->x * (ff / ar)) / toaply->z;
    ret.y = (toaply->y*ff) / toaply->z;
    ret.z = toaply->z;
    return ret;
}
Vector scale = (Vector){20,20,20};
void ApplyScaling(Vector* vertices)
{
    vertices->x = vertices->x * scale.x;
    vertices->y = vertices->y * scale.y;
    vertices->z = vertices->z * scale.z;
}
void ApplyRotation(Vector* vertices, Vector rotation)
{
    //Rotation
    //X
    Vector temp;   
    float angl = rotation.x;
    float radangl = ((angl*0.5f) * 3.141592653f) / 180.0f;
    float sinrad = sin(radangl);
    float cosrad = cos(radangl);

    temp.y = ((*vertices).y*cosrad) - ((*vertices).z*sinrad);
    temp.z = ((*vertices).y*sinrad) + ((*vertices).z*cosrad);

    (*vertices).y = temp.y;
    (*vertices).z = temp.z;
  
    //Y
    angl = rotation.y;
    radangl = ((angl*0.5f) * 3.141592653f) / 180.0f;
    sinrad = sin(radangl);
    cosrad = cos(radangl);

    temp.x = ((*vertices).x*cosrad) + ((*vertices).z*sinrad);
    temp.z = ((-(*vertices).x)*sinrad) + ((*vertices).z*cosrad);

    (*vertices).x = temp.x;
    (*vertices).z = temp.z;

    //Z
    angl = rotation.z;
    radangl = ((angl*0.5f) * 3.141592653f) / 180.0f;
    sinrad = sin(radangl);
    cosrad = cos(radangl);

    temp.x = ((*vertices).x*cosrad) - ((*vertices).y*sinrad);
    temp.y = ((*vertices).x*sinrad) + ((*vertices).y*cosrad);

    (*vertices).x = temp.x;
    (*vertices).y = temp.y;
}
Vector rot = (Vector){0,0,0};


GRAPHI graphi;
void WhileRunning()
{
    Clear_Graphi(RGBA(0,0,0,0),&graphi);
    DrawMesh(&graphi);
    rot.y += 0.2f;
    rot.x += 0.2f;
    rot.z += 0.2f;
}
void VertexShader(Vector *vert)
{
    ApplyRotation(vert, rot);
    (*vert) = Add_Vector((*vert), SetVector(0,0,4));
    ApplyScaling(vert);
    (*vert) = Perspective_Projection(vert);
}


// Function to generate genColor[] filled with random colors from color2[]
void generateRandomColorArray(uint32* genColor, int n, uint32* color2, int colorCount) {
    
    for (int i = 0; i < n; ++i) {
        int randomIndex = rand() % colorCount;
        genColor[i] = color2[randomIndex];
    }
}
int main()
{
    // Generate Random colors
    uint32 color2[] = {
        RGBA(255,   0,   0, 255), // Red
        RGBA(  0, 255,   0, 255), // Green
        RGBA(  0,   0, 255, 255), // Blue

        RGBA(255, 255,   0, 255), // Yellow
        RGBA(  0, 255, 255, 255), // Cyan
        RGBA(255,   0, 255, 255), // Magenta

        RGBA(255, 165,   0, 255), // Orange
        RGBA(128,   0, 128, 255), // Purple
        RGBA(165,  42,  42, 255), // Brown
        RGBA(  0, 128, 128, 255), // Teal
        RGBA(128, 128,   0, 255), // Olive
        RGBA(128, 128, 128, 255), // Gray
        RGBA(255, 255, 255, 255), // White
    };

    srand((unsigned int)time(NULL));
    int colorCount = sizeof(color2) / sizeof(color2[0]);
    int n = (sizeof(indices)/sizeof(uint32))/3;
    uint32* genColor = malloc(n * sizeof(uint32));
    if (!genColor) return -1;

    generateRandomColorArray(genColor, n,color2,colorCount);

    Mesh m;
    m.vertices = pos;
    m.vertcount = sizeof(pos)/sizeof(Vector);
    m.indices = indices;
    m.indcount = sizeof(indices)/sizeof(uint32);
    m.color = genColor;

    Create_Graphi_Window(width,height,"Sarthak",&graphi);


    Export_Mesh(&m,1,&graphi);
    Render(&graphi);
    Destroy_Graphi(&graphi);
    return 0;
}