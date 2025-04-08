#include "f.hxx"
#include <unistd.h>

class Foo;
Foo::Foo (): i(getpid()) {}
Foo f;
