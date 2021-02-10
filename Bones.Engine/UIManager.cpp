#include "UIManager.hpp"
#include "BaseUIComponent.hpp"
#include "WindowUIComponent.hpp"
#include "ColorPickerUIComponent.hpp"
#include "CheckboxUIComponent.hpp"
#include "GroupUIComponent.hpp"
#include "TreeUIComponent.hpp"
#include "TextUIComponent.hpp"
#include "SelectableLabelUIComponent.hpp";

using namespace Bones::UI;
using namespace Bones::UI::Core;

// Nuklear stuff.
#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024
#if EMSCRIPTEN
#define NK_SDL_GLES2_IMPLEMENTATION
#else 
#define NK_SDL_GL3_IMPLEMENTATION
#endif
#include "nuklear.h"
#if EMSCRIPTEN
#include "nuklear_sdl_gles2.h"
#else 
#include "nuklear_sdl_gl3.h"
#endif 

nk_context* UIManager::m_ctx = nullptr;

vector<BaseUIComponent*> UIManager::m_components;
vector<BaseUIComponent*> UIManager::m_childComponents;
UIManager::UpdateData UIManager::m_updateData = { 200, 0 };
std::queue<SDL_Event> UIManager::m_eventQueue;

void UIManager::Initialize(SDL_Window* win)
{
	m_ctx = nk_sdl_init(win);
	/* Load Fonts: if none of these are loaded a default font will be used  */
	/* Load Cursor: if you uncomment cursor loading please hide the cursor */
	{struct nk_font_atlas* atlas;
	nk_sdl_font_stash_begin(&atlas);
	/*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
	/*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16, 0);*/
	/*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
	/*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
	/*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
	/*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
	nk_sdl_font_stash_end();
	/*nk_style_load_all_cursors(ctx, atlas->cursors);*/
	/*nk_style_set_font(ctx, &roboto->handle);*/}

	/* style.c */
#ifdef INCLUDE_STYLE
/*set_style(ctx, THEME_WHITE);*/
/*set_style(ctx, THEME_RED);*/
/*set_style(ctx, THEME_BLUE);*/
/*set_style(ctx, THEME_DARK);*/
#endif
}


void UIManager::PollEvents(SDL_Event evt)
{
	m_eventQueue.push(evt);
}


void UIManager::Update(Uint32 deltaTime)
{
	// process event 
	nk_input_begin(m_ctx);
	// process while not empty.
	while (m_eventQueue.empty() == false) {
		SDL_Event evt = m_eventQueue.front();
		nk_sdl_handle_event(&evt);
		m_eventQueue.pop();
	}
	nk_input_end(m_ctx);


	for (auto& component : m_components)
	{
		component->Update(deltaTime);
	}
}

void UIManager::Draw()
{
	/* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
* with blending, scissor, face culling, depth test and viewport and
* defaults everything back into a default state.
* Make sure to either a.) save and restore or b.) reset your own state after
* rendering the UI. */
	nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
}

void UIManager::Destroy()
{
	for (auto& cmp : m_childComponents)
	{
		delete cmp;
	}
	m_childComponents.clear();

	for (auto& cmp : m_components)
	{
		delete cmp;
	}
	m_components.clear();
}

WindowUIComponent* UIManager::CreateWindowComponent(string name, DrawRect drawRect)
{
	auto window = new WindowUIComponent(m_ctx, name, drawRect);
	m_components.push_back(window);
	return window;
}

ColorPickerUIComponent* UIManager::CreateColorPickerComponent(WindowUIComponent* parent, string name, Color color)
{
	auto colorPickr = new ColorPickerUIComponent(m_ctx, parent, name, color);
	m_childComponents.push_back(colorPickr);
	return colorPickr;
}

CheckboxUIComponent* UIManager::CreateCheckboxComponent(WindowUIComponent* parent, string name, bool value)
{
	auto cb = new CheckboxUIComponent(m_ctx, parent, name, value);
	m_childComponents.push_back(cb);
	return cb;
}

GroupUIComponent* UIManager::CreateGroupComponent(WindowUIComponent* parent, string name)
{
	GroupUIComponent* g = new GroupUIComponent(m_ctx, name);
	m_childComponents.push_back(g);
	return g;
}

TreeUIComponent* UIManager::CreateTreeComponent(WindowUIComponent* parent, string name)
{
	TreeUIComponent* tree = new TreeUIComponent(m_ctx, name);
	m_childComponents.push_back(tree);
	return tree;
}


TextUIComponent* UIManager::CreateTextComponent(WindowUIComponent* parent, string value, string label)
{
	TextUIComponent* text = new TextUIComponent(m_ctx, parent, value, label);
	m_childComponents.push_back(text);
	return text;
}

SelectableLabelUIComponent* UIManager::CreateSelectableLabelComponent(WindowUIComponent* parent, const string& label)
{
	SelectableLabelUIComponent* lbl = new SelectableLabelUIComponent(m_ctx, label);
	m_childComponents.push_back(lbl);
	parent->AddComponent(lbl);
	return lbl;
}

SelectableLabelUIComponent* UIManager::CreateSelectableLabelComponent(TreeUIComponent* parent, const string& label)
{
	SelectableLabelUIComponent* lbl = new SelectableLabelUIComponent(m_ctx, label);
	m_childComponents.push_back(lbl);
	parent->AddComponent(lbl);
	return lbl;
}

void UIManager::DestroyComponent(BaseUIComponent* component)
{
	for (size_t i = 0; i < m_childComponents.size(); i++)
	{
		BaseUIComponent* ptr = m_childComponents[i];
		if (ptr == component)
		{
			m_childComponents.erase(m_childComponents.begin() + i);
			// TODO: handle in self.f
			ptr->m_parent->DestroyComponent(ptr);
			delete ptr;
		}
	}

	for (size_t i = 0; i < m_components.size(); i++)
	{
		BaseUIComponent* ptr = m_components[i];
		if (ptr == component)
		{
			m_components.erase(m_components.begin() + i);
			delete ptr;
		}
	}
}

