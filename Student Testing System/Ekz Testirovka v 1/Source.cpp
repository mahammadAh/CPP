#include<iostream>
#include<vector>
#include<Windows.h>
#include<fstream>
#include<string>


// Стурктура для хранение инфомарции о пользователях (Гостях и Администраторе )
struct UserData {
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string login;
	std::string password;
	std::vector<std::pair<int, int>> marks;  // Первый элемент пары хранит номер теста , второй элемент хранит оценку пользователя по данному тесту
	std::vector<std::pair<int, int>> promitions;  // Первый элемент пары хранит номер теста , второй элемент хранит прогресс пользователя по данному тесту

};

// Класс позволяющий зарегстрировать Администратора , а так же гостей
class  UserCl {
public:
	void CheckInUser(std::string& name, std::string& surname, std::string& patronymic, // Метод позволяющий регестрировать пользователя
		std::string& login, std::string& password) {
		UserData* copy_user = new UserData[user_size + 1];
		for (int i = 0; i < user_size; i++) {
			copy_user[i].name = user[i].name;
			copy_user[i].surname = user[i].surname;
			copy_user[i].patronymic= user[i].patronymic;
			copy_user[i].login= user[i].login;
			copy_user[i].password = user[i].password;
			copy_user[i].marks.swap(user[i].marks);
			copy_user[i].promitions.swap(user[i].promitions);
			
		}

		copy_user[user_size].name = name;
		copy_user[user_size].surname = surname;
		copy_user[user_size].patronymic = patronymic;
		copy_user[user_size].login = login;
		copy_user[user_size].password = password;

		delete[]user;
		user = copy_user;
		user_size++;

	} 

	void DeleteUser(int num) {
		UserData* copy_user = new UserData[user_size- 1 ];
		for (int i = 0, j=0; i < user_size; i++ , j++) {
			if (i == num ) {
				i++;
			}
			if (i < user_size) {
				copy_user[j].name = user[i].name;
				copy_user[j].surname = user[i].surname;
				copy_user[j].patronymic = user[i].patronymic;
				copy_user[j].login = user[i].login;
				copy_user[j].password = user[i].password;
				copy_user[j].marks.swap(user[i].marks);
				copy_user[j].promitions.swap(user[i].promitions);
			}
		}
		delete[]user;
		user = copy_user;
		user_size--;
	}


	void CheckInAdmin(std::string& name, std::string& surname, std::string& patronymic, // Специальный метод для одноразового регестрирования администратора
		std::string& login, std::string& password) {
		 admin.name = name;
		 admin.surname = surname;
		 admin.patronymic = patronymic;
		 admin.login = login;
		 admin.password = password;
	}

	UserData*& GetUser() {
		return user;
	}

	UserData& GetAdmin() {
		return admin;
	}

	size_t& GetUserSize() {
		return user_size;
	}

private:
	UserData* user = nullptr;
	UserData admin;
	size_t user_size = 0;

};

// Структура для храние тестов 
struct TestData {
	std::string question;
	std::string option1;
	std::string option2;
	std::string option3;
	std::string option4;
	size_t ansewer;
};

// Класс позволяющий создать тесты по одной теме
class CreateTest {
public:

	void TestName(std::string& test_name) {
		this->test_name = test_name;
	}

	
	void Create(std::string& question, std::string& option1, std::string& option2,
	std::string& option3, std::string& option4, size_t& ansewer) {
		TestData* copy_test = new TestData[test_size + 1];
		for (int i = 0; i < test_size; i++) {
			copy_test[i].question = test[i].question;
			copy_test[i].option1 = test[i].option1;
			copy_test[i].option2 = test[i].option2;
			copy_test[i].option3 = test[i].option3;
			copy_test[i].option4 = test[i].option4;
			copy_test[i].ansewer = test[i].ansewer;
		}

		copy_test[test_size].question = question;
		copy_test[test_size].option1 = option1;
		copy_test[test_size].option2 = option2;
		copy_test[test_size].option3 = option3;
		copy_test[test_size].option4 = option4;
		copy_test[test_size].ansewer = ansewer;

		delete[] test;
		test = copy_test;
		test_size++;
		
	}

	void SetTest( TestData*& test) {
		this->test = test;
	}

	void SetTestSize(const size_t& test_size) {
		this->test_size = test_size;
	}

	void SetTestName( const std::string& test_name) {
		this->test_name = test_name;
	}

	TestData*& GetTest() {
		return test;
	}

