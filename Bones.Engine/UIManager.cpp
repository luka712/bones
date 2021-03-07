#include "UIManager.hpp"
#include "Engine.hpp"
#include "IEvent.hpp"
#include "HierarchyWindow.hpp"
#include "IndexBufferWindow.hpp"
#include "VertexBufferWindow.hpp"
#include "InterleavedBufferWindow.hpp"
#include "IndexBuffer.hpp"

Bones::UI::UIManager::UIManager(Bones::Engine& engine)
	: m_engine(engine)
{
	m_hierarchyWindow = new Bones::UI::Windows::HierarchyWindow(m_engine);
	m_indexBufferWindow = new Bones::UI::Windows::IndexBufferWindow(m_engine);
	m_indexBufferWindow->m_active = false;
	m_vertexBufferWindow = new Bones::UI::Windows::VertexBufferWindow(m_engine);
	m_vertexBufferWindow->m_active = false;
	m_interleavedBufferWindow = new Bones::UI::Windows::InterleavedBufferWindow(m_engine);
	m_interleavedBufferWindow->m_active = false;
}

Bones::UI::UIManager::~UIManager()
{
	Destroy();
}

void Bones::UI::UIManager::Load_impl()
{
	IMGUI_CHECKVERSION();

	m_hierarchyWindow->Load();
	m_indexBufferWindow->Load();
}

void Bones::UI::UIManager::Initialize_impl()
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_engine.m_renderer->m_window, m_engine.m_renderer->m_glContext);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();

	m_hierarchyWindow->Initialize();
	m_indexBufferWindow->Initialize();


	m_hierarchyWindow->m_onIndexBufferSelected += [&](const Bones::IEvent& evt) -> void
	{
		m_indexBufferWindow->m_active = true;
		m_indexBufferWindow->SetIndexBuffer(static_cast<Buffers::IndexBuffer*>(evt.m_arguments.at("index_buffer").m_asPointer));
	};

	m_hierarchyWindow->m_onVertexBufferSelected += [&](const Bones::IEvent& evt) -> void
	{
		m_vertexBufferWindow->m_active = true;
		m_vertexBufferWindow->SetVertexBuffer(static_cast<Buffers::VertexBuffer*>(evt.m_arguments.at("vertex_buffer").m_asPointer));
	};

	m_hierarchyWindow->m_onInterleavedBufferSelected += [&](const Bones::IEvent& evt) -> void
	{
		m_interleavedBufferWindow->m_active = true;
		m_interleavedBufferWindow->SetInterleavedBuffer(static_cast<Buffers::InterleavedBuffer*>(evt.m_arguments.at("interleaved_buffer").m_asPointer));
	};
}

void Bones::UI::UIManager::Update_impl(F32 dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_engine.m_renderer->m_window);
	ImGui::NewFrame();

	m_hierarchyWindow->Update(dt);
	m_indexBufferWindow->Update(dt);
	m_vertexBufferWindow->Update(dt);
	m_interleavedBufferWindow->Update(dt);
}

void Bones::UI::UIManager::Render_impl()
{
	m_hierarchyWindow->Render();
	m_indexBufferWindow->Render();
	m_vertexBufferWindow->Render();
	m_interleavedBufferWindow->Render();
}

void Bones::UI::UIManager::Destroy_impl()
{
	m_hierarchyWindow->Destroy();
	delete m_hierarchyWindow;

	m_indexBufferWindow->Destroy();
	delete m_indexBufferWindow;

	m_vertexBufferWindow->Destroy();
	delete m_vertexBufferWindow;

	m_interleavedBufferWindow->Destroy();
	delete m_interleavedBufferWindow;

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

void Bones::UI::UIManager::OnBeforeRender_impl()
{
	ImGui::Render();
}

void Bones::UI::UIManager::OnAfterRender_impl()
{
	// disabled cached shader check 
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

