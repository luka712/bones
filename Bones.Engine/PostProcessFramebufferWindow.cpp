#include "PostProcessFramebufferWindow.hpp"
#include "PostProcessFramebuffer.hpp"
#include "imgui.h"

using Bones::Framebuffers::PostProcess::PostProcessFramebuffer;

Bones::UI::Windows::PostProcessFramebufferWindow::PostProcessFramebufferWindow(Bones::Engine& engine)
	: m_engine(engine)
{

}

void Bones::UI::Windows::PostProcessFramebufferWindow::Load_impl()
{
}

void Bones::UI::Windows::PostProcessFramebufferWindow::Initialize_impl()
{
}

void Bones::UI::Windows::PostProcessFramebufferWindow::Update_impl(F32)
{
	if (m_postProcessFramebuffer == nullptr) return;

	ImGui::Begin("Post Process Framebuffer", &m_active, ImGuiWindowFlags_MenuBar);
	ShowNameSection();
	ShowPropertiesTableSection();
	for (auto& pair : m_postProcessFramebuffer->m_values)
	{
		if (pair.second.m_type == PostProcessFramebuffer::ValueType::FLOAT)
		{
			ImGui::SliderFloat(pair.first.c_str(), &pair.second.m_value.m_asFloat, 0, 5, "%f.4f");
		}
		if (pair.second.m_type == PostProcessFramebuffer::ValueType::VEC2)
		{
			ImGui::SliderFloat2(pair.first.c_str(), pair.second.m_value.m_asFloat2, 0, 5, "%f.4f");
		}
	}
	ImGui::End();
}

void Bones::UI::Windows::PostProcessFramebufferWindow::Render_impl()
{
}

void Bones::UI::Windows::PostProcessFramebufferWindow::Destroy_impl()
{
}

void Bones::UI::Windows::PostProcessFramebufferWindow::SetPostProcessFramebuffer(Framebuffers::PostProcess::PostProcessFramebuffer* framebuffer)
{
	m_postProcessFramebuffer = framebuffer;
	m_postProcessFramebuffer->m_name.copy(m_nameBuffer, m_postProcessFramebuffer->m_name.size());
}

void Bones::UI::Windows::PostProcessFramebufferWindow::ShowNameSection()
{
	if (ImGui::InputText("name", m_nameBuffer, 128, ImGuiInputTextFlags_EnterReturnsTrue))
	{
		m_postProcessFramebuffer->m_name = std::string(m_nameBuffer);
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::PostProcessFramebufferWindow::ShowPropertiesTableSection()
{
	if (ImGui::BeginTable("properties", 3, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("Framebuffer Object Id");
		ImGui::TableSetupColumn("Renderbuffer Object Id");
		ImGui::TableSetupColumn("Texture Id");
		ImGui::TableHeadersRow();

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("%d", m_postProcessFramebuffer->m_fbo);
		ImGui::TableNextColumn();
		ImGui::Text("%d", m_postProcessFramebuffer->m_renderBufferObject);
		ImGui::TableNextColumn();
		ImGui::Text("%d", m_postProcessFramebuffer->m_textureId);
		ImGui::EndTable();
	}

	ImGui::Spacing();
}
