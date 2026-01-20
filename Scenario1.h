#ifndef SCENARIO1_H
#define SCENARIO1_H

#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream>

#define PI 3.14159265358979323846

namespace Scenario1 {

    // --- Global Variables ---
    float sunny = 660;
    float moony = 160;
    float stary = 230;
    float cloudXOffset = -1000.0;
    bool is_Day = true;
    bool cloudMovingRight = true;
    float boatXOffset = -540.0;
    bool boatMovingRight = true;
    bool animateSunMoon = false;
    bool sunToDown = false;
    bool moonToUp = false;

    void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i++) {
            float angle = PI * i / 180;
            float x = rx * cosf(angle);
            float y = ry * sinf(angle);
            glVertex2f((x + cx), (y + cy));
        }
        glEnd();
    }

    // --- Drawing Functions ---

    void draw_cow() {
        glColor3ub(103, 53, 53);
        glBegin(GL_POLYGON); glVertex2f(200.9, 311.6); glVertex2f(205.9, 300.4); glVertex2f(210.0, 300.3); glVertex2f(206.9, 311.7); glVertex2f(210.8, 319.2); glVertex2f(205.3, 322.7); glVertex2f(199.2, 318.1); glEnd();
        glBegin(GL_POLYGON); glVertex2f(240, 320); glVertex2f(246.4, 301.8); glVertex2f(251.4, 301.4); glVertex2f(247.8, 319.9); glEnd();
        glBegin(GL_POLYGON); glVertex2f(205.3, 322.7); glVertex2f(191.3, 326.4); glVertex2f(190.7, 343.7); glVertex2f(196.6, 350.2); glVertex2f(203.4, 354.4); glVertex2f(235.7, 355.2); glVertex2f(242.1, 354.4); glVertex2f(247.7, 350.6); glVertex2f(252.0, 344.8); glVertex2f(255.8, 339.1); glVertex2f(260, 335); glVertex2f(265.4, 331.3); glVertex2f(230, 320); glVertex2f(210.8, 319.2); glEnd();
        glBegin(GL_POLYGON); glVertex2f(192.3, 311.9); glVertex2f(191.9, 300.3); glVertex2f(187.3, 300.3); glVertex2f(187.4, 317.6); glVertex2f(191.3, 326.5); glVertex2f(205.3, 322.7); glEnd();
        glBegin(GL_POLYGON); glVertex2f(233.6, 300.7); glVertex2f(230.0, 300.9); glVertex2f(230, 320); glVertex2f(240, 320); glEnd();
        glBegin(GL_POLYGON); glVertex2f(265.6, 330.9); glVertex2f(220.9, 319.6); glVertex2f(240, 320); glVertex2f(253.2, 319.2); glVertex2f(266.4, 308.1); glVertex2f(273.3, 308.5); glVertex2f(270.8, 327.4); glVertex2f(268.5, 330.2); glEnd();
        glBegin(GL_POLYGON); glVertex2f(268.5, 330.2); glVertex2f(273.8, 336.3); glVertex2f(273.4, 332.4); glVertex2f(270.8, 327.4); glEnd();
    }

    void draw_day_road(){
        glColor3ub(219,179,79);
        glBegin(GL_POLYGON); glVertex2f(522, 257); glVertex2f(648, 291); glVertex2f(734, 293); glVertex2f(608, 243); glEnd();
        glBegin(GL_POLYGON); glVertex2f(648, 291); glVertex2f(734, 293); glVertex2f(613, 345); glVertex2f(565, 334); glEnd();
        glBegin(GL_POLYGON); glVertex2f(630, 330); glVertex2f(565, 334); glVertex2f(670.5, 372.5); glVertex2f(700, 373); glEnd();
    }

    void draw_night_road(){
        glColor3ub(219,179,89);
        glBegin(GL_POLYGON); glVertex2f(522, 257); glVertex2f(648, 291); glVertex2f(734, 293); glVertex2f(608, 243); glEnd();
        glBegin(GL_POLYGON); glVertex2f(648, 291); glVertex2f(734, 293); glVertex2f(613, 345); glVertex2f(565, 334); glEnd();
        glBegin(GL_POLYGON); glVertex2f(630, 330); glVertex2f(565, 334); glVertex2f(670.5, 372.5); glVertex2f(700, 373); glEnd();
    }

   void draw_day_field() {
        glBegin(GL_POLYGON); glVertex2f(0, 300); glVertex2f(0, 372); glVertex2f(1150, 372); glVertex2f(1150, 200); glVertex2f(466, 270); glVertex2f(225, 271); glEnd();
        draw_cow();
        draw_day_road();

        // 2nd cow
        glPushMatrix(); glTranslated(700, 10, 0); draw_cow(); glPopMatrix();

        // 3rd cow
        glPushMatrix();
        glTranslated(550, 10, 0);
        glRotatef(180, 0, 1, 0);
        draw_cow();
        glPopMatrix();
    }

    void draw_night_field() {
        glBegin(GL_POLYGON); glVertex2f(0, 300); glVertex2f(0, 372); glVertex2f(1150, 372); glVertex2f(1150, 200); glVertex2f(466, 270); glVertex2f(225, 271); glEnd();
        draw_night_road();
    }

    void draw_river_bank() {
        glColor3ub(142, 97, 70);
        glBegin(GL_POLYGON); glVertex2f(472, 282); glVertex2f(1150, 240); glVertex2f(1150, 196); glVertex2f(468, 260); glEnd();
        glBegin(GL_POLYGON); glVertex2f(468, 260); glVertex2f(220, 260); glVertex2f(232, 282); glVertex2f(472, 282); glEnd();
        glBegin(GL_POLYGON); glVertex2f(220, 260); glVertex2f(0, 289); glVertex2f(0, 310); glVertex2f(232, 282); glEnd();
        glLineWidth(7); glColor3ub(114, 69, 44);
        glBegin(GL_LINES); glVertex2f(0, 289); glVertex2f(232, 260); glVertex2f(232, 260); glVertex2f(472, 260); glVertex2f(472, 260); glVertex2f(1150, 200); glEnd();
    }

    void draw_day_boat(){
        glPushMatrix(); glTranslatef(boatXOffset, 0.0, 0.0);
        glColor3ub(27,125,178); circle(140,10,320,68);
        glColor3ub(187,79,53); glBegin(GL_POLYGON); glVertex2f(441, 104); glVertex2f(459, 114); glVertex2f(418.5, 104); glVertex2f(305, 99); glVertex2f(195.5, 103.5); glVertex2f(224, 69); glVertex2f(409, 69); glEnd();
        glColor3ub(147,63,37); glBegin(GL_POLYGON); glVertex2f(224, 69); glVertex2f(409, 69); glVertex2f(424, 83.5); glVertex2f(213, 83.5); glEnd();
        glColor3ub(223,115,36); glBegin(GL_POLYGON); glVertex2f(169, 122); glVertex2f(178, 106); glVertex2f(195.5, 103); glVertex2f(418.5, 104); glVertex2f(459, 114); glVertex2f(494.5, 122); glVertex2f(494.5, 125); glEnd();
        glColor3ub(110,49,35); glBegin(GL_POLYGON); glVertex2f(177, 130); glVertex2f(184, 116); glVertex2f(274, 110); glVertex2f(358, 110); glVertex2f(467, 119); glVertex2f(473.9, 122); glVertex2f(473.9, 125); glVertex2f(385, 135); glVertex2f(253, 135); glEnd();
        glLineWidth(4); glBegin(GL_LINES); glVertex2f(473.9, 125); glVertex2f(544, 132); glEnd();
        glLineWidth(4); glBegin(GL_LINES); glVertex2f(360, 155); glVertex2f(250, 155); glEnd(); glBegin(GL_LINES); glVertex2f(360, 240); glVertex2f(250, 240); glEnd();
        glBegin(GL_POLYGON); glColor3ub(252,196,62); glVertex2f(360, 240); glVertex2f(360, 155); glVertex2f(250,155); glVertex2f(250, 240); glEnd();
        glColor3ub(110,49,35); glBegin(GL_POLYGON); glVertex2f(302, 250); glVertex2f(306, 250); glVertex2f(310.5, 122.5); glVertex2f(302, 122.5); glEnd();
        glLineWidth(2); glColor3ub(110,49,35); glBegin(GL_LINES); glVertex2f(305, 220); glVertex2f(470, 120); glEnd();
        glLineWidth(2); glColor3ub(110,49,35); glBegin(GL_LINES); glVertex2f(305, 230); glVertex2f(500, 128); glEnd();
        glLineWidth(2); glColor3ub(110,49,35); glBegin(GL_LINES); glVertex2f(305, 238); glVertex2f(530, 130); glEnd();
        glColor3ub(254, 3, 16); glBegin(GL_QUADS); glVertex2f(265, 160); glVertex2f(380, 160); glVertex2f(400, 114); glVertex2f(280, 110); glEnd();
        glColor3ub(200,100,0); glBegin(GL_TRIANGLES); glVertex2f(265, 160); glVertex2f(240, 132); glVertex2f(280, 110); glEnd();
        glPopMatrix();
    }

    void draw_night_boat(){
        glPushMatrix(); glTranslatef(boatXOffset, 0.0, 0.0);
        glColor3ub(20,20,116); circle(140,10,320,68);
        glColor3ub(187,79,53); glBegin(GL_POLYGON); glVertex2f(441, 104); glVertex2f(459, 114); glVertex2f(418.5, 104); glVertex2f(305, 99); glVertex2f(195.5, 103.5); glVertex2f(224, 69); glVertex2f(409, 69); glEnd();
        glColor3ub(147,63,37); glBegin(GL_POLYGON); glVertex2f(224, 69); glVertex2f(409, 69); glVertex2f(424, 83.5); glVertex2f(213, 83.5); glEnd();
        glColor3ub(223,115,36); glBegin(GL_POLYGON); glVertex2f(169, 122); glVertex2f(178, 106); glVertex2f(195.5, 103); glVertex2f(418.5, 104); glVertex2f(459, 114); glVertex2f(494.5, 122); glVertex2f(494.5, 125); glEnd();
        glColor3ub(110,49,35); glBegin(GL_POLYGON); glVertex2f(177, 130); glVertex2f(184, 116); glVertex2f(274, 110); glVertex2f(358, 110); glVertex2f(467, 119); glVertex2f(473.9, 122); glVertex2f(473.9, 125); glVertex2f(385, 135); glVertex2f(253, 135); glEnd();
        glLineWidth(4); glBegin(GL_LINES); glVertex2f(473.9, 125); glVertex2f(544, 132); glEnd();
        glLineWidth(4); glBegin(GL_LINES); glVertex2f(360, 155); glVertex2f(250, 155); glEnd(); glBegin(GL_LINES); glVertex2f(360, 240); glVertex2f(250, 240); glEnd();
        glBegin(GL_POLYGON); glColor3ub(252,196,62); glVertex2f(360, 240); glVertex2f(360, 155); glVertex2f(250,155); glVertex2f(250, 240); glEnd();
        glColor3ub(110,49,35); glBegin(GL_POLYGON); glVertex2f(302, 250); glVertex2f(306, 250); glVertex2f(310.5, 122.5); glVertex2f(302, 122.5); glEnd();
        glLineWidth(2); glColor3ub(110,49,35); glBegin(GL_LINES); glVertex2f(305, 220); glVertex2f(470, 120); glEnd();
        glLineWidth(2); glColor3ub(110,49,35); glBegin(GL_LINES); glVertex2f(305, 230); glVertex2f(500, 128); glEnd();
        glLineWidth(2); glColor3ub(110,49,35); glBegin(GL_LINES); glVertex2f(305, 238); glVertex2f(530, 130); glEnd();
        glColor3ub(254, 3, 16); glBegin(GL_QUADS); glVertex2f(265, 160); glVertex2f(380, 160); glVertex2f(400, 114); glVertex2f(280, 110); glEnd();
        glColor3ub(200,100,0); glBegin(GL_TRIANGLES); glVertex2f(265, 160); glVertex2f(240, 132); glVertex2f(280, 110); glEnd();
        glPopMatrix();
    }

    void draw_boat(bool isNight) {
        if (isNight) draw_night_boat(); else draw_day_boat();
    }

    void draw_river(bool isNight) {
        if(isNight) glColor3ub(10, 10, 50); else glColor3ub(41, 169, 221);
        glBegin(GL_POLYGON); glVertex2f(0, 0); glVertex2f(1150, 0); glVertex2f(1150, 200); glVertex2f(0, 300); glVertex2f(225, 271); glVertex2f(466, 270); glEnd();
    }

    void draw_tree() {
        glColor3ub(53,127,11); circle(25,25,630, 495); circle(18,18,600, 480); circle(18,18,580, 460); circle(18,18,570, 440); circle(18,18,590, 420); circle(18,18,615, 410); circle(18,18,640, 415); circle(20,20,666, 420); circle(20,20,695, 415); circle(20,20,725, 415); circle(20,20,750, 425); circle(20,20,750, 445); circle(20,20,735, 470); circle(20,20,710, 490); circle(30,30,670, 500);
        glColor3ub(98,169,41); circle(20,20,730, 445); glColor3ub(53,127,11); circle(18,18,720, 445); glColor3ub(98,169,41); circle(18,18,710, 445); glColor3ub(98,169,41); circle(15,15,730, 470); glColor3ub(98,169,41); circle(18,18,705, 485); glColor3ub(98,169,41); circle(30,30,670, 485); glColor3ub(53,127,11); circle(25,18,695, 460); glColor3ub(98,169,41); circle(18,18,695, 465);
        glColor3ub(142,205,68); circle(25,15,670, 490);
        glColor3ub(98,169,41); circle(15,15,700, 435); glColor3ub(98,169,41); circle(18,18,680, 430);
        glColor3ub(142,205,68); circle(25,15,670, 490); circle(18,18,620, 480); circle(18,18,600, 460); circle(18,18,590, 440); circle(18,18,610, 430); circle(18,18,630, 430); circle(18,18,630, 450); circle(18,18,650, 450); circle(18,18,660, 455); circle(18,18,640, 470);
        glColor3ub(53,127,11); circle(20,20,600, 445); glColor3ub(142,205,68); circle(18,18,610, 445);
        glColor3ub(53,127,11); circle(20,20,650, 445); glColor3ub(142,205,68); circle(18,18,655, 445);
        glColor3ub(209,245,134); circle(10,5,630, 470); circle(10,5,620, 430); circle(5,2,670, 490);
        glBegin(GL_POLYGON); glColor3ub(177,125,76); glVertex2f(672, 392); glVertex2f(665, 405); glVertex2f(667, 408); glVertex2f(676, 399); glVertex2f(682, 411); glVertex2f(684, 409); glVertex2f(680, 395); glVertex2f(681, 360); glVertex2f(672, 360); glEnd();
    }

    void draw_forest() {
        glBegin(GL_POLYGON); glColor3ub(65, 160, 70); glVertex2f(1150, 372); glVertex2f(1150, 450); glVertex2f(600, 372); glEnd();
        glColor3ub(65, 160, 70); circle(72, 25, 100, 380); circle(36, 36, 450, 370); circle(40, 30, 810, 380);
        draw_tree();
        glPushMatrix(); glTranslated(190, 10, 0); draw_tree(); glPopMatrix();
        glPushMatrix(); glTranslated(380, 0, 0); draw_tree(); glPopMatrix();
    }

    void draw_sky(bool isNight) {
        glBegin(GL_POLYGON);
        if(isNight) { glColor3ub(0, 0, 64); glVertex2f(0, 300); glVertex2f(1150, 300); glColor3ub(32, 32, 64); }
        else { glColor3ub(255, 255, 147); glVertex2f(0, 300); glVertex2f(1150, 300); glColor3ub(102, 204, 255); }
        glVertex2f(1150, 750); glVertex2f(0, 750); glEnd();
    }

    void draw_sun() { glColor3ub(253, 183, 77); circle(36, 36, 750, sunny); }
    void draw_moon() { glColor3ub(255, 255, 170); circle(36, 36, 750, moony); }
    void draw_star() {
        if(is_Day) return;
        glColor3ub(255, 255, 255);
        circle(2, 2.3, 50, stary); circle(2, 2.3, 337, stary); circle(2, 2.3, 625, stary); circle(2.5, 2.3, 798, stary - 40);
    }

    void draw_cloud() {
        glColor3ub(254,255,254); circle(30,30,1000+ cloudXOffset,640); circle(30,20,965+ cloudXOffset,665); circle(35,35,930+ cloudXOffset,670); circle(20,18,890+ cloudXOffset,675); circle(20,20,865+ cloudXOffset,680); circle(30,30,830+ cloudXOffset,680); circle(20,20,800+ cloudXOffset,665); circle(10,10,780+ cloudXOffset,650); circle(20,10,770+ cloudXOffset,640); circle(20,10,740+ cloudXOffset,630); circle(20,10,810+ cloudXOffset,640); circle(20,20,810+ cloudXOffset,640);
        glColor3ub(232,241,255); circle(20,5,740+ cloudXOffset,625); circle(12,12,762+ cloudXOffset,630); circle(20,20,785+ cloudXOffset,630); circle(12,12,810+ cloudXOffset,625); circle(20,20,835+ cloudXOffset,615); circle(20,20,865+ cloudXOffset,620); circle(15,15,890+ cloudXOffset,615); circle(30,30,920+ cloudXOffset,625); circle(15,15,955+ cloudXOffset,625); circle(30,20,990+ cloudXOffset,625); circle(15,15,1012+ cloudXOffset,630); circle(15,15,1016+ cloudXOffset,639); circle(15,15,835+ cloudXOffset,639); circle(20,15,865+ cloudXOffset,640); circle(20,20,890+ cloudXOffset,645); circle(15,20,855+ cloudXOffset,655); circle(30,19,890+ cloudXOffset,655); circle(30,19,950+ cloudXOffset,635);
        glColor3ub(254,255,254); circle(30,30,300+ cloudXOffset,640); circle(30,20,265+ cloudXOffset,665); circle(35,35,230+ cloudXOffset,670); circle(20,18,190+ cloudXOffset,675); circle(20,20,165+ cloudXOffset,680); circle(30,30,130+ cloudXOffset,680); circle(20,20,100+ cloudXOffset,665); circle(10,10,80+ cloudXOffset,650); circle(20,20,70+ cloudXOffset,625); circle(20,10,110+ cloudXOffset,640); circle(20,20,110+ cloudXOffset,640); circle(20,20,65+ cloudXOffset,610); circle(20,20,200+ cloudXOffset,640);
        glColor3ub(232,241,255); circle(20,20,70+ cloudXOffset,610); circle(20,20,90+ cloudXOffset,630); circle(20,20,100+ cloudXOffset,620); circle(20,20,100+ cloudXOffset,610); circle(12,12,110+ cloudXOffset,625); circle(20,20,135+ cloudXOffset,615); circle(20,20,165+ cloudXOffset,620); circle(30,30,130+ cloudXOffset,610); circle(15,15,190+ cloudXOffset,615); circle(30,30,220+ cloudXOffset,625); circle(15,15,255+ cloudXOffset,625); circle(30,20,290+ cloudXOffset,625); circle(15,15,312+ cloudXOffset,630); circle(15,15,316+ cloudXOffset,639); circle(15,15,135+ cloudXOffset,639); circle(20,15,165+ cloudXOffset,640); circle(20,20,190+ cloudXOffset,645); circle(15,20,155+ cloudXOffset,655); circle(30,19,190+ cloudXOffset,655); circle(30,19,250+ cloudXOffset,635); circle(40,20,220+ cloudXOffset,610); circle(20,20,260+ cloudXOffset,610); circle(15,15,180+ cloudXOffset,600);
        glColor3ub(254,255,254); circle(30,10,180+ cloudXOffset,660); circle(30,10,270+ cloudXOffset,635); circle(30,10,110+ cloudXOffset,635);
    }


    void init() {

        cloudXOffset = -1000.0;
        boatXOffset = -540.0;
    
    }

    void display() {

        draw_sky(!is_Day);
        draw_sun();
        draw_moon();
        draw_star();
        draw_cloud();
        draw_forest();

        if (is_Day) {
            glColor3ub(137, 172, 49);
            draw_day_field();
        } else {
            glColor3ub(17, 75, 16);
            draw_night_field();
        }

        draw_river(!is_Day);
        draw_river_bank();
        draw_boat(!is_Day);

    }


    void update() {
        // Sun/Moon T
        if (animateSunMoon) {
            if (sunToDown && sunny > 160) sunny -= 10.0f;
            else if (!sunToDown && sunny < 660) sunny += 10.0f;

            if (moonToUp && moony < 660) {
                moony += 10.0f;
                stary += 10.0;
            } else if (!moonToUp && moony > 160) {
                moony -= 10.0f;
                stary -= 10.0f;
            }

            if ((sunToDown && sunny <= 160) || (!sunToDown && sunny >= 660)) animateSunMoon = false;
            if ((moonToUp && moony >= 660) || (!moonToUp && moony <= 160)) animateSunMoon = false;
        }

        // Cloud Animation
        if (cloudMovingRight) {
            cloudXOffset += 2.0f;
            if (cloudXOffset > 1150) cloudXOffset = -1000;
        } else {
            cloudXOffset -= 2.0f;
            if (cloudXOffset < -1150) cloudXOffset = 1000;
        }

        // Boat Animation
        if (boatMovingRight) {
            boatXOffset += 4.5f;
            if (boatXOffset > 1150) boatXOffset = -540;
        }
    }


    void handleKey(unsigned char key) {
        switch (key) {
            case 'd': // Day Trigger
                is_Day = true;
                animateSunMoon = true;
                sunToDown = false;
                moonToUp = false;
                break;
            case 'n': // Night Trigger
                is_Day = false;
                animateSunMoon = true;
                sunToDown = true;
                moonToUp = true;
                break;
            case 'a': // Maual 
                animateSunMoon = !animateSunMoon;
                break;
        }
    }
}
#endif
