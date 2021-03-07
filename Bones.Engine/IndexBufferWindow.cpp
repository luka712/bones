#include "IndexBufferWindow.hpp"
#include "Engine.hpp"
#include "imgui.h"
#include "IndexBuffer.hpp"
#include "utils.h"

Bones::UI::Windows::IndexBufferWindow::IndexBufferWindow(Bones::Engine& engine)
	:m_engine(engine)
{
}

void Bones::UI::Windows::IndexBufferWindow::Load_impl()
{
}

void Bones::UI::Windows::IndexBufferWindow::Initialize_impl()
{
}

void Bones::UI::Windows::IndexBufferWindow::Update_impl(F32)
{
	if (m_indexBuffer == nullptr) return;

	ImGui::Begin("Index Buffer View", &m_active, ImGuiWindowFlags_MenuBar);
	ShowNameSection();
	ShowPropertiesTableSection();
	ShowIndicesTableSection();
	ImGui::End();
}

void Bones::UI::Windows::IndexBufferWindow::Render_impl()
{
}

void Bones::UI::Windows::IndexBufferWindow::Destroy_impl()
{
}

void Bones::UI::Windows::IndexBufferWindow::SetIndexBuffer(Buffers::IndexBuffer* iBuffer)
{
	m_indexBuffer = iBuffer;
	iBuffer->m_name.copy(m_nameBuffer, iBuffer->m_name.size());
}

void Bones::UI::Windows::IndexBufferWindow::ShowNameSection()
{
	if (ImGui::InputText("name", m_nameBuffer, 128, ImGuiInputTextFlags_EnterReturnsTrue))
	{
		m_indexBuffer->m_name = std::string(m_nameBuffer);
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::IndexBufferWindow::ShowPropertiesTableSection()
{
	if (ImGui::BeginTable("properties", 4, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("GL Type");
		ImGui::TableSetupColumn("Element length");
		ImGui::TableSetupColumn("no. structSize");
		ImGui::TableSetupColumn("Length");
		ImGui::TableHeadersRow();

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(m_indexBuffer->IndexTypeAsChar());
		ImGui::TableNextColumn();
		ImGui::Text("%d_b", m_indexBuffer->m_structComponentLength);
		ImGui::TableNextColumn();
		ImGui::Text("%d", m_indexBuffer->m_count);
		ImGui::TableNextColumn();
		ImGui::Text("%db", m_indexBuffer->m_length);
		ImGui::EndTable();
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::IndexBufferWindow::ShowIndicesTableSection()
{

	// Select type to show as , for example show indices as triangle, as lines or as points
	static const char* type[] = { "Point" , "Line", "Triangle" };
	static U32 typeIndex = 2;

	static U32 startAt = 2;

	if (ImGui::BeginCombo("show as", type[typeIndex], 0))
	{
		for (size_t n = 0; n < 3; n++)
		{
			if (ImGui::Selectable(type[n], typeIndex == n))
				typeIndex = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (typeIndex == n)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	I32 structSize = typeIndex + 1;

	// Get the correct byte size
	U64 byteSize = 1;
	switch (m_indexBuffer->m_structComponentLength)
	{
	case Bones::IndicesByteSize::UNSIGNED_SHORT:
		byteSize = 2;
		break;
	case Bones::IndicesByteSize::UNSIGNED_INT:
		byteSize = 4;
		break;
	}

	// For paging, max items to show and page offset 
	static I32 staticMaxCount = 20;
	static I32 staticPageStart = 0;

	// default values. Length is in bytes. 64 bytes - 2 * 4 as last offset.
	U64 structLength = structSize * byteSize; // length of row in bytes. for example for struct size 2 and int it should be 8
	U64 length = m_indexBuffer->m_length - structLength; // offset last row from total length
	U64 count = m_indexBuffer->m_length / structLength;

	// Create pagination sliders 
	ImGui::SliderInt("max items to show", &staticMaxCount, 1, 20);
	ImGui::SliderInt("page start", &staticPageStart, 0, count);

	// Length is always bytes, therefore we reference as such
	U64 pageOffsetLength = std::min(length, staticPageStart * structLength);
	U64 lengthToCount = std::min(length, pageOffsetLength + (staticMaxCount * structLength - structLength));


	if (ImGui::BeginTable("indices", structSize + 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("#");
		ImGui::TableSetupColumn("i1");
		if (structSize > 1)
			ImGui::TableSetupColumn("i2");
		if (structSize > 2)
			ImGui::TableSetupColumn("i3");

		ImGui::TableHeadersRow();

		U64 index = pageOffsetLength / structLength;
		for (U64 r = pageOffsetLength; r <= lengthToCount; r += structLength)
		{
			ImGui::TableNextRow();

			ImGui::TableNextColumn();
			ImGui::Text("%llu.", index++);

			for (U64 c = 0; c < structSize; c++)
			{
				ImGui::TableNextColumn();

				U64 index = r + (c * byteSize);

				if (byteSize == 1)
					ImGui::Text("%d", m_indexBuffer->m_data.at(index));
				if (byteSize == 2)
				{
					ImGui::Text("%d", Bones::Utils::ConvertB8ToB16<U16>(
						m_indexBuffer->m_data[index],
						m_indexBuffer->m_data[index + 1UL]
						));
				}
				if (byteSize == 4)
				{
					ImGui::Text("%d", Bones::Utils::ConvertB8ToB32<U32>(
						m_indexBuffer->m_data[index],
						m_indexBuffer->m_data[index + 1UL],
						m_indexBuffer->m_data[index + 2UL],
						m_indexBuffer->m_data[index + 3UL]
						));
				}
			}
		}

		ImGui::EndTable();
	}

}


