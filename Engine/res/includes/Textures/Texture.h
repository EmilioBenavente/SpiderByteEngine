#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../glad/glad.h"
#include "../GLFW/glfw3.h"

enum TextureColorFormat
{
	RGB,
	RGBA,
};

void
GenerateTexture(u32* ID, const c8* File, TextureColorFormat ColorFormat)
{
	glGenTextures(1, ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	s32 Width;
	s32 Height;
	s32 nrChannels;
	stbi_set_flip_vertically_on_load(true);
	u8* Data = stbi_load(File, &Width, &Height, &nrChannels, 0);
	if(Data)
	{
		if(ColorFormat == TextureColorFormat::RGB)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
		}
		else if(ColorFormat == TextureColorFormat::RGBA)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load Texture %s\n", File);
	}
	stbi_image_free(Data);
}

#endif
