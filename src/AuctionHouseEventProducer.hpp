
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
    void OnAuctionAdd(AuctionHouseObject* ah, AuctionEntry* entry) override
    {
        try
        {
            boost::json::value jv = {
                {"ah",boost::json::value_from(ah) },
                {"entry",boost::json::value_from(entry) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnAuctionAdd", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called when an auction is removed from an auction house.
    void OnAuctionRemove(AuctionHouseObject* ah, AuctionEntry* entry) override
    {
        try
        {
            boost::json::value jv = {
                {"ah",boost::json::value_from(ah) },
                {"entry",boost::json::value_from(entry) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnAuctionRemove", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called when an auction was succesfully completed.
    void OnAuctionSuccessful(AuctionHouseObject* ah, AuctionEntry* entry) override
    {
        try
        {
            boost::json::value jv = {
                {"ah",boost::json::value_from(ah) },
                {"entry",boost::json::value_from(entry) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnAuctionSuccessful", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called when an auction expires.
    void OnAuctionExpire(AuctionHouseObject* ah, AuctionEntry* entry) override
    {
        try
        {
            boost::json::value jv = {
                {"ah",boost::json::value_from(ah) },
                {"entry",boost::json::value_from(entry) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnAuctionExpire", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called before sending the mail concerning a won auction
    void OnBeforeAuctionHouseMgrSendAuctionWonMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* bidder, uint32& bidder_accId, bool& sendNotification, bool& updateAchievementCriteria, bool& sendMail) override
    {
        try
        {
            boost::json::value jv = {
                {"auctionHouseMgr",boost::json::value_from(auctionHouseMgr) },
                {"auction",boost::json::value_from(auction) },
                {"bidder",boost::json::value_from(bidder) },
                {"bidder_accId",boost::json::value_from(bidder_accId) },
                {"sendNotification",boost::json::value_from(sendNotification) },
                {"updateAchievementCriteria",boost::json::value_from(updateAchievementCriteria) },
                {"sendMail",boost::json::value_from(sendMail) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnBeforeAuctionHouseMgrSendAuctionWonMail", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called before sending the mail concerning a pending sale
    void OnBeforeAuctionHouseMgrSendAuctionSalePendingMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* owner, uint32& owner_accId, bool& sendMail) override
    {
        try
        {
            boost::json::value jv = {
                {"auctionHouseMgr",boost::json::value_from(auctionHouseMgr) },
                {"auction",boost::json::value_from(auction) },
                {"owner",boost::json::value_from(owner) },
                {"owner_accId",boost::json::value_from(owner_accId) },
                {"sendMail",boost::json::value_from(sendMail) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnBeforeAuctionHouseMgrSendAuctionSalePendingMail", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called before sending the mail concerning a successful auction
    void OnBeforeAuctionHouseMgrSendAuctionSuccessfulMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* owner, uint32& owner_accId, uint32& profit, bool& sendNotification, bool& updateAchievementCriteria, bool& sendMail) override
    {
        try
        {
            boost::json::value jv = {
                {"auctionHouseMgr",boost::json::value_from(auctionHouseMgr) },
                {"auction",boost::json::value_from(auction) },
                {"owner",boost::json::value_from(owner) },
                {"owner_accId",boost::json::value_from(owner_accId) },
                {"profit",boost::json::value_from(profit) },
                {"sendNotification",boost::json::value_from(sendNotification) },
                {"sendMail",boost::json::value_from(sendMail) },
                {"updateAchievementCriteria",boost::json::value_from(updateAchievementCriteria) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnBeforeAuctionHouseMgrSendAuctionSuccessfulMail", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called before sending the mail concerning an expired auction
    void OnBeforeAuctionHouseMgrSendAuctionExpiredMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* owner, uint32& owner_accId, bool& sendNotification, bool& sendMail) override
    {
        try
        {
            boost::json::value jv = {
                {"auctionHouseMgr",boost::json::value_from(auctionHouseMgr) },
                {"auction",boost::json::value_from(auction) },
                {"owner",boost::json::value_from(owner) },
                {"owner_accId",boost::json::value_from(owner_accId) },
                {"sendNotification",boost::json::value_from(sendNotification) },
                {"sendMail",boost::json::value_from(sendMail) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnBeforeAuctionHouseMgrSendAuctionExpiredMail", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }

    // Called before sending the mail concerning an outbidded auction
    void OnBeforeAuctionHouseMgrSendAuctionOutbiddedMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* oldBidder, uint32& oldBidder_accId, Player* newBidder, uint32& newPrice, bool& sendNotification, bool& sendMail) override
    {
        try
        {
            boost::json::value jv = {
                {"auctionHouseMgr",boost::json::value_from(auctionHouseMgr) },
                {"auction",boost::json::value_from(auction) },
                {"oldBidder",boost::json::value_from(oldBidder) },
                {"oldBidder_accId",boost::json::value_from(oldBidder_accId) },
                {"newBidder",boost::json::value_from(newBidder) },
                {"newPrice",boost::json::value_from(newPrice) },
                {"sendNotification",boost::json::value_from(sendNotification) },
                {"sendMail",boost::json::value_from(sendMail) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnBeforeAuctionHouseMgrSendAuctionOutbiddedMail", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called before sending the mail concerning an cancelled auction
    void OnBeforeAuctionHouseMgrSendAuctionCancelledToBidderMail(AuctionHouseMgr* auctionHouseMgr, AuctionEntry* auction, Player* bidder, uint32& bidder_accId, bool& sendMail) override
    {
        try
        {
            boost::json::value jv = {
                {"auctionHouseMgr",boost::json::value_from(auctionHouseMgr) },
                {"auction",boost::json::value_from(auction) },
                {"bidder",boost::json::value_from(bidder) },
                {"bidder_accId",boost::json::value_from(bidder_accId) },
                {"sendMail",boost::json::value_from(sendMail) }
            };
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnBeforeAuctionHouseMgrSendAuctionCancelledToBidderMail", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }


    // Called before updating the auctions
    void OnBeforeAuctionHouseMgrUpdate() override
    {
        try
        {
            boost::json::value jv = {};
            std::string body = serialize(jv);

            RdKafka::ErrorCode resp = _producer->produce("AuctionHouseScript.OnBeforeAuctionHouseMgrUpdate", RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(body.c_str()), body.size(), NULL, 0, 0, NULL, NULL);
            if (resp != RdKafka::ERR_NO_ERROR) {
                std::cerr << "% Produce failed: " <<
                    RdKafka::err2str(resp) << std::endl;
            }
            _producer->poll(0);
        }
        catch (...)
        {
        }
    }

    };
}
