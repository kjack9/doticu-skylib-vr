/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Form_t;

    class Description_c : public Form_Data_c // TESDescription
    {
    public:
        class Offset_e : Enum_t<Word_t>
        {
        public:
            enum
            {
                GET = 0x00190480,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Description_c(); // 0

    public:
        u32 description_offset;     // 8
        u32 description_text_id;    // C

    public:
        DString_t&& Description_DString(some<Form_t*> parent, u32 sub_type = 'DESC');
        void        Description_DString(DString_t& result, some<Form_t*> parent, u32 sub_type = 'DESC');
    };
    STATIC_ASSERT(sizeof(Description_c) == 0x10);

}
