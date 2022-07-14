/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
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
 *  $Id: Can.h 1245 2015-03-25 09:25:18Z panasonic-ayane $
 */

#ifndef TOPPERS_CAN_H
#define TOPPERS_CAN_H

/*
 * [CAN043][CAN037] 本ファイルには，Canのシステムサービスや変数のextern宣言，データ型定義を記述する
 */

/* [CAN034][CAN435][CAN388] */
/* [CAN222] Canモジュールで必要なデータ型が定義されたヘッダファイル */
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"
#include "EcuM.h"

#define CAN_MODULE_ID	80U

/*
 *  [CAN111] AUTOSARリリースバージョン
 */
#define CAN_AR_RELEASE_MAJOR_VERSION		4U
#define CAN_AR_RELEASE_MINOR_VERSION		0U
#define CAN_AR_RELEASE_REVISION_VERSION		3U

/*
 *  サプライヤバージョン情報
 */
#define CAN_SW_MAJOR_VERSION	1U
#define CAN_SW_MINOR_VERSION	2U
#define CAN_SW_PATCH_VERSION	0U
#define CAN_VENDOR_ID			65U /* NCESベンダID */

/*
 *  情報取得マクロ
 */
#define GET_HOH_NUM()								p_cur_can_config->tnum_hoh
#define GET_CONTROLLER_NUM()						p_cur_can_config->tnum_controller
#define GET_HTH_NUM(id)								p_cur_can_ctrl_inib_table[(id)].tnum_hth
#define GET_HRH_NUM(id)								p_cur_can_ctrl_inib_table[(id)].tnum_hrh
#define GET_BOX_IDX(hoh)							p_cur_hoh_box_table[(hoh)].box_idx
#define GET_CONTROLLER_ID(hoh)						p_cur_hoh_box_table[(hoh)].CanControllerId
#define GET_BOX_OBJ_TYPE(hoh)						p_cur_hoh_box_table[(hoh)].box_obj_type
#define GET_RBOX_CAN_OBJ_ID(id, mb_no)				p_cur_can_ctrl_inib_table[(id)].p_rbox_hrh_table[(mb_no)]
#define GET_RBOX_CAN_ID(id, hrh_no)					p_cur_can_ctrl_inib_table[(id)].p_rbox_canid_table[(hrh_no)].CanIdValue
#define GET_RBOX_FILTER_MASK_IDX(id, hrh_no)		p_cur_can_ctrl_inib_table[(id)].p_rbox_canid_table[(hrh_no)].filtermask_idx
#define GET_SAVED_PDU_ID(id, box_no)				p_cur_can_ctrl_inib_table[(id)].p_can_hth_cb_table[(box_no)].saved_pduid
#define GET_HTH_MUTEX(id, box_no)					p_cur_can_ctrl_inib_table[(id)].p_can_hth_cb_table[(box_no)].mutex
#define GET_CAN_CTRL_INIB(id)						&p_cur_can_ctrl_inib_table[(id)]

/*
 *  情報設定マクロ
 */
#define SET_SAVED_PDU_ID(id, box_no, pdu_id)		(p_cur_can_ctrl_inib_table[(id)].p_can_hth_cb_table[(box_no)].saved_pduid = (pdu_id))
#define SET_HTH_MUTEX(id, box_no, mutex_state)		(p_cur_can_ctrl_inib_table[(id)].p_can_hth_cb_table[(box_no)].mutex = (mutex_state))

/*
 *  [CAN080] エラーコード(uint8)
 */
#define CAN_E_PARAM_POINTER		0x01U
#define CAN_E_PARAM_HANDLE		0x02U
#define CAN_E_PARAM_DLC			0x03U
#define CAN_E_PARAM_CONTROLLER	0x04U
#define CAN_E_UNINIT			0x05U
#define CAN_E_TRANSITION		0x06U
#define CAN_E_DATALOST			0x07U
#define CAN_E_PARAM_BAUDRATE	0x08U
#define CAN_E_FATAL				0xFFU

/*
 *  フィルタマスク未設定用インデックス
 */
#define CAN_NO_MASK_IDX			0xFFU

/*
 *  送受信種別
 */
#define CAN_TRANSMIT			0x00U
#define CAN_RECEIVE				0x01U

/*
 *  CANドライバ状態種別
 */
#define CAN_UNINIT				0x00U
#define CAN_READY				0x01U

/* ネストカウント最大値 */
#define CAN_INTERRUPT_NESTED_CNT_MAX		0xFFU

/* ポーリングモード種別 */
#define CAN_USE_POLLING_BUSOFF	0x01U
#define CAN_USE_POLLING_RX		0x02U
#define CAN_USE_POLLING_TX		0x04U
#define CAN_USE_POLLING_WAKEUP	0x08U


/*
 *  [CAN082][CAN083][CAN084] DETエラーマクロ(ON/OFF切り替え)
 */
#if CAN_DEV_ERROR_DETECT == STD_ON
/* [CAN027][CAN028] DETエラーが有効の場合，DETシステムサービスを呼び出す */
#define CAN_DET_REPORT_ERROR(ApiId, ErrorId)	(void) Det_ReportError(CAN_MODULE_ID, 0U, (ApiId), (ErrorId))

