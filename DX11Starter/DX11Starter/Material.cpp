#include "Material.h"



Material::Material(SimpleVertexShader* vtxShader, SimplePixelShader* pixShader, ID3D11ShaderResourceView* Srv, ID3D11SamplerState* samplerstate)
{
	vertexShader = vtxShader;
	pixelShader = pixShader;
	srv = Srv;
	samplerState = samplerstate;
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

ID3D11ShaderResourceView * Material::getSRV()
{
	return srv;
}

ID3D11SamplerState * Material::getSamplerState()
{
	return samplerState;
}
