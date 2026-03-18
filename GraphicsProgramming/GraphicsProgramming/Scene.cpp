#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	

	// Initialise scene variables
	
}

void Scene::handleInput(float dt)
{
	// Camera movement
	if (input->isKeyDown('w')) myCamera.moveForward(dt * 10);
	else if (input->isKeyDown('s'))	myCamera.moveForward(-dt * 10);
	if (input->isKeyDown(32)) myCamera.moveUp(dt * 10);
	else if (GetAsyncKeyState(VK_CONTROL)) myCamera.moveUp(-dt * 10);									//This is needed cuz ctrl is a modifier key, thus it doesn't normally register alone normally. Shift is VK_SHIFT

	int mousePos[2] = { input->getMouseX(), input->getMouseY()};
	// Camera rotation
	if (input->isMouseRDown())
	{
		myCamera.turnUp(mousePreviousPos[1] - mousePos[1]);
		myCamera.turnRight(mousePos[0] - mousePreviousPos[0]);
	}
	mousePreviousPos[0] = mousePos[0];
	mousePreviousPos[1] = mousePos[1];
}

void Scene::update(float dt)
{
	// update scene related variables.

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	//gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	myCamera.update();
	
	// Render geometry/scene here -------------------------------------
	
	drawSeven();

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending function
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}


void Scene::drawSeven()
{
	glPushMatrix();	//Sun
		glColor3f(1, 1, 0);
		glRotatef(time / 30, 0, 0, 1);
		glTranslatef(7, 0, 0);

		glutWireSphere(3, 20, 10);

		glPushMatrix();	//Planet
			glColor3f(0, 0, 1);
			glRotatef(time / 20, 0, 0, 1);
			glTranslatef(20, 0, 0);

			glutWireSphere(1, 10, 7);

			glPushMatrix();	//Moon1
				glColor3f(0.4, 0.4, 0.4);
				glRotatef(time / 5, 0, 0, 1);
				glTranslatef(3, 0, 0);

				glutWireSphere(0.4, 7, 5);
			glPopMatrix();	//Moon1
			glPushMatrix();	//Moon2
				glColor3f(0.6, 0.6, 0.6);
				glRotatef(time / 8, 0, 1, 0);
				glTranslatef(4.5, 0, 0);
				
				glutWireSphere(0.3, 7, 5);
			glPopMatrix();	//Moon2
		glPopMatrix();	//Planet

		
		glPushMatrix();	//Planet2
			glColor3f(1, 0, 0);
			glRotatef(time / 6, 0, 0, 1);
			glTranslatef(10, 0, 0);

			glutWireSphere(0.9, 10, 7);

			glPushMatrix();	//Moon1
				glColor3f(0.4, 0.4, 0.4);
				glRotatef(time / 3, 0, 0.3, 1);
				glTranslatef(3, 0, 0);

				glutWireSphere(0.4, 7, 5);

				glPushMatrix();	//Moonception
					glColor3f(0.2, 0.2, 0.2);
					glRotatef(time / 5, 0, 0.3, 1);
					glTranslatef(3, 0, 0);

					glutWireSphere(0.2, 7, 5);

				glPopMatrix();	//Moonception
			glPopMatrix();	//Moon1
			glPushMatrix();	//Moon2
				glColor3f(0.6, 0.6, 0.6);
				glRotatef(time / 5, 0, 1, 0.6);
				glTranslatef(4.5, 0, 0);
				
				glutWireSphere(0.3, 7, 5);
			glPopMatrix();	//Moon2
		glPopMatrix();	//Planet2
	glPopMatrix();	//Sun



	//glPopMatrix();
	//
	//glPushMatrix();

	//	//glRotatef(triangleRotation, 0, 0, 1);
	//	glTranslatef(-1.5, 0, 0);
	//	glScalef(2, 2, 1);

	//	glBegin(GL_TRIANGLES);
	//		glVertex3f(0, 0.5, 0);
	//		glVertex3f(0.5, 0, 0);
	//		glVertex3f(-0.5, 0, 0);
	//	glEnd();

	//glPopMatrix();
}
