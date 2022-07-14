/*
 *  TOPPERS/A-CANIF
 *      Automotive CANIF
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
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
 *  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
 *  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
 *  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 *  $Id: CanIf.c 1241 2015-03-25 07:26:02Z panasonic-ayane $
 */

/* CanIf.c */
#include "CanIf.h"      /* [CANIF116][CANIF122] */
#include "CanIf_Cbk.h"  /* [CANIF121][CANIF409] */

#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
#include "Det.h"        /* [CANIF464][CANIF294] */
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */

#include "Dem.h"        /* [CANIF020][CANIF150][CANIF153][CANIF155][CANIF223] */
#include "MemMap.h"     /* [CANIF278][CANIF463] */

/* PduR_CanIf.h��PduR�����ͥ졼���ˤ����������� */
#include "PduR_CanIf.h" /* [CANIF208] */
/* SchM_CanIf.h��RTE�����ͥ졼���ˤ����������� */
#include "SchM_CanIf.h" /* [CANIF208][CANIF040] */


/*
 *  ���߼¹����CanIf����ե�����졼��������
 */
static const CanIf_ConfigType	*p_cur_canif_config;
static const CANIF_CTRL_INIB	*p_cur_canif_ctrl_inib;
static const LPDU_INIB			*p_cur_lpdu_inib;
static const LPDU_INIB			* const *pp_cur_lpdu_inib_hoh;

