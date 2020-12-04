/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/script.h"

#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_list.inl"

#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib {

    Reference_t* Reference_t::Create(Form_t* base, u32 count, Reference_t* at, Bool_t force_persist, Bool_t initially_disable)
    {
        static auto place_at_me = reinterpret_cast
            <Reference_t*(*)(Virtual::Machine_t*, Virtual::Stack_ID_t, Reference_t*, Form_t*, u32, Bool_t, Bool_t)>
            (Game_t::Base_Address() + Offset_e::PLACE_AT_ME);
        return place_at_me(Virtual::Machine_t::Self(), 0, at, base, count, force_persist, initially_disable);
    }

    Reference_t* Reference_t::From_Handle(Reference_Handle_t reference_handle)
    {
        static auto from_reference_handle = reinterpret_cast
            <Reference_t*(*)(Reference_Handle_t&, Reference_t*&)>
            (Game_t::Base_Address() + Offset_e::FROM_REFERENCE_HANDLE_1);

        Reference_t* reference = nullptr;
        from_reference_handle(reference_handle, reference);
        return reference;
    }

    Bool_t Reference_t::Is_Persistent()
    {
        return (form_flags & Form_Flags_e::IS_PERSISTENT) != 0;
    }

    Bool_t Reference_t::Is_Temporary()
    {
        return !Is_Persistent();
    }

    Bool_t Reference_t::Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id)
    {
        SKYLIB_ASSERT_SOME(quest);

        Aliases_x* xaliases = xlist.Get<Aliases_x>();
        if (xaliases) {
            for (Index_t idx = 0, end = xaliases->instances.count; idx < end; idx += 1) {
                Aliases_x::Instance_t* instance = xaliases->instances.entries[idx];
                if (instance && instance->quest == quest && instance->alias_base && instance->alias_base->id == alias_id) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    const char* Reference_t::Name()
    {
        static auto get_name = reinterpret_cast
            <const char*(*)(Reference_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::GET_NAME));
        return get_name(this);
    }

    String_t Reference_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

    Location_t* Reference_t::Location()
    {
        Cell_t* cell = Cell();
        if (cell) {
            return Cell()->Location();
        } else {
            return nullptr;
        }
    }

    Cell_t* Reference_t::Cell()
    {
        return parent_cell;
    }

    void Reference_t::Select_In_Console()
    {
        Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            script->Command((std::string("prid ") + Form_ID_String().data).c_str());
            script->Execute(this);
            delete script;
        }
    }

    void Reference_t::Enable()
    {
        static Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            script->Command("Enable");
            script->Execute(this);
            delete script;
        }
    }

    void Reference_t::Disable()
    {
        static Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            script->Command("Disable");
            script->Execute(this);
            delete script;
        }
    }

    void Reference_t::Mark_For_Delete(Bool_t do_disable)
    {
        static Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            if (do_disable) {
                script->Command("Disable");
                script->Execute(this);
            }
            if (Is_Persistent()) {
                script->Command("MarkForDelete");
                script->Execute(this);
            }
            delete script;
        }
    }

}
