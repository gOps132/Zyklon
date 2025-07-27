#ifndef __ZYKLON_H__
#define __ZYKLON_H__

/*
 * USE ONLY FOR ZYKLON CLIENT APPLICATIONS
 */

#include "zyklon_exports.h"

//------------CORE---------------
#include "Core/Application.h"
#include "Core/Layer.h"
#include "Core/Log.h"
#include "Core/Timestep.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"
#include "Core/UUID.h"

//------------INPUT--------------
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseButtonCodes.h"

//------------IMGUI--------------
#include "Imgui/ImguiLayer.h"

//-----------RENDERER------------
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Camera/Camera.h"
#include "Renderer/Camera/OrthographicCamera.h"
#include "Renderer/Camera/PerspectiveCamera.h"
#include "Renderer/Camera/OrbitControls.h"

#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Material/BasicLitMaterial.h"

//----------Entry Point----------
#include "Zyklon/Core/EntryPoint.h"
//-------------------------------

#endif // __ZYKLON_H__