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
 *  $Id: CanIf.c 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

/* CanIf.c */
#include "CanIf.h"      /* [CANIF116][CANIF122] */
#include "CanIf_Cbk.h"  /* [CANIF121][CANIF409] */

#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
#include "Det.h"        /* [CANIF464][CANIF294] */
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */

#include "Dem.h"        /* [CANIF020][CANIF150][CANIF153][CANIF155][CANIF223] */
#include "MemMap.h"     /* [CANIF278][CANIF463] */

/* PduR_CanIf.hはPduRジェネレータにより生成される */
#include "PduR_CanIf.h" /* [CANIF208] */
/* SchM_CanIf.hはRTEジェネレータにより生成される */
#include "SchM_CanIf.h" /* [CANIF208][CANIF040] */


/*
 *  現在実行中のCanIfコンフィギュレーション情報
 */
static const CanIf_ConfigType	*p_cur_canif_config;
static const CANIF_CTRL_INIB	*p_cur_canif_ctrl_inib;
static const LPDU_INIB			*p_cur_lpdu_inib;
static const LPDU_INIB			* const *pp_cur_lpdu_inib_hoh;

/*
 *  CanIfの初期化状態
 */
static uint8					canif_state = CANIF_UNINIT;

/*
 *  [CANIF001] CanIf_Init
 */
void
CanIf_Init(const CanIf_ConfigType *ConfigPtr)
{
	CANIF_CTRL_CB	*p_canif_ctrl_cb;
	uint16			i;
#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON) || defined(SUPPORT_READ_PDU_NOTYFY_STATUS)
	const LPDU_INIB	*p_lpdu_inib;
	PduIdType		j;
#endif /* (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON) || defined(SUPPORT_READ_PDU_NOTYFY_STATUS) */

	SchM_Enter_CanIf_Reentrant_0();

	/*
	 *  [CANIF302] 不正なポインタへの対応は，NULL_PTRに対してのみ行う
	 */
	if (ConfigPtr == NULL_PTR) {
		/* [CANIF301] NULL_PTRの場合，デフォルトのコンフィギュレーション情報を使用する */
		ConfigPtr = p_default_canif_config;
	}

	/* 現在実行中のコンフィグレーション情報を保持 */
	p_cur_canif_config = ConfigPtr;
	p_cur_canif_ctrl_inib = canif_ctrl_inib_table;
	p_cur_lpdu_inib = ConfigPtr->p_lpdu_inib_table;
	pp_cur_lpdu_inib_hoh = ConfigPtr->pp_lpdu_inib_hoh_list;

	/* [CANIF085] CanIfのグローバル変数とデータ構造を初期化 */
	canif_state = CANIF_INIT;

	for (i = 0U; i < GET_CANIF_CTRL_NUM(); i++) {
		p_canif_ctrl_cb = GET_CANIF_CTRL_CB(i);
		/* [CANIF476][CANIF477][CANIF478][CANIF479] */
		p_canif_ctrl_cb->controller_mode = CANIF_CS_STOPPED;
		p_canif_ctrl_cb->validation_status = FALSE;
		p_canif_ctrl_cb->pdu_mode = CANIF_GET_OFFLINE;
#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
		p_canif_ctrl_cb->tx_confirmation_flg = FALSE;
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */
	}

#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON) || defined(SUPPORT_READ_PDU_NOTYFY_STATUS)
	for (j = 0U; j < GET_LPDU_NUM(); j++) {
		p_lpdu_inib = GET_LPDU_INIB(j);

#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
		if (p_lpdu_inib->p_rx_indication_flg != NULL_PTR) {
			*(p_lpdu_inib->p_rx_indication_flg) = FALSE;
		}
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS
		if (p_lpdu_inib->p_notify_status != NULL_PTR) {
			*(p_lpdu_inib->p_notify_status) = CANIF_NO_NOTIFICATION;
		}
#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */
	}
#endif /* (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON) || defined(SUPPORT_READ_PDU_NOTYFY_STATUS) */

	SchM_Exit_CanIf_Reentrant_0();

	return;
}

/*
 *  [CANIF003] CanIf_SetControllerMode
 */
Std_ReturnType
CanIf_SetControllerMode(uint8 ControllerId, CanIf_ControllerModeType ControllerMode)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	Can_ReturnType			ret_can;
	Std_ReturnType			ercd;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF312] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_SetControllerMode);
	/* [CANIF311] */
	CANIF_CHECK_PARAM_ERCD((ControllerId < GET_CANIF_CTRL_NUM()), CanIfServiceId_SetControllerMode, CANIF_E_PARAM_CONTROLLERID);
	/* [CANIF774] */
	CANIF_CHECK_PARAM_ERCD(((ControllerMode >= CANIF_CS_SLEEP) && (ControllerMode <= CANIF_CS_STOPPED)), CanIfServiceId_SetControllerMode, CANIF_E_PARAM_CTRLMODE);

	p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(ControllerId);

	/*
	 *  [CANIF474]
	 *  CanIfは完全なCANコントローラステートマシンは含んでいない
	 *
	 *  CanIfで確認できるCCMSMモードはCANIF_CS_UNINIT，CANIF_CS_STOPPED，CANIF_CS_STARTED，およびCANIF_CS_SLEEPのみであり，
	 *  その他のCCMSM状態(CANIF_CS_START_TO_SLEEP，CANIF_CS_SLEEP_TO_START)は含まない．
	 */

	/* [CANIF308] CANコントローラに対してCan_SetControllerModeを呼び出す */
	if (ControllerMode == CANIF_CS_SLEEP) {
		/* [CANIF482][CANIF486] */
		ret_can = Can_SetControllerMode(p_canif_ctrl_inib->CanControllerId, CAN_T_SLEEP);
	}
	else if (ControllerMode == CANIF_CS_STARTED) {
		/* [CANIF481][CANIF584] */
		ret_can = Can_SetControllerMode(p_canif_ctrl_inib->CanControllerId, CAN_T_START);
	}
	else {  /* ControllerMode == CANIF_CS_STOPPED */
		p_canif_ctrl_cb = p_canif_ctrl_inib->p_canif_ctrl_cb;
		if (p_canif_ctrl_cb->controller_mode == CANIF_CS_SLEEP) {
			/* [CANIF487] */
			ret_can = Can_SetControllerMode(p_canif_ctrl_inib->CanControllerId, CAN_T_WAKEUP);
		}
		else {
			/* [CANIF480][CANIF585] */
			ret_can = Can_SetControllerMode(p_canif_ctrl_inib->CanControllerId, CAN_T_STOP);
		}
	}

	if (ret_can == CAN_OK) {
		ercd = E_OK;
	}
	else {
		/* [CANIF475] Can_SetControllerModeがCAN_NOT_OKを返した場合，CanIf_SetControllerModeはE_NOT_OKを返す */
		ercd = E_NOT_OK;
	}

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}

