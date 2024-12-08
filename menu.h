#pragma once
#include <iostream>
#include <vector>
#include <string>

int choice, output, input, slt;
std::string login, pass, name, message;
bool enable, readed, alls;

class Accounts {
    protected:
        std::string _login, _pass, _name;
        bool _enable;
        int _id;
    public:
        Accounts(int id, std::string login, std::string pass, std::string name, bool enable);
        ~Accounts();

        const int GetID() const;
        const std::string GetLogin() const;
        const std::string GetPass() const;
        const std::string GetName() const;
        const bool GetEnable() const;

        const std::string GetUserData() const;

        void SetLogin(std::string login);
        void SetPass(std::string pass);
        void SetName(std::string name);
        void SetEnable(bool enable);
};

class SettingAccounts {
    protected:
        Accounts* acc;
    public:
        SettingAccounts();
        ~SettingAccounts();
        std::vector<std::vector<Accounts>> AccBase;

        bool RegistrationUser(std::string login, std::string pass, std::string name, bool enable);
        bool CheckAccounts();
        bool Logining(std::string login, std::string pass);

        int SearchByLogin(std::string login);
        int SearchByName(std::string name);
        std::string SearchByID(int id);
        bool EnableAccountSearch(int id);

        bool SearchID(int id); 

        void BlockAccount(int id);
        void UnblockAccount(int id);
        void ShowAllAccount();
        void ShowAllIDName();
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

        bool NewMailAllAccounts(int output, std::string message, int input, bool alls);
        bool NewMailOneAccount(int output, std::string message, int input, bool alls);
        
        void ShowAllMail();
        void ShowOneMail(int ouput, int input);
};

void Menu();
