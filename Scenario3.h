#ifndef SCENARIO3_H
#define SCENARIO3_H

#include <GL/glut.h>

namespace Scenario3 {
    float carPos = 1150.0f;
    float carSpeed = 5.0f;

    void display() {
        // Road
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(0, 50); glVertex2f(1150, 50); glVertex2f(1150, 200); glVertex2f(0, 200);
        glEnd();

        
    }

    void update() {
        
    }
}
#endif