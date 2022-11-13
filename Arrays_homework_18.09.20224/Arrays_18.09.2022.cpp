#include<iostream>
#include<string>
#include<vector>
#include<random>


class Sound {
public:
	Sound(){}
	Sound(std::string sound):sound_(sound){}
	virtual void play()const = 0;
	virtual ~Sound() {};
	  //чиста€ виртуальна€ функци€ 
	 //наличие чистой виртуальной ф-ии
	//делает класс абстрактным!
   //мы не можем пока создать в майне объект на данном шаге
	//но позвол€ет наследовать им€ класса


protected://дл€ того чтобы иметь доступ к полю Sound
	std::string sound_;

};

class Buzzer :public Sound {//создадим дочерний класс
public:
	Buzzer():Sound("Buzz"){}
	void play()const override {
		std::cout << sound_;

	}
};
class Zapper :public Sound {//создадим дочерний класс
public:
	Zapper() :Sound("Zzap") {}//это пример сильной св€зи
	void play()const override {
		std::cout << sound_;// это пример сильной св€зи

	}
};

class Optional :public Sound {
public:
	Optional(std::string sound) :Sound(sound) {}
	void play()const override {
		std::cout << sound_;//
	}
};
class Playlist {//создадим коллекцию звуков - это наш информационный эксперт
public:
	void generate(int i) {//создадим метод generate
		std::mt19937 gen{ std::random_device()() }//создание генератора
			//mt19937 - генератор...это такой синтаксис
	;
		std::uniform_int_distribution<int> dist(0, 1);//это поставщик случайных числе
		//стандартный синтаксис uniform
		for (int j = 0; j < i; j++)
		{
			if (dist(gen)) {
				data_.emplace_back(new Buzzer);

			}
			else {
				data_.emplace_back(new Zapper);
			}
		}//это код имитации броска монетки - стандартный код
	}
	void play()const {
		for (int i = 0; i < size(); i++) {
			data_[i]->play();
		}
	}

	int size()const {//создадим метод size
		return data_.size();

	}
	Sound& operator[](int i) {
		//Sound* tmp = data_[i];//расшифровка
		//Sound& result = *tmp;
		return *(data_[i]);
	}//синтаксис перегрузки операторов
	const Sound& operator[](int i) const {//это на случай чтобы пользователь мог только смотреть и ни чего не мен€ть - вызов константной ссылки
		return *(data_[i]);

	}
	~Playlist() {
		if (!data_.empty()) {//если данные не пустые
			for (int i = 0; i < data_.size(); i++) {
				delete data_[i];//оператор delete вызывает диструктор
				//класса 
			}
		}
	}

private:
	std::vector<Sound *> data_;//если не добавить указатель
	//по€витс€ ошибка при компил€ции...это пример
	//зацеплени€ (или слабой св€зи)


};
int main() {
	setlocale(LC_ALL, "Russian");
	//Sound g;
	Playlist pl;

	std::cout << pl.size() << "\n";
	pl.generate(10);
	std::cout << pl.size() << "\n";
	pl.play();
	std::cout << "\n";
	for (int i = pl.size() - 1; i >= 0; i--) {
		pl[i].play();
		std::cout << "\n";
	}//выведем элементы плэйлиста в обратном пор€дке

	//pl[0].play();


	return 0;


}