	size_t GetTestSize() {
		return test_size;
	}

	std::string& GetTestName() {
		return test_name;
	}

private:
	TestData* test= nullptr;
	size_t test_size = 0;
	std::string test_name;

 };

// Класс позволяющий создать разные темы тестов (Например : Математика, География, Русский )
class Tests {
public:
	void NewTest(std::string& test_name) {
		CreateTest* copy_new_test = new CreateTest [new_test_size + 1];
		for (int i = 0; i < new_test_size; i++) {
			copy_new_test[i].SetTest(new_test[i].GetTest());
			copy_new_test[i].SetTestSize(new_test[i].GetTestSize());
			copy_new_test[i].SetTestName(new_test[i].GetTestName());
		}

		copy_new_test[new_test_size].TestName(test_name);
		delete[]new_test;
		new_test = copy_new_test;
		new_test_size++;
	}

	CreateTest*& GetNewTest() {
		return new_test;
	}

	size_t& GetNewTestSize() {
		return new_test_size;
	}

private:
	CreateTest* new_test = nullptr;
	size_t new_test_size = 0;
};



// Функция для шифрования строки 
std::string XOR_Crypt(std::string in, std::string pass)
{
	std::string out;
	for (int x = 0; x < in.length() ; x++)
	{
		out += (char)(in[x] ^ pass[x % pass.length() ]);
	}
	return out;
}



// Функция для чтения из файл информации о администраторе
namespace std {

	bool ReadInFileAdminInformation(UserCl& users) {
		ios::openmode mode = ios::in;
		ifstream read("AdminData.txt", mode);
		string name;
		string surname;
		string patronymic;
		string login;
		string password;
		string password1;
		if (read.is_open()) {
			getline(read, name);
			getline(read, surname);
			getline(read, patronymic);
			getline(read, login);
			getline(read, password1);
			password = XOR_Crypt(password1, "01010101");
			users.CheckInAdmin(name, surname, patronymic, login, password);
			return 0;
		}
		read.close();

		return 1;
	}
	
}

// Функция регестрирующая администратора 
void AdminRegistration(UserCl& users) {

	if (std::ReadInFileAdminInformation(users)) {
		std::cout << "Check In For Admin" << std::endl;
		std::string name;
		std::string surname;
		std::string patronymic;
		std::string login;
		std::string password;
		std::string check_password;

		std::cout << "Enter 0 for Exit" << std::endl << std::endl;

		std::cout << "Enter Name" << std::endl;
		std::getline(std::cin >> std::ws, name);
		if (name[0] == '0' && name.size()==1) { goto ExitAdminRegistration; }

		std::cout << "Enter Surname" << std::endl;
		std::getline(std::cin >> std::ws, surname);
		if (surname[0] == '0'&& surname.size()==1) { goto ExitAdminRegistration; }

		std::cout << "Enter Patronymic" << std::endl;
		std::getline(std::cin >> std::ws, patronymic);
		if (patronymic[0] == '0'&& patronymic.size()==1) { goto ExitAdminRegistration; }

		std::cout << "Enter Login" << std::endl;
		std::cin >> login;
		if (login[0] == '0' && login.size()==1) { goto ExitAdminRegistration; }
		bool work = true;

		while (work) {

			std::cout << "Enter Password" << std::endl;
			std::cin >> password;
			if (password[0] == '0' && password.size()==1) { goto ExitAdminRegistration; }
			std::cout << "Return Password" << std::endl;
			std::cin >> check_password;
			if (check_password[0] == '0' && check_password.size()==1) { goto ExitAdminRegistration; }

			if (password == check_password) {
				users.CheckInAdmin(name, surname, patronymic, login, password);
				work = false;
			}
			else {

				std::cout << " Password mismatch. Try again " << std::endl;
			}
		}
	}
ExitAdminRegistration:;
}

// Функция позволяющая войти админу в систему 
int AdminLogin(UserCl& users) {
	std::string login;
	std::string password;
	std::cout << "Enter 0 for Exit" << std::endl << std::endl;

	std::cout << "Enter Login" << std::endl;
	std::cin >> login;

	if (login[0] == '0' && login.size()==1) { goto ExitAdminLogin; }
	std::cout << "Enter Password" << std::endl;
	std::cin >> password;
	if (password[0] == '0' && password.size()==1) { goto ExitAdminLogin; }
	if (users.GetAdmin().login == login && users.GetAdmin().password == password) {
		system("cls");
		std::cout << "Hello " << users.GetAdmin().name << " " << users.GetAdmin().surname << " " << users.GetAdmin().patronymic << std::endl;
		Sleep(1000);
		return 1;
	}
	else {
		std::cout << "Incorrect login or password" << std::endl;
	}
    ExitAdminLogin:;
	return 0;

}

