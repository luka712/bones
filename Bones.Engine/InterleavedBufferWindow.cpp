#include "InterleavedBufferWindow.hpp"
#include "Engine.hpp"
#include "imgui.h"
#include "InterleavedBuffer.hpp"
#include "utils.h"

Bones::UI::Windows::InterleavedBufferWindow::InterleavedBufferWindow(Bones::Engine& engine)
	:m_engine(engine)
{
}

void Bones::UI::Windows::InterleavedBufferWindow::Load_impl()
{
}

void Bones::UI::Windows::InterleavedBufferWindow::Initialize_impl()
{
}

void Bones::UI::Windows::InterleavedBufferWindow::Update_impl(F32)
{
	if (m_interleavedBuffer == nullptr) return;

	ImGui::Begin("Interleaved Buffer View", &m_active, ImGuiWindowFlags_MenuBar);
	ShowNameSection();
	ShowPropertiesTableSection();
	ShowAttributesTableSection();
	ShowVerticesTableSection();
	ImGui::End();
}

void Bones::UI::Windows::InterleavedBufferWindow::Render_impl()
{
}

void Bones::UI::Windows::InterleavedBufferWindow::Destroy_impl()
{
}

void Bones::UI::Windows::InterleavedBufferWindow::SetInterleavedBuffer(Buffers::InterleavedBuffer* iBuffer)
{
	m_interleavedBuffer = iBuffer;
	iBuffer->m_name.copy(m_nameBuffer, iBuffer->m_name.size());
}

void Bones::UI::Windows::InterleavedBufferWindow::ShowNameSection()
{
	if (ImGui::InputText("name", m_nameBuffer, 128, ImGuiInputTextFlags_EnterReturnsTrue))
	{
		m_interleavedBuffer->m_name = std::string(m_nameBuffer);
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::InterleavedBufferWindow::ShowPropertiesTableSection()
{
	if (ImGui::BeginTable("properties", 3, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		// -- HEADERS
		ImGui::TableSetupColumn("no. Elements");
		ImGui::TableSetupColumn("Total length");
		ImGui::TableSetupColumn("Stride length");
		ImGui::TableHeadersRow();

		ImGui::TableNextRow();

		// -- Layout id
		ImGui::TableNextColumn();
		ImGui::Text("%d", m_interleavedBuffer->m_count);

		ImGui::TableNextColumn();
		ImGui::Text("%d_b", m_interleavedBuffer->m_length);

		ImGui::TableNextColumn();
		ImGui::Text("%d_b", m_interleavedBuffer->m_strideLength);

		ImGui::EndTable();
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::InterleavedBufferWindow::ShowAttributesTableSection()
{
	// -- Attributes
	if (ImGui::BeginTable("attributes", 6, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		// -- HEADERS
		ImGui::TableSetupColumn("Attribute id");
		ImGui::TableSetupColumn("Attribute name");
		ImGui::TableSetupColumn("Struct Type");
		ImGui::TableSetupColumn("Struct Element Length");
		ImGui::TableSetupColumn("Struct Length");
		ImGui::TableSetupColumn("Stride offset");
		ImGui::TableHeadersRow();

		// Go through attributes 
		// -- ROWS 
		for (auto& attr : m_interleavedBuffer->m_attributes)
		{
			ImGui::TableNextRow();

			// -- Layout id
			ImGui::TableNextColumn();
			ImGui::Text("%d", attr.m_attributeLocation, 0, 0);

			// -- Layout name 
			ImGui::TableNextColumn();
			ImGui::Text(attr.m_attributeLayoutName.c_str(), 0, 0);

			// -- Struct type 
			ImGui::TableNextColumn();
			if (attr.m_structSize == 1)
				ImGui::Text("Float", 0, 0);
			else
				ImGui::Text("Vector%d", attr.m_structSize, 0, 0);

			// -- Struct element length
			ImGui::TableNextColumn();
			ImGui::Text("%d_b", attr.m_structComponentLength);

			// Struct length
			ImGui::TableNextColumn();
			ImGui::Text("%d_b", attr.StructLength());

			ImGui::TableNextColumn();
			ImGui::Text("%d_b", attr.m_offsetLength);
		}

		ImGui::EndTable();
	}

	ImGui::Spacing();
}

void Bones::UI::Windows::InterleavedBufferWindow::ShowVerticesTableSection()
{
	// For paging, max items to show and page offset 
	static I32 staticMaxCount = 20;
	static I32 staticPageStart = 0;

	U64 strideLength = m_interleavedBuffer->m_strideLength; // length of row in bytes. for example for struct size 2 and int it should be 8
	U64 componentsSize = m_interleavedBuffer->m_strideComponentsSize;
	// Each row is stride of all components.
	U64 rows = m_interleavedBuffer->m_length - strideLength; // offset last row from total lengt

	// Create pagination sliders 
	ImGui::SliderInt("max items to show", &staticMaxCount, 1, 20);
	ImGui::SliderInt("page start", &staticPageStart, 0, m_interleavedBuffer->m_length / strideLength);

	// Length is always bytes, therefore we reference as such
	U64 pageOffsetLength = std::min(rows, staticPageStart * strideLength);
	U64 lengthToCount = std::min(rows, pageOffsetLength + (staticMaxCount * strideLength - strideLength));

	if (ImGui::BeginTable("indices", componentsSize + 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("#");

		for (auto& attrib : m_interleavedBuffer->m_attributes)
		{
			// Change label type 
			// TODO: ability to change labels 
			ImGui::TableSetupColumn("x");
			if (attrib.m_structSize > 1)
				ImGui::TableSetupColumn("y");
			if (attrib.m_structSize > 2)
				ImGui::TableSetupColumn("z");
			if (attrib.m_structSize > 3)
				ImGui::TableSetupColumn("w");
		}

		ImGui::TableHeadersRow();

		// Going throught length, due to bytes.
		U64 index = pageOffsetLength / strideLength;
		for (U64 r = pageOffsetLength; r <= lengthToCount; r += strideLength)
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("%llu.", index++);

			// C is outside due to pass of all attribs
			U64 c = 0;
			U64 attribStructSize = 0;
			for (auto& attrib : m_interleavedBuffer->m_attributes)
			{
				// V1... columns
				attribStructSize += attrib.m_structSize;
				for (; c < attribStructSize; c++)
				{

					ImGui::TableNextColumn();

					U64 index = r + (c * attrib.m_structComponentLength);


					if (attrib.m_structComponentLength == 1)
					{
						// TODO if not a float and byte size 2 
					}
					if (attrib.m_structComponentLength == 2)
					{
						// TODO if not a float and byte size 2 
					}
					// TODO if not a float, for example U32
					if (attrib.m_structComponentLength == 4)
					{
						// bytes to pointer.
						F32 val = Bones::Utils::ConvertU8ToF32(
							m_interleavedBuffer->m_data[index],
							m_interleavedBuffer->m_data[index + 1UL],
							m_interleavedBuffer->m_data[index + 2UL],
							m_interleavedBuffer->m_data[index + 3UL]);

						ImGui::Text("%.4f", val);
					}
				}
			}
		}

		ImGui::EndTable();
	}

	ImGui::Spacing();
}

