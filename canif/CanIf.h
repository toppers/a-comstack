/*
 *  TOPPERS/A-CANIF
 *      Automotive CANIF
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
 *  $Id: CanIf.h 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

/* [CANIF116] CanIf.h */

/*
 *  開発方針
 *  - [CANIF565] Debuggingでアクセス可能な各変数はグローバル変数で定義する
 *  - [CANIF566] CanIf.hをincludeするだけで全てのデータ型を使用可能とする
 *  - [CANIF567] 定義したデータ型のサイズをsizeofで取得可能とする
 *  - [CANIF568] デバッグするための変数にはそれぞれ説明を書く
 *  - [CANIF672] CanIf.hにはCanIf SWSで規定された定数やグローバルデータ，システムサービスのみを記載する
 *  - [CANIF725] 標準化されたパラメータは本ヘッダファイルで他のBSWに提供可能とする
 */

#ifndef CANIF_H
#define CANIF_H

#include "CanIf_Types.h"        /* [CANIF643] */
#include "CanIf_Cfg.h"
#include "EcuM.h"
#include "Can.h"                /* [CANIF040][CANIF294][CANIF023][CANIF377][CANIF378][CANIF023] */

#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
#define CANIF_SWITCH_DET_ERROR(ModuleId, InstanceId, ApiId, ErrorId)	(void) Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId)
#else
#define CANIF_SWITCH_DET_ERROR(ModuleId, InstanceId, ApiId, ErrorId)
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */

#define CANIF_MODULE_ID					60U      /* [CANIF727] */

#define CANIF_E_PARAM_CANID				10U         /* [CANIF154] */
#define CANIF_E_PARAM_DLC				11U         /* [CANIF154] */
#define CANIF_E_PARAM_HRH				12U         /* [CANIF154] */
#define CANIF_E_PARAM_LPDU				13U         /* [CANIF154] */
#define CANIF_E_PARAM_CONTROLLER		14U         /* [CANIF154] */
#define CANIF_E_PARAM_CONTROLLERID		15U         /* [CANIF154] */
#define CANIF_E_PARAM_WAKEUPSOURCE		16U         /* [CANIF154] */
#define CANIF_E_PARAM_TRCV				17U         /* [CANIF154] */
#define CANIF_E_PARAM_TRCVMODE			18U         /* [CANIF154] */
#define CANIF_E_PARAM_TRCVWAKEUPMODE	19U         /* [CANIF154] */
#define CANIF_E_PARAM_CTRLMODE			21U         /* [CANIF154] */
#define CANIF_E_PARAM_POINTER			20U         /* [CANIF154] */
#define CANIF_E_UNINIT					30U         /* [CANIF154] */
#define CANIF_E_INVALID_TXPDUID			50U         /* [CANIF154] */
#define CANIF_E_DATA_LENGTH_MISMATCH	51U
#define CANIF_E_INVALID_RXPDUID			60U         /* [CANIF154] */
#define CANIF_E_INVALID_DLC				61U         /* [CANIF154] */
#define CANIF_E_STOPPED					70U         /* [CANIF154] */
#define CANIF_E_NOT_SLEEP				71U         /* [CANIF154] */
#define CANIF_E_FATAL					0xFFU

#define CANIF_UNINIT	0x01U
#define CANIF_INIT		0x02U

#define CANIF_SEND		0x03U
#define CANIF_RECEIVE	0x04U
#define CANIF_STANDARD_CAN		0x05U
#define CANIF_STANDARD_FD_CAN	0x06U
#define CANIF_FDTYPE			0x4000U

#define DLC_MAX	8U
#define CANFD_DLC_MAX	64U


/*
 *  [CANIF018][CANIF019][CANIF156][CANIF119]
 *  チェックマクロ
 */
#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
/* [CANIF661]  */
#define CANIF_CHECK_INITIALIZED(ApiId)											  \
	do {																		  \
		if (canif_state != CANIF_INIT) {										  \
			(void) Det_ReportError(CANIF_MODULE_ID, 0U, (ApiId), CANIF_E_UNINIT); \
			goto error_exit;													  \
		}																		  \
	} while (0)

