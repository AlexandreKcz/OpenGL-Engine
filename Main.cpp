#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"

//#include <wtypes.h> //pour DWORD pour le gpu nvidia
/* pour activer le gpu nvidia ? (les uv bug bruh)
extern "C"
{
	//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}*/

const unsigned int width = 800;
const unsigned int height = 800;

//Coordonees des vertices (il triangulo)
GLfloat vertices[] = {
	/* Coordonees :				Couleurs : 					UV:					Normals : */
	-0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f,		0.0f,	0.0f,		0.0f, -1.0f, 0.0f,
	-0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,		0.0f,	5.0f,		0.0f, -1.0f, 0.0f,
	0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,		5.0f,	5.0f,		0.0f, -1.0f, 0.0f,
	0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f,		5.0f,	0.0f,		0.0f, -1.0f, 0.0f,

	-0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f,		0.0f,	0.0f,		-0.8f, 0.5f, 0.0f,
	-0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,		5.0f,	0.0f,		-0.8f, 0.5f, 0.0f,
	0.0f,	0.8f,	0.0f,		0.92f, 0.86f, 0.76f,		2.5f,	5.0f,		-0.8f, 0.5f, 0.0f,

	-0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,		5.0f,	0.0f,		0.0f, 0.5f, -0.8f,
	0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,		0.0f,	0.0f,		0.0f, 0.5f, -0.8f,
	0.0f,	0.8f,	0.0f,		0.92f, 0.86f, 0.76f,		2.5f,	5.0f,		0.0f, 0.5f, -0.8f,

	0.5f,	0.0f,	-0.5f,		0.83f, 0.70f, 0.44f,		0.0f,	0.0f,		0.8f, 0.5f, 0.0f,
	0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f,		5.0f,	0.0f,		0.8f, 0.5f, 0.0f,
	0.0f,	0.8f,	0.0f,		0.92f, 0.86f, 0.76f,		2.5f,	5.0f,		0.8f, 0.5f, 0.0f,

	0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f,		5.0f,	0.0f,		0.0f, 0.5f, 0.8f,
	-0.5f,	0.0f,	0.5f,		0.83f, 0.70f, 0.44f,		0.0f,	0.0f,		0.0f, 0.5f, 0.8f,
	0.0f,	0.8f,	0.0f,		0.92f, 0.86f, 0.76f,		2.5f,	5.0f,		0.0f, 0.5f, 0.8f,
};

GLuint indices[] = {
	0,1,2,
	0,2,3,
	4,6,5,
	7,9,8,
	10,12,11,
	13,15,14
};

GLfloat lightVertices[] = {
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

/* QUAD
GLfloat vertices[] = {
	-0.5f,	-0.5f,	0.0f,		0.83f, 0.70f, 0.44f,	0.0f,	0.0f,
	-0.5f,	0.5f,	0.0f,		0.83f, 0.70f, 0.44f,	0.0f,	1.0f,
	0.5f,	0.5f,	0.0f,		0.83f, 0.70f, 0.44f,	1.0f,	1.0f,
	0.5f,	-0.5f,	0.0f,		0.83f, 0.70f, 0.44f,	1.0f,	0.0f,
};

GLuint indices[] = {
	0, 2, 1,
	0, 3, 2,
};*/


int main() {

	glfwInit();

	/* Specifie version + profile OGL */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	//glfwWindowHint(GLFW_EGL_DEVICE_EXT, 1);


	/*creation fenetre*/
	GLFWwindow* window = glfwCreateWindow(width, height, "Open GL Engine", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;

	VAO1.Bind();
	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture vittor("Vittor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	vittor.texUnit(shaderProgram, "tex0", 0);

	float prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	glfwSwapInterval(0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) {

		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		//Fixed Update
		if (timeDiff >= 1.0 / 120.0) {

			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string windowTitle = "OpenGL Engine : " + FPS + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, windowTitle.c_str());
			prevTime = crntTime;
			counter = 0;
			camera.Inputs(window);
		}

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		shaderProgram.Activate();

		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		camera.Matrix(shaderProgram, "camMatrix");

		vittor.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

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