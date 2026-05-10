#pragma once

// ============================================================================
// StratiumEngine.Core - Main Public Header
// Motorun çekirdeğindeki tüm başlıklara erişim noktası
// ============================================================================

#include "Types.hpp"
#include "Config.hpp"

// ============================================================================
// Platform Macros - Platform Makroları
// ============================================================================

// DLL Export/Import için makro (Windows)
#ifdef STRATIUM_PLATFORM_WINDOWS
    #ifdef STRATIUM_CORE_EXPORTS
        #define STRATIUM_API __declspec(dllexport)
    #else
        #define STRATIUM_API __declspec(dllimport)
    #endif
#else
    #define STRATIUM_API
#endif

// Platformlar arası uyumlu dışa aktarım
#define STRATIUM_INLINE inline

// ============================================================================
// Debug Macros - Hata Ayıklama Makroları
// ============================================================================

#ifdef STRATIUM_DEBUG
    #include <cassert>
    #define STRATIUM_ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                assert(false && message); \
            } \
        } while(0)

    #define STRATIUM_STATIC_ASSERT(condition, message) \
        static_assert(condition, message)
#else
    #define STRATIUM_ASSERT(condition, message) ((void)0)
    #define STRATIUM_STATIC_ASSERT(condition, message) ((void)0)
#endif

// ============================================================================
// Scope Guards - Kapsam Koruması (RAII Pattern)
// ============================================================================

// Bellek temizleme için basit bir RAII wrapper
template <typename T, typename Deleter>
class ScopeGuard {
public:
    ScopeGuard(T* resource, Deleter deleter) 
        : m_resource(resource), m_deleter(deleter) {}

    ~ScopeGuard() {
        if (m_resource) {
            m_deleter(m_resource);
        }
    }

    // Move semantiği
    ScopeGuard(ScopeGuard&& other) noexcept 
        : m_resource(other.release()), m_deleter(other.m_deleter) {}

    ScopeGuard& operator=(ScopeGuard&& other) noexcept {
        reset(other.release());
        return *this;
    }

    // Kopyalama yasak
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    T* get() const { return m_resource; }
    T* operator->() const { return m_resource; }
    T& operator*() const { return *m_resource; }

    T* release() {
        T* temp = m_resource;
        m_resource = nullptr;
        return temp;
    }

    void reset(T* resource = nullptr) {
        if (m_resource) {
            m_deleter(m_resource);
        }
        m_resource = resource;
    }

private:
    T* m_resource;
    Deleter m_deleter;
};

// ============================================================================
// Engine Namespace - Motor Ana Namespace
// ============================================================================

namespace Stratium {

    // Forward declarations
    class Engine;
    class Logger;
    class IWindow;
    class InputManager;

} // namespace Stratium
