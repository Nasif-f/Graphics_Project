#ifndef SCENARIO4_H
#define SCENARIO4_H

#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define SCENARIO4_PI 3.14159265358979323846

namespace Scenario4 {

    // --- Global Variables ---
    float windTime = 0.0f;
    float cloudPosition = 0.0f;
    float sunPosition = 350.0f;
    bool sunMovingUp = true;
    float cloudDirection = 1.0f;
    float sunDirection = 1.0f;
    bool isNightMode = false;
    bool birdsAnimating = true;
    bool cloudsAnimating = true;
    bool sunAnimating = true;

    struct Bird {
        float x;
        float y;
        float speedX;
        float speedY;
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    const int NUM_BIRDS = 4;
    Bird birds[NUM_BIRDS];

    // --- Helper Functions ---

    float mapX(float x) {
        return 575.0f * x;
    }

    float mapY(float y) {
        return 375.0f * y;
    }

    void renderBitmapString(float x, float y, void *font, const char *string) {
        const char *c;
        glRasterPos2f(x, y);
        for (c = string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }

    unsigned char randomColor() {
        return rand() % 256;
    }

    void initializeBirds() {
        birds[0] = {0.0f, 100.0f, 2.0f, 1.5f, randomColor(), randomColor(), randomColor()};
        birds[1] = {0.0f, 200.0f, 2.0f, 1.0f, randomColor(), randomColor(), randomColor()};
        birds[2] = {1150.0f, 300.0f, -2.0f, 1.5f, randomColor(), randomColor(), randomColor()};
        birds[3] = {1150.0f, 400.0f, -2.0f, 1.0f, randomColor(), randomColor(), randomColor()};
    }

    // --- Drawing Functions ---

    void drawBird(float x, float y, float scale, unsigned char r, unsigned char g, unsigned char b, bool isMovingLeft, float wingAngle) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(r, g, b);
        glVertex2f(x, y);
        int triangleAmount = 100;
        float twicePi = 2.0f * SCENARIO4_PI;
        for (int i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            float xOffset = isMovingLeft ? -1 : 1;
            glVertex2f(x + (scale * 20.0f * xOffset) * cos(angle), y + (scale * 10.0f * sin(angle)));
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(r, g, b);
        glVertex2f(x + (isMovingLeft ? -scale * 20.0f : scale * 20.0f), y + scale * 5.0f);
        for (int i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            glVertex2f(x + (isMovingLeft ? -scale * 20.0f : scale * 20.0f) + (scale * 8.0f * cos(angle)),
                       y + scale * 5.0f + (scale * 8.0f * sin(angle)));
        }
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(255, 165, 0);
        glVertex2f(x + (isMovingLeft ? -scale * 20.0f : scale * 20.0f), y + scale * 5.0f);
        glVertex2f(x + (isMovingLeft ? -scale * 30.0f : scale * 30.0f), y + scale * 8.0f);
        glVertex2f(x + (isMovingLeft ? -scale * 30.0f : scale * 30.0f), y + scale * 2.0f);
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255, 255, 255);
        glVertex2f(x + (isMovingLeft ? -scale * 22.0f : scale * 22.0f), y + scale * 7.0f);
        for (int i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            glVertex2f(x + (isMovingLeft ? -scale * 22.0f : scale * 22.0f) + (scale * 2.0f * cos(angle)),
                       y + scale * 7.0f + (scale * 2.0f * sin(angle)));
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(0, 0, 0);
        glVertex2f(x + (isMovingLeft ? -scale * 22.0f : scale * 22.0f), y + scale * 7.0f);
        for (int i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            glVertex2f(x + (isMovingLeft ? -scale * 22.0f : scale * 22.0f) + (scale * 1.0f * cos(angle)),
                       y + scale * 7.0f + (scale * 1.0f * sin(angle)));
        }
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(r - 20, g - 20, b - 20);
        glVertex2f(x + (isMovingLeft ? -scale * 5.0f : scale * 5.0f), y + scale * 2.0f);
        glVertex2f(x + (isMovingLeft ? scale * 5.0f : -scale * 5.0f), y + scale * 2.0f);
        float flapOffset = scale * 5.0f * sin(wingAngle);
        glVertex2f(x, y + scale * (10.0f + flapOffset));
        glEnd();

        float tailBaseX = x + (isMovingLeft ? scale * 20.0f : -scale * 20.0f);
        glBegin(GL_LINES);
        glColor3ub(r - 30, g - 30, b - 30);
        glVertex2f(tailBaseX, y);
        glVertex2f(tailBaseX + (isMovingLeft ? scale * 15.0f : -scale * 15.0f), y);
        glVertex2f(tailBaseX, y);
        glVertex2f(tailBaseX + (isMovingLeft ? scale * 12.0f : -scale * 12.0f), y - scale * 5.0f);
        glVertex2f(tailBaseX, y);
        glVertex2f(tailBaseX + (isMovingLeft ? scale * 12.0f : -scale * 12.0f), y + scale * 5.0f);
        glEnd();
    }

    void drawBirds() {
        if (isNightMode) return;
        static float wingAngle = 0.0f;
        wingAngle += 0.1f;
        if (wingAngle > 2 * SCENARIO4_PI) wingAngle -= 2 * SCENARIO4_PI;
        for (int i = 0; i < NUM_BIRDS; i++) {
            bool isMovingLeft = (birds[i].speedX < 0);
            drawBird(birds[i].x, birds[i].y, 1.0f, birds[i].r, birds[i].g, birds[i].b, isMovingLeft, wingAngle);
        }
    }

    void drawCircle(float x, float y, float radius, unsigned char rLight, unsigned char gLight, unsigned char bLight, unsigned char rDark, unsigned char gDark, unsigned char bDark) {
        int i;
        int triangleAmount = 100;
        GLfloat twicePi = 2.0f * SCENARIO4_PI;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub((rLight + rDark) / 2, (gLight + gDark) / 2, (bLight + bDark) / 2);
        glVertex2f(x, y);
        for (i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            float vertY = y + (radius * sin(angle));
            float t = (vertY - (y - radius)) / (2.0f * radius);
            unsigned char r = (unsigned char)(rLight + (rDark - rLight) * t);
            unsigned char g = (unsigned char)(gLight + (gDark - gLight) * t);
            unsigned char b = (unsigned char)(bLight + (bDark - bLight) * t);
            glColor3ub(r, g, b);
            glVertex2f(x + (radius * cos(angle)), vertY);
        }
        glEnd();
    }

    void drawFlower(float x, float y) {
        float cx = mapX(x);
        float cy = mapY(y);
        float radius = 8.0f;

        // 1. Draw Stem
        glLineWidth(3.0f);
        glColor3ub(34, 139, 34);
        glBegin(GL_LINES);
        glVertex2f(cx, cy);
        glVertex2f(cx, cy - 22.0f);
        glEnd();
        glLineWidth(1.0f);

        // 2. Draw Petals
        if ((int)(cx) % 3 == 0) glColor3ub(255, 20, 147);
        else if ((int)(cx) % 3 == 1) glColor3ub(255, 69, 0);
        else glColor3ub(255, 105, 180);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i += 30) {
            float angle = i * SCENARIO4_PI / 180.0f;
            glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));
        }
        glEnd();

