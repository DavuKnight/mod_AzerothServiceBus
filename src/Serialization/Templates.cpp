/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "Channel.h"
#include "Guild.h"
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
    const BattlegroundDesertionType t)
{

    jv =  static_cast<int>(t);
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
    CreatureTemplate* const t)
{

    jv = {
        {"Guid", t->Entry}
    };
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
    ItemTemplate const t)
{

    jv = {
        {"Guid", t.ItemId}
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
    Player* const t)
{

    jv = {
        {"Guid", t->GetGUID().GetRawValue()}
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
    VendorItem const t)
{

    jv = {
        {"item", t.item}
    };
}
