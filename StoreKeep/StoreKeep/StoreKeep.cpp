#include "pch.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <conio.h> //для _getch

using namespace std;

//блок функций для авторизации и регистрации
void registration();//регистрация и запись в файл
void read();
string login(int *id);
bool checkLogin(string login);
bool checkPass(string pass);
string starPass(string str);

//блок функций админа
void textMenuAdmin();
void registration_new();
void seeAll();
void addStorekeeper();
void addAdmin();
void delAdmin();


//блок функций кладовщика
void textMenuStoreKeeper();
void addWorker();
void delWorker();
void addItem();
void delItem();
void addStock();


//блок функций работника
void textMenuWorker();
void seeItem();
void exitFunc();

void autorization();

struct Users
{
	string login;
	string pass;
	int idUser;
};
auto Lusers = list <Users>();

struct Item
{
	string name;
	int height; //высота 
	int width;  //ширина 
	int lenght; //длина 
	//решить проблему с датой
};

struct Stock
{
	int count;
	int rows;
	int columns;
};

typedef void(*MENU) ();
MENU menu_admin[] = { textMenuAdmin, seeAll, addStorekeeper, registration_new, delAdmin, addWorker, delWorker, addItem, delItem, addStock, seeItem,autorization, exitFunc };

MENU menu_storekeeper[] = { textMenuStoreKeeper, addWorker, delWorker, addItem, delItem, addStock, seeItem , autorization, exitFunc };

MENU menu_worker[] = { textMenuWorker, seeItem, autorization, exitFunc };

void enterMenu(int menuNum, string Login)
{
	string mas[3] = { "Администратор","Кладовщик","Рабочий" };
	system("cls");
	cout << "Добро пожаловать, " << Login;
	cout << "\nВы " << mas[menuNum - 1] << "\n\n";
	switch (menuNum)
	{
	case 1:
	{
		menu_admin[0]();
		break;
	}
	case 2:
	{
		menu_storekeeper[0]();
		break;
	}
	case 3:
		menu_worker[0]();
		break;
	}
	int menu;
	while (true)
	{
		cin >> menu;
		switch (menuNum)
		{
		case 1:
		{
			menu_admin[menu]();
			break;
		}
		case 2:
		{
			menu_storekeeper[menu]();
			break;
		}
		case 3:
			menu_worker[menu]();
			break;
		}
	}
}

