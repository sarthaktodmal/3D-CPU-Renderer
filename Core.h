#pragma once

#include"defines.h"

uint32 RGBA(uint8 r, uint8 g, uint8 b, uint8 a);

//----------------------------------------ACTUAL CORE----------------------------------------//

typedef struct GRAPHI { } GRAPHI;

typedef struct Vector { float x, y, z; } Vector;
Vector SetVector(float x, float y, float z);
Vector Multiply_Vector(Vector vec1, Vector vec2);
Vector Add_Vector(Vector vec1, Vector vec2);

typedef struct Mesh 
{ 
    Vector* vertices;
    uint32 vertcount;
    uint32* indices;
    uint32 indcount;
    uint32* color;
} Mesh;

void Create_Graphi_Window(unsigned int width, unsigned int height, const char* title, GRAPHI* graphi);
void Destroy_Graphi(GRAPHI* graphi);
void Render(GRAPHI* graphi);
void WhileRunning();
void Clear_Graphi(uint32 color, GRAPHI* graphi);

void Export_Mesh(Mesh* mesh, uint32 meshcount, GRAPHI* graphi);
void DrawMesh(GRAPHI* graphi);
void VertexShader(Vector *vert);