#define CANIF_CHECK_INITIALIZED_ERCD(ApiId)										  \
	do {																		  \
		if (canif_state != CANIF_INIT) {										  \
			ercd = E_NOT_OK;													  \
			(void) Det_ReportError(CANIF_MODULE_ID, 0U, (ApiId), CANIF_E_UNINIT); \
			goto error_exit;													  \
		}																		  \
	} while (0)

#define CANIF_CHECK_PARAM(exp, ApiId, ErrorId)								 \
	do {																	 \
		if (!(exp)) {														 \
			(void) Det_ReportError(CANIF_MODULE_ID, 0U, (ApiId), (ErrorId)); \
			goto error_exit;												 \
		}																	 \
	} while (0)

#define CANIF_CHECK_PARAM_ERCD(exp, ApiId, ErrorId)							 \
	do {																	 \
		if (!(exp)) {														 \
			ercd = E_NOT_OK;												 \
			(void) Det_ReportError(CANIF_MODULE_ID, 0U, (ApiId), (ErrorId)); \
			goto error_exit;												 \
		}																	 \
	} while (0)

#define CANIF_CHECK_NULL_POINTER(exp, ApiId)											 \
	do {																				 \
		if (!(exp)) {																	 \
			(void) Det_ReportError(CANIF_MODULE_ID, 0U, (ApiId), CANIF_E_PARAM_POINTER); \
			goto error_exit;															 \
		}																				 \
	} while (0)

#define CANIF_CHECK_NULL_POINTER_ERCD(exp, ApiId)										 \
	do {																				 \
		if (!(exp)) {																	 \
			ercd = E_NOT_OK;															 \
			(void) Det_ReportError(CANIF_MODULE_ID, 0U, (ApiId), CANIF_E_PARAM_POINTER); \
			goto error_exit;															 \
		}																				 \
	} while (0)

#else /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_OFF */
#define CANIF_CHECK_INITIALIZED(ApiId)
#define CANIF_CHECK_INITIALIZED_ERCD(ApiId)
#define CANIF_CHECK_PARAM(exp, ApiId, ErrorId)
#define CANIF_CHECK_PARAM_ERCD(exp, ApiId, ErrorId)
#define CANIF_CHECK_NULL_POINTER(exp, ApiId)
#define CANIF_CHECK_NULL_POINTER_ERCD(exp, ApiId)
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */

/* パラメータにより，実施有無が変わるチェックマクロ */
#if CANIF_PRIVATE_DLC_CHECK == STD_ON
#define A_CHECK_DLC(dlc, config_dlc)																	   \
	do {																								   \
		if ((dlc) < (config_dlc)) {																		   \
			CANIF_SWITCH_DET_ERROR(CANIF_MODULE_ID, 0U, CanIfServiceId_RxIndication, CANIF_E_INVALID_DLC); \
			goto error_exit;																			   \
		}																								   \
	} while (0)
#else /* CANIF_PRIVATE_DLC_CHECK == STD_OFF */
#define A_CHECK_DLC(dlc, config_dlc)
#endif /* CANIF_PRIVATE_DLC_CHECK == STD_ON */

/* DET有無にかかわらず実施するチェックマクロ */
#define C_CANIF_CHECK_PARAM_ERCD(exp, ApiId, ErrorId)						 \
	do {																	 \
		if (!(exp)) {														 \
			ercd = E_NOT_OK;												 \
			CANIF_SWITCH_DET_ERROR(CANIF_MODULE_ID, 0U, (ApiId), (ErrorId)); \
			goto error_exit;												 \
		}																	 \
	} while (0)

/* 実施必須チェックマクロ */
#define D_CANIF_CHECK_PARAM(exp) \
	do {						 \
		if (!(exp)) {			 \
			goto error_exit;	 \
		}						 \
	} while (0)

