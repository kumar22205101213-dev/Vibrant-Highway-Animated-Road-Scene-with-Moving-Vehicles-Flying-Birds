#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>

float tx = 10, bx = 10, shift = 0;
float bird_tx = -200;
float bus_x = -600;
float moto_x = -800;
float bike_x = -1000;

int traffic_state = 0;
float traffic_timer = 0;

bool is_day = true;
float cycle_timer = 0.0f;

bool snow_enabled = true;
float snow_x[150];
float snow_y[150];

// ==================== Basic Shapes ====================
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
    }
    glEnd();
}

void round(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        glVertex2f(cx + rx * cos(angle), cy + ry * sin(angle));
    }
    glEnd();
}

// ==================== Birds ====================
void birds()
{
    glPushMatrix();
    glTranslatef(bird_tx, 0, 0);
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON); glVertex2f(50,400); glVertex2f(70,400); glVertex2f(75,410); glVertex2f(65,415); glVertex2f(50,410); glEnd();
    glBegin(GL_TRIANGLES); glVertex2f(70,400); glVertex2f(80,402); glVertex2f(70,410); glEnd();
    glColor3ub(255,140,0); glBegin(GL_TRIANGLES); glVertex2f(80,402); glVertex2f(88,406); glVertex2f(80,410); glEnd();
    glColor3ub(165,42,42); glBegin(GL_POLYGON); glVertex2f(55,405); glVertex2f(68,390); glVertex2f(73,410); glEnd();
    glColor3ub(210,105,30); glBegin(GL_TRIANGLES); glVertex2f(50,405); glVertex2f(40,400); glVertex2f(40,410); glEnd();

    glColor3ub(210,105,30);
    glBegin(GL_POLYGON); glVertex2f(140,370); glVertex2f(160,370); glVertex2f(165,380); glVertex2f(155,385); glVertex2f(140,380); glEnd();
    glBegin(GL_TRIANGLES); glVertex2f(160,370); glVertex2f(170,372); glVertex2f(160,380); glEnd();
    glColor3ub(255,140,0); glBegin(GL_TRIANGLES); glVertex2f(170,372); glVertex2f(178,376); glVertex2f(170,380); glEnd();
    glColor3ub(165,42,42); glBegin(GL_POLYGON); glVertex2f(145,375); glVertex2f(158,360); glVertex2f(163,380); glEnd();
    glColor3ub(210,105,30); glBegin(GL_TRIANGLES); glVertex2f(140,375); glVertex2f(130,370); glVertex2f(130,380); glEnd();

    glColor3ub(210,105,30);
    glBegin(GL_POLYGON); glVertex2f(230,440); glVertex2f(250,440); glVertex2f(255,450); glVertex2f(245,455); glVertex2f(230,450); glEnd();
    glBegin(GL_TRIANGLES); glVertex2f(250,440); glVertex2f(260,442); glVertex2f(250,450); glEnd();
    glColor3ub(255,140,0); glBegin(GL_TRIANGLES); glVertex2f(260,442); glVertex2f(268,446); glVertex2f(260,450); glEnd();
    glColor3ub(165,42,42); glBegin(GL_POLYGON); glVertex2f(235,445); glVertex2f(248,430); glVertex2f(253,450); glEnd();
    glColor3ub(210,105,30); glBegin(GL_TRIANGLES); glVertex2f(230,445); glVertex2f(220,440); glVertex2f(220,450); glEnd();
    glPopMatrix();

    bird_tx += 0.25f;
    if (bird_tx > 600) bird_tx = -250;
}

// ==================== Vehicles ====================
void bus() {
    glPushMatrix(); glTranslatef(bus_x, 0, 0);
    glColor3ub(255, 215, 0); glBegin(GL_POLYGON); glVertex2d(300,40); glVertex2d(420,40); glVertex2d(420,110); glVertex2d(300,110); glEnd();
    glColor3ub(173,216,230);
    glBegin(GL_POLYGON); glVertex2d(310,75); glVertex2d(340,75); glVertex2d(340,105); glVertex2d(310,105); glEnd();
    glBegin(GL_POLYGON); glVertex2d(350,75); glVertex2d(380,75); glVertex2d(380,105); glVertex2d(350,105); glEnd();
    glBegin(GL_POLYGON); glVertex2d(390,75); glVertex2d(415,75); glVertex2d(415,105); glVertex2d(390,105); glEnd();
    glColor3ub(0,0,0); circle(12,16,325,40); circle(12,16,395,40);
    glColor3ub(245,245,245); circle(7,10,325,40); circle(7,10,395,40);
    glPopMatrix();
    bus_x += 0.45f; if(bus_x > 650) bus_x = -550;
}

