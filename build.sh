create() {
    mkdir -p build && cd build && cmake .. && cmake --build .
}

create
cd ..
