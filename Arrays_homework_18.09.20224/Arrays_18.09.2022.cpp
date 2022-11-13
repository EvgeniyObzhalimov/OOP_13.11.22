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
	  //������ ����������� ������� 
	 //������� ������ ����������� �-��
	//������ ����� �����������!
   //�� �� ����� ���� ������� � ����� ������ �� ������ ����
	//�� ��������� ����������� ��� ������


protected://��� ���� ����� ����� ������ � ���� Sound
	std::string sound_;

};

class Buzzer :public Sound {//�������� �������� �����
public:
	Buzzer():Sound("Buzz"){}
	void play()const override {
		std::cout << sound_;

	}
};
class Zapper :public Sound {//�������� �������� �����
public:
	Zapper() :Sound("Zzap") {}//��� ������ ������� �����
	void play()const override {
		std::cout << sound_;// ��� ������ ������� �����

	}
};

class Optional :public Sound {
public:
	Optional(std::string sound) :Sound(sound) {}
	void play()const override {
		std::cout << sound_;//
	}
};
class Playlist {//�������� ��������� ������ - ��� ��� �������������� �������
public:
	void generate(int i) {//�������� ����� generate
		std::mt19937 gen{ std::random_device()() }//�������� ����������
			//mt19937 - ���������...��� ����� ���������
	;
		std::uniform_int_distribution<int> dist(0, 1);//��� ��������� ��������� �����
		//����������� ��������� uniform
		for (int j = 0; j < i; j++)
		{
			if (dist(gen)) {
				data_.emplace_back(new Buzzer);

			}
			else {
				data_.emplace_back(new Zapper);
			}
		}//��� ��� �������� ������ ������� - ����������� ���
	}
	void play()const {
		for (int i = 0; i < size(); i++) {
			data_[i]->play();
		}
	}

	int size()const {//�������� ����� size
		return data_.size();

	}
	Sound& operator[](int i) {
		//Sound* tmp = data_[i];//�����������
		//Sound& result = *tmp;
		return *(data_[i]);
	}//��������� ���������� ����������
	const Sound& operator[](int i) const {//��� �� ������ ����� ������������ ��� ������ �������� � �� ���� �� ������ - ����� ����������� ������
		return *(data_[i]);

	}
	~Playlist() {
		if (!data_.empty()) {//���� ������ �� ������
			for (int i = 0; i < data_.size(); i++) {
				delete data_[i];//�������� delete �������� ����������
				//������ 
			}
		}
	}

private:
	std::vector<Sound *> data_;//���� �� �������� ���������
	//�������� ������ ��� ����������...��� ������
	//���������� (��� ������ �����)


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
	}//������� �������� ��������� � �������� �������

	//pl[0].play();


	return 0;


}


