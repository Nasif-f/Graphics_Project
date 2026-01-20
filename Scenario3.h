#ifndef SCENARIO3_H
#define SCENARIO3_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>


#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <windows.h>


#define SCENARIO3_MAX_STARS 150
#define SCENARIO3_MAX_RAIN 150

namespace Scenario3 {

    // --- Global Variables ---
    float boatOffsetX = 0.0f;
    float cloudOffsetX = 0.0f;
    float boatSpeed = 2.0f;
    bool boatMoving = true;
    bool isDay = true;
    bool isRaining = false;

    struct Star {
        float x, y;
        float brightness;
        float flickerSpeed;
        float size;
    };

    struct RainDrop {
        float x, y, speed;
        float length;
    };

    Star stars[SCENARIO3_MAX_STARS];
    RainDrop rain[SCENARIO3_MAX_RAIN];

    // --- Helper Functions

    void renderBitmapString(float x, float y, void* font, const char* string) {
        const char* c;
        glRasterPos2f(x, y);
        for (c = string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }

    // --- Initialization ---

    void initStars() {
        srand(time(NULL));
        for (int i = 0; i < SCENARIO3_MAX_STARS; i++) {
            stars[i].x = rand() % 1150;
            stars[i].y = 480 + rand() % 270;
            stars[i].brightness = ((float)(rand() % 100)) / 100.0f;
            stars[i].flickerSpeed = 0.02f + ((float)(rand() % 10) / 500.0f);
            stars[i].size = 1.0f + (rand() % 300) / 100.0f;
        }
    }

    void initRain() {
        for (int i = 0; i < SCENARIO3_MAX_RAIN; i++) {
            rain[i].x = rand() % 1150;
            rain[i].y = rand() % 750;
            rain[i].speed = 5 + rand() % 8;
            rain[i].length = 10 + rand() % 10;
        }
    }

    void init() {
        initStars();
        initRain();
    }

    // --- Drawing Functions ---

    void drawStars() {
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        for (int i = 0; i < SCENARIO3_MAX_STARS; i++) {
            glPointSize(stars[i].size);
            float flicker = 0.5f + 0.5f * sin(stars[i].brightness);
            glColor3f(flicker, flicker, flicker);
            glVertex2f(stars[i].x, stars[i].y);
            stars[i].brightness += stars[i].flickerSpeed;
        }
        glEnd();
    }

    void drawRain() {
        glColor3f(0.8f, 0.8f, 1.0f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
        for (int i = 0; i < SCENARIO3_MAX_RAIN; i++) {
            glVertex2f(rain[i].x, rain[i].y);
            glVertex2f(rain[i].x - 3, rain[i].y - rain[i].length);
        }
        glEnd();
    }

    void LITTLE_BOAT() {
        glPushMatrix();
        glTranslatef(boatOffsetX, 0.0f, 0.0f);

        // Boat base with gradient
        glBegin(GL_POLYGON);
        glColor3f(0.65f, 0.45f, 0.25f);
        glVertex2f(960, 380);
        glColor3f(0.55f, 0.35f, 0.15f);
        glVertex2f(1020, 335);
        glVertex2f(1080, 335);
        glColor3f(0.65f, 0.45f, 0.25f);
        glVertex2f(1140, 380);
        glEnd();

        // Cabin with details
        glBegin(GL_POLYGON);
        glColor3f(0.75f, 0.25f, 0.25f);
        glVertex2f(1020, 380);
        glVertex2f(1020, 405);
        glColor3f(0.85f, 0.35f, 0.35f);
        glVertex2f(1050, 415);
        glVertex2f(1080, 405);
        glColor3f(0.75f, 0.25f, 0.25f);
        glVertex2f(1080, 380);
        glEnd();

        // Cabin window
        glColor3f(0.9f, 0.9f, 1.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 50; i++) {
            float angle = 2.0f * 3.1415926f * i / 50;
            glVertex2f(1050 + 8 * cos(angle), 395 + 8 * sin(angle));
        }
        glEnd();

        glPopMatrix();
    }

    void BOAT() {
        // Main hull with gradient
        glBegin(GL_POLYGON);
        glColor3f(0.6f, 0.3f, 0.1f);
        glVertex2f(320, 120);
        glColor3f(0.5f, 0.25f, 0.05f);
        glVertex2f(520, 40);
        glVertex2f(470, 120);
        glColor3f(0.6f, 0.3f, 0.1f);
        glVertex2f(280, 200);
        glEnd();

        // Upper deck
        glBegin(GL_POLYGON);
        glColor3f(0.35f, 0.25f, 0.15f);
        glVertex2f(280, 200);
        glVertex2f(340, 195);
        glColor3f(0.45f, 0.35f, 0.25f);
        glVertex2f(395, 210);
        glVertex2f(415, 250);
        glColor3f(0.4f, 0.3f, 0.2f);
        glVertex2f(620, 175);
        glVertex2f(600, 130);
        glColor3f(0.35f, 0.25f, 0.15f);
        glVertex2f(520, 100);
        glVertex2f(470, 120);
        glEnd();

        // Cabin
        glBegin(GL_POLYGON);
        glColor3f(0.75f, 0.25f, 0.25f);
        glVertex2f(620, 175);
        glVertex2f(600, 130);
        glColor3f(0.65f, 0.15f, 0.15f);
        glVertex2f(520, 100);
        glVertex2f(470, 120);
        glColor3f(0.8f, 0.3f, 0.3f);
        glVertex2f(520, 40);
        glVertex2f(615, 85);
        glEnd();
    }

    void AIR() {
        glBegin(GL_POLYGON);
        if (isDay && !isRaining) {
            // Day gradient
            glColor3f(0.53f, 0.81f, 0.92f);
            glVertex2f(0, 480);
            glColor3f(0.65f, 0.85f, 0.95f);
            glVertex2f(1150, 440);
            glColor3f(0.7f, 0.88f, 0.98f);
            glVertex2f(1150, 750);
            glColor3f(0.6f, 0.8f, 0.9f);
            glVertex2f(0, 750);
        }
        else if (isDay && isRaining) {
            // Rainy day
            glColor3f(0.4f, 0.5f, 0.6f);
            glVertex2f(0, 480);
            glVertex2f(1150, 440);
            glColor3f(0.45f, 0.55f, 0.65f);
            glVertex2f(1150, 750);
            glVertex2f(0, 750);
        }
        else if (!isDay && !isRaining) {
            // Night gradient
            glColor3f(0.0f, 0.0f, 0.2f);
            glVertex2f(0, 480);
            glColor3f(0.05f, 0.05f, 0.3f);
            glVertex2f(1150, 440);
            glColor3f(0.1f, 0.1f, 0.35f);
            glVertex2f(1150, 750);
            glColor3f(0.05f, 0.05f, 0.25f);
            glVertex2f(0, 750);
        }
        else {
            // Rainy night
            glColor3f(0.05f, 0.05f, 0.15f);
            glVertex2f(0, 480);
            glVertex2f(1150, 440);
            glColor3f(0.08f, 0.08f, 0.18f);
            glVertex2f(1150, 750);
            glVertex2f(0, 750);
        }
        glEnd();
    }

    void LAND_BOUNDARY() {
        glBegin(GL_POLYGON);
        // Green gradient for land
        glColor3f(0.386f, 0.888f, 0.0f);
        glVertex2f(0, 0);
        glColor3f(0.486f, 0.988f, 0.0f);
        glVertex2f(0, 142);
        glColor3f(0.586f, 1.0f, 0.1f);
        glVertex2f(1150, 240);
        glColor3f(0.386f, 0.888f, 0.0f);
        glVertex2f(1150, 0);
        glEnd();
    }

    void drawCircle(float cx, float cy, float r, int segments = 100) {
        float angle;
        glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            angle = 2.0f * 3.1415926f * i / segments;
            glVertex2f(cx + cos(angle) * r, cy + sin(angle) * r);
        }
        glEnd();
    }

    void CLOUD(float x, float y) {
        glPushMatrix();
        glTranslatef(cloudOffsetX, 0.0f, 0.0f);
        glColor3f(0.98f, 0.98f, 0.98f);
        drawCircle(x, y, 35);
        drawCircle(x - 25, y, 30);
        drawCircle(x + 25, y, 30);
        drawCircle(x - 15, y + 25, 25);
        drawCircle(x + 15, y + 25, 25);

        // Cloud shadow
        glColor3f(0.88f, 0.88f, 0.88f);
        drawCircle(x - 5, y - 5, 30);
        drawCircle(x - 30, y - 5, 25);
        glPopMatrix();
    }

    void SUN() {
        if (!isDay) return;

        float cx = 1000, cy = 600, r = 40;

        // Sun glow effect
        glColor4f(1.0f, 0.9f, 0.3f, 0.3f);
        drawCircle(cx, cy, r + 20);

        // Main sun
        glColor3f(1.0f, 0.843f, 0.0f);
        drawCircle(cx, cy, r);

        // Sun rays
        glColor3f(1.0f, 0.8f, 0.2f);
        glLineWidth(3.0);
        glBegin(GL_LINES);
        for (int i = 0; i < 12; i++) {
            float angle = i * 2.0f * 3.1415926f / 12.0f;
            float x1 = cx + r * cos(angle);
            float y1 = cy + r * sin(angle);
            float x2 = cx + (r + 25) * cos(angle);
            float y2 = cy + (r + 25) * sin(angle);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        glEnd();
    }

    void MOON() {
        if (isDay) return;

        float cx = 1000, cy = 600, r = 35;

        // Moon glow
        glColor4f(1.0f, 1.0f, 0.95f, 0.2f);
        drawCircle(cx, cy, r + 15);

        // Main moon
        glColor3f(1.0f, 1.0f, 0.95f);
        drawCircle(cx, cy, r);

        // Moon craters
        glColor3f(0.9f, 0.9f, 0.85f);
        drawCircle(cx - 10, cy + 10, 5);
        drawCircle(cx + 15, cy - 5, 7);
        drawCircle(cx + 5, cy + 15, 4);
    }

    void RIVER() {
        glBegin(GL_POLYGON);
        // River with gradient
        glColor3f(0.4f, 0.6f, 0.8f);
        glVertex2f(0, 142);
        glColor3f(0.5f, 0.7f, 0.9f);
        glVertex2f(1150, 240);
        glColor3f(0.6f, 0.8f, 1.0f);
        glVertex2f(1150, 440);
        glColor3f(0.4f, 0.6f, 0.8f);
        glVertex2f(0, 480);
        glEnd();
    }

    void TREE(float x, float y) {
        // Trunk with gradient
        glBegin(GL_POLYGON);
        glColor3f(0.45f, 0.22f, 0.05f);
        glVertex2f(x - 20, y);
        glColor3f(0.55f, 0.27f, 0.07f);
        glVertex2f(x + 20, y);
        glVertex2f(x + 20, y + 120);
        glColor3f(0.45f, 0.22f, 0.05f);
        glVertex2f(x - 20, y + 120);
        glEnd();

        // Tree foliage layers
        glColor3f(0.0f, 0.7f, 0.15f);
        drawCircle(x, y + 150, 50);

        glColor3f(0.0f, 0.65f, 0.1f);
        drawCircle(x - 40, y + 140, 45);
        drawCircle(x + 40, y + 140, 45);

        glColor3f(0.0f, 0.6f, 0.05f);
        drawCircle(x - 25, y + 120, 40);
        drawCircle(x + 25, y + 120, 40);
        drawCircle(x, y + 170, 35);
    }

    void BUSH(float x, float y) {
        glColor3f(0.0f, 0.7f, 0.2f);
        drawCircle(x, y, 20);

        glColor3f(0.0f, 0.65f, 0.15f);
        drawCircle(x - 15, y - 8, 18);
        drawCircle(x + 15, y - 8, 18);

        glColor3f(0.0f, 0.6f, 0.1f);
        drawCircle(x - 20, y, 15);
        drawCircle(x + 20, y, 15);
    }

    void WOODEN_SIGNBOARD(float x, float y) {
        // Enhanced wooden plank with 3D effect
        glBegin(GL_POLYGON);
        glColor3f(0.65f, 0.37f, 0.17f);
        glVertex2f(x - 120, y);
        glColor3f(0.75f, 0.47f, 0.27f);
        glVertex2f(x + 120, y);
        glColor3f(0.7f, 0.42f, 0.22f);
        glVertex2f(x + 110, y + 50);
        glColor3f(0.6f, 0.32f, 0.12f);
        glVertex2f(x - 110, y + 50);
        glEnd();

        // Plank border with thickness
        glColor3f(0.36f, 0.20f, 0.09f);
        glLineWidth(4);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - 120, y);
        glVertex2f(x + 120, y);
        glVertex2f(x + 110, y + 50);
        glVertex2f(x - 110, y + 50);
        glEnd();

        // Enhanced wooden posts with gradient
        glBegin(GL_POLYGON);
        glColor3f(0.35f, 0.18f, 0.05f);
        glVertex2f(x - 90, y - 100);
        glColor3f(0.45f, 0.23f, 0.07f);
        glVertex2f(x - 70, y - 100);
        glVertex2f(x - 70, y);
        glColor3f(0.35f, 0.18f, 0.05f);
        glVertex2f(x - 90, y);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.35f, 0.18f, 0.05f);
        glVertex2f(x + 70, y - 100);
        glColor3f(0.45f, 0.23f, 0.07f);
        glVertex2f(x + 90, y - 100);
        glVertex2f(x + 90, y);
        glColor3f(0.35f, 0.18f, 0.05f);
        glVertex2f(x + 70, y);
        glEnd();

        // Render text with shadow effect
        const char* text = "MONPURA";
        void* font = GLUT_BITMAP_TIMES_ROMAN_24;

        // Text shadow
        glColor3f(0.2f, 0.2f, 0.2f);
        renderBitmapString(x - 58, y + 13, font, text);

        // Main text
        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(x - 60, y + 15, font, text);
    }

