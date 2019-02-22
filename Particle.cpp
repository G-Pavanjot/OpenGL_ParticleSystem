
#include <stdlib.h>
#include "Particle.h"

/*
Name: Pavanjot Gill
*/

/*
Constructor for a single particle, contains default values
Such as: origin, friction on, wind off, random directions, speed, random colours, random rotating angles, and an age of 1
*/
Particle::Particle(){
	/*
	origin position is 60,60,-60
	*/
	position[0] = 60;
	position[1] = 60;
	position[2] = -60;

	frictionMode = true; //friction mode is on by defualt
	windMode = false; //wind mode is off by defualt
	windX = 0; //when wind mode is off, windX and windZ equal 0
	windZ = 0;

	dirX = 1+(rand() % 15); //random X direction movement between 1 and 15
	dirY = (rand() % 12); //random Y direction movement between 0 and 12
	dirZ = 1+(rand() % 15); //random Z direction movement between 1 and 15
	particleSpeedY = 0.0002; //particle speed in the Y direction (has to be different than speed of other directions because otherwise it is too fast)
	particleSpeedX = 0.02; //particle speed in the X direction
	particleSpeedZ = 0.02; //particle speed in the Z direction
	colour[0] = (rand() % 17) / 10; //create random red value for particle 
	colour[1] = (rand() % 17) / 10; //create random green value for particle
	colour[2] = (rand() % 17) / 10; //create random blue value for particle
	particleAge = 1; //age when created is 1

	particleRot[0] = (rand() % 360); //random angle for particle about x axis
	particleRot[1] = (rand() % 360); //random angle for particle about y axis
	particleRot[2] = (rand() % 360); //random angle for particle about z axis
}

/*
Updates the position of the particle
first increments the rotation angles by 1 (until 360) so the particles spin
then incrememnt the age by 1
Adjust movement directions (wind (0 when wind mode off) and gravity))
and finally adjust position (if within the range of the ground)
*/
void Particle::updateParticle(){

	/*
	Adjust partical rotation angles so the particle spins
	angle between 0 and 360 (if greater than 360, it should go back to 0)
	*/
	for (int z = 0; z < 3; z++){
		if (particleRot[z] >= 360){
			particleRot[z] = 0;
		}
		else{
			particleRot[z] += 1;
		}
	}
	particleAge += 1; //increment age by 1

	/*
	Only if the particle is still within the ground area should the wind adjust the x and z direction movements
	*/
	if ((position[0] <= 60) && (position[0] >= -60) && (position[2] <= 60) && (position[2] >= -60)){
	dirX = dirX - windX;
	dirZ = dirZ - windZ;
	}
	dirY = dirY - 9.8; //direction movement in y is changed due to gravity (-9.8)
	
	/*
	if the y position has reached the ground and is within the ground area, it should bounce back up (dirY * -1)
	*/
	if (position[1] <= 1.2)
	{
		if ((position[0] <= 60) && (position[0] >= -60) && (position[2] <= 60) && (position[2] >= -60)){
			if (frictionMode){
				//if friction mode is on and the particle reaches the ground, the speed should be decreased by 25%
					particleSpeedX *= 0.75;
					particleSpeedY *= 0.75;
					particleSpeedZ *= 0.75;
			}
			dirY *= -1; //bounce back up
		}
	}
	// this conditional is if due to friciton a particle gets stuck in the ground, it should be stationary on the ground rather than in the ground
	if ((position[1] <= 1.2) && (particleSpeedY <= 0.0001125) && (position[0] >= -60) && (position[2] <= 60)){
		position[1] = 1.2;
	}
	else{
		/*
		position of particle is updated
		P' = P + (d * S)
		*/
		position[1] = position[1] + (dirY * particleSpeedY);
	}
		position[0] = position[0] - (dirX * particleSpeedX);
		position[2] = position[2] + (dirZ * particleSpeedZ);
}

/*
Returns the current position of the particle
*/
float* Particle::getPosition(){
	return position;
}

/*
returns the colour values of the particle
*/
float* Particle::getColour(){
	return colour;
}

/*
Returns true if the particle has reached a specified age (3000) so it can be removed
*/
bool Particle::overAge(){
	if (particleAge == 3000){
		return true;
	}
	else{
		return false;
	}
}

/*
Returns the current angles for the particle
*/
float* Particle::getAngles(){
	return particleRot;
}

/*
Toggle method to turn friction mode on/off
*/
void Particle::frictionModeToggle(){
	if (frictionMode){
		frictionMode = false;
	}
	else{
		frictionMode = true;
	}
}

/*
Toggle method to turn wind mode on/off
*/
void Particle::windModeToggle(){
	if (windMode){
		windMode = false;
		windX = 0;
		windZ = 0;
	}
	else{
		windMode = true;	
	}
}

/*
Sets the windX variable depending on what the input is
*/
void Particle::setWindX(float windx){
	windX = windx;
}

/*
Sets the windZ variable depending on what the input is
*/
void Particle::setWindZ(float windz){
	windZ = windz;
}