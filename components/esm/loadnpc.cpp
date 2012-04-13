#include "loadnpc.hpp"

namespace ESM
{

void NPC::load(ESMReader &esm)
{
    npdt52.gold = -10;

    model = esm.getHNOString("MODL");
    name = esm.getHNOString("FNAM");

    race = esm.getHNString("RNAM");
    cls = esm.getHNString("CNAM");
    faction = esm.getHNString("ANAM");
    head = esm.getHNString("BNAM");
    hair = esm.getHNString("KNAM");

    script = esm.getHNOString("SCRI");

    esm.getSubNameIs("NPDT");
    esm.getSubHeader();
    if (esm.getSubSize() == 52)
    {
        npdtType = 52;
        esm.getExact(&npdt52, 52);
    }
    else if (esm.getSubSize() == 12)
    {
        npdtType = 12;
        esm.getExact(&npdt12, 12);
    }
    else
        esm.fail("NPC_NPDT must be 12 or 52 bytes long");

    esm.getHNT(flags, "FLAG");

    inventory.load(esm);
    spells.load(esm);
    aiData.load(esm);

    esm.skipRecord();
}
void NPC::save(ESMWriter &esm)
{
    esm.writeHNOCString("MODL", model);
    esm.writeHNOCString("FNAM", name);
    esm.writeHNCString("RNAM", race);
    esm.writeHNCString("CNAM", cls);
    esm.writeHNCString("ANAM", faction);
    esm.writeHNCString("BNAM", head);
    esm.writeHNCString("KNAM", hair);
    esm.writeHNOCString("SCRI", script);
    
    if (npdtType == 52)
        esm.writeHNT("NPDT", npdt52, 52);
    else if (npdtType == 12)
        esm.writeHNT("NPDT", npdt12, 12);

    esm.writeHNT("FLAG", flags);
    
    inventory.save(esm);
    spells.save(esm);
    aiData.save(esm);
}

}
