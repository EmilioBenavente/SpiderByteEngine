#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef struct Camera Camera;
struct Camera
{
  glm::mat4 ViewMatrix;
  
  glm::vec3 CamPos;
  glm::vec3 CamFront;
  glm::vec3 CamRight;
  glm::vec3 CamUp;
  glm::vec3 Target;
  
  float Yaw;
  float Pitch;
  float Roll;
  float FOV;
  
  unsigned int IsMovement;
};

unsigned int UpdateFPSCamera(Camera* Cam)
{
  if(Cam->IsMovement)
    {
      Cam->CamFront.x = cos(glm::radians(Cam->Yaw)) * cos(glm::radians(Cam->Pitch));
      Cam->CamFront.y = sin(glm::radians(Cam->Pitch));
      Cam->CamFront.z = sin(glm::radians(Cam->Yaw)) * cos(glm::radians(Cam->Pitch));
      Cam->CamFront = glm::normalize(Cam->CamFront);

      Cam->CamRight = glm::normalize(glm::cross(Cam->CamFront, glm::vec3(0.0f, 1.0f, 0.0f)));
      Cam->CamUp = glm::normalize(glm::cross(Cam->CamFront, Cam->CamRight));      
      Cam->ViewMatrix = glm::lookAt(Cam->CamPos, Cam->CamPos + Cam->CamFront, glm::vec3(0.0f, 1.0f, 0.0f));
      Cam->IsMovement = 0;
    }
  return 1;
};
