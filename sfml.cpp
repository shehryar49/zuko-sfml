#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "sfml.h"
#include <stdio.h>
#include "/opt/zuko/include/zapi.h"


zclass* renderwinclass;
zclass* circleclass;
zclass* rectclass;
zclass* evclass;
zclass* colorclass;
zclass* clockclass;
zclass* timeclass;
zclass* vaclass;
zclass* fontclass;
zclass* textclass;
zclass* textureclass;
zclass* spriteclass;
zclass* vector2fclass;
zclass* floatrectclass;

zobject nil;
zobject init()
{
    nil.type = Z_NIL;
    // Initialize classes
    renderwinclass = vm_alloc_zclass();
    renderwinclass->name = "RenderWindow";
    zclass_add_method(renderwinclass,"__construct__", &RenderWindow__construct);
    zclass_add_method(renderwinclass,"clear",&RenderWindow__clear);
    zclass_add_method(renderwinclass,"draw",&RenderWindow__draw);
    zclass_add_method(renderwinclass,"display",&RenderWindow__display);
    zclass_add_method(renderwinclass,"pollEvent",&RenderWindow__pollevent);
    zclass_add_method(renderwinclass,"setFramerateLimit", &RenderWindow__setFrameRateLimit);
    zclass_add_method(renderwinclass,"close",&RenderWindow__close);

    circleclass = vm_alloc_zclass();
    circleclass->name = "Circle";
    zclass_add_method(circleclass,"__construct__",&Circle__construct);
    zclass_add_method(circleclass,"setPosition",&Circle__setpos);
    zclass_add_method(circleclass,"setFillColor",&Circle__setfillcolor);
    zclass_add_method(circleclass,"setPointCount",&Circle__setpointcount);
    zclass_add_method(circleclass,"__del__",&Circle__del);
  
    colorclass = vm_alloc_zclass();
    colorclass->name = "Color";
    zclass_add_method(colorclass,"__construct__",&Color__construct);
    zclass_add_method(colorclass,"__del__",&Color__del);

    rectclass = vm_alloc_zclass();
    rectclass->name = "Rectangle";
    zclass_add_method(rectclass,"__construct__",&Rect__construct);
    zclass_add_method(rectclass,"setPosition", &Rect__setpos);
    zclass_add_method(rectclass,"setFillColor", &Rect__setfillcolor);
    zclass_add_method(rectclass,"setOutlineColor", &Rect__setOutlineColor);
    zclass_add_method(rectclass,"setOutlineThickness",&Rect__setOutlineThickness);
    zclass_add_method(rectclass,"setPosition",&Rect__setpos);
    zclass_add_method(rectclass,"getPosition",&Rect__getPosition);
    zclass_add_method(rectclass,"getGlobalBounds",&Rect__getGlobalBounds);
    zclass_add_method(rectclass,"setSize",&Rect__setSize);

    evclass = vm_alloc_zclass();
    evclass->name = "Event";
    zclass_add_method(evclass,"__construct__",&Event__construct);
    zclass_add_method(evclass,"__del__",&Event__del);
    zclass_addmember(evclass,"type", nil);
    zclass_addmember(evclass,"keycode", nil);

    textureclass = vm_alloc_zclass();
    textureclass->name = "Texture";
    zclass_add_method(textureclass,"__construct__", &Texture__construct);
    zclass_add_method(textureclass,"loadFromFile", &Texture__loadFromFile);
    zclass_add_method(textureclass,"__del__", &Texture__del);

    clockclass = vm_alloc_zclass();
    clockclass->name = "Clock";
    zclass_add_method(clockclass,"__construct__", &Clock__construct);
    zclass_add_method(clockclass,"restart", &Clock__restart);
    zclass_add_method(clockclass,"__del__", &Clock__del);

    vaclass = vm_alloc_zclass();
    vaclass->name = "VertexArray";
    zclass_add_method(vaclass,"__construct__", &VertexArray__construct);
    zclass_add_method(vaclass,"resize", &VertexArray__resize);
    zclass_add_method(vaclass,"setPrimitiveType", &VertexArray__setPrimType);
    zclass_add_method(vaclass,"setKth", &VertexArray__setKth);
    zclass_add_method(vaclass,"__del__", &VertexArray__del);

    fontclass = vm_alloc_zclass();
    fontclass->name = "Font";
    zclass_add_method(fontclass,"__construct__", &Font__construct);
    zclass_add_method(fontclass,"loadFromFile", &Font__loadFromFile);
    zclass_add_method(fontclass,"__del__", &Font__del);

    spriteclass = vm_alloc_zclass();
    spriteclass->name = "Sprite";
    zclass_add_method(spriteclass,"__construct__", &Sprite__construct);
    zclass_add_method(spriteclass,"setTexture", &Sprite__setTexture);
    zclass_add_method(spriteclass,"__del__", &Sprite__del);

    textclass = vm_alloc_zclass();
    textclass->name = "Text";
    zclass_add_method(textclass,"__construct__", &Text__construct);
    zclass_add_method(textclass,"setCharacterSize", &Text__setCharacterSize);
    zclass_add_method(textclass,"setString", &Text__setString);
    zclass_add_method(textclass,"setPosition", &Text__setPostion);
    zclass_add_method(textclass,"setFont", &Text__setFont);
    zclass_add_method(textclass,"setFillColor", &Text__setFillColor);
    zclass_add_method(textclass,"__del__", &Text__del);

    timeclass = vm_alloc_zclass();
    timeclass->name = "Time";
    zclass_add_method(timeclass,"asSeconds", &Time__asSeconds);
    zclass_add_method(timeclass,"__del__", &Time__del);

    vector2fclass = vm_alloc_zclass();
    vector2fclass->name = "Vector2f";
    zclass_addmember(vector2fclass,"x", nil);
    zclass_addmember(vector2fclass,"y", nil);

    floatrectclass = vm_alloc_zclass();
    floatrectclass->name = "FloatRect";
    
    zclass_addmember(floatrectclass,"width", nil);
    zclass_addmember(floatrectclass,"height", nil);
    zclass_addmember(floatrectclass,"top", nil);
    zclass_addmember(floatrectclass,"left", nil);
    zclass_add_method(floatrectclass,"intersects", &FloatRect__intersects);

    vm_mark_important(timeclass);
    vm_mark_important(vector2fclass);
    vm_mark_important(floatrectclass);

    // Add classes to module
    zmodule *sfml = vm_alloc_zmodule();
    sfml->name = "sfml";
    zmodule_add_member(sfml,"RenderWindow", zobj_from_class(renderwinclass));
    zmodule_add_member(sfml,"Circle", zobj_from_class(circleclass));
    zmodule_add_member(sfml,"Color", zobj_from_class(colorclass));
    zmodule_add_member(sfml,"Rectangle", zobj_from_class(rectclass));
    zmodule_add_member(sfml,"Event", zobj_from_class(evclass));
    zmodule_add_member(sfml,"Clock", zobj_from_class(clockclass));
    zmodule_add_member(sfml,"VertexArray", zobj_from_class(vaclass));
    zmodule_add_member(sfml,"Font", zobj_from_class(fontclass));
    zmodule_add_member(sfml,"Text", zobj_from_class(textclass));
    zmodule_add_member(sfml,"Texture", zobj_from_class(textureclass));
    zmodule_add_member(sfml,"Sprite", zobj_from_class(spriteclass));
    zmodule_add_member(sfml,"Vector2f", zobj_from_class(vector2fclass));

    zmodule_add_member(sfml,"getMousePosition", zobj_from_function("getMousePosition", &getMousePosition));

    zmodule_add_member(sfml,"EventClosed", zobj_from_int(sf::Event::Closed));
    zmodule_add_member(sfml,"EventKeyPressed", zobj_from_int(sf::Event::KeyPressed));
    zmodule_add_member(sfml,"EventMouseButtonPressed", zobj_from_int(sf::Event::MouseButtonPressed));
    zmodule_add_member(sfml,"EventMouseMoved", zobj_from_int(sf::Event::MouseMoved));
    zmodule_add_member(sfml,"KeyboardA", zobj_from_int(sf::Keyboard::A));
    zmodule_add_member(sfml,"KeyboardS", zobj_from_int(sf::Keyboard::S));
    zmodule_add_member(sfml,"KeyboardD", zobj_from_int(sf::Keyboard::D));
    zmodule_add_member(sfml,"KeyboardW", zobj_from_int(sf::Keyboard::W));
    zmodule_add_member(sfml,"KeyboardUp", zobj_from_int(sf::Keyboard::Up));
    zmodule_add_member(sfml,"KeyboardDown", zobj_from_int(sf::Keyboard::Down));
    zmodule_add_member(sfml,"KeyboardLeft", zobj_from_int(sf::Keyboard::Left));
    zmodule_add_member(sfml,"KeyboardRight", zobj_from_int(sf::Keyboard::Right));
    zmodule_add_member(sfml,"KeyboardEsc", zobj_from_int(sf::Keyboard::Escape));
    zmodule_add_member(sfml,"KeyboardEnter", zobj_from_int(sf::Keyboard::Enter));
    // More keymappings to be added later

    zmodule_add_member(sfml,"LinesStrip", zobj_from_int(sf::LinesStrip));
    zmodule_add_member(sfml,"MouseLeft", zobj_from_int(sf::Mouse::Left));

    return zobj_from_module(sfml);
}
// Global zmodule functions
zobject getMousePosition(zobject *args, int n)
{
    if (n != 1)
        return z_err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
    {
        return z_err(TypeError, "Argument 1 must be an instance of RenderWindow");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(zclassobj_get(k,".handle"));
    zclass_object *ki = vm_alloc_zclassobj(vector2fclass);
    sf::Vector2i v = sf::Mouse::getPosition(*w);
    
    zclassobj_set(ki,"x",zobj_from_double(v.x));
    zclassobj_set(ki,"y",zobj_from_double(v.y));
    
    return zobj_from_classobj(ki);
}
// RenderWindow
zobject RenderWindow__construct(zobject *args, int n)
{
    if (n != 4)
        return z_err(ArgumentError, "4 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
        return z_err(TypeError, "self must be an instance of RenderWindow");
    if (args[1].type != 'i' || args[2].type != 'i' || args[3].type != 's')
        return z_err(TypeError, "Invalid types of arguments!");
    zstr* title = AS_STR(args[3]);
    sf::RenderWindow *w = new sf::RenderWindow(sf::VideoMode(args[1].i, args[2].i), title->val);
    zclass_object *k = (zclass_object *)args[0].ptr;
    zclassobj_set(k,".handle",zobj_from_ptr((void*)w));// we use .handle so that user can't change it's value
    return nil;                                            //
}
zobject RenderWindow__clear(zobject *args, int n)
{
    if (n != 1 && n != 2)
    {
        return z_err(ArgumentError, "1 or 2 arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
    {
        return z_err(TypeError, "self must be an instance of RenderWindow");
    }
    sf::Color c = sf::Color::Black;
    if (n == 2)
    {
        if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != colorclass)
            return z_err(TypeError, "Argument 2 must be an instance of Color");
        zclass_object *ki = (zclass_object *)args[1].ptr;
        sf::Color *color = (sf::Color *)AS_PTR(zclassobj_get(ki,".handle"));
        c = *color;
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(zclassobj_get(k,".handle"));
    w->clear(c);
    return nil;
}
zobject RenderWindow__close(zobject *args, int n)
{
    if (n != 1)
        return z_err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
        return z_err(TypeError, "self must be an instance of RenderWindow");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(zclassobj_get(k,".handle"));
    w->close();
    delete w;
    zclassobj_set(k,".handle",nil);
    return nil;
}
zobject RenderWindow__display(zobject *args, int n)
{
    if (n != 1)
    {
        return z_err(ArgumentError, "1 argument needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
    {
        return z_err(TypeError, "self must be an instance of RenderWindow");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(zclassobj_get(k,".handle"));;
    w->display();
    return nil;
}
zobject RenderWindow__draw(zobject *args, int n)
{
    if (n != 2)
    {
        return z_err(ArgumentError, "2 arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
    {
        return z_err(TypeError, "self must be an instance of RenderWindow");
    }
    if (args[1].type != Z_OBJ)
    {
        return z_err(TypeError, "Argument must be a drawable sfml object!");
    }
    zclass_object *obj = (zclass_object *)args[1].ptr;

    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(zclassobj_get(k,".handle"));;
    if (obj->_klass == circleclass)
    {
        sf::CircleShape *d = (sf::CircleShape *)AS_PTR(zclassobj_get(obj,".handle"));;
        w->draw(*d);
    }
    else if (obj->_klass == rectclass)
    {
        sf::RectangleShape *d = (sf::RectangleShape *)AS_PTR(zclassobj_get(obj,".handle"));;
        w->draw(*d);
    }
    else if (obj->_klass == spriteclass)
    {
        sf::Sprite *d = (sf::Sprite *)AS_PTR(zclassobj_get(obj,".handle"));
        w->draw(*d);
    }
    else if (obj->_klass == textclass)
    {
        sf::Text *d = (sf::Text *)AS_PTR(zclassobj_get(obj,".handle"));
        w->draw(*d);
    }
    else if (obj->_klass == vaclass)
    {
        sf::VertexArray *d = (sf::VertexArray *)AS_PTR(zclassobj_get(obj,".handle"));
        w->draw(*d);
    }
    else
        return z_err(TypeError, "Argument must be a drawable sfml object!");
    return nil;
}
zobject RenderWindow__pollevent(zobject *args, int n)
{
    if (n != 2)
    {
        return z_err(ArgumentError, "2 argument needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
    {
        return z_err(TypeError, "self must be an instance of RenderWindow");
    }
    if (args[1].type != Z_OBJ)
    {
        return z_err(TypeError, "Argument must be an instance of Event class.");
    }
    zclass_object *obj = (zclass_object *)args[1].ptr;
    if (obj->_klass != evclass)
    {
        return z_err(TypeError, "Argument must be an instance of Event class.");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(zclassobj_get(k,".handle"));;
    sf::Event *e = (sf::Event *)AS_PTR(zclassobj_get(obj,".handle"));;
    bool b = w->pollEvent(*e);
    if (b)
    {
        zclassobj_set(obj,"type",zobj_from_int(e->type));
        if (e->type == sf::Event::KeyPressed)
            zclassobj_set(obj,"keycode",zobj_from_int(e->key.code));
        if (e->type == sf::Event::MouseButtonPressed)
            zclassobj_set(obj,"mouseButton",zobj_from_int(e->mouseButton.button));
    }
    return zobj_from_bool(b);
}
zobject RenderWindow__setFrameRateLimit(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 argument needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != renderwinclass)
        return z_err(TypeError, "self must be an instance of RenderWindow");
    if (args[1].type != Z_INT)
        return z_err(TypeError, "Argument 2  must be an integer.");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(zclassobj_get(k,".handle"));;
    w->setFramerateLimit(args[1].i);
    return nil;
}

// Event
zobject Event__construct(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != evclass)
    {
        return z_err(ArgumentError, "1 argument self needed which must be instance of event");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Event *e = new sf::Event;
    zclassobj_set(k,".handle",zobj_from_ptr(e));
    return nil;
}
zobject Event__del(zobject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != evclass)
        return nil;
    zclass_object *ki = (zclass_object *)args[0].ptr;
    zobject ptr = zclassobj_get(ki,".handle");
    if (ptr.type == Z_NIL)
        return nil;
    sf::Event *ev = (sf::Event *)ptr.ptr;
    delete ev;
    zclassobj_set(ki,".handle",nil);
    return nil;
}
// Circle
zobject Circle__construct(zobject *args, int n)
{
    if (n != 1 && n != 2)
    {
        return z_err(ArgumentError, "Two or One arguments needed!");
    }
    float radius = 0;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != circleclass)
    {
        return z_err(TypeError, "self must be an instance of circle class!");
    }
    if (n == 2)
    {
        if (args[1].type != Z_FLOAT)
        {
            return z_err(TypeError, "Radius must be a float!");
        }
        radius = static_cast<float>(args[1].f);
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::CircleShape *c = new sf::CircleShape(radius);
    zclassobj_set(k,".handle", zobj_from_ptr(c));
    
    return nil;
}
zobject Circle__setpos(zobject *args, int n)
{
    if (n != 3)
    {
        return z_err(ArgumentError, "Three arguments needed!");
    }
    float radius = 0;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != circleclass)
    {
        return z_err(TypeError, "self must be an instance of circle class!");
    }
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
    {
        return z_err(TypeError, "Position coordinates must be floats!");
    }

    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::CircleShape *c = (sf::CircleShape *)AS_PTR(zclassobj_get(k,".handle"));
    float x = (float)args[1].f;
    float y = (float)args[2].f;
    c->setPosition(x, y);
    return nil;
}
zobject Circle__setpointcount(zobject *args, int n)
{
    if (n != 2)
    {
        return z_err(ArgumentError, "Two arguments needed!");
    }
    float radius = 0;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != circleclass)
    {
        return z_err(TypeError, "self must be an instance of circle class!");
    }
    if (args[1].type != Z_INT && args[1].type != Z_INT64)
    {
        return z_err(TypeError, "Point count must be an integer!");
    }

    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::CircleShape *c = (sf::CircleShape *)AS_PTR(zclassobj_get(k,".handle"));
    if (args[1].type == Z_INT)
        c->setPointCount(args[1].i);
    else
        c->setPointCount(args[1].l);
    return nil;
}
zobject Circle__setfillcolor(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "Two arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != circleclass)
        return z_err(TypeError, "Argument 1(self) must be an instance of circle class!");
    if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != colorclass)
        return z_err(TypeError, "Argument 2 must be an instance of class Color!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    zclass_object *j = (zclass_object *)args[1].ptr;
    sf::CircleShape *c = (sf::CircleShape *)AS_PTR(zclassobj_get(k,".handle"));
    sf::Color *color = (sf::Color *)AS_PTR(zclassobj_get(j,".handle"));
    c->setFillColor(*color);
    return nil;
}
zobject Circle__del(zobject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != circleclass)
        return nil;
    zclass_object *ki = (zclass_object *)args[0].ptr;
    if (zclassobj_get(ki,".handle").type == Z_NIL)
        return nil;
    sf::CircleShape *circle = (sf::CircleShape *)AS_PTR(zclassobj_get(ki,".handle"));
    delete circle;
    zclassobj_set(ki,".handle",nil);
    return nil;
}
// Rectangle
zobject Rect__construct(zobject *args, int n)
{
    if (n != 3)
    {
        return z_err(ArgumentError, "3 arguments needed!");
    }
    float width = 0;
    float height = 0;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
        return z_err(TypeError, "self must be an instance of Rectangle class!");
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
        return z_err(TypeError, "Width and height must be floats!");

    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RectangleShape *c = new sf::RectangleShape(sf::Vector2f(args[1].f, args[2].f));
    zclassobj_set(k,".handle", zobj_from_ptr(c));
    return nil;
}
zobject Rect__setpos(zobject *args, int n)
{
    if (n != 3)
    {
        return z_err(ArgumentError, "Three arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
    {
        return z_err(TypeError, "self must be an instance of Rectangle class!");
    }
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
    {
        return z_err(TypeError, "Position coordinates must be floats!");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(zclassobj_get(k,".handle"));
    c->setPosition(args[1].f, args[2].f);
    return nil;
}
zobject Rect__setSize(zobject *args, int n)
{
    if (n != 3)
    {
        return z_err(ArgumentError, "Three arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
    {
        return z_err(TypeError, "self must be an instance of Rectangle class!");
    }
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
    {
        return z_err(TypeError, "Size values must be floats!");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(zclassobj_get(k,".handle"));
    c->setSize(sf::Vector2f(args[1].f, args[2].f));
    return nil;
}
zobject Rect__getPosition(zobject *args, int n)
{
    if (n != 1)
        return z_err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
        return z_err(TypeError, "self must be an instance of Rectangle class!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(zclassobj_get(k,".handle"));
    zclass_object *ki = vm_alloc_zclassobj(vector2fclass);
    sf::Vector2f v = c->getPosition();
    zclassobj_set(ki,"x",zobj_from_double(v.x));
    zclassobj_set(ki,"y",zobj_from_double(v.y));
    return zobj_from_classobj(ki);
}
zobject Rect__getGlobalBounds(zobject *args, int n)
{
    if (n != 1)
        return z_err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
        return z_err(TypeError, "self must be an instance of Rectangle class!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(zclassobj_get(k,".handle"));
    zclass_object *ki = vm_alloc_zclassobj(floatrectclass);

    sf::FloatRect v = c->getGlobalBounds();

    zclassobj_set(ki,"width",zobj_from_double(v.width));
    zclassobj_set(ki,"height",zobj_from_double(v.height));
    zclassobj_set(ki,"left",zobj_from_double(v.left));
    zclassobj_set(ki,"top",zobj_from_double(v.top));
    return zobj_from_classobj(ki);
}
zobject Rect__setOutlineThickness(zobject *args, int n)
{
    if (n != 2)
    {
        return z_err(ArgumentError, "Three arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
    {
        return z_err(TypeError, "self must be an instance of Rectangle class!");
    }
    if (args[1].type != Z_FLOAT)
    {
        return z_err(TypeError, "Argument 1 must be a float!");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(zclassobj_get(k,".handle"));
    c->setOutlineThickness(args[1].f);
    return nil;
}
zobject Rect__setfillcolor(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "Two arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
        return z_err(TypeError, "Argument 1(self) must be an instance of Rectangle class!");
    if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != colorclass)
        return z_err(TypeError, "Argument 2 must be an instance of class Color!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    zclass_object *j = (zclass_object *)args[1].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(zclassobj_get(k,".handle"));
    sf::Color *color = (sf::Color *)AS_PTR(zclassobj_get(j,".handle"));
    c->setFillColor(*color);
    return nil;
}
zobject Rect__setOutlineColor(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "Two arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
        return z_err(TypeError, "Argument 1(self) must be an instance of Rectangle class!");
    if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != colorclass)
        return z_err(TypeError, "Argument 2 must be an instance of class Color!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    zclass_object *j = (zclass_object *)args[1].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(zclassobj_get(k,".handle"));
    sf::Color *color = (sf::Color *)AS_PTR(zclassobj_get(j,".handle"));
    c->setOutlineColor(*color);
    return nil;
}
zobject Rect__del(zobject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != rectclass)
        return nil;
    zclass_object *ki = (zclass_object *)args[0].ptr;
    if (zclassobj_get(ki,".handle").type == Z_NIL)
        return nil;
    sf::RectangleShape *rect = (sf::RectangleShape *)AS_PTR(zclassobj_get(ki,".handle"));
    delete rect;
    zclassobj_set(ki,".handle",nil);
    return nil;
}
// Color
zobject Color__construct(zobject *args, int n)
{
    if (n != 4)
    {
        return z_err(ArgumentError, "4 arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != colorclass)
    {
        return z_err(TypeError, "self must be an instance of Color class!");
    }
    if (args[1].type != Z_INT || args[2].type != Z_INT || args[3].type != Z_INT)
    {
        return z_err(TypeError, "RGB values must be integers!");
    }
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Color *c = new sf::Color(args[1].i, args[2].i, args[3].i);
    zclassobj_set(k,".handle", zobj_from_ptr(c));
    return nil;
}
zobject Color__del(zobject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != colorclass)
        return nil;
    zclass_object *ki = (zclass_object *)args[0].ptr;
    if (zclassobj_get(ki,".handle").type == Z_NIL)
        return nil;
    sf::Color *color = (sf::Color *)AS_PTR(zclassobj_get(ki,".handle"));
    delete color;
    zclassobj_set(ki,".handle",nil);
    return nil;
}
// Clock
zobject Clock__construct(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != clockclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of Clock");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Clock *e = new sf::Clock;
    zclassobj_set(k,".handle", zobj_from_ptr(e));
    return nil; // values returned by consructors are ignored anyway
}
zobject Clock__restart(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != clockclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of Clock");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Clock *e = (sf::Clock *)AS_PTR(zclassobj_get(k,".handle"));
    sf::Time *t = new sf::Time(e->restart());
    zclass_object *ki = vm_alloc_zclassobj(timeclass);
    zclassobj_set(ki,".handle", zobj_from_ptr(t));
    return zobj_from_classobj(ki);
}
zobject Clock__del(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != clockclass)
        return nil;
    zclass_object *k = (zclass_object *)args[0].ptr;
    if (zclassobj_get(k,".handle").type == Z_NIL)
        return nil;
    sf::Clock *e = (sf::Clock *)AS_PTR(zclassobj_get(k,".handle"));
    delete e;
    zclassobj_set(k,".handle",nil);
    return nil;
}

// Time
zobject Time__asSeconds(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != timeclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of Time");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Time *t = (sf::Time *)AS_PTR(zclassobj_get(k,".handle"));

    return zobj_from_double(t->asSeconds());
}
zobject Time__del(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != timeclass)
        return nil;
    zclass_object *k = (zclass_object *)args[0].ptr;
    if (zclassobj_get(k,".handle").type == Z_NIL)
        return nil;
    sf::Time *t = (sf::Time *)AS_PTR(zclassobj_get(k,".handle"));
    delete t;
    zclassobj_set(k,".handle",nil);
    return nil;
}
// Texture
zobject Texture__construct(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textureclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of Texture");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Texture *e = new sf::Texture;
    zclassobj_set(k,".handle", zobj_from_ptr(e));
    return nil; // values returned by consructors are ignored anyway
}
zobject Texture__loadFromFile(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textureclass)
        return z_err(TypeError, "Argument 1 must be instance of Texture");
    if (args[1].type != Z_STR)
        return z_err(TypeError, "Argument 2 must be a string!");
    auto fname = AS_STR(args[1]);
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Texture *f = (sf::Texture *)AS_PTR(zclassobj_get(k,".handle"));
    f->loadFromFile(fname->val);
    return nil;
}
zobject Texture__del(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textureclass)
        return nil;
    zclass_object *k = (zclass_object *)args[0].ptr;
    if (zclassobj_get(k,".handle").type == Z_NIL)
        return nil;
    sf::Texture *e = (sf::Texture *)AS_PTR(zclassobj_get(k,".handle"));
    // delete e;
    return nil; // values returned by consructors/destructors are ignored anyway
}
// VertexArray
zobject VertexArray__construct(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != vaclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of VertexArray");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::VertexArray *e = new sf::VertexArray;
    zclassobj_set(k,".handle", zobj_from_ptr(e));
    return nil; // values returned by consructors are ignored anyway
}
zobject VertexArray__setPrimType(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != vaclass)
        return z_err(TypeError, "Argument 1  must be instance of VertexArray");
    if (args[1].type != Z_INT)
        return z_err(TypeError, "Argument 2 must be an integer!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::VertexArray *va = (sf::VertexArray *)AS_PTR(zclassobj_get(k,".handle"));
    va->setPrimitiveType((sf::PrimitiveType)args[1].i);
    return nil;
}
zobject VertexArray__resize(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != vaclass)
        return z_err(TypeError, "Argument 1  must be instance of VertexArray");
    if (args[1].type != Z_INT)
        return z_err(TypeError, "Argument 2 must be an integer!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::VertexArray *va = (sf::VertexArray *)AS_PTR(zclassobj_get(k,".handle"));
    va->resize(args[1].i);
    return nil;
}
zobject VertexArray__setKth(zobject *args, int n)
{
    if (n != 4)
        return z_err(ArgumentError, "3 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != vaclass)
        return z_err(TypeError, "Argument 1  must be instance of VertexArray");
    if (args[1].type != Z_INT)
        return z_err(TypeError, "Argument 1 must be an integer!");
    if (args[2].type != Z_FLOAT || args[3].type != Z_FLOAT)
        return z_err(TypeError, "Argument 3 and 4 must be floats!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::VertexArray *va = (sf::VertexArray *)AS_PTR(zclassobj_get(k,".handle"));
    (*va)[args[1].i].position = sf::Vector2f(args[2].f, args[3].f);
    return nil;
}
zobject VertexArray__del(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != vaclass)
        return nil;
    zclass_object *k = (zclass_object *)args[0].ptr;
    if (zclassobj_get(k,".handle").type == Z_NIL)
        return nil;
    sf::VertexArray *e = (sf::VertexArray *)AS_PTR(zclassobj_get(k,".handle"));
    delete e;
    return nil;
}
// Font
zobject Font__construct(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != fontclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of Font");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Font *e = new sf::Font;
    zclassobj_set(k,".handle", zobj_from_ptr(e));
    return nil; // values returned by consructors are ignored anyway
}
zobject Font__loadFromFile(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != fontclass)
        return z_err(TypeError, "Argument 1 must be instance of Font");
    if (args[1].type != Z_STR)
        return z_err(TypeError, "Argument 2 must be a string!");
    auto fname = AS_STR(args[1]);
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Font *f = (sf::Font *)AS_PTR(zclassobj_get(k,".handle"));
    f->loadFromFile(fname->val);
    return nil;
}
zobject Font__del(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != fontclass)
        return nil;
    zclass_object *k = (zclass_object *)args[0].ptr;
    if (zclassobj_get(k,".handle").type == Z_NIL)
        return nil;
    sf::Font *e = (sf::Font *)AS_PTR(zclassobj_get(k,".handle"));
    // delete e; //Deleting this was causing SegFault
    // even tho no illegal memory access was made by Plutonium
    // Prolly a SFML thing
    return nil; // values returned by consructors are ignored anyway
}
// Text
zobject Text__construct(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of Text");
    zclass_object *k = (zclass_object *)args[0].ptr;
    auto e = new sf::Text;
    zclassobj_set(k,".handle", zobj_from_ptr(e));
    return nil; // values returned by consructors are ignored anyway
}
zobject Text__setCharacterSize(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textclass)
        return z_err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_INT)
        return z_err(TypeError, "Argument 2 must be an integer!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(zclassobj_get(k,".handle"));
    t->setCharacterSize(args[1].i);
    return nil;
}
zobject Text__setPostion(zobject *args, int n)
{
    if (n != 3)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textclass)
        return z_err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
        return z_err(TypeError, "Argument 2 and 3 must be an floats!");
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(zclassobj_get(k,".handle"));
    t->setPosition(sf::Vector2f(args[1].f, args[2].f));
    return nil;
}
zobject Text__setString(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textclass)
        return z_err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_STR)
        return z_err(TypeError, "Argument 2 must be a string!");
    auto str = AS_STR(args[1]);
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(zclassobj_get(k,".handle"));
    t->setString(str->val);
    return nil;
}
zobject Text__setFont(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textclass)
        return z_err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != fontclass)
        return z_err(TypeError, "Argument 2 must be an instance of Font!");
    zclass_object *k1 = (zclass_object *)args[1].ptr;
    sf::Font *f = (sf::Font *)AS_PTR(zclassobj_get(k1,".handle"));
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(zclassobj_get(k,".handle"));
    t->setFont(*(sf::Font *)AS_PTR(zclassobj_get(k1,".handle")));
    vm_mark_important(k1);
    return nil;
}
zobject Text__setFillColor(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textclass)
        return z_err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != colorclass)
        return z_err(TypeError, "Argument 2 must be an instance of Color!");
    zclass_object *k1 = (zclass_object *)args[1].ptr;
    sf::Color *f = (sf::Color *)AS_PTR(zclassobj_get(k1,".handle"));
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(zclassobj_get(k,".handle"));
    t->setFillColor(*f);
    vm_mark_important(k1);
    return nil;
}
zobject Text__del(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != textclass)
        return nil;
    zclass_object *k = (zclass_object *)args[0].ptr;
    if (zclassobj_get(k,".handle").type == Z_NIL)
        return nil;
    sf::Text *e = (sf::Text *)AS_PTR(zclassobj_get(k,".handle"));
    delete e;
    return nil;
}

// Sprite
zobject Sprite__construct(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != spriteclass)
        return z_err(ArgumentError, "1 argument self needed which must be instance of Sprite");
    zclass_object *k = (zclass_object *)args[0].ptr;
    auto e = new sf::Sprite;
    zclassobj_set(k,".handle", zobj_from_ptr(e));
    return nil; // values returned by consructors are ignored anyway
}
zobject Sprite__setTexture(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != spriteclass)
        return z_err(TypeError, "Argument 1 must be instance of Sprite");
    if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != textureclass)
        return z_err(TypeError, "Argument 2 must be an instance of Texture!");
    zclass_object *k1 = (zclass_object *)args[1].ptr;
    sf::Texture *f = (sf::Texture *)AS_PTR(zclassobj_get(k1,".handle"));
    zclass_object *k = (zclass_object *)args[0].ptr;
    sf::Sprite *t = (sf::Sprite *)AS_PTR(zclassobj_get(k,".handle"));
    t->setTexture(*(sf::Texture *)AS_PTR(zclassobj_get(k1,".handle")));
    vm_mark_important(k1);
    return nil;
}
zobject Sprite__del(zobject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != spriteclass)
        return nil;
    zclass_object *k = (zclass_object *)args[0].ptr;
    if (zclassobj_get(k,".handle").type == Z_NIL)
        return nil;
    sf::Sprite *e = (sf::Sprite *)AS_PTR(zclassobj_get(k,".handle"));
    delete e;
    return nil;
}
// FloatRect
zobject FloatRect__intersects(zobject *args, int n)
{
    if (n != 2)
        return z_err(ArgumentError, "2 arguments required");
    if (args[0].type != Z_OBJ || ((zclass_object *)args[0].ptr)->_klass != floatrectclass)
        return z_err(TypeError, "Argument 1 must be an instance of FloatRect");
    if (args[1].type != Z_OBJ || ((zclass_object *)args[1].ptr)->_klass != floatrectclass)
        return z_err(TypeError, "Argument 2 must be an instance of FloatRect");
    zclass_object *k1 = (zclass_object *)args[0].ptr;
    zclass_object *k2 = (zclass_object *)args[1].ptr;
    sf::FloatRect v1;
    sf::FloatRect v2;
    v1.width = AS_DOUBLE(zclassobj_get(k1,"width"));
    v1.height = AS_DOUBLE(zclassobj_get(k1,"height"));
    v1.left = AS_DOUBLE(zclassobj_get(k1,"left"));
    v1.top = AS_DOUBLE(zclassobj_get(k1,"top"));

    v2.width = AS_DOUBLE(zclassobj_get(k2,"width"));
    v2.height = AS_DOUBLE(zclassobj_get(k2,"height"));
    v2.left = AS_DOUBLE(zclassobj_get(k2,"left"));
    v2.top = AS_DOUBLE(zclassobj_get(k2,"top"));

    return zobj_from_bool(v1.intersects(v2));
}
