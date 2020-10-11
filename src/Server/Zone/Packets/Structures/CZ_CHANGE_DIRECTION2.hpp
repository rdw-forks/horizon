/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_CZ_CHANGE_DIRECTION2_HPP
#define HORIZON_ZONE_CZ_CHANGE_DIRECTION2_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Zone
{
class AuthSocket;
namespace Packet
{

enum {
#if PACKET_VERSION >= 20180523
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180511
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180321
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180315
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180314
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180228
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180221
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180213
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180131
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180124
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180117
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20180103
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171227
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171206
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171204
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171130
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171129
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171127
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171115
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171101
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171025
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171018
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20171002
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170927
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170830
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170823
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170816
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170809
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170801
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170719
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170712
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170705
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170628
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170621
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170614
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170607
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170531
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170329
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170322
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170315
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170308
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20170104
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20161214
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20161207
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20161130
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20161109
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20161102
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20161026
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20161019
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160928
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160921
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160913
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160907
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160831
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160824
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160817
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160810
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160629
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160622
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160504
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160427
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160323
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160316
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160309
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160211
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160203
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160127
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160120
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20160106
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151223
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151216
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151209
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151202
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151104
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151028
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151021
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151007
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20151001
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150923
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150916
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150909
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150819
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150805
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150729
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150722
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150610
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150603
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150527
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150520
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150429
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150422
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150415
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150225
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150217
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150211
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150204
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20150107
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141231
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141224
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141223
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141105
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141029
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141015
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141008
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20141001
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140903
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140827
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140813
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140806
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140611
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140514
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140508
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140423
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140416
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140312
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140226
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140212
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140205
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140129
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140122
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140115
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20140108
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131230
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131223
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131127
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131120
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131023
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131016
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131008
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20131002
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130911
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130904
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130828
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130821
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130814
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130807
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130717
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130710
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130612
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130605
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130502
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130424
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130227
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130220
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130121
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130115
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130109
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20130103
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20121227
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20121212
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20121205
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20121114
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20121107
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120925
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120919
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120822
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120814
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120724
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120716
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120626
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120612
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120604
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120601
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120529
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120523
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120522
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120508
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120503
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120502
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120424
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120417
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120214
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120207
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120131
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120120
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120117
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120110
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20120103
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111220
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111213
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111207
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111122
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111114
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111025
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111017
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111010
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20111004
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110928
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110831
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110823
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110816
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110809
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110726
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110718
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110711
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110705
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110627
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110620
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110614
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110607
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110531
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110523
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110511
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110503
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110405
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110329
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110322
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110315
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110308
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110228
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110131
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110125
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110118
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110111
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20110104
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20101228
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20101221
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20101214
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20101130
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20101123
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20100105
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090406
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090401
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090325
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090225
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090218
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090211
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090204
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090120
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090114
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20090107
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081217
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081203
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081126
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081119
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081112
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081105
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081029
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081022
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081015
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20081008
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080910
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080903
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080827
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080813
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080806
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080730
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080722
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080708
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080701
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080624
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080618
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080617
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080610
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080528
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 20080527
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#elif PACKET_VERSION >= 0
	ID_CZ_CHANGE_DIRECTION2 = 0x0361
#endif
};
/**
 * @brief Main object for the aegis packet: CZ_CHANGE_DIRECTION2
 * Size : 27 @ 20080701
 *
 */ 
class CZ_CHANGE_DIRECTION2 : public Base::NetworkPacket<ZoneSocket>
{
public:
	CZ_CHANGE_DIRECTION2(std::shared_ptr<ZoneSocket> sock);
	~CZ_CHANGE_DIRECTION2();


	void handle(ByteBuffer &buf);

private:
	void deserialize(ByteBuffer &buf) override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_ZONE_CZ_CHANGE_DIRECTION2_HPP */