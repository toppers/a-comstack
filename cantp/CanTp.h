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
 *  $Id: CanTp.h 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

/* CanTp.h */

/*
 *  開発方針
 *  - [CANIF565] Debuggingでアクセス可能な各変数はグローバル変数で定義する
 *  - [CANIF566] CanIf.hをincludeするだけで全てのデータ型を使用可能とする
 *  - [CANIF567] 定義したデータ型のサイズをsizeofで取得可能とする
 *  - [CANIF568] デバッグするための変数にはそれぞれ説明を書く
 *  - [CANIF672] CanIf.hにはCanIf SWSで規定された定数やグローバルデータ，システムサービスのみを記載する
 *  - [CANIF725] 標準化されたパラメータは本ヘッダファイルで他のBSWに提供可能とする
 */

#ifndef CANTP_H
#define CANTP_H

#include "ComStack_Types.h"		/* [SWS_CanTp_00156][SWS_CanTp_00209] */
#include "CanTp_Cfg.h"

/* モジュールID */
#define CANTP_MODULE_ID					0x23U		/* [SWS_CanTp_00115] */

/* DETエラーコード */
#define CANTP_E_INIT_FAILED				0x04U		/* [SWS_CanTp_00293] */
#define CANTP_E_UNINIT					0x20U		/* [SWS_CanTp_00293] */
#define CANTP_E_INVALID_TX_ID			0x30U		/* [SWS_CanTp_00293] */
#define CANTP_E_INVALID_RX_ID			0x40U		/* [SWS_CanTp_00293] */
#define CANTP_E_PADDING					0x70U		/* [SWS_CanTp_00293] */
#define CANTP_E_PARAM_CONFIG			0x01U		/* [SWS_CanTp_00352] */
#define CANTP_E_PARAM_ID				0x02U		/* [SWS_CanTp_00352] */
#define CANTP_E_PARAM_POINTER			0x03U		/* [SWS_CanTp_00352] */
#define CANTP_E_INVALID_TATYPE			0x90U		/* [SWS_CanTp_00352] */
#define CANTP_E_OPER_NOT_SUPPORTED		0xA0U		/* [SWS_CanTp_00352] */
#define CANTP_E_COM						0xB0U		/* [SWS_CanTp_00352] */
#define CANTP_E_RX_COM					0xC0U		/* [SWS_CanTp_00352] */
#define CANTP_E_TX_COM					0xD0U		/* [SWS_CanTp_00352] */

/* CANTP送受信状態 */
#define CANTP_STATUS_IDLE				0x00U

/* CANTP受信状態 */
#define CANTP_STATUS_SND_FC				0x01U
#define CANTP_STATUS_END_FC				0x02U
#define CANTP_STATUS_WAIT_CF			0x03U

/* CANTP送信状態 */
#define CANTP_STATUS_SND_SF				0x01U
#define CANTP_STATUS_END_SF				0x02U
#define CANTP_STATUS_SND_FF				0x03U
#define CANTP_STATUS_END_FF				0x04U
#define CANTP_STATUS_WAIT_FC			0x05U
#define CANTP_STATUS_SND_CF				0x06U
#define CANTP_STATUS_END_CF				0x07U

/* タイマステータス */
#define CANTP_TIME_STOP					0x00U
#define CANTP_TIME_AS					0x01U
#define CANTP_TIME_BS					0x02U
#define CANTP_TIME_CS					0x03U
#define CANTP_TIME_AR					0x04U
#define CANTP_TIME_BR					0x05U
#define CANTP_TIME_CR					0x06U

/* タイマクリア */
#define CANTP_TIMECNT_CLR				0x00000000U


/* N_PDU識別 */
#define CANTP_NPCI_SF					0x00U
#define CANTP_NPCI_FF					0x10U
#define CANTP_NPCI_CF					0x20U
#define CANTP_NPCI_FC					0x30U

/* データ長 */
#define CANTP_SF_8MAX_NPCI_LEN			(PduLengthType)0x01U
#define CANTP_SF_8OVER_NPCI_LEN			(PduLengthType)0x02U
#define CANTP_FF_4095MAX_NPCI_LEN		(PduLengthType)0x02U
#define CANTP_FF_4095OVER_NPCI_LEN		(PduLengthType)0x06U
#define CANTP_CF_NPCI_LEN				(PduLengthType)0x01U
#define CANTP_FC_NPCI_LEN				(PduLengthType)0x01U

