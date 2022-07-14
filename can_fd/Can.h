/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2013-2017 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2013-2017 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2016-2017 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2016-2017 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2016-2017 by SUZUKI MOTOR CORPORATION
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
 *  $Id: Can.h 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

#ifndef CAN_H
#define CAN_H

/* [CAN034][CAN435][CAN388] */
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"

#define CAN_MODULE_ID	80U

/*
 *  AUTOSARリリースバージョン
 */
#define CAN_AR_RELEASE_MAJOR_VERSION		4U
#define CAN_AR_RELEASE_MINOR_VERSION		0U
#define CAN_AR_RELEASE_REVISION_VERSION		3U

/*
 *  サプライヤバージョン情報
 */
#define CAN_SW_MAJOR_VERSION	1U
#define CAN_SW_MINOR_VERSION	0U
#define CAN_SW_PATCH_VERSION	0U
#define CAN_VENDOR_ID			65U /* NCESベンダID */

/*
 *  情報取得マクロ
 */
#define GET_HOH_NUM()					p_cur_can_config->tnum_hoh
#define GET_HTH_NUM()					p_cur_can_config->tnum_hth
#define GET_HRH_NUM()					p_cur_can_config->tnum_hrh
#define GET_BOX_ID(hoh)					p_cur_hoh_box_table[(hoh)]
#define GET_RBOX_CAN_OBJ_ID(rbox)		p_cur_rbox_hrh_table[(rbox)]
#define GET_RBOX_CAN_ID_FILTER(rbox)	p_cur_rbox_filter_table[(rbox)]
#define GET_SAVED_PDU_ID(tbox)			p_cur_saved_pduid[(tbox)]
#define GET_CAN_CTRL_INIB(id)			&p_cur_can_ctrl_inib_table[(id)]


/* [CAN043][CAN037] 本ファイルには，Canのシステムサービスや変数のextern宣言，データ型定義のみを記述する */

typedef struct can_controller_initialization_block {
	uint8			CanIfCtrlId;        /* CanIf側のコントローラID */
	uint8			tnum_baudrate;      /* 選択可能なボーレート数 */
	uint16			default_baudrate;   /* デフォルトボーレート */
	const uint16	*p_baudrate_table;  /* サポートボーレートリスト */
} CAN_CTRL_INIB;

/*
 *  [CAN413] Canコンフィギュレーション管理ブロック
 */
typedef struct can_config_type {
	Can_HwHandleType		tnum_hoh;               /* HOH数 */
	Can_HwHandleType		tnum_hth;               /* HTH数 */
	Can_HwHandleType		tnum_hrh;               /* HRH数 */
	const Can_HwHandleType	*p_hoh_box_table;       /* HOH→ボックス番号変換テーブル配列 */
	const Can_HwHandleType	*p_rbox_hrh_table;      /* 受信ボックス番号→HRH変換テーブル配列 */
	const Can_IdType		*p_rbox_filter_table;   /* 受信ボックスフィルタテーブル(FullCanではCAN-IDと一致する) */
	PduIdType				*p_saved_pduid;         /* 送信完了通知用PDU-ID保存バッファ */
	const CAN_CTRL_INIB		*p_can_ctrl_inib_table; /* コントローラ初期化ブロックテーブル */
} Can_ConfigType;

extern void Can_Init(const Can_ConfigType *Config);
extern void Can_GetVersionInfo(Std_VersionInfoType *versioninfo);
extern Std_ReturnType Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate);
extern Std_ReturnType Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate);
extern Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition);
extern Can_ReturnType Can_CheckWakeup(uint8 Controller);
extern Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);
extern void Can_ISR(uint8 Controller);

extern const CAN_CTRL_INIB can_ctrl_inib_table[];

#endif /* CAN_H */
