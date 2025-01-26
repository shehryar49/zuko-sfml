#ifndef ZUKO_SFML_H_
#define ZUKO_SFML_H_
#ifdef _WIN32
  #include "C:\\zuko\\include\\zapi.h"
  #define EXPORT __declspec(dllexport)
#else
  #include "/opt/zuko/include/zapi.h"
  #define EXPORT
#endif

extern "C"
{
    EXPORT zobject init();
    EXPORT zobject getMousePosition(zobject*, int);

    //RenderWindow methods
    EXPORT zobject RenderWindow__construct(zobject*, int);
    EXPORT zobject RenderWindow__draw(zobject*, int);
    EXPORT zobject RenderWindow__clear(zobject*, int);
    EXPORT zobject RenderWindow__display(zobject*, int);
    EXPORT zobject RenderWindow__pollevent(zobject*, int);
    EXPORT zobject RenderWindow__setFrameRateLimit(zobject*, int);
    EXPORT zobject RenderWindow__close(zobject*, int);

    //Circle Methods
    EXPORT zobject Circle__construct(zobject*, int);
    EXPORT zobject Circle__setpointcount(zobject*, int);
    EXPORT zobject Circle__setfillcolor(zobject*, int);
    EXPORT zobject  Circle__setpos(zobject*, int);
    EXPORT zobject Circle__del(zobject*, int);
    //Color methods
    EXPORT zobject  Color__construct(zobject*, int);
    EXPORT zobject Color__del(zobject*, int);
    //Rectangle Methods
    EXPORT zobject  Rect__construct(zobject*, int);
    EXPORT zobject  Rect__setfillcolor(zobject*, int);
    EXPORT zobject  Rect__setOutlineColor(zobject*, int);
    EXPORT zobject  Rect__setOutlineThickness(zobject*, int);
    EXPORT zobject  Rect__setpos(zobject*, int);
    EXPORT zobject Rect__getPosition(zobject*, int);
    EXPORT zobject Rect__getGlobalBounds(zobject*, int);
    EXPORT zobject  Rect__setSize(zobject*, int);
    EXPORT zobject  Rect__del(zobject*, int);
    //Event Methods
    EXPORT zobject  Event__construct(zobject*, int);
    EXPORT zobject  Event__del(zobject*, int);
    //Texture Methods
    EXPORT zobject  Texture__construct(zobject*, int);
    EXPORT zobject  Texture__loadFromFile(zobject*, int);
    EXPORT zobject  Texture__del(zobject*, int);
    //Sprite Methods
    EXPORT zobject  Sprite__construct(zobject*, int);
    EXPORT zobject  Sprite__setTexture(zobject*, int);
    EXPORT zobject  Sprite__del(zobject*, int);
    //Clock Methods
    EXPORT zobject  Clock__construct(zobject*, int);
    EXPORT zobject  Clock__restart(zobject*, int);
    EXPORT zobject  Clock__del(zobject*, int);
    //Time Methods
    EXPORT zobject Time__asSeconds(zobject*, int);
    EXPORT zobject Time__del(zobject*, int);
    //VertexArray Methods
    EXPORT zobject  VertexArray__construct(zobject*, int);
    EXPORT zobject  VertexArray__setKth(zobject*, int);
    EXPORT zobject  VertexArray__resize(zobject*, int);
    EXPORT zobject  VertexArray__setPrimType(zobject*, int);
    EXPORT zobject  VertexArray__del(zobject*, int);
    //Font Methods
    EXPORT zobject  Font__construct(zobject*, int);
    EXPORT zobject  Font__loadFromFile(zobject*, int);
    EXPORT zobject  Font__del(zobject*, int);
    //Text Methods
    EXPORT zobject  Text__construct(zobject*, int);
    EXPORT zobject  Text__setString(zobject*, int);
    EXPORT zobject  Text__setPostion(zobject*, int);
    EXPORT zobject  Text__setCharacterSize(zobject*, int);
    EXPORT zobject  Text__setFont(zobject*, int);
    EXPORT zobject  Text__setFillColor(zobject*, int);
    EXPORT zobject  Text__del(zobject*, int);
  
    //FloatRect Methods
    EXPORT zobject FloatRect__intersects(zobject*, int);
}
#endif
