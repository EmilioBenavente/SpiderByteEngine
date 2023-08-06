#include "SpiderUtil.h"
#include "../res/includes/glad/glad.h"
#include "glad.c"
#include "../res/includes/GLFW/glfw3.h"
#include "../res/includes/Shaders/Shader.h"
#include "../res/includes/Textures/Texture.h"
#include "../res/includes/glm/glm/glm.hpp"
#include "../res/includes/glm/glm/gtc/matrix_transform.hpp"
#include "../res/includes/glm/glm/gtc/type_ptr.hpp"
#include "../res/includes/Camera/Camera.h"
#include <cstdio>
#include <math.h>

#define VERTEX_FILE "../Engine/res/includes/Shaders/DefaultShader.vs"
#define FRAGMENT_FILE "../Engine/res/includes/Shaders/DefaultLightMap.fs"

#define LIGHT_VERTEX_FILE "../Engine/res/includes/Shaders/DefaultLightShader.vs"
#define LIGHT_FRAGMENT_FILE "../Engine/res/includes/Shaders/DefaultLightShader.fs"

#define DIFFUSE_MAP "../Engine/res/includes/Textures/container2.png"
#define SPECULAR_MAP "../Engine/res/includes/Textures/container2_specular_colored.png"

glm::vec3 LightPos = glm::vec3(0.0f, 100.0f, 0.0f);
glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);

void
framebuffer_size_callback(GLFWwindow* Window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int
InitializeOpenGL(GLFWwindow** GLWindow, Window* Window)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	*GLWindow = glfwCreateWindow(Window->Width, Window->Height, (const c8*)Window->WindowName, 0, 0);
	if(*GLWindow)
	{
		glfwMakeContextCurrent(*GLWindow);

		if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glViewport(0, 0, Window->Width, Window->Height);
			return 1;
		}
		else
		{
			printf("Failed to initialize GLAD\n");
		}
	}
	else
	{
		printf("Failed to create OpenGL Window\n");
	}

	glfwTerminate();
	return 0;
}


