#ifndef OPENMW_ESM_CLAS_H
#define OPENMW_ESM_CLAS_H

#include <string>
#include <boost/array.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/utility/identity_type.hpp>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * Character class definitions
 */

// These flags tells us which items should be auto-calculated for this
// class
struct Class
{
    enum AutoCalc
    {
        Weapon = 0x00001,
        Armor = 0x00002,
        Clothing = 0x00004,
        Books = 0x00008,
        Ingredient = 0x00010,
        Lockpick = 0x00020,
        Probe = 0x00040,
        Lights = 0x00080,
        Apparatus = 0x00100,
        Repair = 0x00200,
        Misc = 0x00400,
        Spells = 0x00800,
        MagicItems = 0x01000,
        Potions = 0x02000,
        Training = 0x04000,
        Spellmaking = 0x08000,
        Enchanting = 0x10000,
        RepairItem = 0x20000
    };

    enum Specialization
    {
        Combat = 0,
        Magic = 1,
        Stealth = 2
    };

    static const Specialization sSpecializationIds[3];
    static const char *sGmstSpecializationIds[3];

    struct CLDTstruct
    {
        boost::array<int,2> mAttribute; // Attributes that get class bonus
        int mSpecialization; // 0 = Combat, 1 = Magic, 2 = Stealth
        boost::array<int,10> mSkills; // Minor (0-4) and major (5-9) skills.
        int mIsPlayable; // 0x0001 - Playable class

        // I have no idea how to autocalculate these items...
        int mCalc;
    }; // 60 bytes

    std::string mId, mName, mDescription;
    CLDTstruct mData;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};

}

BOOST_FUSION_ADAPT_STRUCT(
    ESM::Class::CLDTstruct,
    (BOOST_IDENTITY_TYPE((boost::array<int,2>)), mAttribute)
    (int, mSpecialization)
    (BOOST_IDENTITY_TYPE((boost::array<int,10>)), mSkills)
    (int, mIsPlayable)
    (int, mCalc))

#endif
