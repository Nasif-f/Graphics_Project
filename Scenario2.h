#ifndef SCENARIO2_H
#define SCENARIO2_H

#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>

#define PI 3.14159265358979323846

namespace Scenario2 {

    // --- Global Variables ---
    GLfloat car_position = 0.0f;
    GLfloat car_speed = 10;
    GLfloat cloud_Position = 0.0f;

    GLfloat sun_position = 0.0f;
    bool cloud_MovingRight = true;

    bool backimage_pointer = true;
    GLfloat bird_Position = 0.0f;
    bool bird_pointer = true;
    GLfloat angle = 180.0f;

    bool isPaused = false;


    // --- Helper Function
    void renderBitmapString(float x, float y, float z, void *font, const char *string) {
        const char *c;
        glRasterPos3f(x, y, z);
        for (c = string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }

    void drawCircle(float x, float y, float radius, float r, float g, float b) {
        int i;
        int triangleAmount = 100;
        float twicePi = 2.0f * PI;

        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y);
            for(i = 0; i <= triangleAmount; i++) {
                glVertex2f(
                    x + (radius * cos(i * twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount))
                );
            }
        glEnd();
    }

    void draw_bird(float r, float g, float b) {
        // Body
        glBegin(GL_POLYGON);
        glColor3f(r, g, b);
        glVertex2f(8+287, 6+580);
        glVertex2f(14.6171+287, 5.14569+580);
        glVertex2f(22.1048+287, 5.02227+580);
        glVertex2f(29.42794+287, 5.76281+580);
        glVertex2f(31.6907+287, 6.58564+580);
        glVertex2f(33.5832+287, 9.5478+580);
        glVertex2f(33.21293+287, 13.08595+580);
        glVertex2f(30.45647+287, 17.11778+580);
        glVertex2f(25.84865+287, 18.76343+580);
        glVertex2f(19.55405+287, 19.29827+580);
        glVertex2f(16.87987+287, 19.33941+580);
        glVertex2f(11.49037+287, 18.26974+580);
        glVertex2f(6.84141+287, 16.58295+580);
        glVertex2f(4.90778+287, 14.97844+580);
        glVertex2f(3.13871+287, 11.72829+580);
        glVertex2f(5.19577+287, 9.05411+580);
        glEnd();

        // Eye
        drawCircle(288, 594, 4, 0.0f, 0.0f, 0.0f);        // Black
        drawCircle(288, 594, 2.6f, 1.0f, 1.0f, 1.0f);     // White pupil

        // Beak
        glBegin(GL_POLYGON);
        glColor3f(0.15f, 0.15f, 0.15f);
        glVertex2f(33.21293-2+287, 13.08595+3+580);
        glVertex2f(33.21293+10+287, 13.08595+3+580);
        glVertex2f(33.21293+3+287, 13.08595-3.5+3+580);
        glVertex2f(33.21293+10+287, 13.08595-7+3+580);
        glVertex2f(31.6907+287, 6.58564+3+580);
        glEnd();

        // Wing
        glBegin(GL_TRIANGLES);
        glColor3f(0.15f, 0.15f, 0.15f);
        glVertex2f(11.49037+287, 18.26974+580);
        glVertex2f(11.49037+287, 18.26974+15+580);
        glVertex2f(19.55405+287, 19.29827+580);

        glVertex2f(14.6171+287, 5.14569+580);
        glVertex2f(22.47507+287, 5.10455-15+580);
        glVertex2f(22.47507+287, 5.10455+580);
        glEnd();
    }


    void draw_triangle_tree() {
        // Trunk
        glBegin(GL_QUADS);
        glColor3f(0.55, 0.27, 0.07);
        glVertex2f(0, 0);
        glVertex2f(30, 0);
        glVertex2f(30, 100);
        glVertex2f(0, 100);
        glEnd();

        // Middle Green Box
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.6f, 0.0f);
        glVertex2f(-35, 70);
        glVertex2f(65, 70);
        glVertex2f(30, 102);
        glColor3f(0.8588f, 0.8078f, 0.0588f);
        glVertex2f(0, 102);
        glEnd();

