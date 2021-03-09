/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_owner.h"

namespace doticu_skylib {

    some<Extra_Owner_t*> Extra_Owner_t::Create(Form_Owner_t owner)
    {
        some<Extra_Owner_t*> x_owner = Extra_Data_t::Create<Extra_Owner_t>();

        x_owner->owner = owner;

        return x_owner;
    }

    void Extra_Owner_t::Destroy(some<Extra_Owner_t*> x_owner)
    {
        SKYLIB_ASSERT_SOME(x_owner);

        Extra_Data_t::Destroy<Extra_Owner_t>(x_owner);
    }

}
