#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Particle.h"	

#include <vector>
using std::vector;


/*
Name: Pavanjot Gill
*/


vector <Particle> particleList; //Vector containing all of the particles type:Particle
int spaceHit; //spaceHit indicates if the simulation is on start (0) or stop (1)
int frictionMode, windMode, twisterMode; //Mode variables which equal 1 if on, else they equal 0
float windX, windZ; //Variables containing the values of the wind in x or z direction
float sceneRotX; //Contains the rotation angle for the scene about the x axis
float sceneRotY; //Contains the rotation angle for the scene about the y axis
int twisterAngle; //Contains the angle that causes the particles to rotate like a twister (for twister mode)

/*
Display shows the ground and each particle
Also used for rotating scene and for twister mode
*/
void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(-7, 5, 5, 0, 0, 0, 0, 1, 0); //Set the camera position

	glColor3f(0, 0.25, 1); //the ground colour

	glPushMatrix();

	glRotatef(sceneRotY, 0, 1, 0);
	glRotatef(sceneRotX, 1, 0, 0);
	glScalef(6, 0.2, 6);
	glutSolidCube(1); //create the ground first so everything is made relative to it so the scene can rotate

	glPushMatrix();
	glRotatef(twisterAngle, 0, 1, 0); //Rotate everything except the ground for twister mode, until twister mode is turned on, twisterAnge = 0


	/*
	loop allows all the particles in the vector to be created
	*/
	for (int i = 0; i < particleList.size(); i++)
	{
		glColor3f(particleList[i].getColour()[0], particleList[i].getColour()[1], particleList[i].getColour()[2]);
		glPushMatrix();
		glScalef(0.05/6, 0.05/0.2, 0.05/6); //to create a cube that is even length on all sides
		glTranslatef(particleList[i].getPosition()[0], particleList[i].getPosition()[1], particleList[i].getPosition()[2]); //Translate the particle to its current position using getPosition()
		glRotatef(particleList[i].getAngles()[0], 1, 0, 0); //Rotate particle about its x axis
		glRotatef(particleList[i].getAngles()[1], 0, 1, 0); //Rotate particle about its y axis
		glRotatef(particleList[i].getAngles()[2], 0, 0, 1); //Rotate particle about its z axis
		glutSolidCube(1); //Create the particle as a cube
		glPopMatrix(); //Particle
	}

	
	glPopMatrix(); // twister mode
	
	glPopMatrix(); //Entire scene

	glutSwapBuffers();

}

/*
Keyboard method that does different things depending on which key is pressed
*/
void keyBoard(unsigned char keyPressed, int x, int y){

	switch (keyPressed)
	{

	case 'q':
		exit(0);
		break;

	case 32:
		if (spaceHit == 0){
			spaceHit = 1;
		}
		else{
			spaceHit = 0;
		}
		break;

	case 'r': //Reset the entire scene
		sceneRotX = 0;  //Scene goes back to original position
		sceneRotY = 0;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT && GL_DEPTH_BUFFER_BIT);
		particleList.clear(); //Empty the vector
		particleList.push_back(Particle()); //Create the first particle
		frictionMode = 1; //Friction mode on by default
		windMode = 0; //Wind mode off by default
		windX = 0; //When wind is off, windX = 0
		windZ = 0; //When wind is off, windZ = 0
		spaceHit = 0; //Simulation is on play by defualt
		twisterMode = 0; //Twister mode is off by default
		twisterAngle = 0; //Twister angle is reset back to zero
		glutPostRedisplay();
		break;

	case 'f': //toggles friction mode
		if (frictionMode == 1){
			frictionMode = 0;
		}
		else{
			frictionMode = 1;
		}
		for (int w = 0; w < particleList.size(); w++){
			particleList[w].frictionModeToggle(); //toggle friction mode on all particles
		}
		break;

	case 'w': //toggles wind mode
		if (windMode == 0){
			windMode = 1;
		}
		else{
			windMode = 0;
			windX = 0; //when wind mode turns off, windX and windZ go back to zero
			windZ = 0;
		}
		for (int j = 0; j < particleList.size(); j++){
			particleList[j].windModeToggle(); //toggle wind mode on all particles
		}
		break;

	case '[': //increase the wind in X direction
		if (windMode == 1){
			if (windX >= -0.1){ //can only go until 0.1 because if more, no particles hit the ground
				windX -= 0.02;
			}
		}
		break;

	case ']': //decrease the wind in X direction
		if (windMode == 1){
			if (windX <= 0.1){
				windX += 0.02;
			}
		}
		break;

	case '.': //increase the wind in Z direction
		if (windMode == 1){
			if (windZ >= -0.1){
				windZ -= 0.02;
			}
		}
		break;

	case ',': //decrease the wind in Z direction
		if (windMode == 1){
			if (windZ <= 0.1){
				windZ += 0.02;
			}
		}
		break;
		
	case 't': //toggles twister mode
		if (twisterMode == 0){
			twisterMode = 1;
		}
		else{
			twisterMode = 0;
		}
		break;
}

}

