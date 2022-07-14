/*
 *  TOPPERS/A-CANTP
 *      Automotive CANTP
 *
 *  Copyright (C) 2016-2017 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2016-2017 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2016-2017 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2016-2017 by SCSK Corporation, JAPAN
 *  Copyright (C) 2016-2017 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2016-2017 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2016-2017 by Witz Corporation
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
#include "CanTp.h"
#include "CanTp_Cbk.h"
#include "t_syslog.h"

#define CANTP_MAIN_FUNCTION_PERIOD 5

#define CANFD_FF_SIZE 64

#define PADDING_MODE 1

#define TX_ID_INDEX_CanTp_Transmit			0
#define TX_ID_INDEX_CanIfId_Send			1
#define TX_ID_INDEX_CanTpId_Confirmation	2
#define TX_ID_INDEX_CanTpId_FcIndication	3
#define TX_ID_INDEX_PduRId_Confirmation		4

#define RX_ID_INDEX_CanTpId_Nsud			0
#define RX_ID_INDEX_CanIfId_FcSend			1
#define RX_ID_INDEX_CanTpId_Indication		2
#define RX_ID_INDEX_CanTpId_FcConfirmation	3
#define RX_ID_INDEX_PduRId_Indication		4

void SendSingleFrame(PduIdType *id, PduLengthType len);
void SendMultiFrame(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding);
void ReceiveSingleFrame(PduIdType *id, PduLengthType len, uint8 padding);
void ReceiveMultiFrame(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding);

void SendSingleFrameFD(PduIdType *id, PduLengthType len);
void SendMultiFrameFD(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding, uint8 div);
void ReceiveSingleFrameFD(PduIdType *id, PduLengthType len, uint8 padding);
void ReceiveMultiFrameFD(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding, uint8 div);

TASK(MainTask)
{
	Std_VersionInfoType vi;
	PduIdType id[5];

	syslog(LOG_NOTICE, "=== MainTask ===");

	syslog(LOG_NOTICE, "== CanTp_Init ==");
	CanTp_Init(NULL_PTR);

	syslog(LOG_NOTICE, "== CanTp_GetVersionInfo ==");
	CanTp_GetVersionInfo(&vi);
	syslog(LOG_NOTICE, "** versioninfo->vendorID = %d **", vi.vendorID);
	syslog(LOG_NOTICE, "** versioninfo->moduleID = %d **", vi.moduleID);
	syslog(LOG_NOTICE, "** versioninfo->sw_major_version = %d **", vi.sw_major_version);
	syslog(LOG_NOTICE, "** versioninfo->sw_minor_version = %d **", vi.sw_minor_version);
	syslog(LOG_NOTICE, "** versioninfo->sw_patch_version = %d **", vi.sw_patch_version);

/****************************** 送信 ******************************/
	id[TX_ID_INDEX_CanTp_Transmit] = 0x00;	/* CanTp_Transmit */
	id[TX_ID_INDEX_CanTpId_Confirmation] = 0x00;	/* CanTpId_Confirmation */
	id[TX_ID_INDEX_CanTpId_FcIndication] = 0x01;	/* CanTpId_FcIndication */
	id[TX_ID_INDEX_PduRId_Confirmation] = 0x08;	/* PduRId_Confirmation */
	
	/* シングルフレーム送信 */
	SendSingleFrame(id, 6);
	/* マルチフレーム送信 */
	SendMultiFrame(id, 8, 0, 0, PADDING_MODE);
	
/****************************** 受信 ******************************/
	id[RX_ID_INDEX_CanTpId_Nsud] = 0x01;
	id[RX_ID_INDEX_CanTpId_Indication] = 0x03;
	id[RX_ID_INDEX_CanTpId_FcConfirmation] = 0x02;
	id[RX_ID_INDEX_PduRId_Indication] = 0x09;
	
	/* シングルフレーム受信 */
	ReceiveSingleFrame(id, 6, PADDING_MODE);
	/* マルチフレーム受信 */
	ReceiveMultiFrame(id, 8, 0, 0, PADDING_MODE);
	
