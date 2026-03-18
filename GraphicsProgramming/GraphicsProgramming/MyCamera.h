#pragma once
#include "Vector3.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>


class MyCamera
{
	public:
		MyCamera(Vector3 position = { 0, 0, 0 }, Vector3 rotation = {0, 0, 0});

		void update();

		void moveForward(float speed);
		void moveRight(float speed);
		void moveUp(float speed);

		void turnRight(float speed);
		void turnUp(float speed);

		

	private:
		Vector3 Position = {0,0,0};
		Vector3 Rotation = {0,0,0};
		Vector3 Up;
		Vector3 Right;
		Vector3 Forward;
};

