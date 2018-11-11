/**
 * @file                main.cpp
 * @brief       Slightly more complex FreeGLUT usage example
 *
 * @author      Achille Peternier (C) SUPSI [achille.peternier@supsi.ch]
 */



//////////////
// #INCLUDE //
//////////////

// GLM:
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// FreeGLUT:
#include <GL/freeglut.h>

// C/C++:
#include <iostream>

#include "point.h"

struct RGBColor {
    float r;
    float g;
    float b;
};

bool isHex(char c){
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

RGBColor getColor(char* color){
    int hexLen = static_cast<int>(strlen("#ffffff"));
    RGBColor rgbColor = RGBColor{};
    if(color[0] == '#') {
        if (strlen(color) == hexLen) {
            // RGB Hex Color
            for (int i = 1; i < hexLen; i++) {
                if (!isHex(color[i])) {
                    return rgbColor;
                }
            }

            char *output = new char[hexLen + 1];
            sprintf(output, "0x%s", color + 1);

            int num = (int) strtol(output, nullptr, 0);

            float r = static_cast<float>((num >> 16 & 0xFF) / 255.0);
            float g = static_cast<float>(((num >> 8) & 0xFF) / 255.0);
            float b = static_cast<float>(((num) & 0xFF) / 255.0);

            rgbColor.r = r;
            rgbColor.g = g;
            rgbColor.b = b;
        }
    }

    return rgbColor;
}

/////////////
// GLOBALS //
/////////////

// Rotation angle:
float angle = 0.0f;
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;
float cubeAngle = 0.0f;
float distance = -45.0f;
int windowId;
bool wireFrame = false;

void setColor(char* hex){
    RGBColor color = getColor(hex);
    glColor3f(color.r, color.g, color.b);
}

void colorOrange(){
    glColor3f(95.0f/100, 31.4f/100, 13.3f/100);
}

void colorGreen(){
    glColor3f(49.8f/100, 72.9f/100, 0.0f/100);
}

void colorBlue(){
    glColor3f(0.0f/100, 64.3f/100, 93.7f/100);
}

void colorYellow(){
    glColor3f(100.0f/100, 72.5f/100, 0.0f/100);
}

void colorGray(){
    glColor3f(28.6f/100, 28.6f/100, 28.6f/100);
}

void colorRed(){
    glColor3f(72.3f/100, 0.0f/100, 0.0f/100);
}

void drawCube(float width){
    glBegin(GL_TRIANGLE_STRIP);
    colorOrange();
    glVertex3f(width/2, -width/2, width/2);
    glVertex3f(-width/2, -width/2, width/2);
    glVertex3f(width/2, width/2, width/2);
    glVertex3f(-width/2, width/2, width/2);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    colorGreen();
    glVertex3f(width/2, -width/2, -width/2);
    glVertex3f(-width/2, -width/2, -width/2);
    glVertex3f(width/2, width/2, -width/2);
    glVertex3f(-width/2, width/2, -width/2);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    colorBlue();
    glVertex3f(width/2, -width/2, -width/2);
    glVertex3f(width/2, width/2, -width/2);
    glVertex3f(width/2, -width/2, width/2);
    glVertex3f(width/2, width/2, width/2);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    colorYellow();
    glVertex3f(-width/2, -width/2, -width/2);
    glVertex3f(-width/2, width/2, -width/2);
    glVertex3f(-width/2, -width/2, width/2);
    glVertex3f(-width/2, width/2, width/2);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    colorGray();
    glVertex3f(-width/2, -width/2, -width/2);
    glVertex3f(width/2, -width/2, -width/2);
    glVertex3f(-width/2, -width/2, width/2);
    glVertex3f(width/2, -width/2, width/2);
    glEnd();


    glBegin(GL_TRIANGLE_STRIP);
    colorRed();
    glVertex3f(-width/2, width/2, -width/2);
    glVertex3f(width/2, width/2, -width/2);
    glVertex3f(-width/2, width/2, width/2);
    glVertex3f(width/2, width/2, width/2);
    glEnd();
}

void drawPlane(float width){
    glBegin(GL_TRIANGLE_STRIP);
    setColor("#8e44ad");
    glVertex3f(width, 0, 0);
    glVertex3f(0, 0, -width);
    glVertex3f(0, 0, width);
    glVertex3f(-width, 0, 0);
    glEnd();
}

void clearColor(char* color){
    int hexLen = static_cast<int>(strlen("#ffffff"));
    if(color[0] == '#') {
        if (strlen(color) == hexLen) {
            // RGB Hex Color
            for(int i=1; i<hexLen; i++){
                if(!isHex(color[i])){
                    return;
                }
            }

            char* output = new char[hexLen + 1];
            sprintf(output, "0x%s", color+1);

            int num = (int) strtol(output, nullptr, 0);

            float r = static_cast<float>((num >> 16 & 0xFF) / 255.0);
            float g = static_cast<float>(((num >> 8) & 0xFF) / 255.0);
            float b = static_cast<float>(((num) & 0xFF) / 255.0);

            glClearColor(r, g, b, 0.0f);
        }
    }
}

void displayCallback() {
    cubeAngle += 0.2f;

    clearColor("#2980b9");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    if (wireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Set a matrix to move our triangle:
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, distance));
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));

    float pos = 0;

    for(int i=0; i<4; i++){
        float cs = 4 - i;
        Point center = {0.0f, pos, 0.0f};
        pos += cs;


        glm::mat4 cubePosition = glm::translate(glm::mat4(1.0f), glm::vec3(center.getX(), center.getY(), center.getZ()));
        glm::mat4 cubeTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0, cs/2, 0));
        glm::mat4 cubeSize = glm::scale(glm::mat4(1.0f), glm::vec3(cs, cs, cs));
        glm::mat4 cubeRotation = glm::rotate(glm::mat4(1.0f), glm::radians(cubeAngle * (i+1)), glm::vec3(0.0f, 1.0f, 0.0f));


        glm::mat4 f = translation * rotationX * rotationY * rotationZ * cubeRotation * cubeTranslation * cubePosition * cubeSize;
        glLoadMatrixf(glm::value_ptr(f));
        drawCube(1.0);
    }

    glm::mat4 planeScaling = glm::scale(glm::mat4(1.0f), glm::vec3(5,5,5));

    glm::mat4 f = translation * rotationX * rotationY * rotationZ * planeScaling;
    glLoadMatrixf(glm::value_ptr(f));

    drawPlane(5.0);

    // Swap this context's buffer:
    glutPostWindowRedisplay(windowId);
    glutSwapBuffers();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time the window gets resized (and once also when created).
 * @param width new window width
 * @param height new window height
 */
