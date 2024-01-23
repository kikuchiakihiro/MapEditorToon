#pragma once
#include "Engine/Fbx.h"
namespace LightPosController
{
	static XMFLOAT4 lightPosition_;

	XMFLOAT4 GetLightPosition();
	void SetLightPosition(XMFLOAT4 _lightPos);
};

