/*
 *  TOPPERS/A-COM
 *      Automotive COM
 *
 *  Copyright (C) 2013-2015 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2013-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2014-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2013-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2015 by Witz Corporation
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
 *  $Id: Com.h 1245 2015-03-25 09:25:18Z panasonic-ayane $
 */

/* [COM005] Com.h */

/*
 *  開発方針
 *  - [COM746] Com.hをincludeするだけで全てのデータ型を使用可能とする
 *  - [COM747] 定義したデータ型のサイズをsizeofで取得可能とする
 *  - [COM748] デバッグするための変数にはそれぞれ説明を書く
 *  - [COM786] 標準化されたパラメータは本ヘッダファイルで他のBSWに提供可能とする
 */

#ifndef COM_H
#define COM_H

/* [COM220][COM609] */
#include "ComStack_Types.h"
#include "Com_Cfg.h"


#define COM_E_PARAM									0x01U       /* [COM442][COM707] */
#define COM_E_UNINIT								0x02U       /* [COM442][COM707] */
#define COM_E_PARAM_POINTER							0x03U       /* [COM442][COM707] */
#define COM_MODULE_ID								0x32U       /* [COM442] */
#define COM_SERVICE_NOT_AVAILABLE					0x80U       /* [COM459] */
#define COM_BUSY									0x81U       /* [COM459] */
#define COM_INVALID_UINT8							(uint8) 0xFF
#define COM_INVALID_UINT16							(uint16) 0xFFFF
#define COM_INVALID_UINT32							(uint32) 0xFFFFFFFF

#define COM_ALWAYS									0x01U
#define COM_MASKED_NEW_DIFFERS_MASKED_OLD			0x02U
#define COM_MASKED_NEW_DIFFERS_X					0x03U
#define COM_MASKED_NEW_EQUALS_X						0x04U
#define COM_NEVER									0x05U
#define COM_NEW_IS_OUTSIDE							0x06U
#define COM_NEW_IS_WITHIN							0x07U
#define COM_ONE_EVERY_N								0x08U

#define COM_SEND									0x09U
#define COM_RECEIVE									0x0AU

#define COM_DEFERRED								0x0BU
#define COM_IMMEDIATE								0x0CU

#define COM_CONFIRMATION							0x0DU
#define COM_TRANSMIT								0x0EU
#define COM_TRIGGER_TRANSMIT						0x0FU

#define COM_NOTIFY									0x10U
#define COM_REPLACE									0x11U
#define COM_NONE									0x12U

#define COM_BIG_ENDIAN								0x13U
#define COM_LITTLE_ENDIAN							0x14U
#define COM_OPAQUE									0x15U

#define COM_BOOLEAN									0x16U
#define COM_UINT8									0x17U
#define COM_UINT16									0x18U
#define COM_UINT32									0x19U
#define COM_SINT8									0x1AU
#define COM_SINT16									0x1BU
#define COM_SINT32									0x1CU
#define COM_UINT8_N									0x1DU
#define COM_UINT8_DYN								0x1EU
#define COM_FLOAT32									0x1FU
#define COM_FLOAT64									0x20U

#define COM_PENDING									0x21U
#define COM_TRIGGERED								0x22U
#define COM_TRIGGERED_ON_CHANGE						0x23U
#define COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION	0x24U
#define COM_TRIGGERED_WITHOUT_REPETITION			0x25U

#define COM_DIRECT									0x26U
#define COM_PERIODIC								0x27U
#define COM_MIXED									0x28U

#define COM_NORMAL									0x29U
#define COM_TP										0x2AU

#define COM_START									0x2BU
#define COM_STOP									0x2CU
#define COM_WAIT									0x2DU

/* IPDUグループの状態を格納する配列サイズ */
#define IPDU_GROUP_VECTOR_NUM	(((COM_SUPPORTED_IPDU_GROUPS - 1U) / 8U) + 1U)