/* FS */
#define CANTP_FS_CTS					0x00U
#define CANTP_FS_WAIT					0x01U
#define CANTP_FS_OVFLW					0x02U

/* シーケンスナンバー最大値 */
#define CANTP_SN_MAX					0x0FU

/* 閾値 */
#define CANTP_THRESHOLD_SF				8U
#define CANTP_THRESHOLD_FF				4095U

/* DLC */
#define CANTP_CAN_DL					0x08U
#define CANTP_CANFD_DL					0x40U

/* STmin */
#define CANTP_FC_STMIN_MS_MIN			0x01U
#define CANTP_FC_STMIN_MS_MAX			0x7FU
#define CANTP_FC_STMIN_US_MIN			0xF1U
#define CANTP_FC_STMIN_US_MAX			0xF9U

/* CANFDのDLC範囲 */
#define CANTP_CANFD_DL_8				8U
#define CANTP_CANFD_DL_12				12U
#define CANTP_CANFD_DL_16				16U
#define CANTP_CANFD_DL_20				20U
#define CANTP_CANFD_DL_24				24U
#define CANTP_CANFD_DL_32				32U
#define CANTP_CANFD_DL_48				48U
#define CANTP_CANFD_DL_64				64U

/* クリア値 */
#define CANTP_UINT8_CLR					(uint8)0x00U
#define CANTP_UINT16_CLR				(uint16)0x0000U
#define CANTP_UINT32_CLR				(uint32)0x00000000U
#define CANTP_ZERO						0x00U
#define CANTP_UINT8_1					(uint8)0x01U
#define CANTP_UINT8_4					(uint8)0x04U

#define CANTP_TRUE						0x01U
#define CANTP_FALSE						0x00U

/* アドレスフォーマットインデックス */
#define CANTP_STANDARD_IND_DATA			0x00U
#define CANTP_EXTENDED_IND_NTA			0x00U
#define CANTP_EXTENDED_IND_DATA			0x01U
#define CANTP_MIXED_IND_NAE				0x00U
#define CANTP_MIXED_IND_DATA			0x01U

/* MAX値 */
#define CANTP_UINT8_MAX					0xFFU

/* マスク用 */
#define CANTP_UINT8_MASK_0F				(uint8)0x0FU
#define CANTP_UINT8_MASK_F0				(uint8)0xF0U
#define CANTP_UINT8_MASK_FF				(uint8)0xFFU

/* ビットシフト用 */
#define CANTP_SHIFT_8					8U
#define CANTP_SHIFT_16					16U
#define CANTP_SHIFT_24					24U

/* 無効値 */
#define CANTP_INVALID_ID				(PduIdType)0xFFFFU

/* コンフィグ設定用 */
/* 通信方向 */
#define CANTP_SEND						0x00U
#define CANTP_RECEIVE					0x01U

/* 通信方式 */
#define CANTP_MODE_FULL_DUPLEX			0x00U
#define CANTP_MODE_HALF_DUPLEX			0x01U

/* アドレスフォーマット */
#define CANTP_EXTENDED					0x00U
#define CANTP_MIXED						0x01U
#define CANTP_MIXED29BIT				0x02U
#define CANTP_NORMALFIXED				0x03U
#define CANTP_STANDARD					0x04U

/* 送受信パディング動作設定 */
#define CANTP_OFF						0x00U
#define CANTP_ON						0x01U

/* 通信タイプ */
#define CANTP_CANFD_FUNCTIONAL			0x00U
#define CANTP_CANFD_PHYSICAL			0x01U
#define CANTP_FUNCTIONAL				0x02U
#define CANTP_PHYSICAL					0x03U



/*
 *  [SWS_CanTp_00008][NCanTp_00030][SWS_CanTp_00006][SWS_BSW_00203][SWS_CanTp_00115][SWS_CanTp_00217]
 *  チェックマクロ
 */
#if CANTP_DEV_ERROR_DETECT == STD_ON
#define CANTP_SWITCH_DET_ERROR(ApiId, ErrorId)	(void) Det_ReportError(CANTP_MODULE_ID, 0U, (ApiId), (ErrorId))