#define D_CANIF_CHECK_PARAM_ERCD(exp) \
	do {							  \
		if (!(exp)) {				  \
			ercd = E_NOT_OK;		  \
			goto error_exit;		  \
		}							  \
	} while (0)

/*
 *  [CANIF728][CANIF021] AUTOSARリリースバージョン
 */
#define CANIF_AR_RELEASE_MAJOR_VERSION		4U
#define CANIF_AR_RELEASE_MINOR_VERSION		0U
#define CANIF_AR_RELEASE_REVISION_VERSION	3U

/*
 *  [CANIF728][CANIF729] サプライヤバージョン情報
 */
#define CANIF_SW_MAJOR_VERSION	1U
#define CANIF_SW_MINOR_VERSION	3U
#define CANIF_SW_PATCH_VERSION	0U
#define CANIF_VENDOR_ID			65U /* [CANIF726] NCESベンダID */

/*
 *  情報取得マクロ
 */
#define GET_CANIF_CTRL_NUM()				tnum_canif_controller
#define GET_LPDU_NUM()						p_cur_canif_config->tnum_lpdu
#define GET_CANIF_CTRL_INIB(ControllerId)	(&p_cur_canif_ctrl_inib[(ControllerId)])
#define GET_CANIF_CTRL_CB(ControllerId)		p_cur_canif_ctrl_inib[(ControllerId)].p_canif_ctrl_cb
#define GET_LPDU_INIB(PduId)				(&p_cur_lpdu_inib[(PduId)])
#define GET_LPDU_INIB_HOH(Hoh)				pp_cur_lpdu_inib_hoh[(Hoh)]

/*
 *  DETへ通知するサービスID
 */
#define CanIfServiceId_Init							0x01U
#define CanIfServiceId_SetControllerMode			0x03U
#define CanIfServiceId_GetControllerMode			0x04U
#define CanIfServiceId_Transmit						0x05U
#define CanIfServiceId_CancelTransmit				0x18U
#define CanIfServiceId_ReadRxPduData				0x06U
#define CanIfServiceId_ReadTxNotifStatus			0x07U
#define CanIfServiceId_ReadRxNotifStatus			0x08U
#define CanIfServiceId_SetPduMode					0x09U
#define CanIfServiceId_GetPduMode					0x0AU
#define CanIfServiceId_GetVersionInfo				0x0BU
#define CanIfServiceId_CheckWakeup					0x11U
#define CanIfServiceId_CheckValidation				0x12U
#define CanIfServiceId_GetTxConfirmationState		0x19U
#define CanIfServiceId_CheckBaudrate				0x1AU
#define CanIfServiceId_ChangeBaudrate				0x1BU
#define CanIfServiceId_TxConfirmation				0x13U
#define CanIfServiceId_RxIndication					0x14U
#define CanIfServiceId_ControllerBusOff				0x16U
#define CanIfServiceId_ControllerModeIndication		0x17U


/*
 *  関数ポインタ型定義
 */
