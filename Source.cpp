#include <iostream>
#include <windows.h>
#include <fstream>
#include <list>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

struct ticket
{
	string name, surname, pass, ntrain, date, type;
	int cost;
};
auto tickets = list<ticket>();
struct Users
{
	string login;
	string parol;
	string name;
	string surname;
	int post;
};
auto Lusers = list <Users>();

struct timetable
{
	string train, date1, time, city1, city2;
	int mestEko, mestKomf, costEco, costKomf;
};
auto actTimetable = list<timetable>();

struct vag
{
	string type;
	int mesta, cost;
};

typedef list<vag> vag_list;

struct train
{
	string name, city1, city2;
	int c_vagons, costEco, costComf;
	vag_list* vagons;// ������ �������
};
auto lst_train = list <train>();

void register_1();
void read();
string login();
bool testlog(string login);
bool testpass(string parol);
int setgroup(string login);
void about();
void logout();
void reference();
void infoTimetable();
void refund();
void sale();
void account();
void quit();
void createTimetable();
void deleteTimetable();
void readTimetable();
void editAccount();
void rewriteUser();
void coutUser();
void deleteAccount();
void readTrain();
void init_trains();
void coutTrain();
void delTrain();
void editTrain();
void ttrain();
void mtimetable();
void rewTimetable();
void rewtrain();
void coutTicket();
void readTicket();
void rewTickets();
bool testDate(string str1);
bool checkPass(string pass);
string pushDate1();
string pushDate2();
bool flag, flagmain;
string firstName;
string GetTableDate(string date, int addDays);

void(*menu[])(void)
{
	account, mtimetable, ttrain, sale, refund, reference, infoTimetable, logout, about, quit, coutTicket
};

void admin(void)
{
	int t;
	flag = true;
	system("cls");
	while (flag == true && flagmain == true)
	{
		system("cls");
		cout << "�� ���������������� ��� ��������� ��������������! \n�������� ������������ ��� ����� ����:" << endl;
		cout << "1. ���������� ����������" << endl;
		cout << "2. ���������� �����������" << endl;
		cout << "3. ���������� ������� �������" << endl;
		cout << "4. ������� ������" << endl;
		cout << "5. ������� ������" << endl;
		cout << "6. �������" << endl;
		cout << "7. ���������� �������� �������" << endl;
		cout << "8. ������� ������������" << endl;
		cout << "9. � ���������" << endl;
		cout << "10. �����" << endl;
		cin >> t;
		if (t >= 1 && t <= 10)
		{
			system("cls");
			menu[t - 1]();
		}
		else
		{
			cout << "�������� ����� ����!" << endl;
			system("pause");
		}
	}
}

void cashier(void)
{
	int t;
	flag = true;
	while (flag == true && flagmain == true)
	{
		system("cls");
		cout << "�� ���������������� ��� ��������� �������! \n�������� ������������ ��� ����� ����:" << endl;
		cout << "1. ������� ������" << endl;
		cout << "2. ������� ������" << endl;
		cout << "3. �������" << endl;
		cout << "4. ���������� �������� �������" << endl;
		cout << "5. ������� ������������" << endl;
		cout << "6. � ���������" << endl;
		cout << "7. �����" << endl;
		cin >> t;
		system("cls");
		if (t >= 1 && t <= 7)
			menu[t + 2]();
		else
		{
			cout << "�������� ����� ����" << endl;
			system("pause");
		}
	}
}

void passanger(void)
{	//���� ���������
	int t;
	flag = true;
	while (flag == true && flagmain == true)
	{
		system("cls");
		cout << "�� ���������������� ��� ��������� ���������! \n�������� ������������ ��� ����� ����:" << endl;
		cout << "1. ���������� �������� �������" << endl;
		cout << "2. ������� ������������" << endl;
		cout << "3. � ���������" << endl;
		cout << "4. �����" << endl;
		cin >> t;
		if (t >= 1 && t <= 4)
			menu[t + 5];
		else
		{
			cout << "�������� ����� ����" << endl;
			system("pause");
		}
	}
}

void(*group[])(void) =  // ������ ���������� �� �������
{
 admin, cashier, passanger
};

void(*acc[])(void) =  // ������ ���������� �� �������
{
 register_1, editAccount , deleteAccount,coutUser
};

void(*mtrain[])(void) =
{
	coutTrain,delTrain,editTrain,init_trains
};