/*
 *  [CANIF229] CanIf_GetControllerMode
 */
Std_ReturnType
CanIf_GetControllerMode(uint8 ControllerId, CanIf_ControllerModeType *ControllerModePtr)
{
	CANIF_CTRL_CB	*p_canif_ctrl_cb;
	Std_ReturnType	ercd;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF316] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_GetControllerMode);
	/* [CANIF313] */
	CANIF_CHECK_PARAM_ERCD((ControllerId < GET_CANIF_CTRL_NUM()), CanIfServiceId_GetControllerMode, CANIF_E_PARAM_CONTROLLERID);
	/* [CANIF656] */
	CANIF_CHECK_PARAM_ERCD((ControllerModePtr != NULL_PTR), CanIfServiceId_GetControllerMode, CANIF_E_PARAM_POINTER);

	p_canif_ctrl_cb = GET_CANIF_CTRL_CB(ControllerId);

	/* [CANIF541] */
	*ControllerModePtr = p_canif_ctrl_cb->controller_mode;

	ercd = E_OK;

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}

/*
 *  [CANIF005] CanIf_Transmit
 */
Std_ReturnType
CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr)
{
	const LPDU_INIB			*p_lpdu_inib;
	const CanIf_ConfigType	*p_saved_config;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	User_TxConfirmation		TxConfirmation;     /* [CANIF011][CANIF437] */
	Can_PduType				PduInfo;
	PduIdType				pduid;
	Std_ReturnType			ercd;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF323] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_Transmit);
	/* [CANIF319] */
	CANIF_CHECK_PARAM_ERCD(CanTxPduId < GET_LPDU_NUM(), CanIfServiceId_Transmit, CANIF_E_INVALID_TXPDUID);
	/* [CANIF320] */
	CANIF_CHECK_NULL_POINTER_ERCD(PduInfoPtr != NULL_PTR, CanIfServiceId_Transmit);

	p_lpdu_inib = GET_LPDU_INIB(CanTxPduId);

	/* [CANIF319] */
	CANIF_CHECK_PARAM_ERCD(p_lpdu_inib->lpdu_direction == CANIF_SEND, CanIfServiceId_Transmit, CANIF_E_INVALID_TXPDUID);
/*↓↓ 16.10.21 ADD ↓↓*/
	/* [SWS_CANIF_00893] */
	if (p_lpdu_inib->CanIfPduCanIdType == CANIF_STANDARD_FD_CAN){
		CANIF_CHECK_PARAM_ERCD((uint8) PduInfoPtr->SduLength <= CANFD_DLC_MAX, CanIfServiceId_Transmit, CANIF_E_DATA_LENGTH_MISMATCH);
	}
	else {
		CANIF_CHECK_PARAM_ERCD((uint8) PduInfoPtr->SduLength <= DLC_MAX, CanIfServiceId_Transmit, CANIF_E_DATA_LENGTH_MISMATCH);
	}
