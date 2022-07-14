/*
 *  TOPPERS/A-COMSTACK
 *      Automotive COMSTACK
 *
 *  Copyright (C) 2013-2017 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2014-2016 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2015-2016 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2013-2017 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2014-2017 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2016 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2014-2017 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2016 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2015-2017 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2013-2017 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2017 by Witz Corporation
 *
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
 *  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
 *  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
 *  用する者に対して，AUTOSARパートナーになることを求めている．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *  $Id: Rte_Cbk.c 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

#include "t_syslog.h"

void Rte_COMCbkTxAck_snA()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxAck_snA ==");
	return;
}
void Rte_COMCbkTxErr_snA()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxErr_snA ==");
	return;
}
void Rte_COMCbkTxTOut_snA()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkTxTOut_snA ==");
	return;
}

void Rte_COMCbkTxAck_sgA()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxAck_sgA ==");
	return;
}
void Rte_COMCbkTxErr_sgA()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxErr_sgA ==");
	return;
}
void Rte_COMCbkTxTOut_sgA()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkTxTOut_sgA ==");
	return;
}

void Rte_COMCbkRxAck_snD()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkRxAck_snD ==");
	return;
}
void Rte_COMCbkRxTOut_snD()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkRxTOut_snD ==");
	return;
}
void Rte_COMCbkInv_snD()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkInv_snD ==");
	return;
}

void Rte_COMCbkRxAck_sgB()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkRxAck_sgB ==");
	return;
}
void Rte_COMCbkRxTOut_sgB()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkRxTOut_sgB ==");
	return;
}
void Rte_COMCbkInv_sgB()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkInv_sgB ==");
	return;
}

void Rte_COMCbkTxAck_snG()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxAck_snG ==");
	return;
}
void Rte_COMCbkTxErr_snG()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxErr_snG ==");
	return;
}
void Rte_COMCbkTxTOut_snG()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkTxTOut_snG ==");
	return;
}

void Rte_COMCbkTxAck_sgC()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxAck_sgC ==");
	return;
}
void Rte_COMCbkTxErr_sgC()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxErr_sgC ==");
	return;
}
void Rte_COMCbkTxTOut_sgC()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkTxTOut_sgC ==");
	return;
}

void Rte_COMCbkRxAck_snJ()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkRxAck_snJ ==");
	return;
}
void Rte_COMCbkRxTOut_snJ()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkRxTOut_snJ ==");
	return;
}
void Rte_COMCbkInv_snJ()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkInv_snJ ==");
	return;
}

void Rte_COMCbkRxAck_sgD()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkRxAck_sgD ==");
	return;
}
void Rte_COMCbkRxTOut_sgD()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkRxTOut_sgD ==");
	return;
}
void Rte_COMCbkInv_sgD()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkInv_sgD ==");
	return;
}

void Rte_COMCbkTxAck_snM()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxAck_snM ==");
	return;
}
void Rte_COMCbkTxErr_snM()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxErr_snM ==");
	return;
}
void Rte_COMCbkTxTOut_snM()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkTxTOut_snM ==");
	return;
}

void Rte_COMCbkTxAck_sgE()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxAck_sgE ==");
	return;
}
void Rte_COMCbkTxErr_sgE()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkTxErr_sgE ==");
	return;
}
void Rte_COMCbkTxTOut_sgE()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkTxTOut_sgE ==");
	return;
}

void Rte_COMCbkRxAck_snP()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkRxAck_snP ==");
	return;
}
void Rte_COMCbkRxTOut_snP()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkRxTOut_snP ==");
	return;
}
void Rte_COMCbkInv_snP()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkInv_snP ==");
	return;
}

void Rte_COMCbkRxAck_sgF()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkRxAck_sgF ==");
	return;
}
void Rte_COMCbkRxTOut_sgF()
{
//	syslog(LOG_NOTICE, "== Rte_COMCbkRxTOut_sgF ==");
	return;
}
void Rte_COMCbkInv_sgF()
{
	syslog(LOG_NOTICE, "== Rte_COMCbkInv_sgF ==");
	return;
}

