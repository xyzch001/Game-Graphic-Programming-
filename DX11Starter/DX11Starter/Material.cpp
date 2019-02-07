#include "Material.h"



Material::Material(SimpleVertexShader* vtxShader, SimplePixelShader* pixShader)
{
	vertexShader = vtxShader;
	pixelShader = pixShader;
}


Material::~Material()
{
}

SimpleVertexShader * Material::getVertexShader()
{
	return vertexShader;
}

SimplePixelShader * Material::getPixelShader()
{
	return pixelShader;
}
