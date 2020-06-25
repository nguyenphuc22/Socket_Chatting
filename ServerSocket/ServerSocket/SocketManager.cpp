#include "pch.h"
#include "SocketManager.h"


static int iCount;
static list<User> sArray;

void SocketManager::addNewuser(User user) {
    sArray.push_back(user);
}

bool SocketManager::isUserOnline(string userName) {
    
    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {
        if (userName == it->userName)
        {
            return true;
        }
    }
    return false;
}

bool SocketManager::signupfunc(string userName, string passWord, SOCKET& socket) {

    string error = "";
    if (checkSignup(userName, passWord, error))
    {
        signupResponse(true, error, socket);

        //update client list
        cout << error << endl;
        return true;
    }
    // Signup Fail
    cout << error << endl;
    signupResponse(false, error, socket);


    return false;
}

void SocketManager::signupResponse(bool isSucc, string errorMsg, SOCKET& socket) {

    ResponseSignupStruct* responseSignupStruct = new ResponseSignupStruct(isSucc, errorMsg);

    vector<char> data = responseSignupStruct->pack();

    send(socket, &data[0], data.size(), 0);
}

bool SocketManager::checkLogin(string userName, string passWord, string& errorMsg) {
    // check empty
    if (userName.empty() || passWord.empty())
    {
        errorMsg = "Username or Password can't be blank!";
        return false;
    }

    if (!checkAccount(userName, passWord, errorMsg))
    {
        return false;
    }
    // chec current online
    
    if (isUserOnline(userName))
    {
        errorMsg = "Account is online!";
        return false;
    }
    
    errorMsg = "Login Success!";
    return true;
}
bool SocketManager::checkAccount(string username, string password, string& errorMsg) {

    ifstream fileInput(this->accountPath);

    if (fileInput.fail())
    {
        errorMsg = "Can't not open file database";
        return false;
    }
    string tmp, tmp1, tmp2,temp3;
    while (!fileInput.eof())
    {

        getline(fileInput, tmp);
        getline(fileInput, tmp1);
        tmp2 = username + password;
        temp3 = tmp + tmp1;
        if (tmp2 == temp3)
        {
            return true;
        }
    }
    errorMsg = "Username or Password is not correct!";
    return false;
}
bool SocketManager::checkSignup(string username, string password, string& errorMsg) {

    // check empty
    if (username.empty() || password.empty())
    {
        errorMsg = "Username or Password can't be blank!";
        return false;
    }

    //Check exists username in database
    if (checkAccountExists(username))
    {
        errorMsg = "This username has been registered!";
        return false;
    }

    if (!addAnAccountToDatabase(username, password))
    {
        errorMsg = "Can't register!";
        return false;
    }

    errorMsg = "Signup Success";
    return true;
}
bool SocketManager::checkAccountExists(string username) {

    ifstream fileInput(this->accountPath);

    if (fileInput.fail())
    {
        return false;
    }
    string tmp;
    while (!fileInput.eof())
    {
        getline(fileInput, tmp);

        if (tmp == username)
        {
            return true;
        }
        // skip line password
        getline(fileInput, tmp);
    }

    return false;
}
bool SocketManager::addAnAccountToDatabase(string username, string password) {
    // Mode write file the end postion
    ofstream fileOutput(this->accountPath, std::ios::app);

    if (fileOutput.fail())
    {
        return false;
    }

    fileOutput << username << endl;
    fileOutput << password << endl;

    fileOutput.close();

    return true;
}

