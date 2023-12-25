#include "Scene.hpp"
#include "Entity.hpp"
#include "General/Transform.hpp"
#include "2D/Sprite.hpp"
#include "2D/TileMap.hpp"
#include "3D/Model.hpp"
#include "3D/Material.hpp"
#include "General/Identifier.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>

#include "Systems/StandartSystems.hpp"

namespace Rvl
{
    static int entityNum = 0;

    Scene::Scene() 
    {
        AddSystem(TransformSystem);
        AddSystem(Movement2DSystem);
        AddSystem(Animation2DSystem);
        AddSystem(MaterialSystem);
        AddSystem(LightSystem);
        AddSystem(ModelLoaderSystem);
    }

    Scene::~Scene() {}
    
    Entity Scene::NewEntity()
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>("Entity" + std::to_string(entityNum));
        entity.Add<Transform>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        _entitiesData.emplace(entity, EntityData());
        return entity;
    }

    Entity Scene::NewEntity(const glm::vec3& position)
    {
       Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>("Entity" + std::to_string(entityNum));
        entity.Add<Transform>(position, glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        _entitiesData.emplace(entity, EntityData());
        return entity;
    }

    Entity Scene::NewEntity(const std::string& name)
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>(name);
        entity.Add<Transform>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        _entitiesData.emplace(entity, EntityData());
        return entity;
    }

    Entity Scene::NewEntity(const std::string& name, const glm::vec3& position)
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>(name);
        entity.Add<Transform>(position, glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        _entitiesData.emplace(entity, EntityData());
        return entity;
    }

    void Scene::RemoveEntity(Entity entity)
    {
        _entities.erase(std::remove(_entities.begin(), _entities.end(), entity));
        _entitiesData.erase(entity);
        _registry.destroy(entity.GetId());
    }

    void Scene::AddSystem(const System& system)
    {
        _systems.push_back(system);
    }
    
    void Scene::AddBehaviour(Behaviour* behaviour)
    {
        _behaviours.push_back(behaviour);
    }

    void Scene::StartBehaviours()
    {
        for (auto behaviour : _behaviours)
        {
            behaviour->Start();
        }
    }
    
    void Scene::UpdateBehaviours()
    {
        for (auto behaviour : _behaviours)
        {
            behaviour->Update();
        }

        for (auto system : _systems)
        {
            system(_entities);
        }
    }
    
    void Scene::OnEvent(Event* event)
    {
        for (auto behaviour : _behaviours)
        {
            behaviour->OnEvent(event);
        }
    }
    
    std::vector<Entity> Scene::GetEntities() const
    {
        return _entities;
    }

    EntityData& Scene::GetEntityData(Entity entity)
    {
        return _entitiesData[entity];
    }

    void Scene::AddChild(Entity parent, Entity child)
    {
        _entitiesData[parent].Children.push_back(child);
    }

    std::size_t EntityHasher::operator()(const Entity& k) const
    {
        return (std::hash<uint32>()(k.GetIdInt()));
    }

}