typedef void (*User_TxConfirmation)(PduIdType TxPduId);
typedef void (*User_RxIndication)(PduIdType RxPduId, PduInfoType *PduInfoPtr);
typedef void (*User_ValidateWakeupEvent)(EcuM_WakeupSourceType sources);
typedef void (*User_ControllerBusOff)(uint8 ControllerId);
typedef void (*User_ControllerModeIndication)(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
typedef void (*CanIf_PduUserConfirmation)();

/*
 *  CanIfコントローラ管理ブロック
 */
typedef struct canif_controller_control_block {
	CanIf_ControllerModeType	controller_mode;        /* CCMSM */
	CanIf_PduGetModeType		pdu_mode;               /* コントローラに属するPDUチャネルモード */
	boolean						validation_status;      /* TRUE:CANメッセージを受信した，FALSE:CANメッセージを1度も受信していない */

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	boolean	tx_confirmation_flg;                        /* コントローラに対してTxConfirmationが呼ばれたかどうかを保持する */
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */
} CANIF_CTRL_CB;

/*
 *  CanIfコントローラ初期化ブロック
 */
typedef struct canif_controller_initialization_block {
	uint8					CanControllerId;        /* CanIfCtrlCanCtrlRefの参照先から取得 */
	EcuM_WakeupSourceType	EcuMWakeupSourceId;     /* CanWakeupSourceRefの参照先から取得 */
	boolean					CanIfCtrlWakeupSupport; /* TRUE:CANコントローラ起動をサポートする，FALSE:CANコントローラ起動をサポートしない */
	CANIF_CTRL_CB			*p_canif_ctrl_cb;       /* CANコントローラ管理ブロック */
} CANIF_CTRL_INIB;

/*
 *  LPDU初期化ブロック
 */
typedef struct lpdu_initialization_block {
	Can_IdType		CanIfPduCanId;                          /* [CANIF281] 送信:CanIfTxPduCanId，受信:CanIfRxPduCanId */
	uint8			CanIfPduCanIdType;                       /* 送信:CanIfTxPduCanIdType，受信:CanIfRxPduCanIdType */
	uint8			CanIfPduDlc;                            /* 送信:CanIfTxPduDlc，受信:CanIfRxPduDlc */
	uint8			CanObjectId;                            /* 参照先のCanHardWareObjectから取得 */
	PduIdType		PduRPduHandleId;                        /* 送信:PduRDestPduHandleId，受信:PduRSourcePduHandleId */
	CanIf_PduUserConfirmation	CanIfPduUserConfirmationName;           /* 送信:CanIfTxPduUserTxConfirmationName，受信:CanIfRxPduUserRxIndicationName */
	CANIF_CTRL_CB	*p_canif_ctrl_cb;                       /* CANIFコントローラ管理ブロック */

#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS
	/*
	 *  LPDUの通知ステータス
	 *  送信 TRUE:CanIf_TxConfirmationが呼ばれた，FALSE:CanIf_TxConfirmationが呼ばれていない
	 *       CanIfTxPduReadNotifyStatusがFALSEの場合，NULL_PTR
	 *
	 *  受信 TRUE:CanIf_RxIndicationが呼ばれた，FALSE:CanIf_RxIndicationが呼ばれていない
	 *       CanIfRxPduReadNotifyStatusがFALSEの場合，NULL_PTR
	 */
	CanIf_NotifStatusType *p_notify_status;
#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */

#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
	/*
	 * 受信完了通知有無フラグ
	 * 送信の場合，NULL_PTR．受信の場合，必須．
	 * TRUE:1度でもCanIf_RxIndicationが呼ばれた，FALSE:1度もCanIf_RxIndicationが呼ばれていない
	 */
	boolean	*p_rx_indication_flg;
	uint8	*p_rx_lpdu_buffer;                              /* 送信または，受信かつCanIfRxPduReadDataがFALSEならば，NULL_PTR */
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
	uint8 lpdu_direction;                                   /* LPDU送受信方向 */
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */
} LPDU_INIB;

/*
 *  CanIfコンフィギュレーション管理ブロック
 */
typedef struct canif_config_type {
	uint16			tnum_lpdu;                      /* LPDU数 */
	const LPDU_INIB	*p_lpdu_inib_table;             /* LPDU初期化ブロック配列 */
	const LPDU_INIB	* const *pp_lpdu_inib_hoh_list; /* LPDU初期化ブロックポインタをCanObjectIdでソートしたリスト */
} CanIf_ConfigType;

extern const CanIf_ConfigType			* p_default_canif_config;

extern User_ControllerBusOff			CanIfDispatchUserCtrlBusOffName;
extern User_ControllerModeIndication	CanIfDispatchUserCtrlModeIndicationName;
extern User_ValidateWakeupEvent			CanIfDispatchUserValidateWakeupEventName;

extern const uint16						tnum_canif_controller;
extern const CANIF_CTRL_INIB			canif_ctrl_inib_table[];


/*
 *  CanIfシステムサービスプロトタイプ宣言
 */
extern void CanIf_Init(const CanIf_ConfigType *ConfigPtr);
extern Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
extern Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, CanIf_ControllerModeType *ControllerModePtr);
extern Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr);
extern Std_ReturnType CanIf_CancelTransmit(PduIdType CanTxPduId);
extern Std_ReturnType CanIf_ReadRxPduData(PduIdType CanRxPduId, PduInfoType *PduInfoPtr);
extern CanIf_NotifStatusType CanIf_ReadTxNotifStatus(PduIdType CanTxPduId);
extern CanIf_NotifStatusType CanIf_ReadRxNotifStatus(PduIdType CanRxPduId);
extern Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduSetModeType PduModeRequest);
extern Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduGetModeType *PduModePtr);
extern void CanIf_GetVersionInfo(Std_VersionInfoType *VersionInfo);
extern Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
extern Std_ReturnType CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource);
extern CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 ControllerId);
extern Std_ReturnType CanIf_CheckBaudrate(uint8 ControllerId, const uint16 Baudrate);
extern Std_ReturnType CanIf_ChangeBaudrate(uint8 ControllerId, const uint16 Baudrate);