int main()
{
	int id = 0;
	setlocale(LC_ALL, "russian");
	string userlog;
	userlog = login(&id);
	enterMenu(id, userlog);
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
	auto *buf = new Users;
	do
	{
		cout << "Регистрация.\n";
		cout << "Введите логин: ";
		cin >> buf->login;
		cout << "\nВведите пароль: ";
		buf->pass = starPass(buf->pass);
		buf->idUser = 1;
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

void registration_new()
{
	system("cls");
	ofstream fout("USERS", ios::binary | ios::app);
	bool flag = true;
	auto *buf = new Users;
	do
	{
		cout << "Меню регистрации пользователей\n";
		cout << "Введите логин:" << endl;
		cin >> buf->login;
		cout << "Введите пароль:" << endl;
		cin >> buf->pass;
		cout << "Введите идентификатор пользователя\n";
		cout << "Администратор (1)    Кладовщик(2)    Рабочий(3)";
		cin >> buf->idUser;
		if (!checkLogin(buf->login))
			flag = false;
		else if (!checkPass(buf->pass))
			flag = false;
		else if (buf->idUser < 2 && buf->idUser > 3)
			flag = false;
		else
			for (auto lusers : Lusers)
				if (lusers.login == buf->login)
					flag = false;
	} while (!flag);
	Lusers.push_back(*buf);
	fout.write((char*)buf, sizeof(*buf));
	system("cls");
	cout << "Регистрация прошла успешно!" << endl;
	fout.close();
	menu_admin[0]();

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

string starPass(string str) {
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

string login(int *id)
{
	string login, pass;
	bool flag = true;
	cout << "Меню авторизации.\n";
	int k = 0;
	read();
	do
	{
		k = 0;
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
			cout << "Введите логин: ";
			login = "";
			cin >> login;
			cout << "Введите пароль: ";
			pass = "";
			pass = starPass(pass);

			for (auto lusers : Lusers)
			{
				if (login == lusers.login && pass == lusers.pass)
				{
					system("cls");
					*id = lusers.idUser;
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

//блок функций админа
void seeAll()
{
	cout << "Просмотр всего" << endl;
}

void addStorekeeper()
{
	cout << "Добавление кладовщика" << endl;
}

void addAdmin()
{
	cout << "Добавление админа" << endl;
}

void delAdmin()
{
	cout << "Удаление админа" << endl;
}

void textMenuAdmin()
{
	cout << "Меню: \n";
	cout << "1. Просмотр всех файлов.(-)" << endl;
	cout << "2. Добавление Кладовщика(-)." << endl;
	cout << "3. Добавление нового пользователя(+)." << endl;
	cout << "4. Удаление админа(-). " << endl;
	cout << "5. Добавление рабочего.(-)" << endl;
	cout << "6. Удаление рабочего. " << endl;
	cout << "7. Добавление товара.(-)" << endl;
	cout << "8. Удаление товара(-). " << endl;
	cout << "9. Добавление склада(-)." << endl;
	cout << "10. Просмотр товаров(-)." << endl;
	cout << endl << "11. Авторизация.(+)" << endl;
	cout << "12. Выход.(+)" << endl;

}

//блок функций кладовщика
void addWorker()
{
	cout << "Добавление рабочего" << endl;
}

void delWorker()
{
	cout << "Удаление рабочего" << endl;
}

void addItem()
{
	cout << "Добавление товара./n" << endl;

}

void delItem()
{
	cout << "Удаление товара" << endl;
}

void addStock()
{
	cout << "Добавление склада" << endl;
}

void textMenuStoreKeeper()
{
	cout << "Меню: \n";
	cout << "1. Добавление рабочего." << endl;
	cout << "2. Удаление рабочего. " << endl;
	cout << "3. Добавление товара." << endl;
	cout << "4. Удаление товара. " << endl;
	cout << "5. Добавление склада." << endl;
	cout << "6. Просмотр товаров." << endl;
	cout << endl << "7. Авторизация." << endl;
	cout << "8. Выход" << endl;
}

//блок функций работника
void textMenuWorker()
{
	cout << "Меню: \n";
	cout << "1. Просмотр товаров." << endl;
	cout << endl << "2. Авторизация." << endl;
	cout << "3. Выход" << endl;
}

void seeItem()
{

}

void autorization()
{
	{
		system("cls");
		string login = "", pass = "";
		bool flag = true;
		cout << "Меню авторизации\n";
		int k = 0;
		read();
		do
		{
			string mas[3] = { "администратор","кладовщик","рабочий" };
			cout << "Введите логин:" << endl;
			cin >> login;
			cout << "Введите пароль:" << endl;
			cin >> pass;
			system("cls");
			for (auto lusers : Lusers)
			{
				if (login == lusers.login && pass == lusers.pass)
				{
					cout << "Вход в систему выполнен. " << mas[lusers.idUser - 1] << login << endl;
					switch (lusers.idUser)
					{
					case 1:
					{
						menu_admin[0]();
						break;
					}
					case 2:
					{
						menu_storekeeper[0]();
						break;
					}
					case 3:
						menu_worker[0]();
						break;
					}
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				cout << "Логин или пароль введены неверно.\nПовторите ввод данных либо обратитесь к администратору.\n" << endl;
				system("pause");
				system("cls");
			}

		} while (flag == true);
	}

}

void exitFunc() {
	exit(0);
}