// Функция позволяющая редактировать данные админа 
void AdminModification(UserCl& users) {
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string login;
	std::string password;
	std::string check_password;

	bool work = true;

	while (work) {

		std::cout << "1. Edit Name" << std::endl;
		std::cout << "2. Edit Surname" << std::endl;
		std::cout << "3. Patronymic" << std::endl;
		std::cout << "4. Login" << std::endl;
		std::cout << "5. Password" << std::endl;
		std::cout << "6. Exit" << std::endl;
		int choose;
		std::cin >> choose;
		switch (choose) {
		case 1:
			std::cout << "Enter 0 for Exit" << std::endl << std::endl;
			std::cout << "Enter Name" << std::endl;
			std::getline(std::cin >> std::ws, name);
			if (name[0] == '0' && name.size()==1) { goto ExitAdminModification; }
			users.GetAdmin().name = name;
			break;
		case 2:
			std::cout << "Enter 0 for Exit" << std::endl << std::endl;
			std::cout << "Enter Surname" << std::endl;
			std::getline(std::cin >> std::ws, surname);
			if (surname[0] == '0' && surname.size() == 1) { goto ExitAdminModification; }
			users.GetAdmin().surname = surname;
			break;
		case 3:
			std::cout << "Enter 0 for Exit" << std::endl << std::endl;
			std::cout << "Enter Patronymic" << std::endl;
			std::getline(std::cin >> std::ws, patronymic);
			if (patronymic[0] == '0' && patronymic.size() == 1) { goto ExitAdminModification; }
			users.GetAdmin().patronymic = patronymic;
			break;
		case 4:
			std::cout << "Enter 0 for Exit" << std::endl << std::endl;
			std::cout << "Enter Login " << std::endl;
			std::cin >> login;
			if (login[0] == '0' && login.size() == 1) { goto ExitAdminModification; }
			users.GetAdmin().login = login;
			break;
		case 5:
			std::cout << "Enter 0 for Exit" << std::endl << std::endl;
			std::cout << "Enter Password" << std::endl;
			std::cin >> password;
			if (password[0] == '0' && password.size() == 1) { goto ExitAdminModification; }
			std::cout << "Return Password" << std::endl;
			std::cin >> check_password;
			if (check_password[0] == '0' && check_password.size() == 1) { goto ExitAdminModification; }
			if (password == check_password) {
				users.GetAdmin().password = password;
			}
			else {
				std::cout << "Password mismatch. Try again" << std::endl;
			}

			break;
		case 6:
			work = false;
			break;
		default:
			break;
		}

	}
    ExitAdminModification:;
}




// Функция регестрирующая пользователей 
void UserRegistration(UserCl& users) {
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string login;
	std::string password;
	std::string check_password;
	bool work = true;
	size_t count = 0;
	std::cout << "Enter 0 for Exit" << std::endl << std::endl;

	std::cout << "Enter Name" << std::endl;
	std::getline(std::cin >> std::ws, name);
	if (name[0]=='0' && name.size()==1) {goto ExitUserRegistration; }

	std::cout << "Enter Surname" << std::endl;
	std::getline(std::cin >> std::ws, surname);
	if (surname[0] == '0' && surname.size() == 1) { goto ExitUserRegistration; }

	std::cout << "Enter Patronymic" << std::endl;
	std::getline(std::cin >> std::ws, patronymic);
	if (patronymic[0] == '0' && patronymic.size() == 1) { goto ExitUserRegistration; }

	while (work) {

		std::cout << "Enter Login" << std::endl;
	   
		std::cin >> login;
		if (login[0] == '0' && login.size() == 1) { goto ExitUserRegistration; }
		bool check_login = true;

		for (int i = 0; i < users.GetUserSize(); i++) {
			if (login == users.GetUser()[i].login) {
				check_login = false;
			}
		}

		if (check_login) {
			std::cout << "Enter Password" << std::endl;
			std::cin >> password;
			if (password[0] == '0' && password.size() == 1) { goto ExitUserRegistration; }
			std::cout << "Return Password" << std::endl;
			std::cin >> check_password;
			if (check_password[0] == '0' && check_password.size() == 1) { goto ExitUserRegistration; }
			if (password == check_password) {
				users.CheckInUser(name, surname, patronymic, login, password);

				work = false;
			}
			else {
				count++;
				std::cout << " Password mismatch. Try again " << std::endl;
			}

		}

		else {
			std::cout << " This login is busy . Try again " << std::endl;
			count++;
		}

		if (count > 5) {
			work = false;
		}
	}

  ExitUserRegistration:;
}