/*↑↑ 16.10.21 ADD ↑↑*/

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

	/* [CANIF317][CANIF723][CANIF677] */
	C_CANIF_CHECK_PARAM_ERCD(p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED, CanIfServiceId_Transmit, CANIF_E_STOPPED);

	/* [CANIF382][CANIF073][CANIF489] */
	C_CANIF_CHECK_PARAM_ERCD((p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_TX_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE), CanIfServiceId_Transmit, CANIF_E_STOPPED);

	/* [CANIF075][CANIF491] PDUチャネルモードがCANIF_GET_ONLINE，CANIF_GET_TX_ONLINEの場合 */
	if ((p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) || (p_canif_ctrl_cb->pdu_mode == CANIF_GET_TX_ONLINE)) {
		/* CAN PDU構造体設定 */
		PduInfo.swPduHandle = CanTxPduId;
		PduInfo.sdu = PduInfoPtr->SduDataPtr;
/*↓↓ 16.10.26 CHANGE ↓↓*/
		/* [SWS_CANIF_00894] */
		if(p_lpdu_inib->CanIfPduCanIdType == CANIF_STANDARD_FD_CAN){
			PduInfo.id = p_lpdu_inib->CanIfPduCanId | CANIF_FDTYPE ;

			if((uint8) PduInfoPtr->SduLength > CANFD_DLC_MAX){
				PduInfo.length = CANFD_DLC_MAX;
			}
			else {
				PduInfo.length = ((uint8) PduInfoPtr->SduLength);
			}
		}
		else {
			PduInfo.id = p_lpdu_inib->CanIfPduCanId;

			if((uint8) PduInfoPtr->SduLength > DLC_MAX){
				PduInfo.length = DLC_MAX;
			}
			else {
				PduInfo.length = ((uint8) PduInfoPtr->SduLength);
			}
		}
/*↑↑ 16.10.26 CHANGE ↑↑*/

		/* [CANIF318] メッセージ書き込み */
		if (Can_Write(p_lpdu_inib->CanObjectId, &PduInfo) == CAN_OK) {
			/* [CANIF162] */
			ercd = E_OK;
		}
		else {
			ercd = E_NOT_OK;
		}
	}
	else {
		/*
		 * [CANIF072] PDUチャネルモードがCANIF_GET_OFFLINE_ACTIVE，CANIF_GET_OFFLINE_ACTIVE_RX_ONLINEの場合，
		 *            送信コンファメーションコールバックを呼び出す
		 */
		if (p_lpdu_inib->CanIfPduUserConfirmationName != NULL_PTR) {
			/* 排他エリア内で各情報を取り出す */
			TxConfirmation = ((User_TxConfirmation) p_lpdu_inib->CanIfPduUserConfirmationName);
			pduid = p_lpdu_inib->PduRPduHandleId;
			/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
			p_saved_config = p_cur_canif_config;

			SchM_Exit_CanIf_Reentrant_0();
			TxConfirmation(pduid);
			SchM_Enter_CanIf_Reentrant_0();

			/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
			CANIF_CHECK_PARAM_ERCD(p_saved_config == p_cur_canif_config, CanIfServiceId_Transmit, CANIF_E_FATAL);
		}
		ercd = E_OK;
	}

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}

/*
 *  [CANIF520] CanIf_CancelTransmit
 */
/* [CANIF521] */
#if CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON
Std_ReturnType
CanIf_CancelTransmit(PduIdType CanTxPduId)
{
	Std_ReturnType	ercd = E_OK;
#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
	const LPDU_INIB	*p_lpdu_inib;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF652] */
	CANIF_CHECK_PARAM_ERCD(CanTxPduId < GET_LPDU_NUM(), CanIfServiceId_CancelTransmit, CANIF_E_INVALID_TXPDUID);

	p_lpdu_inib = GET_LPDU_INIB(CanTxPduId);

	/* [CANIF652] */
	CANIF_CHECK_PARAM_ERCD(p_lpdu_inib->lpdu_direction == CANIF_SEND, CanIfServiceId_CancelTransmit, CANIF_E_INVALID_TXPDUID);

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */

	/* CanIf_CancelTransmitに機能はない */

	return(ercd);
}
#endif /* CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON */

/*
 *  [CANIF194] CanIf_ReadRxPduData
 */
/* [CANIF330] CANIF_PUBLIC_READRXPDU_DATA_APIがSTD_ONならば，本システムサービスは有効 */
#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
Std_ReturnType
CanIf_ReadRxPduData(PduIdType CanRxPduId, PduInfoType *PduInfoPtr)
{
	const LPDU_INIB	*p_lpdu_inib;
	CANIF_CTRL_CB	*p_canif_ctrl_cb;
	Std_ReturnType	ercd;
	uint8			i;

	/* [CANIF064][CANIF199] */
	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF329] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_ReadRxPduData);
	/* [CANIF325] */
	CANIF_CHECK_PARAM_ERCD((CanRxPduId < GET_LPDU_NUM()), CanIfServiceId_ReadRxPduData, CANIF_E_INVALID_RXPDUID);
	/* [CANIF326] */
	CANIF_CHECK_NULL_POINTER_ERCD((PduInfoPtr != NULL_PTR), CanIfServiceId_ReadRxPduData);

	p_lpdu_inib = GET_LPDU_INIB(CanRxPduId);

	/* [CANIF325] */
	CANIF_CHECK_PARAM_ERCD(p_lpdu_inib->lpdu_direction == CANIF_RECEIVE, CanIfServiceId_ReadRxPduData, CANIF_E_INVALID_RXPDUID);

	/* [CANIF325] 受信バッファが構成されてない*/
	CANIF_CHECK_PARAM_ERCD((p_lpdu_inib->p_rx_lpdu_buffer != NULL_PTR), CanIfServiceId_ReadRxPduData, CANIF_E_INVALID_RXPDUID);

	/* [CANIFa001] 対象のPDUを一度も受信してない場合は何も処理せず，E_NOT_OKを返す */
	CANIF_CHECK_PARAM_ERCD((p_lpdu_inib->p_rx_indication_flg != NULL_PTR), CanIfServiceId_ReadRxPduData, CANIF_E_PARAM_POINTER);
	D_CANIF_CHECK_PARAM_ERCD(*(p_lpdu_inib->p_rx_indication_flg) == TRUE);

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

	/*
	 *  [CANIF324]
	 *  CCMSMがCANIF_CS_STARTEDではない場合，またはPDUチャネルモードが受信パスオンライン
	 *  (CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE，CANIF_GET_ONLINE，CANIF_GET_RX_ONLINE)ではない場合はE_NOT_OKを返す
	 */
	D_CANIF_CHECK_PARAM_ERCD(p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED);
	D_CANIF_CHECK_PARAM_ERCD((p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_RX_ONLINE));

	/* [CANIF058] 受信バッファ，DLCを渡す */
	for (i = 0U; i < p_lpdu_inib->CanIfPduDlc; i++) {
		(PduInfoPtr->SduDataPtr)[i] = (p_lpdu_inib->p_rx_lpdu_buffer)[i];
	}
	PduInfoPtr->SduLength = p_lpdu_inib->CanIfPduDlc;

	ercd = E_OK;

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

