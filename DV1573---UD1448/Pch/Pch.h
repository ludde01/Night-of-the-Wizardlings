#ifndef _PCH_H
#define _PCH_H

#include "Bullet/btBulletDynamicsCommon.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <limits.h>
#include <time.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>
#include <chrono>
#include <thread>
#include <string>
#include <stdio.h>
#include <future>

//GL related includes
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

#include "System/Log.h"
//Raknet
#include <raknet/MessageIdentifiers.h>
#include <raknet/RakPeerInterface.h>
#include <raknet/RakNetTypes.h>
#include <raknet/RakSleep.h>
#include <raknet/GetTime.h>
#include <raknet/BitStream.h>

#include <Networking/NetworkGlobals.h>
#include <Networking/NetworkPackets.h>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>


//Custom
#include <Mesh/MeshFormat.h>
#include <Mesh/Mesh.h>
#include <Renderer/Shader.h>
#include <Renderer/ShaderMap.h>
#include <Renderer/Camera.h>
#include <Renderer/Renderer.h>
#include <System/Input.h>


const std::string SHADERPATH = "Assets/Shaders/";
const std::string TEXTUREPATH = "Assets/Textures/";
const std::string MESHPATH = "Assets/Meshes/";

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

#endif