/*
keyboard method for special keys such as the arrow keys
*/
void specialKeys(int keyPressed, int x, int y)
{

	switch (keyPressed)
	{
		/*
		left and right arrow keys rotate scene about y axis
		up and down arrow keys rotate scene about x axis
		*/
	case GLUT_KEY_LEFT: 
		sceneRotY--;
		break;

	case GLUT_KEY_RIGHT:
		sceneRotY++;
		break;

	case GLUT_KEY_DOWN:
		sceneRotX--;
		break;

	case GLUT_KEY_UP:
		sceneRotX++;
		break;
	}
}

/*
initial values when program is started
*/
void init(void)
{
	sceneRotX = 0; //scene is at start position
	sceneRotY = 0;

	spaceHit = 0; //simulation is started

	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	particleList.push_back(Particle()); //creates the first particle

	frictionMode = 1; //friction mode on (default)

	twisterMode = 0; //twister mode off (default)
	twisterAngle = 0;

	windMode = 0; //wind mode off(default)
	windX = 0;
	windZ = 0;

	glEnable(GL_CULL_FACE); //enables culling
}


/*
timer is used to create new particles, update positions of each particle and remove particles that reach age limit
*/
void timer(int value)
{

	/*
	if twister mode is on, then the twister angle should be incremented to create the twister animation
	*/
	if (twisterMode == 1){
		twisterAngle += 1;
	}

	/*
	only create new particles if spaceHit = 0 (simulation is started)
	*/
	if (spaceHit == 0){
		particleList.push_back(Particle());
		if (frictionMode == 0){ //if friction mode is off, new particle's friction has to be toggled
			particleList[particleList.size() - 1].frictionModeToggle();
		}if (windMode == 1){ //if wind mode is on, new particle's wind has to be toggled
			particleList[particleList.size() - 1].windModeToggle();
		}
	}

	/*
	loop updates each particle in the vector particleList
	*/
	for (int x = 0; x < particleList.size(); x++){
		if (windMode == 1){ //if wind mode is on, the windX and windZ values have to be adjusted in the Particle class using setWindX and setWindZ methods
			particleList[x].setWindX(windX);
			particleList[x].setWindZ(windZ);
		}
		particleList[x].updateParticle(); //each particle's position is updated using updateParticle() method
		if (particleList[x].overAge()){ //if the particle has reached the age limit, it needs to be removed from the vector
			particleList.erase(particleList.begin() + x);
		}
	}
	glutTimerFunc(8, timer, 0);
	glutPostRedisplay();

}

/*
Main Method
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	/*
	print what each key does
	*/
	printf("r: reset\n");
	printf("f: friction toggle (default on)\n");
	printf("w: wind mode toggle(default off)\n");
	printf("]: increase x-direction wind speed\n");
	printf("[: decrease x-direction wind speed (negative wind direction means -x direction)\n");
	printf(".: increase z-direction wind speed\n");
	printf(",: decrease z-direction wind speed (negative wind direction means -z direction)\n");
	printf("t: twister mode toggle (default off)\n");
	printf("space bar: Start/Stop Animation\n");
	printf("direction keys rotate scene\n");
	printf("q: exit program");

	glutCreateWindow("Particle System"); //create the window called Particle System

	glutDisplayFunc(display);
	glutKeyboardFunc(keyBoard);
	glutSpecialFunc(specialKeys);
	glutTimerFunc(8, timer, 0);

	glEnable(GL_DEPTH_TEST);
	init();

	glutFullScreen();
	glutMainLoop();			

	return(0);					
}