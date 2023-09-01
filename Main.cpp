#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

//Coordonees des vertices (il triangulo)
GLfloat vertices[] = {
	/* Coordonees :				Couleurs : 	*/
	-0.5f,	-0.5f,		0.0f,	1.0f, 0.0f, 0.0f,	0.0f,	0.0f,
	-0.5f,	0.5f,		0.0f,	0.0f, 1.0f, 0.0f,	0.0f,	1.0f,
	0.5f,	0.5f,		0.0f,	0.0f, 0.0f, 1.0f,	1.0f,	1.0f,
	0.5f,	-0.5f,		0.0f,	1.0f, 1.0f,	1.0f,	1.0f,	0.0f
};

GLuint indices[] = {
	0, 2, 1, //Triangle bas gauche
	0, 3, 2, //triangle bas droit
};



int main() {

	glfwInit();

	/* Specifie version + profile OGL */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/*creation fenetre*/
	GLFWwindow* window = glfwCreateWindow(800, 800, "Open GL Engine", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;

	VAO1.Bind();
	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture vittor("Vittor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	vittor.texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0);
		vittor.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents(); //Gere les evenements de la fenetre
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	vittor.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}