    void PARK_BENCH(float x, float y) {
        // Enhanced bench with 3D effect
        // Seat base
        glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.25f, 0.05f);
        glVertex2f(x - 50, y);
        glColor3f(0.7f, 0.4f, 0.15f);
        glVertex2f(x + 50, y);
        glColor3f(0.6f, 0.3f, 0.1f);
        glVertex2f(x + 50, y + 15);
        glColor3f(0.4f, 0.2f, 0.05f);
        glVertex2f(x - 50, y + 15);
        glEnd();

        // Backrest with cushion effect
        glBegin(GL_POLYGON);
        glColor3f(0.6f, 0.35f, 0.1f);
        glVertex2f(x - 50, y + 25);
        glColor3f(0.8f, 0.5f, 0.2f);
        glVertex2f(x + 50, y + 25);
        glColor3f(0.7f, 0.45f, 0.15f);
        glVertex2f(x + 50, y + 40);
        glColor3f(0.5f, 0.3f, 0.1f);
        glVertex2f(x - 50, y + 40);
        glEnd();

        // Bench legs with shading
        glColor3f(0.3f, 0.15f, 0.05f);
        glLineWidth(6.0f);
        glBegin(GL_LINES);
        glVertex2f(x - 40, y); glVertex2f(x - 40, y - 25);
        glVertex2f(x + 40, y); glVertex2f(x + 40, y - 25);
        glEnd();