#define CANTP_CHECK_PARAM(exp, ApiId, ErrorId)								 \
	do {																	 \
		if (!(exp)) {														 \
			(void) Det_ReportError(CANTP_MODULE_ID, 0U, (ApiId), (ErrorId)); \
			goto error_exit;												 \
		}																	 \
	} while (0)


#else /* CANTP_DEV_ERROR_DETECT == STD_OFF */
#define CANTP_SWITCH_DET_ERROR(ApiId, ErrorId)
#define CANTP_CHECK_PARAM(exp, ApiId, ErrorId)
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */


/* タイマ関連 */
#define CANTP_SET_RX_TIMER(p_ch_rx_cb, timer, time)							 \
	do {																	 \
		(p_ch_rx_cb)->rx_time = (timer);									 \
		(p_ch_rx_cb)->rx_time_cnt = (time);									 \
	} while (0)

#define CANTP_SET_TX_TIMER(p_ch_tx_cb, timer, time)							 \
	do {																	 \
		(p_ch_tx_cb)->tx_time = (timer);									 \
		(p_ch_tx_cb)->tx_time_cnt = (time);									 \
	} while (0)

#define CANTP_CLR_RX_TIMER(p_ch_rx_cb)										 \
	do {																	 \
		(p_ch_rx_cb)->rx_time = CANTP_TIME_STOP;							 \
		(p_ch_rx_cb)->rx_time_cnt = CANTP_TIMECNT_CLR;						 \
	} while (0)

#define CANTP_CLR_TX_TIMER(p_ch_tx_cb)										 \
	do {																	 \
		(p_ch_tx_cb)->tx_time = CANTP_TIME_STOP;							 \
		(p_ch_tx_cb)->tx_time_cnt = CANTP_TIMECNT_CLR;						 \
	} while (0)


/*
 *  [SWS_CanTp_00267]AUTOSARリリースバージョン
 */
#define CANTP_AR_RELEASE_MAJOR_VERSION		4U
#define CANTP_AR_RELEASE_MINOR_VERSION		2U
#define CANTP_AR_RELEASE_REVISION_VERSION	2U

/*
 *  サプライヤバージョン情報
 */
#define CANTP_SW_MAJOR_VERSION	1U
#define CANTP_SW_MINOR_VERSION	0U
#define CANTP_SW_PATCH_VERSION	0U
#define CANTP_VENDOR_ID			65U

/*
 *  情報取得マクロ
 */
#define GET_CH_INIB(ch)						(&(p_cur_cantp_config->p_ch_inib_table[(ch)]))
#define GET_CH_RX_CB(ch)					((p_cur_cantp_config->p_ch_inib_table[(ch)]).p_ch_rx_cb)
#define GET_CH_TX_CB(ch)					((p_cur_cantp_config->p_ch_inib_table[(ch)]).p_ch_tx_cb)

#define GET_NSDU_INIB(PduId)				(&(p_cur_cantp_config->p_nsdu_inib_table[(PduId)]))
#define GET_RX_NSDU_INIB(PduId)				((const RX_NSDU_INIB*)((p_cur_cantp_config->p_nsdu_inib_table[(PduId)]).rxtx_inib))
#define GET_TX_NSDU_INIB(PduId)				((const TX_NSDU_INIB*)((p_cur_cantp_config->p_nsdu_inib_table[(PduId)]).rxtx_inib))

#define GET_CH_FROM_ID(PduId)				(p_cur_cantp_config->p_nsdu_inib_table[(PduId)].ch_no)
#define GET_CH_NUM()						(p_cur_cantp_config->tnum_ch)
#define GET_NSDU_NUM()						(p_cur_cantp_config->tnum_nsdu)
#define GET_PDU_NUM()						(p_cur_cantp_config->tnum_pdu)
#define GET_NSDUID_FROM_PDUID(pduid)		(p_cur_cantp_config->p_pduid_to_nsduid_table[(pduid)])
#define GET_PERIOD()						(p_cur_cantp_config->period)

#define GET_CANFD_DL(len)					(cantp_canfd_dlc_snd_table[len])
#define CHK_CANFD_DL(len)					(cantp_canfd_dlc_rcv_chk_table[len])

