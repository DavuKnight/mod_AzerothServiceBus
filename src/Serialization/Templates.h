/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
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

//

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AchievementCriteriaEntry const t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AchievementEntry const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AreaTrigger const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuraApplication const* t);

//AuraRemoveMode
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuraRemoveMode t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuraEffect const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    AuraEffect const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    const BattlegroundDesertionType t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Battleground* t)
    ;

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Channel* t)
    ;

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Creature* const t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    CreatureTemplate* const t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    GridMap* t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Group* t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Guardian const t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Guild* t);
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    InstanceSave* t);
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Item* t);
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    ItemTemplate const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Loot* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    LootStore const t);

//MailDraft
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    MailDraft* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Map* t);


void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Object* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    ObjectGuid const t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Pet const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Player const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Quest const* t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    RemoveMethod  t);

void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    ScalingStatValuesEntry const t);
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Unit* const t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    TempSummon* const t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Vehicle const* t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    VendorItem const t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    Weather* t)
    ;
void
tag_invoke(
    const boost::json::value_from_tag&,
    boost::json::value& jv,
    WeatherState t)
    ;