void motorcycle() {
    glPushMatrix(); glTranslatef(moto_x, 0, 0);
    glColor3ub(255,0,0); glBegin(GL_POLYGON); glVertex2d(200,45); glVertex2d(260,45); glVertex2d(255,65); glVertex2d(210,65); glEnd();
    glColor3ub(0,0,0); glBegin(GL_POLYGON); glVertex2d(215,65); glVertex2d(245,65); glVertex2d(245,72); glVertex2d(220,72); glEnd();
    glColor3ub(0,0,0); circle(8,11,215,40); circle(8,11,255,40);
    glColor3ub(200,200,200); circle(4,6,215,40); circle(4,6,255,40);
    glPopMatrix();
    moto_x += 0.95f; if(moto_x > 600) moto_x = -350;
}

void bicycle() {
    glPushMatrix(); glTranslatef(bike_x, 0, 0);
    glColor3ub(0,0,139);
    glBegin(GL_LINES); glVertex2d(150,50); glVertex2d(180,70); glVertex2d(180,70); glVertex2d(210,50);
    glVertex2d(150,50); glVertex2d(210,50); glVertex2d(180,70); glVertex2d(195,40); glEnd();
    glColor3ub(0,0,0); circle(10,13,160,40); circle(10,13,205,40);
    glColor3ub(255,255,255); circle(5,7,160,40); circle(5,7,205,40);
    glColor3ub(255,0,0); circle(6,8,185,80);
    glPopMatrix();
    bike_x += 0.28f; if(bike_x > 600) bike_x = -400;
}

// ==================== ONLY Traffic Light (No lamp behind it) ====================
void trafficLight() {
    glColor3ub(50,50,50);
    glBegin(GL_POLYGON); glVertex2d(70,80); glVertex2d(78,80); glVertex2d(78,220); glVertex2d(70,220); glEnd();
    glColor3ub(30,30,30);
    glBegin(GL_POLYGON); glVertex2d(55,180); glVertex2d(93,180); glVertex2d(93,240); glVertex2d(55,240); glEnd();

    if(traffic_state == 0){ // Red
        glColor3ub(255,0,0); circle(8,12,74,225);
        glColor3ub(80,80,80); circle(8,12,74,205); circle(8,12,74,185);
    }
    else if(traffic_state == 1){ // Yellow
        glColor3ub(80,80,80); circle(8,12,74,225); circle(8,12,74,185);
        glColor3ub(255,255,0); circle(8,12,74,205);
    }
    else { // Green
        glColor3ub(80,80,80); circle(8,12,74,225); circle(8,12,74,205);
        glColor3ub(0,255,0); circle(8,12,74,185);
    }
}

// ==================== Serial Street Lamps (along the road) ====================
void streetLamp(float x)
{
    // Pole
    glColor3ub(40,40,40);
    glBegin(GL_POLYGON);
    glVertex2d(x, 50); glVertex2d(x+6, 50);
    glVertex2d(x+6, 165); glVertex2d(x, 165);
    glEnd();

    // Arm
    glBegin(GL_POLYGON);
    glVertex2d(x+6, 155); glVertex2d(x+28, 155);
    glVertex2d(x+28, 160); glVertex2d(x+6, 160);
    glEnd();

    // Lamp head
    if(is_day)
        glColor3ub(220, 220, 180);
    else
        glColor3ub(255, 240, 80);

    glBegin(GL_POLYGON);
    glVertex2d(x+20, 155); glVertex2d(x+36, 155);
    glVertex2d(x+36, 168); glVertex2d(x+20, 168);
    glEnd();

    circle(9, 13, x+28, 162);
}

void drawAllStreetLamps()
{
    streetLamp(130);
    streetLamp(230);
    streetLamp(330);
    streetLamp(430);
    streetLamp(530);
}