/*
 *  [CANIF202] CanIf_ReadTxNotifStatus
 */
/* [CANIF335] CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_APIがSTD_ONならば，本システムサービスは有効 */
#if CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON
CanIf_NotifStatusType
CanIf_ReadTxNotifStatus(PduIdType CanTxPduId)
{
	const LPDU_INIB			*p_lpdu_inib;
	CanIf_NotifStatusType	status;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF334] */
	CANIF_CHECK_INITIALIZED(CanIfServiceId_ReadTxNotifStatus);
	/* [CANIF331] */
	CANIF_CHECK_PARAM((CanTxPduId < GET_LPDU_NUM()), CanIfServiceId_ReadTxNotifStatus, CANIF_E_INVALID_TXPDUID);

	p_lpdu_inib = GET_LPDU_INIB(CanTxPduId);

	/* [CANIF331] */
	CANIF_CHECK_PARAM(p_lpdu_inib->lpdu_direction == CANIF_SEND, CanIfServiceId_ReadTxNotifStatus, CANIF_E_INVALID_TXPDUID);

	/* [CANIF331] ステータス情報が構成されてない場合，エラーとする */
	CANIF_CHECK_PARAM((p_lpdu_inib->p_notify_status != NULL_PTR), CanIfServiceId_ReadTxNotifStatus, CANIF_E_INVALID_TXPDUID);

	status = *(p_lpdu_inib->p_notify_status);

	/* [CANIF393] LPDUの通知ステータスをリセットする */
	*(p_lpdu_inib->p_notify_status) = CANIF_NO_NOTIFICATION;

  no_error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(status);

  error_exit:
	status = CANIF_NO_NOTIFICATION;
	goto no_error_exit;
}
#endif /* CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON */

/*
 *  [CANIF230] CanIf_ReadRxNotifStatus
 */
/* [CANIF340] CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_APIがSTD_ONならば，本システムサービスは有効 */
#if CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON
CanIf_NotifStatusType
CanIf_ReadRxNotifStatus(PduIdType CanRxPduId)
{
	const LPDU_INIB			*p_lpdu_inib;
	CanIf_NotifStatusType	status;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF339] */
	CANIF_CHECK_INITIALIZED(CanIfServiceId_ReadRxNotifStatus);
	/* [CANIF336] */
	CANIF_CHECK_PARAM((CanRxPduId < GET_LPDU_NUM()), CanIfServiceId_ReadRxNotifStatus, CANIF_E_INVALID_RXPDUID);

	p_lpdu_inib = GET_LPDU_INIB(CanRxPduId);

	/* [CANIF336] */
	CANIF_CHECK_PARAM(p_lpdu_inib->lpdu_direction == CANIF_RECEIVE, CanIfServiceId_ReadRxNotifStatus, CANIF_E_INVALID_RXPDUID);

	/* [CANIF336] CANIF_READRXPDU_DATA_APIが無効の場合，エラーとする */
	CANIF_CHECK_PARAM((CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON), CanIfServiceId_ReadRxNotifStatus, CANIF_E_INVALID_RXPDUID);
	/* [CANIF336] ステータス情報が構成されてない場合，エラーとする */
	CANIF_CHECK_PARAM((p_lpdu_inib->p_notify_status != NULL_PTR), CanIfServiceId_ReadRxNotifStatus, CANIF_E_INVALID_RXPDUID);

	status = *(p_lpdu_inib->p_notify_status);

	/* [CANIF394] LPDUの通知ステータスをリセットする */
	*(p_lpdu_inib->p_notify_status) = CANIF_NO_NOTIFICATION;

  no_error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(status);

  error_exit:
	status = CANIF_NO_NOTIFICATION;
	goto no_error_exit;
}
#endif /* CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON */

/*
 *  [CANIF008] CanIf_SetPduMode
 */
Std_ReturnType
CanIf_SetPduMode(uint8 ControllerId, CanIf_PduSetModeType PduModeRequest)
{
	/* PDUチャネルモードテーブル */
	CanIf_PduGetModeType	pdu_mode_table[6][7] = {
		{ CANIF_GET_OFFLINE, CANIF_GET_ONLINE, CANIF_GET_OFFLINE,        CANIF_GET_RX_ONLINE,                CANIF_GET_OFFLINE,   CANIF_GET_OFFLINE_ACTIVE,           CANIF_GET_TX_ONLINE },
		{ CANIF_GET_OFFLINE, CANIF_GET_ONLINE, CANIF_GET_OFFLINE_ACTIVE, CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE, CANIF_GET_OFFLINE,   CANIF_GET_OFFLINE_ACTIVE,           CANIF_GET_TX_ONLINE },
		{ CANIF_GET_OFFLINE, CANIF_GET_ONLINE, CANIF_GET_OFFLINE_ACTIVE, CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE, CANIF_GET_RX_ONLINE, CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE, CANIF_GET_ONLINE },
		{ CANIF_GET_OFFLINE, CANIF_GET_ONLINE, CANIF_GET_TX_ONLINE,      CANIF_GET_ONLINE,                   CANIF_GET_RX_ONLINE, CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE, CANIF_GET_ONLINE },
		{ CANIF_GET_OFFLINE, CANIF_GET_ONLINE, CANIF_GET_OFFLINE,        CANIF_GET_RX_ONLINE,                CANIF_GET_RX_ONLINE, CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE, CANIF_GET_ONLINE },
		{ CANIF_GET_OFFLINE, CANIF_GET_ONLINE, CANIF_GET_TX_ONLINE,      CANIF_GET_ONLINE,                   CANIF_GET_OFFLINE,   CANIF_GET_OFFLINE_ACTIVE,           CANIF_GET_TX_ONLINE }
	};

	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	Std_ReturnType			ercd;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF344] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_SetPduMode);
	/* [CANIF341] */
	CANIF_CHECK_PARAM_ERCD(ControllerId < GET_CANIF_CTRL_NUM(), CanIfServiceId_SetPduMode, CANIF_E_PARAM_CONTROLLERID);

	p_canif_ctrl_cb = GET_CANIF_CTRL_CB(ControllerId);

	/* PDUチャネルモードを設定する */
	p_canif_ctrl_cb->pdu_mode = pdu_mode_table[p_canif_ctrl_cb->pdu_mode][PduModeRequest];
	ercd = E_OK;

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}

