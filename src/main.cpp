#include <bits/stdc++.h>
#include <easyx.h>
#include "AVLTree.h"
#include "widget.h"
using namespace std;

const int width=640;
const int height=480;
const int midWidth=width/2;
const int midHeight=height/2;

int main()
{
    typedef pair<string,string> user;
    AVL<user> t;
    t.loadFromFile();

    initgraph(width,height);
    setbkcolor(LIGHTBLUE);
    cleardevice();

    RECT usernameLabelRect={midWidth-200,midHeight-100,midWidth-100,midHeight-50};
    Label usernameLabel(usernameLabelRect,"username:");
    RECT usernameInputRect={midWidth-100,midHeight-100,midWidth+100,midHeight-50};
    string username;
    InputArea usernameInput(usernameInputRect);
    auto usernameEvent=[&usernameInputRect,&usernameInput,&username]()
    {
        RECT rect=usernameInputRect;
        clearrectangle(rect.left,rect.top,rect.right,rect.bottom);
        char buf[256];
        InputBox(buf,256,"Input your username:");
        username=buf;
        usernameInput.update(username);
    };
    usernameInput.setEvent(usernameEvent);

    RECT passwordLabelRect={midWidth-200,midHeight-30,midWidth-100,midHeight+20};
    Label passwordLabel(passwordLabelRect,"password:");
    RECT passwordInputRect={midWidth-100,midHeight-30,midWidth+100,midHeight+20};
    string password;
    InputArea passwordInput(passwordInputRect);
    auto passwordEvent=[&passwordInputRect,&passwordInput,&password]()
    {
        RECT rect=passwordInputRect;
        clearrectangle(rect.left,rect.top,rect.right,rect.bottom);
        char buf[256];
        InputBox(buf,256,"Input your password:");
        password=buf;
        passwordInput.update(password);
    };
    passwordInput.setEvent(passwordEvent);

    auto loginEvent=[&t,&username,&password]()
    {
        if(t.find({username,password}))
        {
            cout<<"Login Success"<<endl;
        }
        else
        {
            cout<<"Login failed"<<endl;
        }
    };
    RECT loginLabel={midWidth+10,midHeight+40,midWidth+70,midHeight+80};
    Button loginButton(loginLabel,"Login");
    loginButton.setEvent(loginEvent);

    auto registerEvent=[&t,&username,&password]()
    {
        if(t.insert({username,password}))
        {
            cout<<"Register Success"<<endl;
        }
        else
        {
            cout<<"Register failed"<<endl;
        }
    };
    RECT registerLabel={midWidth-70,midHeight+40,midWidth-10,midHeight+80};
    Button registerButton(registerLabel,"Register");
    registerButton.setEvent(registerEvent);

    auto deleteAccountEvent=[&t,&username,&password]()
    {
        if(t.remove({username,password}))
        {
            cout<<"Cancel Success"<<endl;
        }
        else
        {
            cout<<"Cancel failed"<<endl;
        }
    };
    RECT deleteAccountLabel={midWidth-50,midHeight+90,midWidth+50,midHeight+110};
    Button deleteAccountButton(deleteAccountLabel,"deleteAccount");
    deleteAccountButton.setEvent(deleteAccountEvent);

    ExMessage m;		// 定义消息变量
    while(true)
    {
        Label::drawAll();
        m = getmessage(EX_MOUSE|EX_KEY);
        if(m.message==WM_LBUTTONUP)
        {
            Button::checkClick(m);
        }
        else if(m.message==WM_KEYDOWN)
            if (m.vkcode == VK_ESCAPE)
            {
                t.saveToFile();
                return 0;
            }
    }

    return 0;
}