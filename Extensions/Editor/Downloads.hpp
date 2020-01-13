///////////////////////////////////////////////////////////////////////////////
///
/// \file Downloads.hpp
/// 
///
/// Authors: Joshua Claeys
/// Copyright 2014, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//---------------------------------------------------------------- Download Task
class DownloadTaskJob : public BackgroundTaskJob
{
public:
  static BackgroundTask* DownloadToBuffer(StringParam url);
  static BackgroundTask* DownloadToBuffer(StringParam url, StringParam fileName);

  typedef DownloadTaskJob LightningSelf;
  DownloadTaskJob(StringParam url, u64 forceCacheSeconds = 0);

  /// Job Interface.
  void Execute() override;
  int Cancel() override;

  float GetPercentageComplete();
  String GetData();

  String mName;
  String mFileName;

protected:
  void OnWebResponsePartialData(WebResponseEvent* e);
  void OnWebResponseComplete(WebResponseEvent* e);
  void UpdateDownloadProgress();

  String mDownloadedLocation;
  HandleOf<AsyncWebRequest> mRequest;
};

}//namespace Plasma
