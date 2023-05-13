#include "gc.h"

using namespace std;

int main()
{
	VM* vm = new VM;
	Object* a = vm->pushInt(100);
	Object* left = vm->pushInt(69);
	Object* right = vm->pushInt(420);
	Object* b = vm->pushButterfly(left, right);
	vm->markAll();
	Object* l = vm->pushInt(11111111);
	Object* r = vm->pushInt(1111111);
	vm->pushButterfly(l, r);
	vm->sweep();
	delete vm;
}