// ==================== Snow ====================
void snowEffect()
{
    if(!snow_enabled) return;
    glColor3ub(255, 255, 255);
    glPointSize(3.5);
    glBegin(GL_POINTS);
    for(int i = 0; i < 150; i++)
        glVertex2f(snow_x[i], snow_y[i]);
    glEnd();
    glPointSize(1.0);

    for(int i = 0; i < 150; i++)
    {
        snow_y[i] -= 1.8f + (i % 3);
        snow_x[i] += sin(i) * 0.6f;
        if(snow_y[i] < 0)
        {
            snow_y[i] = 500 + (rand() % 100);
            snow_x[i] = rand() % 520;
        }
    }
}

// ==================== Sky ====================
void drawSky()
{
    if(is_day)
        glColor3ub(173, 216, 230);
    else
        glColor3ub(10, 15, 50);

    glBegin(GL_POLYGON);
    glVertex2d(0,0); glVertex2d(500,0); glVertex2d(500,500); glVertex2d(0,500);
    glEnd();

    if(!is_day){
        glColor3ub(240, 240, 255);
        circle(22, 28, 420, 420); // Moon
    }
}

// ==================== Other Objects ====================
void Bushes() {
    glColor3ub(34,139,34); circle(20,30,20,180); circle(20,30,40,210); circle(20,30,60,180);
    glColor3ub(107,142,35); circle(20,30,430,180); circle(20,30,450,210); circle(20,30,470,180);
    glColor3ub(34,139,34); circle(20,30,490,180); circle(20,30,510,210);
}

void road() {
    glColor3ub(0,128,0); glBegin(GL_POLYGON); glVertex2d(0,0); glVertex2d(500,0); glVertex2d(500,75); glVertex2d(0,75); glEnd();
    glColor3ub(105,105,105); glBegin(GL_POLYGON); glVertex2d(0,0); glVertex2d(500,0); glVertex2d(500,50); glVertex2d(0,50); glEnd();
    glColor3ub(255,255,255);
    for(int i=0; i<10; i++){
        glBegin(GL_POLYGON); glVertex2d(15+i*50,20); glVertex2d(45+i*50,20);
        glVertex2d(45+i*50,30); glVertex2d(15+i*50,30); glEnd();
    }
}

void sun() {
    if(is_day){
        glColor3ub(255,255,0); circle(20,30,450,450);
    }
}

void tree() {
    glColor3ub(139,69,19); glBegin(GL_POLYGON); glVertex2d(75,180); glVertex2d(85,180); glVertex2d(85,350); glVertex2d(75,350); glEnd();
    glColor3ub(34,139,34); circle(30,40,85,370); circle(20,30,90,340); circle(20,30,65,395);
    glColor3ub(50,205,50); circle(40,50,45,360); circle(30,30,60,330); circle(20,30,30,300); circle(20,30,60,300);
    glColor3ub(139,69,19);
    glBegin(GL_POLYGON); glVertex2d(40,180); glVertex2d(50,180); glVertex2d(50,296);
    glVertex2d(60,320); glVertex2d(55,326); glVertex2d(50,300); glVertex2d(50,350); glVertex2d(45,350); glVertex2d(45,310); glEnd();
}

void little_tree() {
    int posx[] = {0,65,125,190,300,365,425,490};
    for(int i=0; i<8; i++){
        glColor3ub(139,69,19);
        glBegin(GL_POLYGON); glVertex2d(posx[i],60); glVertex2d(posx[i]+10,60); glVertex2d(posx[i]+10,100); glVertex2d(posx[i],100); glEnd();
        glColor3ub(50,205,50);
        circle(15,20,posx[i],110); circle(15,20,posx[i]+10,110); circle(15,20,posx[i]+5,130);
    }
}

void clouds() {
    glColor3ub(255,255,255);
    round(20,30,90+shift,460); round(15,20,110+shift,460); round(15,20,70+shift,460);
    round(20,30,185+shift,430); round(15,20,205+shift,430); round(15,20,165+shift,430);
}

