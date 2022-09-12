
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
#include "Serialization/Templates.h"
// Add player scripts
namespace mod_AzerothServiceBus
{
    class AuctionHouseEventProducer : public AuctionHouseScript
    {

    public:
        RdKafka::Producer* _producer;

        AuctionHouseEventProducer(RdKafka::Producer* producer) : AuctionHouseScript("AuctionHouseEventProducer") {
            _producer = producer;
        }
    // Called when an auction is added to an auction house.
    void OnAuctionAdd(AuctionHouseObject* ah, AuctionEntry* entry) override { }

    // Called when an auction is removed from an auction house.
    void OnAuctionRemove(AuctionHouseObject* ah, AuctionEntry* entry) override { }

    // Called when an auction was succesfully completed.
    void OnAuctionSuccessful(AuctionHouseObject* ah, AuctionEntry* entry) override { }

    // Called when an auction expires.
    void OnAuctionExpire(AuctionHouseObject* ah, AuctionEntry* entry) override { }

    // Called before sending the mail concerning a won auction
    void OnBeforeAuctionHouseMgrSendAuctionWonMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* bidder, uint32& bidder_accId, bool& sendNotification, bool& updateAchievementCriteria, bool& sendMail) override { }

    // Called before sending the mail concerning a pending sale
    void OnBeforeAuctionHouseMgrSendAuctionSalePendingMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* owner, uint32& owner_accId, bool& sendMail) override { }

    // Called before sending the mail concerning a successful auction
    void OnBeforeAuctionHouseMgrSendAuctionSuccessfulMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* owner, uint32& owner_accId, uint32& profit, bool& sendNotification, bool& updateAchievementCriteria, bool& sendMail) override { }

    // Called before sending the mail concerning an expired auction
    void OnBeforeAuctionHouseMgrSendAuctionExpiredMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* owner, uint32& owner_accId, bool& sendNotification, bool& sendMail) override { }

    // Called before sending the mail concerning an outbidded auction
    void OnBeforeAuctionHouseMgrSendAuctionOutbiddedMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* oldBidder, uint32& oldBidder_accId, Player* newBidder, uint32& newPrice, bool& sendNotification, bool& sendMail) override { }

    // Called before sending the mail concerning an cancelled auction
    void OnBeforeAuctionHouseMgrSendAuctionCancelledToBidderMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* bidder, uint32& bidder_accId, bool& sendMail) override { }

    // Called before updating the auctions
    void OnBeforeAuctionHouseMgrUpdate() override{ }
    };
}
