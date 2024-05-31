#include "CApiReader.hpp"

int main(int argc, char const* argv[]) {
    CApiReader reader("54.71.61.211", 80);
    reader.start();
    return 0;
}
