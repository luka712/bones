#include "UIManager.hpp"
#include "Engine.hpp"
#include "IEvent.hpp"

Bones::UI::UIManager::UIManager(Bones::Engine& engine)
	: m_engine(engine)
{

}

Bones::UI::UIManager::~UIManager()
{
	Destroy();
}

void Bones::UI::UIManager::Load_impl()
{
	IMGUI_CHECKVERSION();
}

void Bones::UI::UIManager::Initialize_impl()
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_engine.m_renderer->m_window, m_engine.m_renderer->m_glContext);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();
}

void Bones::UI::UIManager::Update_impl(F32 dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_engine.m_renderer->m_window);
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");

	ImGui::End();
}

void Bones::UI::UIManager::Render_impl()
{
	
}

void Bones::UI::UIManager::Destroy_impl()
{
#if EMSCRIPTEN_RUNTIME
#else 
	ImGui_ImplOpenGL3_Shutdown();
#endif 
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void Bones::UI::UIManager::OnSDLEvent_impl(const SDL_Event& evt)
{
	ImGui_ImplSDL2_ProcessEvent(&evt);
}

