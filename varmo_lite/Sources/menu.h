/*
 * Copyright (c) 2015, 2016 arduino-menusystem
 * Licensed under the MIT license (see LICENSE)
 */

#ifndef MENU_H
#define MENU_H


class MenuSystem;

class MenuComponent
{
    friend class MenuSystem;
public:
    MenuComponent(const char* name);

    void set_name(const char* name);

    /**
     * Gets the original name
     *
     * Returns the original name assigned in the constructor or via set_name.
     */
    const char* get_name() const;

    virtual MenuComponent* select() = 0;
    virtual void reset() = 0;

    /**
     * Returns true if the MenuComponent's value is being edited; false
     * otherwise.
     */
    virtual bool is_editing_value() const { return false; }

protected:
    virtual bool next_value() { return false; }
    virtual bool prev_value() { return false; }

    const char* _name;
};


class MenuItem : public MenuComponent
{
public:
    MenuItem(const char* name);

    void set_select_function(void (*on_select)(MenuItem*));

    virtual MenuComponent* select();
    virtual void reset();

protected:
    void (*_on_select)(MenuItem*);
};

/**
 * A MenuItem executes MenuSystem::back() when selected.
 */
class BackMenuItem : public MenuItem
{
public:
    BackMenuItem(MenuSystem* ms, const char* name = "back");

    virtual MenuComponent* select();

protected:
    MenuSystem* menu_system;
};

class NumericMenuItem;


class NumericMenuItem : public MenuItem
{


public:
    /**
     * @param name The name of the menu item.
     * @param value Default value.
     * @param minValue The minimum value.
     * @param maxValue The maximum value.
     * @param increment How much the value should be incremented by.
     * @param valueFormatter The custom formatter. If NULL the String float
     *                       formatter will be used.
     */
    NumericMenuItem(const char* name, float value, float minValue,
                    float maxValue, float increment=1.0);

    /**
     * Toggles edit mode and invokes the _on_select function (if not NULL).
     */
    virtual MenuComponent* select();

    float get_value() const { return _value; }
    void set_value(float value) { _value = value; }

    /**
     * Returns true if this menuitem is in editing mode. i.e. it is using next()
     * and prev() events to increase and decrease its value.
     */
    virtual bool is_editing_value() const;

protected:
    virtual bool next_value();
    virtual bool prev_value();

protected:
    float _value;
    float _minValue;
    float _maxValue;
    float _increment;
    bool _editing_value;
};

class Menu : public MenuComponent
{
    friend class MenuSystem;
public:
    Menu(const char* name);

    bool next(bool loop=false);
    bool prev(bool loop=false);
    MenuComponent* activate();
    virtual MenuComponent* select();
    virtual void reset();

    void add_item(MenuItem* pItem, void (*on_select)(MenuItem*) = 0x0);
    Menu const* add_menu(Menu* pMenu);

    void set_parent(Menu* pParent);
    Menu const* get_parent() const;

    MenuComponent const* get_selected() const;
    MenuComponent const* get_menu_component(char index) const;

    char get_num_menu_components() const;
    char get_cur_menu_component_num() const;

private:
    MenuComponent* _p_sel_menu_component;
    MenuComponent** _menu_components;
    Menu* _p_parent;
    char _num_menu_components;
    char _cur_menu_component_num;
};


class MenuSystem
{
public:
    MenuSystem();

    bool next(bool loop=false);
    bool prev(bool loop=false);
    void reset();
    void select(bool reset=false);
    bool back();

    void set_root_menu(Menu* p_root_menu);

    Menu const* get_current_menu() const;

private:
    Menu* _p_root_menu;
    Menu* _p_curr_menu;
};


#endif