void(*mttable[])(void) =
{
	createTimetable,deleteTimetable,infoTimetable
};

int main()
{
	setlocale(LC_ALL, "rus");
	string log;
	int g;
	flagmain = true;
	read();
	readTimetable();
	readTrain();
	readTicket();
	while (flagmain == true)
	{
		log = login();
		cout << "����� ����������, " << firstName << endl;
		system("pause");
		g = setgroup(log);
		group[g - 1]();
	}
	system("pause");
	return 0;
}

void register_1()
{
	int t;
	string gr[3] = { "�������������","������","��������" };
	ofstream fout("users", ios::binary | ios::app);
	auto *buf = new Users;
	bool flag;
	do
	{
		system("cls");
		flag = true;
		cout << "���� ����������� �������������\n";
		cout << "������� ���" << endl;
		cin >> buf->name;
		cout << "������� �������" << endl;
		cin >> buf->surname;
		cout << "������� �����:" << endl;
		cin >> buf->login;
		cout << "������� ������:" << endl;
		cin >> buf->parol;
		cout << "������� ������������� ������������\n���� ��������� ������ ������������� � �� ��������������\n";
		for (int i = 0; i < 3; i++)
		{
			cout << gr[i] << "(" << i + 1 << ")" << "\t";
		}
		cin >> buf->post;
		if (!testlog(buf->login))
			flag = false;
		else if (!testpass(buf->parol))
			flag = false;
		else if (buf->post < 1 || buf->post > 3)
		{
			system("cls");
			flag = false;
			cout << "������ ����� ��������������." << endl;
		}
		if (flag)
		{
			system("cls");
			cout << "���:" << buf->name << endl << "�������: " << buf->surname << endl << "�����: " << buf->login << endl << "������: " << buf->parol << endl << "��� ������������: " << gr[buf->post - 1] << endl;
			cout << "��� ������������� ������� 1, ��� ������� ����� ������ ������� 0." << endl << ">>";
			cin >> t;
			if (t != 1)
				flag = false;
		}
	} while (!flag);
	system("cls");
	Lusers.push_back(*buf);
	fout.write((char*)buf, sizeof(*buf));
	system("cls");
	cout << "����������� ������ �������!" << endl;
	fout.close();
}

void read()
{
	ifstream users("users", ios::binary | ios::app);
	auto *buf = new Users;
	users.seekg(0);
	while (!users.eof())
	{
		users.read((char*)buf, sizeof(*buf));
		Lusers.push_back(*buf);
	}
	Lusers.pop_back();
	users.close();
}