/* IPDU状態操作マクロ */
#define IPDU_STARTED_BIT						0x01U       /* IPDUが開始されているかどうか */
#define IPDU_NOTICED_BIT						0x02U       /* DEFERREDのIPDUの受信(送信完了)通知がきたかどうか */
#define IPDU_DIRECT_SEND_BIT					0x04U       /* DIRECT送信中かどうか */
#define IPDU_FIRST_DIRECT_SEND_BIT				0x08U       /* 初回のDIRECT送信であるかどうか */
#define IPDU_RETRY_BIT							0x10U       /* リトライ状態かどうか */
#define IPDU_MDT_WAIT_BIT						0x20U       /* MDT待ち状態かどうか */
#define IPDU_DM_BIT								0x40U       /* DMが開始されているかどうか */
#define IPDU_TRIGGERED_BIT						0x80U       /* Com_TriggerIPDUSendが呼ばれたかどうか */
#define IPDU_IS_STARTED(state)					(((*(state)) & IPDU_STARTED_BIT) != 0U)
#define IPDU_IS_NOTICED(state)					(((*(state)) & IPDU_NOTICED_BIT) != 0U)
#define IPDU_IS_DIRECT_SEND(state)				(((*(state)) & IPDU_DIRECT_SEND_BIT) != 0U)
#define IPDU_IS_FIRST_DIRECT_SEND(state)		(((*(state)) & IPDU_FIRST_DIRECT_SEND_BIT) != 0U)
#define IPDU_IS_RETRY(state)					(((*(state)) & IPDU_RETRY_BIT) != 0U)
#define IPDU_IS_MDT_WAIT(state)					(((*(state)) & IPDU_MDT_WAIT_BIT) != 0U)
#define IPDU_IS_DM(state)						(((*(state)) & IPDU_DM_BIT) != 0U)
#define IPDU_IS_TRIGGERED(state)				(((*(state)) & IPDU_TRIGGERED_BIT) != 0U)
#define IPDU_SET_STARTED(state)					((*(state)) |= IPDU_STARTED_BIT)
#define IPDU_SET_NOTICED(state)					((*(state)) |= IPDU_NOTICED_BIT)
#define IPDU_SET_DIRECT_SEND(state)				((*(state)) |= IPDU_DIRECT_SEND_BIT)
#define IPDU_SET_FIRST_DIRECT_SEND(state)		((*(state)) |= IPDU_FIRST_DIRECT_SEND_BIT)
#define IPDU_SET_RETRY(state)					((*(state)) |= IPDU_RETRY_BIT)
#define IPDU_SET_MDT_WAIT(state)				((*(state)) |= IPDU_MDT_WAIT_BIT)
#define IPDU_SET_DM(state)						((*(state)) |= IPDU_DM_BIT)
#define IPDU_SET_TRIGGERED(state)				((*(state)) |= IPDU_TRIGGERED_BIT)
#define IPDU_CLEAR_STARTED(state)				((*(state)) &= (uint8) (~IPDU_STARTED_BIT))
#define IPDU_CLEAR_NOTICED(state)				((*(state)) &= (uint8) (~IPDU_NOTICED_BIT))
#define IPDU_CLEAR_DIRECT_SEND(state)			((*(state)) &= (uint8) (~IPDU_DIRECT_SEND_BIT))
#define IPDU_CLEAR_FIRST_DIRECT_SEND(state)		((*(state)) &= (uint8) (~IPDU_FIRST_DIRECT_SEND_BIT))
#define IPDU_CLEAR_RETRY(state)					((*(state)) &= (uint8) (~IPDU_RETRY_BIT))
#define IPDU_CLEAR_MDT_WAIT(state)				((*(state)) &= (uint8) (~IPDU_MDT_WAIT_BIT))
#define IPDU_CLEAR_DM(state)					((*(state)) &= (uint8) (~IPDU_DM_BIT))
#define IPDU_CLEAR_TRIGGERED(state)				((*(state)) &= (uint8) (~IPDU_TRIGGERED_BIT))
#define IPDU_CLEAR_ALL(state)					((*(state)) = 0x00U)
#define IPDU_CLEAR_EXCEPT_STARTED(state)		((*(state)) &= IPDU_STARTED_BIT)

/*
 *  チェックマクロ
 *  [COM024] DETエラーがOFFの場合，パラメータチェックはしない
 *  [COM442] Det_ReportErrorの第2引数(InstanceId)は0とする
 */
