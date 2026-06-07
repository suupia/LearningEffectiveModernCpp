#!/bin/bash

# 以下のようにして、引数でファイル名を指定できるのですが、
# 引数がない場合はデフォルトで "a.cpp" を使用します。
# ~/LearningEffectiveModernCpp$ ./scripts/run_hase_decltype.sh ファイル名.cpp


TARGET_DIR="./hase/decltype"
FILE_NAME="${1:-a.cpp}"
TARGET_PATH="$TARGET_DIR/$FILE_NAME"

if [ ! -f "$TARGET_PATH" ]; then
    echo "エラー: ファイル '$TARGET_PATH' が見つかりません。"
    exit 1
fi

echo "========================================"
echo "ターゲット: $TARGET_PATH"
echo "========================================"

cd "$TARGET_DIR" || exit 1

g++ -std=c++17 -Wall -Wextra "$FILE_NAME"

if [ $? -eq 0 ]; then
    echo "--- 実行結果 ---"
    ./a.out
    echo "---------------"
    rm ./a.out
else
    echo "[エラー] コンパイルに失敗したため、実行を中止しました。"
    exit 1
fi