// Функиця позволяющая пользователям сойти в систему 
int UserLogin(UserCl& users) {

	std::string login;
	std::string password;
	std::cout << "Enter 0 for Exit" << std::endl<<std::endl;
	std::cout << "Enter Login" << std::endl;
	std::cin >> login;
	if (login[0] == '0' && login.size()==1) { goto ExitUserLogin; }
	std::cout << "Enter Password" << std::endl;
	std::cin >> password;
	if (password[0] == '0' && password.size() == 1) { goto ExitUserLogin; }
	for (int i = 0; i < users.GetUserSize(); i++) {

		if (login == users.GetUser()[i].login) {
			if (password == users.GetUser()[i].password) {
				system("cls");
				std::cout << "Hello " << users.GetUser()[i].name << " " << users.GetUser()[i].surname << " " << users.GetUser()[i].patronymic << std::endl;
				Sleep(1000);
				return i;
			}
		}

	}
    ExitUserLogin:;
	std::cout << "Incorrect login or password" << std::endl;
	return -1;

}

// Функция позволяющая редактировать данные пользователей
void UserModification(UserCl& users) {
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string login;
	std::string password;
	std::string check_password;
	std::cout << "Choose User for Modification" << std::endl;
	for (int i = 0; i < users.GetUserSize(); i++) {
		std::cout << i + 1 << users.GetUser()[i].login << std::endl;
	}
	int num;
	std::cin >> num;
	if (num <= users.GetUserSize() ) {
		bool work = true;

		while (work) {
			bool login_check = true;
			std::cout << "1. Edit Name" << std::endl;
			std::cout << "2. Edit Surname" << std::endl;
			std::cout << "3. Patronymic" << std::endl;
			std::cout << "4. Login" << std::endl;
			std::cout << "5. Password" << std::endl;
			std::cout << "6. Exit" << std::endl;
			int choose;
			std::cin >> choose;
			switch (choose) {
			case 1:
				std::cout << "Enter 0 for Exit" << std::endl << std::endl;
				std::cout << "Enter Name" << std::endl;
				std::getline(std::cin >> std::ws, name);
				if (name[0] == '0' && name.size()==1) { goto ExitUserModification; }
				users.GetUser()[num - 1].name = name;
				break;
			case 2:
				std::cout << "Enter 0 for Exit" << std::endl << std::endl;
				std::cout << "Enter Surname" << std::endl;
				std::getline(std::cin >> std::ws, surname);
				if (surname[0] == '0' && surname.size() == 1) { goto ExitUserModification; }
				users.GetUser()[num - 1].surname = surname;
				break;
			case 3:
				std::cout << "Enter 0 for Exit" << std::endl << std::endl;
				std::cout << "Enter Patronymic" << std::endl;
				std::getline(std::cin >> std::ws, patronymic);
				if (patronymic[0] == '0' && patronymic.size() == 1) { goto ExitUserModification; }
				users.GetUser()[num - 1].patronymic = patronymic;
				break;
			case 4:
				std::cout << "Enter 0 for Exit" << std::endl << std::endl;
				std::cout << "Enter Login " << std::endl;
				std::cin >> login;
				if (login[0] == '0'&&  login.size()==1) { goto ExitUserModification; }
				for (int i = 0; i < users.GetUserSize(); i++) {
					if (login == users.GetUser()[i].login) {
						login_check = false;
					}

					if (login_check) {
						users.GetUser()[num - 1].login = login;
					}
					else {
						std::cout << "This login is busy . Try again" << std::endl;
					}

				}
				break;
			case 5:
				std::cout << "Enter 0 for Exit" << std::endl << std::endl;
				std::cout << "Enter Password" << std::endl;
				std::cin >> password;
				if (password[0] == '0' && password.size()==1) { goto ExitUserModification; }
				std::cout << "Return Password" << std::endl;
				std::cin >> check_password;
				if (check_password[0] == '0' && check_password.size() == 1) { goto ExitUserModification; }
				if (password == check_password) {
					users.GetUser()[num - 1].password = password;
				}
				else {
					std::cout << "Password mismatch. Try again" << std::endl;
				}

				break;
			case 6:
				work = false;
				break;
			default:
				break;
			}
		}
	}
	else {
		std::cout << "User does not exist" << std::endl;
		system("pause");
	}
    ExitUserModification:;
}

