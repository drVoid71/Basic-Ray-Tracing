#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "image.h"
#include "camera.h"
#include "shape.h"

GLfloat theta = 0;
GLfloat phi = 0;
GLfloat rho = 10;
const int width = 640;
const int height = 480;

float data[height*width][3];

ShapeSet scene;
Image image(width, height);
Sphere lightSphere(Point(1.0f, 1.0f, 0.0f), 1.0f, Color(1.0f));
PerspectiveCamera camera(Point(0.0f, 1.0f, -10.0f), Vector(0.0f, 1.0f, 0.0f), Vector(), 25.0f * PI / 180.0f, (float)width / (float)height);

float max(float a, float b)
{
	return a > b ? a : b;
}
static void display(void)
{
	GLfloat camX = rho * cos(theta*PI / 180)*sin(phi*PI / 180);
	GLfloat camY = rho * sin(theta*PI / 180);
	GLfloat camZ = rho * cos(theta*PI / 180)*cos(phi*PI / 180);

	// Reduce theta slightly to obtain another point on the same longitude line on the sphere.
	GLfloat dt = 1;
	GLfloat eyeXtemp = -rho * cos((theta - dt)*PI / 180)*sin(phi*PI / 180);
	GLfloat eyeYtemp = -rho * sin((theta - dt)*PI / 180);
	GLfloat eyeZtemp = -rho * cos((theta - dt)*PI / 180)*cos(phi*PI / 180);

	// Connect these two points to obtain the camera's up vector.
	GLfloat upX = eyeXtemp - camX;
	GLfloat upY = eyeYtemp - camY;
	GLfloat upZ = eyeZtemp - camZ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(camX, camY, camZ, 0, 0, 0, upX, upY, upZ);

	glDrawPixels(width, height, GL_RGB, GL_FLOAT, data);

	glutSwapBuffers();
}

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void rayTrace(Image& image, Camera* camera, Shape* scene)
{
	//std::ofstream out("out.ppm");
	//out << "P3\n" << ' ' << 1080 << ' ' << 1920 << ' ' << "255\n";
	for (int x = 0; x < image.getWidth(); x++)
	{
		for (int y = 0; y < image.getHeight(); y++)
		{
			Vector2 screenCoord((2.0f*x) / image.getWidth() - 1.0f, (-2.0f*y) / image.getHeight() + 1.0f);
			Ray ray = camera->makeRay(screenCoord);

			Color* curPixel = image.getPixel(x, y);

			Intersection intersection(ray);
			if (scene->intersect(intersection))
			{
				Vector pi = ray.calculate(intersection.t);
				Vector L = Vector(5.0f, 5.0f, 5.0f) - pi;
				Color asdf = intersection.color;
				Ray shadRay(pi, L);
				Intersection shadInt(shadRay);
				if (scene->doesIntersect(shadRay))
				{
					// shadows: use ambient lighting only
					*curPixel = Color(0.2f)*intersection.color;
				}
				else {
					Vector N = intersection.normal;
					float nl = max(0, dot(N.normalized(), L.normalized()));
					float p = 50.0f;
					float ks = 1.0f;
					Vector r = 2 * (nl)* N.normalized() - L.normalized();
					float rv = max(0, dot(r.normalized(), pi.normalized()));
					// Phong model	=  ambient lighting		+		diffuse lighting		+		specular lighting (includes shininess)
					Color c = Color(0.2f)*intersection.color + (Color(1.0f)*intersection.color*nl) + (ks*Color(1.0f)*pow(rv, p));
					c.r = c.r > 1.0f ? 1.0f : c.r < 0.0f ? 0.0f : c.r;
					c.g = c.g > 1.0f ? 1.0f : c.g < 0.0f ? 0.0f : c.g;
					c.b = c.b > 1.0f ? 1.0f : c.b < 0.0f ? 0.0f : c.b;
					*curPixel = c;
				}
			}
			else
			{
				// background color
				*curPixel = Color(0.5f);
			}
			data[x + (height - y - 1) * width][0] = curPixel->r;
			data[x + (height - y - 1) * width][1] = curPixel->g;
			data[x + (height - y - 1) * width][2] = curPixel->b;
			//out << (int) red << ' ' << (int) green << ' ' << (int) blue << '\n';
		}
	}
	//out.close();
}

GLvoid keyboard(GLubyte key, GLint x, GLint y)
{
	switch (key) {
	case 'i':
		camera.moveForward(1, Vector(0.0f, 1.0f, 0.0f), Vector(), 25.0f * PI / 180.0f, (float)width / (float)height);
		rayTrace(image, &camera, &scene);
		break;
	case 'o':
		camera.moveForward(-1, Vector(0.0f, 1.0f, 0.0f), Vector(), 25.0f * PI / 180.0f, (float)width / (float)height);
		rayTrace(image, &camera, &scene);
		break;
	case 'j':
		camera.moveRight(1, Vector(0.0f, 1.0f, 0.0f), Vector(), 25.0f * PI / 180.0f, (float)width / (float)height);
		rayTrace(image, &camera, &scene);
		break;
	case 'k':
		camera.moveRight(-1, Vector(0.0f, 1.0f, 0.0f), Vector(), 25.0f * PI / 180.0f, (float)width / (float)height);
		rayTrace(image, &camera, &scene);
		break;
	case 27:   /* Exit whenever the Escape key is pressed */
		exit(0);
	}

	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Programming Techniques - 3D Teapots");
	glClearColor(0, 0, 0, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);

	// Light sphere was added as a global variable atop of the code

	Sphere sphere(Point(3.0f, 0.0f, 1.0f), 1.0f,
		Color(0.5f, 0.5f, 1.0f));
	Sphere sphere2(Point(0.0f, 0.0f, 1.0f), 1.0f,
		Color(0.5f, 1.0f, 0.5f));
	Sphere sphere3(Point(3.0f, 3.0f, 1.0f), 1.0f,
		Color(1.0f, 0.5f, 0.5f));
	scene.addShape(&sphere);
	scene.addShape(&sphere2);
	scene.addShape(&sphere3);

	rayTrace(image, &camera, &scene);

	glutMainLoop();
}
