#include "gc.h"

using namespace std;

int main()
{
	VM* vm = new VM;
	vm->pushInt(100);
	Object* left = vm->pushInt(69);
	Object* right = vm->pushInt(420);
	vm->pushButterfly(left, right);
	vm->markAll();
	vm->sweep();
	delete vm;
}
