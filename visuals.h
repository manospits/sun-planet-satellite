#ifndef VISUALS_H
#define VISUALS_H
#define MIN_STARS 10
#define MAX_STARS 100

typedef struct Star {
    float radius;
    float x;
    float y;
    float z;
    float transparecy;
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
