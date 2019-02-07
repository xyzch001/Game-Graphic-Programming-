#pragma once
#include "SimpleShader.h"

class Material
{
public:
	Material(SimpleVertexShader* vtxShader, SimplePixelShader* pixShader);
	~Material();

	SimpleVertexShader* getVertexShader();
	SimplePixelShader*  getPixelShader();


private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

};