/*
 *  CanIf�ν��������
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
	 *  [CANIF302] �����ʥݥ��󥿤ؤ��б��ϡ�NULL_PTR���Ф��ƤΤ߹Ԥ�
	 */
	if (ConfigPtr == NULL_PTR) {
		/* [CANIF301] NULL_PTR�ξ�硤�ǥե���ȤΥ���ե�����졼�����������Ѥ��� */
		ConfigPtr = p_default_canif_config;
	}

	/* ���߼¹���Υ���ե����졼����������ݻ� */
	p_cur_canif_config = ConfigPtr;
	p_cur_canif_ctrl_inib = canif_ctrl_inib_table;
	p_cur_lpdu_inib = ConfigPtr->p_lpdu_inib_table;
	pp_cur_lpdu_inib_hoh = ConfigPtr->pp_lpdu_inib_hoh_list;

	/* [CANIF085] CanIf�Υ����Х��ѿ��ȥǡ�����¤������ */
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
	 *  CanIf�ϴ�����CAN����ȥ��饹�ơ��ȥޥ���ϴޤ�Ǥ��ʤ�
	 *
	 *  CanIf�ǳ�ǧ�Ǥ���CCMSM�⡼�ɤ�CANIF_CS_UNINIT��CANIF_CS_STOPPED��CANIF_CS_STARTED�������CANIF_CS_SLEEP�ΤߤǤ��ꡤ
	 *  ����¾��CCMSM����(CANIF_CS_START_TO_SLEEP��CANIF_CS_SLEEP_TO_START)�ϴޤޤʤ���
	 */

	/* [CANIF308] CAN����ȥ�����Ф���Can_SetControllerMode��ƤӽФ� */
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
		/* [CANIF475] Can_SetControllerMode��CAN_NOT_OK���֤�����硤CanIf_SetControllerMode��E_NOT_OK���֤� */
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

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

	/* [CANIF317][CANIF723][CANIF677] */
	C_CANIF_CHECK_PARAM_ERCD(p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED, CanIfServiceId_Transmit, CANIF_E_STOPPED);

	/* [CANIF382][CANIF073][CANIF489] */
	C_CANIF_CHECK_PARAM_ERCD((p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_TX_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE), CanIfServiceId_Transmit, CANIF_E_STOPPED);

	/* [CANIF075][CANIF491] PDU����ͥ�⡼�ɤ�CANIF_GET_ONLINE��CANIF_GET_TX_ONLINE�ξ�� */
	if ((p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) || (p_canif_ctrl_cb->pdu_mode == CANIF_GET_TX_ONLINE)) {
		/* CAN PDU��¤������ */
		PduInfo.id = p_lpdu_inib->CanIfPduCanId;
		PduInfo.swPduHandle = CanTxPduId;
		PduInfo.sdu = PduInfoPtr->SduDataPtr;
		PduInfo.length = ((uint8) PduInfoPtr->SduLength);

		/* [CANIF318] ��å������񤭹��� */
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
		 * [CANIF072] PDU����ͥ�⡼�ɤ�CANIF_GET_OFFLINE_ACTIVE��CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE�ξ�硤
		 *            ��������ե��᡼����󥳡���Хå���ƤӽФ�
		 */
		if (p_lpdu_inib->CanIfPduUserConfirmationName != NULL_PTR) {
			/* ��¾���ꥢ��ǳƾ������Ф� */
			TxConfirmation = ((User_TxConfirmation) p_lpdu_inib->CanIfPduUserConfirmationName);
			pduid = p_lpdu_inib->PduRPduHandleId;
			/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
			p_saved_config = p_cur_canif_config;

			SchM_Exit_CanIf_Reentrant_0();
			TxConfirmation(pduid);
			SchM_Enter_CanIf_Reentrant_0();

			/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
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

	/* CanIf_CancelTransmit�˵�ǽ�Ϥʤ� */

	return(ercd);
}
#endif /* CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON */

/*
 *  [CANIF194] CanIf_ReadRxPduData
 */
/* [CANIF330] CANIF_PUBLIC_READRXPDU_DATA_API��STD_ON�ʤ�С��ܥ����ƥॵ���ӥ���ͭ�� */
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

	/* [CANIF325] �����Хåե�����������Ƥʤ� */
	CANIF_CHECK_PARAM_ERCD((p_lpdu_inib->p_rx_lpdu_buffer != NULL_PTR), CanIfServiceId_ReadRxPduData, CANIF_E_INVALID_RXPDUID);

	/* [CANIFa001] �оݤ�PDU����٤�������Ƥʤ����ϲ������������E_NOT_OK���֤� */
	CANIF_CHECK_PARAM_ERCD((p_lpdu_inib->p_rx_indication_flg != NULL_PTR), CanIfServiceId_ReadRxPduData, CANIF_E_PARAM_POINTER);
	D_CANIF_CHECK_PARAM_ERCD(*(p_lpdu_inib->p_rx_indication_flg) == TRUE);

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

	/*
	 *  [CANIF324]
	 *  CCMSM��CANIF_CS_STARTED�ǤϤʤ���硤�ޤ���PDU����ͥ�⡼�ɤ������ѥ�����饤��
	 *  (CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE��CANIF_GET_ONLINE��CANIF_GET_RX_ONLINE)�ǤϤʤ�����E_NOT_OK���֤�
	 */
	D_CANIF_CHECK_PARAM_ERCD(p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED);
	D_CANIF_CHECK_PARAM_ERCD((p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
							 (p_canif_ctrl_cb->pdu_mode == CANIF_GET_RX_ONLINE));

	/* [CANIF058] �����Хåե���DLC���Ϥ� */
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
/* [CANIF335] CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API��STD_ON�ʤ�С��ܥ����ƥॵ���ӥ���ͭ�� */
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

	/* [CANIF331] ���ơ��������󤬹�������Ƥʤ���硤���顼�Ȥ��� */
	CANIF_CHECK_PARAM((p_lpdu_inib->p_notify_status != NULL_PTR), CanIfServiceId_ReadTxNotifStatus, CANIF_E_INVALID_TXPDUID);

	status = *(p_lpdu_inib->p_notify_status);

	/* [CANIF393] LPDU�����Υ��ơ�������ꥻ�åȤ��� */
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
/* [CANIF340] CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API��STD_ON�ʤ�С��ܥ����ƥॵ���ӥ���ͭ�� */
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

	/* [CANIF336] CANIF_READRXPDU_DATA_API��̵���ξ�硤���顼�Ȥ��� */
	CANIF_CHECK_PARAM((CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON), CanIfServiceId_ReadRxNotifStatus, CANIF_E_INVALID_RXPDUID);
	/* [CANIF336] ���ơ��������󤬹�������Ƥʤ���硤���顼�Ȥ��� */
	CANIF_CHECK_PARAM((p_lpdu_inib->p_notify_status != NULL_PTR), CanIfServiceId_ReadRxNotifStatus, CANIF_E_INVALID_RXPDUID);

	status = *(p_lpdu_inib->p_notify_status);

	/* [CANIF394] LPDU�����Υ��ơ�������ꥻ�åȤ��� */
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
	/* PDU����ͥ�⡼�ɥơ��֥� */
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

	/* PDU����ͥ�⡼�ɤ����ꤹ�� */
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

	/* ���ߤ�PDU����ͥ�⡼�ɤ�������� */
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

		/* [CANIF180][CANIF402] CanIfCtrlWakeupSupport��ͭ���ξ�硤EcuMWakeupSourceId�˰��פ��륳��ȥ���򸡽Ф��� */
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
			/* EcuMWakeupSourceId�˰��פ��륳��ȥ��餬���Ĥ��ä���硤������ȴ���� */
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

		/* EcuMWakeupSourceId�˰��פ��륳��ȥ���򸡽� */
		if (((((uint32) 0x00000001) << p_canif_ctrl_inib->EcuMWakeupSourceId) & WakeupSource) != ((uint32) 0x00000000)) {
			p_canif_ctrl_cb = p_canif_ctrl_inib->p_canif_ctrl_cb;

			/* [CANIF407] */
			D_CANIF_CHECK_PARAM_ERCD(p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED);

			/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
			p_saved_config = p_cur_canif_config;

			/* CAN��å����������������� */
			if (p_canif_ctrl_cb->validation_status != FALSE) {
				/* [CANIF179][CANIF532] */
				SchM_Exit_CanIf_Reentrant_0();
				CanIfDispatchUserValidateWakeupEventName(WakeupSource);
				SchM_Enter_CanIf_Reentrant_0();
			}
			else {
				/* [CANIF681][CANIF532] CAN��å�������������Ƥʤ����ϡ�WakeupSource�����ӥåȤ򥯥ꥢ������������ */
				SchM_Exit_CanIf_Reentrant_0();
				CanIfDispatchUserValidateWakeupEventName(0U);
				SchM_Enter_CanIf_Reentrant_0();
			}

			ercd = E_OK;

			/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
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
/* [CANIF780] CANIF_PUBLIC_CHANGE_BAUDRATE_SUPPORT��STD_OFF�ξ��ϡ�CanIf_CheckBaudrate��̵���ˤ��� */
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
	/* [CANIF391][CANIF472] LPDU�����Υ��ơ����������ꤹ�� */
	if (p_lpdu_inib->p_notify_status != NULL_PTR) {
		*(p_lpdu_inib->p_notify_status) = CANIF_TX_RX_NOTIFICATION;
	}
#endif /* CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON */

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	/* [CANIF740] TxConfirmation���ƤФ줿���Ȥ��ݻ����� */
	p_canif_ctrl_cb->tx_confirmation_flg = TRUE;
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */

	/*
	 *  [CANIF073][CANIF489][CANIF075][CANIF491]
	 *  �����ѥ�������饤��ޤ��ϥ���饤�󥢥��ƥ��֤ξ�硤��̥쥤��ؤ���������ե��᡽����󥵡��ӥ���ƤӽФ�
	 */
	D_CANIF_CHECK_PARAM((p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_TX_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE));

	if (p_lpdu_inib->CanIfPduUserConfirmationName != NULL_PTR) {
		/* ��¾���ꥢ��ǳƾ������Ф� */
		TxConfirmation = ((User_TxConfirmation) p_lpdu_inib->CanIfPduUserConfirmationName);
		pduid = p_lpdu_inib->PduRPduHandleId;
		/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
		p_saved_config = p_cur_canif_config;

		/* [CANIF383][CANIF414] ��������ե��᡼����󥳡���Хå� */
		SchM_Exit_CanIf_Reentrant_1();
		TxConfirmation(pduid);
		SchM_Enter_CanIf_Reentrant_1();

		/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
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
	/* [CANIF418] */
	CANIF_CHECK_PARAM((CanDlc <= DLC_MAX), CanIfServiceId_RxIndication, CANIF_E_PARAM_DLC);
	/* [CANIF419] */
	CANIF_CHECK_NULL_POINTER((CanSduPtr != NULL_PTR), CanIfServiceId_RxIndication);

	p_lpdu_inib = GET_LPDU_INIB_HOH(Hrh);

	/* [CANIF416] */
	CANIF_CHECK_PARAM(p_lpdu_inib->lpdu_direction == CANIF_RECEIVE, CanIfServiceId_RxIndication, CANIF_E_PARAM_HRH);

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;

	/* [CANIF417] */
	CANIF_CHECK_PARAM((CanId == p_lpdu_inib->CanIfPduCanId), CanIfServiceId_RxIndication, CANIF_E_PARAM_CANID);

	/* DLC�����å� */
	/* [CANIF390][CANIF026][CANIF168] */
	A_CHECK_DLC(CanDlc, p_lpdu_inib->CanIfPduDlc);

	/* ����LPDU�ΥХåե���� */
#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
	if (p_lpdu_inib->p_rx_lpdu_buffer != NULL_PTR) {
		/* [CANIF198][CANIF297] */
		for (i = 0U; i < p_lpdu_inib->CanIfPduDlc; i++) {
			(p_lpdu_inib->p_rx_lpdu_buffer)[i] = CanSduPtr[i];
		}
	}
	/* [CANIFa001] ���������Τ�p_tx_rx_flg��TRUE�ˤ��� */
	CANIF_CHECK_PARAM((p_lpdu_inib->p_rx_indication_flg != NULL_PTR), CanIfServiceId_RxIndication, CANIF_E_PARAM_POINTER);
	*(p_lpdu_inib->p_rx_indication_flg) = TRUE;
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

#if CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON
	if (p_lpdu_inib->p_notify_status != NULL_PTR) {
		/* [CANIF392][CANIF473] ���Υ��ơ����������ꤹ�� */
		*(p_lpdu_inib->p_notify_status) = CANIF_TX_RX_NOTIFICATION;
	}
#endif /* CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API = STD_ON */

#if CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON
	if (p_canif_ctrl_cb->controller_mode == CANIF_CS_STARTED) {
		/* [CANIF286] �оݤΥ���ȥ�����Ф��ơ�CCMSM��CANIF_CS_STARTED�Ǥ���С�CanIf_RxIndication���ƤФ줿���Ȥ��ݻ����� */
		p_canif_ctrl_cb->validation_status = TRUE;
	}
#endif /* CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON */

	/*
	 *  [CANIF073][CANIF490][CANIF492][CANIF075][CANIF492][CANIF490]
	 *  �����ѥ�������饤��ξ�硤��̥쥤��ؤμ������Υ����ƥॵ���ӥ���ƤӽФ�
	 */
	D_CANIF_CHECK_PARAM((p_canif_ctrl_cb->pdu_mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_ONLINE) ||
						(p_canif_ctrl_cb->pdu_mode == CANIF_GET_RX_ONLINE));

	if (p_lpdu_inib->CanIfPduUserConfirmationName != NULL_PTR) {
		/* ��¾���ꥢ��ǳƾ������Ф� */
		pduid = p_lpdu_inib->PduRPduHandleId;
		/* [CANIF056] ��̥쥤��ؤμ������Υ����ƥॵ���ӥ��ƤӽФ� */
		RxIndication = ((User_RxIndication) p_lpdu_inib->CanIfPduUserConfirmationName);
		/* [CANIF057][CANIF135] PDU�������� */
		pduinfo.SduDataPtr = CanSduPtr;
		/* [CANIF829][CANIF830] ��������DLC���̥쥤��⥸�塼����Ϥ� */
		pduinfo.SduLength = CanDlc;
		/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
		p_saved_config = p_cur_canif_config;

		/* [CANIF423][CANIF012][CANIF415][CANIF830] */
		SchM_Exit_CanIf_Reentrant_0();
		RxIndication(pduid, &pduinfo);
		SchM_Enter_CanIf_Reentrant_0();

		/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
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

	/* [CANIF298][CANIF488] CCMSM��CANIF_CS_STOPPED�ˤ��� */
	p_canif_ctrl_cb->controller_mode = CANIF_CS_STOPPED;

	/* ��¾���ꥢ��ǥ���ȥ���ID����Ф� */
	ctrl_id = p_canif_ctrl_inib->CanControllerId;
	/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
	p_saved_config = p_cur_canif_config;

	/* [CANIF724][CANIF014][CANIF433] */
	SchM_Exit_CanIf_Reentrant_1();
	CanIfDispatchUserCtrlBusOffName(ctrl_id);
	SchM_Enter_CanIf_Reentrant_1();

	/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
	CANIF_CHECK_PARAM(p_saved_config == p_cur_canif_config, CanIfServiceId_ControllerBusOff, CANIF_E_FATAL);

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	/* [CANIF739] TxConfirmation�˴ؤ�������õ�� */
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
	/* ���Τ��줿CCMSM�����ꤹ�� */
	p_canif_ctrl_cb->controller_mode = ControllerMode;

#if CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON
	if (ControllerMode == CANIF_CS_SLEEP) {
		/* [CANIF756] CANIF_CS_SLEEP�ξ�硤�оݤΥ���ȥ�����Ф��ơ�CanIf_RxIndication���ƤФ줿���Ȥ����ꥢ����� */
		p_canif_ctrl_cb->validation_status = FALSE;
	}
#endif /* CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON */

	/* ��¾���ꥢ��ǥ���ȥ���ID����Ф� */
	ctrl_id = p_canif_ctrl_inib->CanControllerId;
	/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
	p_saved_config = p_cur_canif_config;

	/* [CANIF711][CANIF704][CANIF687] */
	SchM_Exit_CanIf_Reentrant_1();
	CanIfDispatchUserCtrlModeIndicationName(ctrl_id, ControllerMode);
	SchM_Enter_CanIf_Reentrant_1();

	/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
	CANIF_CHECK_PARAM(p_saved_config == p_cur_canif_config, CanIfServiceId_ControllerModeIndication, CANIF_E_FATAL);

  error_exit:
	SchM_Exit_CanIf_Reentrant_1();
	return;
}

/*
 *  �ʲ���̤���ݡ��ȵ�ǽ
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