#if (COM_DEV_ERROR_DETECT == STD_ON) && !defined(OMIT_COM_DEBUG)

#define COM_CHECK_UNINITIALIZED(ApiId)										 \
	do {																	 \
		if (com_state != COM_UNINIT) {										 \
			(void) Det_ReportError(COM_MODULE_ID, 0U, (ApiId), COM_E_PARAM); \
			goto error_exit;												 \
		}																	 \
	} while (0)

#define COM_CHECK_INITIALIZED(ApiId)										  \
	do {																	  \
		if (com_state != COM_INIT) {										  \
			(void) Det_ReportError(COM_MODULE_ID, 0U, (ApiId), COM_E_UNINIT); \
			goto error_exit;												  \
		}																	  \
	} while (0)

#define COM_CHECK_INITIALIZED_ERCD(ApiId)									  \
	do {																	  \
		if (com_state != COM_INIT) {										  \
			ercd = COM_SERVICE_NOT_AVAILABLE;								  \
			(void) Det_ReportError(COM_MODULE_ID, 0U, (ApiId), COM_E_UNINIT); \
			goto error_exit;												  \
		}																	  \
	} while (0)

#define COM_CHECK_PARAM(exp, ApiId)											 \
	do {																	 \
		if (!(exp)) {														 \
			(void) Det_ReportError(COM_MODULE_ID, 0U, (ApiId), COM_E_PARAM); \
			goto error_exit;												 \
		}																	 \
	} while (0)

#define COM_CHECK_PARAM_ERCD(exp, ApiId)									 \
	do {																	 \
		if (!(exp)) {														 \
			ercd = COM_SERVICE_NOT_AVAILABLE;								 \
			(void) Det_ReportError(COM_MODULE_ID, 0U, (ApiId), COM_E_PARAM); \
			goto error_exit;												 \
		}																	 \
	} while (0)

#define COM_CHECK_NULL_POINTER(exp, ApiId)											 \
	do {																			 \
		if (!(exp)) {																 \
			(void) Det_ReportError(COM_MODULE_ID, 0U, (ApiId), COM_E_PARAM_POINTER); \
			goto error_exit;														 \
		}																			 \
	} while (0)

#define COM_CHECK_NULL_POINTER_ERCD(exp, ApiId)										 \
	do {																			 \
		if (!(exp)) {																 \
			ercd = COM_SERVICE_NOT_AVAILABLE;										 \
			(void) Det_ReportError(COM_MODULE_ID, 0U, (ApiId), COM_E_PARAM_POINTER); \
			goto error_exit;														 \
		}																			 \
	} while (0)

#else /* (COM_DEV_ERROR_DETECT == STD_OFF) || defined(OMIT_COM_DEBUG) */

#define COM_CHECK_UNINITIALIZED(ApiId)
#define COM_CHECK_INITIALIZED(ApiId)
#define COM_CHECK_INITIALIZED_ERCD(ApiId)
#define COM_CHECK_PARAM(exp, ApiId)
#define COM_CHECK_PARAM_ERCD(exp, ApiId)
#define COM_CHECK_NULL_POINTER(exp, ApiId)
#define COM_CHECK_NULL_POINTER_ERCD(exp, ApiId)

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) && !defined(OMIT_COM_DEBUG) */

/*
 *  AUTOSARリリースバージョン
 */
#define COM_AR_RELEASE_MAJOR_VERSION	4U
#define COM_AR_RELEASE_MINOR_VERSION	0U
#define COM_AR_RELEASE_PATCH_VERSION	3U

/*
 *  サプライヤバージョン情報
 */
#define COM_SW_MAJOR_VERSION	1U
#define COM_SW_MINOR_VERSION	2U
#define COM_SW_PATCH_VERSION	0U
#define COM_VENDOR_ID			65U  /* NCESベンダID */

/*
 *  情報取得マクロ
 */
