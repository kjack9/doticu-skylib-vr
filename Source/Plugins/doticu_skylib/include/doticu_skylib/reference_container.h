/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference_container_entry.h"

namespace doticu_skylib {

    // we may want to rename Container_Entry_t to Component_Container_Entry_t and Container_c to Component_Container_t

    // also, we could set container_changes on reference to nullptr while we operate. that way we "lock" the container.
    // if there is a new container_changes by the time we're done, it's probably safe enough to delete it. maybe we could
    // make sure quest items are moved over.

    class Bound_Object_t;
    class Container_c;
    class Container_Changes_t;
    class Container_Changes_Entry_t;
    class Extra_List_t;
    class Reference_t;

    class Reference_Container_t
    {
    public:
        some<Reference_t*>                      reference;
        some<Container_c*>                      base_container;
        maybe<Container_Changes_t*>             reference_container;
        Vector_t<Reference_Container_Entry_t>   entries;
        Bool_t                                  has_changed;

    public:
        Reference_Container_t(some<Reference_t*> reference);
        Reference_Container_t(const Reference_Container_t& other)                   = delete;
        Reference_Container_t(Reference_Container_t&& other) noexcept;
        Reference_Container_t& operator =(const Reference_Container_t& other)       = delete;
        Reference_Container_t& operator =(Reference_Container_t&& other) noexcept   = delete;
        ~Reference_Container_t();

    public:
        Bool_t                              Is_Valid() const;
        Bool_t                              Has_Quest_Item() const;
        Bool_t                              Has_Entry(some<Bound_Object_t*> object);
        Bool_t                              Has_Changed() const;
        void                                Has_Changed(Bool_t value);

        some<Reference_t*>                  Reference() const;

        some<Container_c*>                  Some_Base_Container();
        maybe<Container_Changes_t*>         Maybe_Reference_Container();
        some<Container_Changes_t*>          Some_Reference_Container();

        maybe<Reference_Container_Entry_t*> Maybe_Entry(some<Bound_Object_t*> object);
        some<Reference_Container_Entry_t*>  Some_Entry(some<Bound_Object_t*> object);

        size_t                              Count() const;

        Container_Entry_Count_t             Count(some<Bound_Object_t*> object);
        Container_Entry_Count_t             Increment_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount);
        Container_Entry_Count_t             Decrement_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount);
        Container_Entry_Count_t             Remove_Count_To(some<Bound_Object_t*> object,
                                                            Container_Entry_Count_t amount,
                                                            some<Reference_t*> to);

        Container_Entry_Count_t             Add(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Add_Copy_Or_Increment(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Remove(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Remove_And_Destroy(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Remove_To(some<Bound_Object_t*> object,
                                                      some<Extra_List_t*> extra_list,
                                                      some<Reference_t*> to);
        maybe<Container_Entry_Count_t>      Try_To_Consume(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);

    public:
        Reference_Container_Entry_t&        operator [](size_t index);
        const Reference_Container_Entry_t&  operator [](size_t index) const;

    public:
        void Log(std::string indent = "");
    };

}
