//@TODO(Emilio): Too lazy right now to clean up white space \
will do so next time.

#include <stdio.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader/Shader.h>
#include <Camera/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define VS_FILE "../Spider_Byte_Engine/res/includes/Shader/BasicLight.vs"
#define FS_FILE "../Spider_Byte_Engine/res/includes/Shader/BasicLight.fs"
#define VS_LIGHT_FILE "../Spider_Byte_Engine/res/includes/Shader/WhiteLight.vs"
#define FS_LIGHT_FILE "../Spider_Byte_Engine/res/includes/Shader/WhiteLight.fs"

#define IMAGE_FILE "../Spider_Byte_Engine/res/includes/Textures/Box.png"
#define IMAGE_FILE2 "../Spider_Byte_Engine/res/includes/Textures/BoxSpecular.png"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Camera Cam = {};
float DeltaSpeed = 0.0f;
float LastFrame = 0.0f;
float LastX = 400.0f;
float LastY = 300.0f;
int IsFirstMouse = 1;
glm::vec3 LightPos(1.2f, 1.0f, -7.0f);

void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
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
  glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(MainWindow, mouse_callback);
  glfwSetScrollCallback(MainWindow, scroll_callback);


  //@TODO(Emilio): Find OFF By One Error?
float Verts[] =
  {
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,  1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,
   
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,  1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
   
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f,  0.0f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f,  1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f,  0.0f,
   
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f,  0.0f,
   
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  1.0f,
   
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  1.0f, 0.0f
  };
   
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),
			(void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),
			(void*)(3 * sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(1);
			
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),
			(void*)(6 * sizeof(GL_FLOAT)));
  glEnableVertexAttribArray(2);
			
  unsigned int LightVAO;
  glGenVertexArrays(1, &LightVAO);
  glBindVertexArray(LightVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT),
			(void*)0);
  glEnableVertexAttribArray(0);
  
  unsigned int Texture[2];
  if(!ShaderCreateTexture(IMAGE_FILE, &Texture[0], 1))
    {
      glfwTerminate();
      return -1;
    }
  if(!ShaderCreateTexture(IMAGE_FILE2, &Texture[1], 1))
    {
      glfwTerminate();
      return -1;
    }
  
  unsigned int BasicShader = 0;
  CreateShader(VS_FILE, FS_FILE, &BasicShader);
  UseShader(BasicShader);
  ShaderSetFloat3(BasicShader, "Light.Ambient", 0.2f, 0.2f, 0.2f);
  ShaderSetFloat3(BasicShader, "Light.Diffuse", 0.8f, 0.8f, 0.8f);
  ShaderSetFloat3(BasicShader, "Light.Specular", 1.0f, 1.0f, 1.0f);
  ShaderSetFloat(BasicShader, "Material.Shininess", 64.0f);
  
  unsigned int LightShader = 0;
  CreateShader(VS_LIGHT_FILE, FS_LIGHT_FILE, &LightShader);
  UseShader(LightShader);
  
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
  Cam.CamPos = glm::vec3(0.0f, 0.0f, -3.0f);
  Cam.IsMovement = 1;
  Cam.Yaw = -90.0f;
  Cam.FOV = 45.0f;
  float TimeValue = 0;
  float GreenValue = 0.0f;
  float MixValue = 0.0f;
  glm::mat4 Base = glm::mat4(1.0f);
  glm::mat4 Persp = glm::perspective(glm::radians(Cam.FOV),
				     (float)WINDOW_WIDTH /
				     (float)WINDOW_HEIGHT, 0.1f, 100.0f);

  
  glEnable(GL_DEPTH_TEST);
  while(!glfwWindowShouldClose(MainWindow))
    {
      processInput(MainWindow);
      UpdateFPSCamera(&Cam);

      TimeValue = glfwGetTime();
      DeltaSpeed = TimeValue - LastFrame;
      LastFrame = TimeValue;
      
      GreenValue = (sin(TimeValue) / 2.0f) * 8.0f;
      LightPos.x = GreenValue;
      LightPos.z = -10.0f + (cos(TimeValue) / 2.0f) * 5.0f;
      MixValue = sin(TimeValue);

      glm::mat4 Model = glm::translate(Base, glm::vec3(0.0f, 0.0f, -10.0f));
      glClearColor(0.12f, 0.13f, 0.13f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      float LightX = (sin(TimeValue) / 2.0f) + 0.5f;
      float LightY = (cos(TimeValue) / 2.0f) + 0.2f;
      float LightZ = (cos(TimeValue) / 2.0f) + 0.4f;
      glm::vec3 LightColor = glm::vec3(LightX, LightY, LightZ);
      
      UseShader(BasicShader);
      ShaderSetInt(BasicShader, "Material.Diffuse", 0);
      ShaderSetInt(BasicShader, "Material.Specular", 1);
      ShaderSetMat4(BasicShader, "Model", Model);
      ShaderSetMat4(BasicShader, "View", Cam.ViewMatrix);
      ShaderSetMat4(BasicShader, "Persp", Persp);
      ShaderSetFloat3(BasicShader, "ViewPos", Cam.CamPos.x, Cam.CamPos.y, Cam.CamPos.z);
      ShaderSetFloat3(BasicShader, "Light.Position", LightPos.x, LightPos.y, LightPos.z);
      ShaderSetFloat3(BasicShader, "Light.Color", LightColor.x, LightColor.y, LightColor.z);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, Texture[0]);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, Texture[1]);

      
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      UseShader(LightShader);
      Model = glm::translate(Base, LightPos);
      Model = glm::scale(Model, glm::vec3(0.2f));
      
      ShaderSetMat4(LightShader, "Model", Model);
      ShaderSetMat4(LightShader, "View", Cam.ViewMatrix);
      ShaderSetMat4(LightShader, "Persp", Persp);
      ShaderSetFloat3(LightShader, "LightColor", LightColor.x, LightColor.y, LightColor.z);

      
      glBindVertexArray(LightVAO);
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

