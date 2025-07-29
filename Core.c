#include"Core.h"

#include<stdlib.h>
#include"winmain.h"
#include<stdlib.h>
#include<math.h>
#include<float.h> // for FLT_MAX

uint32 RGBA(uint8 r, uint8 g, uint8 b, uint8 a)
{
    uint8 ptr2[4];
    ptr2[0] = b;
    ptr2[1] = g;
    ptr2[2] = r;
    ptr2[3] = a;
    return *((uint32*)ptr2);
}
void getRGB(uint8 *r, uint8 *g, uint8 *b, uint8 *a, uint32* color)
{
    uint8 *rgb = (uint8*)color;
    *b = *rgb;
    *g = *(rgb+1);
    *r = *(rgb+2);
    *a = *(rgb+3);
}

Vector SetVector(float x, float y, float z) { return (Vector){x, y, z}; }
Vector Multiply_Vector(Vector vec1, Vector vec2)
{
    return SetVector(vec1.x*vec2.x,vec1.y*vec2.y,vec1.z*vec2.z);
}
Vector Add_Vector(Vector vec1, Vector vec2)
{
    return SetVector(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z);
}

int absINT(int a){
    return (a<0)?-a:a;
}
float absFLOAT(float a){
    return (a<0)?-a:a;
}

//----------------------------------------ACTUAL CORE----------------------------------------//

Window window;
uint32* Buffer;
float *zbuff;
uint32 _width;
uint32 _height;
uint32 resolution;
uint32 i, j;

Mesh* _mesh;
uint32 _meshcount = 0;

void Create_Graphi_Window(unsigned int width, unsigned int height, const char* title,GRAPHI* graphi)
{
    _width = width;
    _height = height;
    resolution = width * height;
    
    Initialize_Window(&window, width, height, title);
    Create_Window(&window);

    Buffer = (uint32*)malloc(resolution * sizeof(uint32));
    zbuff = (float*)malloc(resolution*sizeof(float));
}
void Destroy_Graphi(GRAPHI* graphi)
{
    free(_mesh);
    free(Buffer);
    free(zbuff);
    Destroy_Window(&window);
}
void Clear_Graphi(uint32 color, GRAPHI* graphi)
{
    for(i = 0; i < resolution; i++)
    {
        Buffer[i] = color;
        zbuff[i] = FLT_MAX;
    }
}
void Render(GRAPHI* graphi)
{
    while(ProcessMessages())
    {
        WhileRunning();
        PresentBuffer(&window, Buffer);
    }
}
void Export_Mesh(Mesh* mesh, uint32 meshcount, GRAPHI* graphi)
{
    _meshcount = meshcount;
    _mesh = (Mesh*)malloc(meshcount * sizeof(Mesh));
    for(i = 0; i < meshcount; i++)
    {
        _mesh[i] = mesh[i];
    }
}
void SetPixel(uint32 x, uint32 y, uint32 color)
{
    if(x>=0 && y >= 0 && x < _width && y < _height)
    Buffer[(_width*y)+x] = color;
}
Vector unit2pixel(Vector unit)
{
    if((unit.x <= 0.5f) && (unit.x >= -0.5f) && (unit.y <= 0.5f) && (unit.y >= -0.5f))
    {
        Vector ret;
        ret.x = (unit.x + 0.5f) * (_width-1);
        ret.y = (unit.y + 0.5f) * (_height-1);
        ret.z = unit.z;
        return ret;
    }
}

void RegisterPixel(int x, int y, float z, uint32 color)
{
    if(zbuff[(_width*y)+x] > z)
    {
        zbuff[(_width*y)+x] = z;
        Buffer[(_width*y)+x] = color;
    }
}

double near = 0.0;
double far = 100.0;

//--------------------------------TRIANGLE-----------------------------------//

