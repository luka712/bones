#include "OpenGL_4_6_Renderer.hpp"

void OpenGL_4_6_Renderer::PointLightPass( Scene& scene, PointLight& light)
{
	// TODO : optimize lights to have same shader instance.
	/*OmniDirectionalLightShadowMap& shadowMap = *light.GetShadowMap();
	OmniDirectionalShadowShader& shader = shadowMap.GetShader();*/

	// optimize, no need to use if those are same 
	//if (m_currentShader != &shader)
	//{
	//	// start program
	//	shader.UseProgram();
	//	m_currentShader = &shader;
	//}

	//// set viewport
	//glViewport(0, 0, shadowMap.GetShadowWidth(), shadowMap.GetShadowHeight());

	//// use framebuffer and clear it
	//shadowMap.BindFramebuffer();
	//glClear(GL_DEPTH_BUFFER_BIT);
	//
	//shader.UseFarPlane(light.GetFarPlane());
	//shader.UseLightPosition(light.GetPosition());
	//shader.UseLightProjectionViewLocations(light.GetLightProjectionViewMatrices());

	//shader.Validate();

	//// Render scene objects 
	//BaseRenderer::RenderScene(scene);
}


void OpenGL_4_6_Renderer::SpotLightPass( Scene& scene, SpotLight& light)
{
	// PointLightPass(scene, light);
}

void OpenGL_4_6_Renderer::OmniDirectionalShadowMapPass(Scene& scene)
{
	//// get vars 
	//const vector<PointLight*>& pointLights = scene.GetPointLights();
	//const vector<SpotLight*>& spotLights = scene.GetSpotLights();

	//for (PointLight* light : pointLights)
	//{
	//	PointLightPass(scene, *light);
	//}

	//for (SpotLight* light : spotLights)
	//{
	//	PointLightPass(scene, *light);
	//}

	//// TO DEFAULT BUFFER 
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