/*
 *  DETへ通知するサービスID
 */
#define CanTpServiceId_Init							0x01U
#define CanTpServiceId_GetVersionInfo				0x07U
#define CanTpServiceId_Shutdown						0x02U
#define CanTpServiceId_Transmit						0x03U
#define CanTpServiceId_CancelTransmit				0x08U
#define CanTpServiceId_CancelReceive				0x09U
#define CanTpServiceId_ChangeParameter				0x0aU
#define CanTpServiceId_ReadParameter				0x0bU
#define CanTpServiceId_MainFunction					0x06U
#define CanTpServiceId_RxIndication					0x42U
#define CanTpServiceId_TxConfirmation				0x40U

/* [SWS_CanTp_00002][SWS_CanTp_00296] */
/* [SWS_CanTp_00027][NCanTp_00005][NCanTp_00009] */
/* [SWS_CanTp_00253] CANTP状態はデバッグ用に利用できる */
typedef enum {
	CANTP_UNINIT,
	CANTP_INIT
} CanTp_StatusType;

/* [[NCanTp_00010]] */
typedef uint8 CanTp_ServiceIdType;

/*
 *  受信NSDU管理ブロック
 */
typedef struct rx_nsdu_control_block {
	uint8	stmin;									/* STmin値 */
	uint8	bs;										/* BS値 */
} RX_NSDU_CB;

/*
 *  受信NSDU初期化ブロック
 */
typedef struct rx_initialization_block {
	uint16		CanTpRxWftMax;						/* FC(WAIT)の最大送信数 */
	uint8		CanTpSTmin;							/* STmin値 */
	uint8		CanTpBs;							/* BS値 */
	PduIdType	CanIfId_FcSend;						/* CanIf_TransmitでFC送信時に指定するCanIfのId */
	PduIdType	CanTpId_Indication;					/* CanTp_RxIndicationでSF，FF，CF受信時に指定されるCanTpのId */
	PduIdType	CanTpId_FcConfirmation;				/* CanTp_TxConfirmationでFC送信完了時に指定されるCanTpのId */
	PduIdType	PduRId_Indication;					/* PduR_CanTpRxIndication時に指定するId */
	RX_NSDU_CB	*p_rx_cb;							/* 受信NSDU管理ブロック */
} RX_NSDU_INIB;

/*
 *  送信NSDU初期化ブロック
 */
typedef struct tx_initialization_block {
	PduIdType	CanIfId_Send;						/* CanIf_TransmitでSF，FF，CF送信時に指定するCanIfのId */
	PduIdType	CanTpId_Confirmation;				/* CanTp_TxConfirmationでSF，FF，CF送信完了時に指定されるCanTpのId */
	PduIdType	CanTpId_FcIndication;				/* CanTp_RxIndicationでFC受信時に指定されるCanTpのId */
	PduIdType	PduRId_Confirmation;				/* PduR_CanTpTxConfirmationに指定するId */
} TX_NSDU_INIB;

/*
 *  [SWS_CanTp_00035]NSDU初期化ブロック
 *  (1NSDUにつき1つ作成する)
 */
