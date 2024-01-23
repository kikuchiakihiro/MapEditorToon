#include "LightPosController.h"

XMFLOAT4 LightPosController::GetLightPosition()
{
	return lightPosition_;
}

void LightPosController::SetLightPosition(XMFLOAT4 _lightPos)
{
	lightPosition_ = _lightPos;
}