//draw line ony in horizontal direction
void Render_H_Line(uint32 x1,uint32 x2,uint32 y, float z1, float z2, uint32 color){
    int dx = x2 - x1;
    char sx = (dx<0)?-1:1;
    float zinc = (z2-z1) / (float)absINT(dx);
    RegisterPixel(x1,y,z1,color);
    while(x1!=x2){
        x1 = x1 + sx;
        z1 += zinc;
        RegisterPixel(x1,y,z1,color);
    }
    RegisterPixel(x1,y,z1,color);
}
//RenderTriangle uses this function
void swap_uint32(uint32* a, uint32 *b){
    uint32 temp = *a;
    *a = *b;
    *b = temp;
}
void swap_float(float* a, float *b){
    float temp = *a;
    *a = *b;
    *b = temp;
}

void RenderTriangle(uint32 x1, uint32 y1, uint32 x2, uint32 y2, uint32 x3, uint32 y3, float z1, float z2, float z3, uint32 color){

    //swap vertices to make first vertex(x1,y1) having smallest y
    if(y2<y1 && y2<y3){
        swap_uint32(&x1,&x2);
        swap_uint32(&y1,&y2);
        swap_float(&z1,&z2);
    }
    if(y3<y1 && y3<y2){
        swap_uint32(&x1,&x3);
        swap_uint32(&y1,&y3);
        swap_float(&z1,&z3);
    }

    //convert z value between 0.0 -> 1.0
    {
        float divval = (far-near);
        z1 /= divval;
        z2 /= divval; 
        z3 /= divval;
    }

    //initialization for lines going in two direction/sides
    int dx = x2 - x1; char sx = (dx<0)?-1:1;
    int dy = y2 - y1; char sy = (dy<0)?-1:1;
    dx = dx*sx; dy = dy*sy;
    int dx2 = dx + dx; int dy2 = dy + dy;

    //for 2nd
    int dx_2 = x3 - x1; char sx_2 = (dx_2<0)?-1:1;
    int dy_2 = y3 - y1; char sy_2 = (dy_2<0)?-1:1;
    dx_2 = dx_2*sx_2; dy_2 = dy_2*sy_2;
    int dx2_2 = dx_2 + dx_2; int dy2_2 = dy_2 + dy_2;
    int x1_2 = x1;
    int y1_2 = y1;
    float z1_2 = z1;
    int di_2;
    float zinc_2;
    if(dx_2>dy_2){
        di_2 = dy2_2;
        zinc_2 = (z3-z1_2) / (float)absINT(dx_2);
    } else{
        di_2 = dx2_2;
        zinc_2 = (z3-z1_2) / (float)absINT(dy_2);
    } 
    //

    bool isdone = false;

    //first direction
    restart:
    if(dx>dy){
        int di = dy2;
        float zinc = (z2-z1) / (float)absINT(dx);
        RegisterPixel(x1,y1,z1,color);
        first:
        while(x1!=x2){
            z1 += zinc;
            if(di>dx){
                x1 = x1 + sx;
                y1 = y1 + sy;
                di = di - dx2 + dy2;

                if(dx_2>dy_2)goto second; else goto second_;
            }else{
                x1 = x1 + sx;
                di = di + dy2;
                RegisterPixel(x1,y1,z1,color);
            }
        }
        if(!isdone){
            isdone = true;
            dx = x3 - x1;  sx = (dx<0)?-1:1;
            dy = y3 - y1;  sy = (dy<0)?-1:1;
            dx = dx*sx; dy = dy*sy;
            dx2 = dx + dx;  dy2 = dy + dy;
            x2 = x3;
            y2 = y3;
            z2 = z3;
            goto restart;
        }
    }else{
        int di = dx2;
        float zinc = (z2-z1) / (float)absINT(dy);
        RegisterPixel(x1,y1,z1,color);
        first_:
        while(y1!=y2){
            z1 += zinc;
            if(di>dy){
                x1 = x1 + sx;
                y1 = y1 + sy;
                di = di - dy2 + dx2;
            }else{
                y1 = y1 + sy;
                di = di + dx2;
            }

            if(dx_2>dy_2)goto second; else goto second_;
        }
        if(!isdone){
            isdone = true;
            dx = x3 - x1;  sx = (dx<0)?-1:1;
            dy = y3 - y1;  sy = (dy<0)?-1:1;
            dx = dx*sx; dy = dy*sy;
            dx2 = dx + dx;  dy2 = dy + dy;
            x2 = x3;
            y2 = y3;
            z2 = z3;
            goto restart;
        }
    }
    return;
    //second direction
    restart2:
    if(dx_2>dy_2){
        di_2 = dy2_2;
        zinc_2 = (z3-z1_2) / (float)absINT(dx_2);
        second:
        while(x1_2!=x3){
            z1_2 += zinc_2;
            if(di_2>dx_2){
                x1_2 = x1_2 + sx_2;
                y1_2 = y1_2 + sy_2;
                di_2 = di_2 - dx2_2 + dy2_2;

                Render_H_Line(x1,x1_2,y1,z1,z1_2,color);
                if(dx>dy) goto first; else goto first_;
            }else{
                x1_2 = x1_2 + sx_2;
                di_2 = di_2 + dy2_2;
                RegisterPixel(x1_2,y1_2,z1_2,color);
            }
        }
        if(!isdone){
            isdone = true;
            dx_2 = x2 - x1_2;  sx_2 = (dx_2<0)?-1:1;
            dy_2 = y2 - y1_2;  sy_2 = (dy_2<0)?-1:1;
            dx_2 = dx_2*sx_2; dy_2 = dy_2*sy_2;
            dx2_2 = dx_2 + dx_2;  dy2_2 = dy_2 + dy_2;
            x3 = x2;
            y3 = y2;
            z3 = z2;
            goto restart2;
        }
    }else{
        di_2 = dx2_2;
        zinc_2 = (z3-z1_2) / (float)absINT(dy_2);
        second_:
        while(y1_2!=y3){
            z1_2 += zinc_2;
            if(di_2>dy_2){
                x1_2 = x1_2 + sx_2;
                y1_2 = y1_2 + sy_2;
                di_2 = di_2 - dy2_2 + dx2_2;
            }else{
                y1_2 = y1_2 + sy_2;
                di_2 = di_2 + dx2_2;
            }
            Render_H_Line(x1,x1_2,y1,z1,z1_2,color);
            if(dx>dy) goto first; else goto first_;
        }
        if(!isdone){
            isdone = true;
            dx_2 = x2 - x1_2;  sx_2 = (dx_2<0)?-1:1;
            dy_2 = y2 - y1_2;  sy_2 = (dy_2<0)?-1:1;
            dx_2 = dx_2*sx_2; dy_2 = dy_2*sy_2;
            dx2_2 = dx_2 + dx_2;  dy2_2 = dy_2 + dy_2;
            x3 = x2;
            y3 = y2;
            z3 = z2;
            goto restart2;
        }
    }
}

