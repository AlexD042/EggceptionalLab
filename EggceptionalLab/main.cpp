#include <iostream>
#include <exception>
#include <string>
#include <vector>

class bad_egg : public std::exception {
public:
	const char* what() const {
		return "You can't eat a rotten egg!";
	}
};

class Egg {
protected:
	int size;
	std::string flavor;
public:
	Egg(int s, std::string f) : size(s), flavor(f) {}

	int getSize() const { return size; }
	std::string getFlavor() const { return flavor; }

	virtual void eat_egg() = 0;
};

class RottenEgg : public Egg {
public:
	RottenEgg(int s) : Egg(s, "Awful") {}

	void eat_egg() override {
		throw bad_egg();
	}
};

class TastyEgg : public Egg {
public:
	TastyEgg(int s) : Egg(s, "Tasty") {}

	void eat_egg() override {
		std::cout << "You eat a tasty egg.\n";
	}
};

class HardboiledEgg : public Egg {
public:
	HardboiledEgg(int s) : Egg(s, "Yummy") {}

	void eat_egg() override {
		std::cout << "You peel off the shell and eat a yummy egg.\n";
	}
};

class Carton {
private:
	std::vector<Egg*> eggs;
	const int maxSize = 12;
public:
	void addEgg(Egg* egg) {
		if (eggs.size() < maxSize) {
			eggs.push_back(egg);
		}
		else {
			std::cout << "The carton is full!\n";
			delete egg;
		}
	}

	void takeEgg() {
		if (eggs.empty()) {
			std::cout << "The carton is empty! You have no eggs to take.\n";
			return;
		}

		Egg* currentEgg = eggs.back();
		eggs.pop_back();

		try {
			currentEgg->eat_egg();
		}
		catch (const bad_egg& e) {
			std::cout << "ERROR: " << e.what() << "\n";
		}

		delete currentEgg;
	}
};

int main() {
	Carton myCarton;

	myCarton.addEgg(new TastyEgg(2));
	myCarton.addEgg(new RottenEgg(1));
	myCarton.addEgg(new HardboiledEgg(3));

	myCarton.takeEgg();
	myCarton.takeEgg();
	myCarton.takeEgg();

	return 0;
}