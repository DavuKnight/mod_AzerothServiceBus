#include <boost/serialization/base_object.hpp>
#include <ObjectGuid.h>
namespace mod_AzerothServiceBus::SerializeableModels
{
    class ObjectGuidDto
    {
        ObjectGuid _objectGuid;
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar & rawValue;
        }
        uint64 rawValue;
    public:
        ObjectGuidDto() {};
        ObjectGuidDto(ObjectGuid objectGuid)
        {
            _objectGuid = objectGuid;
            rawValue = _objectGuid.GetRawValue();
        }
    };
}
