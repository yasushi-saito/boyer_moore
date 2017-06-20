#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

class BoyerMooreSearch {
 public:
  explicit BoyerMooreSearch(const std::string& pattern) : pattern_(pattern) {
    assert(!pattern.empty());
    InitBadCharsTable(pattern);
    InitGoodSuffixes(pattern);
  }

  int Search(const std::string& data) const {
    const int N = pattern_.size();
    const int D = data.size();
    int j = 0;
    while (j <= D - N) {
      int i = 0;
      for (i = N - 1; i >= 0 && pattern_[i] == data[i + j]; --i)
        ;
      if (i < 0) {
        return j;
      }
      unsigned char ch = data[i + j];
      j += std::max(good_suffixes_[i], bad_chars_[ch] - N + 1 + i);
    }
    return -1;
  }

 private:
  void InitBadCharsTable(const std::string& pattern) {
    static_assert(sizeof(pattern[0]) == 1);
    const int N = pattern.size();
    for (int i = 0; i < 256; ++i) {
      bad_chars_[i] = N;
    }
    for (int i = 0; i < N; ++i) {
      unsigned char ch = pattern[i];
      bad_chars_[ch] = N - i - 1;
    }
  }

  static std::vector<int> FillSuffixes(const std::string& pattern) {
    const int N = pattern.size();
    std::vector<int> suffixes(pattern.size());
    suffixes[N - 1] = N;
    int g = N - 1;
    int f = 0;
    for (int i = N - 2; i >= 0; --i) {
      if (i > g && suffixes[i + N - 1 - f] < i - g) {
        suffixes[i] = suffixes[i + N - 1 - f];
      } else {
        if (i < g) {
          g = i;
        }
        f = i;
        while (g >= 0 && pattern[g] == pattern[g + N - 1 - f]) {
          --g;
        }
        suffixes[i] = f - g;
      }
    }
    return suffixes;
  }

  void InitGoodSuffixes(const std::string& pattern) {
    std::vector<int> suffixes = FillSuffixes(pattern);
    const int N = pattern.size();
    good_suffixes_.resize(N);
    for (int i = 0; i < N; ++i) {
      good_suffixes_[i] = N;
    }
    int j = 0;
    for (int i = N - 1; i >= 0; --i) {
      if (suffixes[i] == i + 1) {
        for (; j < N - 1 - i; ++j) {
          if (good_suffixes_[j] == N) {
            good_suffixes_[j] = N - 1 - i;
          }
        }
      }
    }
    for (int i = 0; i <= N - 2; ++i) {
      good_suffixes_[N - 1 - suffixes[i]] = N - 1 - i;
    }
  }
  const std::string pattern_;
  std::array<int, 256> bad_chars_;
  std::vector<int> good_suffixes_;
};
