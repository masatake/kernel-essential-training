#include <stdio.h>

static int var_static_a;
static int var_static_init_a = 0xaaaaaaa1;
static const int const_static_init_a = 0xaaaaaaa2;

int var_global_a;
int var_global_init_a = 0xaaaaaaa3;
const int const_global_init_a = 0xaaaaaaa4;

static int func_static_a(int i)
{
    return i;
}

int func_global_a(int i)
{
    return i;
}

void report_fun_a(void)
{
    printf("func_static_a: %p\n", &func_static_a);
}

void report_var_a(void)
{
    printf("var_static_a: %p\n", &var_static_a);
    printf("var_static_init_a: %p\n", &var_static_init_a);
}

void report_const_a(void)
{
    printf("const_static_init_a: %p\n", &const_static_init_a);
}
