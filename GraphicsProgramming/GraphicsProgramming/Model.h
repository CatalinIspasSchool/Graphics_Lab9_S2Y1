#pragma once
#include "Vector3.h"

#include "glut.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include "Input.h"
//#include <stdio.h>
#include "SOIL.h"
#include <vector>
#include <cstdio>

class Model
{
	public:
		Model();
		~Model();


		void Load(char* modelFileName, char* textureDef);
		void Render();
		bool LoadModel(char* modelFileName); 
		void LoadTexture(char* textureFileName);

	private:
		std::vector<Vector3> vertices;
		std::vector<Vector3> texcords;
		std::vector<Vector3> normals;
		std::vector<unsigned int> faces;
		GLuint texture;
};