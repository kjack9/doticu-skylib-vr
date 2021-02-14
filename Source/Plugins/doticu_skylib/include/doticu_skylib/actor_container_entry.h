/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_Container_t;
    class Bound_Object_t;
    class Container_Entry_t;
    class Container_Changes_Entry_t;

    class Actor_Container_Entry_t
    {
    public:
        maybe<Container_Entry_t*>           base_entry;
        maybe<Container_Changes_Entry_t*>   reference_entry;

    public:
        Actor_Container_Entry_t(some<Actor_Container_t*> owner, some<Bound_Object_t*> object);
        Actor_Container_Entry_t(maybe<Container_Entry_t*> base_entry, maybe<Container_Changes_Entry_t*> reference_entry);
        Actor_Container_Entry_t(const Actor_Container_Entry_t& other);
        Actor_Container_Entry_t(Actor_Container_Entry_t&& other) noexcept;
        Actor_Container_Entry_t& operator =(const Actor_Container_Entry_t& other);
        Actor_Container_Entry_t& operator =(Actor_Container_Entry_t&& other) noexcept;
        ~Actor_Container_Entry_t();

    public:
        some<Bound_Object_t*>               Some_Object();
        some<Container_Changes_Entry_t*>    Some_Reference_Entry(some<Actor_Container_t*> owner);

        Container_Entry_Count_t             Base_Count();
        Container_Entry_Count_t             Count();

        Container_Entry_Count_t             Increment_Count(some<Actor_Container_t*> owner, Container_Entry_Count_t amount);
        Container_Entry_Count_t             Decrement_Count(some<Actor_Container_t*> owner, Container_Entry_Count_t amount);

    public:
        void Log(std::string indent = "");
    };

}