/****************************** 送信 ******************************/
	id[TX_ID_INDEX_CanTp_Transmit] = 0x02;	/* CanTp_Transmit */
	id[TX_ID_INDEX_CanTpId_Confirmation] = 0x04;	/* CanTpId_Confirmation */
	id[TX_ID_INDEX_CanTpId_FcIndication] = 0x05;	/* CanTpId_FcIndication */
	id[TX_ID_INDEX_PduRId_Confirmation] = 0x0a;	/* PduRId_Confirmation */
	
	/* シングルフレーム送信 */
	SendSingleFrameFD(id, 61);
	/* マルチフレーム送信 */
	SendMultiFrameFD(id, 128, 0, 0, PADDING_MODE, CANFD_FF_SIZE);
	
/****************************** 受信 ******************************/
	id[RX_ID_INDEX_CanTpId_Nsud] = 0x03;
	id[RX_ID_INDEX_CanTpId_Indication] = 0x07;
	id[RX_ID_INDEX_CanTpId_FcConfirmation] = 0x06;
	id[RX_ID_INDEX_PduRId_Indication] = 0x0b;
	
	/* シングルフレーム受信 */
	ReceiveSingleFrameFD(id, 61, PADDING_MODE);
	/* マルチフレーム受信 */
	ReceiveMultiFrameFD(id, 128, 0, 0, PADDING_MODE, CANFD_FF_SIZE);
	
	syslog(LOG_NOTICE, "== CanTp_Shutdown ==");
	CanTp_Shutdown();
}

/* シングルフレーム送信 */
void SendSingleFrame(PduIdType *id, PduLengthType len)
{
	Std_ReturnType ercd;
	PduInfoType CanTpInfo;
	
	CanTpInfo.SduLength = len;
	CanTpInfo.SduDataPtr = NULL_PTR;
	syslog(LOG_NOTICE, "---Send SingleFrame Start---");
	
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) Start ==", id[TX_ID_INDEX_CanTp_Transmit]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	ercd = CanTp_Transmit(id[TX_ID_INDEX_CanTp_Transmit], &CanTpInfo);
	syslog(LOG_NOTICE, "** ret = 0x%02x **", ercd);
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) End ==", id[TX_ID_INDEX_CanTp_Transmit]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "---Send SingleFrame End---\n");
}

/* マルチフレーム送信 */
void SendMultiFrame(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding)
{
	Std_ReturnType ercd;
	PduInfoType CanTpInfo;
	uint8 data[64];
	uint8 i;
	uint16 bs_cnt = 0;
	uint32 cf_cnt = 0;
	uint8 stmin_cnt = 0;
	
	stmin_cnt = (uint8)(stmin / CANTP_MAIN_FUNCTION_PERIOD);
	if ((stmin % CANTP_MAIN_FUNCTION_PERIOD) !=0 ) {
		stmin_cnt++;
	}
	stmin_cnt++;
	
	CanTpInfo.SduLength = len;
	CanTpInfo.SduDataPtr = NULL_PTR;
	syslog(LOG_NOTICE, "---Send MultiFrame Start---");
	
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) Start ==", id[TX_ID_INDEX_CanTp_Transmit]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	ercd = CanTp_Transmit(id[TX_ID_INDEX_CanTp_Transmit], &CanTpInfo);
	syslog(LOG_NOTICE, "** ret = 0x%02x **", ercd);
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) End ==", id[TX_ID_INDEX_CanTp_Transmit]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	if (len <= 4095) {
		len -= 6;
	}
	else {
		len -= 2;
	}
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	while(len != 0) {
		/* FC受信 */
		CanTpInfo.SduLength = 3;
		CanTpInfo.SduDataPtr = data;
		data[0] = 0x30;
		data[1] = bs;
		data[2] = stmin;
		if (padding == 1) {
			for (i=3; i<8; i++) {
				data[i] = 0xFF;
				CanTpInfo.SduLength++;
			}
		}
		syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_FcIndication]);
		syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
		for (i = 0U; i < CanTpInfo.SduLength; i++) {
			syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
		}
		CanTp_RxIndication(id[TX_ID_INDEX_CanTpId_FcIndication], &CanTpInfo);
		syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_FcIndication]);
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
		
		for (bs_cnt=0; bs_cnt<bs; bs_cnt++ ) {
			syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
			CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
			syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
			syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
			cf_cnt++;
			if (len>7) {
				len -= 7;
			}
			else {
				len = 0;
				break;
			}
			
			if (bs_cnt != (bs - 1)) {
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		if (bs == 0) {
			while(len != 0) {
				syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
				CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
				syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
				syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
				cf_cnt++;
				if (len>7) {
					len -= 7;
				}
				else {
					len = 0;
					break;
				}
				
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	}
	
	syslog(LOG_NOTICE, "---Send MultiFrame End---\n");
}

/* シングルフレーム受信 */
void ReceiveSingleFrame(PduIdType *id, PduLengthType len, uint8 padding)
{
	PduInfoType CanTpInfo;
	uint8 data[64];
	uint8 i;
	
	syslog(LOG_NOTICE, "---Receive SingleFrame Start---");
	CanTpInfo.SduLength = len;
	CanTpInfo.SduDataPtr = data;
	data[0] = len;
	CanTpInfo.SduLength++;
	for (i=0; i<len; i++) {
		data[i+1] = i;
	}
	if (padding == 1) {
		for (i=len+1; i<8; i++) {
			data[i] = 0xFF;
			CanTpInfo.SduLength++;
		}
	}
	
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	for (i = 0U; i < CanTpInfo.SduLength; i++) {
		syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
	}
	CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);

	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "---Receive SingleFrame End---\n");
}

