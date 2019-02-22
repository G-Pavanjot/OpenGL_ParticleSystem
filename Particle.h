
/*
Name: Pavanjot Gill
*/

/*
Header file for Particle class
*/
class Particle{
public:
	Particle(); //constructor
	void updateParticle(); //Method to update the particle's position
	float* getPosition(); //Method to return the particle's current position
	float* getAngles(); //Method to return the particle's current rotation angles
	float* getColour(); //Method to return the particle's colour values
	bool overAge(); //Method to check if the age of the particle has reached a specified value
	void frictionModeToggle(); //Toggle method for friction mode
	void windModeToggle(); //Toggle method for wind mode
	void setWindX(float); //Method to set the wind in x direction
	void setWindZ(float); //Method to set the wind in z direction

/*
private variables used only in the Particle class
*/
private:
	bool frictionMode, windMode; //True if mode is on, else false
	int particleAge; //Age of the particle
	float particleSpeedX, particleSpeedY, particleSpeedZ; //Speed values for the particles
	float windX, windZ; //Wind values
	float particleRot[3]; //Array containing the current rotation angles
	float dirX, dirY, dirZ; //Movement directions for the particle
	float position[3]; //Array containing the current position of particle
	float colour[3]; //Array containing the colour values of the particle
};