# Learning Effective Modern C++ (C++20)

Effective Modern C++ の学習用サンプルコード集です。

このリポジトリは、以下の書籍の内容を参考に作成しています。

- 題名: Effective Modern C++ - C++11/14 プログラムを進化させる 42 項目
- 著者: Scott Meyers
- 出版社: 株式会社オライリー・ジャパン
- ISBN: 978-4-87311-736-2

現在は、Mac と Windows の両方で動作する最小の C++20 ウィンドウアプリと、項目2「auto の型推論を理解する」のコンソールサンプルを含みます。

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

項目2のサンプルを実行:

```bash
sh scripts/run_item02_auto.sh
```

## Windows でのビルドと実行

Visual Studio 2022 など、C++開発環境が入ったターミナルでプロジェクトルートから実行:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\HelloWindow.exe
```

項目2のサンプルを実行:

```powershell
cmake -S . -B build
cmake --build build --target Item02AutoTypeDeduction --config Release
.\build\Release\Item02AutoTypeDeduction.exe
```

## ソース構成

- `src/main.cpp` : 共通エントリポイント
- `src/main_windows.cpp` : Windows (Win32 API)
- `src/main_macos.mm` : macOS (Cocoa)
- `src/item02_auto_type_deduction.cpp` : 項目2「auto の型推論を理解する」の解説コード
- `scripts/run_item02_auto.sh` : 項目2サンプルのビルド・実行スクリプト
- `CMakeLists.txt` : OSごとのビルド設定
