///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Reese Jones.
/// Copyright 2016, DigiPen Institute of Technology.
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//---------------------------------------------------------------------------------//
//                                NetHostRecord                                    //
//---------------------------------------------------------------------------------//

LightningDefineType(NetHostRecord, builder, type)
{
  // Bind documentation
  PlasmaBindDocumented();

  // Bind member properties
  LightningBindFieldGetterProperty(mIpAddress);
  LightningBindFieldGetterProperty(mBasicHostInfo);
  LightningBindFieldGetterProperty(mLifetime);
  // LightningBindFieldGetterProperty(mProjectGuid); //This type is not yet bound. (int64 I think)
}

NetHostRecord::NetHostRecord()
  : mLifetime(0.0f),
    mIpAddress(),
    mBasicHostInfo(),
    mProjectGuid()
{
}
NetHostRecord::NetHostRecord(NetHostRecord const& ref)
  : mLifetime(ref.mLifetime),
    mIpAddress(ref.mIpAddress),
    mBasicHostInfo(ref.mBasicHostInfo),
    mProjectGuid(ref.mProjectGuid)
{
}

NetHostRecord::~NetHostRecord()
{
}

bool NetHostRecord::operator ==(const NetHostRecord& rhs) const
{
  return mIpAddress == rhs.mIpAddress;
}
bool NetHostRecord::operator !=(const NetHostRecord& rhs) const
{
  return mIpAddress != rhs.mIpAddress;
}
bool NetHostRecord::operator  <(const NetHostRecord& rhs) const
{
  return mIpAddress < rhs.mIpAddress;
}
bool NetHostRecord::operator ==(const IpAddress& rhs) const
{
  return mIpAddress == rhs;
}
bool NetHostRecord::operator !=(const IpAddress& rhs) const
{
  return mIpAddress != rhs;
}
bool NetHostRecord::operator  <(const IpAddress& rhs) const
{
  return mIpAddress < rhs;
}

} // namespace Plasma
