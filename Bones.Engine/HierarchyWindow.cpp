#include "HierarchyWindow.hpp"
#include "Engine.hpp"
#include "BuffersManager.hpp"
#include "FramebufferManager.hpp"
#include "imgui.h"


Bones::UI::Windows::HierarchyWindow::HierarchyWindow(Bones::Engine& engine)
	:m_engine(engine) {}

void Bones::UI::Windows::HierarchyWindow::Load_impl()
{
}

void Bones::UI::Windows::HierarchyWindow::Initialize_impl()
{
}

void Bones::UI::Windows::HierarchyWindow::Update_impl(F32)
{
	ImGui::Begin("Hierarchy", &m_active, ImGuiWindowFlags_MenuBar);

	// -- MENU BAR
	if (ImGui::BeginMenuBar())
	{
		// -- SHOW
		if (ImGui::BeginMenu("Show"))
		{
			ImGui::Checkbox("Show Index Buffers", &m_showBuffers.m_index);
			ImGui::Checkbox("Show Vertices Buffers", &m_showBuffers.m_vertices);
			ImGui::Checkbox("Show Interleaved Buffers", &m_showBuffers.m_interleaved);
			ImGui::Separator();
			ImGui::Checkbox("Show Post Process Framebuffers", &m_showFramebuffers.m_postProcess);
			ImGui::EndMenu();
		}
		// -- END SHOW
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::BeginMenu("Post Process Framebuffer"))
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				if (ImGui::Button("Blur Framebuffer"))
					Bones::Managers::FramebufferManager::GetOrCreateBlurFramebuffer();
				if (ImGui::Button("Detect Edge Framebuffer"))
					Bones::Managers::FramebufferManager::GetOrCreateDetectEdgeFramebuffer();
				if (ImGui::Button("Gray Scale Framebuffer"))
					Bones::Managers::FramebufferManager::GetOrCreateGrayScaleFramebuffer();
				if (ImGui::Button("Gray Scale Ordered Dithering Framebuffer"))
					Bones::Managers::FramebufferManager::GetOrCreateGrayScaleOrderedDitheringFramebuffer();
				if (ImGui::Button("Invert Color Framebuffer"))
					Bones::Managers::FramebufferManager::GetOrCreateInvertColorFramebuffer();
				if (ImGui::Button("Night Shader Post Process Framebuffer"))
					Bones::Managers::FramebufferManager::GetOrCreateNightVisionFramebuffer();
				if (ImGui::Button("Gray Scale Ordered Dithering Framebuffer"))
					Bones::Managers::FramebufferManager::GetOrCreateInvertColorFramebuffer();

				ImGui::PopStyleColor(1);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	// -- END MENU BAR

	BuffersTree();
	FramebufferTree();


	ImGui::End();
}

void Bones::UI::Windows::HierarchyWindow::Render_impl()
{

}

void Bones::UI::Windows::HierarchyWindow::Destroy_impl()
{
}

void Bones::UI::Windows::HierarchyWindow::BuffersTree()
{
	// -- BUFFERS TREE VIEW
	if (ImGui::TreeNode("Buffers"))
	{
		// -- INDEX BUFFER TREE VIEW 
		if (ImGui::TreeNode("Index Buffers"))
		{
			static I32 selectedIndexBufferIndex = -1;
			for (size_t i = 0; i < Bones::Managers::BuffersManager::m_indexBufferCache.size(); i++)
			{
				auto& iBuffer = Bones::Managers::BuffersManager::m_indexBufferCache[i];
				if (ImGui::Selectable(iBuffer->m_name.c_str(), selectedIndexBufferIndex == i))
				{
					selectedIndexBufferIndex = static_cast<I32>(i);
					m_onIndexBufferSelected.Invoke(Bones::IEvent("ui.index_buffer_selected",
						{
							{"source", Variant(this) },
							{"index_buffer", Variant(&*iBuffer) },
							{"index", Variant(selectedIndexBufferIndex) }
						}));
				}
			}
			ImGui::TreePop();
		}
		// -- END INDEX BUFFER TREE VIEW 

		// -- VERTEX BUFFER TREE VIEW 
		if (ImGui::TreeNode("Vertex Buffers"))
		{
			static int selectedVertexBufferIndex = -1;
			for (size_t i = 0; i < Bones::Managers::BuffersManager::m_vertexBufferCache.size(); i++)
			{
				auto& vBuffer = Bones::Managers::BuffersManager::m_vertexBufferCache[i];
				if (ImGui::Selectable(vBuffer->m_name.c_str(), selectedVertexBufferIndex == i))
				{
					selectedVertexBufferIndex = i;
					m_onVertexBufferSelected.Invoke(Bones::IEvent("ui.vertex_buffer_selected",
						{
							{"source", Variant(this) },
							{"vertex_buffer", Variant(&*vBuffer) },
							{"index", Variant(selectedVertexBufferIndex) }
						}));
				}
			}
			ImGui::TreePop();
		}
		// -- END VERTEX BUFFER TREE VIEW 

		// -- INTERLEAVED BUFFER TREE VIEW 
		if (ImGui::TreeNode("Interleaved Buffers"))
		{
			static int selectedIntrlvdBufferIndex = -1;
			for (size_t i = 0; i < Bones::Managers::BuffersManager::m_interleavedBufferCache.size(); i++)
			{
				auto& iBuffer = Bones::Managers::BuffersManager::m_interleavedBufferCache[i];
				if (ImGui::Selectable(iBuffer->m_name.c_str(), selectedIntrlvdBufferIndex == i))
				{
					selectedIntrlvdBufferIndex = i;
					m_onInterleavedBufferSelected.Invoke(Bones::IEvent("ui.interleaved_buffer_selected",
						{
							{"source", Variant(this) },
							{"interleaved_buffer", Variant(&*iBuffer) },
							{"index", Variant(selectedIntrlvdBufferIndex) }
						}));
				}
			}
			ImGui::TreePop();
		}
		// -- END INTERLEAVED BUFFER TREE VIEW 

		ImGui::TreePop();
	}
	// -- END BUFFERS TREE VIEW
}

void Bones::UI::Windows::HierarchyWindow::FramebufferTree()
{
	// -- FRAMEBUFFERS TREE VIEW
	if (ImGui::TreeNode("Framebuffers"))
	{
		if (ImGui::TreeNode("Postprocess Framebuffers"))
		{
			static I32 selectedPostProcessFramebuf = -1;
			for (I32 i = 0; i < Bones::Managers::FramebufferManager::m_postProcessFramebuffers.size(); i++)
			{
				auto& ppFramebuffer = Bones::Managers::FramebufferManager::m_postProcessFramebuffers[i];

				if (ImGui::Selectable(ppFramebuffer->m_name.c_str(), selectedPostProcessFramebuf == i))
				{
					selectedPostProcessFramebuf = i;
					m_onPostProcessFramebufferSelected.Invoke(Bones::IEvent("ui.post_process_framebuffer_selected",
						{
							{"source", Variant(this)},
							{"post_process_framebuffer", Variant(&*ppFramebuffer)},
							{"index", Variant(selectedPostProcessFramebuf)}
						}));
				}
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
	// END
}
