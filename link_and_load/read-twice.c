#include <unistd.h>

int main(void)
{
    read (-1, NULL, 0);
    read (-1, NULL, 0);
    write (-1, NULL, 0);
    write (-1, NULL, 0);
    return 0;
}