typedef struct nsdu_initialization_block {
	uint16	ch_no;									/* 所属するチャネル番号 */
	uint8	nsdu_direction;							/* NSDU送受信方向 */
	uint32	CanTpNa;								/* N_Ar／N_Asタイムアウト値 */
	uint32	CanTpNb;								/* N_Br／N_Bsタイムアウト値 */
	uint32	CanTpNc;								/* N_Cr／N_Csタイムアウト値 */
	uint8	CanTpTc;								/* 通信中止の許可／禁止 */
	uint8	CanTpAddressingFormat;					/* アドレスフォーマット */
	uint8	CanTpPaddingActivation;					/* Paddingの使用有無 */
	uint8	CanTpTaType;							/* N-SDUの通信タイプ */
	uint8	CanTpNAe;								/* N_AE */
	uint8	CanTpNSa;								/* N_SA */
	uint8	CanTpNTa;								/* N_TA */
	PduLengthType	sdu_max_sf;						/* 最大SDUデータ長(シングルフレーム) */
			/* CanTpAddressingFormat,CanTpTaType: */
			/* NORMAL,PHYSICAL:				7	*/
			/* NORMAL,FUNCTIONAL:			7	*/
			/* NORMAL,CANFD_PHYSICAL:		CANFD_DL-2(10/14/18/22/30/46/62)	*/
			/* NORMAL,CANFD_FUNCTIONAL:		CANFD_DL-2(10/14/18/22/30/46/62)	*/
			/* EXTENDED,PHYSICAL:			6	*/
			/* EXTENDED,FUNCTIONAL:			6	*/
			/* EXTENDED,CANFD_PHYSICAL:		CANFD_DL-3(9/13/17/21/29/45/61)	*/
			/* EXTENDED,CANFD_FUNCTIONAL:	CANFD_DL-3(9/13/17/21/29/45/61)	*/
			/* NOMALFIXEDはNORMALと同じ			*/
			/* MIXEDはEXTENDEDと同じ			*/
			/* MIXED29BITはEXTENDEDと同じ		*/
	PduLengthType	sdu_max_ff;						/* 最大SDUデータ長(マルチフレーム) */
			/* CanTpAddressingFormat,CanTpTaType: */
			/* NORMAL,PHYSICAL:				0xFFFFFFFF	*/
			/* NORMAL,FUNCTIONAL:			0			*/
			/* NORMAL,CANFD_PHYSICAL:		0xFFFFFFFF	*/
			/* NORMAL,CANFD_FUNCTIONAL:		0			*/
			/* EXTENDED,PHYSICAL:			0xFFFFFFFF	*/
			/* EXTENDED,FUNCTIONAL:			0			*/
			/* EXTENDED,CANFD_PHYSICAL:		0xFFFFFFFF	*/
			/* EXTENDED,CANFD_FUNCTIONAL:	0			*/
			/* NOMALFIXEDはNORMALと同じ			*/
			/* MIXEDはEXTENDEDと同じ			*/
			/* MIXED29BITはEXTENDEDと同じ		*/
	PduLengthType	sdu_max_sf_data;				/* SF最大データ長 */
			/* CanTpAddressingFormat,CanTpTaType: */
			/* NORMAL,PHYSICAL:				7	*/
			/* NORMAL,FUNCTIONAL:			7	*/
			/* NORMAL,CANFD_PHYSICAL:		CANFD_DL-2(10/14/18/22/30/46/62)	*/
			/* NORMAL,CANFD_FUNCTIONAL:		CANFD_DL-2(10/14/18/22/30/46/62)	*/
			/* EXTENDED,PHYSICAL:			6	*/
			/* EXTENDED,FUNCTIONAL:			6	*/
			/* EXTENDED,CANFD_PHYSICAL:		CANFD_DL-3(9/13/17/21/29/45/61)	*/
			/* EXTENDED,CANFD_FUNCTIONAL:	CANFD_DL-3(9/13/17/21/29/45/61)	*/
			/* NOMALFIXEDはNORMALと同じ			*/
			/* MIXEDはEXTENDEDと同じ			*/
			/* MIXED29BITはEXTENDEDと同じ		*/
	PduLengthType	sdu_max_ff_data;				/* FF最大データ長 */
			/* CanTpAddressingFormat,CanTpTaType: */
			/* NORMAL,PHYSICAL:				6		*/
			/* NORMAL,FUNCTIONAL:			0		*/
			/* NORMAL,CANFD_PHYSICAL:		CANFD_DL-2(10/14/18/22/30/46/62)	*/
			/* NORMAL,CANFD_FUNCTIONAL:		0		*/
			/* EXTENDED,PHYSICAL:			5		*/
			/* EXTENDED,FUNCTIONAL:			0		*/
			/* EXTENDED,CANFD_PHYSICAL:		CANFD_DL-3(9/13/17/21/29/45/61)	*/
			/* EXTENDED,CANFD_FUNCTIONAL:	0		*/
			/* NOMALFIXEDはNORMALと同じ				*/
			/* MIXEDはEXTENDEDと同じ				*/
			/* MIXED29BITはEXTENDEDと同じ			*/
	PduLengthType	sdu_max_cf_data;				/* CF最大データ長 */
			/* CanTpAddressingFormat,CanTpTaType: */
			/* NORMAL,PHYSICAL:				7	*/
			/* NORMAL,FUNCTIONAL:			0	*/
			/* NORMAL,CANFD_PHYSICAL:		CANFD_DL-1(11/15/19/23/31/45/63)	*/
			/* NORMAL,CANFD_FUNCTIONAL:		0	*/
			/* EXTENDED,PHYSICAL:			6	*/
			/* EXTENDED,FUNCTIONAL:			0	*/
			/* EXTENDED,CANFD_PHYSICAL:		CANFD_DL-2(10/14/18/22/30/46/62)	*/
			/* EXTENDED,CANFD_FUNCTIONAL:	0	*/
			/* NOMALFIXEDはNORMALと同じ			*/
			/* MIXEDはEXTENDEDと同じ			*/
			/* MIXED29BITはEXTENDEDと同じ		*/
	const void		*rxtx_inib;						/* 送受信別NSDU初期化ブロック */
} NSDU_INIB;

