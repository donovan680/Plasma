///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once


namespace Plasma
{

// This is a central place for all our online locations.
// The term 'User' means that the link goes to a user facing site. Ends with a '/' for concatenating reasons.
// The term 'Api' means that it goes to an online script and is typically parsed. Does NOT end with a '/'.
namespace Urls
{
extern const cstr cUserPlasmaHub;
extern const cstr cUserDoc;
extern const cstr cUserLightning;
extern const cstr cUserRoadmap;
extern const cstr cUserCompany;
extern const cstr cUserQa;
extern const cstr cUserMarket;
extern const cstr cApiReportIssue;
extern const cstr cUserReportIssue;
extern const cstr cUserLatestIssues;
extern const cstr cUserSpecificIssue;
extern const cstr cUserChat;
extern const cstr cUserLauncherDownloads;
extern const cstr cUserOnlineDocs;
extern const cstr cUserHelp;
extern const cstr cUserWebBrowserDefault;
extern const cstr cUserWebRequesterDefault;
extern const cstr cApiPlasmaBuilds;
extern const cstr cApiLauncherTemplates;
extern const cstr cApiLauncherBuilds;
extern const cstr cUserDevNotes;
extern const cstr cApiDevNotes;
}

}//namespace Plasma
