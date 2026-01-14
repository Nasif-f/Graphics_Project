#ifndef SCENARIO4_H
#define SCENARIO4_H

#include <GL/glut.h>
#include <math.h>

namespace Scenario4 {
    float boatX = -500.0f;
    bool isDayMode = true;

    void display() {
        // Sky
        glBegin(GL_POLYGON);
        if(isDayMode) glColor3ub(102, 204, 255); else glColor3ub(10, 10, 40);
        glVertex2f(0, 300); glVertex2f(1150, 300); glVertex2f(1150, 750); glVertex2f(0, 750);
        glEnd();

        // River
        glColor3ub(41, 169, 221);
        glBegin(GL_QUADS);
        glVertex2f(0, 0); glVertex2f(1150, 0); glVertex2f(1150, 300); glVertex2f(0, 300);
        glEnd();


    }

    void update() {

    }
}
#endif
