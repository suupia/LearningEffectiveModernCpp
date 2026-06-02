# HelloWindow (C++20)

Mac と Windows の両方で動作する、最小の C++20 ウィンドウアプリです。
ウィンドウ中央に `Hello World` を表示します。

## 必要環境

- CMake 3.20 以上
- C++20 対応コンパイラ
  - macOS: AppleClang (Xcode Command Line Tools)
  - Windows: Visual Studio 2022 など (MSVC)

## ビルド手順

プロジェクトルートで実行:

```bash
cmake -S . -B build
cmake --build build -j
```

## 実行方法

### macOS

```bash
./build/HelloWindow
```

### Windows

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\HelloWindow.exe
```

## ソース構成

- `src/main.cpp` : 共通エントリポイント
- `src/main_windows.cpp` : Windows (Win32 API)
- `src/main_macos.mm` : macOS (Cocoa)
- `CMakeLists.txt` : OSごとのビルド設定
