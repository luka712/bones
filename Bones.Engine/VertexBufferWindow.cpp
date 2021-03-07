#include "VertexBufferWindow.hpp"
#include "Engine.hpp"
#include "imgui.h"
#include "VertexBuffer.hpp"
#include "utils.h"

Bones::UI::Windows::VertexBufferWindow::VertexBufferWindow(Bones::Engine& engine)
	:m_engine(engine)
{
}

void Bones::UI::Windows::VertexBufferWindow::Load_impl()
{
}

void Bones::UI::Windows::VertexBufferWindow::Initialize_impl()
{
}

void Bones::UI::Windows::VertexBufferWindow::Update_impl(F32)
{
	if (m_vertexBuffer == nullptr) return;

	ImGui::Begin("Vertex Buffer View", &m_active, ImGuiWindowFlags_MenuBar);
	ShowNameSection();
	ShowPropertiesTableSection();
	ShowVerticesTableSection();
	ImGui::End();
}

void Bones::UI::Windows::VertexBufferWindow::Render_impl()
{
}

void Bones::UI::Windows::VertexBufferWindow::Destroy_impl()
{
}

void Bones::UI::Windows::VertexBufferWindow::SetVertexBuffer(Buffers::VertexBuffer* iBuffer)
{
	m_vertexBuffer = iBuffer;
	iBuffer->m_name.copy(m_nameBuffer, iBuffer->m_name.size());
}

void Bones::UI::Windows::VertexBufferWindow::ShowNameSection()
{

	if (ImGui::InputText("name", m_nameBuffer, 128, ImGuiInputTextFlags_EnterReturnsTrue))
	{
		m_vertexBuffer->m_name = std::string(m_nameBuffer);
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::VertexBufferWindow::ShowPropertiesTableSection()
{

	if (ImGui::BeginTable("properties", 7, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("Attribute id");
		ImGui::TableSetupColumn("Attribute name");
		ImGui::TableSetupColumn("Struct Type");
		ImGui::TableSetupColumn("Struct Element Length");
		ImGui::TableSetupColumn("Struct Length");
		ImGui::TableSetupColumn("no. Elements");
		ImGui::TableSetupColumn("Total Length");
		ImGui::TableHeadersRow();

		ImGui::TableNextRow();

		// Attrib id
		ImGui::TableNextColumn();
		ImGui::Text("%d", m_vertexBuffer->m_attributeLocation, 0, 0);

		// attrib name
		ImGui::TableNextColumn();
		ImGui::Text(m_vertexBuffer->m_layoutName.c_str());

		// Size of element attrib
		ImGui::TableNextColumn();
		if (m_vertexBuffer->m_structSize == 1)
			ImGui::Text("Float", 0, 0);
		else
			ImGui::Text("Vector%d", m_vertexBuffer->m_structSize);

		// Struct element length
		ImGui::TableNextColumn();
		ImGui::Text("%d_b", m_vertexBuffer->m_structComponentLength);

		// Struct length
		ImGui::TableNextColumn();
		ImGui::Text("%d_b", m_vertexBuffer->m_structLength);

		// Count of elements in attrib
		ImGui::TableNextColumn();
		ImGui::Text("%d", m_vertexBuffer->m_count);

		// Total buffer length
		ImGui::TableNextColumn();
		ImGui::Text("%d_b", m_vertexBuffer->m_length);

		ImGui::EndTable();
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::VertexBufferWindow::ShowVerticesTableSection()
{
	// For paging, max items to show and page offset 
	static I32 staticMaxCount = 20;
	static I32 staticPageStart = 0;

	U64 structLength = m_vertexBuffer->m_structLength; // length of row in bytes. for example for struct size 2 and int it should be 8
	U64 length = m_vertexBuffer->m_length / m_vertexBuffer->m_structSize - structLength; // offset last row from total length

	U64 byteSize = m_vertexBuffer->m_structComponentLength;

	// Create pagination sliders 
	ImGui::SliderInt("max items to show", &staticMaxCount, 1, 20);
	ImGui::SliderInt("page start", &staticPageStart, 0, m_vertexBuffer->m_length / m_vertexBuffer->m_structLength / m_vertexBuffer->m_structSize);

	// Size of elements, is it float, vec2, vec3 ... 
	I32 structSize = m_vertexBuffer->m_structSize;

	// Length is always bytes, therefore we reference as such
	U64 pageOffsetLength = std::min(length, staticPageStart * structLength);
	U64 lengthToCount = std::min(length, pageOffsetLength + (staticMaxCount * structLength - structLength));

	if (ImGui::BeginTable("indices", structSize + 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("#");
		ImGui::TableSetupColumn("x");
		if (structSize > 1)
			ImGui::TableSetupColumn("y");
		if (structSize > 2)
			ImGui::TableSetupColumn("z");
		if (structSize > 3)
			ImGui::TableSetupColumn("w");

		ImGui::TableHeadersRow();

		// Going throught length, due to bytes.
		U64 index = pageOffsetLength / structLength;
		for (U64 r = pageOffsetLength; r <= lengthToCount; r += structLength)
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("%d.", index++);

			// V1... columns
			for (U64 c = 0; c < structSize; c++)
			{

				ImGui::TableNextColumn();

				U64 index = r + (c * byteSize);


				if (byteSize == 1)
				{
					// TODO if not a float and byte size 2 
				}
				if (byteSize == 2)
				{
					// TODO if not a float and byte size 2 
				}
				// TODO if not a float, for example U32
				if (byteSize == 4)
				{
					// bytes to pointer.
					F32 val = Bones::Utils::ConvertU8ToF32(
						m_vertexBuffer->m_data[index],
						m_vertexBuffer->m_data[index + 1UL],
						m_vertexBuffer->m_data[index + 2UL],
						m_vertexBuffer->m_data[index + 3UL]);

					ImGui::Text("%.4f", val);
				}

			}
		}

		ImGui::EndTable();
	}
}