/* マルチフレーム受信 */
void ReceiveMultiFrame(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding)
{
	PduInfoType CanTpInfo;
	uint8 data[64];
	uint8 i;
	uint8 sn = 1;
	uint16 bs_cnt = 0;
	uint32 cf_cnt= 0;
	uint8 stmin_cnt = 0;
	
	stmin_cnt = (uint8)(stmin / CANTP_MAIN_FUNCTION_PERIOD);
	if ((stmin % CANTP_MAIN_FUNCTION_PERIOD) !=0 ) {
		stmin_cnt++;
	}
	stmin_cnt++;
	
	syslog(LOG_NOTICE, "---Receive MultiFrame Start---");
	CanTpInfo.SduLength = 8;
	CanTpInfo.SduDataPtr = data;
	if (len <= 4095) {
		data[0] = 0x10 | ((len >> 8) &0x0f);
		data[1] = len & 0xff;
		for (i=2; i<8; i++) {
			data[i] = i;
		}
		len -= 6;
	}
	else {
		data[0] = 0x10;
		data[1] = 0x00;
		data[2] = (uint8)((len >> 24) & 0xff);
		data[3] = (uint8)((len >> 16) & 0xff);
		data[4] = (uint8)((len >> 8) & 0xff);
		data[5] = (uint8)(len & 0xff);
		for (i=6; i<8; i++) {
			data[i] = i;
		}
		len -= 2;
	}
	
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	for (i = 0U; i < CanTpInfo.SduLength; i++) {
		syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
	}
	CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	while(len != 0) {
		/* FC送信 */
		CanTpInfo.SduLength = 8;
		CanTpInfo.SduDataPtr = NULL_PTR;
		syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_FcConfirmation]);
		CanTp_TxConfirmation(id[RX_ID_INDEX_CanTpId_FcConfirmation]);
		syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_FcConfirmation]);
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
		
		for (bs_cnt=0; bs_cnt<bs; bs_cnt++ ) {
			CanTpInfo.SduLength = 0;
			CanTpInfo.SduDataPtr = data;
			data[0] = 0x20 | sn;
			CanTpInfo.SduLength++;
			if (len < 7) {
				for (i=0; i<len; i++) {
					data[i+1] = i;
					CanTpInfo.SduLength++;
				}
				if (padding == 1) {
					for (i=len+1; i<8; i++) {
						data[i] = 0xFF;
						CanTpInfo.SduLength++;
					}
				}
			}
			else {
				for (i=1; i<8; i++) {
					data[i] = i;
					CanTpInfo.SduLength++;
				}
			}
			
			syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
			syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
			for (i = 0U; i < CanTpInfo.SduLength; i++) {
				syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
			}
			CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
			syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);
			syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
			cf_cnt++;
			if (len>7) {
				len -= 7;
			}
			else {
				len = 0;
				break;
			}
			sn++;
			if (sn>=0x10) {
				sn = 0;
			}
			
			if (bs_cnt != (bs - 1)) {
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		if (bs == 0) {
			while(len != 0) {
				CanTpInfo.SduLength = 0;
				CanTpInfo.SduDataPtr = data;
				data[0] = 0x20 | sn;
				CanTpInfo.SduLength++;
				if (len < 7) {
					for (i=0; i<len; i++) {
						data[i+1] = i;
						CanTpInfo.SduLength++;
					}
					if (padding == 1) {
						for (i=len+1; i<8; i++) {
							data[i] = 0xFF;
							CanTpInfo.SduLength++;
						}
					}
				}
				else {
					for (i=1; i<8; i++) {
						data[i] = i;
						CanTpInfo.SduLength++;
					}
				}
				
				syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
				syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
				for (i = 0U; i < CanTpInfo.SduLength; i++) {
					syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
				}
				CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
				syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);
				syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
				cf_cnt++;
				if (len>7) {
					len -= 7;
				}
				else {
					len = 0;
					break;
				}
				sn++;
				if (sn>=0x10) {
					sn = 0;
				}
				
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	}
	
	syslog(LOG_NOTICE, "---Receive MultiFrame End---\n");
}

