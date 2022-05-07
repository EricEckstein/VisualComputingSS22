#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

unsigned int SCREEN_WIDTH = 1200;
unsigned int SCREEN_HEIGHT = 800;
unsigned int VAO = 0;
size_t numberOfVertsToDraw = 0;


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

GLFWwindow* initGL()
{
	GLFWwindow* window;

	if (!glfwInit())
		return nullptr;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Marching cubes with OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	return window;
}

void bufferGLGridData()
{
	//auto vertices = gridData.computeVertexDrawData(isoLevel);
	std::vector<float> vertices = {
		-0.5f,  1.5f, 1.0f, 0.0f, 0.0f, 0.5f, 
		2.5f, 0.0f, 1.0f, 0.0f, 0.5f, -15.5f,
		0.0f, 0.0f, 1.0f,-0.5f, -0.5f, 1.0f,
	};
	numberOfVertsToDraw = vertices.size() / 6;
	if (numberOfVertsToDraw == 0)
		return;

	unsigned int VBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main()
{
	auto window = initGL();
	if (!window)
		return -1;

	bufferGLGridData();

	glm::vec3 lightColor{ 0.1f, 1.0f, 1.0f };
	glm::vec3 objectColor{ 0.99609375f,0.80078125f,0.31640625f };

	Shader* s = new Shader("./Vertex.glsl", "./Fragment.glsl", "./Geometry.glsl");
	glEnable(GL_DEPTH_TEST);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	glUseProgram(s->ID);
	glUniformMatrix4fv(glGetUniformLocation(s->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


	// Rendering loop
	while (!glfwWindowShouldClose(window))
	{
		// Move visuals later
		processInput(window);

		//Rotate camera
		float camX = float(sin(1.5f * glfwGetTime()) * 60.0f);
		float camZ = float(cos(1.5f * glfwGetTime()) * 60.0f);
		glm::vec3 viewPos{ camX, 8.0f, camZ };
		glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		view = glm::lookAt(viewPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		float lightX = float(sin(5.0f * glfwGetTime()) * 25.0f);
		float lightZ = float(cos(5.0f * glfwGetTime()) * 25.0f);
		glm::vec3 lightPos{ lightX,0.0f,lightZ };

		//Render
		glClearColor(0.59765625f, 0.21484375f, 0.30078125f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Draw marching cubes
		glm::mat4 marchingCubesModelMat = glm::mat4(1.0f);

		glUseProgram(s->ID);
		glUniform3fv(glGetUniformLocation(s->ID, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform3fv(glGetUniformLocation(s->ID, "lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(glGetUniformLocation(s->ID, "objectColor"), 1, glm::value_ptr(objectColor));

		glUniformMatrix4fv(glGetUniformLocation(s->ID, "model"), 1, GL_FALSE, glm::value_ptr(marchingCubesModelMat));
		glUniformMatrix4fv(glGetUniformLocation(s->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(glGetUniformLocation(s->ID, "viewPos"), 1, glm::value_ptr(viewPos));
		if (numberOfVertsToDraw > 0)
		{
			glUseProgram(s->ID);
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glDrawArrays(GL_TRIANGLES, 0, GLsizei(numberOfVertsToDraw));
		}

		//Finalise main loop
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
	
}