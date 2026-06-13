# Learning Effective Modern C++ (C++20)

Effective Modern C++ の学習用サンプルコード集です。

このリポジトリは、以下の書籍の内容を参考に作成しています。

- 題名: Effective Modern C++ - C++11/14 プログラムを進化させる 42 項目
- 著者: Scott Meyers
- 出版社: 株式会社オライリー・ジャパン
- ISBN: 978-4-87311-736-2

現在は、Mac と Windows の両方で動作する最小の C++20 ウィンドウアプリと、各 Item ごとのコンソールサンプル用ファイルを含みます。

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

指定した Item のサンプルを実行:

```bash
sh scripts/run_item.sh 2
```

## Windows でのビルドと実行

Visual Studio 2022 など、C++開発環境が入ったターミナルでプロジェクトルートから実行:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\HelloWindow.exe
```

指定した Item のサンプルを実行:

```powershell
cmake -S . -B build
cmake --build build --target Item02 --config Release
.\build\Release\Item02.exe
```

## ソース構成

- `src/main.cpp` : 共通エントリポイント
- `src/main_windows.cpp` : Windows (Win32 API)
- `src/main_macos.mm` : macOS (Cocoa)
- `src/itemNN_*.cpp` : 各 Item の解説コード
- `scripts/run_item.sh` : Item 番号を指定してサンプルをビルド・実行するスクリプト
- `CMakeLists.txt` : OSごとのビルド設定
