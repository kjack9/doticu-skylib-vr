/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    Bool_t Record_Header_Base_t::Has_Type(const char* type)
    {
        SKYLIB_ASSERT(type);
        SKYLIB_ASSERT(type[0] && type[1] && type[2] && type[3]);

        return
            this->type[0] == type[0] &&
            this->type[1] == type[1] &&
            this->type[2] == type[2] &&
            this->type[3] == type[3];
    }

    void Record_Header_t::Log(Mod_t* mod, std::string indent)
    {
        static Byte_t data[256];

        SKYLIB_LOG(indent + "Record_Header_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "type     :     %c%c%c%c", type[0], type[1], type[2], type[3]);
        SKYLIB_LOG(indent + SKYLIB_TAB + "body_size: %8u", body_size);
        SKYLIB_LOG(indent + SKYLIB_TAB + "form_id  : %8.8X", form_id);

        if (mod->Has_Current_Sub_Record_Type("EDID")) {
            mod->Read(data, sizeof(data));
            data[255] = 0;
            SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: %s", data);
            mod->Seek_Next_Sub_Record();
        }

        SKYLIB_LOG(indent + "}");
    }

    Bool_t Record_Group_t::Has_Inner_Type(const char* type)
    {
        SKYLIB_ASSERT(type);
        SKYLIB_ASSERT(type[0] && type[1] && type[2] && type[3]);

        return
            this->inner_type[0] == type[0] &&
            this->inner_type[1] == type[1] &&
            this->inner_type[2] == type[2] &&
            this->inner_type[3] == type[3];
    }

    size_t Mod_t::Active_Mod_Count()
    {
        return Active_Heavy_Mod_Count() + Active_Light_Mod_Count();
    }

    size_t Mod_t::Active_Heavy_Mod_Count()
    {
        return Game_t::Self()->heavy_mods.count;
    }

    size_t Mod_t::Active_Light_Mod_Count()
    {
        return Game_t::Self()->light_mods.count;
    }

    Vector_t<some<Mod_t*>> Mod_t::Active_Mods()
    {
        Array_t<Mod_t*>& heavy_mods = Game_t::Self()->heavy_mods;
        Array_t<Mod_t*>& light_mods = Game_t::Self()->light_mods;

        Vector_t<some<Mod_t*>> results;
        results.reserve(heavy_mods.count + light_mods.count);

        for (Index_t idx = 0, end = heavy_mods.count; idx < end; idx += 1) {
            Mod_t* mod = heavy_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        for (Index_t idx = 0, end = light_mods.count; idx < end; idx += 1) {
            Mod_t* mod = light_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Vector_t<some<Mod_t*>> Mod_t::Active_Heavy_Mods()
    {
        Array_t<Mod_t*>& heavy_mods = Game_t::Self()->heavy_mods;

        Vector_t<some<Mod_t*>> results;
        results.reserve(heavy_mods.count);

        for (Index_t idx = 0, end = heavy_mods.count; idx < end; idx += 1) {
            Mod_t* mod = heavy_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Vector_t<some<Mod_t*>> Mod_t::Active_Light_Mods()
    {
        Array_t<Mod_t*>& light_mods = Game_t::Self()->light_mods;

        Vector_t<some<Mod_t*>> results;
        results.reserve(light_mods.count);

        for (Index_t idx = 0, end = light_mods.count; idx < end; idx += 1) {
            Mod_t* mod = light_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Array_t<Mod_t*>& Mod_t::Active_Heavy_Mods_2()
    {
        return Game_t::Self()->heavy_mods;
    }

    Array_t<Mod_t*>& Mod_t::Active_Light_Mods_2()
    {
        return Game_t::Self()->light_mods;
    }

    static void Log_Mods(const char* title, Vector_t<some<Mod_t*>> mods)
    {
        #define TAB "    "

        _MESSAGE("%s {", title);
        for (size_t idx = 0, end = mods.size(); idx < end; idx += 1) {
            Mod_t* mod = mods[idx];
            _MESSAGE(TAB "index: %6zu, mod: %s", idx, mod->Name());
        }
        _MESSAGE("}");

        #undef TAB
    }

    void Mod_t::Log_Active_Mods()
    {
        doticu_skylib::Log_Mods("Log_Active_Mods", Active_Mods());
    }

    void Mod_t::Log_Active_Heavy_Mods()
    {
        doticu_skylib::Log_Mods("Log_Active_Heavy_Mods", Active_Heavy_Mods());
    }

    void Mod_t::Log_Active_Light_Mods()
    {
        doticu_skylib::Log_Mods("Log_Active_Light_Mods", Active_Light_Mods());
    }

    maybe<Mod_t*> Mod_t::Active_Mod(some<const char*> mod_name)
    {
        SKYLIB_ASSERT_SOME(mod_name);

        Array_t<Mod_t*>& heavy_mods = Game_t::Self()->heavy_mods;
        Array_t<Mod_t*>& light_mods = Game_t::Self()->light_mods;

        for (Index_t idx = 0, end = heavy_mods.count; idx < end; idx += 1) {
            Mod_t* mod = heavy_mods.entries[idx];
            if (mod) {
                if (CString_t::Is_Same(mod_name, mod->Name(), true)) {
                    return mod;
                }
            }
        }

        for (Index_t idx = 0, end = light_mods.count; idx < end; idx += 1) {
            Mod_t* mod = light_mods.entries[idx];
            if (mod) {
                if (CString_t::Is_Same(mod_name, mod->Name(), true)) {
                    return mod;
                }
            }
        }

        return nullptr;
    }

    some<Mod_t*> Mod_t::Skyrim()
    {
        static maybe<Mod_t*> skyrim = Active_Mod("Skyrim.esm");
        SKYLIB_ASSERT(skyrim);
        return skyrim;
    }

    Bool_t Mod_t::Is_Active()
    {
        return (mod_flags & Mod_Flags_e::IS_ACTIVE) != 0;
    }

    Bool_t Mod_t::Is_Heavy()
    {
        return !Is_Light();
    }

    Bool_t Mod_t::Is_Light()
    {
        return (mod_flags & Mod_Flags_e::IS_LIGHT) != 0;
    }

    Bool_t Mod_t::Has_Current_Record_Type(const char* type)
    {
        return current_record_header.Has_Type(type);
    }

    Bool_t Mod_t::Has_Current_Sub_Record_Type(const char* type)
    {
        return current_sub_record_header.Has_Type(type);
    }

    const char* Mod_t::Name()
    {
        return static_cast<const char*>(file_name);
    }

    maybe<Index_t> Mod_t::Heavy_Index()
    {
        if (Is_Heavy()) {
            if (heavy_index == 0xFF) {
                return none<Index_t>();
            } else {
                return maybe<Index_t>(static_cast<Index_t>(heavy_index));
            }
        } else {
            return none<Index_t>();
        }
    }

    maybe<Index_t> Mod_t::Light_Index()
    {
        if (Is_Light()) {
            if (light_index == 0xFFFF) {
                return none<Index_t>();
            } else {
                return maybe<Index_t>(static_cast<Index_t>(light_index));
            }
        } else {
            return none<Index_t>();
        }
    }

    Bool_t Mod_t::Seek(u32 offset)
    {
        static auto seek = reinterpret_cast
            <Bool_t(*)(Mod_t*, u32)>
            (Game_t::Base_Address() + Mod_t::Offset_e::SEEK);

        return seek(this, offset);
    }

    Bool_t Mod_t::Seek_Next_Sub_Record()
    {
        static auto seek_next_sub_record = reinterpret_cast
            <Bool_t(*)(Mod_t*)>
            (Game_t::Base_Address() + Mod_t::Offset_e::SEEK_NEXT_SUB_RECORD);

        return seek_next_sub_record(this);
    }

    void Mod_t::Read(void* destination, u32 size)
    {
        static auto read = reinterpret_cast
            <void(*)(Mod_t*, void*, u32)>
            (Game_t::Base_Address() + Mod_t::Offset_e::READ);

        read(this, destination, size);
    }

    Bool_t Mod_t::Find_Record(const char* type, Form_ID_t form_id)
    {
        for (Index_t offset = 0; Seek(offset) && offset < file_size;) {
            if (Has_Current_Record_Type("GRUP")) {
                Record_Group_t& record_group = reinterpret_cast<Record_Group_t&>(current_record_header);
                if (record_group.Has_Inner_Type(type)) {
                    offset += sizeof(Record_Header_t);
                } else {
                    offset += sizeof(Record_Header_t) + current_record_header.body_size;
                }
            } else {
                if (Has_Current_Record_Type(type) && current_record_header.form_id == form_id) {
                    return true;
                } else {
                    offset += sizeof(Record_Header_t) + current_record_header.body_size;
                }
            }
        }
        return false;
    }

    String_t Mod_t::Editor_ID(const char* type, Form_ID_t form_id)
    {
        if (Find_Record(type, form_id)) {
            if (Has_Current_Sub_Record_Type("EDID")) {
                char editor_id[256];
                Read(editor_id, sizeof(editor_id));
                editor_id[255] = 0;
                return editor_id;
            } else {
                return "";
            }
        } else {
            return "";
        }
    }

    void Mod_t::Log_Records(std::string indent)
    {
        SKYLIB_LOG(indent + "Mod_t::Log_Records");
        SKYLIB_LOG(indent + "{");

        for (Index_t offset = 0; Seek(offset) && offset < file_size; offset += sizeof(Record_Header_t) + current_record_header.body_size) {
            current_record_header.Log(this, indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}