void mouse_callback(GLFWwindow* window, double XPos, double YPos)
{
  Cam.IsMovement = 1;
  if(IsFirstMouse)
    {
      LastX = XPos;
      LastY = YPos;
      IsFirstMouse = 0;
    }

  float XOffset = XPos - LastX;
  float YOffset = LastY - YPos;
  LastX = XPos;
  LastY = YPos;
  float Sensitivity = 0.1f;
  XOffset *= Sensitivity;
  YOffset *= Sensitivity;

  Cam.Yaw += XOffset;
  Cam.Pitch += YOffset;

  if(Cam.Pitch > 89.0f)
    {
      Cam.Pitch = 89.0f;
    }
  else if(Cam.Pitch < -89.0f)
    {
      Cam.Pitch = -89.0f;
    }

}

void scroll_callback(GLFWwindow* window, double XOffset, double YOffset)
{
  Cam.IsMovement = 1;
  Cam.FOV -= (float)YOffset;
  if(Cam.FOV < 1.0f)
    {
      Cam.FOV = 1.0f;
    }
  else if(Cam.FOV > 55.0f)
    {
      Cam.FOV = 55.0f;
    }  
}

void processInput(GLFWwindow* window)
{
  float CameraSpeed = 2.5f * DeltaSpeed;
  
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      Cam.IsMovement = 1;
      Cam.CamPos += CameraSpeed * Cam.CamFront;
    }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {      
      Cam.IsMovement = 1;
      Cam.CamPos -= CameraSpeed * Cam.CamFront;
    }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
      Cam.IsMovement = 1;
      Cam.CamPos += CameraSpeed * glm::cross(Cam.CamFront, Cam.CamUp);
    }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {      
      Cam.IsMovement = 1;
      Cam.CamPos -= CameraSpeed * glm::cross(Cam.CamFront, Cam.CamUp);
    }
  if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
      Cam.IsMovement = 1;
      Cam.CamPos.y += CameraSpeed;
    }
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {      
      Cam.IsMovement = 1;
      Cam.CamPos.y -= CameraSpeed;
    }
}
