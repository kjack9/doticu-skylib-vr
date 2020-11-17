/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_handle.h"

namespace doticu_skylib { namespace Virtual {

    class Class_t;
    class Variable_t;

    class Object_t {
    public:
        enum class Offset_e : Word_t {
            INCREMENT_LOCK  = 0x01234360, // 97468
            DECREMENT_LOCK  = 0x01234410, // 97469
            DESTROY         = 0x01233670, // 97462
        };

        template <typename Type>
        static Object_t* Fetch(Type* instance, String_t class_name, Bool_t do_auto_decrement = false);
        template <typename Type>
        static Object_t* Create(Type* instance, String_t class_name);
        template <typename Type>
        static Object_t* Create(Type* instance, Class_t* class_info);

    public:
        UInt64 unk_00; // 00
        Class_t* info; // 08
        String_t unk_10; // 10
        void* unk_18; // 18
        volatile Handle_t handle; // 20
        volatile SInt32 lock; // 28
        UInt32 pad_2C; // 2C
        //Variable_t variables[0]; // 30

        void Destroy();
        void Increment_Lock();
        u32 Decrement_Lock();

        Handle_t Handle();
        Variable_t* Variables();
        Variable_t* Variable(String_t variable_name);
        Variable_t* Property(String_t property_name);

        void Log_Variables();
    };
    STATIC_ASSERT(sizeof(Object_t) == 0x30);

}}

#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Type>
    inline Object_t* Object_t::Fetch(Type* instance, String_t class_name, Bool_t do_auto_decrement)
    {
        Handle_t handle(instance);
        if (handle.Is_Valid()) {
            Object_t* object = nullptr;
            if (Machine_t::Self()->Find_Bound_Object(handle, class_name, &object)) {
                if (do_auto_decrement) {
                    object->Decrement_Lock();
                }
                return object;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

}}