        // Top Triangle
        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.6f, 0.0f);
        glVertex2f(-28, 100);
        glColor3f(0.8588f, 0.8078f, 0.0588f);
        glVertex2f(60, 100);
        glVertex2f(14, 155);
        glEnd();
    }


    void draw_gnarly_tree() {

        glBegin(GL_POLYGON);
        glColor3f(0.55, 0.27, 0.07);
        glVertex2f(-12.41, 86.7);
        glVertex2f(-8.16, 91.65);
        glVertex2f(-2.5, 96.6);
        glVertex2f(6, 100);
        glVertex2f(11.6, 100.1);
        glVertex2f(8.1, 95.6);
        glVertex2f(1.2, 90.2);
        glVertex2f(-3.9, 84.1);
        glVertex2f(-6.0, 74.2);
        glVertex2f(-6.0, 59.5);
        glVertex2f(-6.0, 26.3);
        glVertex2f(-4.8, 14.9);
        glVertex2f(-1.3, 8.6);
        glVertex2f(6, 0);
        glVertex2f(-23.8, 0.5);
        glVertex2f(-19.5, 8.3);
        glVertex2f(-17.6, 14.9);
        glVertex2f(-16.4, 26.5);
        glVertex2f(-15.5, 60.0);
        glVertex2f(-16.9, 74.2);
        glVertex2f(-20.4, 85.7);
        glVertex2f(-26.5, 95.4);
        glVertex2f(-29.8, 100.6);
        glVertex2f(-24, 100);
        glVertex2f(-20, 100);
        glVertex2f(-17.3, 94.7);
        glVertex2f(-15.5, 90.2);
        glEnd();

        // Leaves
        drawCircle(0, 133, 40, 0.0f, 0.6f, 0.0f);
        drawCircle(-60, 146, 40, 0.0f, 0.6f, 0.0f);
        drawCircle(54, 117, 40, 0.0f, 0.6f, 0.0f);
        drawCircle(42, 176, 40, 0.0f, 0.6f, 0.0f);
        drawCircle(-16, 183, 40, 0.0f, 0.6f, 0.0f);
    }

    // Tree
    void draw_road_tree() {
        // Trunk
        glBegin(GL_QUADS);
        glColor3f(0.55, 0.27, 0.07);
        glVertex2f(-7.5, 0);
        glVertex2f(7.5, 0);
        glVertex2f(7.5, 70);
        glVertex2f(-7.5, 70);
        glEnd();

        // Leaves
        drawCircle(0, 88, 20, 0.0f, 0.4f, 0.0f);
        drawCircle(-20, 88, 15, 0.0f, 0.4f, 0.0f);
        drawCircle(20, 88, 15, 0.0f, 0.4f, 0.0f);
        drawCircle(0, 108, 15, 0.0f, 0.4f, 0.0f);
    }


    void draw_flower(float x, float y, float r, float g, float b) {
        // Stem
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x+6, y);
        glVertex2f(x+6, y-18);
        glVertex2f(x, y-18);
        glEnd();

        // leaves
        drawCircle(x, y, 10, r, g, b);
        drawCircle(x+11, y, 10, r, g, b);
        drawCircle(x+5, y+5, 10, r, g, b);   
    }

    // --- Drawing Functions ---
    void bird(){
        if(backimage_pointer && bird_pointer)   // ONLY DAY
        {
            glPushMatrix();
            glTranslatef(bird_Position, 0, 0.0f);

            draw_bird(0.94f, 0.87f, 0.73f);

            glPushMatrix();
            glTranslatef(-65.0f, 4.0f, 0.0f);
            draw_bird(0.76f, 0.69f, 0.50f);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-130.0f, -8.0f, 0.0f);
            draw_bird(0.87f, 0.72f, 0.53f);
            glPopMatrix();

            glPopMatrix();
        }
    }

    void backimage(){
    if(backimage_pointer){
        glBegin(GL_POLYGON);
    glColor3ub(255, 255, 147);
        glVertex2f(0, 300);
        glVertex2f(1150, 300);
    glColor3ub (102, 204, 255);
        glVertex2f(1150, 750);
        glVertex2f(0, 750);
        glEnd();
    }
    else{
        glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
        glVertex2f(0, 300);
        glVertex2f(1150, 300);
    glColor3ub(102, 204, 255);
        glVertex2f(1150, 750);
        glVertex2f(0, 750);
        glEnd();
    }
    }


    /**........................................ Back ground...........................................**/
    void Back_ground(){
    glBegin(GL_QUADS);
         glColor3f(0.53f, 0.81f, 0.98f);

        glVertex2f(0, 300);
        glVertex2f(1150,300);
        glVertex2f(1150,750);
        glVertex2f(0,750);
        glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.53f, 0.81f, 0.98f);
        glVertex2f(0, 300);
        glVertex2f(1150,300);
        glVertex2f(1150,750);
        glVertex2f(0,750);
        glEnd();
    }
    /**........................................ HIll ...........................................**/
    void HIll(){
        // --- Left Side Hills ---

        drawCircle(4.6f, 300, 80, 0.0f, 0.4f, 0.0f);

        drawCircle(104.6f, 300, 55, 0.0f, 0.4f, 0.0f);


        drawCircle(224.6f, 300, 89, 0.0f, 0.4f, 0.0f);


        drawCircle(384.6f, 300, 118, 0.0f, 0.4f, 0.0f);


        // --- Right Side Hills ---

        drawCircle(1150-4.6f, 300, 80, 0.0f, 0.4f, 0.0f);


        drawCircle(1150-104.6f, 300, 55, 0.0f, 0.4f, 0.0f);


        drawCircle(1150-224.6f, 300, 89, 0.0f, 0.4f, 0.0f);


        drawCircle(1150-384.6f, 300, 118, 0.0f, 0.4f, 0.0f);


        // --- Ground (Day/Night Logic) ---

        if(backimage_pointer)
        {
            glBegin(GL_QUADS);
            glColor3f(0.39f, 0.8f, 0.13f); // Light Green (Day)
            glVertex2f(0, 0);
            glVertex2f(1150,0);
            glVertex2f(1150,320);
            glColor3f(0.8196f, 0.6157f, 0.2039f);
            glVertex2f(0,320);
            glEnd();
        }
        else{
            glBegin(GL_QUADS);
            glColor3ub(17,75,16); // Dark Green (Night)
            glVertex2f(0, 0);
            glVertex2f(1150,0);
            glVertex2f(1150,320);
            glVertex2f(0,320);
            glEnd();
        }
    }
    /**........................................ Tree1 ...........................................**/
    void Tree1() {
        glPushMatrix();
        glTranslatef(266, 300, 0); // Position of Tree 1
        draw_triangle_tree();
        glPopMatrix();
    }
    /**........................................ Tree2 ...........................................**/
    void Tree2() {
        glPushMatrix();
        glTranslatef(800, 300, 0); // Position of Tree 2
        draw_triangle_tree();
        glPopMatrix();
    }
    /**........................................ Tree3  ...........................................**/
    void Tree3() {
        glPushMatrix();
        glTranslatef(1080, 300, 0); // Position of Tree 3
        draw_triangle_tree();
        glPopMatrix();
    }
    /**........................................ HOUSE ...........................................**/
    void HOUSE(){
        // --- Walls and Roof ---
        glColor3f(0.235f, 0.816f, 0.784f);
        glBegin(GL_QUADS);
        glVertex2f(497, 490);
        glVertex2f(630, 490);
        glVertex2f(630, 300);
        glVertex2f(497, 300);
        glEnd();

        glColor3f(0.349f, 0.204f, 0.129f);
        glBegin(GL_TRIANGLES);
        glVertex2f(560, 540);
        glVertex2f(497, 490);
        glVertex2f(630, 490);
        glEnd();

        // Side Roof Left
        glColor3f(0.235f, 0.816f, 0.784f);
        glBegin(GL_TRIANGLES);
        glVertex2f(497, 450);
        glVertex2f(497, 421);
        glVertex2f(421, 421);
        glEnd();

        // Side Roof Right
        glColor3f(0.235f, 0.816f, 0.784f);
        glBegin(GL_TRIANGLES);
        glVertex2f(630, 450);
        glVertex2f(630, 421);
        glVertex2f(706, 421);
        glEnd();

        // Side Wall Right
        glColor3f(0.235f, 0.816f, 0.784f);
        glBegin(GL_QUADS);
        glVertex2f(630, 421);
        glVertex2f(706, 421);
        glVertex2f(706, 300);
        glVertex2f(630, 300);
        glEnd();

        // --- Right Door ---
        glColor3f(0.36f, 0.17f, 0.02f);
        glBegin(GL_QUADS);
        glVertex2f(650, 345);
        glVertex2f(686, 345);
        glVertex2f(686, 395);
        glVertex2f(650, 395);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.95f, 0.61f, 0.07f);
        glBegin(GL_LINES);
        glVertex2f(668, 345); // Cross 1
        glVertex2f(668, 395);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.95f, 0.61f, 0.07f);
        glBegin(GL_LINES);
        glVertex2f(650, 370); // Cross 2
        glVertex2f(686, 370);
        glEnd();

        // Side Wall Left
        glColor3f(0.235f, 0.816f, 0.784f);
        glBegin(GL_QUADS);
        glVertex2f(497, 421);
        glVertex2f(421, 421);
        glVertex2f(421, 300);
        glVertex2f(497, 300);
        glEnd();

        // --- Left Door ---
        glColor3f(0.36f, 0.17f, 0.02f);
        glBegin(GL_QUADS);
        glVertex2f(441, 345);
        glVertex2f(477, 345);
        glVertex2f(477, 395);
        glVertex2f(441, 395);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.95f, 0.61f, 0.07f);
        glBegin(GL_LINES);
        glVertex2f(459, 345); // Cross 1
        glVertex2f(459, 395);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.95f, 0.61f, 0.07f);
        glBegin(GL_LINES);
        glVertex2f(441, 370); // Cross 2
        glVertex2f(477, 370);
        glEnd();

        // --- Outlines ---
        glLineWidth(5.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(497, 490);
        glVertex2f(630, 490);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.141f, 0.490f, 0.470f);
        glBegin(GL_LINES);
        glVertex2f(496, 450);
        glVertex2f(496, 300);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.349f, 0.204f, 0.129f);
        glBegin(GL_LINES);
        glVertex2f(497, 450);
        glVertex2f(421, 421);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.141f, 0.490f, 0.470f);
        glBegin(GL_LINES);
        glVertex2f(632, 450);
        glVertex2f(632, 300);
        glEnd();

        glLineWidth(5.0f);
        glColor3f(0.349f, 0.204f, 0.129f);
        glBegin(GL_LINES);
        glVertex2f(630, 450);
        glVertex2f(706, 421);
        glEnd();

        // --- Orange Window Background Box ---
        glColor3f(0.95f, 0.61f, 0.07f);
        glBegin(GL_QUADS);
        glVertex2f(507, 425);
        glVertex2f(620, 425);
        glVertex2f(620, 300);
        glVertex2f(507, 300);
        glEnd();

        // --- ROUND WINDOW

        drawCircle(563.5f, 425.0f, 56.5f, 0.95f, 0.61f, 0.07f);

        // Inner Dark Brown Circle
        drawCircle(563.5f, 425.0f, 48.5f, 0.349f, 0.204f, 0.129f); // 56.5 - 8 = 48.5

        // --- Bottom Dark Strip (Under Window) ---
        glColor3f(0.349f, 0.204f, 0.129f);
        glBegin(GL_QUADS);
        glVertex2f(515, 425);
        glVertex2f(612, 425);
        glVertex2f(612, 300);
        glVertex2f(515, 300);
        glEnd();

        // --- Base/Platform ---
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(421, 300);
        glVertex2f(706, 300);
        glVertex2f(731, 280);
        glVertex2f(396, 280);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(731, 280);
        glVertex2f(396, 280);
        glVertex2f(396, 270);
        glVertex2f(731, 270);
        glEnd();
    }
    /**........................................ railing ...........................................**/
    void railing() {

        for(int i = 0; i < 8; i++) {
            float x = 706 + (i * 20);

            // Post (Quad)
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(x, 300);
            glVertex2f(x+15, 300);
            glVertex2f(x+15, 350);
            glVertex2f(x, 350);
            glEnd();

            // Spike Tip (Triangle)
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(x+15, 350);
            glVertex2f(x, 350);
            glVertex2f(x+7.5, 360);
            glEnd();
        }


        for(int i = 0; i < 7; i++) {
            float x = 286 + (i * 20);

            // Post
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(x, 300);
            glVertex2f(x+15, 300);
            glVertex2f(x+15, 350);
            glVertex2f(x, 350);
            glEnd();

            // Spike Tip
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(x+15, 350);
            glVertex2f(x, 350);
            glVertex2f(x+7.5, 360);
            glEnd();
        }

        // --- Horizontal Bars ---
        glLineWidth(5.0f);

        // Right Bars
        glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(706, 317); glVertex2f(841, 317); // Bottom
        glVertex2f(706, 334); glVertex2f(841, 334); // Top
        glEnd();

        // Left Bars
        glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(406, 317); glVertex2f(286, 317); // Bottom
        glVertex2f(406, 334); glVertex2f(286, 334);
        glEnd();
    }
    /**........................................ Plus sign ...........................................**/
    void Plus_sign(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(507, 300);
    glVertex2f(620, 300);
    glVertex2f(620, 318);
    glVertex2f(507, 318);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(524, 318);
    glVertex2f(604, 318);
    glVertex2f(604, 343);
    glVertex2f(524, 343);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(536, 343);
    glVertex2f(590, 343);
    glVertex2f(590, 369);
    glVertex2f(536, 369);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(552, 369);
    glVertex2f(572, 369);
    glVertex2f(572, 453);
    glVertex2f(552, 453);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(529, 421);
    glVertex2f(596, 421);
    glVertex2f(596, 440);
    glVertex2f(529, 440);
    glEnd();

    }
    /**........................................ First vertical line ...........................................**/
    void First_vertical_line(){
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(562, 443);
    glVertex2f(562, 385);
    glEnd();
    }
    /**........................................ Second horizontal line ...........................................**/
    void Second_horizontal_line(){
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(552, 430.5);
    glVertex2f(572, 430.5);
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(202+305+7.5, 183 + 135);
    glVertex2f(208+305+7.5, 183 + 135);
    glVertex2f(208+305+7.5, 165 + 135);
    glVertex2f(202+305+7.5, 165 + 135);
    glEnd();

    int i31;
    GLfloat x31 = 202+305+7.5; GLfloat y31 = 318; GLfloat radius31 = 10;
    int triangleAmount31 = 100;

    GLfloat twicePi31 = 2.0f * PI;


    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x31, y31);
        for(i31 = 0; i31 <= triangleAmount31; i31++) {
            glVertex2f(
                x31 + (radius31 * cos(i31 * twicePi31 / triangleAmount31)),
                y31 + (radius31 * sin(i31 * twicePi31 / triangleAmount31))
            );
        }
    glEnd();

    int i32;
    GLfloat x32 = 213+305+7.5; GLfloat y32 = 318; GLfloat radius32 = 10;
    int triangleAmount32 = 100;

    GLfloat twicePi32 = 2.0f * PI;
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x32, y32);
        for(i32 = 0; i32 <= triangleAmount32; i32++) {
            glVertex2f(
                x32 + (radius32 * cos(i32 * twicePi32 / triangleAmount32)),
                y32 + (radius32 * sin(i32 * twicePi32 / triangleAmount32))
            );
        }
    glEnd();

    int i33;
    GLfloat x33 = 207+305+7.5; GLfloat y33 = 323; GLfloat radius33 = 10;
    int triangleAmount33 = 100;

    GLfloat twicePi33 = 2.0f * PI;

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x33, y33);
        for(i33 = 0; i33 <= triangleAmount33; i33++) {
            glVertex2f(
                x33 + (radius33 * cos(i33 * twicePi33 / triangleAmount33)),
                y33 + (radius33 * sin(i33 * twicePi33 / triangleAmount33))
            );
        }
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(202+305+7.5+25, 183 + 135);
    glVertex2f(208+305+7.5+25, 183 + 135);
    glVertex2f(208+305+7.5+25, 165 + 135);
    glVertex2f(202+305+7.5+25, 165 + 135);
    glEnd();

    int i37;
    GLfloat x37 = 202 + 305 + 7.5+25; GLfloat y37 = 318; GLfloat radius37 = 10;
    int triangleAmount37 = 100;

    GLfloat twicePi37 = 2.0f * PI;

    glColor3f(0.54f, 0.17f, 0.89f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x37, y37);
        for(i37 = 0; i37 <= triangleAmount37; i37++) {
            glVertex2f(
                x37 + (radius37 * cos(i37 * twicePi37 / triangleAmount37)),
                y37 + (radius37 * sin(i37 * twicePi37 / triangleAmount37))
            );
        }
    glEnd();

    int i38;
    GLfloat x38 = 213 + 305 + 7.5+25; GLfloat y38 = 318; GLfloat radius38 = 10;
    int triangleAmount38 = 100;

    GLfloat twicePi38 = 2.0f * PI;

    glColor3f(0.54f, 0.17f, 0.89f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x38, y38);
        for(i38 = 0; i38 <= triangleAmount38; i38++) {
            glVertex2f(
                x38 + (radius38 * cos(i38 * twicePi38 / triangleAmount38)),
                y38 + (radius38 * sin(i38 * twicePi38 / triangleAmount38))
            );
        }
    glEnd();

    int i39;
    GLfloat x39 = 207 + 305 + 7.5+25; GLfloat y39 = 323; GLfloat radius39 = 10;
    int triangleAmount39 = 100;

    GLfloat twicePi39 = 2.0f * PI;

    glColor3f(0.54f, 0.17f, 0.89f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x39, y39);
        for(i39 = 0; i39 <= triangleAmount39; i39++) {
            glVertex2f(
                x39 + (radius39 * cos(i39 * twicePi39 / triangleAmount39)),
                y39 + (radius39 * sin(i39 * twicePi39 / triangleAmount39))
            );
        }
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(202+305+7.5+25+25, 183 + 135);
    glVertex2f(208+305+7.5+25+25, 183 + 135);
    glVertex2f(208+305+7.5+25+25, 165 + 135);
    glVertex2f(202+305+7.5+25+25, 165 + 135);
    glEnd();

    int i40;
    GLfloat x40 = 202 + 305 + 7.5 + 25 + 25; GLfloat y40 = 318; GLfloat radius40 = 10;
    int triangleAmount40 = 100;

    GLfloat twicePi40 = 2.0f * PI;

    glColor3f(1.0f, 0.87f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x40, y40);
        for(i40 = 0; i40 <= triangleAmount40; i40++) {
            glVertex2f(
                x40 + (radius40 * cos(i40 * twicePi40 / triangleAmount40)),
                y40 + (radius40 * sin(i40 * twicePi40 / triangleAmount40))
            );
        }
    glEnd();

    int i41;
    GLfloat x41 = 213 + 305 + 7.5 + 25 + 25; GLfloat y41 = 318; GLfloat radius41 = 10;
    int triangleAmount41 = 100;

    GLfloat twicePi41 = 2.0f * PI;

    glColor3f(1.0f, 0.87f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x41, y41);
        for(i41 = 0; i41 <= triangleAmount41; i41++) {
            glVertex2f(
                x41 + (radius41 * cos(i41 * twicePi41 / triangleAmount41)),
                y41 + (radius41 * sin(i41 * twicePi41 / triangleAmount41))
            );
        }
    glEnd();

    int i42;
    GLfloat x42 = 207 + 305 + 7.5 + 25 + 25; GLfloat y42 = 323; GLfloat radius42 = 10;
    int triangleAmount42 = 100;

    GLfloat twicePi42 = 2.0f * PI;

    glColor3f(1.0f, 0.87f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x42, y42);
        for(i42 = 0; i42 <= triangleAmount42; i42++) {
            glVertex2f(
                x42 + (radius42 * cos(i42 * twicePi42 / triangleAmount42)),
                y42 + (radius42 * sin(i42 * twicePi42 / triangleAmount42))
            );
        }
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(202+305+7.5+25+25+25, 183 + 135);
    glVertex2f(208+305+7.5+25+25+25, 183 + 135);
    glVertex2f(208+305+7.5+25+25+25, 165 + 135);
    glVertex2f(202+305+7.5+25+25+25, 165 + 135);
    glEnd();

    int i43;
    GLfloat x43 = 202 + 305 + 7.5 + 25 + 25 + 25; GLfloat y43 = 318; GLfloat radius43 = 10;
    int triangleAmount43 = 100;

    GLfloat twicePi43 = 2.0f * PI;

    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x43, y43);
        for(i43 = 0; i43 <= triangleAmount43; i43++) {
            glVertex2f(
                x43 + (radius43 * cos(i43 * twicePi43 / triangleAmount43)),
                y43 + (radius43 * sin(i43 * twicePi43 / triangleAmount43))
            );
        }
    glEnd();

    int i44;
    GLfloat x44 = 213 + 305 + 7.5 + 25 + 25 + 25; GLfloat y44 = 318; GLfloat radius44 = 10;
    int triangleAmount44 = 100;

    GLfloat twicePi44 = 2.0f * PI;

    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x44, y44);
        for(i44 = 0; i44 <= triangleAmount44; i44++) {
            glVertex2f(
                x44 + (radius44 * cos(i44 * twicePi44 / triangleAmount44)),
                y44 + (radius44 * sin(i44 * twicePi44 / triangleAmount44))
            );
        }
    glEnd();

    int i45;
    GLfloat x45 = 207 + 305 + 7.5 + 25 + 25 + 25; GLfloat y45 = 323; GLfloat radius45 = 10;
    int triangleAmount45 = 100;

    GLfloat twicePi45 = 2.0f * PI;

    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x45, y45);
        for(i45 = 0; i45 <= triangleAmount45; i45++) {
            glVertex2f(
                x45 + (radius45 * cos(i45 * twicePi45 / triangleAmount45)),
                y45 + (radius45 * sin(i45 * twicePi45 / triangleAmount45))
            );
        }
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(202+305+103, 183 + 135);
    glVertex2f(208+305+103, 183 + 135);
    glVertex2f(208+305+103, 165 + 135);
    glVertex2f(202+305+103, 165 + 135);
    glEnd();

    int i34;
    GLfloat x34 = 202 + 305 + 103; GLfloat y34 = 318; GLfloat radius34 = 10;
    int triangleAmount34 = 100;

    GLfloat twicePi34 = 2.0f * PI;

    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x34, y34);
        for(i34 = 0; i34 <= triangleAmount34; i34++) {
            glVertex2f(
                x34 + (radius34 * cos(i34 * twicePi34 / triangleAmount34)),
                y34 + (radius34 * sin(i34 * twicePi34 / triangleAmount34))
            );
        }
    glEnd();

    int i35;
    GLfloat x35 = 213 + 305 + 103; GLfloat y35 = 318; GLfloat radius35 = 10;
    int triangleAmount35 = 100;

    GLfloat twicePi35 = 2.0f * PI;

    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x35, y35);
        for(i35 = 0; i35 <= triangleAmount35; i35++) {
            glVertex2f(
                x35 + (radius35 * cos(i35 * twicePi35 / triangleAmount35)),
                y35 + (radius35 * sin(i35 * twicePi35 / triangleAmount35))
            );
        }
    glEnd();

    int i36;
    GLfloat x36 = 207 + 305 + 103; GLfloat y36 = 323; GLfloat radius36 = 10;
    int triangleAmount36 = 100;

    GLfloat twicePi36 = 2.0f * PI;

    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x36, y36);
        for(i36 = 0; i36 <= triangleAmount36; i36++) {
            glVertex2f(
                x36 + (radius36 * cos(i36 * twicePi36 / triangleAmount36)),
                y36 + (radius36 * sin(i36 * twicePi36 / triangleAmount36))
            );
        }
    glEnd();

    }
    /**........................................ Tree Circle 1 ...........................................**/
    void Tree_Circle_1() {
        glPushMatrix();
        glTranslatef(120, 300, 0);
        draw_gnarly_tree();
        glPopMatrix();
    }
    /**........................................ Tree Circle 2 ...........................................**/
    void Tree_Circle_2() {
        glPushMatrix();
        glTranslatef(944, 300, 0);
        draw_gnarly_tree();
        glPopMatrix();
    }
    /**........................................ Sun ...........................................**/
    void Sun(){
        if(backimage_pointer)   // ONLY DAY
        {
            glPushMatrix();
            glTranslatef(sun_position, sun_position, 0.0f);
            drawCircle(770, 640, 28, 1.0f, 1.0f, 0.0f);
            glPopMatrix();
        }
    }

    void Cloud(){

        // --- Cloud 1 ---
        glPushMatrix();
        glTranslatef(cloud_Position, 0, 0.0f);

        // Center
        drawCircle(255, 652, 38, 1.0f, 1.0f, 1.0f);
        // Left
        drawCircle(206, 652, 22, 1.0f, 1.0f, 1.0f); // 190+16
        // Right
        drawCircle(302, 652, 23, 1.0f, 1.0f, 1.0f); // 320-18

        glPopMatrix();


        // --- Cloud 2 ---
        glPushMatrix();
        glTranslatef(cloud_Position, 0, 0.0f);

        // Center
        drawCircle(555, 612, 25, 1.0f, 1.0f, 1.0f);
        // Left
        drawCircle(525, 612, 12, 1.0f, 1.0f, 1.0f);
        // Right
        drawCircle(590, 612, 18, 1.0f, 1.0f, 1.0f);

        // Shadow
        drawCircle(570, 602, 18, 0.83f, 0.83f, 0.83f);
        // Cover
        drawCircle(570, 612, 18, 1.0f, 1.0f, 1.0f);

        glPopMatrix();


        // --- Cloud 3 ---
        glPushMatrix();
        glTranslatef(cloud_Position, 0, 0.0f);

        // Center
        drawCircle(914, 670, 25, 1.0f, 1.0f, 1.0f);
        // Right 1
        drawCircle(945, 670, 15, 1.0f, 1.0f, 1.0f);
        // Left
        drawCircle(887, 670, 15, 1.0f, 1.0f, 1.0f);
        // Right Tip
        drawCircle(960, 670, 10, 1.0f, 1.0f, 1.0f);

        glPopMatrix();


        // --- Cloud 4  ---
        glPushMatrix();
        glTranslatef(cloud_Position, 0, 0.0f);

        // Center
        drawCircle(336, 640, 23, 0.83f, 0.83f, 0.83f);
        // Right 1
        drawCircle(367, 640, 15, 0.83f, 0.83f, 0.83f);
        // Left
        drawCircle(309, 640, 15, 0.83f, 0.83f, 0.83f);
        // Right Tip
        drawCircle(382, 640, 10, 0.83f, 0.83f, 0.83f);

        glPopMatrix();
    }

    /**-------------------------Grave-----------------------**/
    void Grave_1(){
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(20, 215); glVertex2f(48, 255);
        glVertex2f(170, 255); glVertex2f(170, 215);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4f(0.78f, 0.78f, 0.78f, 0.3f);
        glVertex2f(170, 255); glVertex2f(143, 215); glVertex2f(170, 215);
        glEnd();

        glColor3f(0.0f, 1.0f, 1.0f);
        renderBitmapString(51, 229, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, " ADISON ");

        // Flower 1 (Yellow)
        draw_flower(32, 221, 1.0f, 0.87f, 0.0f);

        // Flower 2 (Red)
        draw_flower(140, 221, 1.0f, 0.0f, 0.0f);
    }
    /**.......................................Grave_2...........................................**/
    void Grave_2()
    {
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(215, 216); glVertex2f(243, 255);
        glVertex2f(365, 255); glVertex2f(338, 216);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4f(0.78f, 0.78f, 0.78f, 0.3f);
        glVertex2f(365, 255); glVertex2f(338, 216); glVertex2f(365, 216);
        glEnd();

        glColor3f(0.0f, 1.0f, 1.0f);
        renderBitmapString(243, 229, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, " LINKON ");

        // Flower 1 (Orange)
        draw_flower(227, 221, 1.0f, 0.5f, 0.0f);

        // Flower 2 (Yellow)
        draw_flower(335, 221, 1.0f, 0.87f, 0.0f);
    }/**........................................Grave 3...........................................**/
    void Grave_3(){
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(772, 216); glVertex2f(800, 255);
        glVertex2f(922, 255); glVertex2f(895, 216);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4f(0.78f, 0.78f, 0.78f, 0.3f);
        glVertex2f(922, 255); glVertex2f(895, 216); glVertex2f(922, 216);
        glEnd();

        glColor3f(0.0f, 1.0f, 1.0f);
        renderBitmapString(794, 227, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, " Dr. JON ");

        // Flower 1 (Purple)
        draw_flower(798, 221, 0.54f, 0.17f, 0.89f);

        // Flower 2 (Yellow)
        draw_flower(889, 221, 1.0f, 0.87f, 0.0f);
    }/**........................................Grave 4 ...........................................**/
    void Grave_4(){
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(975, 216); glVertex2f(1003, 255);
        glVertex2f(1125, 255); glVertex2f(1098, 216);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor4f(0.78f, 0.78f, 0.78f, 0.3f);
        glVertex2f(1125, 255); glVertex2f(1098, 216); glVertex2f(1125, 216);
        glEnd();

        glColor3f(0.0f, 1.0f, 1.0f);
        renderBitmapString(992, 227, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, " JONSON ");

        // Flower 1 (Light Blue)
        draw_flower(990, 221, 0.53f, 0.81f, 0.92f);

        // Flower 2 (Pink)
        draw_flower(1096, 221, 1.0f, 0.41f, 0.71f);
    }
    /**........................................ Tree beside road ...........................................**/
    void Tree_beside_road() {

        float tree_positions[] = {17.5f, 188.5f, 403.5f, 723.5f, 938.5f, 1132.5f};

        for(int i = 0; i < 6; i++) {
            glPushMatrix();
            glTranslatef(tree_positions[i], 140, 0); // All trees start at y=140
            draw_road_tree();
            glPopMatrix();
        }

        // Road border
        glLineWidth(45.0f);
        glColor3f(0.0f, 0.4f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(0, 140);
        glVertex2f(1175, 140);
        glEnd();


        glColor3f(0.6f, 0.8f, 0.4f);
        glBegin(GL_QUADS);
        glVertex2f(471, 270);
        glVertex2f(651, 270);
        glVertex2f(716, 118);
        glVertex2f(411, 118);
        glEnd();
    }
    /**........................................Road ...........................................**/
    void Road(){
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0, 120);
    glVertex2f(1175, 120);
    glVertex2f(1175, 140);
    glVertex2f(0, 140);
    glEnd();

    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(0, 20);
    glVertex2f(1175, 20);
    glVertex2f(1175, 120);
    glVertex2f(0, 120);
    glEnd();

    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0, 20);
    glVertex2f(1175, 20);
    glVertex2f(1175, 0);
    glVertex2f(0, 0);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 60);
    glVertex2f(100, 60);
    glVertex2f(100, 80);
    glVertex2f(0, 80);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(200, 60);
    glVertex2f(400, 60);
    glVertex2f(400, 80);
    glVertex2f(200, 80);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(500, 60);
    glVertex2f(600, 60);
    glVertex2f(600, 80);
    glVertex2f(500, 80);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(700, 60);
    glVertex2f(900, 60);
    glVertex2f(900, 80);
    glVertex2f(700, 80);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(1000, 60);
    glVertex2f(1100, 60);
    glVertex2f(1100, 80);
    glVertex2f(1000, 80);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(1100, 60);
    glVertex2f(1200, 60);
    glVertex2f(1200, 80);
    glVertex2f(1100, 80);
    glEnd();

    }
    /**........................................Car ...........................................**/
    void Car(){

        glPushMatrix();
        glTranslatef(car_position,0, 0.0f);

        glColor3f(0.0f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(150, 100-34);
        glVertex2f(450, 100-34);
        glVertex2f(450, 160-34);
        glVertex2f(150, 160-34);
        glEnd();

        glColor3f(0.0f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(150, 160-34);
        glVertex2f(100, 160-15-34);
        glVertex2f(100, 100-34);
        glVertex2f(150, 100-34);
        glEnd();

        //Light
        glColor3f(1.0f, 0.4f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(120, 140-34);
        glVertex2f(100, 140-34);
        glVertex2f(100, 100+10+10-34);
        glVertex2f(120, 100+10+10-34);
        glEnd();

        //Light 2
        glColor3f(1.0f, 0.4f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(450, 140+5-34);
        glVertex2f(435, 140+5-34);
        glVertex2f(435, 100+10+10-34);
        glVertex2f(450, 100+10+10-34);
        glEnd();

        glColor3f(0.0f, 0.2f, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(200, 200-34);
        glVertex2f(400, 200-34);
        glVertex2f(400, 160-34);
        glVertex2f(200, 160-34);
        glEnd();

        glColor3f(0.0f, 0.2f, 0.6f);
        glBegin(GL_TRIANGLES);
        glVertex2f(200, 200-34);
        glVertex2f(150, 160-34);
        glVertex2f(200, 160-34);
        glEnd();

        glColor3f(0.0f, 0.2f, 0.6f);
        glBegin(GL_TRIANGLES);
        glVertex2f(400, 200-34);
        glVertex2f(400, 160-34);
        glVertex2f(450, 160-34);
        glEnd();

        //Window
        glColor4f(0.6f, 0.8f, 1.0f, 0.4f);
        glBegin(GL_QUADS);
        glVertex2f(210, 196-5-34);
        glVertex2f(290, 196-5-34);
        glVertex2f(290, 160-34);
        glVertex2f(170, 160-34);
        glEnd();
        //Window
        glColor4f(0.6f, 0.8f, 1.0f, 0.4f);
        glBegin(GL_QUADS);
        glVertex2f(300, 196-5-34);
        glVertex2f(400-10, 196-5-34);
        glVertex2f(400+18+7+6, 160-34);
        glVertex2f(300, 160-34);
        glEnd();
        // Left Wheel: Tire (Black) then Rim (White)
        drawCircle(200, 66, 32, 0.0f, 0.0f, 0.0f);
        drawCircle(200, 66, 19, 1.0f, 1.0f, 1.0f); // 32-13 = 19
        // Right Wheel: Tire (Black) then Rim (White)
        drawCircle(380, 66, 32, 0.0f, 0.0f, 0.0f);
        drawCircle(380, 66, 19, 1.0f, 1.0f, 1.0f);
        glPopMatrix();
    }



    void update() {
        // Bird
        bird_Position -= 1.9f;
        if (bird_Position < -1100.0f) {
            bird_Position = 1109.0f;
        }

        // Cloud
        if(cloud_MovingRight){
             cloud_Position += 1.9f;
             if (cloud_Position > 800.0f) cloud_Position = -900.0f;
        } else {
             cloud_Position -= 1.9f;
             if (cloud_Position < -960.0f) cloud_Position = 1200.0f;
        }

        // Sun
        sun_position += 0.8f;
        if (sun_position > 338.0f) {
            sun_position = -200.0f;
            backimage_pointer = true;
        }
        if (sun_position > 138.0f) {
            backimage_pointer = false;
        }

        // Car
        if(car_speed > 0){
            if(car_position < -450)
                car_position = 1150;
            car_position -= car_speed;
        }
    }

    void update(int value) {
    if (!isPaused) {
        car_position += car_speed * 0.1f;
        cloud_Position += 0.2f;
        bird_Position += 0.3f;
        sun_position += 0.05f;

        // reset positions if needed
        if (car_position > 1200) car_position = -500;
        if (cloud_Position > 1200) cloud_Position = -1200;
        if (bird_Position > 1200) bird_Position = -1200;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}


 void init()
    {
       
    }

    // --- Display Function ---
    void display() {


        backimage();
        Sun();
        HIll();
        Tree1();
        Tree2();
        Tree3();
        HOUSE();
        railing();
        Plus_sign();
        First_vertical_line();
        Second_horizontal_line();
        Tree_Circle_1();
        Tree_Circle_2();
        Cloud();
        Grave_1();
        Grave_2();
        Grave_3();
        Grave_4();
        Tree_beside_road();
        Road();
        Car();
        bird();
    }

    void handleKey(unsigned char key) {

    switch (key) {
        case 'p':
        case 'P':
            isPaused = !isPaused;
            break;

        case 27: 
            exit(0);
            break;
    }
}
}
#endif
