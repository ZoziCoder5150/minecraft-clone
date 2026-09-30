rm -rf build
mkdir build

g++ -c src/main.cpp -o build/main.o -I./raylib/src

g++ build/main.o -o build/final -L./raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11