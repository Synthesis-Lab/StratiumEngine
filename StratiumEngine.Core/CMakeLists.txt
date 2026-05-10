# StratiumEngine.Core için CMake projesi

# Kaynak ve başlık dosyalarını otomatik ekle
file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "include/*.h" "include/*.hpp")

add_library(StratiumEngine.Core STATIC
    ${CORE_SOURCES}
    ${CORE_HEADERS}
)

# Public include dizini
target_include_directories(StratiumEngine.Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StratiumEngine
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(StratiumEngine.Core PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
)

# Platformlara özel makrolar
if(WIN32)
    target_compile_definitions(StratiumEngine.Core PUBLIC STRATIUM_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(StratiumEngine.Core PUBLIC STRATIUM_PLATFORM_LINUX)
endif()

# Gerekirse bağımlılıklar ve tanımlar ekleyin