/*
 *  チャネル受信管理ブロック
 */
typedef struct rx_control_block {
	PduIdType		id;								/* 現在受信中ID */
	uint8			rx_status;						/* 受信状態 */
	uint8			rx_time;						/* 受信タイムアウトカウント状態（停止/N_Ar/N_Br/N_Cr） */
	uint32			rx_time_cnt;					/* タイムアウトカウンタ */
	PduLengthType	sdu_len;						/* SDUのデータ長 */
	PduLengthType	data_len;						/* 残りの受信データ長 */
	uint8			cf_sn;							/* CFで次に受信するシーケンスナンバー */
	uint8			fc_fs;							/* FCで送信したFS */
	uint8			fc_bs;							/* FCで送信したBS */
	uint8			fc_stmin;						/* FCで送信したSTmin */
	uint8			bs_cnt;							/* 受信CFカウンタ */
	uint8			wft_cnt;						/* 送信FC(WAIT)カウンタ */
} CH_RX_CB;

/*
 *  チャネル送信管理ブロック
 */
typedef struct tx_control_block {
	PduIdType		id;								/* 現在送信中ID */
	uint8			tx_status;						/* 送信状態 */
	uint8			tx_time;						/* 送信タイムアウトカウント状態（停止/N_As/N_Bs/N_Cs） */
	uint32			tx_time_cnt;					/* タイムアウトカウンタ */
	PduLengthType	sdu_len;						/* SDUのデータ長 */
	PduLengthType	data_len;						/* 残りの送信データ長 */
	uint8			cf_sn;							/* CFで次に送信するシーケンスナンバー */
	uint8			fc_fs;							/* FCで受信したFS */
	uint8			fc_bs;							/* FCで受信したBS */
	uint8			fc_stmin;						/* FCで受信したSTmin */
	uint8			fc_cts;							/* FC(CTS)受信済みフラグ */
	uint8			bs_cnt;							/* 送信CFカウンタ */
	uint16			stmin_cnt;						/* STminカウンタ */
} CH_TX_CB;

/*
 *  チャネル初期化管理ブロック
 *  (1チャネルにつき1つ作成する)
 */
/* [SWS_CanTp_00122] */
typedef struct ch_initialization_block {
	uint8			CanTpChannelMode;				/* チャネル通信方式 */
	CH_RX_CB		*p_ch_rx_cb;					/* チャネル受信管理ブロック */
	CH_TX_CB		*p_ch_tx_cb;					/* チャネル送信管理ブロック */
} CH_INIB;


/*
 *  [SWS_CanTp_00340]
 *  CanTpコンフィギュレーション管理ブロック
 *  (1コンフィギュレーションにつき1つ作成する)
 */
typedef struct cantp_config_type {
	uint16			tnum_ch;						/* チャネル数 */
	const CH_INIB	*p_ch_inib_table;				/* CH初期化ブロック配列 */
	uint16			tnum_nsdu;						/* NSDU数 */
	const NSDU_INIB	*p_nsdu_inib_table;				/* NSDU初期化ブロック配列 */
	uint16			tnum_pdu;						/* PDU数 */
	const PduIdType	*p_pduid_to_nsduid_table;		/* ID引き当てテーブル */
	uint8			period;							/* 周期 */
} CanTp_ConfigType;


