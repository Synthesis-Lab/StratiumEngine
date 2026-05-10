#pragma once

#include "StratiumEngine/Core/Types.hpp"
#include <cstdlib>
#include <memory>

namespace Stratium {

    struct MemoryStats {
        u64 allocated_bytes = 0;
        u64 freed_bytes = 0;
        u64 peak_bytes = 0;
        u32 allocation_count = 0;
        u32 deallocation_count = 0;

        u64 GetCurrentUsage() const { return allocated_bytes - freed_bytes; }
    };

    class LinearAllocator {
    public:
        explicit LinearAllocator(u64 size);
        ~LinearAllocator();

        void* Allocate(u64 size);
        void Clear();

        u64 GetCapacity() const { return m_capacity; }
        u64 GetUsed() const { return m_used; }
        u64 GetRemaining() const { return m_capacity - m_used; }

    private:
        u8* m_buffer = nullptr;
        u64 m_capacity = 0;
        u64 m_used = 0;
    };

    class PoolAllocator {
    public:
        explicit PoolAllocator(u64 element_size, u32 element_count);
        ~PoolAllocator();

        void* Allocate();
        void Free(void* ptr);

        u32 GetCapacity() const { return m_element_count; }
        u32 GetUsed() const { return m_used_count; }
        u32 GetAvailable() const { return m_element_count - m_used_count; }

    private:
        struct FreeNode {
            FreeNode* next;
        };

        u8* m_buffer = nullptr;
        FreeNode* m_free_list = nullptr;
        u64 m_element_size = 0;
        u32 m_element_count = 0;
        u32 m_used_count = 0;
    };

    class MemoryManager {
    public:
        static MemoryManager& Get();

        void Init(u64 linear_size, u64 pool_size, u32 pool_element_size);
        void Shutdown();

        void* AllocateLinear(u64 size);
        void* AllocateFromPool();
        void FreeFromPool(void* ptr);
        void ClearLinearAllocator();

        MemoryStats GetStats() const { return m_stats; }
        void PrintStats() const;

    private:
        MemoryManager() = default;

        static MemoryManager* s_instance;
        std::unique_ptr<LinearAllocator> m_linear_allocator;
        std::unique_ptr<PoolAllocator> m_pool_allocator;
        MemoryStats m_stats;
    };

} // namespace Stratium
