//
// Created by nolla on 24-4-14.
//

#ifndef DATA_STRUCTURE_COURSE_WIDGET_H
#define DATA_STRUCTURE_COURSE_WIDGET_H
#include <easyx.h>
#include <bits/stdc++.h>
using namespace std;

class Label
{
protected:
    RECT rect;
    string content;
    static vector<Label*> labels;
public:
    explicit Label(RECT rect):rect(rect){labels.push_back(this);}
    Label(RECT rect,string content):rect(rect),content(content){labels.push_back(this);}
    static void drawAll()
    {
        for(Label* i: labels)
            i->draw();
    }
    virtual void draw()
    {
        drawtext(content.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
};
vector<Label*> Label::labels;

class Button:public Label
{
private:
    static vector<Button*> buttons;
    bool clicked(ExMessage m)
    {
        if((rect.left < m.x && m.x < rect.right) || (rect.left > m.x && m.x > rect.right))
        {
            if((rect.bottom < m.y && m.y < rect.top) || (rect.bottom > m.y && m.y > rect.top))
                return true;
        }
        return false;
    }

protected:
    function<void()> event;

public:
    explicit Button(RECT rect):Label(rect){buttons.push_back(this);}
    Button(RECT rect,string content):Label(rect,content){buttons.push_back(this);}
    static void checkClick(ExMessage m)
    {
        for(Button* i: buttons)
        {
            if(i->clicked(m))
            {
                i->event();
                return;
            }
        }
    }
    virtual void draw()
    {
        drawtext(content.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        rectangle(rect.left, rect.top, rect.right, rect.bottom);
    }

    template<class FUNC>
    void setEvent(FUNC func)
    {
        event=func;
    }
};
vector<Button*> Button::buttons;

class InputArea:public Button
{
private:
    string _content;
public:
    explicit InputArea(RECT rect):Button(rect){}
    void draw() override
    {
        rectangle(rect.left, rect.top, rect.right, rect.bottom);
        RECT output=rect;
        output.left+=10;
        drawtext(_content.c_str(), &output, DT_VCENTER | DT_SINGLELINE);
    }
    void update(string content)
    {
        _content =content;
    }
};

#endif //DATA_STRUCTURE_COURSE_WIDGET_H