        // Backrest supports
        glBegin(GL_LINES);
        glVertex2f(x - 40, y + 15); glVertex2f(x - 40, y + 25);
        glVertex2f(x + 40, y + 15); glVertex2f(x + 40, y + 25);
        glEnd();
    }

    void COTTAGE(float x, float y) {
        // ENHANCED: Larger and more detailed cottage

        // Main house body with gradient and depth
        glBegin(GL_POLYGON);
        glColor3f(0.9f, 0.63f, 0.2f);  // Light orange-brown (top)
        glVertex2f(x - 80, y);
        glColor3f(0.85f, 0.53f, 0.1f); // Medium
        glVertex2f(x + 80, y);
        glColor3f(0.8f, 0.48f, 0.08f); // Darker at top
        glVertex2f(x + 80, y + 100);
        glColor3f(0.88f, 0.58f, 0.15f); // Lighter at bottom
        glVertex2f(x - 80, y + 100);
        glEnd();

        // House outline
        glColor3f(0.7f, 0.4f, 0.05f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - 80, y);
        glVertex2f(x + 80, y);
        glVertex2f(x + 80, y + 100);
        glVertex2f(x - 80, y + 100);
        glEnd();

        // Enhanced roof with overhang
        glColor3f(0.6f, 0.15f, 0.15f); // Dark red
        glBegin(GL_TRIANGLES);
        glVertex2f(x - 100, y + 100);
        glVertex2f(x + 100, y + 100);
        glVertex2f(x, y + 160);
        glEnd();

        // Roof outline
        glColor3f(0.5f, 0.1f, 0.1f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - 100, y + 100);
        glVertex2f(x + 100, y + 100);
        glVertex2f(x, y + 160);
        glEnd();

        // Roof texture lines
        glBegin(GL_LINES);
        for (int i = -80; i <= 80; i += 20) {
            glVertex2f(x + i, y + 100);
            glVertex2f(x + (i * 0.6), y + 130);
        }
        glEnd();

        // Enhanced door with frame
        glBegin(GL_POLYGON);
        glColor3f(0.3f, 0.15f, 0.0f); // Dark brown door
        glVertex2f(x - 25, y);
        glVertex2f(x + 25, y);
        glColor3f(0.4f, 0.2f, 0.0f);
        glVertex2f(x + 25, y + 60);
        glVertex2f(x - 25, y + 60);
        glEnd();

        // Door frame
        glColor3f(0.2f, 0.1f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - 25, y);
        glVertex2f(x + 25, y);
        glVertex2f(x + 25, y + 60);
        glVertex2f(x - 25, y + 60);
        glEnd();

        // Doorknob with highlight
        glColor3f(0.9f, 0.9f, 0.2f);
        drawCircle(x + 18, y + 30, 4);
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(x + 18, y + 30, 2);

        // Enhanced windows with frames and curtains
        // Left window
        glBegin(GL_POLYGON);
        glColor3f(0.8f, 0.95f, 1.0f); // Light blue glass
        glVertex2f(x - 65, y + 60);
        glVertex2f(x - 25, y + 60);
        glVertex2f(x - 25, y + 90);
        glVertex2f(x - 65, y + 90);
        glEnd();

        // Left window frame
        glColor3f(0.3f, 0.2f, 0.1f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - 65, y + 60);
        glVertex2f(x - 25, y + 60);
        glVertex2f(x - 25, y + 90);
        glVertex2f(x - 65, y + 90);
        glEnd();

        // Window cross
        glBegin(GL_LINES);
        glVertex2f(x - 45, y + 60); glVertex2f(x - 45, y + 90);
        glVertex2f(x - 65, y + 75); glVertex2f(x - 25, y + 75);
        glEnd();

        // Right window
        glBegin(GL_POLYGON);
        glColor3f(0.8f, 0.95f, 1.0f);
        glVertex2f(x + 25, y + 60);
        glVertex2f(x + 65, y + 60);
        glVertex2f(x + 65, y + 90);
        glVertex2f(x + 25, y + 90);
        glEnd();

        // Right window frame
        glColor3f(0.3f, 0.2f, 0.1f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + 25, y + 60);
        glVertex2f(x + 65, y + 60);
        glVertex2f(x + 65, y + 90);
        glVertex2f(x + 25, y + 90);
        glEnd();

        // Window cross
        glBegin(GL_LINES);
        glVertex2f(x + 45, y + 60); glVertex2f(x + 45, y + 90);
        glVertex2f(x + 25, y + 75); glVertex2f(x + 65, y + 75);
        glEnd();

        // Chimney
        glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.12f, 0.12f);
        glVertex2f(x + 30, y + 100);
        glVertex2f(x + 60, y + 100);
        glVertex2f(x + 60, y + 140);
        glVertex2f(x + 30, y + 140);
        glEnd();

        // Chimney top
        glBegin(GL_POLYGON);
        glColor3f(0.4f, 0.1f, 0.1f);
        glVertex2f(x + 25, y + 140);
        glVertex2f(x + 65, y + 140);
        glVertex2f(x + 65, y + 150);
        glVertex2f(x + 25, y + 150);
        glEnd();

        // House foundation
        glBegin(GL_POLYGON);
        glColor3f(0.4f, 0.35f, 0.3f);
        glVertex2f(x - 85, y - 10);
        glVertex2f(x + 85, y - 10);
        glColor3f(0.5f, 0.45f, 0.4f);
        glVertex2f(x + 85, y);
        glVertex2f(x - 85, y);
        glEnd();
    }

    void FLOWER(float x, float y) {
        // Flower petals with gradient
        glColor3f(1.0f, 0.6f, 0.8f);
        drawCircle(x + 7, y, 8);
        drawCircle(x - 7, y, 8);
        drawCircle(x, y + 7, 8);
        drawCircle(x, y - 7, 8);

        // Flower center with highlight
        glColor3f(1.0f, 0.9f, 0.3f);
        drawCircle(x, y, 6);
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(x, y, 3);
    }

    void display() {
        // Title with shadow
        glColor3f(0.2f, 0.2f, 0.2f);
        renderBitmapString(537, 738, GLUT_BITMAP_HELVETICA_18, "Monpura Village Scene");
        glColor3f(0.0f, 0.3f, 0.6f);
        renderBitmapString(535, 735, GLUT_BITMAP_HELVETICA_18, "Monpura Village Scene");

        // Instructions
        glColor3f(0.8f, 0.8f, 0.8f);
        renderBitmapString(10, 720, GLUT_BITMAP_9_BY_15, "D: Day/Night  R: Rain  B: Boat Stop/Start");

        AIR();
        LAND_BOUNDARY();
        RIVER();
        LITTLE_BOAT();
        SUN();
        MOON();

        if (!isDay) {
            drawStars(); // Draw stars only at night
        }

        if (isRaining) {
            drawRain(); // Draw rain on top if raining
        }

        BOAT();
        CLOUD(450, 580);
        CLOUD(700, 680);
        CLOUD(150, 650);

        TREE(200, 90);
        TREE(1080, 180);
        TREE(920, 150);
        TREE(720, 40);

        BUSH(100, 50);
        BUSH(280, 60);
        BUSH(850, 160);

        FLOWER(100, 50);
        FLOWER(280, 60);
        FLOWER(850, 160);

        WOODEN_SIGNBOARD(880, 80);
        PARK_BENCH(90, 90);

        // Draw the enhanced cottage
        COTTAGE(1080, 75);
    }

    // --- Updates and Inputs ---

    void update() {
        if (boatMoving && boatSpeed > 0.0f) {
            boatOffsetX -= boatSpeed;
            if (boatOffsetX < -1200) boatOffsetX = 0;
        }

        cloudOffsetX += 0.5f;
        if (cloudOffsetX > 1200) cloudOffsetX = -200;

        if (isRaining) {
            for (int i = 0; i < SCENARIO3_MAX_RAIN; i++) {
                rain[i].y -= rain[i].speed;
                if (rain[i].y < 0) {
                    rain[i].x = rand() % 1150;
                    rain[i].y = 750 + rand() % 100;
                }
            }
        }
    }

    void handleKey(unsigned char key) {
        switch (key) {
        case 'd': case 'D':
            isDay = !isDay;
            break;
        case 'r': case 'R':
            isRaining = !isRaining;
            break;
        case 'b': case 'B':
            boatMoving = !boatMoving;
            break;
        }
    }
}
#endif