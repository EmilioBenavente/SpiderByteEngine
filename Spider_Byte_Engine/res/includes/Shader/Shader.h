#if !defined(SHADER_H)
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

unsigned int ReadFile(const char*, char**);
unsigned int CharCountOfFile(const char*);
void DebugReadBuffer(char**);
void UseShader(unsigned int);
void SetBool(unsigned int, const char*, bool);
void SetInt(unsigned int ID, const char*, int);
void SetFloat(unsigned int ID, const char*, float);
void SetFloat3(unsigned int ID, const char* Name, float A, float B, float C);

unsigned int CreateShader(const char* VertPath, const char* FragPath, unsigned int* ID)
{
  char* Buffer;
  int Size = 0;

  Size = CharCountOfFile(VertPath);
  if(Size)
    {
      Buffer = (char*)malloc(sizeof(char) * Size + 1);
      if(ReadFile(VertPath, &Buffer))
	{
	  unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
	  int Success;
	  char InfoLog[512];
	  glShaderSource(VertexShader, 1, &Buffer, 0);
	  glCompileShader(VertexShader);
	  glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
	  if(!Success)
	    {
	      glGetShaderInfoLog(VertexShader, 512, 0, InfoLog);
	      printf("SPI_ERR: Could not compile the Vertex Shader\n%s\n", InfoLog);
	      return -1;
	    }
	  Size = CharCountOfFile(FragPath);
	  Buffer = (char*)realloc(Buffer, sizeof(char) * Size + 1);
	  if(ReadFile(FragPath, &Buffer))
	    {
	      unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	      glShaderSource(FragmentShader, 1, &Buffer, 0);
	      glCompileShader(FragmentShader);
	      glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
	      if(!Success)
		{
		  glGetShaderInfoLog(FragmentShader, 512, 0, InfoLog);
		  printf("\n\nSPI_ERR: Could not compile the Fragment Shader\n%s\n", InfoLog);
		  return -1;
		}
	      *ID = glCreateProgram();
	      glAttachShader(*ID, VertexShader);
	      glAttachShader(*ID, FragmentShader);
	      glLinkProgram(*ID);
	      glGetProgramiv(*ID, GL_LINK_STATUS, &Success);
	      glDeleteShader(VertexShader);
	      glDeleteShader(FragmentShader);
	      free((char*)Buffer);
	      if(!Success)
		{
		  glGetProgramInfoLog(*ID, 512, 0, InfoLog);
		  printf("SPI_ERR: Could not link the Shader Program ID: %d\n\%s\n", *ID, InfoLog);
		  return -1;
		}
	    }
	}
    }
  return 1;
}

void UseShader(unsigned int ID)
{
  glUseProgram(ID);
}

void SetBool(unsigned int ID, const char* Name, bool A)
{
  glUniform1i(glGetUniformLocation(ID, Name), (int)A);
}

void SetInt(unsigned int ID, const char* Name, int A)
{
  glUniform1i(glGetUniformLocation(ID, Name), A);
}

void SetFloat(unsigned int ID, const char* Name, float A)
{
  glUniform1f(glGetUniformLocation(ID, Name), A);  
}

void SetFloat3(unsigned int ID, const char* Name, float A, float B, float C)
{
  glUniform3f(glGetUniformLocation(ID, Name), A, B, C);
}

 
unsigned int ReadFile(const char* FilePath, char** Buffer)
{
  FILE* ptr = fopen(FilePath, "r");
  int count = 0;
  if(ptr)
    {
      char c;
      while((c = fgetc(ptr)) != EOF)
	{
	  *(*Buffer + count) = c;
	  count++;
	}
	fclose(ptr);
	*(*Buffer + count) = '\0';
    }
  else
    {
      printf("SPI_ERR: Could not read file %s\n", FilePath);
      return 0;
    }

  return 1;
}

unsigned int CharCountOfFile(const char* FilePath)
{
  unsigned int count = 0;
  FILE* ptr = fopen(FilePath, "r");

  if(ptr)
    {
      while(fgetc(ptr) != EOF)
	{
	  count++;
	}
	fclose(ptr);
    }
  else
    {
      printf("SPI_ERR: Could not read file %s\n", FilePath);
      return 0;
    }
  return count;
  
}

void DebugReadBuffer(char** Buffer)
{
  char* Ptr = *Buffer;
  while(*Ptr != '\0')
    {
      if(*Ptr == '\n')
	{
	  printf("\n");
	}
      else
	{
	  printf("%c", *Ptr);
	}
      Ptr++;
    }
}

#endif
