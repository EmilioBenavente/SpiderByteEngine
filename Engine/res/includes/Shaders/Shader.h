#ifndef SHADER_H
#define SHADER_H

#include "../glad/glad.h"
#include "../GLFW/glfw3.h"
#include "../../../code/SpiderUtil.h"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"

enum ShaderStatus
{
	Vertex,
	Fragment,
	Program,
};

u8
CheckShaderStatus(ShaderStatus Status, u32 Shader)
{
	s32 Success = 0;
	c8 InfoLog[512] = {};

	switch(Status)
	{
		case ShaderStatus::Vertex:
		{
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
			if(!Success)
			{
				glGetShaderInfoLog(Shader, 512, 0, InfoLog);
				printf("Error, unable to compile VertexShader.\n%s\n", InfoLog);

				glfwTerminate();
				return 0;
			}
		}break;

		case ShaderStatus::Fragment:
		{
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
			if(!Success)
			{
				glGetShaderInfoLog(Shader, 512, 0, InfoLog);
				printf("Error, unable to compile FragmentShader.\n%s\n", InfoLog);

				glfwTerminate();
				return 0;
			}
		}break;

		case ShaderStatus::Program:
		{
			glGetProgramiv(Shader, GL_LINK_STATUS, &Success);
			if(!Success)
			{
				glGetProgramInfoLog(Shader, 512, 0, InfoLog);
				printf("Error, unable to link Shaders.\n%s\n", InfoLog);

				glfwTerminate();
				return 0;
			}
		}break;
	};
	return 1;
}


void
GenerateShader(u32* ID, const c8* VertFile, const c8* FragFile)
{

	c8 VertBuffer[1024] = {};
	u32 FileSize = 0;
	ReadEntireFile((u8*)VertBuffer, &FileSize, VertFile);

	if(FileSize)
	{
		u32 VertexShader = glCreateShader(GL_VERTEX_SHADER);
		c8* VertPtr = &VertBuffer[0];
		glShaderSource(VertexShader, 1, &VertPtr, 0);
		glCompileShader(VertexShader);
		if(CheckShaderStatus(ShaderStatus::Vertex, VertexShader))
		{
			c8 FragBuffer[1024] = {};
			FileSize = 0;
			ReadEntireFile((u8*)FragBuffer, &FileSize, FragFile);

			if(FileSize)
			{
				u32 FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				c8* FragPtr = &FragBuffer[0];
				glShaderSource(FragmentShader, 1, &FragPtr, 0);
				glCompileShader(FragmentShader);

				if(CheckShaderStatus(ShaderStatus::Fragment, FragmentShader))
				{
					*ID = glCreateProgram();
					glAttachShader(*ID, VertexShader);
					glAttachShader(*ID, FragmentShader);
					glLinkProgram(*ID);

					if(CheckShaderStatus(ShaderStatus::Program, *ID))
					{
						glUseProgram(*ID);
					}

					glDeleteShader(FragmentShader);
				}

				glDeleteShader(VertexShader);
			}
		}
	}
}


void
ShaderSetMat2(u32* ID, const c8* UniformName, glm::mat2 A)
{
	glUniformMatrix2fv(glGetUniformLocation(*ID, UniformName), 1, GL_FALSE, glm::value_ptr(A));
}

void
ShaderSetMat3(u32* ID, const c8* UniformName, glm::mat3 A)
{
	glUniformMatrix3fv(glGetUniformLocation(*ID, UniformName), 1, GL_FALSE, glm::value_ptr(A));
}

void
ShaderSetMat4(u32* ID, const c8* UniformName, glm::mat4 A)
{
	glUniformMatrix4fv(glGetUniformLocation(*ID, UniformName), 1, GL_FALSE, glm::value_ptr(A));
}


void
ShaderSetInt(u32* ID, const c8* UniformName, s32 A)
{
	glUniform1i(glGetUniformLocation(*ID, UniformName), A);
}

void
ShaderSetInt2(u32* ID, const c8* UniformName, s32 A, s32 B)
{
	glUniform2i(glGetUniformLocation(*ID, UniformName), A, B);
}

void
ShaderSetInt3(u32* ID, const c8* UniformName, s32 A, s32 B, s32 C)
{
	glUniform3i(glGetUniformLocation(*ID, UniformName), A, B, C);
}

void
ShaderSetInt4(u32* ID, const c8* UniformName, s32 A, s32 B, s32 C, s32 D)
{
	glUniform4i(glGetUniformLocation(*ID, UniformName), A, B, C, D);
}


void
ShaderSetFloat(u32* ID, const c8* UniformName, r32 A)
{
	glUniform1f(glGetUniformLocation(*ID, UniformName), A);
}

void
ShaderSetFloat2(u32* ID, const c8* UniformName, r32 A, r32 B)
{
	glUniform2f(glGetUniformLocation(*ID, UniformName), A, B);
}

void
ShaderSetFloat3(u32* ID, const c8* UniformName, r32 A, r32 B, r32 C)
{
	glUniform3f(glGetUniformLocation(*ID, UniformName), A, B, C);
}

void
ShaderSetFloat4(u32* ID, const c8* UniformName, r32 A, r32 B, r32 C, r32 D)
{
	glUniform4f(glGetUniformLocation(*ID, UniformName), A, B, C, D);
}


#endif
