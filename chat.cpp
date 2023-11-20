/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

char input() {
    string temp("-");
    const char* bi = "Bad input";
    cin >> temp;
    if (
        temp[0] != 'l'
        && temp[0] != 'c'
        && temp[0] != 's'
        && temp[0] != 'a'
        && temp[0] != 'm'
        && temp[0] != 'i'
        && temp[0] != 'o'
        && temp[0] != 't'
        && temp[0] != 'L'
        && temp[0] != 'C'
        && temp[0] != 'S'
        && temp[0] != 'A'
        && temp[0] != 'M'
        && temp[0] != 'I'
        && temp[0] != 'O'
        && temp[0] != 'T'
        )
        throw bi;
    else return temp[0];
}

char input_yn() {
    string temp("-");
    const char* bi = "Bad input";
    cin >> temp;
    if (temp[0] != 'y' && temp[0] != 'n' && temp[0] != 'Y' && temp[0] != 'N')
        throw bi;
    else return temp[0];
}

bool input_ex() {
    char ch = '-';
    bool exit = 0;
    cout << "<<<<<Press Y to choose again or N to EXIT>>>>>" << endl;
    try { ch = input_yn(); }
    catch (const char* ex) { cout << ex << endl; ch = 'y'; }
    switch (ch)
    {
    case 'y': case 'Y': exit = true; break;
    case 'n': case 'N': exit = false; break;
    default:
        break;
    }
    return exit;
}

class Msg {
    //Message class
    friend ostream& operator<< (ostream& out, const Msg& msg);
    int id = 0;
    string body;
    string sender;

public:
    Msg() :body("-") { id++; };
    Msg(string msg) :body(msg) { id++; };
    //Methods
    string show() { return body; }
    void set_sender(string s) { sender=s; }
    string get_sender() { return sender; }
    
    Msg& operator=(const Msg& other) {
        this->body = other.body;
        this->sender = other.sender;
        return *this;
    }

    Msg(const Msg& other) {
        this->body = other.body;
        this->sender = other.sender;
    }

};

ostream& operator<< (ostream & out, const Msg & msg) {
    out << msg.body;
    return out;
}

class User {
    string name="";
    string pass="";
    int uId = 0;
    int imsg = 0;
    int omsg = 0;
    int tsize = 100;
    Msg* iarr=nullptr;
    Msg* oarr=nullptr;
public:
    User() :name("no_name"), pass("no_pass") {
        iarr = new Msg[tsize];
        oarr = new Msg[tsize];
    }
    User(string name, string pass) :name(name), pass(pass) {
        iarr = new Msg[tsize];
        oarr = new Msg[tsize];
    }

    string get_name() { return name; }
    string get_pass() { return name; }

    void recieve(Msg msg) {
            //cout << "recieve_called" << endl;
        if (imsg < tsize) {
            //cout << "enter_condition" << endl;
            iarr[imsg] = msg;
            //cout << "assigment compleat" << endl;
            imsg++;
            //return true;
        }

        //else throw "out of range";
        //return false;
    }


    bool send(Msg msg) {
        if (omsg < tsize) {
            oarr[omsg] = msg;
            cout<<"Sent added"<<endl;
            omsg++;
            return true;
        }

        //else throw "out of range";
        return false;
    }
    void get_imsg() {
        cout << "<<<<Incomeing messages>>>>>" << endl;
        int tmp = omsg;
        if (imsg == 0) { cout << "You got no Incomeing messages" << endl; }
        else { cout << "Message - " << iarr[tmp - 1].show() << "||Sender - " << iarr[tmp- 1].get_sender() << endl; }
    }
    void get_omsg() { 
        cout << "<<<<<Sent messages>>>>>" << endl;
        int tmp = omsg;
        if (omsg == 0) { cout << "You got no Sent messages" << endl; }
        else { cout << "Message - " << oarr[tmp - 1].show() << "||Sender - " << oarr[tmp - 1].get_sender() << endl; }
    }

