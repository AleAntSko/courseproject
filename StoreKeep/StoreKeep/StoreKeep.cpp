#include "pch.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <conio.h> //для _getch

using namespace std;

bool flag, flagmain;

//функции
void registration();//регистрация и запись в файл
void read();
string login();
bool checkLogin(string login);
bool checkPass(string pass);
string enterPassWithStars(string str);
int setgroup(string login);
//функции меню
void admin(void);
void storekeeper(void);
void worker(void);





void(*group[])(void) =  // массив указателей на функции
{
	admin, storekeeper, worker
};



struct Users
{
	string login;
	string pass;
	int idUser;
};

auto Lusers = list <Users>();

int main()
{
	setlocale(LC_ALL, "russian");
	string userlog;
	flagmain = true;
	int id;
	read();
	while (flagmain == true)
	{
		userlog = login();
		cout << "Добро пожаловать, " << userlog<< endl;
		system("pause");
		id = setgroup(userlog);
		group[id - 1]();
	}
	system("pause");
	return 0;
}

bool checkLogin(string login)
{
	bool flag = false;
	for (int i = 0; i < login.size(); i++)
	{
		if ((login[i] >= '0' && login[i] <= '9') || (login[i] >= 'A' && login[i] <= 'z') || (login[i] == '-' || login[i] == '_'))
		{
			flag = true;
		}
		else
		{
			cout << "Недопустимые символы при вводе логина\n";
			flag = false;
			break;
		}
	}
	return flag;
}

bool checkPass(string pass)
{
	bool flag = false;
	for (int i = 0; i < pass.size(); i++)
	{
		if ((pass[i] >= 'A' && pass[i] <= 'z') || (pass[i] >= '0' && pass[i] <= '9'))
		{
			flag = true;
		}
		else
		{
			cout << "Недопустимые символы при вводе пароля\n";
			flag = false;
			break;
		}
		if (pass.size() <= 6 && pass.size() >= 14)
		{
			cout << "Длина пароля должна быть не менее 6 и не более 14 символов\n";
			flag = false;
			break;
		}
	}
	return flag;
}

void registration()
{
	ofstream fout("USERS", ios::binary | ios::app);
	bool flag = true;
	int k = 0;
	auto *buf = new Users;
	do
	{
		cout << "Регистрация.\n";
		cout << "Введите логин: ";
		cin >> buf->login;
		cout << "Введите пароль: ";
		buf->pass = enterPassWithStars(buf->pass);
		for (auto lusers : Lusers)
		{
			if (lusers.idUser == 1)
			{
				k++;
				break;
			}
		}
		if (k == 0)
		{
			buf->idUser = 1;
		}
		else
		{
			cout << "\nВыберите права доступа.\n1-администратор\n2-кладовщик\n3-рабочий\n";
			cin >> buf->idUser;
		}
		if (!checkLogin(buf->login))
			flag = false;
		else if (!checkPass(buf->pass))
			flag = false;
		else if (buf->idUser < 1 && buf->idUser > 3)
			flag = false;
		else
			for (auto lusers : Lusers)
				if (lusers.login == buf->login)
					flag = false;
	} while (!flag);
	Lusers.push_back(*buf);
	fout.write((char*)buf, sizeof(*buf));
	system("cls");
	cout << "Регистрация выполнена!" << endl;
	fout.close();
}

void read()
{
	ifstream fout("USERS", ios::binary | ios::app);
	auto *buf = new Users;
	fout.seekg(0);
	while (!fout.eof())
	{
		fout.read((char*)buf, sizeof(*buf));
		Lusers.push_back(*buf);
	}
	Lusers.pop_back();
	fout.close();
}

string enterPassWithStars(string str) {
	unsigned char p;
	while (true) {
		p = _getch();
		if (p == 13) break;
		if (p == '\b' && !str.empty()) {
			cout << '\b';
			cout << ' ';
			cout << '\b';
			str.pop_back();
			continue;
		}
		if (isalnum((unsigned char)p)) {
			cout << '*';
			str.push_back(p);
		}
	}
	return str;
}

string login()
{
	string login="", pass="";
	bool flag = true;
	cout << "Меню авторизации.\n";
	int k = 0;
	read();
	do
	{
		for (auto lusers : Lusers)
		{
			if (lusers.idUser == 1)
			{
				k++;
				break;
			}
		}
		if (k == 0)
		{

			cout << "Первый запуск программы.\nЗарегистрируйте администратора.\n\n";
			registration();
		}
		else
		{
			string mas[3] = { "Администратор","Кладовщик","Рабочий" };
			login = "";
			cout << "Введите логин:";
			cin >> login;
			pass = "";
			cout << "Введите пароль:";
			pass = enterPassWithStars(pass);

			for (auto lusers : Lusers)
			{
				if (login == lusers.login && pass == lusers.pass)
				{
					system("cls");
					cout << "Добро пожаловать, " << login;
					cout << "\nВы " << mas[lusers.idUser - 1] << "\n\n";	
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				system("cls");
				cout << "Ошибка авторизации.\nПроверьте правильность введенных данных.\n";
			}
		}
	} while (flag == true || k == 0);
	return login;
}

int setgroup(string login)
{
	int group;
	for (auto lusers : Lusers)
		if (lusers.login == login)
		{
			group = lusers.idUser;
			break;
		}
	return group;
}

void admin(void)
{
	cout << "\nHELLO ADMIN\n";
	system("pause");
}
void storekeeper(void)
{
	cout << "\nHELLO STOREKEEPER\n";
}
void worker(void)
{
	cout << "\nHELLO WORKER\n";
}