#define GET_SIGNAL_NUM()			p_cur_com_config->tnum_signal
#define GET_VECTOR_NUM()			p_cur_com_config->tnum_vector
#define GET_IPDU_G_NUM()			p_cur_com_config->tnum_ipdu_g
#define GET_IPDU_NUM()				p_cur_com_config->tnum_ipdu
#define GET_RX_IPDU_NUM()			p_cur_com_config->tnum_rx_ipdu
#define GET_TX_IPDU_NUM()			p_cur_com_config->tnum_tx_ipdu
#define GET_IPDU_INIB(PduId)		pp_cur_all_ipdu_inib[(PduId)]
#define GET_RX_IPDU_INIB(Index)		(&p_cur_rx_ipdu_inib[(Index)])
#define GET_TX_IPDU_INIB(Index)		(&p_cur_tx_ipdu_inib[(Index)])
#define GET_SIGNAL_INIB(SignalId)	(&p_cur_signal_inib[(SignalId)])

/*
 *  [COM442] DETへ通知するサービスID
 */
#define COMServiceId_Init							0x01U
#define COMServiceId_DeInit							0x02U
#define COMServiceId_IpduGroupControl				0x03U
#define COMServiceId_ReceptionDMControl				0x06U
#define COMServiceId_GetStatus						0x07U
#define COMServiceId_GetConfigurationId				0x08U
#define COMServiceId_GetVersionInfo					0x09U
#define COMServiceId_SendSignal						0x0AU
#define COMServiceId_ReceiveSignal					0x0BU
#define COMServiceId_SendSignalGroup				0x0DU
#define COMServiceId_ReceiveSignalGroup				0x0EU
#define COMServiceId_InvalidateSignal				0x10U
#define COMServiceId_TriggerIPDUSend				0x17U
#define COMServiceId_MainFunctionRx					0x18U
#define COMServiceId_MainFunctionTx					0x19U
#define COMServiceId_MainFunctionRouteSignals		0x1AU
#define COMServiceId_InvalidateSignalGroup			0x1BU
#define COMServiceId_ClearIpduGroupVector			0x1CU
#define COMServiceId_SetIpduGroup					0x1DU
#define COMServiceId_TpRxIndication					0x1EU
#define COMServiceId_SendDynSignal					0x21U
#define COMServiceId_ReceiveDynSignal				0x22U
#define COMServiceId_CopyRxData						0x23U
#define COMServiceId_CopyTxData						0x24U
#define COMServiceId_StartOfReception				0x25U
#define COMServiceId_TpTxConfirmation				0x26U
#define COMServiceId_SwitchIpduTxMode				0x27U
#define COMServiceId_TxConfirmation					0x40U
#define COMServiceId_TriggerTransmit				0x41U
#define COMServiceId_RxIndication					0x42U
#define COMServiceId_set_signal_for_send			0x51U
#define COMServiceId_set_signal_for_receive			0x52U
#define COMServiceId_get_signal						0x53U
#define COMServiceId_set_filter_buffer				0x54U
#define COMServiceId_packing						0x55U
#define COMServiceId_pack_little_endian				0x56U
#define COMServiceId_pack_big_endian				0x57U
#define COMServiceId_ipdu_receive					0x58U
#define COMServiceId_unpacking						0x59U
#define COMServiceId_set_updatebit					0x5AU
#define COMServiceId_clear_updatebit				0x5BU
#define COMServiceId_mdt_send						0x5CU
#define COMServiceId_mdt_countdown					0x5DU
#define COMServiceId_mdt_set						0x5EU
#define COMServiceId_changed_signal					0x5FU
#define COMServiceId_filtering						0x60U
#define COMServiceId_check_tms						0x61U
#define COMServiceId_copy_signal_to_uint32			0x62U
#define COMServiceId_cast_signal_to_sint32			0x63U
#define COMServiceId_invalid_action					0x64U
#define COMServiceId_start_tx_dm					0x65U
#define COMServiceId_start_rx_dm					0x66U
#define COMServiceId_check_signal_dm				0x67U
#define COMServiceId_reset_signal_dm				0x68U
#define COMServiceId_check_updatebit				0x69U
#define COMServiceId_ipdu_initialize				0x6DU
#define COMServiceId_set_tx_mode					0x6EU
#define COMServiceId_switch_tx_mode					0x6FU
#define COMServiceId_clear_occurrence				0x70U
#define COMServiceId_ipdu_send						0x71U
#define COMServiceId_stop_rx_dm						0x72U


