#pragma once
#include "SimpleShader.h"

class Material
{
public:
	Material(SimpleVertexShader* vtxShader, SimplePixelShader* pixShader, ID3D11ShaderResourceView* Srv, ID3D11SamplerState* samplerstate);
	~Material();

	SimpleVertexShader* getVertexShader();
	SimplePixelShader*  getPixelShader();
	ID3D11ShaderResourceView* getSRV();
	ID3D11SamplerState* getSamplerState();

private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* samplerState;
};

