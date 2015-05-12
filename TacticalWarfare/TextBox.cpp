//
//  TextBox.cpp
//  client
//
//  Created by Thomas Redding on 6/10/14.
//  Copyright (c) 2014 Thomas Redding. All rights reserved.
//

#include "TextBox.h"

TextBox::TextBox(sf::Font *fontToUse, sf::Vector2f pos, sf::Vector2f siz)
{
    font = fontToUse;
    position.x = pos.x;
    position.y = pos.y;
    size.x = siz.x;
    size.y = siz.y;
    windowSize.x = 0;
    windowSize.y = 0;
    str = "";
    boxType = 0;
}

TextBox::TextBox(sf::Font *fontToUse, sf::Vector2f pos, sf::Vector2f siz, int typeOfBox)
{
    font = fontToUse;
    position.x = pos.x;
    position.y = pos.y;
    size.x = siz.x;
    size.y = siz.y;
    windowSize.x = 0;
    windowSize.y = 0;
    str = "";
    boxType = typeOfBox;
}

void TextBox::setPosition(sf::Vector2f vect)
{
    position.x = vect.x;
    position.y = vect.y;
}

void TextBox::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

bool TextBox::mouseButtonPressed(sf::Event::MouseButtonEvent mouse)
{
    if(mouse.x>absolutePosition.x && mouse.x<absolutePosition.x+absoluteSize.x && mouse.y>absolutePosition.y && mouse.y<absolutePosition.y+absoluteSize.y)
    {
        focus();
        return true;
    }
    unfocus();
    return false;
}

void TextBox::setSize(sf::Vector2f vect)
{
    size.x = vect.x;
    size.y = vect.y;
}

void TextBox::setSize(float x, float y)
{
    size.x = x;
    size.y = y;
}

void TextBox::render(sf::RenderWindow* window)
{
    windowSize = (*window).getSize();
    sf::RectangleShape renderObject;
    absoluteSize.x = size.x;
    absoluteSize.y = size.y;
    absolutePosition.x = position.x-absoluteSize.x/2;
    absolutePosition.y = position.y-absoluteSize.y/2;
    
    renderObject.setPosition(absolutePosition);
    renderObject.setSize(absoluteSize);
    (*window).draw(renderObject);
    
    sf::Text text(str, *font, absoluteSize.y);
    text.setPosition(absolutePosition.x, absolutePosition.y-absoluteSize.y*0.15);
    text.setColor(sf::Color::Black);
    int len =  str.length();
    std::string x = "";
    if(boxType == 1)
    {
        int i;
        for(i=0; i < len; i++)
        {
            x += "*";
        }
        text.setString(x);
    }
    (*window).draw(text);
    
    std::clock_t currentClock = std::clock();
    int time = currentClock - startClock;
    
    if(focused && time%20000<10000)
    {
        if(boxType == 1)
        {
            sf::Text textB(x.substr(0, cursorSpot), *font, absoluteSize.y);
            float textBWidth = textB.getGlobalBounds().width;
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0].position = sf::Vector2f(absolutePosition.x+textBWidth+2, absolutePosition.y);
            line[0].color = sf::Color(0, 0, 0);
            line[1].position = sf::Vector2f(absolutePosition.x+textBWidth+2, absolutePosition.y+absoluteSize.y);
            line[1].color = sf::Color(0, 0, 0);
            (*window).draw(line);
        }
        else
        {
            sf::Text textB(str.substr(0, cursorSpot), *font, absoluteSize.y);
            float textBWidth = textB.getGlobalBounds().width;
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0].position = sf::Vector2f(absolutePosition.x+textBWidth+2, absolutePosition.y);
            line[0].color = sf::Color(0, 0, 0);
            line[1].position = sf::Vector2f(absolutePosition.x+textBWidth+2, absolutePosition.y+absoluteSize.y);
            line[1].color = sf::Color(0, 0, 0);
            (*window).draw(line);
        }
    }
}

void TextBox::textEntered(int key)
{
    if(!focused) {
        return;
    }
    if(key == 8)
    {
        if(cursorSpot>0)
        {
            str.erase(cursorSpot-1, 1);
            cursorSpot--;
        }
        else if(cursorSpot == 0)
        {
            str.erase(0, 1);
        }
    }
    else
    {
        std::string output = UnicodeToString(key);
        if(output!="")
        {
            if(str.length()<maxCharacterLength)
            {
                if(boxType == 2) {
                    if(output == "0" || output == "1" || output == "2" || output == "3" || output == "4" || output == "5" || output == "6" || output == "7" || output == "8" || output == "9" || output == ".") {
                        str.insert(cursorSpot, output);
                        cursorSpot++;
                    }
                }
                else {
                    str.insert(cursorSpot, output);
                    cursorSpot++;
                }
            }
        }
        else
        {
            // do nothing
        }
    }
}

void TextBox::keyPressed(sf::Event::KeyEvent key)
{
    if(key.code == sf::Keyboard::Left)
    {
        if(cursorSpot>0)
        {
            cursorSpot--;
        }
    }
    else if(key.code == sf::Keyboard::Right)
    {
        if(cursorSpot<str.length())
        {
            cursorSpot++;
        }
    }
}