/*
 *  [CANIF009] CanIf_GetPduMode
 */
Std_ReturnType
CanIf_GetPduMode(uint8 ControllerId, CanIf_PduGetModeType *PduModePtr)
{
	CANIF_CTRL_CB	*p_canif_ctrl_cb;
	Std_ReturnType	ercd;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF349] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_SetPduMode);
	/* [CANIF346] */
	CANIF_CHECK_PARAM_ERCD(ControllerId < GET_CANIF_CTRL_NUM(), CanIfServiceId_GetPduMode, CANIF_E_PARAM_CONTROLLERID);
	/* [CANIF657] */
	CANIF_CHECK_NULL_POINTER_ERCD(PduModePtr != NULL_PTR, CanIfServiceId_GetPduMode);

	p_canif_ctrl_cb = GET_CANIF_CTRL_CB(ControllerId);

	/* 現在のPDUチャネルモードを取得する */
	*PduModePtr = p_canif_ctrl_cb->pdu_mode;
	ercd = E_OK;

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}

/*
 *  [CANIF158] CanIf_GetVersionInfo
 */
/* [CANIF351] */
#if CANIF_PUBLIC_VERSION_INFO_API == STD_ON
void
CanIf_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{
	/* [CANIF658] */
	CANIF_CHECK_NULL_POINTER(VersionInfo != NULL_PTR, CanIfServiceId_GetVersionInfo);

	/* [CANIF350] */
	VersionInfo->vendorID = CANIF_VENDOR_ID;
	VersionInfo->moduleID = CANIF_MODULE_ID;
	VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION;
	VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION;
	VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION;

  error_exit:
	return;
}
#endif /* CANIF_PUBLIC_VERSION_INFO_API == STD_ON */

/*
 *  [CANIF219] CanIf_CheckWakeup
 */
Std_ReturnType
CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	Std_ReturnType			ercd = E_NOT_OK;     /* [CANIF678] */
	uint16					i;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF401] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_CheckWakeup);

	for (i = 0U; i < GET_CANIF_CTRL_NUM(); i++) {
		p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(i);

		/* [CANIF180][CANIF402] CanIfCtrlWakeupSupportが有効の場合，EcuMWakeupSourceIdに一致するコントローラを検出する */
		if (((((uint32) 0x00000001) << p_canif_ctrl_inib->EcuMWakeupSourceId) & WakeupSource) != ((uint32) 0x00000000)) {
			if (p_canif_ctrl_inib->CanIfCtrlWakeupSupport == TRUE) {
				p_canif_ctrl_cb = p_canif_ctrl_inib->p_canif_ctrl_cb;

				/* [CANIF679] */
				C_CANIF_CHECK_PARAM_ERCD(p_canif_ctrl_cb->controller_mode == CANIF_CS_SLEEP, CanIfServiceId_CheckWakeup, CANIF_E_NOT_SLEEP);

				/* [CANIF395] */
				if (Can_CheckWakeup(p_canif_ctrl_inib->CanControllerId) == CAN_OK) {
					/* [CANIF720] */
					ercd = E_OK;
				}
			}
			/* EcuMWakeupSourceIdに一致するコントローラが見つかった場合，処理を抜ける */
			break;
		}
	}

	/* [CANIF398] */
	CANIF_CHECK_PARAM_ERCD(ercd != E_NOT_OK, CanIfServiceId_CheckWakeup, CANIF_E_PARAM_WAKEUPSOURCE);

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}

/*
 *  [CANIF734][CANIF563][CANIF178] CanIf_CheckValidation
 */
/* [CANIF408][CANIF226][CANIF659] */
#if CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON
Std_ReturnType
CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	const CanIf_ConfigType	*p_saved_config;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	uint16					i;
	Std_ReturnType			ercd = E_NOT_OK;

	/* [CANIF455] */
	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF455][CANIF407] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_CheckValidation);

	for (i = 0U; i < GET_CANIF_CTRL_NUM(); i++) {
		p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(i);

		/* EcuMWakeupSourceIdに一致するコントローラを検出 */
		if (((((uint32) 0x00000001) << p_canif_ctrl_inib->EcuMWakeupSourceId) & WakeupSource) != ((uint32) 0x00000000)) {
			p_canif_ctrl_cb = p_canif_ctrl_inib->p_canif_ctrl_cb;

			/* [CANIF407] */
			D_CANIF_CHECK_PARAM_ERCD(p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED);

			/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
			p_saved_config = p_cur_canif_config;

			/* CANメッセージを受信した場合 */
			if (p_canif_ctrl_cb->validation_status != FALSE) {
				/* [CANIF179][CANIF532] */
				SchM_Exit_CanIf_Reentrant_0();
				CanIfDispatchUserValidateWakeupEventName(WakeupSource);
				SchM_Enter_CanIf_Reentrant_0();
			}
			else {
				/* [CANIF681][CANIF532] CANメッセージを受信してない場合は，WakeupSourceの全ビットをクリアして送信する */
				SchM_Exit_CanIf_Reentrant_0();
				CanIfDispatchUserValidateWakeupEventName(0U);
				SchM_Enter_CanIf_Reentrant_0();
			}

			ercd = E_OK;

			/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
			CANIF_CHECK_PARAM_ERCD(p_saved_config == p_cur_canif_config, CanIfServiceId_CheckValidation, CANIF_E_FATAL);

			break;
		}
	}

	/* [CANIF404] */
	CANIF_CHECK_PARAM_ERCD(ercd != E_NOT_OK, CanIfServiceId_CheckWakeup, CANIF_E_PARAM_WAKEUPSOURCE);

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}
#endif /* CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON */

/*
 *  [CANIF734] CanIf_GetTxConfirmationState
 */
/* [CANIF738] */
#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
CanIf_NotifStatusType
CanIf_GetTxConfirmationState(uint8 ControllerId)
{
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	CanIf_NotifStatusType	status;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF737] */
	CANIF_CHECK_INITIALIZED(CanIfServiceId_GetTxConfirmationState);
	/* [CANIF736] */
	CANIF_CHECK_PARAM(ControllerId < GET_CANIF_CTRL_NUM(), CanIfServiceId_GetTxConfirmationState, CANIF_E_PARAM_CONTROLLERID);

	p_canif_ctrl_cb = GET_CANIF_CTRL_CB(ControllerId);

	if (p_canif_ctrl_cb->tx_confirmation_flg == TRUE) {
		status = CANIF_TX_RX_NOTIFICATION;
	}
	else {
		status = CANIF_NO_NOTIFICATION;
	}

  no_error_exit:
	return(status);

  error_exit:
	status = CANIF_NO_NOTIFICATION;
	SchM_Exit_CanIf_Reentrant_0();
	goto no_error_exit;
}
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */

/*
 *  [CANIF775] CanIf_CheckBaudrate
 */
/* [CANIF780] CANIF_PUBLIC_CHANGE_BAUDRATE_SUPPORTがSTD_OFFの場合は，CanIf_CheckBaudrateも無効にする */
#if CANIF_PUBLIC_CHANGE_BAUDRATE_SUPPORT == STD_ON
Std_ReturnType
CanIf_CheckBaudrate(uint8 ControllerId, const uint16 Baudrate)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	Std_ReturnType			ercd;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF779] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_CheckBaudrate);
	/* [CANIF778] */
	CANIF_CHECK_PARAM_ERCD(ControllerId < GET_CANIF_CTRL_NUM(), CanIfServiceId_CheckBaudrate, CANIF_E_PARAM_CONTROLLERID);

	p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(ControllerId);

	/* [CANIF786] */
	ercd = Can_CheckBaudrate(p_canif_ctrl_inib->CanControllerId, Baudrate);

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}
#endif /* CANIF_PUBLIC_CHANGE_BAUDRATE_SUPPORT == STD_ON */

/*
 *  [CANIF776] CanIf_ChangeBaudrate
 */
/* [CANIF784] */
#if CANIF_PUBLIC_CHANGE_BAUDRATE_SUPPORT == STD_ON
Std_ReturnType
CanIf_ChangeBaudrate(uint8 ControllerId, const uint16 Baudrate)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	Std_ReturnType			ercd;

	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF783] */
	CANIF_CHECK_INITIALIZED_ERCD(CanIfServiceId_ChangeBaudrate);
	/* [CANIF782] */
	CANIF_CHECK_PARAM_ERCD(ControllerId < GET_CANIF_CTRL_NUM(), CanIfServiceId_ChangeBaudrate, CANIF_E_PARAM_CONTROLLERID);

	p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(ControllerId);

	/* [CANIF787] */
	ercd = Can_ChangeBaudrate(p_canif_ctrl_inib->CanControllerId, Baudrate);

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return(ercd);
}
#endif /* CANIF_PUBLIC_CHANGE_BAUDRATE_SUPPORT == STD_ON */

/*
 *  [CANIF007] CanIf_TxConfirmation
 */
void
CanIf_TxConfirmation(PduIdType CanTxPduId)
{
	const LPDU_INIB			*p_lpdu_inib;
	const CanIf_ConfigType	*p_saved_config;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	User_TxConfirmation		TxConfirmation;     /* [CANIF011][CANIF437] */
	PduIdType				pduid;

	SchM_Enter_CanIf_Reentrant_1();

	/* [CANIF412][CANIF413] */
	CANIF_CHECK_INITIALIZED(CanIfServiceId_TxConfirmation);
	/* [CANIF410] */
	CANIF_CHECK_PARAM(CanTxPduId < GET_LPDU_NUM(), CanIfServiceId_TxConfirmation, CANIF_E_PARAM_LPDU);

	p_lpdu_inib = GET_LPDU_INIB(CanTxPduId);

	/* [CANIF410] */
	CANIF_CHECK_PARAM(p_lpdu_inib->lpdu_direction == CANIF_SEND, CanIfServiceId_TxConfirmation, CANIF_E_PARAM_LPDU);

#if CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON
	/* [CANIF391][CANIF472] LPDUの通知ステータスを設定する*/
	if (p_lpdu_inib->p_notify_status != NULL_PTR) {
		*(p_lpdu_inib->p_notify_status) = CANIF_TX_RX_NOTIFICATION;
	}
#endif /* CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON */

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	/* [CANIF740] TxConfirmationが呼ばれたことを保持する */
	p_canif_ctrl_cb->tx_confirmation_flg = TRUE;
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */

	/*
	 *  [CANIF073][CANIF489][CANIF075][CANIF491]
	 *  送信パスがオンラインまたはオンラインアクティブの場合，上位レイヤへの送信コンファメ―ションサービスを呼び出す
	 */
	D_CANIF_CHECK_PARAM((p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_TX_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE));

	if (p_lpdu_inib->CanIfPduUserConfirmationName != NULL_PTR) {
		/* 排他エリア内で各情報を取り出す */
		TxConfirmation = ((User_TxConfirmation) p_lpdu_inib->CanIfPduUserConfirmationName);
		pduid = p_lpdu_inib->PduRPduHandleId;
		/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
		p_saved_config = p_cur_canif_config;

		/* [CANIF383][CANIF414] 送信コンファメーションコールバック*/
		SchM_Exit_CanIf_Reentrant_1();
		TxConfirmation(pduid);
		SchM_Enter_CanIf_Reentrant_1();

		/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
		CANIF_CHECK_PARAM(p_saved_config == p_cur_canif_config, CanIfServiceId_TxConfirmation, CANIF_E_FATAL);
	}

  error_exit:
	SchM_Exit_CanIf_Reentrant_1();
	return;
}

