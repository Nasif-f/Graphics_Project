#ifndef SCENARIO2_H
#define SCENARIO2_H

#include <GL/glut.h>

namespace Scenario2 {

    // --- Global Variables ---
    float angle = 0.0f; // For rotation

    // --- Initialization ---
    void init() {
        // Initialize variables if needed
        angle = 0.0f;
    }

    // --- Display Function ---
    void display() {
        // 1. Save the current matrix state
        glPushMatrix();

        // 2. Move to the center of your screen (1150/2, 750/2)
        glTranslatef(575.0f, 375.0f, 0.0f);

        // 3. Rotate the triangle
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        // 4. Draw the Triangle
        glBegin(GL_TRIANGLES);
            // Top Vertex (Red)
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(0.0f, 200.0f);

            // Bottom Left Vertex (Green)
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(-200.0f, -150.0f);

            // Bottom Right Vertex (Blue)
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex2f(200.0f, -150.0f);
        glEnd();

        // 5. Restore the matrix so other scenarios aren't affected
        glPopMatrix();
    }

    // --- Update Function (Animation) ---
    void update() {
        angle += 2.0f; // Rotate 2 degrees every frame
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
    }
    
    // --- Keyboard Handler (Optional placeholder) ---
    void handleKey(unsigned char key) {
        // No keys needed for the triangle yet
    }
}

#endif