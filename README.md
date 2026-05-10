# StratiumEngine

Stratium Engine, modern C++23 ile geliştirilen, modüler ve küçük boyutlu bir 3D oyun motorudur. Başlangıçta strateji oyunları için optimize edilmiştir, ancak mimarisi sayesinde RPG ve diğer türlere de kolayca genişletilebilir.

## Temel Özellikler
- **C++23** ile yazılmıştır, modern donanım ve çoklu platform desteği hedeflenir.
- **Modüler mimari:** Çekirdek, render, fizik, ses, input ve scripting gibi sistemler bağımsız modüller olarak tasarlanır.
- **DOD + OOP Hibrit:** Performans kritik sistemlerde veri odaklı, üst düzeyde ise nesne yönelimli yaklaşım.
- **Scripting:** Geliştirme sürecinde Lua desteği, ileride optimize DSL desteği.
- **Platformlar:** Öncelikli olarak masaüstü (Windows, Linux), ileride mobil ve web desteği.
- **Küçük ve öğrenmesi kolay:** Geliştiriciler için hızlı öğrenim ve entegrasyon.

## Kurulum

1. **Gereksinimler:**
   - CMake >= 3.10
   - C++23 destekli derleyici (MSVC, Clang, GCC)
   - Ninja (önerilir)
2. **Projeyi klonlayın:**
   ```sh
   git clone https://github.com/Synthesis-Lab/StratiumEngine.git
   ```
3. **Derleyin:**
   ```sh
   cmake -S . -B build -G Ninja
   cmake --build build
   ```

## Katkı
Katkıda bulunmak için lütfen bir issue açın veya pull request gönderin.

## Lisans
MIT Lisansı (LICENSE.txt dosyasına bakınız)