        // 3. Draw Center
        glColor3ub(255, 255, 0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i += 30) {
            float angle = i * SCENARIO4_PI / 180.0f;
            glVertex2f(cx + (radius * 0.4f) * cos(angle), cy + (radius * 0.4f) * sin(angle));
        }
        glEnd();
    }

    void fFlowers() {
        srand(42);

        // --- Left side field ---
        for (float x = 0.05f; x < 0.75f; x += 0.07f) {
            for (float y = 0.02f; y < 0.40f; y += 0.09f) {
                float offsetX = (rand() % 100) / 2000.0f;
                float offsetY = (rand() % 100) / 2000.0f;
                drawFlower(x + offsetX, y + offsetY);
            }
        }

        // --- Right side field ---
        for (float x = 1.25f; x < 2.4f; x += 0.07f) {
            for (float y = 0.02f; y < 0.40f; y += 0.09f) {
                float offsetX = (rand() % 100) / 2000.0f;
                float offsetY = (rand() % 100) / 2000.0f;
                drawFlower(x + offsetX, y + offsetY);
            }
        }
    }

    void drawCloud(float x, float y, float radius) {
        int triangleAmount = 100;
        GLfloat twicePi = 2.0f * SCENARIO4_PI;

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y);
            for(int i = 0; i <= triangleAmount; i++) {
                glVertex2f( x + (radius * cos(i * twicePi / triangleAmount)),
                            y + (radius * sin(i * twicePi / triangleAmount)) );
            }
        glEnd();
    }

    void drawSun() {
        int i;
        GLfloat radius = 28.0f;
        int triangleAmount = 100;
        GLfloat twicePi = 2.0f * SCENARIO4_PI;

        glBegin(GL_TRIANGLE_FAN);
        if (isNightMode) {
            glColor3ub(200, 200, 200);
        } else {
            glColor3ub(255, 140, 0);
        }
        glVertex2f(570.0f, sunPosition);
        for (i = 0; i <= triangleAmount; i++) {
            glVertex2f(570.0f + (radius * cos(i * twicePi / triangleAmount)),
                       sunPosition + (radius * sin(i * twicePi / triangleAmount)));
        }
        glEnd();
    }

    void drawMaynamatiText() {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int windowWidth = viewport[2];
        int windowHeight = viewport[3];

        float baseHeight = 750.0f;
        float scalingFactor = (float)windowHeight / baseHeight;

        float textX = windowWidth * 0.5f;
        float textY = windowHeight * 0.95f;

        float fontSize = 24.0f * scalingFactor;
        void* font;

        if (fontSize > 30) font = GLUT_BITMAP_TIMES_ROMAN_24;
        else if (fontSize > 20) font = GLUT_BITMAP_HELVETICA_18;
        else font = GLUT_BITMAP_HELVETICA_12;

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, windowWidth, 0, windowHeight);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3f(0.1f, 0.1f, 0.1f);
        renderBitmapString(textX - (glutBitmapLength(font, (unsigned char*)"MAYNAMATI")/2) + 1*scalingFactor,
                           textY - 1*scalingFactor, font, "MAYNAMATI");

        glColor3f(0.96f, 0.87f, 0.58f);
        renderBitmapString(textX - (glutBitmapLength(font, (unsigned char*)"MAYNAMATI")/2),
                           textY, font, "MAYNAMATI");

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    void fsky() {
        glBegin(GL_QUADS);
        if (isNightMode) {
            glColor3ub(25, 25, 112);
            glVertex2f(mapX(0.0f), mapY(0.9f));
            glVertex2f(mapX(2.0f), mapY(0.9f));
            glColor3ub(0, 0, 50);
            glVertex2f(mapX(2.0f), mapY(2.0f));
            glVertex2f(mapX(0.0f), mapY(2.0f));
        } else {
            glColor3ub(175, 226, 255);
            glVertex2f(mapX(0.0f), mapY(0.9f));
            glVertex2f(mapX(2.0f), mapY(0.9f));
            glColor3ub(95, 186, 215);
            glVertex2f(mapX(2.0f), mapY(2.0f));
            glVertex2f(mapX(0.0f), mapY(2.0f));
        }
        glEnd();
    }

    void fcloud() {
        drawCloud(255 + cloudPosition + 0.2f, 652 + 1.85f, 45.0f);
        drawCloud(190 + cloudPosition + 0.2f, 652 + 1.85f, 30.0f);
        drawCloud(320 + cloudPosition + 0.2f, 652 + 1.85f, 30.0f);
        drawCloud(914 + cloudPosition + 0.2f, 670 + 1.85f, 25.0f);
        drawCloud(945 + cloudPosition + 0.2f, 670 + 1.85f, 15.0f);
        drawCloud(887 + cloudPosition + 0.2f, 670 + 1.85f, 15.0f);
        drawCloud(960 + cloudPosition + 0.2f, 670 + 1.85f, 10.0f);
        drawCloud(500 + cloudPosition + 0.2f, 680 + 1.85f, 35.0f);
        drawCloud(460 + cloudPosition + 0.2f, 680 + 1.85f, 25.0f);
        drawCloud(540 + cloudPosition + 0.2f, 680 + 1.85f, 20.0f);
    }

    void fLeftArc() {
        glBegin(GL_TRIANGLE_FAN);
            glColor3ub(141, 107, 69);
            glVertex2f(mapX(0.525f), mapY(0.932f));
            glVertex2f(mapX(0.565f), mapY(0.932f));
            glVertex2f(mapX(0.594f), mapY(0.92f));
            glVertex2f(mapX(0.639f), mapY(0.92f));
            glVertex2f(mapX(0.665f), mapY(0.92f));
            glVertex2f(mapX(0.699f), mapY(0.908f));
            glVertex2f(mapX(0.732f), mapY(0.92f));
            glVertex2f(mapX(0.763f), mapY(0.936f));
            glVertex2f(mapX(0.839f), mapY(0.979f));
            glVertex2f(mapX(0.874f), mapY(0.991f));
            glVertex2f(mapX(0.879f), mapY(1.019f));
            glVertex2f(mapX(0.937f), mapY(1.015f));
            glVertex2f(mapX(0.941f), mapY(0.964f));
            glVertex2f(mapX(0.968f), mapY(0.979f));
            glVertex2f(mapX(0.972f), mapY(0.908f));
            glVertex2f(mapX(0.941f), mapY(0.912f));
            glVertex2f(mapX(0.937f), mapY(0.924f));
            glVertex2f(mapX(0.941f), mapY(0.632f));
            glVertex2f(mapX(0.919f), mapY(0.596f));
            glVertex2f(mapX(0.899f), mapY(0.6f));
            glVertex2f(mapX(0.899f), mapY(0.647f));
            glVertex2f(mapX(0.852f), mapY(0.643f));
            glVertex2f(mapX(0.859f), mapY(0.695f));
            glVertex2f(mapX(0.852f), mapY(0.742f));
            glVertex2f(mapX(0.794f), mapY(0.746f));
            glVertex2f(mapX(0.672f), mapY(0.742f));
            glVertex2f(mapX(0.510f), mapY(0.734f));
            glVertex2f(mapX(0.001f), mapY(0.734f));
            glVertex2f(mapX(0.0f), mapY(0.889f));
            glVertex2f(mapX(0.048f), mapY(0.924f));
            glVertex2f(mapX(0.083f), mapY(0.9f));
            glVertex2f(mapX(0.128f), mapY(0.912f));
            glVertex2f(mapX(0.197f), mapY(0.908f));
            glVertex2f(mapX(0.241f), mapY(0.912f));
            glVertex2f(mapX(0.265f), mapY(0.912f));
            glVertex2f(mapX(0.288f), mapY(0.932f));
            glVertex2f(mapX(0.334f), mapY(0.932f));
            glVertex2f(mapX(0.345f), mapY(0.916f));
            glVertex2f(mapX(0.359f), mapY(0.908f));
            glVertex2f(mapX(0.368f), mapY(0.904f));
            glVertex2f(mapX(0.381f), mapY(0.904f));
            glVertex2f(mapX(0.401f), mapY(0.92f));
            glVertex2f(mapX(0.457f), mapY(0.932f));
            glVertex2f(mapX(0.468f), mapY(0.916f));
            glVertex2f(mapX(0.485f), mapY(0.916f));
        glEnd();

        glColor3ub(92, 64, 25);
        float bricksStartY = 0.75f;
        float bricksHeight = 0.17f;
        float brickHeight = 0.04f;
        float brickWidth = 0.1f;
        int rows = (int)(bricksHeight / brickHeight);
        float actualBrickHeight = bricksHeight / rows;

        for(int row = 0; row < rows; ++row) {
            float y = bricksStartY + row * actualBrickHeight;
            float xOffset = (row % 2) * (brickWidth / 2.0f);
            float startX = 0.0f + xOffset;
            float endX = 0.9f;

            for(float x = startX; x <= endX; x += brickWidth) {
                float xStart = x;
                float xEnd = x + brickWidth * 0.95f;
                if (xEnd > endX) xEnd = endX;

                glBegin(GL_LINES);
                    glVertex2f(mapX(xStart), mapY(y));
                    glVertex2f(mapX(xEnd), mapY(y));
                glEnd();

                if (xEnd < endX) {
                    glBegin(GL_LINES);
                        glVertex2f(mapX(xEnd), mapY(y));
                        glVertex2f(mapX(xEnd), mapY(y + actualBrickHeight * 0.95f));
                    glEnd();
                }

                glBegin(GL_LINES);
                    glVertex2f(mapX(xStart), mapY(y + actualBrickHeight * 0.95f));
                    glVertex2f(mapX(xEnd), mapY(y + actualBrickHeight * 0.95f));
                glEnd();
            }
        }
    }

    void fRightArc() {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(141, 107, 69);
        glVertex2f(mapX(1.459f), mapY(0.948f));
        glVertex2f(mapX(1.497f), mapY(0.964f));
        glVertex2f(mapX(1.523f), mapY(0.94f));
        glVertex2f(mapX(1.572f), mapY(0.948f));
        glVertex2f(mapX(1.599f), mapY(0.96f));
        glVertex2f(mapX(1.623f), mapY(0.956f));
        glVertex2f(mapX(1.639f), mapY(0.94f));
        glVertex2f(mapX(1.688f), mapY(0.948f));
        glVertex2f(mapX(1.732f), mapY(0.964f));
        glVertex2f(mapX(1.761f), mapY(0.944f));
        glVertex2f(mapX(1.808f), mapY(0.948f));
        glVertex2f(mapX(1.863f), mapY(0.968f));
        glVertex2f(mapX(1.881f), mapY(0.96f));
        glVertex2f(mapX(1.905f), mapY(0.948f));
        glVertex2f(mapX(1.957f), mapY(0.956f));
        glVertex2f(mapX(2.003f), mapY(0.96f));
        glVertex2f(mapX(2.003f), mapY(0.766f));
        glVertex2f(mapX(1.825f), mapY(0.754f));
        glVertex2f(mapX(1.177f), mapY(0.726f));
        glVertex2f(mapX(1.185f), mapY(0.675f));
        glVertex2f(mapX(1.132f), mapY(0.671f));
        glVertex2f(mapX(1.088f), mapY(0.675f));
        glVertex2f(mapX(1.072f), mapY(0.916f));
        glVertex2f(mapX(1.019f), mapY(0.908f));
        glVertex2f(mapX(1.019f), mapY(0.968f));
        glVertex2f(mapX(1.043f), mapY(0.972f));
        glVertex2f(mapX(1.043f), mapY(0.991f));
        glVertex2f(mapX(1.072f), mapY(0.995f));
        glVertex2f(mapX(1.088f), mapY(1.015f));
        glVertex2f(mapX(1.114f), mapY(1.011f));
        glVertex2f(mapX(1.154f), mapY(1.011f));
        glVertex2f(mapX(1.168f), mapY(0.995f));
        glVertex2f(mapX(1.143f), mapY(0.979f));
        glVertex2f(mapX(1.174f), mapY(0.983f));
        glVertex2f(mapX(1.217f), mapY(0.96f));
        glVertex2f(mapX(1.245f), mapY(0.936f));
        glVertex2f(mapX(1.350f), mapY(0.94f));
        glVertex2f(mapX(1.381f), mapY(0.956f));
        glVertex2f(mapX(1.399f), mapY(0.948f));
        glVertex2f(mapX(1.421f), mapY(0.94f));
        glEnd();

        glColor3ub(92, 64, 25);
        float bricksStartY = 0.76f;
        float bricksHeight = 0.19f;
        float brickHeight = 0.04f;
        float brickWidth = 0.1f;
        int rows = (int)(bricksHeight / brickHeight);
        float actualBrickHeight = bricksHeight / rows;
        float minX = 1.1f;
        float maxX = 6.0f;

        for(int row = 0; row < rows; ++row) {
            float y = bricksStartY + row * actualBrickHeight;
            float xOffset = (row % 2) * (brickWidth / 2.0f);
            float startX = minX + xOffset;
            float endX = maxX - 0.1f;

            for(float x = startX; x <= endX; x += brickWidth) {
                float xStart = x;
                float xEnd = x + brickWidth * 0.95f;
                if (xEnd > endX) xEnd = endX;
                glBegin(GL_LINES);
                    glVertex2f(mapX(xStart), mapY(y));
                    glVertex2f(mapX(xEnd), mapY(y));
                glEnd();
                if (xEnd < endX) {
                    glBegin(GL_LINES);
                        glVertex2f(mapX(xEnd), mapY(y));
                        glVertex2f(mapX(xEnd), mapY(y + actualBrickHeight * 0.95f));
                    glEnd();
                }
                glBegin(GL_LINES);
                    glVertex2f(mapX(xStart), mapY(y + actualBrickHeight * 0.95f));
                    glVertex2f(mapX(xEnd), mapY(y + actualBrickHeight * 0.95f));
                glEnd();
            }
        }
    }

    void fGreenField() {
        glBegin(GL_QUADS);
        glColor3ub(80, 120, 0);
        glVertex2f(mapX(0.00f), mapY(0.9f));
        glVertex2f(mapX(2.5f), mapY(0.9f));
        glColor3ub(150, 200, 60);
        glVertex2f(mapX(2.5f), mapY(0.0f));
        glVertex2f(mapX(0.00f), mapY(0.0f));
        glEnd();
    }

    void fRoad() {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(185, 157, 73);
        glVertex2f(mapX(1.163f), mapY(0.442f));
        glVertex2f(mapX(1.452f), mapY(0.442f));
        glVertex2f(mapX(1.617f), mapY(0.434f));
        glVertex2f(mapX(1.705f), mapY(0.383f));
        glVertex2f(mapX(1.201f), mapY(0.367f));
        glVertex2f(mapX(1.412f), mapY(0.0f));
        glVertex2f(mapX(0.659f), mapY(0.003f));
        glVertex2f(mapX(0.794f), mapY(0.268f));
        glVertex2f(mapX(0.808f), mapY(0.28f));
        glVertex2f(mapX(0.812f), mapY(0.3f));
        glVertex2f(mapX(0.859f), mapY(0.383f));
        glVertex2f(mapX(0.857f), mapY(0.398f));
        glVertex2f(mapX(0.879f), mapY(0.442f));
        glVertex2f(mapX(0.910f), mapY(0.497f));
        glVertex2f(mapX(1.123f), mapY(0.505f));
        glVertex2f(mapX(1.123f), mapY(0.55f));
        glVertex2f(mapX(1.123f), mapY(0.55f));
        glEnd();

        // Road lines
        glColor3ub(123, 92, 29);
        glBegin(GL_LINES); glVertex2f(mapX(0.938f), mapY(0.498f)); glVertex2f(mapX(0.722f), mapY(0.0f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.336f), mapY(0.0f)); glVertex2f(mapX(1.098f), mapY(0.506f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.931f), mapY(0.474f)); glVertex2f(mapX(1.111f), mapY(0.478f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.909f), mapY(0.431f)); glVertex2f(mapX(1.127f), mapY(0.443f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.882f), mapY(0.379f)); glVertex2f(mapX(1.153f), mapY(0.391f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.867f), mapY(0.328f)); glVertex2f(mapX(1.176f), mapY(0.34f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.840f), mapY(0.273f)); glVertex2f(mapX(1.202f), mapY(0.289f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.809f), mapY(0.198f)); glVertex2f(mapX(1.236f), mapY(0.213f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.771f), mapY(0.134f)); glVertex2f(mapX(1.267f), mapY(0.15f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.751f), mapY(0.071f)); glVertex2f(mapX(1.296f), mapY(0.087f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.020f), mapY(0.494f)); glVertex2f(mapX(1.024f), mapY(0.462f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.958f), mapY(0.431f)); glVertex2f(mapX(0.960f), mapY(0.379f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.020f), mapY(0.379f)); glVertex2f(mapX(1.027f), mapY(0.336f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.100f), mapY(0.332f)); glVertex2f(mapX(1.100f), mapY(0.277f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.960f), mapY(0.277f)); glVertex2f(mapX(0.949f), mapY(0.261f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.949f), mapY(0.265f)); glVertex2f(mapX(0.947f), mapY(0.198f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.007f), mapY(0.206f)); glVertex2f(mapX(1.013f), mapY(0.142f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.073f), mapY(0.154f)); glVertex2f(mapX(1.076f), mapY(0.087f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(0.840f), mapY(0.067f)); glVertex2f(mapX(0.838f), mapY(0.0f)); glEnd();

        // Horizontal details
        glBegin(GL_LINES); glVertex2f(mapX(1.158f), mapY(0.383f)); glVertex2f(mapX(1.671f), mapY(0.399f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.198f), mapY(0.435f)); glVertex2f(mapX(1.224f), mapY(0.375f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.251f), mapY(0.431f)); glVertex2f(mapX(1.264f), mapY(0.387f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.307f), mapY(0.431f)); glVertex2f(mapX(1.331f), mapY(0.387f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.371f), mapY(0.435f)); glVertex2f(mapX(1.391f), mapY(0.395f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.436f), mapY(0.435f)); glVertex2f(mapX(1.458f), mapY(0.395f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.487f), mapY(0.435f)); glVertex2f(mapX(1.504f), mapY(0.391f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.531f), mapY(0.431f)); glVertex2f(mapX(1.549f), mapY(0.391f)); glEnd();
        glBegin(GL_LINES); glVertex2f(mapX(1.580f), mapY(0.435f)); glVertex2f(mapX(1.598f), mapY(0.395f)); glEnd();
    }


    void drawStairSlopes() {
        glColor3ub(110, 90, 60);

        // Left Slope
        glBegin(GL_TRIANGLES);
        glVertex2f(mapX(0.941f), mapY(0.632f)); // Top-Right of slope (Left Wall Bottom)
        glVertex2f(mapX(0.82f), mapY(0.50f));   // Bottom-Right (Stair Bottom Left)
        glVertex2f(mapX(0.40f), mapY(0.50f));   // Bottom-Left (Extend into field)
        glEnd();

        // Right Slope
        glBegin(GL_TRIANGLES);
        glVertex2f(mapX(1.072f), mapY(0.632f)); // Top-Left of slope (Right Wall Bottom)
        glVertex2f(mapX(1.196f), mapY(0.50f));  // Bottom-Left (Stair Bottom Right)
        glVertex2f(mapX(1.60f), mapY(0.50f));   // Bottom-Right (Extend into field)
        glEnd();
    }


    void drawGrandStaircase() {
        float topY = 0.905f;
        float bottomY = 0.50f;


        float topX_Left = 0.94f;
        float topX_Right = 1.076f;

        float bottomX_Left = 0.82f;
        float bottomX_Right = 1.196f;

        int steps = 15;

        for (int i = 0; i < steps; i++) {
            float t1 = (float)i / steps;
            float t2 = (float)(i + 1) / steps;


            float y1 = bottomY + (topY - bottomY) * t1;
            float y2 = bottomY + (topY - bottomY) * t2;


            float xLeft1 = bottomX_Left + (topX_Left - bottomX_Left) * t1;
            float xRight1 = bottomX_Right + (topX_Right - bottomX_Right) * t1;

            float xLeft2 = bottomX_Left + (topX_Left - bottomX_Left) * t2;
            float xRight2 = bottomX_Right + (topX_Right - bottomX_Right) * t2;


            glBegin(GL_QUADS);
            glColor3ub(160, 130, 90); // Main step color
            glVertex2f(mapX(xLeft1), mapY(y1));
            glVertex2f(mapX(xRight1), mapY(y1));
            glVertex2f(mapX(xRight1), mapY(y2));
            glVertex2f(mapX(xLeft1), mapY(y2));
            glEnd();


            glColor3ub(80, 60, 40); // Dark outline
            glLineWidth(2.0f);
            glBegin(GL_LINES);
            // Bottom line
            glVertex2f(mapX(xLeft1), mapY(y1));
            glVertex2f(mapX(xRight1), mapY(y1));
            // Sides
            glVertex2f(mapX(xLeft1), mapY(y1));
            glVertex2f(mapX(xLeft1), mapY(y2));
            glVertex2f(mapX(xRight1), mapY(y1));
            glVertex2f(mapX(xRight1), mapY(y2));
            glEnd();
        }
        glLineWidth(1.0f);
    }


    void drawRoundTreeWithMultipleLeaves(float x, float y,
                                         float trunkWidth, float trunkHeight,
                                         float leafRadius, float smallLeafRadius) {

        // wind sway
        float sway = sin(windTime + x * 0.01f) * 8.0f;

        // ---------- TRUNK ----------
        glBegin(GL_QUADS);
        glColor3ub(165, 82, 23);

        // bottom (fixed)
        glVertex2f(x - trunkWidth / 2, y);
        glVertex2f(x + trunkWidth / 2, y);

        glColor3ub(113, 56, 15);

        // top (moves slightly)
        glVertex2f(x + trunkWidth / 2 + sway * 0.25f, y + trunkHeight);
        glVertex2f(x - trunkWidth / 2 + sway * 0.25f, y + trunkHeight);
        glEnd();

        // ---------- LEAVES----------
        float leafSway = sway;

        drawCircle(x + leafSway, y + trunkHeight,
                   leafRadius, 0, 153, 0, 0, 102, 0);

        drawCircle(x - leafRadius * 0.5f + leafSway,
                   y + trunkHeight + leafRadius * 0.5f,
                   smallLeafRadius, 0, 153, 0, 0, 102, 0);

        drawCircle(x + leafRadius * 0.5f + leafSway,
                   y + trunkHeight + leafRadius * 0.5f,
                   smallLeafRadius, 0, 153, 0, 0, 102, 0);

        drawCircle(x + leafSway,
                   y + trunkHeight + leafRadius,
                   smallLeafRadius, 0, 153, 0, 0, 102, 0);
    }

    void drawTrees() {
        // LEFT SIDE TREES
        drawRoundTreeWithMultipleLeaves(120, 180, 18, 90, 35, 22);
        drawRoundTreeWithMultipleLeaves(200, 170, 20, 100, 38, 24);
        drawRoundTreeWithMultipleLeaves(300, 160, 16, 85, 30, 20);

        // RIGHT SIDE TREES
        drawRoundTreeWithMultipleLeaves(850, 170, 18, 90, 35, 22);
        drawRoundTreeWithMultipleLeaves(950, 160, 20, 100, 38, 24);
        drawRoundTreeWithMultipleLeaves(1050, 180, 16, 85, 30, 20);

        // LEFT SIDE TREES
        drawRoundTreeWithMultipleLeaves(120, 180, 18, 90, 35, 22);
        drawRoundTreeWithMultipleLeaves(200, 170, 20, 100, 38, 24);
        drawRoundTreeWithMultipleLeaves(300, 160, 16, 85, 30, 20);
        drawRoundTreeWithMultipleLeaves(400, 165, 18, 95, 36, 22);
        drawRoundTreeWithMultipleLeaves(50, 170, 15, 80, 28, 18);

        // RIGHT SIDE TREES
        drawRoundTreeWithMultipleLeaves(850, 170, 18, 90, 35, 22);
        drawRoundTreeWithMultipleLeaves(950, 160, 20, 100, 38, 24);
        drawRoundTreeWithMultipleLeaves(1050, 180, 16, 85, 30, 20);
        drawRoundTreeWithMultipleLeaves(1150, 170, 18, 95, 36, 22);
        drawRoundTreeWithMultipleLeaves(900, 160, 15, 80, 28, 18);
    }

    void fFieldGrass() {
        srand(1);

        // ---------- LEFT SIDE GRASS ----------
        for (float x = 0; x <= 450; x += 5) {
            for (float y = 0; y <= 300; y += 20) {

                float h = 20 + rand() % 10;
                float w = 2;

                // wind effect
                float sway = sin(windTime + x * 0.02f) * 6;

                glColor3ub(30 + rand() % 20, 140 + rand() % 40, 30);

                glBegin(GL_TRIANGLES);
                    glVertex2f(x + sway, y + h);   // tip moves
                    glVertex2f(x - w, y);          // base fixed
                    glVertex2f(x + w, y);
                glEnd();
            }
        }

        // ---------- RIGHT SIDE GRASS ----------
        for (float x = 700; x <= 2050; x += 5) {
            for (float y = 0; y <= 300; y += 20) {

                float h = 20 + rand() % 10;
                float w = 2;

                float sway = sin(windTime + x * 0.02f) * 6;

                glColor3ub(30 + rand() % 20, 140 + rand() % 40, 30);

                glBegin(GL_TRIANGLES);
                    glVertex2f(x + sway, y + h);
                    glVertex2f(x - w, y);
                    glVertex2f(x + w, y);
                glEnd();
            }
        }
    }

    // --- Updates and Inputs ---

    void update() {
        // Wind
        windTime += 0.05f;

        // Cloud
        if (cloudsAnimating) {
            cloudPosition += 1.9f * cloudDirection;
            if (cloudPosition > 800.0f) {
                cloudPosition = -600.0f;
            } else if (cloudPosition < -600.0f) {
                cloudPosition = 800.0f;
            }
        }

        // Sun
        if (sunAnimating) {
            sunPosition += 1.5f * sunDirection;
            if (sunPosition > 760.0f) {
                sunPosition = 350.0f;
            } else if (sunPosition < 350.0f) {
                sunPosition = 760.0f;
            }
        }

        // Birds
        if (birdsAnimating) {
            for (int i = 0; i < NUM_BIRDS; i++) {
                birds[i].x += birds[i].speedX;
                birds[i].y += birds[i].speedY;
                if (birds[i].x < 0.0f || birds[i].x > 1150.0f || birds[i].y > 750.0f) {
                    birds[i].x = (birds[i].speedX > 0) ? 0.0f : 1150.0f;
                    birds[i].y = rand() % 600;
                }
            }
        }
    }

    void handleKey(unsigned char key) {
        switch (key) {
            case 'n': case 'N': isNightMode = !isNightMode; break;
            case 'b': case 'B': birdsAnimating = !birdsAnimating; break;
            case 'c': case 'C': cloudsAnimating = !cloudsAnimating; break;
            case 's': case 'S': sunAnimating = !sunAnimating; break;
        }
    }

    void init() {
        initializeBirds();
    }

    void display() {

        fsky();
        drawSun();
        fcloud();

        fGreenField();

        fFlowers();
        fFieldGrass();

        fLeftArc();
        fRightArc();

        fRoad();


        drawStairSlopes();
        drawGrandStaircase();

        drawTrees();
        drawBirds();

        drawMaynamatiText();
    }
}
#endif