void SocketManager::listenMessageFromClient(SOCKET& socket,vector<char> buf) {

    //vector<char> buf(4096);

    //int recved = recv(socket, &buf[0], buf.size(), 0);

    ChatStruct* msgReceived = ManagerStruct::unpack(buf);

    switch (msgReceived->mesageType)
    {
    case publicMessage:
    {
        ChatpublicStruct* chatpublic = (ChatpublicStruct*)msgReceived;

        this->sendMessagepublic(chatpublic->userName,socket);

        break;
    }
    case privateMessage:
    {
        ChatprivateStruct* chatprivate = (ChatprivateStruct*)msgReceived;

        this->sendMessageprivate(chatprivate->userName, chatprivate->msg, socket);

        break;
    }
    case privateFile:
        break;
    case userStatus:
    {
       
        break;
    }
    case requestSendFile:
        break;
    case responseSendFile:
        break;
    case login:
    {
        LoginStruct* loginStruct = (LoginStruct*)msgReceived;

        this->loginfunc(loginStruct->userName, loginStruct->passWord, socket);

        break;
    }
    case responseLogin:
        break;
    case signup:
    {
        SignupStruct* signupStruct = (SignupStruct*)msgReceived;

        this->signupfunc(signupStruct->userName, signupStruct->passWord, socket);

        break;
    }
    case responseSignup:
        break;
    case loginNotification:
        break;
    case logoutNotification:
    {
        LogoutStruct* logout = (LogoutStruct*)msgReceived;

        this->logoutNoti(logout->userName, socket);
        
        break;
    }
    default:
        break;
    }
}

void SocketManager::loginResponse(bool isSucc, string errorMsg, SOCKET& socket) {
    
    ResponseLoginStruct* responseSignupStruct = new ResponseLoginStruct(isSucc, errorMsg);

    vector<char> data = responseSignupStruct->pack();

    send(socket, &data[0], data.size(), 0);
}


bool SocketManager::loginfunc(string userName, string passWord, SOCKET& socket) {

    string error = "";
    if (this->checkLogin(userName, passWord, error)) {
        for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
        {

            if (it->socket == socket)
            {
                it->userName = userName;
            }

        }
        //login Succecc
        this->loginResponse(true, error, socket);
 
        this->UserOnline(sArray);

        Sleep(1000);

        this->loginNoti(userName, socket);


        return true;
    }
    //login fail
    this->loginResponse(false, error, socket);
    return false;
}

void SocketManager::loginNoti(string userName, SOCKET& socket) {

    LoginNotification* loginNotification = new LoginNotification(userName);

    vector<char> buf = loginNotification->pack();
    
    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {
       
            send(it->socket, &buf[0], buf.size(), 0);
                
    }
}

void SocketManager::logoutNoti(string userName, SOCKET& socket) {

    LogoutStruct* logout = new LogoutStruct(userName);

    vector<char> buf = logout->pack();
    
    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {
        
            send(it->socket, &buf[0], buf.size(), 0);
        
    }

    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {

        if (it->socket == socket)
        {
            sArray.erase(it);
            break;
        }

    }

}

void SocketManager::UserOnline(list<User> sArray) {

    UserOnlineStruct* userOnlineStruct = new UserOnlineStruct(sArray);

    vector<char> buf = userOnlineStruct->pack();

    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {

        send(it->socket, &buf[0], buf.size(), 0);

    }

}

void SocketManager::sendMessagepublic(string msg, SOCKET& socket) {

    string msgg = msg;
    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {

        if (it->socket == socket)
        {
            msgg = it->userName + ":" + msg;
        }

    }

    ChatpublicStruct* userOnlineStruct = new ChatpublicStruct(msgg);

    vector<char> buf = userOnlineStruct->pack();

    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {

        send(it->socket, &buf[0], buf.size(), 0);

    }

}

void SocketManager::sendMessageprivate(string userName, string smg , SOCKET& socket) {

    string msgResult = smg;

    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {

        if (it->socket == socket)
        {

            msgResult = "From:" +  it->userName + "to you : (Private)" + smg;
            break;
        }
        
    }

    for (list<User>::iterator it = sArray.begin(); it != sArray.end(); ++it)
    {

        if (it->userName == userName)
        {
            ChatprivateStruct* userOnlineStruct = new ChatprivateStruct(userName, msgResult);

            vector<char> buf = userOnlineStruct->pack();

            send(it->socket, &buf[0], buf.size(),0);
        }

    }

}