typedef uint16	Com_SignalIdType;
typedef uint16	Com_SignalGroupIdType;
typedef uint16	Com_IpduGroupIdType;
typedef uint8	Com_IpduGroupVector[IPDU_GROUP_VECTOR_NUM];

typedef void (*Com_CbkTxAck)(void);     /* [COM468] */
typedef void (*Com_CbkTxErr)(void);     /* [COM491] */
typedef void (*Com_CbkTxTOut)(void);    /* [COM554] */
typedef void (*Com_CbkRxAck)(void);     /* [COM555] */
typedef void (*Com_CbkRxTOut)(void);    /* [COM556] */
typedef void (*Com_CbkInv)(void);       /* [COM536] */
typedef void (*Com_CbkAck)(void);       /* Com_CbkTxAck, Com_CbkRxAck */
typedef void (*Com_CbkTOut)(void);      /* Com_CbkTxTOut, Com_CbkRxTOut */

typedef boolean (*Com_RxIpduCallout)(PduIdType Id, uint8 *IpduData);    /* [COM700] */
typedef boolean (*Com_TxIpduCallout)(PduIdType Id, uint8 *IpduData);    /* [COM346] */
typedef boolean (*Com_IpduCallout)(PduIdType Id, uint8 *IpduData);      /* Com_RxIpduCallout, Com_TxIpduCallout */

typedef enum {
	COM_UNINIT,
	COM_INIT
} Com_StatusType;

typedef uint8 Com_ServiceIdType;

/*
 *  フィルタ初期化ブロック: UINT系のCOM_MASKED_NEW_DIFFERS_X/COM_MASKED_NEW_EQUALS_X用
 */
typedef struct filter_uint_masked_initialization_block {
	uint32	ComFilterMask;
	uint32	ComFilterX;
} FILTER_UINT_MASKED_INIB;

/*
 *  フィルタ初期化ブロック: SINT系のCOM_MASKED_NEW_DIFFERS_X/COM_MASKED_NEW_EQUALS_X用
 */
typedef struct filter_sint_masked_initialization_block {
	sint32	ComFilterMask;
	sint32	ComFilterX;
} FILTER_SINT_MASKED_INIB;

/*
 *  フィルタ初期化ブロック: UINT系のCOM_MASKED_NEW_DIFFERS_MASKED_OLD用
 */
typedef struct filter_uint_masked_old_initialization_block {
	uint32	ComFilterMask;
	void	*p_filter_buffer;
} FILTER_UINT_MASKED_OLD_INIB;

/*
 *  フィルタ初期化ブロック: SINT系のCOM_MASKED_NEW_DIFFERS_MASKED_OLD用
 */
typedef struct filter_sint_masked_old_initialization_block {
	sint32	ComFilterMask;
	void	*p_filter_buffer;
} FILTER_SINT_MASKED_OLD_INIB;

/*
 *  フィルタ初期化ブロック: UINT系のCOM_NEW_IS_OUTSIDE/COM_NEW_IS_WITHIN用
 */
typedef struct filter_uint_new_is_initialization_block {
	uint32	ComFilterMax;
	uint32	ComFilterMin;
} FILTER_UINT_NEW_IS_INIB;

/*
 *  フィルタ初期化ブロック: SINT系のCOM_NEW_IS_OUTSIDE/COM_NEW_IS_WITHIN用
 */
typedef struct filter_sint_new_is_initialization_block {
	sint32	ComFilterMax;
	sint32	ComFilterMin;
} FILTER_SINT_NEW_IS_INIB;

/*
 *  フィルタ初期化ブロック: COM_ONE_EVERY_N用
 */
typedef struct filter_one_every_n_initialization_block {
	uint32	ComFilterOffset;
	uint32	ComFilterPeriod;
	uint32	*p_occur;
} FILTER_ONE_EVERY_N_INIB;

/*
 *  受信シグナル管理ブロック
 */