int
main()
{
	GLFWwindow* WindowContext = {};
	Window MainWindow = {};
	MainWindow.Width = 800;
	MainWindow.Height = 600;
	MainWindow.WindowName = (u8*)"OpenGL Window";

	if(InitializeOpenGL(&WindowContext, &MainWindow))
	{
		glfwSetFramebufferSizeCallback(WindowContext, framebuffer_size_callback);
		glfwSetInputMode(WindowContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(WindowContext, mouse_callback);
		glfwSetScrollCallback(WindowContext, scroll_callback);

		r32 Vertices[] = {
			// positions // normals // texture coords
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		glm::vec3 CubePositions[] = {
			glm::vec3( 0.0f, 0.0f, 0.0f),
			glm::vec3( 2.0f, 5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f, 3.0f, -7.5f),
			glm::vec3( 1.3f, -2.0f, -2.5f),
			glm::vec3( 1.5f, 2.0f, -2.5f),
			glm::vec3( 1.5f, 0.2f, -1.5f),
			glm::vec3(-1.3f, 1.0f, -1.5f)
		};


		u32 VBO = 0;
		u32 VAO = 0;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*) 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*) (3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*) (3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*) (6 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(3);

		u32 LightVBO = 0;
		u32 LightVAO = 0;
		glGenBuffers(1, &LightVBO);
		glGenVertexArrays(1, &LightVAO);

		glBindVertexArray(LightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, LightVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*) 0);
		glEnableVertexAttribArray(0);

		u32 ShaderID = 0;
		GenerateShader(&ShaderID, VERTEX_FILE, FRAGMENT_FILE);

		u32 LightShaderID = 0;
		GenerateShader(&LightShaderID, LIGHT_VERTEX_FILE, LIGHT_FRAGMENT_FILE);


		u32 DiffuseMap = 0;
		glActiveTexture(GL_TEXTURE0);
		GenerateTexture(&DiffuseMap, DIFFUSE_MAP, TextureColorFormat::RGBA);

		u32 SpecularMap = 0;
		glActiveTexture(GL_TEXTURE1);
		GenerateTexture(&SpecularMap, SPECULAR_MAP, TextureColorFormat::RGBA);

		glEnable(GL_DEPTH_TEST);

		glm::mat4 View = glm::mat4(1.0f);
		glm::mat4 Projection = glm::mat4(1.0f);

		glm::mat4 CubeMat = glm::mat4(1.0f);
		CubeMat = glm::translate(CubeMat, LightPos);
		CubeMat = glm::scale(CubeMat, glm::vec3(40.0f));

		glUseProgram(ShaderID);
		ShaderSetInt(&ShaderID, "Material.Ambient", 0);
		ShaderSetInt(&ShaderID, "Material.Diffuse", 0);
		ShaderSetInt(&ShaderID, "Material.Specular", 1);
		ShaderSetVec3(&ShaderID, "Light.Ambient", glm::vec3(0.2f));
		ShaderSetVec3(&ShaderID, "Light.Diffuse", glm::vec3(0.5f));
		ShaderSetVec3(&ShaderID, "Light.Specular", glm::vec3(1.0f));
		ShaderSetVec3(&ShaderID, "Light.Direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		ShaderSetFloat(&ShaderID, "Light.Constant", 1.0f);
		ShaderSetFloat(&ShaderID, "Light.Linear", 0.09f);
		ShaderSetFloat(&ShaderID, "Material.Shininess", 0.032f);


		while(!glfwWindowShouldClose(WindowContext))
		{
			ProcessInput(&WindowContext);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			r32 CurrentFrame = glfwGetTime();
			DeltaTime = CurrentFrame - LastFrame;
			LastFrame = CurrentFrame;
			r32 TimeValue = glfwGetTime();
			r32 GreenValue = (sin(TimeValue) / 2.0f) + 0.5f;


			glUseProgram(LightShaderID);
			glBindVertexArray(LightVAO);
			ShaderSetMat4(&LightShaderID, "Model", CubeMat);
			ShaderSetMat4(&LightShaderID, "View", View);
			ShaderSetMat4(&LightShaderID, "Projection", Projection);
			ShaderSetVec3(&LightShaderID, "LightColor", LightColor);
			glDrawArrays(GL_TRIANGLES, 0, 36);


			Projection = glm::perspective(glm::radians(FOV), 800.0f / 600.0f, 0.1f, 100.0f);
			View = glm::lookAt(CameraPos, CameraPos + CameraFront, WorldUp);

			glUseProgram(ShaderID);
			ShaderSetFloat4(&ShaderID, "UniformColor", 0.4f, GreenValue, 0.7f, 1.0f);
			ShaderSetMat4(&ShaderID, "View", View);
			ShaderSetMat4(&ShaderID, "Projection", Projection);
			ShaderSetVec3(&ShaderID, "LightColor", LightColor);
			ShaderSetVec3(&ShaderID, "ViewPos", CameraPos);

			ShaderSetVec3(&ShaderID, "Light.Position", CameraPos);
			ShaderSetVec3(&ShaderID, "Light.Direction", CameraFront);
			ShaderSetFloat(&ShaderID, "Light.InnerCutoff", glm::cos(glm::radians(12.5f)));
			ShaderSetFloat(&ShaderID, "Light.OuterCutoff", glm::cos(glm::radians(17.5f)));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, DiffuseMap);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, SpecularMap);

			glBindVertexArray(VAO);
			for(u8 Index = 0; Index < 10; Index++)
			{
				glm::mat4 Model = glm::mat4(1.0f);
				Model = glm::translate(Model, CubePositions[Index]);
				Model = glm::rotate(Model, (r32)glfwGetTime(), glm::vec3(2.12f, 3.25f, 1.0f));
				Model = glm::scale(Model, glm::vec3(0.5f, 0.5f, 0.5f));

				ShaderSetMat4(&ShaderID, "Model", Model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glfwSwapBuffers(WindowContext);
			glfwPollEvents();
		}

		glfwTerminate();
	}

	return 0;
}
