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
 *  $Id: Can_GeneralTypes.h 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H


/* [CAN416] Nios2ではSTANDARDのみサポートする */
typedef uint16 Can_IdType;

#define CAN_FDTYPE		0x4000U

/* [CAN429] Nios2ではメールボックス数上限が32個のため，8ビット固定とする */
typedef uint8 Can_HwHandleType;

/* [CAN415] CAN PDU構造体 */
typedef struct {
	PduIdType	swPduHandle;
	uint8		length;
	Can_IdType	id;
	uint8		*sdu;
} Can_PduType;

/* [CAN417] CANコントローラ状態 */
typedef enum {
	CAN_T_START,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

/* [CAN039] CANドライバ標準戻り値 */
typedef enum {
	CAN_OK,
	CAN_NOT_OK,
	CAN_BUSY
} Can_ReturnType;

/* [CT暫定対応] 必要な型を用意する */
typedef enum {
	CANTRCV_TRCVMODE_NORMAL,
	CANTRCV_TRCVMODE_SLEEP,
	CANTRCV_TRCVMODE_STANDBY
} CanTrcv_TrcvModeType;

typedef enum {
	CANTRCV_WU_ERROR,
	CANTRCV_WU_BY_BUS,
	CANTRCV_WU_BY_PIN,
	CANTRCV_WU_INTERNALLY,
	CANTRCV_WU_NOT_SUPPORTED,
	CANTRCV_WU_POWER_ON,
	CANTRCV_WU_RESET,
	CANTRCV_WU_BY_SYSERR,
} CanTrcv_TrcvWakeupReasonType;

typedef enum {
	CANTRCV_WUMODE_ENABLE,
	CANTRCV_WUMODE_CLEAR,
	CANTRCV_WUMODE_DISABLE
} CanTrcv_TrcvWakeupModeType;

#endif /* CAN_GENERALTYPES_H */