/* シングルフレーム送信 */
void SendSingleFrameFD(PduIdType *id, PduLengthType len)
{
	Std_ReturnType ercd;
	PduInfoType CanTpInfo;
	
	CanTpInfo.SduLength = len;
	CanTpInfo.SduDataPtr = NULL_PTR;
	syslog(LOG_NOTICE, "---Send SingleFrame Start---");
	
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) Start ==", id[TX_ID_INDEX_CanTp_Transmit]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	ercd = CanTp_Transmit(id[TX_ID_INDEX_CanTp_Transmit], &CanTpInfo);
	syslog(LOG_NOTICE, "** ret = 0x%02x **", ercd);
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) End ==", id[TX_ID_INDEX_CanTp_Transmit]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "---Send SingleFrame End---\n");
}

/* マルチフレーム送信 */
void SendMultiFrameFD(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding, uint8 div)
{
	Std_ReturnType ercd;
	PduInfoType CanTpInfo;
	uint8 data[64];
	uint8 i;
	uint16 bs_cnt = 0;
	uint32 cf_cnt = 0;
	uint8 stmin_cnt = 0;
	
	stmin_cnt = (uint8)(stmin / CANTP_MAIN_FUNCTION_PERIOD);
	if ((stmin % CANTP_MAIN_FUNCTION_PERIOD) !=0 ) {
		stmin_cnt++;
	}
	stmin_cnt++;
	
	CanTpInfo.SduLength = len;
	CanTpInfo.SduDataPtr = NULL_PTR;
	syslog(LOG_NOTICE, "---Send MultiFrame Start---");
	
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) Start ==", id[TX_ID_INDEX_CanTp_Transmit]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	ercd = CanTp_Transmit(id[TX_ID_INDEX_CanTp_Transmit], &CanTpInfo);
	syslog(LOG_NOTICE, "** ret = 0x%02x **", ercd);
	syslog(LOG_NOTICE, "== CanTp_Transmit(0x%02x) End ==", id[TX_ID_INDEX_CanTp_Transmit]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
	syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
	len -= (div-2);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	while(len != 0) {
		/* FC受信 */
		CanTpInfo.SduLength = 3;
		CanTpInfo.SduDataPtr = data;
		data[0] = 0x30;
		data[1] = bs;
		data[2] = stmin;
		if (padding == 1) {
			for (i=3; i<8; i++) {
				data[i] = 0xFF;
				CanTpInfo.SduLength++;
			}
		}
		syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_FcIndication]);
		syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
		for (i = 0U; i < CanTpInfo.SduLength; i++) {
			syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
		}
		CanTp_RxIndication(id[TX_ID_INDEX_CanTpId_FcIndication], &CanTpInfo);
		syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_FcIndication]);
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
		
		for (bs_cnt=0; bs_cnt<bs; bs_cnt++ ) {
			syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
			CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
			syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
			syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
			cf_cnt++;
			if (len>(div-1)) {
				len -= (div-1);
			}
			else {
				len = 0;
				break;
			}
			
			if (bs_cnt != (bs - 1)) {
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		if (bs == 0) {
			while(len != 0) {
				syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
				CanTp_TxConfirmation(id[TX_ID_INDEX_CanTpId_Confirmation]);
				syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[TX_ID_INDEX_CanTpId_Confirmation]);
				syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
				cf_cnt++;
				if (len>(div-1)) {
					len -= (div-1);
				}
				else {
					len = 0;
					break;
				}
				
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	}
	
	syslog(LOG_NOTICE, "---Send MultiFrame End---\n");
}

/* シングルフレーム受信 */
void ReceiveSingleFrameFD(PduIdType *id, PduLengthType len, uint8 padding)
{
	PduInfoType CanTpInfo;
	uint8 data[64];
	uint8 i;
	
	syslog(LOG_NOTICE, "---Receive SingleFrame Start---");
	CanTpInfo.SduLength = 0;
	CanTpInfo.SduDataPtr = data;
	if ((len+1) <= 8) {
		data[0] = len;
		CanTpInfo.SduLength++;
	}
	else {
		data[0] = 0x00;
		CanTpInfo.SduLength++;
		data[1] = len;
		CanTpInfo.SduLength++;
	}
	len += CanTpInfo.SduLength;
	for (i=CanTpInfo.SduLength; i<len; i++) {
		data[i] = i;
		CanTpInfo.SduLength++;
	}
	if (padding == 1) {
		for (i=CanTpInfo.SduLength; i<8; i++) {
			data[i] = 0xFF;
			CanTpInfo.SduLength++;
		}
	}
	if (CanTpInfo.SduLength > 8) {
		for (i=CanTpInfo.SduLength; i<64; i++) {
			switch(i) {
			case 9:
			case 12:
			case 16:
			case 20:
			case 24:
			case 32:
			case 48:
				i = 64;
				break;
			default :
				data[i] = 0xFF;
				CanTpInfo.SduLength++;
				break;
			}
		}
	}
	
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	for (i = 0U; i < CanTpInfo.SduLength; i++) {
		syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
	}
	CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);

	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	
	syslog(LOG_NOTICE, "---Receive SingleFrame End---\n");
}

