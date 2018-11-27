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
#include <ctime>

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

float rc_r = 1.0f;
float rc_g = 1.0f;
float rc_b = 1.0f;

float light_angle = 0;
int light_intensity = 0;

const glm::vec4 light_ambient{0.0f, 0.0f, 0.0f, 1.0f};
const glm::vec4 light_diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
const glm::vec4 light_specular{ 1.0f, 1.0f, 1.0f, 1.0f };
const glm::vec4 light_direction{ 0, 0, 0, 1.0f };
glm::vec4 light_position{ 0.0f, 5.0f, 5.0f, 0.0f };

const glm::vec4 mat_ambient{ 0.7f, 0.7f, 0.7f, 1.0f };
const glm::vec4 mat_diffuse{ 0.8f, 0.8f, 0.8f, 1.0f };
const glm::vec4 mat_specular{ 1.0f, 1.0f, 1.0f, 1.0f };
const float high_shininess{ 20.0f };

int windowId;
bool wireFrame = false;
bool showNormalVector = false;
bool gouraudShading = false;

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

void c_PA(float width){
	glVertex3f(-width/2, width/2, width/2);
}

void c_PB(float width){
	glVertex3f(width/2, width/2, width/2);
}

void c_PC(float width){
	glVertex3f(-width/2, -width/2, width/2);
}

void c_PD(float width){
	glVertex3f(width/2, -width/2, width/2);
}

void c_PE(float width){
	glVertex3f(width/2, -width/2, -width/2);
}

void c_PF(float width){
	glVertex3f(-width/2, -width/2, -width/2);
}

void c_PG(float width){
	glVertex3f(width/2, width/2, -width/2);
}

void c_PH(float width){
	glVertex3f(-width/2, width/2, -width/2);
}

void drawArrow(float x, float y, float z, float rx, float ry, float rz){
	double arrow_length = 0.3;
	glPushMatrix();
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glTranslated(x, y, z);
		glutSolidCylinder(0.02, arrow_length, 50, 50);
		glTranslated(0, 0, arrow_length);
		glutSolidCone(0.05, arrow_length*0.85, 50, 50);
	glPopMatrix();
}

void drawCube(float width, bool showNormal){
	glBegin(GL_TRIANGLE_STRIP);
	// Front Face (facing the camera)
	glNormal3f(0.0f, 0.0f, 1.0f);
	c_PB(width);
	c_PA(width);
	c_PD(width);
	c_PC(width);
	glEnd();

	if(showNormal) {
		drawArrow(0.0f, 0.0f, width / 2, 0, 0, 0);
	}

	glBegin(GL_TRIANGLE_STRIP);
	// Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	c_PH(width);
	c_PG(width);
	c_PF(width);
	c_PE(width);
	glEnd();

	if(showNormal) {
		drawArrow(0.0f, 0.0f, width / 2, 0, 180, 0);
	}

	glBegin(GL_TRIANGLE_STRIP);
	// Right Face
	glNormal3f(1.0f, 0.0f, 0.0f);
	c_PG(width);
	c_PB(width);
	c_PE(width);
	c_PD(width);
	glEnd();

	if(showNormal) {
		drawArrow(0.0f, 0.0f, width/2, 0, 90, 0);
	}

	glBegin(GL_TRIANGLE_STRIP);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	c_PA(width);
	c_PH(width);
	c_PC(width);
	c_PF(width);
	glEnd();

	if(showNormal) {
		drawArrow(0.0f, 0.0f, width/2, 0, -90, 0);
	}

	glBegin(GL_TRIANGLE_STRIP);
	// Bottom Face
	c_PD(width);
	c_PC(width);
	c_PE(width);
	c_PF(width);
	glEnd();

	if(showNormal) {
		drawArrow(0.0f, 0.0f, width/2, 90, 0, 0);
	}


	glBegin(GL_TRIANGLE_STRIP);
	// Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);
	c_PB(width);
	c_PG(width);
	c_PA(width);
	c_PH(width);
	glEnd();

	if(showNormal) {
		drawArrow(0.0f, 0.0f, width/2, -90, 0, 0);
	}
}

