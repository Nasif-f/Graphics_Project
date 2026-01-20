#include <windows.h>
#include <GL/glut.h>
#include "Scenario1.h"
#include "Scenario2.h"
#include "Scenario3.h"
#include "Scenario4.h"

typedef enum { COVER, S1, S2, S3, S4 } State;
State currentState = COVER;

void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    switch (currentState) {
        case COVER:
            glClearColor(1, 1, 1, 1);
            glColor3f(0, 0, 0);
            renderText(450, 400, "Scenaries in Bangladesh");
            renderText(450, 350, "Press 1, 2, 3, or 4 to Start");
            break;
        case S1: Scenario1::display(); break;
        case S2: Scenario2::display(); break;
        case S3: Scenario3::display(); break;
        case S4: Scenario4::display(); break;
    }
    glutSwapBuffers();
}

void timer(int v) {

    if (currentState == S1) Scenario1::update();
    else if (currentState == S2) Scenario2::update();
    else if (currentState == S3) Scenario3::update();
    else if (currentState == S4) Scenario4::update();

    glutPostRedisplay();
    glutTimerFunc(20, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {


    if (key == '1') {
        currentState = S1;
        PlaySound("soothing-river-flow-372456.wav", NULL, SND_ASYNC | SND_LOOP);
    }
    else if (key == '2') {
        currentState = S2;
        PlaySound("car.wav", NULL, SND_ASYNC | SND_LOOP);
    }
    else if (key == '3') {
        currentState = S3;
        PlaySound(NULL, 0, 0);
    }
    else if (key == '4') {
        currentState = S4;
        PlaySound(NULL, 0, 0);
    }
    else if (key == 'w') {
        currentState = COVER;
        PlaySound(NULL, 0, 0);
    }
    else if (key == 'e' || key == 27) {
        exit(0);
    }


    else {
        if (currentState == S1) {
            Scenario1::handleKey(key);
        }
        else if (currentState == S2) {
            Scenario2::handleKey(key);
        }
         else if (currentState == S3) {
            Scenario3::handleKey(key);
        }
         else if (currentState == S4){
             Scenario4::handleKey(key);
         }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1150, 750);
    glutCreateWindow("Main Application");

    Scenario1::init();
    Scenario2::init();
    Scenario3::init();
    Scenario4::init();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1150, 0, 750);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(20, timer, 0);
    glutMainLoop();
    return 0;
}
