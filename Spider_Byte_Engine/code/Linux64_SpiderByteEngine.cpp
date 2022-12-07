#include <stdio.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader/Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define VS_FILE "../Spider_Byte_Engine/res/includes/Shader/basic.vs"
#define FS_FILE "../Spider_Byte_Engine/res/includes/Shader/basic.fs"
#define IMAGE_FILE "../Spider_Byte_Engine/res/includes/Textures/Space.png"
#define IMAGE_FILE2 "../Spider_Byte_Engine/res/includes/Textures/Tiger.jpg"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

int main(void)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //@NOTE(Emilio): If We decide to implement MAC OSX
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow* MainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
					    "Game Engine", 0, 0);
  if(!MainWindow)
    {
      printf("Failed to Create a Window\n");
      glfwTerminate();
      return -1;
    }
  glfwMakeContextCurrent(MainWindow);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      printf("Failed to init GLAD\n");
      glfwTerminate();
      return -1;
    }

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  
  //@NOTE(Emilio): This section will be used for OpenGL callbacks
  glfwSetFramebufferSizeCallback(MainWindow, framebuffer_size_callback);


float Verts[] =
  {
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
   
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
   
   -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
   
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
   
   -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
   
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
  };
  

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
			(void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
			(void*)(3*sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(1);

  unsigned int Texture[2];
  if(!ShaderCreateTexture(IMAGE_FILE, &Texture[0], 0))
    {
      glfwTerminate();
      return -1;
    }
  if(!ShaderCreateTexture(IMAGE_FILE2, &Texture[1], 0))
    {
      glfwTerminate();
      return -1;
    }
  
  unsigned int BasicShader = 0;
  CreateShader(VS_FILE, FS_FILE, &BasicShader);
  UseShader(BasicShader);
  ShaderSetInt(BasicShader, "Texture",0);
  ShaderSetInt(BasicShader, "Texture2",1);
  
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
  float TimeValue = 0;
  float GreenValue = 0.0f;
  float MixValue = 0.0f;
  glm::mat4 Base = glm::mat4(1.0f);
  glm::mat4 Persp = glm::perspective(glm::radians(45.0f),
				     (float)WINDOW_WIDTH /
				     (float)WINDOW_HEIGHT, 0.1f, 100.0f);

  glEnable(GL_DEPTH_TEST);
  while(!glfwWindowShouldClose(MainWindow))
    {
      processInput(MainWindow);

      TimeValue = glfwGetTime();
      GreenValue = (sin(TimeValue) / 2.0f) + 0.5f;
      MixValue = sin(TimeValue);

      glm::mat4 Model = glm::translate(Base, glm::vec3(-0.5f, 0.0f, -4.0f));
      Model = glm::rotate(Model, (float)glfwGetTime(),
      				    glm::vec3(3.0f, 2.0f, 4.0f));
      glm::mat4 View = glm::rotate(Base, (float)glfwGetTime(),
				   glm::vec3(0.5f, 1.0f, 1.0f));
      
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, Texture[0]);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, Texture[1]);

      ShaderSetFloat3(BasicShader, "ExtraColor", 0.0f, GreenValue, 0.0f);
      ShaderSetFloat(BasicShader, "MixVal", MixValue);
      ShaderSetMat4(BasicShader, "Model", Model);
      ShaderSetMat4(BasicShader, "View", View);
      ShaderSetMat4(BasicShader, "Persp", Persp);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      
      glfwSwapBuffers(MainWindow);
      glfwPollEvents();
    }

  glfwTerminate();

  return 0;
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
