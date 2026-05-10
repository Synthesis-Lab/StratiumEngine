#pragma once

#include "StratiumEngine/Core/Types.hpp"
#include <vector>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <functional>

namespace Stratium {

    struct Component {
        virtual ~Component() = default;
        virtual const char* GetType() const = 0;
    };

    template<typename T>
    struct TypedComponent : public Component {
        const char* GetType() const override {
            return typeid(T).name();
        }
    };

    class Entity {
    public:
        explicit Entity(EntityID id) : m_id(id) {}

        EntityID GetID() const { return m_id; }

        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            const char* type_name = typeid(T).name();
            if (m_components.find(type_name) != m_components.end()) {
                return nullptr;
            }
            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            m_components[type_name] = component;
            return component.get();
        }

        template<typename T>
        T* GetComponent() {
            const char* type_name = typeid(T).name();
            auto it = m_components.find(type_name);
            if (it == m_components.end()) return nullptr;
            return static_cast<T*>(it->second.get());
        }

        template<typename T>
        bool HasComponent() const {
            return m_components.find(typeid(T).name()) != m_components.end();
        }

        template<typename T>
        void RemoveComponent() {
            m_components.erase(typeid(T).name());
        }

        u32 GetComponentCount() const { return static_cast<u32>(m_components.size()); }

    private:
        EntityID m_id;
        std::unordered_map<std::string, std::shared_ptr<Component>> m_components;
    };

    class System {
    public:
        virtual ~System() = default;
        virtual void Update(float delta_time) = 0;
    };

    class Registry {
    public:
        Registry() : m_next_entity_id(0) {}

        Entity* CreateEntity() {
            EntityID id = m_next_entity_id++;
            auto entity = std::make_shared<Entity>(id);
            m_entities[id] = entity;
            return entity.get();
        }

        void DestroyEntity(EntityID id) {
            m_entities.erase(id);
        }

        Entity* GetEntity(EntityID id) {
            auto it = m_entities.find(id);
            if (it == m_entities.end()) return nullptr;
            return it->second.get();
        }

        template<typename T>
        T* RegisterSystem() {
            auto system = std::make_shared<T>();
            m_systems.push_back(system);
            return system.get();
        }

        void Update(float delta_time) {
            for (auto& system : m_systems) {
                system->Update(delta_time);
            }
        }

        u32 GetEntityCount() const { return static_cast<u32>(m_entities.size()); }
        u32 GetSystemCount() const { return static_cast<u32>(m_systems.size()); }

    private:
        std::unordered_map<EntityID, std::shared_ptr<Entity>> m_entities;
        std::vector<std::shared_ptr<System>> m_systems;
        EntityID m_next_entity_id;
    };

} // namespace Stratium