typedef struct rx_signal_control_block {
	uint32	dm_mf_cnt;  /* DMのMF回数カウンタ[デッドラインモニタリング時間] */
	uint8	dm_state;   /* START:DM監視する，STOP:DM監視しない．WAIT:初回受信までDM監視しない */
} RX_SIGNAL_CB;

/*
 *  送信シグナル管理ブロック
 */
typedef struct tx_signal_control_block {
	boolean	tmc;    /* TMC */
} TX_SIGNAL_CB;

/*
 * 送信モード初期化ブロック
 */
typedef struct tx_mode_initialization_block {
	uint8	ComTxModeMode;                  /* 必須 */
	uint8	ComTxModeNumberOfRepetitions;   /* 未設定の場合，0 */
	uint32	ComTxModeRepetitionPeriod;      /* 未設定の場合，0 */
	uint32	ComTxModeTimeOffset;            /* 未設定の場合，0 */
	uint32	ComTxModeTimePeriod;            /* 未設定の場合，0 */
} TX_MODE_INIB;

/*
 * 送信IPDU初期化ブロック
 */
typedef struct tx_ipdu_initialization_block {
	uint8				ComTxIPduClearUpdateBit;        /* 未設定の場合，COM_INVALID_UINT8 */
	uint8				ComTxIPduUnusedAreasDefault;    /* 必須 */
	uint32				ComMinimumDelayTime;            /* 未設定の場合，0 */
	const TX_MODE_INIB	*p_tx_mode_true_inib;           /* 必須 */
	const TX_MODE_INIB	*p_tx_mode_false_inib;          /* 未設定の場合，NULL_PTR */
} TX_IPDU_INIB;

/*
 *  IPDU初期化ブロック
 */
typedef struct ipdu_initialization_block {
	uint8				ComIPduDirection;               /* 必須 */
	uint8				ComIPduSignalProcessing;        /* 必須 */
	uint8				ComIPduType;                    /* 必須 */
	boolean				ComIPduCancellationSupport;     /* 未設定の場合，FALSE */
	const TX_IPDU_INIB	*p_tx_ipdu_inib;                /* 送信の場合，必須，受信の場合，NULL_PTR */
	Com_IpduCallout		ComIPduCallout;                 /* 未設定の場合，NULL_PTR */
	PduIdType			PduRSourcePduHandleId;          /* 必須 */
	PduLengthType		PduLength;                      /* 必須 */

	const Com_SignalIdType		*p_signalid_list;       /* IPDUに所属するシグナルIDリスト  */
	const Com_IpduGroupVector	*p_ipdu_group_vector;   /* IPDUが所属するIPDUグループベクタ(所属するグループのビットのみON) */
	void						*p_ipdu_cb;             /* IPDU管理ブロック */
	uint8						*p_ipdu_buffer;         /* IPDUバッファ */
	uint8						*p_state;               /* IPDU状態(0bit:開始状態，1bit:バッファ更新状態) */
	uint16						tnum_signal;            /* IPDUに所属するシグナル数 */
} IPDU_INIB;                                                      /* IPDU_INIB */

/*
 *  送信IPDU管理ブロック
 */
typedef struct tx_ipdu_control_block {
	uint32				interval_mf_cnt;        /* 送信する間のMF回数カウンタ[DIRECT時のNの間隔] */
	uint32				period_mf_cnt;          /* 周期のMF回数カウンタ[PERIODIC時の送信周期] */
	uint32				mdt_mf_cnt;             /* MDTのMF回数カウンタ[最小遅延時間] */
	uint32				dm_mf_cnt;              /* DMのMF回数カウンタ[デッドラインモニタリング時間] */
	uint8				repeat_cnt;             /* 繰り返し回数カウンタ[DIRECT時のN] */
	uint8				queuing_cnt;            /* 送信完了した回数 */
	const TX_MODE_INIB	*p_cur_tx_mode_inib;    /* 現在の送信モード初期化ブロックへのポインタ */
} TX_IPDU_CB;

/*
 *  シグナル初期化ブロック
 */
