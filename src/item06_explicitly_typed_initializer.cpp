#include <array>
#include <cstddef>
#include <iostream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

struct Widget {};

std::vector<bool> features(const Widget&) {
  return {false, true, false, true, false, true};
}

void processWidget(const Widget&, bool highPriority) {
  std::cout << "processWidget priority: "
            << (highPriority ? "high" : "normal") << '\n';
}

template <typename T>
void printIsBool(std::string_view name) {
  std::cout << name << " is bool: "
            << (std::is_same_v<T, bool> ? "true" : "false") << '\n';
}

class Matrix {
 public:
  Matrix(double a, double b, double c, double d) : values_{a, b, c, d} {}

  double operator[](std::size_t index) const {
    return values_[index];
  }

  void print(std::string_view name) const {
    std::cout << name << " = [";
    for (std::size_t i = 0; i < values_.size(); ++i) {
      if (i != 0) {
        std::cout << ", ";
      }
      std::cout << values_[i];
    }
    std::cout << "]\n";
  }

 private:
  std::array<double, 4> values_;
};

template <typename T>
void printIsMatrix(std::string_view name) {
  std::cout << name << " is Matrix: "
            << (std::is_same_v<T, Matrix> ? "true" : "false") << '\n';
}

template <typename Lhs, typename Rhs>
class SumExpression {
 public:
  SumExpression(const Lhs& lhs, const Rhs& rhs) : lhs_(lhs), rhs_(rhs) {}

  double operator[](std::size_t index) const {
    return lhs_[index] + rhs_[index];
  }

  explicit operator Matrix() const {
    return Matrix{(*this)[0], (*this)[1], (*this)[2], (*this)[3]};
  }

 private:
  const Lhs& lhs_;
  const Rhs& rhs_;
};

template <typename Lhs, typename Rhs>
SumExpression<Lhs, Rhs> operator+(const Lhs& lhs, const Rhs& rhs) {
  return SumExpression<Lhs, Rhs>{lhs, rhs};
}

int main() {
  std::cout << "Item 06: use ETII when auto deduces an unexpected type\n\n";

  Widget w;

  using VectorBoolSubscriptType =
      decltype(features(std::declval<Widget>())[5]);
  static_assert(!std::is_same_v<VectorBoolSubscriptType, bool>);

  printIsBool<VectorBoolSubscriptType>("features(w)[5]");

  // ñ¢íËã`ìÆçÏÇ∆Ç»ÇÈ
  // auto highPriority = features(w)[5];
  
  auto highPriority = static_cast<bool>(features(w)[5]);
  printIsBool<decltype(highPriority)>("highPriority");
  processWidget(w, highPriority);

  std::cout << '\n';

  std::vector<bool> flags = {false, false, false, false, false, true};
  auto proxy = flags[5];
  auto value = static_cast<bool>(flags[5]);

  proxy = false;
  std::cout << "proxy follows vector<bool>: " << std::boolalpha
            << static_cast<bool>(flags[5]) << '\n';
  std::cout << "value is an independent bool copy: " << value << '\n';

  std::cout << '\n';

  Matrix m1{1, 2, 3, 4};
  Matrix m2{10, 20, 30, 40};
  Matrix m3{100, 200, 300, 400};
  Matrix m4{1000, 2000, 3000, 4000};

  using LazySumType = decltype(m1 + m2 + m3 + m4);
  static_assert(!std::is_same_v<LazySumType, Matrix>);
  printIsMatrix<LazySumType>("m1 + m2 + m3 + m4");

  auto sum = static_cast<Matrix>(m1 + m2 + m3 + m4);
  static_assert(std::is_same_v<decltype(sum), Matrix>);
  printIsMatrix<decltype(sum)>("sum");
  sum.print("ETII sum");

  // Avoid this pattern when the expression stores references to temporaries:
  // auto danglingProxy = Matrix{1, 2, 3, 4} + Matrix{5, 6, 7, 8};

  return 0;
}
