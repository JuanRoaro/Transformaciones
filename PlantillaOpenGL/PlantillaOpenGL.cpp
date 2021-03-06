// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;
float angulo = 0.0f;

enum Direccion {Izquierda, Derecha, Arriba, Abajo};


Direccion direccionXTriangulo = Izquierda;
Direccion direccionYTriangulo = Arriba;

void dibujarTriangulo() {

	//Utilizar matriz identidad
	glPushMatrix();
	//Transformaciones
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
	glRotatef(angulo, 1.0f, 1.0f, 1.0f);

	//Dibujar vertices
	glBegin(GL_TRIANGLES);
		glColor3f(1, .8, 0);
		glVertex3f(-0.4f, -0.4f, 0);
		glVertex3f(0.4f, -0.4f, 0);
		glVertex3f(0.0f, 0.4f, 0);

		glEnd();

		//Soltar matriz
		glPopMatrix();
}


void dibujar() {
	dibujarTriangulo();
}

void actualizar() {

	if (angulo >= 360) {
		angulo = 0.0f;
	}
	angulo += 0.09f;

	if (direccionXTriangulo == Direccion::Izquierda)
	{
		if (posicionXTriangulo > -0.6f)
		{
			posicionXTriangulo -= 0.001f;
		}
		else
		{
			direccionXTriangulo = Direccion::Derecha;
		}
	}
	if (direccionYTriangulo == Direccion::Abajo)
	{
		if (posicionYTriangulo > -0.6f)
		{
			posicionYTriangulo -= 0.002f;
		}
		else
		{
			direccionYTriangulo = Direccion::Arriba;
		}

	}
	if (direccionXTriangulo == Direccion::Derecha)
	{
		if (posicionXTriangulo < 0.6f)
		{
			posicionXTriangulo += 0.001f;
		}
		else
		{
			direccionXTriangulo = Direccion::Izquierda;
		}

	}
	
	if (direccionYTriangulo == Direccion::Arriba)
	{
		if (posicionYTriangulo < 0.6f)
		{
			posicionYTriangulo += 0.001f;
		}
		else
		{
			direccionYTriangulo = Direccion::Abajo;
		}

	}
	
}

int main()
{
	GLFWwindow * window;

	//Si no se pudo iniciar glfw
	//entonces inicializamos en la ventana
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Si se pudo iniciar GLFW
	//entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana
	//Entonces terminamos la ejecucion

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas (gpu / cpu)
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;


	//Ciclo de dibujo (Draw Loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region del dibujo
		glViewport(0, 0, 1024, 768);
		//Establecer el color del borrado
		glClearColor(0.9, 0.2, 0.2, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		

		//Cambiar Buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

