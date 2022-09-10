#include <boost/serialization/base_object.hpp>
#include <ObjectGuidDto.h>


namespace mod_AzerothServiceBus::SerializeableModels
{
    class PlayerDto
    {
        ::Player* _player;
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar & name;
            ar & id;
        }
        std::string name;
        ObjectGuidDto id;
    public:
        PlayerDto() {};
        PlayerDto(::Player* player)
        {
            _player = player;
            name = player->GetPlayerName();
            id = ObjectGuidDto(player->GetGUID());
        }

    };
}
