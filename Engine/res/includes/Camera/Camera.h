#ifndef CAMERA_H
#define CAMERA_H

#include "../GLFW/glfw3.h"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"


//@NOTE(Emilio): FLush this out in the future when Input becomes a dealbreaker or game gets serious.
glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
r32 DeltaTime = 0.0f;
r32 LastFrame = 0.0f;
r32 LastX = 400.0f;
r32 LastY = 300.0f;
r32 Yaw = -90.0f;
r32 Pitch = 0.0f;
r32 FOV = 45.0f;
u8 IsFirstMouseCallback = 1;


void
scroll_callback(GLFWwindow* Window, r64 XOffset, r64 YOffset)
{
	FOV -= (r32)YOffset;
	if(FOV < 1.0f)
	{
		FOV = 1.0f;
	}
	else if(FOV > 45.0f)
	{
		FOV = 45.0f;
	}
}

void
mouse_callback(GLFWwindow* Window, r64 XPos, r64 YPos)
{
	r32 XOffset = XPos - LastX;
	r32 YOffset = LastY - YPos;
	if(IsFirstMouseCallback)
	{
		LastX = XPos;
		LastY = YPos;
		IsFirstMouseCallback = 0;
	}
	LastX = XPos;
	LastY = YPos;
	r32 Sensitivity = 0.1f;
	XOffset *= Sensitivity;
	YOffset *= Sensitivity;
	Yaw += XOffset;
	Pitch += YOffset;
	if(Pitch > 89.0f)
	{
		Pitch = 89.0f;
	}
	else if(Pitch < -89.0f)
	{
		Pitch = -89.0f;
	}
	glm::vec3 Direction;
	Direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Direction.y = sin(glm::radians(Pitch));
	Direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraFront = glm::normalize(Direction);
}

void
ProcessInput(GLFWwindow** Window)
{
	const r32 CameraSpeed = 2.5f * DeltaTime;
	if(glfwGetKey((*Window), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose((*Window), true);
	}

	if(glfwGetKey((*Window), GLFW_KEY_W) == GLFW_PRESS)
	{
		CameraPos += CameraSpeed * CameraFront;
	}

	if(glfwGetKey((*Window), GLFW_KEY_S) == GLFW_PRESS)
	{
		CameraPos -= CameraSpeed * CameraFront;
	}

	if(glfwGetKey((*Window), GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraPos -= glm::normalize(glm::cross(CameraFront, WorldUp)) * CameraSpeed;
	}

	if(glfwGetKey((*Window), GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraPos += glm::normalize(glm::cross(CameraFront, WorldUp)) * CameraSpeed;
	}

	if(glfwGetKey((*Window), GLFW_KEY_E) == GLFW_PRESS)
	{
		CameraPos.y += CameraSpeed;
	}

	if(glfwGetKey((*Window), GLFW_KEY_Q) == GLFW_PRESS)
	{
		CameraPos.y -= CameraSpeed;
	}

}



#endif
