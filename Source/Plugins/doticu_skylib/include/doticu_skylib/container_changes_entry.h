/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/enum_extra_type.h"
#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Extra_List_t;

    class Container_Changes_Entry_t // InventoryEntryData
    {
    public:
        static some<Container_Changes_Entry_t*> Create(some<Bound_Object_t*> object);
        static void                             Destroy(some<Container_Changes_Entry_t*> container_changes_entry);

    public:
        maybe<Bound_Object_t*>                  object;     // 00
        maybe<List_t<maybe<Extra_List_t*>>*>    x_lists;    // 08
        s32                                     delta;      // 10
        u32                                     pad_14;     // 14

    public:
        Container_Changes_Entry_t();
        Container_Changes_Entry_t(some<Bound_Object_t*> object);
        Container_Changes_Entry_t(const Container_Changes_Entry_t& other)                   = delete;
        Container_Changes_Entry_t(Container_Changes_Entry_t&& other) noexcept;
        Container_Changes_Entry_t& operator=(const Container_Changes_Entry_t& other)        = delete;
        Container_Changes_Entry_t& operator=(Container_Changes_Entry_t&& other) noexcept;
        ~Container_Changes_Entry_t();

    public:
        Container_Entry_Count_t         Count(Container_Entry_Count_t base_count);
        s32                             Delta(Container_Entry_Count_t base_count);
        s32                             Minimum_Delta(Container_Entry_Count_t base_count);
        s32                             Maximum_Delta(Container_Entry_Count_t base_count);
        s32                             Increment_Delta(Container_Entry_Count_t base_count, Container_Entry_Count_t amount);
        s32                             Decrement_Delta(Container_Entry_Count_t base_count, Container_Entry_Count_t amount);

        Vector_t<some<Extra_List_t*>>   Extra_Lists();
        Container_Entry_Count_t         Extra_Lists_Count();
        s32                             Add(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);
        s32                             Add_Copy_Or_Increment(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);
        s32                             Remove(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);
        s32                             Remove_And_Destroy(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);
        s32                             Increment_Count(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list, s16 amount);
        s32                             Decrement_Count(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list, s16 amount);
        maybe<s32>                      Try_To_Consume(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);

        Bool_t                          Has_Quest_Item();
        Bool_t                          Should_Be_Destroyed();

        void                            Destroy_Extra_Lists();

    public:
        void Log(std::string indent);
    };
    STATIC_ASSERT(sizeof(Container_Changes_Entry_t) == 0x18);

    /*
    To move an x_list between containers:
        ALIASES:
            this seems to always appear with Extra_Reference_Handle_t. see what happens with Reference_t::Do_Add_Item.
        CANNOT_WEAR:
            probably should be deleted?
        FROM_ALIAS:
            see what happens with Reference_t::Do_Add_Item.
        HOTKEY:
            probably should be deleted.
        LEVELED_ITEM:
            should be deleted.
        OUTFIT:
            should be deleted.
        REFERENCE_HANDLE:
            if representative, it must have its linked reference's handle set to the new container.
        UNIQUE_ID:
            its form_id must be set to the new container, and it's unique_id set to the next available id on new container.
        WORN:
            should be deleted.
        WORN_LEFT:
            should be deleted.

        there may be more like SHOULD_WEAR, but I've not yet seen them.
        we can just use Reference_t::Do_Add_Item, but it may be too slow when scaled to our purposes.
    */

}