/* マルチフレーム受信 */
void ReceiveMultiFrameFD(PduIdType *id, PduLengthType len, uint8 bs, uint8 stmin, uint8 padding, uint8 div)
{
	PduInfoType CanTpInfo;
	uint8 data[64];
	uint8 i;
	uint8 sn = 1;
	uint16 bs_cnt = 0;
	uint32 cf_cnt= 0;
	uint8 stmin_cnt = 0;
	
	stmin_cnt = (uint8)(stmin / CANTP_MAIN_FUNCTION_PERIOD);
	if ((stmin % CANTP_MAIN_FUNCTION_PERIOD) !=0 ) {
		stmin_cnt++;
	}
	stmin_cnt++;
	
	syslog(LOG_NOTICE, "---Receive MultiFrame Start---");
	CanTpInfo.SduLength = div;
	CanTpInfo.SduDataPtr = data;
	data[0] = 0x10 | ((len >> 8) &0x0f);
	data[1] = len & 0xff;
	for (i=2; i<div; i++) {
		data[i] = i;
	}
	
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
	syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
	for (i = 0U; i < CanTpInfo.SduLength; i++) {
		syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
	}
	CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
	syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);
	
	syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
	CanTp_MainFunction();
	syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	len -= (div-2);
	
	while(len != 0) {
		/* FC送信 */
		CanTpInfo.SduLength = div;
		CanTpInfo.SduDataPtr = NULL_PTR;
		syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_FcConfirmation]);
		CanTp_TxConfirmation(id[RX_ID_INDEX_CanTpId_FcConfirmation]);
		syslog(LOG_NOTICE, "== CanTp_TxConfirmation(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_FcConfirmation]);
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
		
		for (bs_cnt=0; bs_cnt<bs; bs_cnt++ ) {
			CanTpInfo.SduLength = 0;
			CanTpInfo.SduDataPtr = data;
			data[0] = 0x20 | sn;
			CanTpInfo.SduLength++;
			if (len < (div-1)) {
				for (i=0; i<len; i++) {
					data[i+1] = i;
					CanTpInfo.SduLength++;
				}
				if (padding == 1) {
					for (i=len+1; i<8; i++) {
						data[i] = 0xFF;
						CanTpInfo.SduLength++;
					}
				}
				if ((len+1) > 8) {
					for (i=len+1; i<div; i++) {
						switch(i) {
						case 12:
						case 16:
						case 20:
						case 24:
						case 32:
						case 48:
							i = div;
							break;
						default :
							data[i] = 0xFF;
							CanTpInfo.SduLength++;
							break;
						}
					}
				}
			}
			else {
				for (i=1; i<div; i++) {
					data[i] = i;
					CanTpInfo.SduLength++;
				}
			}
			
			syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
			syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
			for (i = 0U; i < CanTpInfo.SduLength; i++) {
				syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
			}
			CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
			syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);
			syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
			cf_cnt++;
			if (len>(div-1)) {
				len -= (div-1);
			}
			else {
				len = 0;
				break;
			}
			sn++;
			if (sn>=0x10) {
				sn = 0;
			}
			
			if (bs_cnt != (bs - 1)) {
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		if (bs == 0) {
			while(len != 0) {
				CanTpInfo.SduLength = 0;
				CanTpInfo.SduDataPtr = data;
				data[0] = 0x20 | sn;
				CanTpInfo.SduLength++;
				if (len < (div-1)) {
					for (i=0; i<len; i++) {
						data[i+1] = i;
						CanTpInfo.SduLength++;
					}
					if (padding == 1) {
						for (i=len+1; i<8; i++) {
							data[i] = 0xFF;
							CanTpInfo.SduLength++;
						}
					}
					if ((len+1) > 8) {
						for (i=len+1; i<div; i++) {
							switch(i) {
							case 12:
							case 16:
							case 20:
							case 24:
							case 32:
							case 48:
								i = div;
								break;
							default :
								data[i] = 0xFF;
								CanTpInfo.SduLength++;
								break;
							}
						}
					}
				}
				else {
					for (i=1; i<div; i++) {
						data[i] = i;
						CanTpInfo.SduLength++;
					}
				}
				
				syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) Start ==", id[RX_ID_INDEX_CanTpId_Indication]);
				syslog(LOG_NOTICE, "** SduLength = %d **", CanTpInfo.SduLength);
				for (i = 0U; i < CanTpInfo.SduLength; i++) {
					syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, CanTpInfo.SduDataPtr[i]);
				}
				CanTp_RxIndication(id[RX_ID_INDEX_CanTpId_Indication], &CanTpInfo);
				syslog(LOG_NOTICE, "== CanTp_RxIndication(0x%02x) End ==", id[RX_ID_INDEX_CanTpId_Indication]);
				syslog(LOG_NOTICE, "** cf_cnt = %d **", cf_cnt);
				cf_cnt++;
				if (len>(div-1)) {
					len -= (div-1);
				}
				else {
					len = 0;
					break;
				}
				sn++;
				if (sn>=0x10) {
					sn = 0;
				}
				
				for (i=0; i<stmin_cnt; i++) {
					syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
					CanTp_MainFunction();
					syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
				}
			}
		}
		
		syslog(LOG_NOTICE, "== CanTp_MainFunction Start ==");
		CanTp_MainFunction();
		syslog(LOG_NOTICE, "== CanTp_MainFunction End ==");
	}
	
	syslog(LOG_NOTICE, "---Receive MultiFrame End---\n");
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