    void show_all() {
        cout << "Incomeing messages" << endl;
        if (imsg == 0) { cout << "You got no Incomeing messages" << endl;}
        else {
            for (int i = 0; i < imsg; i++) {
                cout << "Message - " << iarr[i].show() << "||Sender - " << iarr[i].get_sender() << endl;;
            }
        }
        cout << endl << "Sent messages" << endl;
        if (omsg == 0) { cout << "You got no Sent messages" << endl; }
        else {
            for (int i = 0; i < omsg; i++) {
                cout << "Message - " << oarr[i].show() << "||Sender - " << oarr[i].get_sender() << endl;
            }
        }
    }

    User(const User& other) {
        this->name = other.name;
        this->pass = other.pass;
        this->imsg = other.imsg;
        this->omsg = other.omsg;
        this->tsize = other.tsize;
        this->iarr = new Msg[other.tsize];
        this->oarr = new Msg[other.tsize];
        for (int i = 0; i < other.tsize; i++) {
            this->iarr[i] = other.iarr[i];
        }
        for (int i = 0; i < other.tsize; i++) {
            this->oarr[i] = other.oarr[i];
        }
    }
    

    User& operator=(const User& other) {
        this->name = other.name;
        this->pass = other.pass;
        this->imsg = other.imsg;
        this->omsg = other.omsg;
        this->tsize = other.tsize;
        delete[]this->iarr;
        delete[]this->oarr;
        this->iarr = new Msg[other.tsize];
        this->oarr = new Msg[other.tsize];
        for (int i = 0; i < other.imsg; i++) {
            this->iarr[i] = other.iarr[i];
        }
        for (int i = 0; i < other.omsg; i++) {
            this->oarr[i] = other.oarr[i];
        }

        return *this;
    }

    ~User() {
        delete[]iarr; delete[]oarr;
    }
    };

class Db {
    size_t size = 0;
    size_t count = 0;
    shared_ptr<User[]> arr;
    
public:
    Db() :size(100),arr(new User[size]){
        //arr = (User*)malloc(size * sizeof(User));
        //arr = new User[size];
    }

    Db(size_t size) :size(size), arr(new User[size]) {
        //arr = (User*)malloc(size * sizeof(User));
        //arr = new User[size];
    }
    size_t get_size(){ return size; }
    User& operator[](int n) { return arr[n]; }

    bool add(User user) {
        if (count < size) {
            //new(arr + count)User(user);
            arr[count] = user;
            count++;
            return true;
        }

        //else throw "out of range";
        return false;
    }
    void show() {
        if (count == 0) { cout << "User List is emty" << endl; }
        else{
            cout << "User List" << endl;
            for (int i = 0; i < count; i++) {
                cout << arr[i].get_name() << endl;
            }
        }
        
    }

    ~Db() { //delete[]arr; 
    }
};

Msg CreateMsg(string body, string sender){
    Msg msg(body);
    msg.set_sender(sender);
    return msg;
}

User CreateUser() {
    string _name;
    string _pass;
    cout << "User creation" << endl;
    cout<<"Enter user name" << endl;
    cin >> _name;
    cout << "Enter user password" << endl;
    cin>> _pass;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    User user(_name,_pass);
    return user;
}

User* Login(Db& db) {
    string _name;
    string _pass;
    cout << "Enter the name" << endl;
    cin >> _name;
    cout << "Enter the password" << endl;
    cin >> _pass;
    for (int i = 0; i < db.get_size(); i++) {
        if (db[i].get_name() == _name && db[i].get_pass() == _pass)
            return &db[i];
    }
    return nullptr;
}

bool send_msg(Db& db, User& user) {
    //Crearing and send private message
    vector<string>vec(4);
    cout << "Enter the recipient name from user list" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>" << endl;
    db.show();
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>" << endl;
    cin.ignore();
    cout << "Enter Name: "; getline(cin,vec[1]);
    cout << "Enter the message" << endl;
    getline(cin, vec[3]);
    string& _name = vec[1];
    string& _body = vec[3];
    Msg temp = CreateMsg(_body, user.get_name());
    cout << "Message created" << endl;
    for (int i = 0; i < db.get_size(); i++) {
        if (db[i].get_name() == _name) {
            cout << "Found - " <<db[i].get_name()<< endl;
            db[i].recieve(temp);
            cout << "Resieved" << endl;
            user.send(temp);
            cout << "Message sent" << endl;
            return true;
        }
            
    }
    cout << "User not found" << endl;
    return false;
}