void reshapeCallback(int width, int height) {
    std::cout << "[reshape func invoked]" << std::endl;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 1.0f, 100.0f);
    glLoadMatrixf(glm::value_ptr(projection));
    glMatrixMode(GL_MODELVIEW);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time a special keyboard key is pressed.
 * @param key key pressed id
 * @param mouseX mouse X coordinate
 * @param mouseY mouse Y coordinate
 */
void specialCallback(int key, int mouseX, int mouseY) {
    std::cout << "[key pressed]" << std::endl;

    const float speed = 2.0f;
    switch (key) {
        case GLUT_KEY_UP:
            distance -= speed;
            break;

        case GLUT_KEY_DOWN:
            distance += speed;
            break;

        case GLUT_KEY_LEFT:
            angleX += speed;
            break;

        case GLUT_KEY_RIGHT:
            angleX -= speed;
            break;
        default:
            break;
    }

    // Force rendering refresh:
    glutPostWindowRedisplay(windowId);
}

void keyboardCallback(unsigned char c , int x, int y){
    printf("%c pressed\n", c);
    switch(c){
        case 'w':
        case 'W':
            wireFrame = !wireFrame;
            break;
        case 'd':
        case 'D':
            angleY += 2.0f;
            break;
        case 'a':
        case 'A':
            angleY -= 2.0f;
            break;
        default:
            break;
    }
}



//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char *argv[]) {
    // Credits:
    std::cout << "Advanced FreeGLUT example - A. Peternier (C) SUPSI" << std::endl;
    std::cout << std::endl;

    // Init context:
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);

    // FreeGLUT can parse command-line params, in case:
    glutInit(&argc, argv);

    // Set some optional flags:
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Create the window with a specific title:
    windowId = glutCreateWindow("FreeGLUT advanced example");

    // The OpenGL context is now initialized...

    // Set callback functions:
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutSpecialFunc(specialCallback);
    glutKeyboardFunc(keyboardCallback);

    // Check OpenGL version:
    std::cout << "OpenGL context" << std::endl;
    std::cout << "   version  . . : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "   vendor . . . : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "   renderer . . : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "   extensions . : " << glGetString(GL_EXTENSIONS) << std::endl;

    // Additional context info:
    std::cout << "   color bit  . : " << glutGet(GLUT_WINDOW_BUFFER_SIZE)
              << " (red: " << glutGet(GLUT_WINDOW_RED_SIZE)
              << ", green: " << glutGet(GLUT_WINDOW_GREEN_SIZE)
              << ", blue: " << glutGet(GLUT_WINDOW_BLUE_SIZE)
              << ", alpha: " << glutGet(GLUT_WINDOW_ALPHA_SIZE)
              << ")" << std::endl;
    int bits = 0;
    glGetIntegerv(GL_DEPTH_BITS, &bits);
    std::cout << "   depth bit  . : " << glutGet(GLUT_WINDOW_DEPTH_SIZE) << " (max " << bits << ")" << std::endl;
    std::cout << "   stencil bit  : " << glutGet(GLUT_WINDOW_STENCIL_SIZE) << std::endl;
    std::cout << "   double buff. : " << glutGet(GLUT_WINDOW_DOUBLEBUFFER) << std::endl;

    // Enter the main FreeGLUT processing loop:
    glutMainLoop();

    // Done:
    std::cout << "[application terminated]" << std::endl;
    return 0;
}