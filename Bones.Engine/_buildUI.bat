em++^
 main.cpp^
 UIManager.cpp^
 HierarchyWindow.cpp IndexBufferWindow.cpp InterleavedBufferWindow.cpp VertexBufferWindow.cpp^
 Common.cpp^
 utils.cpp^
 BaseBuffer.cpp VertexBuffer.cpp IndexBuffer.cpp InterleavedBuffer.cpp^
 BaseCamera.cpp FreeCamera.cpp OrbitCamera.cpp^
 TransformComponent.cpp ControlsComponent.cpp DrawOutlineComponent.cpp^
 Engine.cpp^
 Skybox.cpp^
 BaseFramebuffer.cpp PostProcessFramebuffer.cpp NightVisionPostProcessFramebuffer.cpp^
 BaseGeometry.cpp^
 core_types.cpp EventQueue.cpp^
 AmbientLight.cpp BaseLight.cpp DirectionalLight.cpp PointLight.cpp SpotLight.cpp^
 SceneObjectLoader.cpp FileLoader.cpp TextureLoader.cpp ShaderParser.cpp BaseModelLoader.cpp TextureLoaderDataStructs.cpp^
 BuffersManager.cpp FramebufferManager.cpp GeometryManager.cpp MaterialManager.cpp MeshManager.cpp SceneManager.cpp ShaderManager.cpp TextureManager.cpp^
 BaseMaterial.cpp StandardMaterial.cpp^
 BaseMesh.cpp StandardMaterialMesh.cpp^
 BasePostProcessPipeline.cpp^
 BaseRenderer.cpp OpenGL_ES_3_0_Renderer.cpp^
 Scene.cpp^
 SceneObject.cpp^
 BaseShader.cpp SkyboxShader.cpp MaterialShader.cpp BasePostProcessShader.cpp BlurShader.cpp DetectEdgeShader.cpp GrayScaleOrderedDitheringShader.cpp GrayScaleShader.cpp InvertColorShader.cpp SharpenShader.cpp StencilOutlineShader.cpp NightVisionShader.cpp^
 BaseTexture.cpp CubeTexture.cpp Texture2D.cpp^
 BlyObjLoader.cpp TinyObjLoader.cpp TinyGltfLoader.cpp^
 imgui.cpp imgui_draw.cpp imgui_impl_opengl3.cpp imgui_impl_sdl.cpp imgui_tables.cpp imgui_widgets.cpp^
 ^
 -s USE_WEBGL2=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2^
 -s WASM=1 -s FETCH=1 -s -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0^
 -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1^
 -s ASSERTIONS=1^
 -std=c++17^
 --bind^
 --use-preload-plugins^
 --preload-file resources^
 -g0^
 -g^
 -o index.html