/*
 *  [CANIF006][NCANIF002] CanIf_RxIndication
 */
void
CanIf_RxIndication(Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, uint8 *CanSduPtr)
{
	const LPDU_INIB			*p_lpdu_inib;
	const CanIf_ConfigType	*p_saved_config;
	User_RxIndication		RxIndication;   /* [CANIF012] */
	PduInfoType				pduinfo;
	PduIdType				pduid;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
	uint8					i;
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

	/* [CANIF064][CANIF199][CANIF440] */
	SchM_Enter_CanIf_Reentrant_0();

	/* [CANIF421][CANIF422][CANIF440] */
	CANIF_CHECK_INITIALIZED(CanIfServiceId_RxIndication);
	/* [CANIF416] */
	CANIF_CHECK_PARAM((Hrh < GET_LPDU_NUM()), CanIfServiceId_RxIndication, CANIF_E_PARAM_HRH);
#if 0
	/* [CANIF418] */
	CANIF_CHECK_PARAM((CanDlc <= DLC_MAX), CanIfServiceId_RxIndication, CANIF_E_PARAM_DLC);
#endif
	/* [CANIF419] */
	CANIF_CHECK_NULL_POINTER((CanSduPtr != NULL_PTR), CanIfServiceId_RxIndication);

	p_lpdu_inib = GET_LPDU_INIB_HOH(Hrh);

	/* [CANIF416] */
	CANIF_CHECK_PARAM(p_lpdu_inib->lpdu_direction == CANIF_RECEIVE, CanIfServiceId_RxIndication, CANIF_E_PARAM_HRH);

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

	/* [CANIF417] */
	CANIF_CHECK_PARAM((CanId == p_lpdu_inib->CanIfPduCanId), CanIfServiceId_RxIndication, CANIF_E_PARAM_CANID);

	/* DLCチェック */
	/* [CANIF390][CANIF026][CANIF168] */
	A_CHECK_DLC(CanDlc, p_lpdu_inib->CanIfPduDlc);

	/* 受信LPDUのバッファリング */
#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
	if (p_lpdu_inib->p_rx_lpdu_buffer != NULL_PTR) {
		/* [CANIF198][CANIF297] */
		for (i = 0U; i < p_lpdu_inib->CanIfPduDlc; i++) {
			(p_lpdu_inib->p_rx_lpdu_buffer)[i] = CanSduPtr[i];
		}
	}
	/* [CANIFa001] 受信したのでp_tx_rx_flgをTRUEにする */
	CANIF_CHECK_PARAM((p_lpdu_inib->p_rx_indication_flg != NULL_PTR), CanIfServiceId_RxIndication, CANIF_E_PARAM_POINTER);
	*(p_lpdu_inib->p_rx_indication_flg) = TRUE;
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

#if CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON
	if (p_lpdu_inib->p_notify_status != NULL_PTR) {
		/* [CANIF392][CANIF473] 通知ステータスを設定する */
		*(p_lpdu_inib->p_notify_status) = CANIF_TX_RX_NOTIFICATION;
	}
#endif /* CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API = STD_ON */

#if CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON
	if (p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED) {
		/* [CANIF286] 対象のコントローラに対して，CCMSMがCANIF_CS_STARTEDであれば，CanIf_RxIndicationが呼ばれたことを保持する */
		p_canif_ctrl_cb->validation_status = TRUE;
	}
#endif /* CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON */

	/*
	 *  [CANIF073][CANIF490][CANIF492][CANIF075][CANIF492][CANIF490]
	 *  受信パスがオンラインの場合，上位レイヤへの受信通知システムサービスを呼び出す
	 */
	D_CANIF_CHECK_PARAM((p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_RX_ONLINE));

	if (p_lpdu_inib->CanIfPduUserConfirmationName != NULL_PTR) {
		/* 排他エリア内で各情報を取り出す */
		pduid = p_lpdu_inib->PduRPduHandleId;
		/* [CANIF056] 上位レイヤへの受信通知システムサービス呼び出し */
		RxIndication = ((User_RxIndication) p_lpdu_inib->CanIfPduUserConfirmationName);
		/* [CANIF057][CANIF135] PDU情報設定 */
		pduinfo.SduDataPtr = CanSduPtr;
		/* [CANIF829][CANIF830] 受信したDLCを上位レイヤモジュールに渡す */
		pduinfo.SduLength = CanDlc;
		/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
		p_saved_config = p_cur_canif_config;

		/* [CANIF423][CANIF012][CANIF415][CANIF830] */
		SchM_Exit_CanIf_Reentrant_0();
		RxIndication(pduid, &pduinfo);
		SchM_Enter_CanIf_Reentrant_0();

		/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
		CANIF_CHECK_PARAM(p_saved_config == p_cur_canif_config, CanIfServiceId_RxIndication, CANIF_E_FATAL);
	}

  error_exit:
	SchM_Exit_CanIf_Reentrant_0();
	return;
}