void DrawTriangles(Vector *pos, uint32 poscount, uint32* indices, uint32 indcount, uint32* color)
{
    uint32 i, trcount = indcount/3, counter;

    Vector* pos2 = (Vector*)malloc(poscount * sizeof(Vector));
    for(i = 0; i < poscount; i++)
    {
        pos2[i] = pos[i];
    }

    for(i = 0; i < poscount; i++)
    {
        VertexShader(&pos2[i]);
        pos2[i] = unit2pixel(pos2[i]);
    }
    counter = 0;
    for(i = 0; i < trcount; i++)
    {
        RenderTriangle(pos2[indices[counter]].x,pos2[indices[counter]].y, pos2[indices[counter+1]].x,pos2[indices[counter+1]].y, 
        pos2[indices[counter+2]].x, pos2[indices[counter+2]].y, pos2[indices[counter]].z, pos2[indices[counter+1]].z, 
        pos2[indices[counter+2]].z,color[i]);

        counter = counter + 3;
    }
    free(pos2);
}

void DrawMesh(GRAPHI* graphi)
{
    for(i = 0; i < _meshcount; i++)
    {
        DrawTriangles(_mesh[i].vertices, _mesh[i].vertcount, _mesh[i].indices, _mesh[i].indcount, _mesh[i].color);
    }
}