/*
 *  以下，未サポート機能
 */
extern void CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId);
extern Std_ReturnType CanIf_SetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);
extern Std_ReturnType CanIf_GetTrcvMode(CanTrcv_TrcvModeType *TransceiverModePtr, uint8 TransceiverId);
extern Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 TransceiverId, CanTrcv_TrcvWakeupReasonType *TrcvWuReasonPtr);
extern Std_ReturnType CanIf_SetTrcvWakeupMode(uint8 TransceiverId, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);
extern Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 TransceiverId);
extern Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 TransceiverId);

/*
 *  ボディ制御系プロファイル以外のために対応しない仕様タグ一覧
 *  (同一仕様タグがボディ制御系プロファイルの要求仕様でも使用されているものは[]で表記)
 *  - 送信キャンセルコンファメーション
 *    <CANIF054><CANIF101><CANIF828><CANIF424><CANIF426><CANIF427><CANIF428><CANIF118>
 *  - 送信バッファリング
 *    <CANIF063><CANIF381><CANIF835><CANIF836><CANIF068><CANIF837><CANIF386><CANIF668><CANIF070><CANIF183>
 *    <CANIF387><CANIF033><CANIF176><CANIF485>
 *  - 動的送信ID設定
 *    <CANIF188><CANIF673><CANIF189><CANIF352><CANIF353><CANIF355><CANIF356><CANIF357>
 *  - 受信フィルタリング
 *    <CANIF645><CANIF646><CANIF030><CANIF211><CANIF389><CANIF663><CANIF469>
 *  - マルチCANドライバサポート
 *    <CANIF124><CANIF224>
 *  - CANトランシーバ制御
 *    <CANIF287><CANIF288><CANIF289><CANIF290><CANIF358><CANIF362><CANIF363><CANIF364><CANIF367><CANIF368>
 *    <CANIF371><CANIF372><CANIF373><CANIF535><CANIF536><CANIF537><CANIF538><CANIF648><CANIF649><CANIF650>
 *    <CANIF693><CANIF694><CANIF706><CANIF708><CANIF709><CANIF710><CANIF712><CANIF730><CANIF757><CANIF759>
 *    <CANIF760><CANIF761><CANIF762><CANIF763><CANIF764><CANIF765><CANIF766><CANIF769><CANIF770><CANIF771>
 *    <CANIF788><CANIF799><CANIF805><CANIF806><CANIF807><CANIF808><CANIF809><CANIF810><CANIF811><CANIF812>
 *    <CANIF813><CANIF814>
 *  - パーシャルネットワーキング
 *    <CANIF747><CANIF748><CANIF749><CANIF750><CANIF751><CANIF752><CANIF827><CANIF753><CANIF754><CANIF815>
 *    <CANIF816><CANIF817><CANIF818><CANIF821><CANIF822><CANIF825><CANIF827>
 */

/*
 *  その他の仕様説明
 *    <CANIF999> 要求仕様ではない
 */

#endif /* CANIF_H */
