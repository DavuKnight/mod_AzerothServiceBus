#include <boost/serialization/base_object.hpp>
namespace mod_AzerothServiceBus::SerializeableModels
{
    class DifficultyDto
    {
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {

        }
    };
}