// Функция для удаления пользователей
void DeleteUser(UserCl& users) {
	std::cout << "Enter 0 for Exit" << std::endl << std::endl;
	std::cout << "Choose User for Delete" << std::endl;
	for (int i = 0; i < users.GetUserSize(); i++) {
		std::cout << i + 1 << " : " << users.GetUser()[i].login << std::endl;
	}
	int num;
	std::cin >> num;
	if (num == 0) { goto ExitDeleteUser; }
	if (num <= users.GetUserSize()) {
		users.DeleteUser(num - 1);
	}
	else {
		std::cout << "User does not exist" << std::endl;
		system("pause");
	}
ExitDeleteUser:;
}

// Функция записывающая оценки для хранения
void UserMark(UserCl& users, int user , int index , int mark) {
	bool add = true;
	for (int i = 0; i < users.GetUser()[user].marks.size(); i++) {
		if (users.GetUser()[user].marks[i].first == index) {
			users.GetUser()[user].marks[i].second = mark;
			add = false;
		}
	}
	if (add) {
		users.GetUser()[user].marks.push_back(std::make_pair(index, mark));
	}
}

// Функция записывающая прогресс для возможности потом продожлить
void UserPromitions(UserCl& users, int user, int index, int promitions) {
	bool add=true;
	for (int i = 0; i < users.GetUser()[user].promitions.size(); i++) {
		if (users.GetUser()[user].promitions[i].first == index) {
			users.GetUser()[user].promitions[i].second = promitions;
			add = false;
		}
	}
	if (add) {
		users.GetUser()[user].promitions.push_back(std::make_pair(index, promitions));
	}
}

// Функция для вывода всех оценок пользователя
void PrintUserMark(UserCl& users, int user) {

	for (int i = 0; i < users.GetUser()[user].marks.size(); i++) {
		if (users.GetUser()[user].marks[i].second < 10000) {
			std::cout << "Test : " << users.GetUser()[user].marks[i].first << std::endl;
			std::cout << "Mark : " << users.GetUser()[user].marks[i].second << std::endl;
		}
	}
}




// Функция для создания тестов по новой теме 
void CreateNewTest(Tests& test) {
	std::cout << "Enter 0 for Exit" << std::endl << std::endl;
	std::string test_name;
	std::cout << "Enter Test Name" << std::endl;
	std::getline(std::cin >> std::ws, test_name);
	if (test_name[0] == '0' && test_name.size()==1) { goto ExitUserModification; }
	test.NewTest(test_name);
	ExitUserModification:;
}

// Функиця для заполнения тестов определенной темы
void FillingOutTests(Tests& test) {
	size_t choose;
	bool work = true;
	std::cout << "Enter 0 for Exit" << std::endl << std::endl;
	std::cout << "Select subject to edit" << std::endl;
	for (int i = 0; i < test.GetNewTestSize(); i++) {
		std::cout << i + 1 << " : " << test.GetNewTest()[i].GetTestName() << std::endl;
	}
	std::cin >> choose;

	if (choose == 0) { goto ExitFillingOutTests; }
	if (choose <= test.GetNewTestSize() ) {
		while (work) {
			std::string question;
			std::string option1;
			std::string option2;
			std::string option3;
			std::string option4;
			size_t ansewer;
			std::cout << "1.Add Question" << std::endl;
			std::cout << "2.Exit" << std::endl;
			int num;
			std::cin >> num;
			switch (num) {
			case 1:
				std::cout << "Enter 0 for Exit" << std::endl << std::endl;
				std::cout << "Question: " << std::endl;
				std::getline(std::cin >> std::ws, question);
				std::cout << " Option 1: " << std::endl;
				std::getline(std::cin >> std::ws, option1);
				std::cout << "Option 2: " << std::endl;
				std::getline(std::cin >> std::ws, option2);
				std::cout << "Option 3: " << std::endl;
				std::getline(std::cin >> std::ws, option3);
				std::cout << "Option 4: " << std::endl;
				std::getline(std::cin >> std::ws, option4);
				std::cout << "Ansewer: " << std::endl;
				std::cin >> ansewer;
				if (ansewer == 0) { goto ExitFillingOutTests; }

				test.GetNewTest()[choose - 1].Create(question, option1, option2, option3, option4, ansewer);
				break;
			case 2:
				work = false;
				break;
			default:
				break;


			}

		}
	}
	else {
		std::cout << "No such test exists" << std::endl;
		system("pause");
	}
    ExitFillingOutTests:;
}

