#ifndef __ZYKLON_H__
#define __ZYKLON_H__

/*
 * USE ONLY FOR ZYKLON CLIENT APPLICATIONS
 */

#include "zyklon_exports.h"

#include "Application.h"
#include "Layer.h"
#include "Log.h"

//------------INPUT--------------
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseButtonCodes.h"
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

#include "Renderer/OrthographicCamera.h"
#include "Renderer/PerspectiveCamera.h"
//-------------------------------

//----------Entry Point----------
#include "EntryPoint.h"
//-------------------------------


#endif // __ZYKLON_H__