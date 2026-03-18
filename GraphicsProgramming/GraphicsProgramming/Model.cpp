#define _CRT_SECURE_NO_WARNINGS
#include "Model.h"
#include <iostream>

Model::Model() 
{
}
Model::~Model()
{
}

void Model::Load(char* modelFileName, char* textureDef)
{
	LoadModel(modelFileName);
	LoadTexture(textureDef);
}

//I have not actually done this myself yet, it got auto suggested. I commented it out cuz I am not dealing with it just yet.
void Model::Render()
{

	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
		glScalef(10, 10, 10);
		glBegin(GL_TRIANGLES);
			for (int i = 0; i < faces.size()-9; i+=9) //faces.size()
			{

				glNormal3f(normals[faces[i + 2] - 1].x, normals[faces[i + 2] - 1].y, normals[faces[i + 2] - 1].z);
				glTexCoord2f(texcords[faces[i+1]-1].x, texcords[faces[i+1]-1].y);
				glVertex3f(vertices[faces[i]-1].x, vertices[faces[i]-1].y, vertices[faces[i]-1].z);

				glNormal3f(normals[faces[i + 5] - 1].x, normals[faces[i + 5] - 1].y, normals[faces[i + 5] - 1].z);
				glTexCoord2f(texcords[faces[i + 4] - 1].x, texcords[faces[i + 4] - 1].y);
				glVertex3f(vertices[faces[i+3]-1].x, vertices[faces[i+3]-1].y, vertices[faces[i+3]-1].z);

				glNormal3f(normals[faces[i + 8] - 1].x, normals[faces[i + 7] - 1].y, normals[faces[i + 7] - 1].z);
				glTexCoord2f(texcords[faces[i + 7] - 1].x, texcords[faces[i + 7] - 1].y);
				glVertex3f(vertices[faces[i+6]-1].x, vertices[faces[i+6]-1].y, vertices[faces[i+6]-1].z);

				
			}
		glEnd();
	glPopMatrix();

	//glBegin(GL_QUADS);
	//	glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
	//	glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
	//	glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
	//	glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
	//glEnd();
}

//should be good
bool Model::LoadModel(char* filename)
{
	std::vector<Vector3> verts;
	std::vector<Vector3> norms;
	std::vector<Vector3> texCs;
	//std::vector<unsigned int> faces;
	FILE* file = fopen(filename, "r");
	if (file == NULL)
		{
			return false;
		}
	while (true)
	{
		char lineHeader[128] = {0};
		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				texcords.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{

				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&face[0], &face[1], &face[2],
					&face[3], &face[4], &face[5],
					&face[6], &face[7], &face[8]);

				if (matches != 9)
				{

					// Parser error, or not triangle faces
					return false;

				}
				for (int i = 0; i < 9; i++)
				{

					faces.push_back(face[i]);

				}

			}
		}
	}
}

//should be good
void Model::LoadTexture(char* filename)
{
	texture = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
