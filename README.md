# HelloWindow (C++20)

Mac と Windows の両方で動作する、最小の C++20 ウィンドウアプリです。
ウィンドウ中央に `Hello World` を表示します。

## 必要環境

- CMake 3.20 以上
- C++20 対応コンパイラ
  - macOS: AppleClang (Xcode Command Line Tools)
  - Windows: Visual Studio 2022 など (MSVC)

## macOS でのビルドと実行

プロジェクトルートで実行:

```bash
cmake -S . -B build
cmake --build build -j
./build/HelloWindow
```

## Windows でのビルドと実行

Visual Studio 2022 など、C++開発環境が入ったターミナルでプロジェクトルートから実行:

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
