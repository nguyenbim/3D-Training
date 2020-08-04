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

Object* test_object = new Object;
Shaders myShaders;

bool bMoveForward, bMoveBackward, bMoveLeft, bMoveRight;
bool bRotateUp, bRotateDown, bRotateLeft, bRotateRight;
int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	
	//buffer object
	test_object->LoadModel("../Resources/Models/Woman1.nfg");
	test_object->LoadTexture("../Resources/Textures/Woman1.tga");

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Matrix WVP = test_object->GetWVP();
	glUseProgram(myShaders.program);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *test_object->GetIBO());
	glBindBuffer(GL_ARRAY_BUFFER, *test_object->GetVBO());
	glBindTexture(GL_TEXTURE_2D, *test_object->GetTexture());
	if (myShaders.WVPLoc != -1) {
		glUniformMatrix4fv(myShaders.WVPLoc, 1, GL_FALSE,&WVP.m[0][0]);	
	}

	if (myShaders.positionAttribute != -1) {
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (myShaders.uvAttribute != -1) {
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(char*)0+sizeof(Vector3)*4);
	}
	

	
	glDrawElements(GL_TRIANGLES, test_object->GetModel()->GetNIndices(), GL_UNSIGNED_INT, 0);

	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);


	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update(ESContext *esContext, float deltaTime)
{
	if (bMoveForward) {
		bMoveForward = false;
		Camera::GetInstance()->MoveForward(deltaTime);
	}
	if (bMoveBackward) {
		bMoveBackward = false;
		Camera::GetInstance()->MoveBack(deltaTime);
	}
	if (bMoveLeft) {
		bMoveLeft = false;
		Camera::GetInstance()->MoveLeft(deltaTime);
	}
	if (bMoveRight) {
		bMoveRight = false;
		Camera::GetInstance()->MoveRight(deltaTime);
	}
	if (bRotateUp) {
		bRotateUp = false;
		Camera::GetInstance()->RotateUp(deltaTime);
	}
	if (bRotateDown) {
		bRotateDown = false;
		Camera::GetInstance()->RotateDown(deltaTime);
	}
	if (bRotateLeft) {
		bRotateLeft = false;
		Camera::GetInstance()->RotateLeft(deltaTime);
	}
	if (bRotateRight) {
		bRotateRight = false;
		Camera::GetInstance()->RotateRight(deltaTime);
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key == VK_UP && bIsPressed && !bMoveForward) {
		bMoveForward = true;
	}

	if (key == VK_DOWN && bIsPressed && !bMoveBackward) {
		bMoveBackward = true;
	}

	if (key == VK_LEFT && bIsPressed && !bMoveLeft) {
		bMoveLeft = true;
	}

	if (key == VK_RIGHT && bIsPressed && !bMoveRight) {
		bMoveRight = true;
	}

	if (key == 0x57 && bIsPressed && !bRotateUp) {
		bRotateUp = true;
	}

	if (key == 0x53 && bIsPressed && !bRotateDown) {
		bRotateDown = true;
	}

	if (key == 0x41 && bIsPressed && !bRotateLeft) {
		bRotateLeft = true;
	}

	if (key == 0x44 && bIsPressed && !bRotateRight) {
		bRotateRight = true;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, test_object->GetVBO());
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

