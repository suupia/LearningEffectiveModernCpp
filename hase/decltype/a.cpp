// Effective Modern C++の項目3、p17~18のサンプルコードを動かせるようにしたもの。
// gccでのみ動作確認済み。（マクロの関係でそれ以外で動作しない可能性大）

#include <iostream>
#include <string_view>
#include <vector>

// decltypeの結果を表示するための関数
template <typename T>
void print_type_impl(std::string_view name) {
    const std::string_view n = __PRETTY_FUNCTION__;
    const std::string_view prefix = "[with T = ";
    const size_t s = n.find(prefix) + prefix.size();
    const size_t e = n.find(';', s);
    std::cout << name << " = " << std::string_view(n.data() + s, e - s) << std::endl;
}

// decltypeの結果を表示するためのマクロ
#define MY_PRINT_DECLTYPE(expr) print_type_impl<expr>(#expr)

// サンプルコードのためのクラス、ｋ構造体、関数
class Widget {};
struct Point { int x, y; };

bool f(const Widget& w) {
    MY_PRINT_DECLTYPE(decltype(w));
    return true;
}

// サンプルコードの実行
int main() {
    std::cout << "[1] const int i = 0; の decltype(i) はそのまま const int になる" << std::endl;
    const int i = 0;
    MY_PRINT_DECLTYPE(decltype(i));
    std::cout << std::endl;

    std::cout << "[2] const Widget& w の場合も、decltype(w) はそのまま const Widget& になる" << std::endl;
    f(Widget{});
    std::cout << "    関数をdecltypeに渡した場合、その関数の型がそのまま得られる" << std::endl;
    MY_PRINT_DECLTYPE(decltype(f));
    std::cout << std::endl;

    std::cout << "[3] クラスのメンバをdecltypeに渡した場合、そのメンバの型がそのまま得られる" << std::endl;
    MY_PRINT_DECLTYPE(decltype(Point::x));
    MY_PRINT_DECLTYPE(decltype(Point::y));
    std::cout << std::endl;

    std::cout << "[4] Widget w; の場合、decltype(w) は Widget になる" << std::endl;
    Widget w;
    MY_PRINT_DECLTYPE(decltype(w));
    std::cout << std::endl;

    std::cout << "[5] decltype(f(w)) のように、関数呼び出しをdecltypeに渡した場合、その関数の戻り値の型が得られる" << std::endl;
    MY_PRINT_DECLTYPE(decltype(f(w)));
    std::cout << std::endl;

    std::cout << "[6] std::vector<int> v; の場合、decltype(v) は std::vector<int> になる" << std::endl;
    std::vector<int> v;
    MY_PRINT_DECLTYPE(decltype(v));
    std::cout << "    decltype(v[0]) は operator[] の戻り値の型、つまり int& になる" << std::endl;
    MY_PRINT_DECLTYPE(decltype(v[0]));
}
