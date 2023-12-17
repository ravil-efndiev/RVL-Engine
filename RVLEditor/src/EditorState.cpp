#include "EditorState.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/OpenGL/GLFrameBuffer.hpp>

struct EditorUIData 
{
    ImGuiWindowFlags GlobalWinFlags;
    glm::vec2 FBOViewport;
};

static EditorUIData UIData;

EditorState::EditorState() : State(RenderMode_Any) {}
EditorState::~EditorState() {}

void EditorState::Start()
{
    CreateFrameBuffer({1000, 600});

    _camera = UserPerspectiveCamera::New({0.f, 0.f, 0.f}, 45.f);

    _directionalLight = _currentScene.NewEntity("Directional light");
    _directionalLight.Add<DirectionalLightComponent>(glm::vec3(0.9f, 0.9f, 0.9f));

    _model = _currentScene.NewEntity("Model");
    _model.Add<ModelComponent>("./assets/textures/backpack.obj");
    _mat = &_model.Add<MaterialComponent>(glm::vec3(0.5, 0.4, 0.2), 32.f);

    _hierarchy = NewRef<HierarchyWindow>(_currentScene);
    _inspector = NewRef<InspectorWindow>();

    tex = NewRef<GLTexture>("./assets/textures/container.jpg");
}

void EditorState::Update()
{
    if (Input::IsKeyPressedOnce(Keys::Key_Escape))
    {
        _lock = !_lock;
        App::GetInstance()->SetCursorLocked(_lock);
    }

    UserCamera::ToPerspective(_camera)->UpdateControls(ControllerType::InPlane, 5.f);

    if (_lock) UserCamera::ToPerspective(_camera)->UpdateCursorRotation(2.f);

    _mat->SetUniform("u_ViewPos", UserCamera::ToPerspective(_camera)->Position());
}

void EditorState::Render()
{
    DockspaceAndMenu();
    RenderImGui();
    SceneRenderer::Render(_currentScene, _camera);
}

void EditorState::RenderImGui()
{
    auto stats = Renderer::GetStats();

    ImGui::Begin("Statistics", nullptr, UIData.GlobalWinFlags);
        ImGui::Text("Application average %.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
        ImGui::Text("Application immidieate %.1f FPS (%.3f ms/frame)", 1.f / Time::DeltaTime(), 1000.f / (1.f / Time::DeltaTime()));
        ImGui::Separator();
        ImGui::Text("Draw calls: %d", stats.DrawCalls);
        ImGui::Text("Total verticies: %d", stats.VerticiesCount);
        ImGui::Text("Total indicies: %d", stats.IndiciesCount);
        ImGui::Text("Total Rectangles: %d", stats.RectCount);
    ImGui::End();

    _hierarchy->ImGuiRender();

    _inspector->SetSelected(_hierarchy->GetSelected());
    _inspector->ImGuiRedner();

    ImGui::Begin("Scene", nullptr, UIData.GlobalWinFlags);
        ImGui::BeginChild("Render");
        
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (UIData.FBOViewport != ImToGlmVec2(viewportSize))
        {
            UIData.FBOViewport = {viewportSize.x, viewportSize.y};
            _fbo->Resize(viewportSize.x, viewportSize.y);
        }

        ImGui::Image(
            (ImTextureID)_fbo->GetColorAttachment(), 
            ImGui::GetContentRegionAvail(), 
            ImVec2(0, 1), 
            ImVec2(1, 0)
        );
        ImGui::EndChild();
    ImGui::End();

    Renderer::ResetStats();
}


void EditorState::DockspaceAndMenu()
{
    static bool dockspaceOpen = true;
    static bool optFullscreen = true;
    static bool optPadding = false;

    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        windowFlags |= ImGuiWindowFlags_NoBackground;

    if (!optPadding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
    if (!optPadding)
        ImGui::PopStyleVar();

    if (optFullscreen)
        ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))   
        {
            ImGui::MenuItem("File");
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}
