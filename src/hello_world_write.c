#include <unistd.h>

int main() {
    char *msg = "Hola World!\n";

    // write(file_descriptor, buffer, count)
    write(1, msg, 12);

    return 0;
}