/*
 *  [CANIF218] CanIf_ControllerBusOff
 */
void
CanIf_ControllerBusOff(uint8 ControllerId)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	const CanIf_ConfigType	*p_saved_config;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	uint8					ctrl_id;

	/* [CANIF449] */
	SchM_Enter_CanIf_Reentrant_1();

	/* [CANIF432][CANIF431][CANIF449] */
	CANIF_CHECK_INITIALIZED(CanIfServiceId_ControllerBusOff);
	/* [CANIF429] */
	CANIF_CHECK_PARAM((ControllerId < GET_CANIF_CTRL_NUM()), CanIfServiceId_ControllerBusOff, CANIF_E_PARAM_CONTROLLERID);

	p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(ControllerId);
	p_canif_ctrl_cb = p_canif_ctrl_inib->p_canif_ctrl_cb;

	/* [CANIF298][CANIF488] CCMSMをCANIF_CS_STOPPEDにする */
	p_canif_ctrl_cb->controller_mode = CANIF_CS_STOPPED;

	/* 排他エリア内でコントローラIDを取り出す */
	ctrl_id = p_canif_ctrl_inib->CanControllerId;
	/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
	p_saved_config = p_cur_canif_config;

	/* [CANIF724][CANIF014][CANIF433] */
	SchM_Exit_CanIf_Reentrant_1();
	CanIfDispatchUserCtrlBusOffName(ctrl_id);
	SchM_Enter_CanIf_Reentrant_1();

	/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
	CANIF_CHECK_PARAM(p_saved_config == p_cur_canif_config, CanIfServiceId_ControllerBusOff, CANIF_E_FATAL);

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	/* [CANIF739] TxConfirmationに関する情報を消去する */
	p_canif_ctrl_cb->tx_confirmation_flg = FALSE;
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */

  error_exit:
	SchM_Exit_CanIf_Reentrant_1();
	return;
}

/*
 *  [CANIF699] CanIf_ControllerModeIndication
 */
void
CanIf_ControllerModeIndication(uint8 ControllerId, CanIf_ControllerModeType ControllerMode)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	const CanIf_ConfigType	*p_saved_config;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;
	uint8					ctrl_id;

	/* [CANIF688] */
	SchM_Enter_CanIf_Reentrant_1();

	/* [CANIF703][CANIF702][CANIF688] */
	CANIF_CHECK_INITIALIZED(CanIfServiceId_ControllerModeIndication);
	/* [CANIF700] */
	CANIF_CHECK_PARAM((ControllerId < GET_CANIF_CTRL_NUM()), CanIfServiceId_ControllerModeIndication, CANIF_E_PARAM_CONTROLLERID);

	p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(ControllerId);
	p_canif_ctrl_cb = p_canif_ctrl_inib->p_canif_ctrl_cb;

	/* [CANIF713][CANIF714][CANIF715][CANIF716][CANIF717][CANIF718][CANIF719] */
	/* 通知されたCCMSMを設定する */
	p_canif_ctrl_cb->controller_mode = ControllerMode;

#if CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON
	if (ControllerMode == CANIF_CS_SLEEP) {
		/* [CANIF756] CANIF_CS_SLEEPの場合，対象のコントローラに対して，CanIf_RxIndicationが呼ばれたことがクリアされる */
		p_canif_ctrl_cb->validation_status = FALSE;
	}
#endif /* CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON */

	/* 排他エリア内でコントローラIDを取り出す */
	ctrl_id = p_canif_ctrl_inib->CanControllerId;
	/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
	p_saved_config = p_cur_canif_config;

	/* [CANIF711][CANIF704][CANIF687] */
	SchM_Exit_CanIf_Reentrant_1();
	CanIfDispatchUserCtrlModeIndicationName(ctrl_id, ControllerMode);
	SchM_Enter_CanIf_Reentrant_1();

	/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
	CANIF_CHECK_PARAM(p_saved_config == p_cur_canif_config, CanIfServiceId_ControllerModeIndication, CANIF_E_FATAL);

  error_exit:
	SchM_Exit_CanIf_Reentrant_1();
	return;
}

/*
 *  以下，未サポート機能
 */

/* <CANIF101> */
void
CanIf_CancelTxConfirmation(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr)
{
	return;
}
/* <CANIF189> */
void
CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId)
{
	return;
}
/* <CANIF287> */
Std_ReturnType
CanIf_SetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{
	return(E_OK);
}
/* <CANIF288> */
Std_ReturnType
CanIf_GetTrcvMode(CanTrcv_TrcvModeType *TransceiverModePtr, uint8 TransceiverId)
{
	return(E_OK);
}
/* <CANIF289> */
Std_ReturnType
CanIf_GetTrcvWakeupReason(uint8 TransceiverId, CanTrcv_TrcvWakeupReasonType *TrcvWuReasonPtr)
{
	return(E_OK);
}
/* <CANIF290> */
Std_ReturnType
CanIf_SetTrcvWakeupMode(uint8 TransceiverId, CanTrcv_TrcvWakeupModeType TrcvWakeupMode)
{
	return(E_OK);
}
/* <CANIF760> */
Std_ReturnType
CanIf_ClearTrcvWufFlag(uint8 TransceiverId)
{
	return(E_OK);
}
/* <CANIF761> */
Std_ReturnType
CanIf_CheckTrcvWakeFlag(uint8 TransceiverId)
{
	return(E_OK);
}
/* <CANIF764> */
void
CanIf_TrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{
	return;
}