void drawPlane(float width){
    glBegin(GL_TRIANGLE_STRIP);
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

void loadCubeMaterial(){
	glm::vec4 ambient(0.7f, 0.7f, 0.7f, 1.0f );
	glm::vec4 diffuse(0.8f, 0.8f, 0.8f, 1.0f);
	glm::vec4 specular(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 emission(0, 0, 0, 1.0f);

	int shininess = 80;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
				 glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
				 glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
				 glm::value_ptr(specular));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));

	glColor3d(rc_r,rc_g,rc_b);
}

void loadLightMaterial(){
	glm::vec4 ambient(0.7f, 0.7f, 0.7f, 1.0f );
	glm::vec4 diffuse(0.8f, 0.8f, 0.8f, 1.0f);
	glm::vec4 specular(1,1,1, 1.0f);

	glm::vec4 mat_emission(1,1,1, 1.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
				 glm::value_ptr(mat_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
				 glm::value_ptr(mat_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
				 glm::value_ptr(mat_specular));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(mat_emission));

	glColor3d(1,1,1);
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

    if(gouraudShading){
    	glShadeModel(GL_SMOOTH);
    } else {
    	glShadeModel(GL_FLAT);
    }

    // Set a matrix to move our triangle:
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, distance));
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


        glm::mat4 f = translation * rotationX * rotationY * rotationZ * cubeTranslation * cubePosition * cubeSize;
		loadCubeMaterial();
        glLoadMatrixf(glm::value_ptr(f));
        drawCube(1.0, showNormalVector);
    }

    loadCubeMaterial();

	glutSolidCylinder(0.1, 2.0, 50, 50);

    glm::mat4 planeScaling = glm::scale(glm::mat4(1.0f), glm::vec3(5,5,5));

    glm::mat4 f = translation * rotationX * rotationY * rotationZ * planeScaling;
    glLoadMatrixf(glm::value_ptr(f));

    drawPlane(5.0);

    glPushMatrix();
		glTranslatef(2.0, 0.5f, 0.0);
		loadCubeMaterial();
		glutSolidSphere(0.5f, 50, 50);
	glPopMatrix();

	glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(light_position));
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light_intensity);

	glPushMatrix();
		glTranslatef(light_position[0], light_position[1], light_position[2]);
		loadLightMaterial();
		glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

    // Swap this context's buffer:
    glutPostWindowRedisplay(windowId);
    glutSwapBuffers();
}


void reshapeCallback(int width, int height) {
    std::cout << "[reshape func invoked]" << std::endl;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 1.0f, 100.0f);
    glLoadMatrixf(glm::value_ptr(projection));
    glMatrixMode(GL_MODELVIEW);
}

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
    	case 'n':
    	case 'N':
    		showNormalVector = !showNormalVector;
    		break;
    	case 'r':
    	case 'R':
    		rc_r = rand() * 1.0f / RAND_MAX * 1.0f;
    		rc_g = rand() * 1.0f / RAND_MAX * 1.0f;
    		rc_b = rand() * 1.0f / RAND_MAX * 1.0f;
    		break;
    	case 'j':
    	case 'J':
    		//light_position[0] -= 0.5;
    		light_angle -= 1;
			light_position[0] = 2.0f * sin(glm::radians(light_angle));
			light_position[2] = 2.0f * cos(glm::radians(light_angle));
    		break;
    	case 'l':
    	case 'L':
    		//light_position[0] += 0.5;
    		light_angle += 1;
			light_position[0] = 2.0f * sin(glm::radians(light_angle));
			light_position[2] = 2.0f * cos(glm::radians(light_angle));
			break;
		case 'i':
		case 'I':
			light_position[1] += 0.5;
			break;
		case 'k':
		case 'K':
			light_position[1] -= 0.5;
			break;
		case 's':
		case 'S':
			gouraudShading = !gouraudShading;
			break;
		case '<':
			light_intensity += 1;
			if(light_intensity > 128){
				light_intensity = 128;
			}
			break;
    	case 'y':
    	case 'Y':
			light_intensity -= 1;
			if(light_intensity < 0){
				light_intensity = 0;
			}
    		break;
        default:
            break;
    }
}



int main(int argc, char *argv[]) {

    std::srand(std::time(nullptr));

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

    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  glm::value_ptr(light_ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  glm::value_ptr(light_diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(light_specular));
	glDisable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  glm::value_ptr(light_ambient));
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  glm::value_ptr(light_diffuse));
	glLightfv(GL_LIGHT1, GL_SPECULAR, glm::value_ptr(light_specular));
	glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(light_position));
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, glm::value_ptr(light_direction));

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

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