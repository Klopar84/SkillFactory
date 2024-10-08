#include <iostream>
#include <string>

using namespace std;

#define SIZE 10
#define LOGINLENGTH 10
typedef unsigned int uint;

#define one_block_size_bytes 64 // количество байб в блоке
#define one_block_size_uints 16 // количество 4байтовых  в блоке
#define block_expend_size_uints 80 // количество 4байтовых в дополненном блоке

#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5

typedef uint* Block;
typedef uint ExpendBlock[block_expend_size_uints];

const uint H[5] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
};

uint cycle_shift_left(uint val, int bit_count) {
    return (val << bit_count | val >> (32 - bit_count));
}

uint bring_to_human_view(uint val) {
    return  ((val & 0x000000FF) << 24) |
        ((val & 0x0000FF00) << 8) |
        ((val & 0x00FF0000) >> 8) |
        ((val & 0xFF000000) >> 24);
}

uint* sha1(string msg, uint msize_bytes) {

    const char* message = msg.c_str();
    msize_bytes *= 4;
    //инициализация
    uint A = H[0];
    uint B = H[1];
    uint C = H[2];
    uint D = H[3];
    uint E = H[4];

    // подсчет целого числа блоков
    uint totalBlockCount = msize_bytes / one_block_size_bytes;

    // подсчет, сколько байт нужно, чтобы дополнить последний блок
    uint needAdditionalBytes =
        one_block_size_bytes - (msize_bytes - totalBlockCount * one_block_size_bytes);

    if (needAdditionalBytes < 8) {
        totalBlockCount += 2;
        needAdditionalBytes += one_block_size_bytes;
    }
    else {
        totalBlockCount += 1;
    }

    // размер дополненного по всем правилам сообщения
    uint extendedMessageSize = msize_bytes + needAdditionalBytes;

    // выделяем новый буфер и копируем в него исходный
    unsigned char* newMessage = new unsigned char[extendedMessageSize];
    memcpy(newMessage, message, msize_bytes);

    // первый бит ставим '1', остальные обнуляем
    newMessage[msize_bytes] = 0x80;
    memset(newMessage + msize_bytes + 1, 0, needAdditionalBytes - 1);

    // задаем длину исходного сообщения в битах
    uint* ptr_to_size = (uint*)(newMessage + extendedMessageSize - 4);
    *ptr_to_size = bring_to_human_view(msize_bytes * 8);

    ExpendBlock exp_block;
    //раунды поехали
    for (int i = 0; i < totalBlockCount; i++) {

        // берем текущий блок и дополняем его
        unsigned char* cur_p = newMessage + one_block_size_bytes * i;
        Block block = (Block)cur_p;

        // первые 16 4байтовых чисел
        for (int j = 0; j < one_block_size_uints; j++) {
            exp_block[j] = bring_to_human_view(block[j]);
        }
        // следующие 64...
        for (int j = one_block_size_uints; j < block_expend_size_uints; j++) {
            exp_block[j] =
                exp_block[j - 3] ^
                exp_block[j - 8] ^
                exp_block[j - 14] ^
                exp_block[j - 16];
            exp_block[j] = cycle_shift_left(exp_block[j], 1);
        }

        // инициализация 
        uint a = H[0];
        uint b = H[1];
        uint c = H[2];
        uint d = H[3];
        uint e = H[4];

        // пересчитываем
        for (int j = 0; j < block_expend_size_uints; j++) {
            uint f;
            uint k;
            // в зависимости от раунда считаем по-разному
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            // перемешивание
            uint temp = cycle_shift_left(a, 5) + f + e + k + exp_block[j];
            e = d;
            d = c;
            c = cycle_shift_left(b, 30);
            b = a;
            a = temp;
        }
        // пересчитываем
        A = A + a;
        B = B + b;
        C = C + c;
        D = D + d;
        E = E + e;
    }

    // A,B,C,D,E являются выходными 32б составляющими посчитанного хэша
    uint* digest = new uint[5];
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;

    // чистим за собой
    delete[] newMessage;
    return digest;
}

class Chat {
public:
    Chat() {};
    void reg(char _login[LOGINLENGTH], string pass) {

        hash_data.add(_login, sha1(pass, pass.length()));
        
    }

    bool login(char _login[LOGINLENGTH], string pass) {
        int index = hash_data.find(_login);
        if (index == -1) return false;
        else return !memcmp(sha1(pass, pass.length()), hash_data.data[index].pass_sha1_hash, SHA1HASHLENGTHBYTES);
    }

private:
    
    struct AuthData {
        AuthData() :
            login(""),
            pass_sha1_hash(0) {
        }
        enum enPairStatus {
            free,
            engaged,
            deleted
        };
        ~AuthData() {
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
        }
        AuthData(char _login[LOGINLENGTH], uint* sh1) {
            strcpy_s(login, _login);
            pass_sha1_hash = sh1;
            status = engaged;
        }
        AuthData& operator = (const AuthData& other) {
            strcpy_s(login, other.login);
            this->status = other.status;

            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            return *this;
        }
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        enPairStatus status = free;
    };

    struct Hash_tab {
        
        int mem_size;
        int count;
        AuthData* data;
        Hash_tab() {
            mem_size=10;
            count = 0;
            data = new AuthData[mem_size];
        }
        

        int hash_func(char _login[LOGINLENGTH], int offset) {
            // вычисляем индекс
            int sum = 0, i = 0;
            for (; i < strlen(_login); i++) {
                sum += _login[i];
            }
            // квадратичные пробы
            return (sum % mem_size + offset * offset) % mem_size;
        }

        void resize() {

            AuthData* save = data;
            int save_ms = mem_size;

            mem_size *= 2;
            data = new AuthData[mem_size];
            count = 0;

            for (int i = 0; i < save_ms; i++) {
                AuthData& old_pair = save[i];
                if (old_pair.status == AuthData::enPairStatus::engaged) {
                    add(old_pair.login, old_pair.pass_sha1_hash);
                }
            }

            delete[] save;
        }

       void add (char _login[LOGINLENGTH], uint* _pass) {
            int index = -1, i = 0;
            // берем пробы по всем i от 0 до размера массива
            for (; i < mem_size; i++) {
                index = hash_func(_login, i);
                if (data[index].status == AuthData::enPairStatus::free) {
                    // найдена пустая ячейка, занимаем ее
                    break;
                }
            }

            if (i >= mem_size) {
                resize();
                add(_login, _pass);
            }
            else {
                data[index] = AuthData(_login, _pass);
                count++;
            }
       
        }

       int find(char _login[LOGINLENGTH]) {
            
            for (int i = 0; i < mem_size; i++) {
                int index = hash_func(_login, i);
                if (data[index].status == AuthData:: enPairStatus::engaged &&
                    !strcmp(data[index].login, _login)) {
                    cout << "Index  - " << index << endl;
                    return index;
                }
                else if (data[index].status == AuthData:: enPairStatus::free) {
                    return -1;
                }
            }
            return -1;

        }
    };

    Hash_tab hash_data;
    
   
    
};

int main()
{
    std::cout << "Hello World!\n";
    char ch[LOGINLENGTH] = "alex";
    Chat c;
    c.reg(ch, "alex");
    cout << "Right - " << c.login(ch, "alex")<<endl;
    cout << "wrong - " << c.login(ch, "ale") << endl;
}
