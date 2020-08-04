// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include"Object.h"
#include"Singleton.h"
#include"ResourceManagement.h"
#include"SceneManagement.h"

Shaders myShaders;


unsigned int uiKeysPressed;

int Init ( ESContext *esContext )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	
	ResourceManagement::GetInstance()->InitWithFile("../Resources/RM.txt");
	SceneManagement::GetInstance()->InitWithFile("../Resources/SM.txt");

	//graCamera = &SMInstance->m_Camera;

	// Creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw ( ESContext *esContext )
{
	SceneManagement::GetInstance()->Draw();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void ClearBit(unsigned int* uiKeysPressed, int iPosition) {
	*uiKeysPressed &= ~(1 << iPosition);
}

void SetBit(unsigned int* uiKeysPressed, int iPosition) {
	*uiKeysPressed |= 1 << iPosition;
}

bool GetBit(unsigned int* uiKeysPressed, int iPosition) {
	unsigned int bBit = *uiKeysPressed & (1 << iPosition);
	if (bBit == 0) {
		return false;
	}
	else {
		return true;
	}
}


void Update(ESContext *esContext, float deltaTime)
{
	if (GetBit(&uiKeysPressed, 0)) {
		ClearBit(&uiKeysPressed, 0);
		Camera::GetInstance()->MoveForward(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 1)) {
		ClearBit(&uiKeysPressed, 1);
		Camera::GetInstance()->MoveBack(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 2)) {
		ClearBit(&uiKeysPressed, 2);
		Camera::GetInstance()->MoveLeft(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 3)) {
		ClearBit(&uiKeysPressed, 3);
		Camera::GetInstance()->MoveRight(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 4)) {
		ClearBit(&uiKeysPressed, 4);
		Camera::GetInstance()->RotateUp(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 5)) {
		ClearBit(&uiKeysPressed, 5);
		Camera::GetInstance()->RotateDown(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 6)) {
		ClearBit(&uiKeysPressed, 6);
		Camera::GetInstance()->RotateLeft(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 7)) {
		ClearBit(&uiKeysPressed, 7);
		Camera::GetInstance()->RotateRight(deltaTime);
	}

	

	//SceneManagement::GetInstance()->Update(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	
	if (key == VK_UP && bIsPressed && !GetBit(&uiKeysPressed, 0)) {
		SetBit(&uiKeysPressed, 0);
	}

	
	if (key == VK_DOWN && bIsPressed && !GetBit(&uiKeysPressed, 1)) {
		SetBit(&uiKeysPressed, 1);
	}

	
	if (key == VK_LEFT && bIsPressed && !GetBit(&uiKeysPressed, 2)) {
		SetBit(&uiKeysPressed, 2);
	}

	
	if (key == VK_RIGHT && bIsPressed && !GetBit(&uiKeysPressed, 3)) {
		SetBit(&uiKeysPressed, 3);
	}

	
	if (key == 0x57 && bIsPressed && !GetBit(&uiKeysPressed, 4)) {
		SetBit(&uiKeysPressed, 4);
	}

	
	if (key == 0x53 && bIsPressed && !GetBit(&uiKeysPressed, 5)) {
		SetBit(&uiKeysPressed, 5);
	}

	
	if (key == 0x41 && bIsPressed && !GetBit(&uiKeysPressed, 6)) {
		SetBit(&uiKeysPressed, 6);
	}

	
	if (key == 0x44 && bIsPressed && !GetBit(&uiKeysPressed, 7)) {
		SetBit(&uiKeysPressed, 7);
	}
}

void CleanUp()
{
	//glDeleteBuffers(1, test_object->GetVBO());
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Training3D", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