#define CAN_CHECK_INITIALIZED(ApiId)					 \
	do {												 \
		if (can_init_flg == CAN_UNINIT) {				 \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_UNINIT); \
			goto error_exit;							 \
		}												 \
	} while (0)
#define CAN_CHECK_INITIALIZED_ERCD_STD_RETERN_TYPE(ApiId) \
	do {												  \
		if (can_init_flg == CAN_UNINIT) {				  \
			ercd = E_NOT_OK;							  \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_UNINIT);  \
			goto error_exit;							  \
		}												  \
	} while (0)
#define CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(ApiId) \
	do {												  \
		if (can_init_flg == CAN_UNINIT) {				  \
			ercd = CAN_NOT_OK;							  \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_UNINIT);  \
			goto error_exit;							  \
		}												  \
	} while (0)
#define CAN_CHECK_CONTROLLER(exp, ApiId)						   \
	do {														   \
		if (!(exp)) {											   \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_PARAM_CONTROLLER); \
			goto error_exit;									   \
		}														   \
	} while (0)
#define CAN_CHECK_CONTROLLER_ERCD_STD_RETERN_TYPE(exp, ApiId)	   \
	do {														   \
		if (!(exp)) {											   \
			ercd = E_NOT_OK;									   \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_PARAM_CONTROLLER); \
			goto error_exit;									   \
		}														   \
	} while (0)
#define CAN_CHECK_CONTROLLER_ERCD_CAN_RETERN_TYPE(exp, ApiId)	   \
	do {														   \
		if (!(exp)) {											   \
			ercd = CAN_NOT_OK;									   \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_PARAM_CONTROLLER); \
			goto error_exit;									   \
		}														   \
	} while (0)
#define CAN_CHECK_HTH_ERCD_CAN_RETERN_TYPE(exp, ApiId)		   \
	do {													   \
		if (!(exp)) {										   \
			ercd = CAN_NOT_OK;								   \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_PARAM_HANDLE); \
			goto error_exit;								   \
		}													   \
	} while (0)
#define CAN_CHECK_DLC_ERCD_CAN_RETERN_TYPE(exp, ApiId)		\
	do {													\
		if (!(exp)) {										\
			ercd = CAN_NOT_OK;								\
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_PARAM_DLC);	\
			goto error_exit;								\
		}													\
	} while (0)
#define CAN_CHECK_SDU_ERCD_CAN_RETERN_TYPE(exp, ApiId)			\
	do {														\
		if (!(exp)) {											\
			ercd = CAN_NOT_OK;									\
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_PARAM_POINTER);	\
			goto error_exit;									\
		}														\
	} while (0)
#define CAN_CHECK_MAILBOX_INDEX_NUM(exp, ApiId)			\
	do {												\
		if (!(exp)) {									\
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_FATAL);	\
			goto error_exit;							\
		}												\
	} while (0)
#else /* CAN_DEV_ERROR_DETECT == STD_OFF */
/* [CAN424][CAN089] DETエラーが無効の場合，何も処理しない */
#define CAN_DET_REPORT_ERROR(ApiId, ErrorId)
#define CAN_CHECK_INITIALIZED(ApiId)
#define CAN_CHECK_INITIALIZED_ERCD_STD_RETERN_TYPE(ApiId)
#define CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(ApiId)
#define CAN_CHECK_CONTROLLER(exp, ApiId)
#define CAN_CHECK_CONTROLLER_ERCD_STD_RETERN_TYPE(exp, ApiId)
#define CAN_CHECK_CONTROLLER_ERCD_CAN_RETERN_TYPE(exp, ApiId)
#define CAN_CHECK_HTH_ERCD_CAN_RETERN_TYPE(exp, ApiId)
#define CAN_CHECK_DLC_ERCD_CAN_RETERN_TYPE(exp, ApiId)
#define CAN_CHECK_SDU_ERCD_CAN_RETERN_TYPE(exp, ApiId)
#define CAN_CHECK_MAILBOX_INDEX_NUM(exp, ApiId)
#endif /* CAN_DEV_ERROR_DETECT == STD_ON */

/* [CAN431] チェックマクロ(MainFunction用) */
#define CAN_CHECK_INITIALIZED_MF(ApiId)					 \
	do {												 \
		if (can_init_flg == CAN_UNINIT) {				 \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_UNINIT); \
			goto error_exit;							 \
		}												 \
	} while (0)

/*
 *  DETへ通知するサービスID
 */
#define CANServiceId_Init							0x00U
#define CANServiceId_GetVersionInfo					0x07U
#define CANServiceId_CheckBaudrate					0x0EU
#define CANServiceId_ChangeBaudrate					0x0DU
#define CANServiceId_SetControllerMode				0x03U
#define CANServiceId_DisableControllerInterrupts	0x04U
#define CANServiceId_EnableControllerInterrupts		0x05U
#define CANServiceId_CheckWakeup					0x0BU
#define CANServiceId_Write							0x06U
#define CANServiceId_MainFunction_Write				0x01U
#define CANServiceId_MainFunction_Read				0x08U
#define CANServiceId_MainFunction_BusOff			0x09U
#define CANServiceId_MainFunction_Wakeup			0x0AU
#define CANServiceId_MainFunction_Mode				0x0CU
#define CANServiceId_IsrRx							0x20U
#define CANServiceId_IsrTx							0x21U
#define CANServiceId_IsrBusoff						0x22U
#define CANServiceId_IsrWakeup						0x23U

