This is a basic example cart in C for the [null0](https://notnull.games/null0) game-engine.

## usage

Carts run natively, and on the web. This repo will auto-publish to github-pages on push, so users can check out your cart without installing anything.

They can also install [the native runtime](https://github.com/notnullgames/null0/releases) and use it to run your cart.

## github

There are 2 actions:

- Publish demo to github-pages - this happens on any push
- Attach current version of your cart to any releases that are created (like [here](https://github.com/notnullgames/cart_c/releases/))

## developing

Make sure you have [wasi-sdk](https://github.com/WebAssembly/wasi-sdk/releases) installed and `WASI_SDK_PATH` set to it's location (eg `/opt/wasi-sdk`.)

Then you can do this:

```sh
$WASI_SDK_PATH/bin/clang src/main.c -o src/main.wasm
cd src
zip -r ../webroot/mygame.null0 . -x '*.h' '*.c'
```

You can also use cmake (recommended) to build a complete cart:

```sh
cmake -B build -DCMAKE_TOOLCHAIN_FILE="${WASI_SDK_PATH}/share/cmake/wasi-sdk.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

You will find your cart in `webroot/mygame.null0`

If you have node installed, you can also get a nice watching-webseerver, locally:

```
npm start
```

After this, create a github-release, and your cart will show up on releases (like [here](https://github.com/notnullgames/cart_c/releases/)).

