#include "editor.h"
#include "components.h"

#ifdef DEBUG

namespace Engine
{
    static ImVec4 ColorToImGui(Color &col)
    {
        return ImVec4{
            col.r / 255.0f,
            col.g / 255.0f,
            col.b / 255.0f,
            col.a / 255.0f};
    }

    static Color ColorToRay(ImVec4 &col)
    {
        return Color{
            static_cast<unsigned char>(col.x * 255.f),
            static_cast<unsigned char>(col.y * 255.f),
            static_cast<unsigned char>(col.z * 255.f),
            static_cast<unsigned char>(col.w * 255.f),
        };
    }

    static void ColorEdit(Color &col, const char *label)
    {
        auto fcol = ColorToImGui(col);
        if (ImGui::ColorEdit4(label, &fcol.x))
            col = ColorToRay(fcol);
    }

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
        if (sceneManager.hasActiveScene())
        {
            ImGui::Text("Scene: %s", sceneManager.getActiveSceneName().c_str());
            auto &col = sceneManager.activeScene()->backgroundColor;
            ColorEdit(col, "##backcol");
        }
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
            for (const auto &[sceneName, constructor] : sceneManager.getRegisteredScenes())
            {
                if (m_selectedSceneName.empty())
                    m_selectedSceneName = sceneName;

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
                sceneManager.changeScene(m_selectedSceneName);
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
        if (sceneManager.hasActiveScene())
        {
            auto &reg = sceneManager.activeScene()->registry;
            ImGui::Text("Entidades:");
            ImGui::Separator();

            for (auto entity : reg.storage<entt::entity>())
            {
                uint32_t entityID = static_cast<uint32_t>(entity);
                std::string nodeName = "Entidade " + std::to_string(entityID);
                if (auto *tag = reg.try_get<TagComponent>(entity))
                    nodeName = tag->name + " (ID: " + std::to_string(entityID) + ")";

                if (ImGui::TreeNode((void *)(intptr_t)entity, "%s", nodeName.c_str()))
                {
                    if (auto *trans = reg.try_get<TransformComponent>(entity))
                    {
                        if (ImGui::TreeNode("Transform"))
                        {
                            ImGui::DragFloat2("Position", &trans->position.x, 1.0f);
                            ImGui::DragFloat2("Scale", &trans->scale.x);
                            ImGui::DragFloat("Rotation", &trans->rotation, 1.0f, 0.0f, 360.0f);

                            ImGui::TreePop();
                        }
                    }

                    if (auto *rec = reg.try_get<RectangleComponent>(entity))
                    {
                        if (ImGui::TreeNode("Rectangle"))
                        {
                            ImGui::DragFloat2("Size", &rec->size.x, 1.0f);
                            ColorEdit(rec->color, "Color");
                            ImGui::TreePop();
                        }
                    }

                    if (auto *body = reg.try_get<BodyComponent>(entity))
                    {
                        if (ImGui::TreeNode("Body"))
                        {
                            ImGui::DragFloat2("Velocity", &body->velocity.x, 1.0f);
                            ImGui::TreePop();
                        }
                    }

                    ImGui::TreePop();
                }
            }
        }
    }

};
#endif