/*
 *  [CAN414] ボーレート設定情報
 */
typedef struct can_controller_baudrate_config_type {
	uint16	CanControllerBaudRate;
	uint8	CanControllerPropSeg;
	uint8	CanControllerSeg1;
	uint8	CanControllerSeg2;
	uint8	CanControllerSyncJumpWidth;
} Can_ControllerBaudrateConfigType;

/*
 *  HOHボックステーブル管理ブロック
 */
typedef struct {
	uint8				CanControllerId;        /* CANコントローラID */
	uint8				box_obj_type;           /* 送受信種別 */
	Can_HwHandleType	box_idx;                /* HRHまたはHTH */
} Can_HohBoxType;

/*
 *  受信ボックスCAN-IDテーブル管理ブロック
 */
typedef struct {
	Can_IdType	CanIdValue;         /* CAN-ID */
	uint8		filtermask_idx;     /* フィルタマスクテーブルのインデックス */
} Can_RboxCanidType;

/*
 *  HTH管理ブロック
 */
typedef struct can_hth_control_block {
	PduIdType	saved_pduid;        /* 送信完了通知用PDU-ID保存 */
	boolean		mutex;              /* ミューテックス管理 */
} CAN_HTH_CB;

/*
 *  CANコントローラ管理ブロック
 */
typedef struct can_controller_initialization_block {
	uint8									CanIfCtrlId;            /* CanIf側のコントローラID */
	uint8									tnum_baudrate;          /* 選択可能なボーレート数 */
	Can_HwHandleType						tnum_hth;               /* HTH数 */
	Can_HwHandleType						tnum_hrh;               /* HRH数 */
	uint8									tnum_filtermask;        /* フィルタマスク数 */
	uint8									use_polling;            /* ポーリングモード使用管理 */
	boolean									CanWakeupSupport;       /* ウェイクアップサポート有無 */
	EcuM_WakeupSourceType					EcuMWakeupSourceId;     /* CanWakeupSourceRefの参照先 */
	const Can_ControllerBaudrateConfigType	*p_default_baudrate;    /* デフォルトボーレート */
	const Can_ControllerBaudrateConfigType	*p_baudrate_table;      /* サポートボーレートリスト */
	const Can_IdType						*p_filtermask_table;    /* フィルタマスクリスト */
	const Can_HwHandleType					*p_rbox_hrh_table;      /* 受信ボックス番号→HRH変換テーブル配列 */
	const Can_RboxCanidType					*p_rbox_canid_table;    /* 受信ボックスCAN-IDテーブル */
	CAN_HTH_CB * const						p_can_hth_cb_table;     /* HTH管理ブロックテーブル */
} CAN_CTRL_INIB;

/*
 *  [CAN413] Canコンフィギュレーション管理ブロック
 */
typedef struct can_config_type {
	Can_HwHandleType		tnum_hoh;                   /* HOH数 */
	uint8					tnum_controller;            /* コントローラ数 */
	const Can_HohBoxType	*p_hoh_box_table;           /* HOH→ボックス番号変換テーブル配列 */
	const CAN_CTRL_INIB		*p_can_ctrl_inib_table;     /* コントローラ初期化ブロックテーブル */
} Can_ConfigType;

/*
 *  L-PDU-Callout関数型定義
 */
typedef boolean (*Can_LpduCallout)(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);

/*
 *  Canシステムサービスプロトタイプ宣言
 */
extern void Can_Init(const Can_ConfigType *Config);
extern void Can_GetVersionInfo(Std_VersionInfoType *versioninfo);
extern Std_ReturnType Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate);
extern Std_ReturnType Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate);
extern Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition);
extern void Can_DisableControllerInterrupts(uint8 Controller);
extern void Can_EnableControllerInterrupts(uint8 Controller);
extern Can_ReturnType Can_CheckWakeup(uint8 Controller);
extern Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);
extern void Can_MainFunction_Write(void);
extern void Can_MainFunction_Read(void);
extern void Can_MainFunction_BusOff(void);
extern void Can_MainFunction_Wakeup(void);
extern void Can_MainFunction_Mode(void);

/*
 *  Can割込みサービスルーチンプロトタイプ宣言
 */
extern void Can_IsrRx(uint8 Controller);
extern void Can_IsrTx(uint8 Controller);
extern void Can_IsrBusoff(uint8 Controller);
extern void Can_IsrWakeup(uint8 Controller);

extern const CAN_CTRL_INIB	can_ctrl_inib_table[];

/*
 *  Canコンフィギュレーション情報(Can_PBcfg.c)
 */
extern const Can_ConfigType	can_config[];

#endif /* TOPPERS_CAN_H */
