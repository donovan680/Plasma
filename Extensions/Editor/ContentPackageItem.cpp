///////////////////////////////////////////////////////////////////////////////
///
/// \file ContentPackage.cpp
/// 
///
/// Authors: Joshua Claeys
/// Copyright 2014, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace Events
{
  DefineEvent(TextureLoaded);
}

//------------------------------------------------------------- Content Package
//******************************************************************************
LightningDefineType(ContentPackage, builder, type)
{
  type->HandleManager = LightningManagerId(PointerManager);
  LightningBindFieldProperty(mName);
  LightningBindFieldProperty(mAuthor);
  LightningBindFieldProperty(mTags);
  LightningBindFieldProperty(mDescription);
}

//******************************************************************************
ContentPackage::ContentPackage()
{
  mSize = 0;
  mVersionBuilt = 0;
  mLocal = true;
  mPreview = nullptr;
  mRequest = AsyncWebRequest::Create();
}

//******************************************************************************
ContentPackage::~ContentPackage()
{
  mRequest->Cancel();
}

//******************************************************************************
void ContentPackage::operator=(const ContentPackage& rhs)
{
  mName = rhs.mName;
  mAuthor = rhs.mAuthor;
  mDate = rhs.mDate;
  mDescription = rhs.mDescription;
  mTags = rhs.mTags;
  mSize = rhs.mSize;
  mVersionBuilt = rhs.mVersionBuilt;
}

//******************************************************************************
void ContentPackage::Serialize(Serializer& stream)
{
  SerializeNameDefault(mName, String());
  SerializeNameDefault(mAuthor, String());
  SerializeNameDefault(mDate, String());
  SerializeNameDefault(mDescription, String());
  SerializeNameDefault(mTags, String());
  SerializeNameDefault(mSize, (u64)0);
  SerializeNameDefault(mVersionBuilt, (uint)9147);
}

//******************************************************************************
void ContentPackage::LoadStreamedTexture(StringParam url)
{
  // Start the web request
  AsyncWebRequest* request = mRequest;
  ConnectThisTo(request, Events::WebResponseComplete, OnWebResponse);
  request->mUrl = url;
  request->Run();
}

//******************************************************************************
void ContentPackage::LoadLocalTexture(StringParam location)
{
  Image image;
  Status status;
  LoadImage(status, location, &image);

  if(status.Failed())
    return;

  mPreview = Texture::CreateRuntime();
  mPreview->Upload(image);
}

//******************************************************************************
void ContentPackage::OnWebResponse(WebResponseEvent* e)
{
  if(e->mResponseCode != WebResponseCode::OK)
    return;

  String location = FilePath::Combine(GetTemporaryDirectory(), "StreamedImage.png");
  WriteStringRangeToFile(location, e->mData);

  LoadLocalTexture(location);

  Event eventToSend;
  GetDispatcher()->Dispatch(Events::TextureLoaded, &eventToSend);
}

}//namespace Plasma
