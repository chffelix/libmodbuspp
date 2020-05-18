/* Copyright © 2018-2019 Pascal JEAN, All rights reserved.
 * This file is part of the libmodbuspp Library.
 *
 * The libmodbuspp Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * The libmodbuspp Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the libmodbuspp Library; if not, see <http://www.gnu.org/licenses/>.
 */
#ifdef _WIN32
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif

#include <modbuspp/message.h>
#include "rtutcplayer_p.h"
#include "config.h"

#if !defined(MSG_NOSIGNAL)
#define MSG_NOSIGNAL 0
#endif

namespace Modbus {

  // ---------------------------------------------------------------------------
  //
  //                         RtuTcpLayer Class
  //
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  RtuTcpLayer::RtuTcpLayer (RtuTcpLayer::Private &dd) : NetLayer (dd) {}

  // ---------------------------------------------------------------------------
  RtuTcpLayer::RtuTcpLayer (const std::string & host, const std::string & service) :
    NetLayer (*new Private (host, service)) {}

  // ---------------------------------------------------------------------------
  const std::string & RtuTcpLayer::node() const {

    return connection();
  }

  // ---------------------------------------------------------------------------
  const std::string & RtuTcpLayer::service() const {

    return settings();
  }

  // ---------------------------------------------------------------------------
  int RtuTcpLayer::sendRawMessage (const Message * msg) {
    PIMP_D (RtuTcpLayer);

    //TODO: Implement based on inheritance from 'TcpLayer'? (Should use a TCP socket)
    throw std::domain_error ("Method 'sendRawMessage' not yet implemented for 'RtuTcp' backend!");
  }

  // ---------------------------------------------------------------------------
  bool RtuTcpLayer::prepareToSend (Message & msg) {

    //TODO: Implement based on inheritance from 'RtuLayer'? (Datagram is the same as RTU, with CRC)
    throw std::domain_error ("Method 'prepareToSend' not yet implemented for 'RtuTcp' backend!");
  }

  // ---------------------------------------------------------------------------
  //
  //                         RtuTcpLayer::Private Class
  //
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  RtuTcpLayer::Private::Private (const std::string & host, const std::string & service) :
    NetLayer::Private (RtuTcp, host, service, MODBUS_TCP_MAX_ADU_LENGTH) {
    const char * node = NULL;

    if (host != "*") {
      node = host.c_str();
    }

    ctx = modbus_new_rtutcp_pi (node, service.c_str());
    if (! ctx) {

      throw std::invalid_argument (
        "Error: Unable to create RTU-TCP Modbus Backend(" +
        host + ":" + service + ")\n" + lastError());
    }
  }

}

/* ========================================================================== */
