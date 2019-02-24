#include "Game.h"
#include "Vertex.h"
#include "WICTextureLoader.h"

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		// The application's handle
		"DirectX Game",	   	// Text for the window's title bar
		1280,			// Width of the window's client area
		720,			// Height of the window's client area
		true)			// Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.\n");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	//// Release any (and all!) DirectX objects
	//// we've made in the Game class
	//if (vertexBuffer) { vertexBuffer->Release(); }
	//if (indexBuffer) { indexBuffer->Release(); }
	if (srv) { srv->Release(); }
	if (srv1) { srv1->Release(); }
	if (sampleState) { sampleState->Release(); }
	if (sampleState1) { sampleState->Release(); }
	
	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;

	//delete Mesh objects and clean up the DirectX objects
	delete sphere;
	delete torus;
	delete helix;
	delete cube;
	delete cone;
	delete cylinder;
	
	//Delete GameEntity objects 
	delete entity1;
	delete entity2;
	delete entity3;
	delete entity4;
	delete entity5;
	delete entity6;

	//Delete Camera
	delete cameraObj;

	//Delete Material
	delete material;
	delete metal;
	
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	CreateWICTextureFromFile(device, context, L"..\\..\\Textures\\TexturesCom_BarkDecidious0194_1_seamless_S.jpg", 0, &srv1);
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	
	

	device->CreateSamplerState(&sampleDesc, &sampleState);


	CreateWICTextureFromFile(device, context, L"..\\..\\Textures\\TexturesCom_MetalBare0146_4_M.jpg", 0, &srv);
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;



	device->CreateSamplerState(&sampleDesc, &sampleState1);

	//---------------------------------------------------


	light1.AmbientColor = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	light1.DiffuseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	light1.Direction = XMFLOAT3(1.0f, -1.0f, 0.0f);

	light2.AmbientColor = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	light2.DiffuseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	light2.Direction = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	
	light3.position = XMFLOAT3(0.0f, 5.0f, 0.0f);
	light3.color = XMFLOAT3(1.0f, 1.0f, 1.0f);

	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");

	

	material = new Material(vertexShader, pixelShader, srv, sampleState);
	metal = new Material(vertexShader, pixelShader, srv1, sampleState1);
	pixelShader->SetData(
		"light1",                    // The name of the (eventual) variable in the shader
		&light1,                     // The address of the data to copy
		sizeof(DirectionalLight));   // The size of the data to copy

	pixelShader->SetData(
		"light2",                    // The name of the (eventual) variable in the shader
		&light2,                     // The address of the data to copy
		sizeof(DirectionalLight));   // The size of the data to copy

	pixelShader->SetData(
		"light3",
		&light3,
		sizeof(PointLight));
}



// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	//// Set up world matrix
	//// - In an actual game, each object will need one of these and they should
	////    update when/if the object moves (every frame)
	//// - You'll notice a "transpose" happening below, which is redundant for
	////    an identity matrix.  This is just to show that HLSL expects a different
	////    matrix (column major vs row major) than the DirectX Math library
	//XMMATRIX W = XMMatrixIdentity();
	//XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!

	//// Create the View matrix
	//// - In an actual game, recreate this matrix every time the camera 
	////    moves (potentially every frame)
	//// - We're using the LOOK TO function, which takes the position of the
	////    camera and the direction vector along which to look (as well as "up")
	//// - Another option is the LOOK AT function, to look towards a specific
	////    point in 3D space
	//XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	//XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	//XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	//XMMATRIX V = XMMatrixLookToLH(
	//	pos,     // The position of the "camera"
	//	dir,     // Direction the camera is looking
	//	up);     // "Up" direction in 3D space (prevents roll)
	//XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	//// Create the Projection matrix
	//// - This should match the window's aspect ratio, and also update anytime
	////    the window resizes (which is already happening in OnResize() below)
	//XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,		// Field of View Angle
	//	(float)width / height,		// Aspect ratio
	//	0.1f,						// Near clip plane distance
	//	100.0f);					// Far clip plane distance
	//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!

	cameraObj = new Camera(float(width), float(height));


}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	//// Create some temporary variables to represent colors
	//// - Not necessary, just makes things more readable
	//XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	//XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	//XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	XMFLOAT3 normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	XMFLOAT2 uv = XMFLOAT2(0.0f, 0.0f);


	// Set up the vertices of the triangle we would like to draw
	// - We're going to copy this array, exactly as it exists in memory
	//    over to a DirectX-controlled data structure (the vertex buffer)
	Vertex vertices1[] =
	{
		{ XMFLOAT3(+0.0f, +0.6f, +0.0f), normal, uv },
		{ XMFLOAT3(+0.5f, +0.1f, +0.0f), normal, uv },
		{ XMFLOAT3(-0.5f, +0.1f, +0.0f), normal, uv },
		{ XMFLOAT3(+0.0f, +0.1f, +0.5f), normal, uv },
		{ XMFLOAT3(+0.0f, +0.1f, -0.5f), normal, uv },
	};

	Vertex vertices2[] =
	{
		{ XMFLOAT3(+0.0f, -0.6f, +0.0f), normal, uv },
		{ XMFLOAT3(+0.5f, -0.1f, +0.0f), normal, uv },
		{ XMFLOAT3(-0.5f, -0.1f, +0.0f), normal, uv },
	    { XMFLOAT3(+0.0f, -0.1f, +0.5f), normal, uv },
		{ XMFLOAT3(+0.0f, -0.1f, -0.5f), normal, uv },
	};

	Vertex vertices3[] =
	{
		{ XMFLOAT3(-0.25f, +0.25f, -0.25f), normal, uv },
		{ XMFLOAT3(-0.25f, -0.25f, -0.25f), normal, uv },
		{ XMFLOAT3(+0.25f, +0.25f, -0.25f), normal, uv },
		{ XMFLOAT3(+0.25f, -0.25f, -0.25f), normal, uv },
		{ XMFLOAT3(+0.25f, +0.25f, +0.25f), normal, uv },
		{ XMFLOAT3(+0.25f, -0.25f, +0.25f), normal, uv },
		{ XMFLOAT3(-0.25f, +0.25f, +0.25f), normal, uv },
		{ XMFLOAT3(-0.25f, -0.25f, +0.25f), normal, uv },
	};


	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	// - But just to see how it's done...
	unsigned int indices1[] = { 0, 1, 4, 0, 4, 2, 0, 3, 1, 0, 2, 3, 1, 2, 4, 2, 1, 3 };
	unsigned int indices2[] = { 0, 2, 4, 0, 4, 1, 2, 1, 4, 2, 3, 1, 0, 3, 2, 0, 1, 3 };
	unsigned int indices3[] = { 0, 2, 1, 1, 2, 3, 2, 5, 3, 2, 4, 5, 4, 7, 5, 4, 6, 7, 0, 1, 7, 0, 7, 6, 0, 6, 2, 2, 6, 4, 1, 3, 7, 3, 5, 7};

	// Create Mesh object and pass the array of vertices and indices.
	/*geometry1 = new Mesh(vertices1, 5, indices1, 18, device);
	geometry2 = new Mesh(vertices2, 5, indices2, 18, device);
	geometry3 = new Mesh(vertices3, 8, indices3, 36, device);*/
	sphere = new Mesh("..\\..\\OBJ_Files\\sphere.obj", device);
	torus = new Mesh("..\\..\\OBJ_Files\\torus.obj", device);
	helix = new Mesh("..\\..\\OBJ_Files\\helix.obj", device);
	cube = new Mesh("..\\..\\OBJ_Files\\cube.obj", device);
	cone = new Mesh("..\\..\\OBJ_Files\\cone.obj", device);
	cylinder = new Mesh("..\\..\\OBJ_Files\\cylinder.obj", device);
	
	//Create GameEntity objects and accept pointer of Mesh
	entity1 = new GameEntity(sphere, material);
	entity2 = new GameEntity(torus, material);
	entity3 = new GameEntity(helix, material);
	entity4 = new GameEntity(cube, metal);
	entity5 = new GameEntity(cone, metal);
	entity6 = new GameEntity(cylinder, metal);
}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	cameraObj->setProjection(float(width), float(height), 0.25f * 3.1415926535f);

	//// Update our projection matrix since the window size changed
	//XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,	// Field of View Angle
	//	(float)width / height,	// Aspect ratio
	//	0.1f,				  	// Near clip plane distance
	//	100.0f);			  	// Far clip plane distance
	//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	float sinTime = sin(totalTime * 0.5f)*2;
	float cosTime = cos(totalTime * 0.5f)*2;

	//Set entity1 worldTransformation
	entity1->SetTranslation(sinTime, sinTime, sinTime);
	entity1->SetRotation(totalTime, totalTime, totalTime);
	//entity1->SetScale(sinTime, sinTime, sinTime);
	entity1->SetWorldMatrix();
	
	//Set entity2 worldTransformation
	entity2->SetTranslation(-sinTime, -sinTime, -sinTime);
	entity2->SetRotation(totalTime, totalTime, totalTime);
	//entity2->SetScale(sinTime, sinTime, sinTime);
	entity2->SetWorldMatrix();

	//Set entity3 worldTransformation
	entity3->SetTranslation(cosTime, cosTime, cosTime);
	entity3->SetRotation(totalTime, totalTime, totalTime);
	//entity3->SetScale(sinTime, sinTime, sinTime);
	entity3->SetWorldMatrix();

	//Set entity4 worldTransformation
	entity4->SetTranslation(-cosTime, -cosTime, -cosTime);
	entity4->SetRotation(totalTime, totalTime, totalTime);
	//entity4->SetScale(sinTime, sinTime, sinTime);
	entity4->SetWorldMatrix();

	//Set entity5 worldTransformation
	entity5->SetTranslation(sinTime, cosTime, sinTime);
	entity5->SetRotation(totalTime, totalTime, totalTime);
	//entity5->SetScale(sinTime, sinTime, sinTime);
	entity5->SetWorldMatrix();

	//Set entity6 worldTransformation
	entity6->SetTranslation(-sinTime, -cosTime, -sinTime);
	entity6->SetRotation(totalTime, totalTime, totalTime);
	//entity6->SetScale(sinTime, sinTime, sinTime);
	entity6->SetWorldMatrix();

	//Update Camera
	cameraObj->Update(deltaTime);

	

}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	//const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };
	const float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	//Shader for the game entities
	Shader(entity1);
	Shader(entity2);
	Shader(entity3);
	Shader(entity4);
	Shader(entity5);
	Shader(entity6);

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}

void Game::Shader(GameEntity* entity) 
{
	//prepareMaterial
	//Send data to shader variables
	//CopyAllBufferData 
	//Set the bertex and pixel shader to use for next Draw()
	entity->prepareMaterial(cameraObj->getView(), cameraObj->getProjection(), cameraObj->getPosition());

	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	vertexBuffer = entity->GetVertexBuffer();
	indexBuffer = entity->GetIndexBuffer();
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Finally do the actual drawing
	//  - Do this ONCE PER OBJECT you intend to draw
	//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
	//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
	//     vertices in the currently set VERTEX BUFFER
	context->DrawIndexed(
		entity->GetIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...


	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	float deltaX = float(x - prevMousePos.x);
	float deltaY = float(y - prevMousePos.y);
	if (buttonState & 0x0001) {
		cameraObj->setRotationX(deltaX);
		cameraObj->setRotationY(deltaY);
	}
	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion