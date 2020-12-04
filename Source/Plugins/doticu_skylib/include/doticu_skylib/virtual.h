/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PapyrusVM.h"

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib { namespace Virtual {

    using Registry_t        = VMClassRegistry;

    using Stack_ID_t        = u32;
    using Raw_Handle_t      = u64;
    using Virtual_Type_t    = u32; // takes Form_Type_e

    class Array_t;
    class Callback_i;
    class Callback_t;
    class Class_t;
    class Machine_t;
    class Object_t;
    class Variable_t;

    template <typename T>
    class Array_Variable_t;
    class Bool_Variable_t;
    class Int_Variable_t;
    class String_Variable_t;

}}
