#pragma once

#include "engine.h"

namespace Engine
{
    class Renderer
    {
    public:
        Renderer() = default;

    private:
        friend class App;

        void requestDraw(SceneManager &sm)
        {
            if (sm.hasActiveScene() == false)
                return;

            auto &registry = sm.activeScene()->registry;
            
            ClearBackground(sm.activeScene()->backgroundColor);

            auto rectView = registry.view<TransformComponent, RectangleComponent>();
            for (auto ent : rectView)
            {
                auto [transform, rect] = rectView.get<TransformComponent, RectangleComponent>(ent);
                
                float fw = rect.size.x * transform.scale.x;
                float fh = rect.size.y * transform.scale.y;

                Rectangle destRect = {transform.position.x, transform.position.y, fw, fh};
                Vector2 origin = {fw / 2.0f, fh / 2.0f}; 

                DrawRectanglePro(destRect, origin, transform.rotation, rect.color);
            }
        };
    };
};