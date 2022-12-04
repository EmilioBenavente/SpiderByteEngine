#include <stdio.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader/Shader.h>

#define VS_FILE "../Spider_Byte_Engine/res/includes/Shader/basic.vs"
#define FS_FILE "../Spider_Byte_Engine/res/includes/Shader/basic.fs"

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

  GLFWwindow* MainWindow = glfwCreateWindow(800, 600, "Game Engine", 0, 0);
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

  glViewport(0, 0, 800, 600);

  
  //@NOTE(Emilio): This section will be used for OpenGL callbacks
  glfwSetFramebufferSizeCallback(MainWindow, framebuffer_size_callback);
  

  float Verts[] =
    {
     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

  float Verts2[] =
    {
      0.7f,  0.5f, 0.0f,
      0.9f,  0.5f, 0.0f,
      0.8f,  0.9f, 0.0f,
    };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(1);
  

  unsigned int BasicShader = 0;
  CreateShader(VS_FILE, FS_FILE, &BasicShader);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
  float TimeValue = 0;
  float GreenValue = 0.0f;

  while(!glfwWindowShouldClose(MainWindow))
    {
      processInput(MainWindow);

      TimeValue = glfwGetTime();
      GreenValue = (sin(TimeValue) / 2.0f) + 0.5f;
      
      
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      UseShader(BasicShader);
      SetFloat3(BasicShader, "ExtraColor", 0.0f, GreenValue, 0.0f);
      SetFloat(BasicShader, "Offset", 0.2f);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      
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
