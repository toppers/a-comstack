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
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
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
 *  $Id: os.c 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

#include "Os.h"
#include "Can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "Com.h"
#include "Dcm.h"
#include "PduR_Dcm.h"
#include "t_syslog.h"
#include "prc_sil.h"


#define SW_BASE		0x08000410
#define KEY_BASE	0x08000400
#define KEY_0		0x01
#define KEY_1		0x02
#define KEY_2		0x04
#define KEY_3		0x08

enum {
	SND_IDLE = 0,
	SND_COM_CAN,
	SND_COM_CANFD,
	SND_DCM_CAN_SINGLE,
	SND_DCM_CAN_MULTI,
	SND_DCM_CANFD_SINGLE,
	SND_DCM_CANFD_MULTI,
	SND_DCM_CAN_SINGLE_EX,
	SND_DCM_CAN_MULTI_EX,
	SND_DCM_CAN_SINGLE_EX2,
	SND_DCM_CAN_MULTI_EX2,
	SND_DCM_CAN_CANCEL,
	SND_DCM_CANFD_CANCEL,
	SND_NUM
};

enum {
	RCV_IDLE = 0,
	RCV_COM_CAN,
	RCV_COM_CANFD,
	RCV_DCM_CAN_CANCEL,
	RCV_DCM_CANFD_CANCEL,
	RCV_NUM
};

