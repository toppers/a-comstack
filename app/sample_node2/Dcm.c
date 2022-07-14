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
 *  $Id: Dcm.c 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

/*
 *	Dcmサンプルプログラム
 *  プログラムの概要：
 *  メッセージを受信し、受信したメッセージデータをそのまま送信する
 *  ※Data_Indication_functionality（受信完了通知）内でTransmit_functionality（送信）を実施
 */
#include "t_syslog.h"
#include "Dcm.h"
#include "PduR_Dcm.h"

#define BUF_SIZE 65535


static uint8 SndBuf[BUF_SIZE];
static uint8 RcvBuf[BUF_SIZE];
static PduLengthType SndLen = 0;
static PduLengthType SndIndex = 0;
static PduLengthType RcvLen = 0;
static PduLengthType RcvIndex = 0;
static uint8 SndStatus = DCM_SND_IDLE;
static uint8 RcvStatus = DCM_RCV_IDLE;
static PduIdType SndId = 0;
static PduIdType RcvId = 0;

static const Dcm_ConfigType		*p_cur_dcm_config;

/* DcmのPduId->PduRのId変換テーブル */
/* DcmのPduId0から順にPduRのIdを指定する
 * ※PduR_DcmTransmitの引数で使用するID
 */
PduIdType PduRid[] = {
	8U,9U,10U,11U,12U,13U,14U,15U
};

/* コンフィギュレーション */
/* PduId->PduRのId変換テーブルを指定 */
static const Dcm_ConfigType dcm_config[1] = {
	{
		PduRid
	}
};

/* 初期化 */
void Dcm_Init(const Dcm_ConfigType* ConfigPtr)
{
	syslog(LOG_NOTICE, "== Dcm_Init ==");
	
	/* コンフィギュレーションは固定 */
	p_cur_dcm_config = &dcm_config[0];
	
	/* 内部変数初期化 */
	SndLen = 0;
	SndIndex = 0;
	RcvLen = 0;
	RcvIndex = 0;
	SndStatus = DCM_SND_IDLE;
	RcvStatus = DCM_RCV_IDLE;
	return;
}

/* 送信完了通知 */
void
Dcm_TpTxConfirmation(PduIdType id, Std_ReturnType result)
{
	if ((SndStatus == DCM_SND_PROC) && (id == SndId)) {
		/* 上位への送信完了通知 */
		Data_Confirmation_functionality(id, result);
		SndStatus = DCM_SND_IDLE;
	}
	return;
}

/* 受信完了通知 */
void
Dcm_TpRxIndication(PduIdType id, Std_ReturnType result)
{
	PduInfoType info;
	
	if ((RcvStatus == DCM_RCV_PROC) && (id == RcvId)) {
		/* 上位への受信完了通知 */
		info.SduLength = RcvLen;
		info.SduDataPtr = RcvBuf;
		Data_Indication_functionality(id, &info, result);
		RcvStatus = DCM_RCV_IDLE;
	}
	return;
}

/* 受信開始 */
BufReq_ReturnType
Dcm_StartOfReception(PduIdType id, const PduInfoType *info, PduLengthType TpSduLength, PduLengthType *bufferSizePtr)
{
	RcvId = id;
	RcvLen = TpSduLength;
	RcvIndex = 0;
	*bufferSizePtr = BUF_SIZE;
	RcvStatus = DCM_RCV_PROC;
	
	return(BUFREQ_OK);
}

/* 受信データコピー */
BufReq_ReturnType
Dcm_CopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr)
{
	PduLengthType i;

	if ((RcvStatus == DCM_RCV_PROC) && (id == RcvId)) {
		for (i = 0U; i < info->SduLength; i++) {
			RcvBuf[i + RcvIndex] = info->SduDataPtr[i];
		}
		RcvIndex += info->SduLength;
		*bufferSizePtr = BUF_SIZE - RcvIndex;
	}
	
	return(BUFREQ_OK);
}

/* 送信データコピー */
BufReq_ReturnType
Dcm_CopyTxData(PduIdType id, PduInfoType *info, RetryInfoType *retry, PduLengthType *availableDataPtr)
{
	PduLengthType i;

	if ((SndStatus == DCM_SND_PROC) && (id == SndId)) {
		for (i = 0U; i < info->SduLength; i++) {
			info->SduDataPtr[i] = SndBuf[i + SndIndex];
		}
		SndIndex += info->SduLength;
	}
	
	return(BUFREQ_OK);
}

/* 送信 */
Std_ReturnType Transmit_functionality(PduIdType id, uint8 data[], PduLengthType len)
{
	Std_ReturnType ret;
	PduLengthType i;
	PduInfoType info;
	
	syslog(LOG_NOTICE, "== Transmit_functionality(0x%02x) ==", id);
	
	info.SduLength = len;
	ret = PduR_DcmTransmit(p_cur_dcm_config->PduRId[id], &info);
	
	if (ret == E_OK) {
		/* データ保持 */
		SndId = id;
		SndLen = len;
		SndIndex = 0;
		syslog(LOG_NOTICE, "** SendData **");
		syslog(LOG_NOTICE, "** SduLength: %d **", SndLen);
		for(i = 0; i < len; i++)
		{
			SndBuf[i] = data[i];
			syslog(LOG_NOTICE, "** SduDataPtr[%d]: 0x%02x **", i, SndBuf[i]);
		}
		SndStatus = DCM_SND_PROC;
	}
	
	return(ret);
}

/* 送信完了通知 */
void Data_Confirmation_functionality(PduIdType id, Std_ReturnType result)
{
	syslog(LOG_NOTICE, "== Data_Confirmation_functionality(0x%02x) ret:%d ==", id, result);
}

/* 受信完了通知 */
void Data_Indication_functionality(PduIdType id, PduInfoType *info, Std_ReturnType result)
{
	PduLengthType i;
	
	syslog(LOG_NOTICE, "== Data_Indication_functionality(0x%02x) ret:%d ==", id, result);
	
	if (result == E_OK) {
		syslog(LOG_NOTICE, "** ReceiveData **");
		syslog(LOG_NOTICE, "** SduLength: %d **", info->SduLength);
		for (i = 0U; i < info->SduLength; i++) {
			syslog(LOG_NOTICE, "** SduData[%d]: 0x%02x **", i, info->SduDataPtr[i]);
		}
//		/* 応答送信 */
//		Transmit_functionality(id - 1, RcvBuf, info->SduLength);
	}
}

uint8 get_dcm_rcv_status()
{
	return(RcvStatus);
}

uint8 get_dcm_snd_status()
{
	return(SndStatus);
}

