#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>


using namespace std;
namespace fs = std::filesystem;

class User {
    string _name;
    string _login;
    string _pass;

public:
    User(string l, string p, string n):_name(n), _pass(p), _login(l){}
    friend fstream& operator>>(fstream& is, User& user);
    friend ofstream& operator<<(ofstream& os, User& user);
    void show() { cout << _name << ' ' << _login << ' ' << _pass << endl; }
 
};
class Message {
    string _text;
    string _sender;
    string _receiver;

public:
    Message(string t, string s, string r) :_text(t), _receiver(r), _sender(s) {}
    friend fstream& operator>>(fstream& is, Message& mes);
    friend ofstream& operator<<(ofstream& os, Message& mes);
    void show() { cout << _text << ' ' << _receiver << ' ' << _sender << endl; }
};

fstream& operator>>(fstream& is, User& user) {
    is >> user._name;
    is >> user._login;
    is >> user._pass;
    return is;
}
ofstream& operator<<(ofstream& os, User& user) {
    os <<user._name;
    os << ' ';
    os << user._login;
    os << ' ';
    os << user._pass;
    os << endl;

    return os;
}

fstream& operator>>(fstream& is, Message& mes) {
    is >> mes._text;
    is >> mes._receiver;
    is >> mes._sender;

    return is;
}
ofstream& operator<<(ofstream& os, Message& mes) {
    os << mes._text;
    os << ' ';
    os << mes._receiver;
    os << ' ';
    os << mes._sender;
    os << endl;

    return os;
}

int main()
{////////////////////////user//////////////////////
    std::cout << "User section\n";
    ofstream fs("user.txt");
    fs::permissions("user.txt", fs::perms::others_read | fs::perms::others_write, fs::perm_options::remove);
    User user("alex", "rev", "test");
    fs << user;
    fs.close();
    fstream is("user.txt", ios::in);
    User user2("a", "r", "t");
    cout << "original user" << endl;
    user2.show();
    cout << "after import user" << endl;
    is >> user2;
    user2.show();
    is.close();

    cout << "_______________________________________" << endl;
    ////////////////////////message//////////////////////
    
    std::cout << "Message section\n";
    ofstream fsm("message.txt");
    fs::permissions("message.txt", fs::perms::others_read | fs::perms::others_write, fs::perm_options::remove);
    Message mess("hello", "alex", "vad");
    fsm << mess;
    fsm.close();

    fstream ism("message.txt", ios::in);
    Message mess2("t", "t", "t");
    cout << "original message" << endl;
    mess2.show();
    cout << "after import message" << endl;
    ism >> mess2;
    mess2.show();
    ism.close();

    
}