void car() {
    glPushMatrix(); glTranslatef(tx,0,0);
    glColor3ub(0,191,255);
    glBegin(GL_POLYGON); glVertex2d(410,40); glVertex2d(490,40); glVertex2d(485,70); glVertex2d(410,70); glEnd();
    glBegin(GL_POLYGON); glVertex2d(420,70); glVertex2d(475,70); glVertex2d(465,100); glVertex2d(430,100); glEnd();
    glColor3ub(220,220,220);
    glBegin(GL_POLYGON); glVertex2d(425,70); glVertex2d(445,70); glVertex2d(445,90); glVertex2d(430,90); glEnd();
    glBegin(GL_POLYGON); glVertex2d(450,70); glVertex2d(470,70); glVertex2d(465,90); glVertex2d(450,90); glEnd();
    glColor3ub(0,0,0); circle(10,14,435,40); circle(10,14,465,40);
    glColor3ub(245,245,245); circle(6,10,435,40); circle(6,10,465,40);
    glPopMatrix();
    tx += 0.32f; if(tx > 0) tx = -520;
}

void truck() {
    glPushMatrix(); glTranslatef(bx,0,0);
    glColor3ub(255,69,0); glBegin(GL_POLYGON); glVertex2d(450,40); glVertex2d(505,40); glVertex2d(505,110); glVertex2d(450,110); glEnd();
    glColor3ub(0,128,128); glBegin(GL_POLYGON); glVertex2d(505,40); glVertex2d(535,40); glVertex2d(535,70); glVertex2d(505,70); glEnd();
    glBegin(GL_POLYGON); glVertex2d(505,70); glVertex2d(525,70); glVertex2d(515,90); glVertex2d(505,90); glEnd();
    glColor3ub(220,220,220); glBegin(GL_POLYGON); glVertex2d(505,70); glVertex2d(520,70); glVertex2d(515,85); glVertex2d(505,85); glEnd();
    glColor3ub(0,0,0); circle(10,14,460,40); circle(10,14,510,40);
    glColor3ub(245,245,245); circle(6,10,460,40); circle(6,10,510,40);
    glPopMatrix();
    bx += 0.72f; if(bx > 0) bx = -550;
}

void flower() {
    glColor3ub(186,85,211);
    circle(3,5,450,210); circle(3,5,455,205); circle(3,5,455,215); circle(3,5,460,210);
    glColor3ub(255,215,0); circle(3,5,455,210);
    glColor3ub(186,85,211);
    circle(3,5,440,195); circle(3,5,440,185); circle(3,5,435,190); circle(3,5,445,190);
    glColor3ub(255,215,0); circle(3,5,440,190);
    glColor3ub(186,85,211);
    circle(3,5,470,195); circle(3,5,470,185); circle(3,5,465,190); circle(3,5,475,190);
    glColor3ub(255,215,0); circle(3,5,470,190);

    glColor3ub(186,85,211); circle(3,5,30,205); circle(3,5,30,195); circle(3,5,25,200); circle(3,5,35,200);
    glColor3ub(255,215,0); circle(3,5,30,200);
    glColor3ub(186,85,211); circle(3,5,10,210);
    glColor3ub(255,215,0); circle(3,5,10,215); circle(3,5,10,205); circle(3,5,5,210); circle(3,5,15,210);
}

// ==================== Display ====================
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();

    Bushes();
    glColor3ub(34,139,34);
    glBegin(GL_POLYGON); glVertex2d(0,0); glVertex2d(500,0); glVertex2d(500,180); glVertex2d(0,180); glEnd();

    little_tree();
    road();
    sun();
    clouds();
    birds();
    tree();

    trafficLight();           // Only traffic light here
    drawAllStreetLamps();     // Serial lamps along the road (not behind traffic light)

    truck(); car(); bus(); motorcycle(); bicycle();

    flower();
    snowEffect();

    glFlush();
    glutSwapBuffers();
}

// ==================== Timer & Keyboard ====================
void timer(int value)
{
    traffic_timer += 1;
    if(traffic_timer > 110){
        traffic_state = (traffic_state + 1) % 3;
        traffic_timer = 0;
    }

    cycle_timer += 0.6f;
    if(cycle_timer > 1600){
        is_day = !is_day;
        cycle_timer = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void key(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT)  shift -= 5;
    if(key == GLUT_KEY_RIGHT) shift += 5;
    if(key == GLUT_KEY_UP)    snow_enabled = !snow_enabled;
    if(key == GLUT_KEY_DOWN)  is_day = !is_day;
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(0.0, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv)
{
    for(int i = 0; i < 150; i++){
        snow_x[i] = rand() % 520;
        snow_y[i] = rand() % 500 + 100;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Road Scene - Traffic Light + Serial Lamps");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(key);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}
