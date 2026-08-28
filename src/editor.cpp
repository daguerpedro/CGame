#include "editor.h"
#include "entity.h"

#ifdef DEBUG
void Editor::draw()
{
    inspectorWindow();
    statsWindow();

    Logger::Draw();
}

void Editor::inspectorWindow()
{
    if (ImGui::Begin("Inspetor"))
    {
        entityList();
        activeScene();
        sceneList();
        changeScene();
    }
    ImGui::End();
};

void Editor::activeScene()
{
    if (sceneManger.hasActiveScene())
        ImGui::Text("Scene: %s", sceneManger.getActiveSceneName().c_str());
    else
        ImGui::TextColored({1, 0, 0, 1}, "No scene loaded.");

    ImGui::Separator();
};

void Editor::sceneList()
{
    ImGui::Spacing();
    ImGui::SetNextItemWidth(-1);
    if (ImGui::BeginListBox("##Scene Registry"))
    {
        for (const auto &[sceneName, constructor] : sceneManger.getRegisteredScenes())
        {
            bool is_selected = (m_selectedSceneName == sceneName);
            if (ImGui::Selectable(sceneName.c_str(), is_selected))
                m_selectedSceneName = sceneName;

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
};

void Editor::changeScene()
{
    ImGui::BeginDisabled(m_selectedSceneName.empty());
    if (ImGui::Button("Trocar Cena"))
    {
        if (!m_selectedSceneName.empty())
            sceneManger.changeScene(m_selectedSceneName);
    }
    ImGui::EndDisabled();
};

void Editor::statsWindow()
{
    // Code by ImGuiDemoTools :D
    if (refresh_time == 0.0)
    {
        refresh_time = ImGui::GetTime();
    }

    while (refresh_time < ImGui::GetTime())
    {
        values[values_offset] = GetFrameTime();
        values_offset = (values_offset + 1) % IM_COUNTOF(values);
        refresh_time += 1.0f / 60.0f;

        auto actualMax = (*std::max_element(values, values + values_offset));
        if (max < actualMax)
        {
            max = actualMax;
        }
    }

    if (ImGui::Begin("Stats"))
    {
        float average = 0.0f;
        for (int n = 0; n < IM_COUNTOF(values); n++)
            average += values[n];
        average /= (float)IM_COUNTOF(values);
        char overlay[32];

        ImGui::Text("FPS: %1.f (%1.f)", 1.0 / GetFrameTime(), 1.0 / average);
        ImGui::Text("Frame Time: %.4f (ms)", average * 1000);

        ImGui::SetNextItemWidth(-1);
        ImGui::PlotLines("##ftime", values, IM_COUNTOF(values), values_offset, NULL, 0, max, ImVec2(0, 80.0f));
    }
    ImGui::End();
}

void Editor::entityList()
{
    ImGui::Spacing();

    if (sceneManger.hasActiveScene())
    {
        auto &reg = sceneManger.activeScene()->sceneRegistry;

        ImGui::Text("Entidades:");
        ImGui::Separator();

        for (auto entity : reg.storage<entt::entity>())
        {
            uint32_t entityID = static_cast<uint32_t>(entity);

            if (ImGui::TreeNode((void *)(intptr_t)entity, "Entidade #%01d", entityID))
            {
                if (auto *pos = reg.try_get<Position>(entity))
                {
                    if (ImGui::TreeNode("Position"))
                    {
                        ImGui::DragFloat("X", &pos->x, 1.0f);
                        ImGui::DragFloat("Y", &pos->y, 1.0f);
                        ImGui::TreePop();
                    }
                }

                if (auto *vel = reg.try_get<Velocity>(entity))
                {
                    if (ImGui::TreeNode("Velocity"))
                    {
                        ImGui::DragFloat("vX", &vel->x, 1.0f);
                        ImGui::DragFloat("vY", &vel->y, 1.0f);
                        ImGui::TreePop();
                    }
                }

                if (auto *ren = reg.try_get<Renderable>(entity))
                {
                    if (ImGui::TreeNode("Renderable"))
                    {
                        ImGui::Text("Size");
                        ImGui::DragFloat2("##Size", &ren->size.x, 1.0f);
                        ImGui::Text("Rotation");
                        ImGui::DragFloat("##Rotation", &ren->rotation);
                        ImGui::Text("Scale");
                        ImGui::DragFloat("##Scale", &ren->scale);

                        float col[4] = {
                            ren->color.r / 255.f, 
                            ren->color.g / 255.f, 
                            ren->color.b / 255.f, 
                            ren->color.a / 255.f
                        };

                        ImGui::Text("Color");
                        ImGui::ColorEdit4("##Color", col);
                        ren->color = {
                            (unsigned char)(col[0] * 255), 
                            (unsigned char)(col[1] * 255), 
                            (unsigned char)(col[2] * 255), 
                            (unsigned char)(col[3] * 255)
                        };
                        ImGui::TreePop();
                    }
                }

                // Fecha o nó desta entidade
                ImGui::TreePop();
            }
        }
    }
}

#endif