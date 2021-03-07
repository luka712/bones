#include "AmbientLight.hpp"
#include "MaterialShader.hpp"
#include "APP_MACROS.h"

using Bones::Lights::AmbientLight;

AmbientLight::AmbientLight()
	: BaseLight(vec3(1,1,1), .6f){}

AmbientLight::AmbientLight(vec3 color, float intensity) 
	: BaseLight(color, intensity) {}

AmbientLight::AmbientLight(vec3 color) 
	: BaseLight(color) {}


void AmbientLight::UseLight(GLint colorLocation) const
{
	BaseLight::UseLight(colorLocation);
}

void AmbientLight::UseLight(const MaterialShader& shdr) const
{
	UseLight(shdr.m_ambientLightLocations.colorLocation);
}


#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;


EMSCRIPTEN_BINDINGS(AmbientLight_JS)
{

}

#endif