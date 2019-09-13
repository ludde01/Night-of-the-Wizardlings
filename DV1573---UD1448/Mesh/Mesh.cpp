#include "Pch/Pch.h"
#include "Mesh.h"

Mesh::Mesh()
{
	name = "";

	m_worldPos = glm::vec3();
	m_worldRot = glm::quat();
	m_worldScale = glm::vec3();

	vertexCount = 0;
	faceCount = 0;
}

Mesh::~Mesh()
{
}

void Mesh::setUpMesh(float* inVertices, int inVertexCount, int* inIndices, int inFaceCount)
{
	int j = 0;
	vertexCount = inVertexCount;
	faceCount = inFaceCount;

	vertices.resize(vertexCount);
	faces.resize(inFaceCount);


	// Fill verts
	float* tempVert = inVertices;
	for (int i = 0; i < vertexCount; i++)
	{

		vertices[i].position[0] = tempVert[j]; j++;
		vertices[i].position[1] = tempVert[j]; j++;
		vertices[i].position[2] = tempVert[j]; j++;
			
		vertices[i].UV[0] = tempVert[j]; j++;
		vertices[i].UV[1] = tempVert[j]; j++;

		vertices[i].Normals[0] = tempVert[j]; j++;
		vertices[i].Normals[1] = tempVert[j]; j++;
		vertices[i].Normals[2] = tempVert[j]; j++;
	}

	// Fill faces
	int* tempFace = inIndices;
	j = 0;
	int k = 0;
	for (int i = 0; i < inFaceCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			faces[i].indices[j] = tempFace[k];
			k++;
		}
	}

}
