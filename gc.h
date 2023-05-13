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
	bool marked = false;
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
	}

	void push(Object* value) {
		this->stack[this->size++] = value;
	}

	Object* pop() {
		return this->stack[--this->size];
	}

	Object* pushInt(int value) {
		Object* object = this->newObject(INT);
		object->value = value;
		this->push(object);
		return object;
	}

	Object* pushButterfly(Object* left, Object* right) {
		Butterfly* butterfly = this->newButterfly(left, right);
		Object* object = this->newObject(BUTTERFLY);
		object->value = butterfly;
		this->push(object);
		return object;
	}

	// gc start
	
	void markAll() {
		for (int i = 0; i < this->size; i++) {
			this->stack[i]->mark();
		}
	}

	void sweep() {
		for (int i = 0; i < this->size; i++) {
			if (!this->stack[i]->marked) {
				delete this->stack[i];
			}
		}
	}

private:
	Object* newObject(TypeName type) {
		Object* object = new Object;
		object->type = type;
		return object;
	}

	Butterfly* newButterfly(Object* left, Object* right) {
		Butterfly* butterfly = new Butterfly;
		butterfly->left = left;
		butterfly->right = right;
		return butterfly;
	}
};