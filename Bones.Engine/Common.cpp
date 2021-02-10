#include "Constants.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;
using namespace glm;
using namespace std;

string GetExceptionMessage(intptr_t exceptionPtr)
{
	return string(reinterpret_cast<exception*>(exceptionPtr)->what());
}

EMSCRIPTEN_BINDINGS(GlobalFunctions_JS)
{
	emscripten::function("GetExceptionMessage", &GetExceptionMessage);
}

EMSCRIPTEN_BINDINGS(Common_JS)
{
	register_vector<unsigned int>("vector<uint>");
	register_vector<int>("vector<int>");
	register_vector<float>("vector<float>");
}

EMSCRIPTEN_BINDINGS(Vectors_JS)
{
	value_object<vec3>("Vec3")
		.field("x", &vec3::x)
		.field("y", &vec3::y)
		.field("z", &vec3::z);

	value_object<vec4>("Vec4")
		.field("x", &vec4::x)
		.field("y", &vec4::y)
		.field("z", &vec4::z)
		.field("w", &vec4::w);
}

#endif 