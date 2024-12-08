# Рабочая версия кода.

> Разработка велась на ОС debian 12.5 в среде разработки Visual Studio Code при поддержке компилятора gcc\g++

### Что за что отвечает

Menu.h
``` cplus
#pragma once
#include <iostream>
#include <vector>
#include <string>

 /*Глобальный параметры*/
int choice, output, input, slt; 
std::string login, pass, name, message;
bool enable, readed, alls;
/*---------------------*/

/*Класс пользователей*/
class Accounts {
    protected:
        std::string _login, _pass, _name; //Логин, пароль, имя пользователей
        bool _enable; //Доступность пользователя 
        int _id; //Порядковый номер пользователя. Выдаётся автоматически в зависимости от размерности vector<vector<Accounts>> accBase;
    public:
        Accounts(int id, std::string login, std::string pass, std::string name, bool enable);
        ~Accounts();

        /*Геттеры для получения данных о конкретном пользователе*/
        const int GetID() const; // получить id пользователя
        const std::string GetLogin() const; // получить логин пользователя
        const std::string GetPass() const; // получить пароль пользователя
        const std::string GetName() const; // получить имя пользователя
        const bool GetEnable() const; // получить доступность пользователя
        /*------------------------------------------------------*/

        // Получение сведений по каждому пользователю без его id и без доступности пользователя
        const std::string GetUserData() const;

        /*Сеттеры для получения данных о конкретном пользователе*/
        void SetLogin(std::string login); // изменить логин пользователя
        void SetPass(std::string pass); // изменить пароль пользователя
        void SetName(std::string name); // изменить имя пользователя
        void SetEnable(bool enable); // изменить статус доступности пользователя
        /*-----------------------------------------------------*/
};

//Класс базы пользователей
class SettingAccounts {
    protected:
        Accounts* acc; // подключение класса пользователей, чтобы было проще работать с ним
    public:
        SettingAccounts();
        ~SettingAccounts();
        std::vector<std::vector<Accounts>> AccBase; // Своеобразная база данных пользователей

        bool RegistrationUser(std::string login, std::string pass, std::string name, bool enable); // Регистрация пользователей в базе
        bool CheckAccounts(); // Проверка на наличие и доступность пользователя
        bool Logining(std::string login, std::string pass); // Для входа в программу с проверкой доступности пользователя

        int SearchByLogin(std::string login); // Поиск id пользователя по его логину
        int SearchByName(std::string name); // Поиск id пользователя по его имени
        std::string SearchByID(int id); // Поиск имени пользователя по его id
        bool EnableAccountSearch(int id); // Проверка доступности пользователя из базы (не был подключен к работе программы)

        bool SearchID(int id); // Поиск id пользователя

        void BlockAccount(int id); // Блок пользователя, чтобы заблокировать доступ к чату
        void UnblockAccount(int id); // Разблокировка пользователя, чтобы вернуть доступ к чату
        void ShowAllAccount(); // Показ всех пользователей программы
        void ShowAllIDName(); // Показ всех id и имён пользователей (реализован для выбора кому написать сообщение)
};

class Mail {
    protected:
        int _output, _input; // переменные отпровителя и получателя
        bool _alls; // является общим чатом или нет
        std::string _message; // сообщение

    public:
        Mail(int output, std::string message, int input, bool alls);
        ~Mail();
        
        const int GetOutput() const; // возвращение данных отправителя
        const int GetInput() const; // возвращение данных получателя
        const std::string GetMessage() const; // возвращение сообщения
        const bool GetAlls() const; // возвращение статуса, общее сообщение или нет
};

class Mails {
    protected:
        Mail* mail; // Подключение класса Mail
    public:
        Mails();
        ~Mails();
        std::vector<std::vector<Mail>> MailBase; // Своеобразная база данных сообщений

        bool NewMailAllAccounts(int output, std::string message, int input, bool alls); // отправка сообщения всем
        bool NewMailOneAccount(int output, std::string message, int input, bool alls); // отправка сообщения конкретному пользователю
        
        void ShowAllMail(); // показ сообщений из общего чата (почему-то сообщения дублируются, возможно, из-за того, что там пользователя 2 создаю для проверки и показывает сообщения для обоих).
        void ShowOneMail(int ouput, int input); // показ сообщений для конкретного пользователя (так и не разобрался почему сообщение дублируется, и как подставить данные другого пользователя, когда заходишь не под отправителем)
};

void Menu();
```