bool send_all(Db& db, User& user) {
    //Send all users function
    string _body;
    cout << "Enter the message for all users" << endl;
    cin.ignore();
    getline(cin,_body);
    Msg temp = CreateMsg(_body, user.get_name());
    for (int i = 0; i < db.get_size(); i++) {
        db[i].recieve(temp);
    }
    user.send(temp);
    return true;
}

void live_chat() {
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<welcome to real time chat>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    string name = "-";
    string sender = "-";
    string message = "-";
    bool exit = 0;
    int count = 1;
    do {
        name = "-";
        sender = "-";
        message = "-";
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Session # " << count << ">>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << "Enter you name" << endl;
        cin >> sender;
        cout << "Enter recipient name" << endl;
        cin >> name;
        cout << "Enter message" << endl;
        cin.ignore();
        getline(cin, message);
        cout << "-------------------------------------------------------------------------------------" << endl;
        cout << "Sent from |" << sender << "| to |" << name << "|" << endl;
        cout << "Message |||" << message << "|||" << endl;
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< End Session # " << count << ">>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        count++;
        exit = input_ex();
    } while (exit);
}




int main()
{
    bool* exit = new bool(0);
    bool* exit2 = new bool(0);
    Db db;//--User Data base
    User* user=nullptr;
    
    char ch = '-';
    
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<MIRA>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Welcome to Mira Chat" << endl;
    
    do{
     //------Main menu 
        
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        db.show();
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << "You are in MAIN MENU please Enter an action" << endl;
        cout << " <<<<<Press C to create a user>>>>>" << endl;
        cout << " <<<<<Press L to login>>>>>" << endl;
        cout << " <<<<<Press T to enter live chat>>>>>" << endl;
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
       
        try {ch=input();}
        catch (const char* ex) { cout << ex << endl; ch = 'q'; }
       
        switch (ch)
        {
        case 'C': case 'c':
            db.add(CreateUser());
            db.show();
            break;

        case 'L': case 'l':
            user = Login(db);
            if (user != nullptr)cout << "Logged " <<user->get_name() <<endl;
            else cout << "Invalid Username or Password!" << endl;
            break; 

        case 'T': case 't':
            live_chat();
            break;

        default:
            cout << "Try again" << endl;
            //cin >> ch;
            break;
        }
        if (user == nullptr) {
            cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "You are not logged in" << endl;
            cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        }
        else {
            cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<User Account>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "You are succesfully logged, please Enter an action" << endl;
            //-----logged
            do {
                cout << " <<<<<Press S to send a private message>>>>>" << endl;
                cout << " <<<<<Press A to send to all users>>>>>" << endl;
                cout << " <<<<<Press M to show all messages>>>>>" << endl;
                cout << " <<<<<Press I to show last recieved message>>>>>" << endl;
                cout << " <<<<<Press O to show last sent message>>>>>" << endl;
                ch = '-';
                try { ch = input(); }
                catch (const char* ex) { cout << ex << endl; ch = 'q';}
                
                switch (ch)
                {
                case 'S': case 's':
                    send_msg(db,*user); 
                break;
                case 'A': case 'a':
                    send_all(db, *user);
                    break;
                case 'M': case 'm':
                    user->show_all();
                    break;
                case 'I': case 'i':
                    user->get_imsg();
                    break;
                case 'O': case 'o':
                    user->get_omsg();
                    break;

                default:
                    cout << "Try again" << endl;
                    break;
                }
                *exit2 = input_ex();

            } while (*exit2);

        }
        cout << "You have returned to main menu" << endl;
        *exit= input_ex();
    } while (*exit);
    cout << "Chat closed" << endl;
    
    return 0;
}