/* CANフレームフォーマット */
/* Normal addressing format */
/* Normal fixed addressing format */
typedef union {
	/* 共通 */
	struct {
		uint8 			n_pci;							/* xxxx xxxxb */
														/* xxxx       : N_PCI		*/
														/*      xxxx  : reserve		*/
	} Common;
	/* SF */
	struct {
		uint8 			n_pci;							/* 0000 xxxxb */
														/* 0000       : SF			*/
														/*      xxxx  : SF_DL		*/
		uint8			data[1];						/* データ先頭 */
	} Sf_8Max;
	struct {
		uint8 			n_pci;							/* 0000 0000b */
														/* 0000       : SF			*/
														/*      0000  : reserve		*/
		uint8			sf_dl;							/* SF_DL */
		uint8			data[1];						/* データ先頭 */
	} Sf_8Over;
	/* FF */
	struct {
		uint8 			n_pci;							/* 0001 xxxxb */
														/* 0001       : FF			*/
														/*      xxxx  : FF_DL		*/
		uint8 			ff_dl_l;						/* FF_DL */
		uint8			data[1];						/* データ先頭 */
	} Ff_4095Max;
	struct {
		uint8 			n_pci;							/* 0001 0000b */
														/* 0001       : FF			*/
														/*      0000  : reserve		*/
		uint8 			reserve;						/* 0000 0000b */
		uint8 			ff_dl_hh;						/* FF_DL */
		uint8 			ff_dl_hl;						/* FF_DL */
		uint8 			ff_dl_lh;						/* FF_DL */
		uint8 			ff_dl_ll;						/* FF_DL */
		uint8			data[1];						/* データ先頭 */
	} Ff_4095Over;
	/* CF */
	struct {
		uint8 			n_pci;							/* 0010 0000b */
														/* 0010       : CF			*/
														/*      xxxx  : SN			*/
		uint8			data[1];						/* データ先頭 */
	} Cf;
	/* FC */
	struct {
		uint8 			n_pci;							/* 0011 0000b */
														/* 0011       : FC			*/
														/*      xxxx  : FS			*/
		uint8 			bs;								/* BS */
		uint8 			stmin;							/* STmin */
		uint8			data[1];						/* 未使用 */
	} Fc;
} CanTp_Frame_Normal;


/*
 *  [NCanTp_00001] CanTpコンフィギュレーション情報(CanTp_PBcfg.c)
 */
extern const CanTp_ConfigType	cantp_config[];

/*
 *  CanTpシステムサービスプロトタイプ宣言
 */
extern void CanTp_Init(const CanTp_ConfigType* CfgPtr) ;
/* [ECUC_CanTp_00283] */
#if CANTP_VERSION_INFO_API == STD_ON
extern void CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif /* CANTP_VERSION_INFO_API == STD_ON */
extern void CanTp_Shutdown(void);
extern Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* CanTpTxInfoPtr);
extern Std_ReturnType CanTp_CancelTransmit(PduIdType CanTpTxSduId);
extern Std_ReturnType CanTp_CancelReceive (PduIdType CanTpRxSduId);
#if CANTP_CHANGE_PARAMETER_API == STD_ON
extern Std_ReturnType CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);
#endif /* CANTP_CHANGE_PARAMETER_API == STD_ON */
#if CANTP_READ_PARAMETER_API == STD_ON
extern Std_ReturnType CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16* value);
#endif /* CANTP_READ_PARAMETER_API == STD_ON */
extern void CanTp_MainFunction(void);


/*
 *  対応しない仕様タグ一覧
 *  - 動的ID
 *    <SWS_CanTp_00330><SWS_CanTp_00331><SWS_CanTp_00332><SWS_CanTp_00333>
 *    <SWS_CanTp_00334><SWS_CanTp_00335><SWS_CanTp_00336><SWS_CanTp_00337>
 *    <SWS_CanTp_00338>
 *  - １つのNSDUからのみ参照可能とする
 *    <SWS_CanTp_00248><SWS_CanTp_00328>
 *  - production errorなしのため対象外
 *    <SWS_CanTp_00291>
 *  - 要求仕様ではない
 *    <SWS_CanTp_00327>
 */

#endif /* CANTP_H */
