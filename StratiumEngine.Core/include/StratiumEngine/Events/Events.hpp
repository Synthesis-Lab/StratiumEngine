#pragma once

#include "StratiumEngine/Core/Types.hpp"
#include <functional>
#include <vector>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <any>

namespace Stratium {

    // ============================================================================
    // Event Base Class
    // ============================================================================

    struct Event {
        virtual ~Event() = default;
        virtual const char* GetType() const = 0;
    };

    // ============================================================================
    // Typed Event Template
    // ============================================================================

    template<typename T>
    struct TypedEvent : public Event {
        const char* GetType() const override {
            static const std::type_info& type = typeid(T);
            return type.name();
        }
        T data;
    };

    // ============================================================================
    // Event Callback
    // ============================================================================

    using EventCallback = std::function<void(const Event&)>;

    // ============================================================================
    // Event Dispatcher (Observer Pattern / Pub-Sub)
    // ============================================================================

    class EventDispatcher {
    public:
        // Subscribe to event type
        template<typename T>
        void Subscribe(EventCallback callback) {
            const char* event_type = typeid(T).name();
            m_subscribers[event_type].push_back(callback);
        }

        // Publish event
        void Publish(const Event& event) {
            const char* event_type = event.GetType();
            auto it = m_subscribers.find(event_type);
            if (it != m_subscribers.end()) {
                for (auto& callback : it->second) {
                    callback(event);
                }
            }
        }

        // Clear all subscriptions
        void Clear() {
            m_subscribers.clear();
        }

        // Subscriber count
        u32 GetSubscriberCount(const char* event_type) const {
            auto it = m_subscribers.find(event_type);
            return it != m_subscribers.end() ? static_cast<u32>(it->second.size()) : 0;
        }

    private:
        std::unordered_map<std::string, std::vector<EventCallback>> m_subscribers;
    };

    // ============================================================================
    // Event Queue (Asynchronous Event Processing)
    // ============================================================================

    class EventQueue {
    public:
        // Enqueue event
        void Enqueue(std::shared_ptr<Event> event) {
            m_queue.push_back(event);
        }

        // Process all queued events
        void Process(EventDispatcher& dispatcher) {
            for (auto& event : m_queue) {
                dispatcher.Publish(*event);
            }
            m_queue.clear();
        }

        // Get queue size
        u32 GetSize() const { return static_cast<u32>(m_queue.size()); }

        // Clear queue
        void Clear() { m_queue.clear(); }

    private:
        std::vector<std::shared_ptr<Event>> m_queue;
    };

} // namespace Stratium