// Функция для работы с тестами
void WorkWithTest(Tests& test, UserCl& users, int user) {
	int num;
	int true_ansewer = 0, choose;
	int mark;
	int indx = 0;
	std::cout << "Enter 0 for Exit" << std::endl << std::endl;
	for (int i = 0; i < test.GetNewTestSize(); i++) {

		std::cout << i + 1 << " : " << test.GetNewTest()[i].GetTestName() << std::endl;

	}
	std::cin >> num;
	if (num == 0) { goto ExitWorkWithTest; }
	
	if (num <= test.GetNewTestSize()) {

		for (int i = 0; i < users.GetUser()[user].marks.size(); i++) { // Цикл проверяющий и выкачиюващий оценкци пользователя по данному тесту
			if (users.GetUser()[user].marks[i].first == num) {
				if (users.GetUser()[user].marks[i].second >= 10000) {
					true_ansewer = users.GetUser()[user].marks[i].second / 10000;
				}
			}
		}

		for (int j = 0; j < users.GetUser()[user].promitions.size(); j++) {  // Цикл проверяющий и выкачиюващий прогресс пользователя по данному тесту

			if (users.GetUser()[user].promitions[j].first == num) {
				indx = users.GetUser()[user].promitions[j].second;
			}

		}
		system("cls");


		for (indx; indx < test.GetNewTest()[num - 1].GetTestSize(); indx++) {

			std::cout << "0. EXIT " << std::endl;
			std::cout << test.GetNewTest()[num - 1].GetTest()[indx].question << std::endl;
			std::cout << " 1 : " << test.GetNewTest()[num - 1].GetTest()[indx].option1 << std::endl;
			std::cout << " 2 : " << test.GetNewTest()[num - 1].GetTest()[indx].option2 << std::endl;
			std::cout << " 3 : " << test.GetNewTest()[num - 1].GetTest()[indx].option3 << std::endl;
			std::cout << " 4 : " << test.GetNewTest()[num - 1].GetTest()[indx].option4 << std::endl;
			std::cout << "Your ansewer : ";
			std::cin >> choose;

			if (test.GetNewTest()[num - 1].GetTest()[indx].ansewer == choose)
			{
				true_ansewer++;
			}

			else if (choose == 0) {
				break;
			}
			system("cls");

		}
		if (indx == test.GetNewTest()[num - 1].GetTestSize()) {
			mark = ((true_ansewer * 12) / test.GetNewTest()[num - 1].GetTestSize());
			std::cout << "Correct Ansewers : " << true_ansewer << std::endl;
			std::cout << "Incorrect Ansewers : " << test.GetNewTest()[num - 1].GetTestSize() - true_ansewer << std::endl;
			std::cout << "Interest : " << ((true_ansewer * 100) / test.GetNewTest()[num - 1].GetTestSize()) << " %" << std::endl;
			std::cout << " 12 ball scale " << mark << std::endl;
			indx = 0;
			UserPromitions(users, user, num, indx);
			UserMark(users, user, num, mark);
			system("pause");
		}
		else {
			UserPromitions(users, user, num, indx);
			UserMark(users, user, num, true_ansewer * 10000);
		}
	}
	else {
		std::cout << "No such test exists" << std::endl;
		system("pause");
	}

    ExitWorkWithTest:;

}


// Функции для записи данных в файлы 
namespace std {