string login()
{
	string login = "adm", parol;
	bool flag = true;
	cout << "���� �����������\n";
	int k = 0;
	do
	{
		for (auto lusers : Lusers)
			if (lusers.post == 1)
			{
				k++;
				break;
			}
		if (k == 0)
		{
			cout << "������� ������ �������������� �� �������.\n��� ���������� ������ ���������� �� �������.\n";
			system("pause");
			system("cls");
			register_1();
		}
		else
		{
			string mas[3] = { "�������������","������","��������" };
			cout << "������� �����:" << endl;
			cin >> login;
			cout << "������� ������:" << endl;
			cin >> parol;
			system("cls");
			for (auto lusers : Lusers)
			{
				if (login == lusers.login && parol == lusers.parol)
				{
					firstName = lusers.name;
					//cout << "���� � ������� ��������. " << mas[lusers.post - 1] << " <" << login << ">" << endl;
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				cout << "����� ��� ������ ������� �������.\n��������� ���� ������ ���� ���������� � ��������������.\n" << endl;
				system("pause");
				system("cls");
			}
		}
	} while (flag == true || k == 0);
	return login;
}

bool testlog(string login)
{
	int sizestr;
	bool flag = 1;
	sizestr = login.size();
	for (int i = 0; i < sizestr; i++)
	{
		if ((login[i] >= 'A' && login[i] <= 'Z') || (login[i] >= 'a' && login[i] <= 'z') || (login[i] >= '0' && login[i] <= '9') || (login[i] == '-' || login[i] == '_'))
			;
		else
		{
			system("cls");
			cout << "������������ ������� ��� ����� ������\n";
			flag = 0;
			system("pause");
			break;
		}
	}
	if (sizestr < 6 || sizestr > 14)
	{
		system("cls");
		cout << "������������ ����� ������.\n����� ������ ���� �� ����� 6 � �� ����� 14 ��������\n";
		flag = 0;
		system("pause");
		return flag;
	}
	for (auto lusers : Lusers)
		if (lusers.login == login)
		{
			cout << "����� ����� ��� ����������!" << endl;
			flag = 0;
			system("pause");
		}
	return flag;
}

bool testpass(string parol)
{
	int sizestr;
	bool flag = 1;
	sizestr = parol.size();
	for (int i = 0; i < sizestr; i++)
	{
		if ((parol[i] >= 'A' && parol[i] <= 'Z') || (parol[i] >= 'a' && parol[i] <= 'z') || (parol[i] >= '0' && parol[i] <= '9'))
			;
		else
		{
			system("cls");
			cout << "������������ ������� ��� ����� ������\n";
			flag = 0;
			system("pause");
			break;
		}
	}
	if (sizestr < 6 || sizestr > 14)
	{
		system("cls");
		cout << "������������ ����� ������.\n����� ������ ������ ���� �� ����� 6 � �� ����� 14 ��������\n";
		flag = 0;
		system("pause");
	}
	return flag;
}

int setgroup(string login)
{
	int group;
	for (auto lusers : Lusers)
		if (lusers.login == login)
		{
			group = lusers.post;
			break;
		}
	return group;
}

void account(void)
{

	int t;
	cout << "���������� ����������" << endl;
	cout << "1. ������� ������� ������������.\n2. �������������� ���������.\n3. ������� �������.\n4. ���������� ���� ������������� �������.\n5. ��������� � ���������� ����� ����." << endl;
	cin >> t;
	if (t >= 1 && t <= 4)
		acc[t - 1]();
	else if (t == 5);
	else
	{
		cout << "������ �������� ����� ����" << endl;
		system("pause");
	}
}

void ttrain(void)
{
	int k;
	cout << "���������� ������� �������" << endl;
	cout << "1. ������� ������ �������\n2. ������� ����� �� �������\n3. ������������� ���������� ������\n4. �������� �����\n5. ��������� � ���������� ����� ����." << endl;
	cin >> k;
	system("cls");
	if (k >= 1 && k <= 4)
	{
		mtrain[k - 1]();
	}
	else if (k == 5);
	else
	{
		cout << "������ �������������� ����� ����" << endl;
		system("pause");
	}

}

void mtimetable()
{
	system("cls");
	int k;
	cout << "���� ���������� �����������" << endl;
	cout << "1. �������� ����� ����\n2. ������� ����\n3. ���������� ���������� � ������ \n4. ��������� � ���������� ����� ����" << endl;
	cin >> k;
	system("cls");
	if (k >= 1 && k <= 3)
		mttable[k - 1]();
	else if (k == 4);
	else
	{
		cout << "�������� ����� ����" << endl;
		system("pause");
	}
}

void sale(void)
{
	bool buf1 = false;
	auto *buffer = new ticket;
	bool bflag, fl2 = false;
	string buf, date, Name, Surname, Pass;
	fstream ticket("tickets", ios::binary | ios::app);
	cout << "������� ������" << endl;
	do
	{
		for (auto list : actTimetable)
		{
			buf1 = true;
			break;
		}
		if (!buf1)
			break;
		bflag = true;
		int k;
		cout << "�������� ����� ������ ��� ���������� ������" << endl;
		infoTimetable();
		cin >> buf;
		cout << "������� ���� �����������" << endl;
		date = pushDate1();
		bflag = testDate(date);
		if (!bflag);
		else
			for (std::list<timetable>::iterator table = actTimetable.begin(); table != actTimetable.end(); ++table)
				if (table->train == buf && table->date1 == date)
				{
					buffer->ntrain = buf;
					buffer->date = date;
					cout << "������� ��� ���������" << endl;
					cin >> buffer->name;
					cout << "������� ������� ���������" << endl;
					cin >> buffer->surname;
					cout << "������� ����� �������� ���������" << endl;
					cin >> buffer->pass;
					if (!checkPass(buffer->pass))
					{
						cout << "������� ������ ����� ��������!" << endl;
						bflag = false;
						system("pause");
						break;
					}
					else
						cout << "�������� ��� ������:\n1. ���������(" << table->mestEko << " ���� ��������)\n2. �������(" << table->mestKomf << " ���� ��������)" << endl;
					cin >> k;
					if (k == 1)
					{
						buffer->type = "���������";
						buffer->cost = table->costEco;
						table->mestEko--;
					}
					else if (k == 2)
					{
						buffer->type = "����������";
						buffer->cost = table->costKomf;
						table->mestKomf--;
					}
					else
					{
						cout << "������� ������ ��� ������. ���������� ������ ��� ������ �����." << endl;
						bflag = false;
						system("pause");
						break;
					}
					fl2 = true;
				}
	} while (!bflag);
	if (!buf1)
		cout << "����������� ���������� �������" << endl;
	else if (fl2 == false)
	{
		cout << "����������� ����� �� ������� ����" << endl;
	}
	else
	{
		tickets.push_back(*buffer);
		ticket.write((char*)buffer, sizeof(*buffer));
		cout << "����� ��������!" << endl;
	}
	ticket.close();
	system("pause");
	rewTimetable();
}

void readTicket()
{
	bool first = true;
	auto *buffer = new ticket;
	fstream ticket("tickets", ios::binary | ios::in);
	while (ticket)
	{
		ticket.read((char*)buffer, sizeof(*buffer));
		tickets.push_back(*buffer);
		first = false;
	}
	if (!first)
		tickets.pop_back();
	ticket.close();
}

void coutTicket()
{
	for (auto buf : tickets)
		cout << buf.name << " " << buf.surname << ", ����������� " << buf.date << ", ����� ���� " << buf.type << ", ��������� ������: " << buf.cost << ", ����� " << buf.ntrain << endl;
	system("pause");
}

void refund(void)
{

	string num, date, family, pass;
	cout << "������� ������" << endl;
	coutTicket();
	cout << "������� ����� ������" << endl;
	cin >> num;
	cout << "������� ���� �����������" << endl;
	date = pushDate1();
	cout << "������� ������� ���������" << endl;
	cin >> family;
	cout << "������� ����� �������� ���������" << endl;
	cin >> pass;
	for (std::list<ticket>::iterator it = tickets.begin(); it != tickets.end(); ++it)
		if (it->ntrain == num && it->date == date && it->surname == family && it->pass == pass)
		{
			for (std::list<timetable>::iterator i1 = actTimetable.begin(); i1 != actTimetable.end(); ++i1)
			{
				if (i1->train == num && i1->date1 == date)
				{
					if (it->type == "���������")
						i1->mestEko++;
					else i1->mestKomf++;
					break;
				}
			}
			cout << "����� ������� ����������. � �������� " << it->cost << endl;
			it = tickets.erase(it);
			system("pause");
			rewTimetable();
			rewTickets();
			break;
		}
}

void rewTickets()
{
	fstream tick("tickets", ios::binary | ios::out);
	for (auto Ticket : tickets)
		tick.write((char*)&Ticket, sizeof(Ticket));
	tick.close();
}

void reference(void)
{
	cout << "�������" << endl;

}

void logout(void)
{
	cout << "������� ������������" << endl;
	flag = false;
}

void about(void)
{
	cout << "� ���������" << endl;
	cout << "������ ��������� �������� ����������� ������������������ ��������� �������." << endl;
	cout << "���� ��������� �������: �������������� ������� ���������������� �������." << endl;
	cout << "�������� ������� ������ ��17-09�, �������� ������. ����� �������� ������: 031722010." << endl;
	system("pause");
	system("cls");
}

void quit(void)
{
	cout << "���������� ���������" << endl;
	flagmain = false;
}

void infoTimetable(void)
{
	bool bflag = false;
	string buf,city1,city2;
	int c1, c2;
	int i = 1;
	cout << "������ �������" << endl;
	for (auto train : lst_train)
		cout << "����� " << train.name << " " << train.city1 << " - " << train.city2 << endl;
	cout << "�������� �����:" << endl;
	cin >> buf;
	system("cls");
	for (auto train : lst_train)
	{
		if (train.name == buf)
		{
			city1 = train.city1;
			city2 = train.city2;
			c1 = train.costEco;
			c2 = train.costComf;
			bflag = true;
			break;
		}
	}
	cout << "����� " << buf << ", ������� ����������: " << city1 << "-" << city2 << endl;
	if(bflag)
		cout << "��������� ���������� ������ : " << c1 << ", ��������� ����������� ������: " << c2 << endl << endl;
	bflag = false;
	for (auto table : actTimetable)
		if (table.train == buf )
		{
			cout<< "����������� " << table.date1 << " � " << table.time << endl << endl;
			bflag = true;
		}
	if (!bflag)
		cout << "������ ����� �� �������� � ����������!" << endl;
	system("pause");
}

void createTimetable()
{
	bool k, buf1;
	do
	{
		k = false;
		buf1 = false;
		for (auto list : lst_train)
		{
			buf1 = true;
			break;
		}
		if (!buf1)
		{
			cout << "����������� ������ �������" << endl;
			system("pause");
			break;
		}
		string bufNum;
		timetable *buffer = new timetable;
		buffer->mestKomf = 0;
		buffer->mestEko = 0;
		fstream schedule("timetable.bin", ios::binary | ios::app);
		cout << "������� ����� ������" << endl;
		coutTrain();
		cin >> bufNum;
		for (auto Train : lst_train)
			if (Train.name == bufNum)
			{
				vag_list* lst = Train.vagons;
				for (vag_list::iterator i2 = lst->begin(); i2 != lst->end(); i2++)
					if (i2->type == "������")
						buffer->mestEko = buffer->mestEko + 45;
					else if (i2->type == "�������")
						buffer->mestKomf = buffer->mestKomf + 30;
				buffer->costEco = Train.costEco;
				buffer->costKomf = Train.costComf;
				buffer->city1 = Train.city1;
				buffer->city2 = Train.city2;
				k = true;
				break;
			}
		if (!k)
			cout << "����� � ������ ������� �����������" << endl;
		else
		{
			buffer->train = bufNum;
			cout << "���� �����������:" << endl;
			buffer->date1 = pushDate1();
			bool fl = testDate(buffer->date1);
			cout << "����� �����������:" << endl;
			buffer->time = pushDate2();
			if (fl)
			{
				int k, p;
				schedule.write((char*)buffer, sizeof(*buffer));//������ ������ ���� � ����
				actTimetable.push_back(*buffer);
				cout << "������� ���������� �����, �� ������� ���������� ��������� ����������" << endl;
				cin >> k;
				cout << "������� ������������� �������� ������" << endl;
				cin >> p;
				for (int i = 0; i < k - 1; i++)
				{
					buffer->date1 = GetTableDate(buffer->date1, p);
					schedule.write((char*)buffer, sizeof(*buffer));
					actTimetable.push_back(*buffer);
				}
			}
		}
	} while (!k);
}

void readTimetable()
{
	bool first = true;
	timetable *buffer = new timetable;
	fstream schedule("timetable.bin", ios::binary | ios::in);
	while (schedule)
	{
		schedule.read((char*)buffer, sizeof(*buffer));
		actTimetable.push_back(*buffer);
		first = false;
	}
	if (!first)
	{
		actTimetable.pop_back();
	}
	schedule.close();
}

void deleteTimetable()
{
	string buf1, buf2;
	cout << "������� ����� ������ ��� �������� �� ����������:" << endl;
	infoTimetable();
	cin >> buf1;
	system("cls");
	cout << "������� ���� ��� �������� ��������" << endl;
	buf2 = pushDate1();
	for (std::list<timetable>::iterator it = actTimetable.begin(); it != actTimetable.end(); ++it)
		if (it->train == buf1 && it->date1 == buf2)
		{
			it = actTimetable.erase(it);
			cout << "����� �� ��������� ���� ������� ������ �� ����������" << endl;
			rewTimetable();
			break;
		}
		else cout << "� ���������� ����������� ����� " << buf1 << " �� " << buf2 << endl;
	system("pause");
}

void rewTimetable()
{
	fstream timetable("timetable.bin", ios::binary | ios::out);
	for (auto table : actTimetable)
		timetable.write((char*)&table, sizeof(table));
	timetable.close();
}

void editAccount()
{
	bool fl = 0;
	system("cls");
	string buf, buf2;
	coutUser();
	cout << "������� ����� ������������ ��� ����������� ��������������:" << endl;
	cin >> buf;
	for (std::list<Users>::iterator it = Lusers.begin(); it != Lusers.end(); ++it)
		if (it->login == buf)
		{
			int p, buf;
			cout << "�������� ������, ������� ���������� ��������:" << endl;
			cout << "1. �����\n2. ������\n3. ������ ������������" << endl;
			cin >> p;
			switch (p)
			{
			case 1:
			{
				do
				{
					system("cls");
					cout << "������� ����� �����" << endl;
					cin >> buf2;
				} while (!testlog(buf2));
				it->login = buf2;
				rewriteUser();
				break;
			}
			case 2:
			{
				do
				{
					system("cls");
					cout << "������� ����� ������" << endl;
					cin >> buf2;
				} while (!testpass(buf2));
				it->parol = buf2;
				rewriteUser();
				break;
			}
			case 3:
			{
				do
				{
					system("cls");
					cout << "������� ������ ������������" << endl;
					cin >> buf;
				} while (buf < 1 && buf>3);
				it->post = buf;
				rewriteUser();
				break;
			}
			default:
			{
				cout << "������" << endl;
				system("pause");
			}
			}
			fl = true;
			break;
		}
	if (!fl)
		cout << "������ �������������� �����!" << endl;
}

void rewriteUser()
{
	fstream users("users", ios::binary | ios::out);
	for (auto lusers : Lusers)
		users.write((char*)&lusers, sizeof(lusers));
	users.close();
}

void coutUser()
{
	cout << "�����" << setw(25) << "�������, ���" << endl;
	for (auto lusers : Lusers)
		cout << lusers.login << setw(15) << lusers.surname << " " << lusers.name << endl;
	system("pause");
}

void deleteAccount()
{
	system("cls");
	bool fl = false;
	string login;
	coutUser();
	cout << "������� ����� ������������ ��� ��������" << endl;
	cin >> login;
	for (std::list<Users>::iterator it = Lusers.begin(); it != Lusers.end(); ++it)
	{
		if (it->login == login)
		{
			it = Lusers.erase(it);
			fl = true;
			rewriteUser();
			break;
		}
	}
	if (!fl)
		cout << "������ �������������� �����" << endl;
}

void readTrain()
{
	ifstream out("trains", ios::binary | ios::app);
	out.seekg(0);
	train *tmp_R = new train;
	while (!out.eof())
	{
		tmp_R->vagons = new vag_list();
		out.read((char*)&tmp_R->name, sizeof(tmp_R->name));
		out.read((char*)&tmp_R->city1, sizeof(tmp_R->city1));
		out.read((char*)&tmp_R->city2, sizeof(tmp_R->city2));
		out.read((char*)&tmp_R->c_vagons, sizeof(tmp_R->c_vagons));
		out.read((char*)&tmp_R->costEco, sizeof(tmp_R->costEco));
		out.read((char*)&tmp_R->costComf, sizeof(tmp_R->costComf));
		for (int i = 1; i <= tmp_R->c_vagons; i++)
		{
			vag *tmp_B = new vag;
			out.read((char*)&tmp_B->type, sizeof(tmp_B->type));
			out.read((char*)&tmp_B->mesta, sizeof(tmp_B->mesta));
			out.read((char*)&tmp_B->cost, sizeof(tmp_B->cost));
			tmp_R->vagons->push_back(*tmp_B);
		}
		lst_train.push_back(*tmp_R);
	}
	lst_train.pop_back();
}

void init_trains()
{
	int  k, num = 1;
	bool buf = true;
	system("cls");
	fstream out("trains", ios::binary | ios::app);
	train *tmp_R = new train;

	tmp_R->vagons = new vag_list();

	cout << "��� ������" << endl;
	cin >> tmp_R->name;
	for (auto tr : lst_train)
		if (tmp_R->name == tr.name)
		{
			buf = false;
			cout << "����� � ����� ��������� ��� ����������" << endl;
			system("pause");
			break;
		}
	if (buf)
	{
		out.write((char*)&tmp_R->name, sizeof(tmp_R->name));
		cout << "����� �����������" << endl;
		cin >> tmp_R->city1;
		out.write((char*)&tmp_R->city1, sizeof(tmp_R->city1));
		cout << "����� ��������" << endl;
		cin >> tmp_R->city2;
		out.write((char*)&tmp_R->city2, sizeof(tmp_R->city2));
		cout << "������� ���������� �������" << endl;
		cin >> tmp_R->c_vagons;
		cout << "������� ��������� ������� � ������ ���� ������" << endl;
		cin >> tmp_R->costEco;
		cout << "������� ��������� ������� � ������ ���� �������" << endl;
		cin >> tmp_R->costComf;
		out.write((char*)&tmp_R->c_vagons, sizeof(tmp_R->c_vagons));
		out.write((char*)&tmp_R->costEco, sizeof(tmp_R->costEco));
		out.write((char*)&tmp_R->costComf, sizeof(tmp_R->costComf));
		for (int i = 1; i <= tmp_R->c_vagons; i++)
		{
			vag *tmp_B = new vag;
			cout << "�������� ��� ������ #" << num << "\n1. ���������\n2. ����������" << endl;
			cin >> k;
			switch (k)
			{
			case 1:
			{
				tmp_B->type = "������";
				tmp_B->mesta = 45;
				tmp_B->cost = tmp_R->costEco;
				break;
			}
			case 2:
			{
				tmp_B->type = "�������";
				tmp_B->mesta = 30;
				tmp_B->cost = tmp_R->costComf;
				break;
			}
			default:
			{
				cout << "err" << endl;
			}
			}
			out.write((char*)&tmp_B->type, sizeof(tmp_B->type));
			out.write((char*)&tmp_B->mesta, sizeof(tmp_B->mesta));
			out.write((char*)&tmp_B->cost, sizeof(tmp_B->cost));
			tmp_R->vagons->push_back(*tmp_B);
			num++;
		}
		lst_train.push_back(*tmp_R);
	}
	out.close();
}

void coutTrain()
{
	cout << "������ �������:" << endl;
	for (list<train>::iterator i1 = lst_train.begin(); i1 != lst_train.end(); i1++)
	{
		cout << "����� ";
		cout << i1->name << " " << i1->city1 << "-" << i1->city2 << " ������: " << endl;
		vag_list* lst = i1->vagons;
		for (vag_list::iterator i2 = lst->begin(); i2 != lst->end(); i2++)
		{
			cout << "����� ���� " << i2->type << ", ��������� " << i2->cost << ", ���������� ���� - " << i2->mesta << endl;
		}
		cout << endl;
	}
	system("pause");
}

void rewtrain()
{
	fstream trains("trains", ios::binary | ios::out);
	for (list<train>::iterator i1 = lst_train.begin(); i1 != lst_train.end(); i1++)
	{
		trains.write((char*)&i1->name, sizeof(i1->name));
		trains.write((char*)&i1->city1, sizeof(i1->city1));
		trains.write((char*)&i1->city2, sizeof(i1->city2));
		trains.write((char*)&i1->c_vagons, sizeof(i1->c_vagons));
		trains.write((char*)&i1->costEco, sizeof(i1->costEco));
		trains.write((char*)&i1->costComf, sizeof(i1->costComf));
		vag_list* lst = i1->vagons;
		for (vag_list::iterator i2 = lst->begin(); i2 != lst->end(); i2++)
		{
			trains.write((char*)&i2->type, sizeof(i2->type));
			trains.write((char*)&i2->mesta, sizeof(i2->mesta));
			trains.write((char*)&i2->cost, sizeof(i2->cost));
		}
	}
	trains.close();
}

void delTrain()
{
	//system("cls");
	bool bflag = false;
	string buf;
	cout << "������� ����� ������ ��� ��������" << endl;
	coutTrain();
	cin >> buf;
	system("cls");
	for (list<train>::iterator i1 = lst_train.begin(); i1 != lst_train.end(); i1++)
		if (i1->name == buf)
		{
			i1 = lst_train.erase(i1);
			bflag = true;
			break;
		}
	system("cls");
	if (!bflag)
		cout << "������ �������������� ����� ������!" << endl;
	else
	{
		cout << "����� ������� ������!" << endl;
		rewtrain();
	}
	system("pause");
}

void editTrain()
{
	//system("cls");
	bool bflag = false;
	string buf;
	cout << "������� ����� ������ ��� ����������� ��������������" << endl;
	coutTrain();
	cin >> buf;
	for (list<train>::iterator i1 = lst_train.begin(); i1 != lst_train.end(); i1++)
		if (i1->name == buf)
		{
			int k;
			string buf;
			cout << "1 �������� ��������  2. �������� ����� 1  3. �������� ����� 2 4 �������� ����� " << endl;
			cin >> k;
			switch (k)
			{
			case 1:
			{
				cout << "������� ����� ��� ��� ������" << endl;
				cin >> buf;
				i1->name = buf;
				break;
			}
			case 2:
			{
				cout << "������� ����� ����� �����������" << endl;
				cin >> buf;
				i1->city1 = buf;
				break;
			}
			case 3:
			{
				cout << "������� ����� ����� ��������" << endl;
				cin >> buf;
				i1->city2 = buf;
				break;
			}
			case 4:
			{
				i1->c_vagons = i1->c_vagons + 1;
				vag *tmp_B = new vag;
				cout << "������� ��� ������" << endl;
				cin >> tmp_B->type;
				cout << "������� ���������� ���� � ������" << endl;
				cin >> tmp_B->mesta;
				cout << "������� ��������� ������� � ������ ������� ���� �� ������ ������" << endl;
				cin >> tmp_B->cost;
				i1->vagons->push_back(*tmp_B);
				break;
			}
			default:
			{
				cout << "������ �������� ����� ����!" << endl;
			}
			}
			bflag = true;
		}
	if (!bflag)
		cout << "������ �������������� ����� ������!" << endl;
	else
	{
		cout << "����� ������� ��������������" << endl;
		rewtrain();
	}
	system("pause");
}

string pushDate1()
{
	int x, y;
	bool fmonth = false, fdate = false;
	int date, month;
	string syear, fulldate;
	cout << "������� ���" << endl;
	cin >> syear;
	while (!fmonth)
	{
		cout << "������� ����� ������" << endl;
		cin >> month;
		if (month >= 1 && month <= 12)
		{
			fmonth = true;
		}
	}
	x = month;
	y = 28 + (x + x / 8) % 2 + 2 % x + 1 / x * 2;
	while (!fdate)
	{
		cout << "������� ���� ������" << endl;
		cin >> date;
		if (date > 0 && date <= y)
			fdate = true;
	}

	auto smonth = to_string(month);
	if (month >= 1 && month <= 9)
		smonth = '0' + smonth;
	auto sdate = to_string(date);
	if (date >= 1 && date <= 9)
		sdate = '0' + sdate;
	fulldate = sdate + "." + smonth + "." + syear;
	return fulldate;
}

string pushDate2()
{
	int  hours, min;
	string fulldate;
	bool  fh = false, fm = false;
	while (!fh)
	{
		cout << "������� ����" << endl;
		cin >> hours;
		if (hours >= 0 && hours <= 23)
			fh = true;
	}
	while (!fm)
	{
		cout << "������� ������" << endl;
		cin >> min;
		if (min >= 0 && min <= 59)
			fm = true;
	}

	auto shours = to_string(hours);
	auto smin = to_string(min);
	if (min <= 9)
		smin = "0" + smin;
	fulldate = shours + ":" + smin;
	return fulldate;
}

bool testDate(string str1)
{
	int bufd, bufm, bufy;
	bool flag;
	SYSTEMTIME st;
	GetSystemTime(&st);
	bufd = atoi(str1.substr(0, 2).c_str());
	bufm = atoi(str1.substr(3, 2).c_str());
	bufy = atoi(str1.substr(6, 4).c_str());
	int d1 = bufd + bufm * 31 + bufy * 365;
	int d2 = st.wDay + st.wMonth * 31 + st.wYear * 365;//������� ����
	if (d1 >= d2)
		flag = true;
	else
	{
		flag = false;
		cout << "���� ������� �����������!" << endl;
		system("pause");
	}
	return flag;
}

bool checkPass(string pass)
{
	int size;
	size = pass.size();
	bool flag = true;
	for (int i = 0; i < size; i++)
		if (pass[i] >= '0' && pass[i] <= '9')
			;
		else
		{
			flag = false;
			break;
		}
	if (size != 6)
		flag = false;
	return flag;
}

string GetTableDate(string date, int addDays)
{
	int bufd, bufm, bufy, days;
	bufd = atoi(date.substr(0, 2).c_str());
	bufm = atoi(date.substr(3, 2).c_str());
	bufy = atoi(date.substr(6, 4).c_str());
	days = 28 + (bufm + bufm / 8) % 2 + 2 % bufm + 1 / bufm * 2;
	for (int i = 0; i < addDays; i++) {

		if (++bufd > days) {
			bufd = 1;
			bufm++;
		}
		if (bufm > 12) {
			bufm = 1;
			bufy++;
		}
	}
	auto smonth = to_string(bufm);
	if (bufm >= 1 && bufm <= 9)
		smonth = '0' + smonth;
	auto sdate = to_string(bufd);
	if (bufd >= 1 && bufd <= 9)
		sdate = '0' + sdate;
	auto syear = to_string(bufy);
	auto fulldate = sdate + "." + smonth + "." + syear;
	return fulldate;
}