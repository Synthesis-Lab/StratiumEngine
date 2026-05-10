#include "StratiumEngine/Memory/Memory.hpp"
#include "StratiumEngine/Logging/Logging.hpp"
#include <cstring>
#include <iomanip>

namespace Stratium {

    // ============================================================================
    // LinearAllocator Implementation
    // ============================================================================

    LinearAllocator::LinearAllocator(u64 size) : m_capacity(size) {
        m_buffer = static_cast<u8*>(malloc(size));
        if (!m_buffer) {
            STRATIUM_LOG_ERROR("Failed to allocate linear allocator buffer ({} bytes)", size);
        }
    }

    LinearAllocator::~LinearAllocator() {
        if (m_buffer) {
            free(m_buffer);
            m_buffer = nullptr;
        }
    }

    void* LinearAllocator::Allocate(u64 size) {
        if (m_used + size > m_capacity) {
            STRATIUM_LOG_WARN("LinearAllocator overflow! Used: {} + Size: {} > Capacity: {}", m_used, size, m_capacity);
            return nullptr;
        }

        void* ptr = m_buffer + m_used;
        m_used += size;
        return ptr;
    }

    void LinearAllocator::Clear() {
        m_used = 0;
    }

    // ============================================================================
    // PoolAllocator Implementation
    // ============================================================================

    PoolAllocator::PoolAllocator(u64 element_size, u32 element_count)
        : m_element_size(element_size), m_element_count(element_count) {

        m_buffer = static_cast<u8*>(malloc(element_size * element_count));
        if (!m_buffer) {
            STRATIUM_LOG_ERROR("Failed to allocate pool allocator buffer");
            return;
        }

        // Başlangıçta tüm elemanlar free
        m_free_list = nullptr;
        for (u32 i = element_count; i > 0; --i) {
            FreeNode* node = reinterpret_cast<FreeNode*>(m_buffer + (i - 1) * element_size);
            node->next = m_free_list;
            m_free_list = node;
        }
    }

    PoolAllocator::~PoolAllocator() {
        if (m_buffer) {
            free(m_buffer);
            m_buffer = nullptr;
        }
    }

    void* PoolAllocator::Allocate() {
        if (!m_free_list) {
            STRATIUM_LOG_WARN("PoolAllocator is full!");
            return nullptr;
        }

        FreeNode* node = m_free_list;
        m_free_list = node->next;
        m_used_count++;

        return node;
    }

    void PoolAllocator::Free(void* ptr) {
        if (!ptr) return;

        FreeNode* node = reinterpret_cast<FreeNode*>(ptr);
        node->next = m_free_list;
        m_free_list = node;
        m_used_count--;
    }

    // ============================================================================
    // MemoryManager Implementation
    // ============================================================================

    MemoryManager* MemoryManager::s_instance = nullptr;

    MemoryManager& MemoryManager::Get() {
        if (!s_instance) {
            s_instance = new MemoryManager();
        }
        return *s_instance;
    }

    void MemoryManager::Init(u64 linear_size, u64 pool_size, u32 pool_element_size) {
        m_linear_allocator = std::make_unique<LinearAllocator>(linear_size);
        m_pool_allocator = std::make_unique<PoolAllocator>(pool_element_size, static_cast<u32>(pool_size / pool_element_size));

        STRATIUM_LOG_INFO("MemoryManager initialized");
        STRATIUM_LOG_INFO("  Linear: {} MB", linear_size / (1024 * 1024));
        STRATIUM_LOG_INFO("  Pool: {} elements x {} bytes", pool_size / pool_element_size, pool_element_size);
    }

    void MemoryManager::Shutdown() {
        m_linear_allocator.reset();
        m_pool_allocator.reset();
        STRATIUM_LOG_INFO("MemoryManager shutdown");
    }

    void* MemoryManager::AllocateLinear(u64 size) {
        void* ptr = m_linear_allocator->Allocate(size);
        if (ptr) {
            m_stats.allocated_bytes += size;
            m_stats.allocation_count++;
            m_stats.peak_bytes = std::max(m_stats.peak_bytes, m_stats.allocated_bytes - m_stats.freed_bytes);
        }
        return ptr;
    }

    void* MemoryManager::AllocateFromPool() {
        void* ptr = m_pool_allocator->Allocate();
        if (ptr) {
            m_stats.allocated_bytes += m_pool_allocator->GetCapacity() > 0 ? 1 : 0;
            m_stats.allocation_count++;
        }
        return ptr;
    }

    void MemoryManager::FreeFromPool(void* ptr) {
        m_pool_allocator->Free(ptr);
        m_stats.freed_bytes += m_pool_allocator->GetCapacity() > 0 ? 1 : 0;
        m_stats.deallocation_count++;
    }

    void MemoryManager::ClearLinearAllocator() {
        m_linear_allocator->Clear();
        m_stats.freed_bytes = m_stats.allocated_bytes;
    }

    void MemoryManager::PrintStats() const {
        STRATIUM_LOG_INFO("=== Memory Stats ===");
        STRATIUM_LOG_INFO("Allocated: {} MB", m_stats.allocated_bytes / (1024 * 1024));
        STRATIUM_LOG_INFO("Freed: {} MB", m_stats.freed_bytes / (1024 * 1024));
        STRATIUM_LOG_INFO("Current: {} MB", m_stats.GetCurrentUsage() / (1024 * 1024));
        STRATIUM_LOG_INFO("Peak: {} MB", m_stats.peak_bytes / (1024 * 1024));
        STRATIUM_LOG_INFO("Allocations: {} / Deallocations: {}", m_stats.allocation_count, m_stats.deallocation_count);
    }

} // namespace Stratium