	// Функция для записи в файл информации о администраторе
	void WriteToFileAdminInformation(UserCl& users) {
		ios::openmode mode = ios::trunc | ios::out;
		ofstream write("AdminData.txt", mode);
		string password = XOR_Crypt(users.GetAdmin().password, "01010101");

		if (write.is_open()) {	
				write << users.GetAdmin().name << endl;
				write << users.GetAdmin().surname << endl;
				write << users.GetAdmin().patronymic << endl;
				write << users.GetAdmin().login << endl;
				write << password << endl;

			
		}
		write.close();
	}
	// Функция для записи в файл информации о пользователе
	void WriteToFileUserInformation(UserCl& users) {
		ios::openmode mode = ios::trunc | ios::out;
		ofstream write("UserData.txt", mode); 
		if (write.is_open()) {
			write << users.GetUserSize() << endl;
			for (int i = 0; i < users.GetUserSize(); i++) {
				write << users.GetUser()[i].name << endl;
				write << users.GetUser()[i].surname << endl;
				write << users.GetUser()[i].patronymic << endl;
				write << users.GetUser()[i].login << endl;
				write<< XOR_Crypt(users.GetUser()[i].password, "01010101")<<endl;
			}
		}
		write.close();
	}
	// Функция для записи в файл информации о тестах
	void WriteToFileTestInformation(Tests& test) {
		ios::openmode mode = ios::trunc | ios::out;
		ofstream write("TestData.txt", mode);
		if (write.is_open()) {
			write << test.GetNewTestSize() << endl;
			for (int i = 0; i < test.GetNewTestSize(); i++) {
				write << test.GetNewTest()[i].GetTestSize() << endl;
				write << test.GetNewTest()[i].GetTestName() << endl;
				for (int j = 0; j < test.GetNewTest()[i].GetTestSize(); j++) {
					write << test.GetNewTest()[i].GetTest()[j].question << endl;
					write << test.GetNewTest()[i].GetTest()[j].option1 << endl;
					write << test.GetNewTest()[i].GetTest()[j].option2 << endl;
					write << test.GetNewTest()[i].GetTest()[j].option3 << endl;
					write << test.GetNewTest()[i].GetTest()[j].option4 << endl;
					write << test.GetNewTest()[i].GetTest()[j].ansewer << endl;
				}
			}
		}
		write.close();
	}

	// Функция для записи в файл информации о прогрессе пользователей (оценки и моменты остановки )
	void WriteToFileProgressInformation(UserCl& users) {
		ios::openmode mode = ios::trunc | ios::out;
		ofstream write("ProgressData.txt", mode);
		if (write.is_open()) {
			write << users.GetUserSize() << endl;
			for (int i = 0; i < users.GetUserSize(); i++) {
				write << users.GetUser()[i].marks.size() << endl;
				for (int j = 0; j < users.GetUser()[i].marks.size(); j++) {
					write << users.GetUser()[i].marks[j].first << endl;
					write << users.GetUser()[i].marks[j].second << endl;
					write << users.GetUser()[i].promitions[j].first << endl;
					write << users.GetUser()[i].promitions[j].second << endl;
				}
			}
		}
		write.close();
	}

	
	// Функция для чтения из файл информации о пользователях
	void ReadInFileUserInformation(UserCl& users) {
		ios::openmode mode = ios::in;
		ifstream read("UserData.txt", mode);
		size_t size1;
		string size;
		string name;
		string surname;
		string patronymic;
		string login;
		string password;
		string password_crpt;
		if (read.is_open()) {
			getline(read, size);
			size1 = atoi(size.c_str());
			for (int i = 0; i < size1; i++) {
				getline(read, name);
				getline(read, surname);
				getline(read, patronymic);
				getline(read, login);
				getline(read, password_crpt);
				password = XOR_Crypt(password_crpt, "01010101");
				users.CheckInUser(name, surname, patronymic, login, password);
			}
		}
		read.close();
	}
	// Функция для чтения из файл информации о тестах
	void ReadInFileTestInformation(Tests& test) {
		ios::openmode mode = ios::in;
		ifstream read("TestData.txt", mode);
		size_t size1;
		size_t size2;
		string size_1;
		string size_2;
		string test_name;
		string question;
		string option1;
		string option2;
		string option3;
		string option4;
		string ansewer1;
		size_t ansewer;
		if (read.is_open()) {
			getline(read, size_1);
			size1 = atoi(size_1.c_str());
			for (int i = 0; i < size1; i++) {
				getline(read, size_2);
				size2 = atoi(size_2.c_str());
				getline(read, test_name);
				test.NewTest(test_name);
				for (int j = 0; j < size2; j++) {
					getline(read, question);
					getline(read, option1);
					getline(read, option2);
					getline(read, option3);
					getline(read, option4);
					getline(read, ansewer1);
					ansewer = atoi(ansewer1.c_str());
					test.GetNewTest()[i].Create(question, option1, option2, option3, option4, ansewer);
				}
			}
		}
		read.close();
	}
	// Функция для чтения из файл информации  о прогрессе пользователей (оценки и моменты остановки )
	void ReadInProgressInformation(UserCl& users) {
		ios::openmode mode = ios::in;
		ifstream read("ProgressData.txt", mode);
		size_t size1;
		size_t size2;
		string size_1;
		string size_2;
		string index1;
		string index2;
		string mark1;
		string promitions1;
		int index;
		int index_2;
		int mark;
		int promitions;
		if (read.is_open()) {
			getline(read, size_1);
			size1 = atoi(size_1.c_str());
			for (int i = 0; i < size1; i++) {
				getline(read, size_2);
				size2 = atoi(size_2.c_str());
				for (int j = 0; j < size2; j++) {
					getline(read, index1);
					getline(read, mark1);
					index = atoi(index1.c_str());
					mark = atoi(mark1.c_str());
					getline(read, index2);
					getline(read, promitions1);
					index_2 = atoi(index2.c_str());
					promitions = atoi(promitions1.c_str());
					users.GetUser()[i].marks.push_back(make_pair(index, mark));
					users.GetUser()[i].promitions.push_back(make_pair(index_2, promitions));

				}
			}
		}
		read.close();
	}
}




