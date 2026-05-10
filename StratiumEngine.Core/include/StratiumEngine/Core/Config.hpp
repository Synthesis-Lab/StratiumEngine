#pragma once

// ============================================================================
// StratiumEngine Configuration Header
// Motorun derleme zamanı yapılandırma ayarları
// ============================================================================

namespace Stratium {

    // ============================================================================
    // Engine Version Information - Motor Versiyon Bilgisi
    // ============================================================================

    constexpr int ENGINE_VERSION_MAJOR = 0;
    constexpr int ENGINE_VERSION_MINOR = 1;
    constexpr int ENGINE_VERSION_PATCH = 0;

    // ============================================================================
    // Debug Configuration - Hata Ayıklama Yapılandırması
    // ============================================================================

#ifdef STRATIUM_DEBUG
    constexpr bool DEBUG_MODE = true;
#else
    constexpr bool DEBUG_MODE = false;
#endif

    // ============================================================================
    // Platform Detection - Platform Tespit
    // ============================================================================

#ifdef STRATIUM_PLATFORM_WINDOWS
    constexpr bool PLATFORM_WINDOWS = true;
    constexpr bool PLATFORM_LINUX   = false;
    constexpr bool PLATFORM_MACOS   = false;
#elif defined(STRATIUM_PLATFORM_LINUX)
    constexpr bool PLATFORM_WINDOWS = false;
    constexpr bool PLATFORM_LINUX   = true;
    constexpr bool PLATFORM_MACOS   = false;
#elif defined(STRATIUM_PLATFORM_MACOS)
    constexpr bool PLATFORM_WINDOWS = false;
    constexpr bool PLATFORM_LINUX   = false;
    constexpr bool PLATFORM_MACOS   = true;
#else
    #error "Unsupported platform"
#endif

    // ============================================================================
    // Engine Configuration Flags - Motor Yapılandırma Bayrakları
    // ============================================================================

    // Varsayılan oyun döngüsü hedef kare hızı (FPS)
    constexpr float TARGET_FPS = 60.0f;
    constexpr float TARGET_FRAME_TIME = 1.0f / TARGET_FPS; // ~16.67ms

    // Bellek ayırıcısı ayarları
    constexpr bool USE_CUSTOM_ALLOCATORS = true;
    constexpr bool ENABLE_MEMORY_PROFILING = DEBUG_MODE;

    // ECS sistem ayarları
    constexpr int MAX_ENTITIES = 100000;
    constexpr int MAX_COMPONENTS = 256;

    // ============================================================================
    // Feature Flags - Özellik Bayrakları
    // ============================================================================

    // Strateji oyunu özellikleri
    constexpr bool ENABLE_TURN_SYSTEM = true;
    constexpr bool ENABLE_FOG_OF_WAR = true;
    constexpr bool ENABLE_PATHFINDING = true;
    constexpr bool ENABLE_AI = true;

    // Grafik özellikleri
    constexpr bool ENABLE_GRAPHICS = false;  // Henüz yapılmadı
    constexpr bool ENABLE_PHYSICS = false;   // Strateji oyunları için isteğe bağlı

    // Ağ özellikleri
    constexpr bool ENABLE_NETWORKING = false; // Gelecek: Çok oyuncu desteği
    constexpr bool ENABLE_SCRIPTING = false;  // Gelecek: Lua/DSL desteği

} // namespace Stratium
