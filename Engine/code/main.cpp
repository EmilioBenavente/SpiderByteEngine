#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

const char* VertShaderSrc = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }\n\0";

const char* FragShaderSrc = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(0.8, 0.5, 0.2, 1.0);}\n\0";



void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
    GLFWwindow* Window = glfwCreateWindow(800, 600, 
                                          "Main Window",
                                          0, 0);
    if(!Window)
    {
        printf("Failed to Create GLFW Window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    
    glViewport(0, 0, 800, 600);
    
    /*
    float Vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f,
    };
    */
    float Vertices[] = 
    {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    unsigned int Indices[] = 
    {
        0, 1, 3, 
        1, 2, 3,
    };
    
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertShaderSrc, 0);
    glCompileShader(VertexShader);
    
    int Success;
    char InfoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
    if(!Success)
    {
        glGetShaderInfoLog(VertexShader, 512, 0, InfoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n",
               InfoLog);
    }
    
    
    unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragShaderSrc, 0);
    glCompileShader(FragmentShader);
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
    if(!Success)
    {
        glGetShaderInfoLog(FragmentShader, 512, 0, InfoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",
               InfoLog);
    }
    
    
    unsigned int ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if(!Success)
    {
        glGetProgramInfoLog(ShaderProgram, 512, 0, InfoLog);
    }
    
    glUseProgram(ShaderProgram);
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    
    
    //OPENGL Callback Functions
    glfwSetFramebufferSizeCallback(Window,
                                   framebuffer_size_callback);
    
    
    int i = 0;
    int isPoly = 0;
    while(!glfwWindowShouldClose(Window))
    {
        if(i == 100)
        {
            if(isPoly)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            isPoly = !isPoly;
            i = 0;
        }
        processInput(Window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glUseProgram(ShaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
        i++;
    }
    
    glfwTerminate();
    return 1;
}


void 
framebuffer_size_callback(GLFWwindow* Window, int Width,
                          int Height)
{
    glViewport(0, 0, Width, Height);
}

void 
processInput(GLFWwindow* Window)
{
    if(glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(Window, GL_TRUE);
    }
}