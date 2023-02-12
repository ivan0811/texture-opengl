#include <GL/glut.h>
#include "Imageloader.h"

// global
    GLuint texId;
    GLfloat angleX = 0, angleY = 0;
// end

struct coor {
    GLfloat pos[2];
};

void resize(int w, int h) {
    const float ar = (float) w/h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45, ar, 1, 100);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

static void quads(
    GLfloat w, GLfloat h,
    GLfloat x, GLfloat y, GLfloat z,
    GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, coor c[]) {

    glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(angle, rx, ry, rz);
        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);
            glTexCoord2fv(c[0].pos);
            glVertex3f(-w/2, -h/2, 0);
            glTexCoord2fv(c[1].pos);
            glVertex3f(w/2, -h/2, 0);
            glTexCoord2fv(c[2].pos);
            glVertex3f(w/2, h/2, 0);
            glTexCoord2fv(c[3].pos);
            glVertex3f(-w/2, h/2, 0);
        glEnd();
    glPopMatrix();
}

static void drawCube(GLfloat x, GLfloat y, GLfloat z,
                     GLfloat posX, GLfloat posY, GLfloat posZ) {
    coor c[4];

    // coor
        c[0].pos[0] = 0;
        c[0].pos[1] = 0.75;
        c[1].pos[0] = 0.33333;
        c[1].pos[1] = 0.75;
        c[2].pos[0] = 0.33333;
        c[2].pos[1] = 1;
        c[3].pos[0] = 0;
        c[3].pos[1] = 1;
    //end
    quads(x, z, posX, (y/2)+posY, posZ, 90, -1, 0, 0, c);
    // coor
        c[0].pos[0] = 0.33333;
        c[0].pos[1] = 0.75;
        c[1].pos[0] = 0.66667;
        c[1].pos[1] = 0.75;
        c[2].pos[0] = 0.66667;
        c[2].pos[1] = 1;
        c[3].pos[0] = 0.33333;
        c[3].pos[1] = 1;
    //end
    quads(x, z, posX, (-y/2)+posY, posZ, 90, 1, 0, 0, c);

    // coor
        c[0].pos[0] = 0.66667;
        c[0].pos[1] = 0.75;
        c[1].pos[0] = 1;
        c[1].pos[1] = 0.75;
        c[2].pos[0] = 1;
        c[2].pos[1] = 1;
        c[3].pos[0] = 0.66667;
        c[3].pos[1] = 1;
    //end
    quads(x, y, posX, posY, (z/2)+posZ, 0, 0, 0, 0, c);
    // coor
        c[0].pos[0] = 0.33333;
        c[0].pos[1] = 0.5;
        c[1].pos[0] = 0.66667;
        c[1].pos[1] = 0.5;
        c[2].pos[0] = 0.66667;
        c[2].pos[1] = 0.75;
        c[3].pos[0] = 0.33333;
        c[3].pos[1] = 0.75;
    //end
    quads(x, y, posX, posY, (-z/2)+posZ, 180, -1, 0, 0, c);

    // coor
        c[0].pos[0] = 0.33333;
        c[0].pos[1] = 0.25;
        c[1].pos[0] = 0.66667;
        c[1].pos[1] = 0.25;
        c[2].pos[0] = 0.66667;
        c[2].pos[1] = 0.5;
        c[3].pos[0] = 0.33333;
        c[3].pos[1] = 0.5;
    //end
    quads(z, y, (-x/2)+posX, posY, posZ, 90, 0, -1, 0, c);
    // coor
        c[0].pos[0] = 0.33333;
        c[0].pos[1] = 0;
        c[1].pos[0] = 0.66667;
        c[1].pos[1] = 0;
        c[2].pos[0] = 0.66667;
        c[2].pos[1] = 0.25;
        c[3].pos[0] = 0.33333;
        c[3].pos[1] = 0.25;
    //end
    quads(z, y, (x/2)+posX, posY, posZ, 90, 0, 1, 0, c);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glLoadIdentity();
    glTranslatef(0, 0, -10);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);

    drawCube(3, 3, 3, 0, 0, 0);

    glDisable(GL_TEXTURE);

    glutSwapBuffers();
}

void special(int key, int x, int y) {
    switch (key)
    {
        case GLUT_KEY_UP:
            angleX++;
            break;
        case GLUT_KEY_DOWN:
            angleX--;
            break;
        case GLUT_KEY_LEFT:
            angleY++;
            break;
        case GLUT_KEY_RIGHT:
            angleY--;
            break;

        default:
            break;
    }
}

void idle() {
    glutPostRedisplay();
}

void getImage() {
    Image *img = loadBMP("C:/Users/Asus/Downloads/GPC/texture/texture.bmp");
    loadTextures(img, &texId, 1);
}

void lightSetup() {
    GLfloat lightPos[] = {0, 0, 5, 1},
            lightDiffuse[] = {0.8, 0.8, 0.8, 1},
            lightAmbient[] = {0.2, 0.2, 0.2, 1},
            lightSpecular[] = {0.5, 0.5, 0.5, 1},
            shine[] = {80};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

    glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void init() {
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);

    lightSetup();

    getImage();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Kubus Texture");

    init();

    glutMainLoop();
    return 0;
}