typedef struct signal_initialization_block {
	uint8			ComBitSize;                         /* UINT8_Nの場合，COM_INVALID_UINT8 */
	uint8			ComDataInvalidAction;               /* 未設定の場合，COM_INVALID_UINT8 */
	uint8			ComRxDataTimeoutAction;             /* 未設定の場合，COM_INVALID_UINT8 */
	uint8			ComSignalEndianness;                /* 必須 */
	uint8			ComSignalType;                      /* 必須 */
	uint8			ComTransferProperty;                /* 送信の場合，必須．受信の場合，COM_INVALID_UINT8 */
	uint16			ComBitPositionLsb;                  /* 必須 */
	uint16			ComSignalLength;                    /* UINT8_N以外の場合，COM_INVALID_UINT16 */
	uint16			ComUpdateBitPosition;               /* 未設定の場合，COM_INVALID_UINT16 */
	uint32			ComFirstTimeout;                    /* 未設定の場合，0 */
	uint32			ComTimeout;                         /* 未設定の場合，0 */
	Com_CbkTxErr	ComErrorNotification;               /* 未設定の場合，NULL_PTR */
	Com_CbkInv		ComInvalidNotification;             /* 未設定の場合，NULL_PTR */
	Com_CbkAck		ComNotification;                    /* 未設定の場合，NULL_PTR */
	Com_CbkTOut		ComTimeoutNotification;             /* 未設定の場合，NULL_PTR */
	const void		*ComSignalDataInvalidValue;         /* 未設定の場合，NULL_PTR */
	const void		*ComSignalInitValue;                /* 必須(デフォルト0) */
	const IPDU_INIB	*p_ipdu_inib;                       /* 所属するIPDU初期化ブロック */
	uint8			ComFilterAlgorithm;                 /* フィルタなしの場合，COM_INVALID_UINT8 */
	/*
	 *  フィルタ初期化ブロック
	 *  フィルタなしの場合，NULL_PTR
	 *  フィルタアルゴリズムがCOM_ALWAYS，COM_NEVERの場合，NULL_PTR
	 */
	const void *p_filter_inib;
	/*
	 *  シグナル管理ブロック
	 *  受信の場合，受信DMがなければ，NULL_PTR
	 *  送信の場合，フィルタがなければ，NULL_PTR
	 */
	void *p_signal_cb;
	/*
	 *  シグナルバッファ
	 *  受信の場合，必須
	 *  送信の場合，TRIGGERED_ON_CHANGE，TRIGGERED_ON_CHANGE_WITHOUT_REPETITION以外は，NULL_PTR
	 */
	void *p_signal_buffer;
} SIGNAL_INIB;

/*
 *  Comコンフィギュレーション管理ブロック
 *  (1コンフィギュレーションにつき1つ作成する)
 */
typedef struct com_config_type {
	uint32 ComConfigurationId;                  /* 必須 */

	uint16	tnum_signal;                        /* シグナル数 */
	uint16	tnum_ipdu_g;                        /* IPDUグループ数 */

	const SIGNAL_INIB *p_signal_inib_table;     /* シグナル初期化ブロック配列 */

	uint8			tnum_vector;                /* IPDUグループをビットで管理するのに必要なバイト数 */
	uint16			tnum_ipdu;                  /* IPDU数 */
	const IPDU_INIB	* const *pp_ipdu_inib_table;/* IPDU初期化ブロックポインタ配列 */
	uint16			tnum_rx_ipdu;               /* 受信IPDU数 */
	uint16			tnum_tx_ipdu;               /* 送信IPDU数 */
	const IPDU_INIB	*p_rx_ipdu_inib_list;       /* 受信IPDU初期化ブロック配列 */
	const IPDU_INIB	*p_tx_ipdu_inib_list;       /* 送信IPDU初期化ブロック配列 */
} Com_ConfigType;


/*
 *  Comシステムサービスプロトタイプ宣言
 */
