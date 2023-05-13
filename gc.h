#pragma once

#include <iostream>
#include <variant>
constexpr int CAPACITY = 512;

enum TypeName {
	INT,
	BUTTERFLY
};

class Butterfly {
public:
	class Object* left;
	class Object* right;
};

class Object {
public:
	TypeName type;
	bool marked;
	std::variant<int, Butterfly*> value;

	void mark() {
		if (this->marked) return;
		this->marked = true;
		if (this->type == BUTTERFLY) {
			Butterfly* butterfly = std::get<Butterfly*>(value);
			butterfly->left->mark();
			butterfly->right->mark();
		}
	}
};

class VM {
	Object* stack[CAPACITY];
	int size;

public:
	VM() {
		this->size = 0;
		for (Object*& object : this->stack) {
			object = nullptr;
		}
	}

	void push(Object* value) {
		this->stack[this->size++] = value;
	}

	Object* pop() {
		return this->stack[--this->size];
	}

	void pushInt(int value) {
		Object* object = this->newObject(INT);
		object->value = value;
		this->push(object);
	}

	Object* pushButterfly(Object* left, Object* right) {
		Butterfly* butterfly = this->newButterfly(left, right);
		Object* object = this->newObject(BUTTERFLY);
		object->value = butterfly;
		this->push(object);
		return object;
	}

	Object* newObject(TypeName type) {
		Object* object = new Object;
		object->type = type;
	}

	Butterfly* newButterfly(Object* left, Object* right) {
		Butterfly* butterfly = new Butterfly;
		butterfly->left = left;
		butterfly->right = right;
		return butterfly;
	}

	// gc start
	
	void markAll() {
		for (Object*& object : this->stack) {
			object->mark();
		}
	}

	void sweep() {
		for (Object*& object : this->stack) {
			if (object->marked) continue;
			delete object;
		}
	}
};