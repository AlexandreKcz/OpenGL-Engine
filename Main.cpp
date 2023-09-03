#include"Mesh.h"

#include <wtypes.h> //pour DWORD pour le gpu nvidia
/* pour activer le gpu nvidia ? (les uv bug bruh)*/
extern "C"
{
	//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
};

const unsigned int width = 800;
const unsigned int height = 800;


Vertex vertices[] =
{
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
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

//Plane Old 
/*
GLfloat vertices[] = {
	-1.0f,	0.0f,	1.0f,		0.0f,	0.0f,	0.0f,		0.0f,	0.0f,		0.0f,	1.0f,	0.0f,
	-1.0f,	0.0f,	-1.0f,		0.0f,	0.0f,	0.0f,		0.0f,	1.0f,		0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	-1.0f,		0.0f,	0.0f,	0.0f,		1.0f,	1.0f,		0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	1.0f,		0.0f,	0.0f,	0.0f,		1.0f,	0.0f,		0.0f,	1.0f,	0.0f
};

GLuint indices[] = {
	0,1,2,
	0,2,3
};*/

//Coordonees des vertices (il piramido)
/*
GLfloat vertices[] = {*/
	/* Coordonees :				Couleurs : 					UV:					Normals : *//*
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
};*/

/*
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
};*/

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

	Texture textures[]
	{
		Texture("Vittor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Vittor_Specular.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Shader shaderProgram("default.vert", "default.frag");

	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh floor(verts, ind, tex);
	

	Shader lightShader("light.vert", "light.frag");

	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);

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

		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		glfwSwapBuffers(window);

		glfwPollEvents(); //Gere les evenements de la fenetre
	}

	shaderProgram.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}