extern void Com_Init(const Com_ConfigType *config);
extern void Com_DeInit(void);
extern void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize);
extern void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector);
extern Com_StatusType Com_GetStatus(void);
extern uint32 Com_GetConfigurationId(void);
extern void Com_GetVersionInfo(Std_VersionInfoType *versioninfo);
extern void Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector);
extern void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval);
extern uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr);
extern uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr);
extern uint8 Com_InvalidateSignal(Com_SignalIdType SignalId);
extern void Com_TriggerIPDUSend(PduIdType PduId);
extern void Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode);
extern void Com_RxIndication(PduIdType RxPduId, PduInfoType *PduInfoPtr);
extern void Com_TxConfirmation(PduIdType TxPduId);
extern void Com_MainFunctionRx(void);
extern void Com_MainFunctionTx(void);

/*
 *  Comコンフィギュレーション情報(Com_PBcfg.c)
 */
extern const Com_ConfigType	com_config[];


/*
 *  以下，未サポート機能
 */

#define NTFRSLT_OK						0x00U
#define NTFRSLT_E_NOT_OK				0x01U
#define NTFRSLT_E_TIMEOUT_A				0x02U
#define NTFRSLT_E_TIMEOUT_BS			0x03U
#define NTFRSLT_E_TIMEOUT_CR			0x04U
#define NTFRSLT_E_WRONG_SN				0x05U
#define NTFRSLT_E_INVALID_FS			0x06U
#define NTFRSLT_E_UNEXP_PDU				0x07U
#define NTFRSLT_E_WFT_OVRN				0x08U
#define NTFRSLT_E_NO_BUFFER				0x09U
#define NTFRSLT_E_CANCELATION_OK		0x0AU
#define NTFRSLT_E_CANCELATION_NOT_OK	0x0BU

extern uint8 Com_SendDynSignal(Com_SignalIdType SignalId, const void *SignalDataPtr, uint16 Length);
extern uint8 Com_ReceiveDynSignal(Com_SignalIdType SignalId, void *SignalDataPtr, uint16 *Length);
extern uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId);
extern uint8 Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId);
extern uint8 Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId);
extern void Com_MainFunctionRouteSignals(void);
extern Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr);
extern void Com_TpRxIndication(PduIdType PduId, NotifResultType Result);
extern void Com_TpTxConfirmation(PduIdType PduId, NotifResultType Result);
extern BufReq_ReturnType Com_StartOfReception(PduIdType ComRxPduId, PduLengthType TpSduLength, PduLengthType *RxBufferSizePtr);
extern BufReq_ReturnType Com_CopyRxData(PduIdType PduId, const PduInfoType *PduInfoPtr, PduLengthType *RxBufferSizePtr);
extern BufReq_ReturnType Com_CopyTxData(PduIdType PduId, PduInfoType *PduInfoPtr, RetryInfoType *RetryInfoPtr, PduLengthType *TxDataCntPtr);

/*
 *  ボディ制御系プロファイル以外のために対応しない仕様タグ一覧
 *  (同一仕様タグがボディ制御系プロファイルの要求仕様でも使用されているものは[]で表記)
 *  - シグナルゲートウェイ
 *    <COM370><COM377>[COM324][COM067]<COM359><COM466><COM539><COM384><COM386><COM598>
 *    <COM357><COM360><COM361><COM383><COM735><COM362><COM701><COM702><COM703><COM704>
 *    <COM705><COM706>
 *  - データシーケンス
 *    <COM687><COM688><COM587><COM588><COM590><COM726><COM727>
 *  - 通信保護
 *    <COM596><COM597>
 *  - シグナルグループ
 *    <COM682><COM683><COM737><COM718>[COM500]<COM393><COM513><COM053><COM484><COM050>
 *    <COM051><COM061><COM741><COM769><COM742><COM743><COM770><COM326><COM365><COM575>
 *  - 大型データ
 *    <COM713><COM714><COM662><COM759><COM760><COM720>
 *  - 動的データ
 *    <COM753><COM754><COM755><COM756><COM757><COM758>
 *  - フィルタリング
 *    <COM327>
 */

/*
 *  その他の仕様説明
 *    [COM780][COM781] 本実装ではCom_TriggerIPDUSend, Com_SendSignal内で即時送信しないため対処不要
 *    <COM696><COM697> Com_TriggerTransmit未サポートのため，対処不要
 */

#endif /* COM_H */