// Функция с меню для администратора 
void MenuAdmin(UserCl& users, Tests& test ) {
	int fun_return_admin;
	int menu;
	bool menu_work = true;
	fun_return_admin = AdminLogin(users);
	
		if (fun_return_admin) {
			while (menu_work) {
			system("cls");
			std::cout << "1.Edit admin data" << std::endl;
			std::cout << "2.Create User" << std::endl;
			std::cout << "3.Delete User" << std::endl;
			std::cout << "4.Modification User" << std::endl;
			std::cout << "5.Information about tests" << std::endl;
			std::cout << "6.Create test topic" << std::endl;
			std::cout << "7.Add question in test" << std::endl;
			std::cout << "8.Exit" << std::endl;
			std::cin >> menu;

			switch (menu) {
			case 1:
				
				system("cls");
				AdminModification(users);
				break;
			case 2:
				system("cls");
				UserRegistration(users);
				break;
			case 3:
				system("cls");
				DeleteUser(users);
				break;
			case 4:
				system("cls");
				UserModification(users);
				break;
			case 5:
				system("cls");
				for (int i = 0; i < users.GetUserSize(); i++) {
					std::cout << "User " << i + 1 << std::endl;
					PrintUserMark(users, i);
				}
				system("pause");
				break;
			case 6:
				system("cls");
				CreateNewTest(test);
				break;
			case 7:
				system("cls");
				FillingOutTests(test);
				break;
			case 8:
				menu_work = false;
				break;
			default:
				break;


			}




		}

	}
}

//Функция с меню для пользователя 
void MenuUser(UserCl& users, Tests& test) {
	int  fun_return_users;
	int menu;
	bool menu_work = true;
	fun_return_users = UserLogin(users);
	system("cls");
	while (menu_work) {
		if (fun_return_users >= 0) {
			system("cls");
			std::cout << "1.Start Test" << std::endl;
			std::cout << "2.Previous results" << std::endl;
			std::cout << "3.Exit" << std::endl;
			std::cin >> menu;
			switch (menu) {
			case 1:
				system("cls");
				WorkWithTest(test, users, fun_return_users);
				break;
			case 2:
				PrintUserMark(users, fun_return_users);
				system("cls");
				break;
			case 3:
				menu_work = false;
				break;

			}


		}
	}
}



// Функция с главным меню
void Application() {
	UserCl users;
	Tests test;
	std::ReadInFileUserInformation(users);
	std::ReadInFileTestInformation(test);
	std::ReadInProgressInformation(users);
	bool menu_work = true;
	int menu;
	AdminRegistration(users);
	system("cls");

	while (menu_work) {
		system("cls");
		std::cout << "1. Admin Login" << std::endl;
		std::cout << "2. User Login" << std::endl;
		std::cout << "3. User registration" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cin >> menu;

		switch (menu) {

		case 1:			  
			system("cls");
			MenuAdmin(users, test );
			
			break;
		case 2:
			system("cls");
			MenuUser(users, test );
			
			break;
		case 3:
			system("cls");
			UserRegistration(users);
			
			break;
		case 4:
			menu_work = false;
			break;


		}



	}
	std::WriteToFileAdminInformation(users);
	std::WriteToFileUserInformation(users);
	std::WriteToFileTestInformation(test);
	std::WriteToFileProgressInformation(users);
}



int main() {
	Application();
}