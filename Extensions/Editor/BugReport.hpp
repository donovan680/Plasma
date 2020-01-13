///////////////////////////////////////////////////////////////////////////////
/// Authors: Trevor Sundberg
/// Copyright 2010-2011, DigiPen Institute of Technology
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{
class Editor;
class TextEditor;
class WebResponseEvent;
class UpdateEvent;
class TextButton;

namespace Events
{
  DeclareEvent(BugReporterResponse);
}//namespace Events

/// Event carrying the AsyncWebRequest back to the main thread
/// so we can run it and listen for the completed response.
class BugReporterResponse : public Event
{
public:
  LightningDeclareType(BugReporterResponse, TypeCopyMode::ReferenceType);
  HandleOf<AsyncWebRequest> mRequest;
};

class BugReporter : public Composite
{
public:
  LightningDeclareType(BugReporter, TypeCopyMode::ReferenceType);

  BugReporter(Composite* parent);
  ~BugReporter();

  void Reset();

  // Internal
  void OnSend(Event* event);
  void OnBrowse(Event* event);
  void OnBrowseSelected(OsFileSelection* event);
  void OnUpdate(UpdateEvent* event);
  
  TextBox* mUsername;
  TextBox* mTitle;
  TextEditor* mDescription;
  TextEditor* mRepro;
  TextButton* mSend;
  SelectorButton* mSelectorButton;
  
  TextBox* mIncludeFile;
  TextButton* mBrowse;
  TextCheckBox* mIncludeClipboardImage;
  TextCheckBox* mIncludeScreenshot;
  TextCheckBox* mIncludeProject;
  bool mSent;
};


class BugReportJob : public Job
{
public:
  typedef BugReportJob LightningSelf;
  void Execute();
  void OnWebResponseComplete(WebResponseEvent* event);

  String mFileName;
  CogId mProject;
  String mUsername;
  String mReportType;
  String mTitle;
  String mDescription;
  String mRepro;
  String mIncludedFile;
  Image mScreenshot;
  Image mClipboardImage;
};


}//namespace Plasma
