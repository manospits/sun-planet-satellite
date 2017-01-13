#ifndef VISUALS_H
#define VISUALS_H

#define MIN_STARS 10
#define MAX_STARS 1000
#define POLYGON_NUM 9122
#define FNUM 18240
#define VNUM 9124


typedef struct Star {
    float radius;
    float x;
    float y;
    float z;
} Star;

class Stars {
    public:
        Stars();
        ~Stars();
        void DrawStars();

    private:
        int numOfStars;
        Star *starsArray;

};

struct point
{
    float x;
    float y;
    float z;
};

struct face
{
    int v[3];
    int vn[3];

};

struct model
{
    point obj_points[VNUM];
    point vn[POLYGON_NUM];
    face obj_faces[FNUM];
    int vertices;
    int faces;
};

//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the
// OpenGL context associated to a window.

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Keyboard(unsigned char key,int x,int y);

void Idle();

#endif