Menu.cpp реализация данного чата
``` cplus
#include "Menu.h"
#include <limits>

SettingAccounts sa;
Mails mls;

void Menu() {
    std::cout << "Wellcome to the chat!" << std::endl;

    while(true) {
        while (true) {
            std::cout << "Choice options: " << std::endl;
            std::cout << "1 - Login in chat" << std::endl;
            std::cout << "2 - Add with account" << std::endl;
            std::cout << "3 - View all account in program" << std::endl;
            std::cout << "4 - Ban account in program" << std::endl;
            std::cout << "5 - Unban account in program" << std::endl;
            std::cout << "0 - Exit program" << std::endl << std::endl;
            std::cin >> choice;
            std::cout << std::endl;
            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), 'n');
                std::cout << "Please, only numeric word" << std::endl << std::endl;
            }
            else {
                break;
            }
        }

        if(choice == 1) {
            if(sa.CheckAccounts()) std::cout << "Not user in program" << std::endl << std::endl;
            else {
                std::cout << "Enter login account: ";
                std::cin >> login;

                std::cout << "\nEnter password account: ";
                std::cin >> pass;

                sa.Logining(login, pass);
                std::cout << std::endl;

                output = sa.SearchByLogin(login);

                if (output > 0) 
                    while(true) {
                        while (true) {
                            std::cout << "Ure choice: " << std::endl;
                            std::cout << "1 - Send message all" << std::endl;
                            std::cout << "2 - Send message one person" << std::endl;
                            std::cout << "3 - Open chat alls" << std::endl;
                            std::cout << "4 - Open chat one person" << std::endl;
                            std::cout << "5 - Rebind login" << std::endl;
                            std::cout << "6 - Rebind password" << std::endl;
                            std::cout << "7 - Rebind name" << std::endl;
                            std::cout << "0 - Exit" << std::endl;
                            
                            std::cin >> choice;
                            std::cout << std::endl;
                            if(std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), 'n');
                                std::cout << "Please, only numeric word" << std::endl << std::endl;
                            }
                            else {
                                break;
                            }
                        }

                        if(choice == 1) {
                            std::cout << "Enter all chat" << std::endl << std::endl;
                            
                            std::string message;
                            std::cout << "Enter message: " << std::endl;
                            std::cin >> message;

                            for(auto& ac : sa.AccBase)
                                for(Accounts& acc : ac) {
                                        input = acc.GetID();
                                        mls.NewMailAllAccounts(output, message, input, true);
                                }
                        }
                        else if(choice == 2) {
                            std::cout << "Select the account to send to by Name" << std::endl;
                            sa.ShowAllIDName();
                            std::string cls;
                            std::cin >> cls;
                            std::cout << "Enter ure message for " << cls << std::endl << std::endl;
                            std::cin >> message;

                            mls.NewMailOneAccount(output, message, sa.SearchByName(cls), false);
                        }
                        else if(choice == 3) {
                            std::cout << "Enter all's chat" << std::endl;
                            mls.ShowAllMail();
                            std::cout << std::endl;
                        }
                        else if(choice == 4) {
                            std::cout << "Select name whose chat open" << std::endl;
                            sa.ShowAllIDName();

                            std::string cls;
                            std::cin >> cls;
                            //int la = sa.SearchByName(cls);
                            for(auto& _mail : mls.MailBase)
                                for(Mail& mail : _mail) {
                                    if(output == mail.GetOutput() && sa.SearchByName(cls) == mail.GetInput()) {
                                        mls.ShowOneMail(output, sa.SearchByName(cls));
                                        break;
                                    }
                                    else if(output == mail.GetInput() && sa.SearchByName(cls) == mail.GetOutput()) {
                                        mls.ShowOneMail(sa.SearchByName(cls), output);
                                        break;
                                    }
                                }
                        }
                        else if(choice == 5) {
                            std::cout << "Enter new login" << std::endl;
                            std::string text;
                            std::cin >> text;

                            for(auto& ac : sa.AccBase)
                                for(Accounts& acc : ac)
                                    if(acc.GetID() == output)
                                        acc.SetLogin(text);
                            break;
                        }
                        else if(choice == 6) {
                            std::cout << "Enter new password" << std::endl;
                            std::string text;
                            std::cin >> text;

                            for(auto& ac : sa.AccBase)
                                for(Accounts& acc : ac)
                                    if(acc.GetID() == output)
                                        acc.SetPass(text);
                            break;
                        }
                        else if(choice == 7) {
                            std::cout << "Enter new name" << std::endl;
                            std::string text;
                            std::cin >> text;

                            for(auto& ac : sa.AccBase)
                                for(Accounts& acc : ac)
                                    if(acc.GetID() == output)
                                        acc.SetName(text);
                        }
                        else if(choice == 0) break;
                        else std::cout << "Is not option in this number" << std::endl << std::endl;
                    }
            }
        }
        else if(choice == 2) {
            std::cout << "Enter login for new account: ";
            std::cin >> login;

            std::cout << "\nEnter password for new account: ";
            std::cin >> pass;

            std::cout << "\nEnter name for new account: ";
            std::cin >> name;

            enable = true;

            sa.RegistrationUser(login, pass, name, enable);
        }
        else if(choice == 3) sa.ShowAllAccount();
        else if(choice == 4) {
            if(sa.CheckAccounts()) std::cout << "Not user in program" << std::endl << std::endl;
            else {
                std::cout << "Enter name account for ban: ";
                std::cin >> name;
                sa.BlockAccount(sa.SearchByName(name));
                std::cout << std::endl << std::endl;
            }
        }
        else if(choice == 5) {
            if(sa.CheckAccounts()) std::cout << "Not user in program" << std::endl << std::endl;
            else {
                std::cout << "Enter name account for unban: ";
                std::cin >> name;
                sa.UnblockAccount(sa.SearchByName(name));
                std::cout << std::endl << std::endl;
            }
        }
        else if(choice == 0) break;
        else std::cout << "This option not yet" << std::endl << std::endl;
    }
}

Accounts::Accounts(int id, std::string login, std::string pass, std::string name, bool enable) :
_id(id), _login(login), _pass(pass), _name(name), _enable(enable) { }
Accounts::~Accounts() {
    _id = 0;
    _login = "";
    _pass = "";
    _name = "";
    _enable = false;
}

const int Accounts::GetID() const { return _id; }
const std::string Accounts::GetLogin() const { return _login; }
const std::string Accounts::GetPass() const { return _pass; }
const std::string Accounts::GetName() const { return _name; }
const bool Accounts::GetEnable() const { return _enable; }
const std::string Accounts::GetUserData() const { return "Login: " + _login + " Pass: " + _pass + " Name: " + _name; }

void Accounts::SetLogin(std::string login) { _login = login; }
void Accounts::SetPass(std::string pass) { _pass = pass; }
void Accounts::SetName(std::string name) { _name = name; }
void Accounts::SetEnable(bool enable) { _enable = enable; }

SettingAccounts::SettingAccounts() { }
SettingAccounts::~SettingAccounts() { }

bool SettingAccounts::RegistrationUser(std::string login, std::string pass, std::string name, bool enable) {
    for(auto& ac : AccBase)
        for(Accounts& acc : ac)
            if(login == acc.GetLogin()) {
                std::cout << "\nErorr add's user!\nThis user added in program earlier";
                return false;
            }

    int id = AccBase.size() + 1;
    AccBase.push_back({Accounts(id, login, pass, name, enable)});
    std::cout << "\nUser add in program.\n\n";
    return true;
}
bool SettingAccounts::CheckAccounts() {
    if(AccBase.empty()) return true;
    else return false;
}
bool SettingAccounts::Logining(std::string login, std::string pass) {
    for(auto& ac : AccBase)
        for(Accounts& acc : ac)
            if(acc.GetLogin() == login &&
                acc.GetPass() == pass && 
                acc.GetEnable()) {
                    std::cout << "Entered in program\n\n";
                    return true;
                }
    std::cout << "\nLogin or pass is incorrect, \nor user is deactivated\n\n";
    return false;
}

int SettingAccounts::SearchByLogin(std::string login) {
    for(auto& ac : AccBase)
        for(Accounts& acc : ac)
            if(login == acc.GetLogin())
                return acc.GetID();
    return 0;
}
int SettingAccounts::SearchByName(std::string name) {
    for(auto& ac : AccBase)
        for(Accounts& acc : ac)
            if(name == acc.GetName())
                return acc.GetID();
    return 0;
}
std::string SettingAccounts::SearchByID(int id) {
    for(auto& ac : AccBase)
        for(Accounts& acc : ac)
            if(id == acc.GetID())
                return acc.GetName();
    return "";
}

bool SettingAccounts::EnableAccountSearch(int id) {
    for(auto& ac : sa.AccBase)
        for(Accounts& acc : ac) {
            if(acc.GetID() == id)
                if(acc.GetEnable())
                    return true;
        }
    return false;
}

bool SettingAccounts::SearchID(int id) {
    for(auto& ac : AccBase)
        for(Accounts& acc : ac){
            if(id == acc.GetID()) return true;
            else return false;
        }
    return false;
}

void SettingAccounts::BlockAccount(int id) {
    if(sa.CheckAccounts()) std::cout << "User search error\n\n";
    else {
        for(auto& ac : AccBase)
            for(Accounts& acc : ac) {
                if(id == acc.GetID()) acc.SetEnable(false);
                else std::cout << "User search error\n\n";
            }
    }
}
void SettingAccounts::UnblockAccount(int id) {
    if(sa.CheckAccounts()) std::cout << "User search error\n\n";
    else {
        for(auto& ac : AccBase)
            for(Accounts& acc : ac) {
                if(id == acc.GetID()) acc.SetEnable(true);
                else std::cout << "User search error\n\n";
            }
    }
}

void SettingAccounts::ShowAllAccount() {
    if(sa.CheckAccounts())
        std::cout << "Zero accounts in program now.\nPlease add users and try again repeat later\n\n";
    else {
        std::cout << "All account in program: \n";
        for(auto& ac : AccBase)
            for(Accounts& acc : ac) {
                if(acc.GetEnable())
                    std::cout << acc.GetUserData() + "\n";
                else
                    std::cout << "Banned (" + acc.GetUserData() + ")\n";
            }
    }
    std::cout << std::endl;
}

void SettingAccounts::ShowAllIDName() {
    if(sa.CheckAccounts())
        std::cout << "Zero accounts in program now.\nPlease add users and try again repeat later\n\n";
    else {
        std::cout << "All account in program: \n";
        for(auto& ac : AccBase)
            for(Accounts& acc : ac) {
                if(acc.GetEnable())
                    std::cout << acc.GetName() << std::endl;
                else
                    std::cout << std::endl;
            }
    }
}

Mail::Mail(int output, std::string message, int input, bool alls) :
    _output(output), _message(message), _input(input), _alls(alls) { }
Mail::~Mail() { }

const int Mail::GetOutput() const { return _output; }
const int Mail::GetInput() const { return _input; }
const std::string Mail::GetMessage() const { return _message; }
const bool Mail::GetAlls() const { return _alls; }

Mails::Mails() { }
Mails::~Mails() { }

bool Mails::NewMailAllAccounts(int output, std::string message, int input, bool alls) {
    MailBase.push_back({Mail(output, message, input, alls)});
    return true;
}
bool Mails::NewMailOneAccount(int output, std::string message, int input, bool alls) {
    MailBase.push_back({Mail(output, message, input, alls)});
    return true;
}

void Mails::ShowAllMail() {
    for(auto& _mail : mls.MailBase)
        for(Mail& mail : _mail)
            if(mail.GetAlls()) {
                std::cout << "Output: " << sa.SearchByID(mail.GetOutput()) << " message: " << mail.GetMessage() << std::endl;
                // int output;
                // for(auto& ac : sa.AccBase)
                //     for(Accounts& acc : ac) {
                //         output = acc.GetID();
                //     }
            }
}

void Mails::ShowOneMail(int output, int input) {
    for(auto& _mail : mls.MailBase)
        for(Mail& mail : _mail)
            if(!mail.GetAlls()) {
                std::cout << "Output: " << sa.SearchByID(output) << " Message: " << mail.GetMessage() << " Input: " << sa.SearchByID(input) << std::endl; 
                // for(auto& ac : sa.AccBase)
                //     for(Accounts& acc : ac)
                //         if(mail.GetOutput() == acc.GetID() && mail.GetInput() == acc.GetID()) {
                                
                //         }
            }
}
```
