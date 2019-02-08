#pragma once

#include "SimpleShader.h"
#include "Vertex.h"
#include <d3d11.h>
#include <fstream>;

class Mesh
{
public:
	Mesh(Vertex* vertices, int numVertices,  int* indices, int numIndices, ID3D11Device* device);
	Mesh(char* fileName);
	~Mesh();



	//returns the pointer to the vertex buffer object
	ID3D11Buffer* GetVertexBuffer();

	//return the pointer to the index buffer object
	ID3D11Buffer* GetIndexBuffer();

	//return the number of indices this mesh contains
	int GetIndexCount();

private:
	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	//Specifying how many indices are in the mesh's index buffer
	int numIndices;



};

