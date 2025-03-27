#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char c;
    read(0, &c, 1);
    getenv("HOME");
    return 0;
}
