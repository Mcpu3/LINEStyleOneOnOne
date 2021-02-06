# LINE風 (個人チャット)

© 2021 岩本圭介

## ビルド

`LINE_style_one_on_one`ディレクトリで次のコマンドを実行してください。

```
make -j
```

### テスト済みのビルド環境

こちらでテスト済みのビルド環境は次の通りです。

- GNU Make 4.3
- g++ (GCC) 10.2.0

## アプリケーションの実行

サーバー アプリケーションを実行するには、`LINE_style_one_on_one/Server`ディレクトリで次のコマンドを実行してください。

```
./server
```

またクライアント アプリケーションを実行するには、`LINE_style_one_on_one/Client`ディレクトリで次のコマンドを実行してください。

```
./client
```

## サードパーティー製ライブラリ

[PicoJSON](https://github.com/kazuho/picojson)を利用しております。