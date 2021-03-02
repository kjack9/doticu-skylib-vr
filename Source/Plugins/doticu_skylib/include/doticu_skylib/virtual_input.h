/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/interface.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Callback_i;

    class Input_t
    {
    public:
        static constexpr const char* SCRIPT_NAME = "Input";

    public:
        static void Is_Key_Pressed(Int_t key, some<Virtual::Callback_i*> v_callback);                       // IsKeyPressed
        static void Is_Key_Pressed(Int_t key, some<unique<doticu_skylib::Callback_i<Bool_t>>> callback);    // IsKeyPressed

        static void Tap_Key(Int_t key, maybe<Virtual::Callback_i*> v_callback = nullptr);                   // TapKey
        static void Tap_Key(Int_t key, maybe<unique<doticu_skylib::Callback_i<>>> callback = nullptr);      // TapKey

    public:
        static void Close_Menus(maybe<unique<doticu_skylib::Callback_i<Bool_t>>> callback = nullptr);
    };

}}
