# CMakeのサンプル

## やりたいこと

- [CMake]を使ってライブラリをつくる。
- [Google Test]を使ってユニットテストをする。
- [gcov]を使ってカバレッジを測定する。
- [cppcheck]を使って静的解析をする。
- [lizard]を使ってコードの複雑度を測定する。

## 事前準備

- [CMake]をインストールする。
- [gcovr]をインストールする。
- [cppcheck]をインストールする。
- [lizard]をインストールする。

## ビルドする

```
cmake -B build
cmake --build build
```

静的解析、複雑度計測を行う

```
cmake -B build -DSAMPLE_USE_CPPCHECK=ON -DSAMPLE_USE_LIZARD=ON
cmake --build build
```

## テストを実行する

```
cmake -B build -DSAMPLE_WITH_TESTS=ON
cmake --build build
cd build
ctest
```

## カバレッジを測定する

```
cmake -B build -DSAMPLE_USE_GCOV=ON
cmake --build build
cd build
ctest
make coverage
```

coverage/index.htmlを開いてカバレッジを確認する。

[CMake]: https://cmake.org/
[Google Test]: https://google.github.io/googletest/
[gcov]: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
[gcovr]: https://gcovr.com/
[cppcheck]: https://cppcheck.sourceforge.io/
[lizard]: https://github.com/terryyin/lizard