std::string TextBox::UnicodeToString(int key)
{
    if(key == 32)
    {
        return " ";
    }
    else if(key == 33)
    {
        return "!";
    }
    else if(key == 34)
    {
        return "\"";
    }
    else if(key == 35)
    {
        return "#";
    }
    else if(key == 36)
    {
        return "$";
    }
    else if(key == 37)
    {
        return "%";
    }
    else if(key == 38)
    {
        return "&";
    }
    else if(key == 39)
    {
        return "\'";
    }
    else if(key == 40)
    {
        return "(";
    }
    else if(key == 41)
    {
        return ")";
    }
    else if(key == 42)
    {
        return "*";
    }
    else if(key == 43)
    {
        return "+";
    }
    else if(key == 44)
    {
        return ", ";
    }
    else if(key == 45)
    {
        return "-";
    }
    else if(key == 46)
    {
        return ".";
    }
    else if(key == 47)
    {
        return "/";
    }
    else if(key == 48)
    {
        return "0";
    }
    else if(key == 49)
    {
        return "1";
    }
    else if(key == 50)
    {
        return "2";
    }
    else if(key == 51)
    {
        return "3";
    }
    else if(key == 52)
    {
        return "4";
    }
    else if(key == 53)
    {
        return "5";
    }
    else if(key == 54)
    {
        return "6";
    }
    else if(key == 55)
    {
        return "7";
    }
    else if(key == 56)
    {
        return "8";
    }
    else if(key == 57)
    {
        return "9";
    }
    else if(key == 58)
    {
        return ":";
    }
    else if(key == 59)
    {
        return ";";
    }
    else if(key == 60)
    {
        return "<";
    }
    else if(key == 61)
    {
        return "=";
    }
    else if(key == 62)
    {
        return ">";
    }
    else if(key == 63)
    {
        return "?";
    }
    else if(key == 64)
    {
        return "@";
    }
    else if(key == 65)
    {
        return "A";
    }
    else if(key == 66)
    {
        return "B";
    }
    else if(key == 67)
    {
        return "C";
    }
    else if(key == 68)
    {
        return "D";
    }
    else if(key == 69)
    {
        return "E";
    }
    else if(key == 70)
    {
        return "F";
    }
    else if(key == 71)
    {
        return "G";
    }
    else if(key == 72)
    {
        return "H";
    }
    else if(key == 73)
    {
        return "I";
    }
    else if(key == 74)
    {
        return "J";
    }
    else if(key == 75)
    {
        return "K";
    }
    else if(key == 76)
    {
        return "L";
    }
    else if(key == 77)
    {
        return "M";
    }
    else if(key == 78)
    {
        return "N";
    }
    else if(key == 79)
    {
        return "O";
    }
    else if(key == 80)
    {
        return "P";
    }
    else if(key == 81)
    {
        return "Q";
    }
    else if(key == 82)
    {
        return "R";
    }
    else if(key == 83)
    {
        return "S";
    }
    else if(key == 84)
    {
        return "T";
    }
    else if(key == 85)
    {
        return "U";
    }
    else if(key == 86)
    {
        return "V";
    }
    else if(key == 87)
    {
        return "W";
    }
    else if(key == 88)
    {
        return "X";
    }
    else if(key == 89)
    {
        return "Y";
    }
    else if(key == 90)
    {
        return "Z";
    }
    else if(key == 91)
    {
        return "[";
    }
    else if(key == 92)
    {
        return "\\";
    }
    else if(key == 93)
    {
        return "]";
    }
    else if(key == 94)
    {
        return "^";
    }
    else if(key == 95)
    {
        return "_";
    }
    else if(key == 96)
    {
        return "`";
    }
    else if(key == 97)
    {
        return "a";
    }
    else if(key == 98)
    {
        return "b";
    }
    else if(key == 99)
    {
        return "c";
    }
    else if(key == 100)
    {
        return "d";
    }
    else if(key == 101)
    {
        return "e";
    }
    else if(key == 102)
    {
        return "f";
    }
    else if(key == 103)
    {
        return "g";
    }
    else if(key == 104)
    {
        return "h";
    }
    else if(key == 105)
    {
        return "i";
    }
    else if(key == 106)
    {
        return "j";
    }
    else if(key == 107)
    {
        return "k";
    }
    else if(key == 108)
    {
        return "l";
    }
    else if(key == 109)
    {
        return "m";
    }
    else if(key == 110)
    {
        return "n";
    }
    else if(key == 111)
    {
        return "o";
    }
    else if(key == 112)
    {
        return "p";
    }
    else if(key == 113)
    {
        return "q";
    }
    else if(key == 114)
    {
        return "r";
    }
    else if(key == 115)
    {
        return "s";
    }
    else if(key == 116)
    {
        return "t";
    }
    else if(key == 117)
    {
        return "u";
    }
    else if(key == 118)
    {
        return "v";
    }
    else if(key == 119)
    {
        return "w";
    }
    else if(key == 120)
    {
        return "x";
    }
    else if(key == 121)
    {
        return "y";
    }
    else if(key == 122)
    {
        return "z";
    }
    else if(key == 123)
    {
        return "{";
    }
    else if(key == 124)
    {
        return "|";
    }
    else if(key == 125)
    {
        return "}";
    }
    else if(key == 126)
    {
        return "~";
    }
    else
    {
        if(key == 9)
        {
            // tab (ignore)
            return "";
        }
        else
        {
            // other
            std::cout << "(";
            std::cout << key;
            std::cout << ")";
            return "";
        }
    }
}

std::string TextBox::getValue()
{
    return str;
}

std::string TextBox::setValue(std::string newValue) {
    str = newValue;
}

void TextBox::focus()
{
    focused = true;
}

void TextBox::unfocus()
{
    focused = false;
}

void TextBox::center(sf::Vector2u screenSize) {
    position.x = screenSize.x/2.0;
    position.y = screenSize.y/2.0;
}

sf::Vector2f TextBox::getPosition() {
    return position;
}