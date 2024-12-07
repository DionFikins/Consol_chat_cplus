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
        int _output, _input;
        bool _alls;
        std::string _message;

    public:
        Mail(int output, std::string message, int input, bool alls);
        ~Mail();
        
        const int GetOutput() const;
        const int GetInput() const;
        const std::string GetMessage() const;
        const bool GetAlls() const;
};

class Mails {
    protected:
        Mail* mail;
    public:
        Mails();
        ~Mails();
        std::vector<std::vector<Mail>> MailBase;

        void NewMailAllAccounts(int output, std::string message, int input, bool alls);
        void NewMailOneAccount(int output, std::string message, int input, bool alls);
        
        void ShowAllMail();
        void ShowOneMail();
};

void Menu();
```
