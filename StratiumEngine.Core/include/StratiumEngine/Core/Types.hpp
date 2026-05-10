#pragma once

#include <cstdint>
#include <cstddef>

namespace Stratium {

    // ============================================================================
    // Integer Types - Sabit Boyutlu Tam Sayılar (Fixed-Size Integer Types)
    // ============================================================================

    // İşaretsiz tam sayılar (Unsigned integers)
    using u8  = std::uint8_t;      // 8-bit  (0 - 255)
    using u16 = std::uint16_t;     // 16-bit (0 - 65535)
    using u32 = std::uint32_t;     // 32-bit (0 - 4294967295)
    using u64 = std::uint64_t;     // 64-bit

    // İşaretli tam sayılar (Signed integers)
    using i8  = std::int8_t;       // 8-bit  (-128 - 127)
    using i16 = std::int16_t;      // 16-bit (-32768 - 32767)
    using i32 = std::int32_t;      // 32-bit (-2147483648 - 2147483647)
    using i64 = std::int64_t;      // 64-bit

    // ============================================================================
    // Floating Point Types - Kayan Noktalı Sayılar
    // ============================================================================

    using f32 = float;             // 32-bit (single precision)
    using f64 = double;            // 64-bit (double precision)

    // ============================================================================
    // Boolean Type - Mantıksal Değer
    // ============================================================================

    using b8  = bool;

    // ============================================================================
    // Size and Pointer Types - Boyut ve İşaretçi Tipleri
    // ============================================================================

    using usize = std::size_t;     // Platform bağımlı boyut (64-bit veya 32-bit)
    using isize = std::ptrdiff_t;  // Platform bağımlı işaretçi farkı

    // ============================================================================
    // Special Type Aliases - Özel Tür Takmaları
    // ============================================================================

    // Eğer bir değeri belirtilmemiş olarak işaretlemek istiyorsak
    struct None {};

    // Entity ID ve Handle tiplerinin base'i
    using EntityID = u32;
    using ComponentID = u32;
    using SystemID = u32;

} // namespace Stratium
