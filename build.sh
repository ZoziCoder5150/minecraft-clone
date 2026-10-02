rm -rf build
mkdir build

cp -r src/res build/res

g++ -c src/main.cpp -o build/main.o -I./raylib/src
g++ -c src/engine.cpp -o build/engine.o -I./raylib/src
g++ -c src/registry.cpp -o build/registry.o -I./raylib/src

g++ build/main.o build/engine.o build/registry.o -o build/final -L./raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11