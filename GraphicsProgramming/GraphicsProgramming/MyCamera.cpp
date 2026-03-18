#include "MyCamera.h"

MyCamera::MyCamera(Vector3 position, Vector3 rotation)
{
	Position = position;
	Rotation = rotation;

	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;

	// Only want to calculate these values once, when rotation changes, not every frame.							TODO: MOVE TO ALL THE FUNCTIONS
	cosY = cosf(Rotation.y * 3.1415 / 180); // yaw
	cosP = cosf(Rotation.x * 3.1415 / 180); // pitch
	cosR = cosf(Rotation.z * 3.1415 / 180); // roll
	sinY = sinf(Rotation.y * 3.1415 / 180);
	sinP = sinf(Rotation.x * 3.1415 / 180);
	sinR = sinf(Rotation.z * 3.1415 / 180);

	//This using the parametric equation of a sphere

	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector															TODO: MOVE TO MOVE FORWARD

	Forward.x = sinY * cosP;
	Forward.y = sinP;
	Forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.

	// Up Vector																									TODO: MOVE TO TURN FUNCTIONS
	Up.x = -cosY * sinR - sinY * sinP * cosR;
	Up.y = cosP * cosR;// should default to 1, rest to 0
	Up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this, don’t do it. (I do)
}

void MyCamera::update()
{


	

	gluLookAt(Position.x, Position.y, Position.z, Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z, Up.x, Up.y, Up.z);
}

//complete
void MyCamera::moveForward(float speed)
{
	Vector3 nFo = Forward.normalised();
	Position.x += nFo.x * speed;
	Position.y += nFo.y * speed;
	Position.z += nFo.z * speed;
}

//incomplete
void MyCamera::moveRight(float speed)
{

}

// untested but complete
void MyCamera::moveUp(float speed)
{
	Vector3 nUp = Up.normalised();
	Position.x += nUp.x * speed;
	Position.y += nUp.y * speed;
	Position.z += nUp.z * speed;

}

//functional but fast with just +-dt as input
void MyCamera::turnUp(float speed)
{
	Rotation.x += speed;

	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;

	// Only want to calculate these values once, when rotation changes, not every frame.							TODO: MOVE TO ALL THE FUNCTIONS
	cosY = cosf(Rotation.y * 3.1415 / 180); // yaw
	cosP = cosf(Rotation.x * 3.1415 / 180); // pitch
	cosR = cosf(Rotation.z * 3.1415 / 180); // roll
	sinY = sinf(Rotation.y * 3.1415 / 180);
	sinP = sinf(Rotation.x * 3.1415 / 180);
	sinR = sinf(Rotation.z * 3.1415 / 180);

	//This using the parametric equation of a sphere

	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector															TODO: MOVE TO MOVE FORWARD

	Forward.x = sinY * cosP;
	Forward.y = sinP;
	Forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.

	// Up Vector																									TODO: MOVE TO TURN FUNCTIONS
	Up.x = -cosY * sinR - sinY * sinP * cosR;
	Up.y = cosP * cosR;// should default to 1, rest to 0
	Up.z = -sinY * sinR - sinP * cosR * -cosY;

}

//functional but fast with just +-dt as input
void MyCamera::turnRight(float speed)
{
	Rotation.y += speed;

	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;

	// Only want to calculate these values once, when rotation changes, not every frame.							TODO: MOVE TO ALL THE FUNCTIONS
	cosY = cosf(Rotation.y * 3.1415 / 180); // yaw
	cosP = cosf(Rotation.x * 3.1415 / 180); // pitch
	cosR = cosf(Rotation.z * 3.1415 / 180); // roll
	sinY = sinf(Rotation.y * 3.1415 / 180);
	sinP = sinf(Rotation.x * 3.1415 / 180);
	sinR = sinf(Rotation.z * 3.1415 / 180);

	//This using the parametric equation of a sphere

	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector															TODO: MOVE TO MOVE FORWARD

	Forward.x = sinY * cosP;
	Forward.y = sinP;
	Forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.

	// Up Vector																									TODO: MOVE TO TURN FUNCTIONS
	Up.x = -cosY * sinR - sinY * sinP * cosR;
	Up.y = cosP * cosR;// should default to 1, rest to 0
	Up.z = -sinY * sinR - sinP * cosR * -cosY;


}