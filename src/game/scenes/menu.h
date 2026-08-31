#include <engine.h>

using namespace Engine;

//RELEASE: 50k Atualizações: 130fps.
//DEBUG: 5k Atualizalções: 80fps.
#define ENEMIES 50000
// TEMP
class Menu : public Scene
{
private:
    Entity player;

public:
    Menu() : Scene("Menu")
    {
    }

    void start() override
    {
        player = createEntity();
        player.addComponent<TagComponent>("Player");
        player.getComponent<TransformComponent>().position = {50, 50};
        player.addComponent<RectangleComponent>(Vector2{15, 15}, Color{0, 0, 255, 255});
        player.addComponent<BodyComponent>().velocity = {100, 100};

        for (int i = 0; i < ENEMIES; i++)
        {
            auto eny = createEntity();
            eny.addComponent<TagComponent>("Enemy");

            auto &trans = eny.getComponent<TransformComponent>();

            trans.position = Vector2{
                Random::Range<float>(0, sceneManager->getViewWidth()),
                Random::Range<float>(0, sceneManager->getViewHeight())};

            eny.addComponent<RectangleComponent>(Vector2{15, 15}, Color{255, 0, 0, 255});

            float s = Random::Range<float>(0.1, 1.5);
            trans.scale = Vector2{s, s};
            trans.rotation = Random::Range<float>(0, 360);

            float dir = Random::Range<float>(0, 1) == 0 ? 1 : -1;
            float vel = Random::Range<float>(10, 500);
            eny.addComponent<BodyComponent>().velocity = {
                vel * dir, vel * dir};
        }
    }

    void stop() override
    {
    }

    //TEMP: MOVER PARA ENGINE DE FISICAS
    void update(float deltaTime) override
    {
        auto view = registry.view<TransformComponent, BodyComponent, RectangleComponent>();
        auto vw = sceneManager->getViewWidth();
        auto vh= sceneManager->getViewHeight();

        for (auto &&[entity, trans, body, rec] : view.each())
        {
            auto &pos = trans.position;
            auto &vel = body.velocity;

            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;

            if (pos.x < 0)
            {
                vel.x = -vel.x;
                pos.x = 0;
            }
            else if (pos.x > vw - rec.size.x)
            {
                vel.x = -vel.x;
                pos.x = vw - rec.size.x;
            }

            if (pos.y < 0)
            {
                vel.y = -vel.y;
                pos.y = 0;
            }
            else if (pos.y > vh - rec.size.y)
            {
                vel.y = -vel.y;
                pos.y = vh - rec.size.y;
            }
        }
    }
};