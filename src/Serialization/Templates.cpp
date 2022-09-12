/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "BattlegroundQueue.h"
#include "Config.h"
#include "Chat.h"
#include "Channel.h"
#include "Guild.h"
#include "Vehicle.h"
#include "InstanceScript.h"
#include "MapInstanced.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>
#include <sstream>

#if _AIX
#include <unistd.h>
#endif
#include <boost/json.hpp>
#include <rdkafkacpp.h>
#include <boost/json/value_from.hpp>
#include <boost/json/value.hpp> // prevent intellisense bugs




void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AchievementCriteriaEntry* const& t)
{

    jv = {
        {"id", t->ID}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AchievementEntry const* t)
{

    jv = {
        {"id", t->ID}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AreaTrigger const* t)
{

    jv = {
        {"entry", t->entry}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    ArenaTeam* t)
{

    jv = {
        {"id", t->GetId()}
    };
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuctionEntry* t)
{
    jv = {
        {"id", t->Id}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuctionHouseObject* t)
{

    jv = {};
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuctionHouseMgr* t)
{
    jv = {
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuraApplication const* t)
{
    jv = {};
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuraEffect const* t)
{
    jv = { };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuraRemoveMode t)
{

    jv = static_cast<int>(t);
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Battleground* t)
{

    jv = {
        {"InstanceId", t->GetInstanceID()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    BattlegroundBracketId t)
{

    jv = static_cast<int>(t);
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    const BattlegroundDesertionType t)
{

    jv =  static_cast<int>(t);
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    BattlegroundQueue* t)
{

    jv = {

    };
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    BattlegroundTypeId t)
{
    jv = static_cast<int>(t);
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Channel* t)
{

    jv = {
        {"channelId", t->GetChannelId()}
    };
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Creature* const t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
    };
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    CreatureTemplate const* t)
{

    jv = {
        {"Guid", t->Entry}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    GridMap* t)
{

    jv = { };
}
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Group* t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    GroupQueueInfo* t)
{

    jv = {
        {"teamId", t->teamId}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Guardian* const t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Guild* t)
{

    jv = {
        {"Guid", t->GetId()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Item* t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
    };
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    InstanceSave* t)
{
    jv = {
        {"id", t->GetInstanceId()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    InstanceScript* t)
{
    jv = {
        {"id", t->instance->GetInstanceId()}
    };

}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    ItemTemplate const* t)
{

    jv = {
        {"id", t->ItemId}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Loot* t)
{

    jv = {
        {"id", t->containerGUID}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Map* t)
{

    jv = {
        {"id", t->GetId()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    MapInstanced* t)
{
    jv = {
        {"id",t->GetInstanceId()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    MailDraft* t)
{
    jv = {
        {"subject",t->GetSubject()},
        {"body",t->GetBody()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    MailReceiver const t)
{
    jv = {
        //todo
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    MailSender const t)
{
    jv = {
        //todo
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Object* t)
{

    jv = {
        {"entry", t->GetEntry()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    ObjectGuid const t)
{

    jv = {
        {"Guid", t.GetRawValue()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Pet const* t)
{
    jv = {
        //{"Guid", t->GetGUID().GetRawValue()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Player const* t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    PvPDifficultyEntry const* t)
{

    jv = {
        {"bracketId", t->bracketId},
        {"difficulty", t->difficulty},
        {"mapId", t->mapId},
        {"maxLevel", t->maxLevel},
        {"minLevel", t->minLevel}
    };
}


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Quest const* t)
{

    jv = {
        {"Quest", t->GetQuestId()}
    };
}
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    RemoveMethod t)
{
    jv = static_cast<int>(t);

}
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    ScalingStatValuesEntry const& t)
{

    jv = {
        {"Guid", t.Id}
    };
}
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    TeamId t)
{
    jv = static_cast<int>(t);
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Unit* const t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    TempSummon* const t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Vehicle* t)
{

    jv = {
        {"item", t->GetCreatureEntry()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    VendorItem const t)
{

    jv = {
        {"item", t.item}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Weather* t)
{

    jv = {
        {"scriptId", t->GetScriptId()},
        {"zone", t->GetZone()}
    };
}

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    WeatherState t)
{

    jv = static_cast<int>(t);
};

