///////////////////////////////////////////////////////////////////////////////
///
/// \file SimpleSocket.hpp
/// Declaration of the SimpleSocket class.
///
/// Authors: Joshua Claeys.
/// Copyright 2012, DigiPen Institute of Technology.
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class TcpSocket;

class SimpleSocket : public Component
{
public:
  LightningDeclareType(SimpleSocket, TypeCopyMode::ReferenceType);

  /// Constructor.
  SimpleSocket();

  /// Returns the socket.
  TcpSocket* GetSocket();

private:

  /// Socket.
  TcpSocket mSocket;
};

}//namespace Plasma
