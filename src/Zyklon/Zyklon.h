#ifndef __ZYKLON_H__
#define __ZYKLON_H__

/*
 * USE ONLY FOR ZYKLON CLIENT APPLICATIONS
 */

#include "zyklon_exports.h"

//------------CORE---------------
#include "Zyklon/Core/Application.h"
#include "Zyklon/Core/Layer.h"
#include "Zyklon/Core/Log.h"
#include "Zyklon/Core/Timestep.h"
//-------------------------------

//------------INPUT--------------
#include "Zyklon/Input/Input.h"
#include "Zyklon/Input/KeyCodes.h"
#include "Zyklon/Input/MouseButtonCodes.h"
//-------------------------------

//------------IMGUI--------------
#include "Imgui/ImguiLayer.h"
//-------------------------------


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
//-------------------------------

//----------Entry Point----------
#include "Zyklon/Core/EntryPoint.h"
//-------------------------------


#endif // __ZYKLON_H__