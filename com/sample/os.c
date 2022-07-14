/*
 *  TOPPERS/A-COM
 *      Automotive COM
 *
 *  Copyright (C) 2013-2016 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2014-2016 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2015-2016 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2013-2016 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2014-2016 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2016 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2014-2016 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2016 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2015-2016 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2013-2016 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2016 by Witz Corporation
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
 *  $Id: os.c 3128 2016-03-15 05:16:52Z fsi-kaitori $
 */

#include "Os.h"
#include "Com.h"
#include "t_syslog.h"

static const uint8			pdur_data[3] = {
	(uint8) 001U,   /*data0*/
	(uint8) 127U,   /*data1*/
	(uint8) 254U    /*data2*/
};

static const PduInfoType	pdu_info_type_table = {
	(uint8 *) pdur_data,
	(PduLengthType) 3U
};


TASK(MainTask)
{
	Com_IpduGroupVector vector_on;
	Com_StatusType		st;
	Std_VersionInfoType vi;
	Std_VersionInfoType *versioninfo = &vi;
	uint32				id;
	uint8				data0 = 123;
	uint8				data1 = 146;
	uint8				data2 = 245;
	uint8				data3;
	uint8				data4;
	uint8				data5;

	syslog(LOG_NOTICE, "== Com_Init ==");
	Com_Init(&com_config[0]);

	syslog(LOG_NOTICE, "== Com_GetStatus ==");
	st = Com_GetStatus();
	syslog(LOG_NOTICE, "** Status = %d **", st);

	syslog(LOG_NOTICE, "== Com_GetConfigurationId ==");
	id = Com_GetConfigurationId();
	syslog(LOG_NOTICE, "** id = %d **", id);

	syslog(LOG_NOTICE, "== Com_GetVersionInfo ==");
	Com_GetVersionInfo(versioninfo);
	syslog(LOG_NOTICE, "** versioninfo->vendorID = %d **", versioninfo->vendorID);
	syslog(LOG_NOTICE, "** versioninfo->moduleID = %d **", versioninfo->moduleID);
	syslog(LOG_NOTICE, "** versioninfo->sw_major_version = %d **", versioninfo->sw_major_version);
	syslog(LOG_NOTICE, "** versioninfo->sw_minor_version = %d **", versioninfo->sw_minor_version);
	syslog(LOG_NOTICE, "** versioninfo->sw_patch_version = %d **", versioninfo->sw_patch_version);

	syslog(LOG_NOTICE, "== Com_ClearIpduGroupVector(0) ==");
	Com_ClearIpduGroupVector(vector_on);

	syslog(LOG_NOTICE, "== Com_SetIpduGroup(0) ==");
	Com_SetIpduGroup(vector_on, 0, TRUE);

	syslog(LOG_NOTICE, "== Com_IpduGroupControl ==");
	Com_IpduGroupControl(vector_on, TRUE);

	//送信確認
	syslog(LOG_NOTICE, "== Com_SendSignal(0) ==");
	(void) Com_SendSignal(0U, &data0);

	syslog(LOG_NOTICE, "== Com_SendSignal(1) ==");
	(void) Com_SendSignal(1U, &data1);

	syslog(LOG_NOTICE, "== Com_SendSignal(2) ==");
	(void) Com_SendSignal(2U, &data2);

	syslog(LOG_NOTICE, "== Com_SwitchIpduTxMode(0) ==");
	Com_SwitchIpduTxMode(0U, FALSE);

	syslog(LOG_NOTICE, "== Com_SendSignalGroup(0) ==");
	(void) Com_SendSignalGroup(0U);

	syslog(LOG_NOTICE, "== Com_TriggerIPDUSend(0) ==");
	Com_TriggerIPDUSend(0U);

	syslog(LOG_NOTICE, "== Com_MainFunctionTx ==");
	Com_MainFunctionTx();

	syslog(LOG_NOTICE, "== Com_InvalidateSignal(0) ==");
	(void) Com_InvalidateSignal(0U);

	syslog(LOG_NOTICE, "== Com_InvalidateSignalGroup(0) ==");
	(void) Com_InvalidateSignalGroup(0U);

	syslog(LOG_NOTICE, "== Com_MainFunctionTx ==");
	Com_MainFunctionTx();

	syslog(LOG_NOTICE, "== Com_TxConfirmation ==");
	Com_TxConfirmation(0U);

	//受信確認
	syslog(LOG_NOTICE, "== Com_RxIndication ==");
	Com_RxIndication(1, (PduInfoType *) &pdu_info_type_table);

	syslog(LOG_NOTICE, "== Com_MainFunctionRx ==");
	Com_MainFunctionRx();

	syslog(LOG_NOTICE, "== Com_ReceiveSignalGroup(1) ==");
	(void) Com_ReceiveSignalGroup(1U);

	syslog(LOG_NOTICE, "== Com_ReceiveSignal(3) ==");
	(void) Com_ReceiveSignal(3U, &data3);

	syslog(LOG_NOTICE, "** data3 = %d **", data3);

	syslog(LOG_NOTICE, "== Com_ReceiveSignal(4) ==");
	(void) Com_ReceiveSignal(4U, &data4);

	syslog(LOG_NOTICE, "** data4 = %d **", data4);

	syslog(LOG_NOTICE, "== Com_ReceiveSignal(5) ==");
	(void) Com_ReceiveSignal(5U, &data5);

	syslog(LOG_NOTICE, "** data5 = %d **", data5);

	syslog(LOG_NOTICE, "== Com_DeInit ==");
	Com_DeInit();

	ShutdownOS(E_OK);
}

ProtectionReturnType
ProtectionHook(StatusType FatalError)
{
	syslog(LOG_NOTICE, "## ProtectionHook is called !! (%d)", FatalError);

	return(PRO_SHUTDOWN);
}

sint32
main(void)
{
	StartOS(MainApp);
	while (1) ;
	return(0);
}