TASK(MainTask)
{
	volatile uint32 i;
	Std_ReturnType ercd;
	Com_IpduGroupVector vector_on;
	uint8 data[64];
	uint8 snd_mod = 0;
	uint8 rcv_mod = 0;
	uint8 req = 0;
	PduInfoType Info;
	PduIdType id;
	PduLengthType len;
	uint32			cur_key;
	uint8			sw_state[8] = {0U};
	static uint32	pre_key = 0xFFFF;
	uint8 end_req = 0;
	
	/* 初期化 */
	syslog(LOG_NOTICE, "== Can_Init ==");
	Can_Init(NULL_PTR);
	
	syslog(LOG_NOTICE, "== CanIf_Init ==");
	CanIf_Init(NULL_PTR);
	syslog(LOG_NOTICE, "== CanIf_SetControllerMode START ==");
	ercd = CanIf_SetControllerMode(0U, CANIF_CS_STARTED);
	if (ercd != E_OK) {
		syslog(LOG_NOTICE, "## CanIf_SetControllerMode returns E_NOT_OK !!");
	}
	syslog(LOG_NOTICE, "== CanIf_SetControllerMode ONLINE ==");
	ercd = CanIf_SetPduMode(0U, CANIF_SET_ONLINE);
	if (ercd != E_OK) {
		syslog(LOG_NOTICE, "## CanIf_SetPduMode returns E_NOT_OK !!");
	}
	
	syslog(LOG_NOTICE, "== CanTp_Init ==");
	CanTp_Init(NULL_PTR);
	
	syslog(LOG_NOTICE, "== Com_Init ==");
	Com_Init(NULL_PTR);
	
	syslog(LOG_NOTICE, "== Com_ClearIpduGroupVector(0) ==");
	Com_ClearIpduGroupVector(vector_on);

	syslog(LOG_NOTICE, "== Com_SetIpduGroup(0) ==");
	Com_SetIpduGroup(vector_on, 0, TRUE);

	syslog(LOG_NOTICE, "== Com_IpduGroupControl ==");
	Com_IpduGroupControl(vector_on, TRUE);

	syslog(LOG_NOTICE, "== Dcm_Init ==");
	Dcm_Init(NULL_PTR);
	
	while(end_req == 0)
	{
		cur_key = sil_rew_iop((void *) KEY_BASE);

		*((uint32 *) sw_state) = sil_rew_iop((void *) SW_BASE);

		/* ボタン押下状態に遷移した場合のみ処理を行う */
		if (((pre_key & KEY_0) != 0) && ((cur_key & KEY_0) == 0)) {
			req = 1;
		}
		else if (((pre_key & KEY_1) != 0) && ((cur_key & KEY_1) == 0)) {
			/* ボタン押下で送信モード切替 */
			snd_mod++;
			if(snd_mod >= SND_NUM) {
				snd_mod = SND_IDLE;
			}
			syslog(LOG_NOTICE, "** snd_mod = %d **", snd_mod);
		}
		else if (((pre_key & KEY_2) != 0) && ((cur_key & KEY_2) == 0)) {
			/* ボタン押下で受信モード切替 */
			rcv_mod++;
			if(rcv_mod >= RCV_NUM) {
				rcv_mod = RCV_IDLE;
			}
			syslog(LOG_NOTICE, "** rcv_mod = %d **", rcv_mod);
		}
		else if (((pre_key & KEY_3) != 0) && ((cur_key & KEY_3) == 0)) {
			end_req = 1;
		}
		
		pre_key = cur_key;
		
		if(req == 1)
		{
			switch(snd_mod)
			{
			case SND_IDLE:
				/* 何もしない */
				break;
				
			case SND_COM_CAN:
				/* Com送信確認(CAN) */
				syslog(LOG_NOTICE, "== Com_SendSignal(0) ==");
				data[0] = 123;
				(void) Com_SendSignal(0U, &data[0]);
				
				data[1] = 146;
				syslog(LOG_NOTICE, "== Com_SendSignal(1) ==");
				(void) Com_SendSignal(1U, &data[1]);
				
				data[2] = 253;
				syslog(LOG_NOTICE, "== Com_SendSignal(2) ==");
				(void) Com_SendSignal(2U, &data[2]);
				
				syslog(LOG_NOTICE, "== Com_SwitchIpduTxMode(0) ==");
				Com_SwitchIpduTxMode(0U, FALSE);
				
				syslog(LOG_NOTICE, "== Com_SendSignalGroup(0) ==");
				(void) Com_SendSignalGroup(0U);
				
				syslog(LOG_NOTICE, "== Com_TriggerIPDUSend(0) ==");
				Com_TriggerIPDUSend(0U);
				break;
				
			case SND_COM_CANFD:
				/* Com送信確認(CANFD) */
				syslog(LOG_NOTICE, "== Com_SendSignal(12) ==");
				data[0] = 123;
				(void) Com_SendSignal(12U, &data[0]);
				
				data[1] = 146;
				syslog(LOG_NOTICE, "== Com_SendSignal(13) ==");
				(void) Com_SendSignal(13U, &data[1]);
				
				data[2] = 253;
				syslog(LOG_NOTICE, "== Com_SendSignal(14) ==");
				(void) Com_SendSignal(14U, &data[2]);
				
				syslog(LOG_NOTICE, "== Com_SwitchIpduTxMode(4) ==");
				Com_SwitchIpduTxMode(4U, FALSE);
				
				syslog(LOG_NOTICE, "== Com_SendSignalGroup(4) ==");
				(void) Com_SendSignalGroup(4U);
				
				syslog(LOG_NOTICE, "== Com_TriggerIPDUSend(4) ==");
				Com_TriggerIPDUSend(4U);
				break;
				
			case SND_DCM_CAN_SINGLE:
				/* Dcm送信確認(CAN シングルフレーム) */
				id = 0U;
				len = 1U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
				
			case SND_DCM_CAN_MULTI:
				/* Dcm送信確認(CAN マルチフレーム) */
				id = 0U;
				len = 8U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
				
			case SND_DCM_CANFD_SINGLE:
				/* Dcm送信確認(CANFD シングルフレーム) */
				id = 2U;
				len = 10U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
				
			case SND_DCM_CANFD_MULTI:
				/* Dcm送信確認(CANFD マルチフレーム) */
				id = 2U;
				len = 63U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
				
			case SND_DCM_CAN_SINGLE_EX:
				/* Dcm送信確認(CAN シングルフレーム) */
				id = 4U;
				len = 1U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
				
			case SND_DCM_CAN_MULTI_EX:
				/* Dcm送信確認(CAN マルチフレーム) */
				id = 4U;
				len = 8U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
				
			case SND_DCM_CAN_SINGLE_EX2:
				/* Dcm送信確認(CAN シングルフレーム) */
				id = 6U;
				len = 1U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
				
			case SND_DCM_CAN_MULTI_EX2:
				/* Dcm送信確認(CAN マルチフレーム) */
				id = 6U;
				len = 8U;
				for (i = 0; i < len; i++) {
					data[i] = (uint8)(i & 0xff);
				}
				syslog(LOG_NOTICE, "== DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", len);
				ercd = Transmit_functionality(id, data, len);
				break;
			case SND_DCM_CAN_CANCEL:
				/* Dcm送信キャンセル確認(CAN マルチフレーム) */
				id = 8U;
				Info.SduLength = 8U;
				syslog(LOG_NOTICE, "== PduR_DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", Info.SduLength);
				ercd = PduR_DcmTransmit(id, &Info);
				syslog(LOG_NOTICE, "** ret = %d **", ercd);
				syslog(LOG_NOTICE, "== PduR_DcmCancelTransmit(%d) ==", id);
				ercd = PduR_DcmCancelTransmit(id);
				syslog(LOG_NOTICE, "** ret = %d **", ercd);
				break;
				
			case SND_DCM_CANFD_CANCEL:
				/* Dcm送信キャンセル確認(CANFD マルチフレーム) */
				id = 10U;
				Info.SduLength = 63U;
				syslog(LOG_NOTICE, "== PduR_DcmTransmit(%d) ==", id);
				syslog(LOG_NOTICE, "** SduLength = %d **", Info.SduLength);
				ercd = PduR_DcmTransmit(id, &Info);
				syslog(LOG_NOTICE, "** ret = %d **", ercd);
				syslog(LOG_NOTICE, "== PduR_DcmCancelTransmit(%d) ==", id);
				ercd = PduR_DcmCancelTransmit(id);
				syslog(LOG_NOTICE, "** ret = %d **", ercd);
				break;
				
			}
			
			switch(rcv_mod)
			{
			case RCV_IDLE:
				/* 何もしない */
				break;
				
			case RCV_COM_CAN:
				/* Com受信確認(CAN) */
				syslog(LOG_NOTICE, "== Com_ReceiveSignalGroup(1) ==");
				(void) Com_ReceiveSignalGroup(1U);

				syslog(LOG_NOTICE, "== Com_ReceiveSignal(3) ==");
				(void) Com_ReceiveSignal(3U, &data[3]);

				syslog(LOG_NOTICE, "** data3 = %d **", data[3]);

				syslog(LOG_NOTICE, "== Com_ReceiveSignal(4) ==");
				(void) Com_ReceiveSignal(4U, &data[4]);

				syslog(LOG_NOTICE, "** data4 = %d **", data[4]);

				syslog(LOG_NOTICE, "== Com_ReceiveSignal(5) ==");
				(void) Com_ReceiveSignal(5U, &data[5]);

				syslog(LOG_NOTICE, "** data5 = %d **", data[5]);
				syslog(LOG_NOTICE, "");
				break;
				
			case RCV_COM_CANFD:
				/* Com受信確認(CANFD) */
				syslog(LOG_NOTICE, "== Com_ReceiveSignalGroup(5) ==");
				(void) Com_ReceiveSignalGroup(5U);

				syslog(LOG_NOTICE, "== Com_ReceiveSignal(15) ==");
				(void) Com_ReceiveSignal(15U, &data[3]);

				syslog(LOG_NOTICE, "** data3 = %d **", data[3]);

				syslog(LOG_NOTICE, "== Com_ReceiveSignal(16) ==");
				(void) Com_ReceiveSignal(16U, &data[4]);

				syslog(LOG_NOTICE, "** data4 = %d **", data[4]);

				syslog(LOG_NOTICE, "== Com_ReceiveSignal(17) ==");
				(void) Com_ReceiveSignal(17U, &data[5]);

				syslog(LOG_NOTICE, "** data5 = %d **", data[5]);
				syslog(LOG_NOTICE, "");
				break;
				
			case RCV_DCM_CAN_CANCEL:
				/* Dcm受信キャンセル確認(CAN マルチフレーム) */
				id = 9U;
				syslog(LOG_NOTICE, "== PduR_DcmCancelReceive(%d) ==", id);
				ercd = PduR_DcmCancelReceive(id);
				syslog(LOG_NOTICE, "** ret = %d **", ercd);
				Dcm_Init(NULL_PTR);
				break;
				
			case RCV_DCM_CANFD_CANCEL:
				/* Dcm受信キャンセル確認(CANFD マルチフレーム) */
				id = 11U;
				syslog(LOG_NOTICE, "== PduR_DcmCancelReceive(%d) ==", id);
				ercd = PduR_DcmCancelReceive(id);
				syslog(LOG_NOTICE, "** ret = %d **", ercd);
				Dcm_Init(NULL_PTR);
				break;
				
			}
			req = 0;
		}
		
		CanTp_MainFunction();
		Com_MainFunctionRx();
		Com_MainFunctionTx();
		
		/* ウェイト */
		for (i = 0U; i < 100000U; i++) {
		}
	}
	
	syslog(LOG_NOTICE, "== Shutdown ==");
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
