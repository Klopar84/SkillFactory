участники команды
1. Ревуцкий Алексей..

Классы и методы

1.class Msg - класс тела сообщений 
имеет поля: 
тело сообщения 
отапавитель
имеет методы: 
показ тела сообщения 
вывод отравителя 
установка отправителя

2.class User - класс - тела пользователей
имеет поля: 
Логин 
Пароль 
счетчик входящих сообщений imsg
счетчик исходящих сообщейний omsg
указатели на масивы сообщений iarr - входящин, oarr - исходящие
имеет методы: 
конструтор(принимает два текстовых поля устанавливает их в качестве логина, пароля)
конструктор без параметров(создает анонимного пользователя)
метод get_name - вывод имени
метод get_pass - вывод пароля
метод recive  - принимает на вход объект класса сообщение добавляет в iarr
метод send - принимает на вход объект класса сообщение добавляет в оarr
метод get_imsg - выводит последнее входящее сообщение
метод щet_imsg - выводит последнее исходящее сообщение
метод shaw_all  - выводи все входящие и исходящие сообщения

3.class Db - класс для создания базы данных пользователей
Имеет поля:
Размер базы
Счетчик созданных пользователей
Умный указатель на массив пользователей
Имеет методы:
add - добавление пользователей
show - вывод на экран всех пользователей

4. Метод Create Msg
Принимает на вход тело сообщения и отправителя, возвращает готовый объект Msg

5. Метод CreateUser
в теле метода происходит ввод имени и пароля, аозвращает объект класса User

6. Метод Login
принимат на вход сыылку на базу данных пользователей
в теле метода происходит ввод пользователя и пароля, происходит поиск по базе данных, возвращает указатель на найденного пользователя

7. Метод Send_msg
В качестве аргументов метод принимает ссылку на базу данных и ссылку на текущего пользователя
в теле метода происходит ввод имени адресата сообщения и само сообщение, далее происходит поиск 
по базе пользователей и при нахождении пользователя сообщение попадает в массив принятых сообщений

8. Метод send_all
В теле метода происходит ввод сообщения и далее сообщение добавляется всем пользователям базы

9. Методы input и input_boll
Методы производят проверку правильности ввода данных пользователем



При завуске программы попадаем в основное меню
Список опций:
1. Список пользователей
2. Выбор опций создания пользователей и входа в систему

<<<<<<<<<<<<<<<<<<<<<<<<<<<MIRA>>>>>>>>>>>>>>>>>>>>>>>>>>
Welcome to Mira Chat
<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
User List is emty
<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
You are in MAIN MENU please Enter an action
 <<<<<Press C to create a user>>>>>
 <<<<<Press L to login>>>>>
 <<<<<Press T to enter live chat>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

При  вводе С вводим имя пользователя и пароль после создания пользователя он появится в списке пользователей(User List), 
после этого вы сможете войти в систему для этого повторите вход в главное меню.
После входа в меню возможно повторить создание пользователя, войти в личный кабинет либо покинуть чат.
При вооде коректного логина и пароля вы попадаете в личный кабинет.

Logged -User-
<<<<<<<<<<<<<<<<<<<<<<<<<<<User Account>>>>>>>>>>>>>>>>>>>>>>>>>>
You are succesfully logged, please Enter an action
 <<<<<Press S to send a private message>>>>>
 <<<<<Press A to send to all users>>>>>
 <<<<<Press M to show all messages>>>>>
 <<<<<Press I to show last recieved message>>>>>
 <<<<<Press O to show last sent message>>>>>
 
 После входа в основное меню мы можем выбрать следующие опции
 
 s - отправка приватного сообщения любому пользователю из списка
 a - отправка сообщения всем пользователям списка
 m - просмотр всех входящих и отправленных сообщений
 i - просмотр последнего полученного сообщения
 0 - просмотр последнего отправленного сообщения
 
 После выбора опции и выполнения операции вы можете повторить выбор опции либо выйти в основное меню для 
 создания пользователей и входа в систему либо покинуть чат.
 
 При вводе Т вы попадаете в режим Live Chat, в данном режиме вы можете обмениваться сообщениями в реальном времени без необходимости авторизации.
 Для отправки сообщения введите свое имя, имя получателя и текст сообщения, после ввода сообщение отобразится на экране, далее другой пользователь может открыть новою сессию и отправить сообщение вам либо вы можете выйти из чата.!S
