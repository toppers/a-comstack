/*
 *  TOPPERS/A-CANIF
 *      Automotive CANIF
 *
 *  Copyright (C) 2013-2014 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2013-2014 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2014 by Witz Corporation, JAPAN
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
 *  $Id: canif_debug.h 425 2014-09-17 00:46:01Z fsi-dankei $
 */

#ifndef CANIF_DEBUG_H
#define CANIF_DEBUG_H

#include "CanIf.h"
#include "ComStack_Types.h"
#include "CanIf_Cfg.h"
#include "t_syslog.h"

#define dump0(str)	syslog(LOG_NOTICE, str)
#define dump1(str, arg1)	syslog(LOG_NOTICE, str, arg1)
#define dump2(str, arg1, arg2)	syslog(LOG_NOTICE, str, arg1, arg2)
#define dump3(str, arg1, arg2, arg3)	syslog(LOG_NOTICE, str, arg1, arg2, arg3)
#define dump4(str, arg1, arg2, arg3, arg4)	syslog(LOG_NOTICE, str, arg1, arg2, arg3, arg4)

LOCAL_INLINE void Debug_DumpAllConfiguration(void);
LOCAL_INLINE void Debug_Dumplpdu(PduIdType PduId);
LOCAL_INLINE void Debug_DumpCtrl(uint8 ControllerId);
LOCAL_INLINE char8 *Debug_PrintBits(void *p_data, uint8 size);

LOCAL_INLINE const char8 *
a_canif_boorean_str(boolean val)
{
	if (val) {
		return("TRUE");
	}
	else {
		return("FALSE");
	}
}

LOCAL_INLINE const char8 *
a_canif_param_ControllerMode_str(CanIf_ControllerModeType val)
{
	switch (val) {
	case CANIF_CS_UNINIT:						return("CANIF_CS_UNINIT");
	case CANIF_CS_SLEEP:						return("CANIF_CS_SLEEP");
	case CANIF_CS_STARTED:						return("CANIF_CS_STARTED");
	case CANIF_CS_STOPPED:						return("CANIF_CS_STOPPED");
	default:
		dump2("Fatal Error!![%s:%d]", __FILE__, __LINE__);
		break;
	}
	return("Error");
}

LOCAL_INLINE const char8 *
a_canif_param_PduGetMode_str(CanIf_PduGetModeType val)
{
	switch (val) {
	case CANIF_GET_OFFLINE:						return("CANIF_GET_OFFLINE");
	case CANIF_GET_OFFLINE_ACTIVE:				return("CANIF_GET_OFFLINE_ACTIVE");
	case CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE:	return("CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE");
	case CANIF_GET_ONLINE:						return("CANIF_GET_ONLINE");
	case CANIF_GET_RX_ONLINE:					return("CANIF_GET_RX_ONLINE");
	case CANIF_GET_TX_ONLINE:					return("CANIF_GET_TX_ONLINE");
	default:
		dump2("Fatal Error!![%s:%d]", __FILE__, __LINE__);
		break;
	}
	return("Error");
}

LOCAL_INLINE const char8 *
a_canif_param_NotifStatus_str(CanIf_PduGetModeType val)
{
	switch (val) {
	case CANIF_NO_NOTIFICATION:					return("CANIF_NO_NOTIFICATION");
	case CANIF_TX_RX_NOTIFICATION:				return("CANIF_TX_RX_NOTIFICATION");
	default:
		dump2("Fatal Error!![%s:%d]", __FILE__, __LINE__);
		break;
	}
	return("Error");
}

LOCAL_INLINE const char8 *
a_canif_param_str(uint32 val)
{
	switch (val) {
	case CANIF_UNINIT:							return("CANIF_UNINIT");
	case CANIF_INIT:							return("CANIF_INIT");
	case CANIF_SEND:							return("CANIF_SEND");
	case CANIF_RECEIVE:							return("CANIF_RECEIVE");
	default:
		dump2("Fatal Error!![%s:%d]", __FILE__, __LINE__);
		break;
	}
	return("Error");
}

LOCAL_INLINE void
Debug_DumpAllConfiguration(void)
{
	dump0("==========================================");
	dump0(" Debug_DumpAllConfiguration");
	dump0("==========================================");
	dump1("tnum_canif_controller: %d", tnum_canif_controller);
	dump1("tnum_lpdu: %d", p_cur_canif_config->tnum_lpdu);

	return;
}

LOCAL_INLINE void
Debug_Dumplpdu(PduIdType PduId)
{
	const LPDU_INIB	*p_lpdu_inib;
	CANIF_CTRL_CB	*p_canif_ctrl_cb;
#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
	uint8			i;
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

	dump0("==========================================");
	dump1(" Debug_Dumplpdu (LPDU-ID: %d)", PduId);
	dump0("==========================================");

	p_lpdu_inib = GET_LPDU_INIB(PduId);
	dump1("CanIfPduCanId: %d", p_lpdu_inib->CanIfPduCanId);
	dump1("CanIfPduDlc: %d", p_lpdu_inib->CanIfPduDlc);
	dump1("CanObjectId: %d", p_lpdu_inib->CanObjectId);
	dump1("PduRPduHandleId: %d", p_lpdu_inib->PduRPduHandleId);

#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS
	if (p_lpdu_inib->p_notify_status != NULL_PTR) {
		dump1("p_notify_status: %s", a_canif_param_NotifStatus_str(*(p_lpdu_inib->p_notify_status)));
	}
	else {
		dump0("p_notify_status: NULL_PTR");
	}
#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */

#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
	if (p_lpdu_inib->p_rx_indication_flg != NULL_PTR) {
		dump1("p_rx_indication_flg: %s", a_canif_boorean_str(*(p_lpdu_inib->p_rx_indication_flg)));
	}
	else {
		dump0("p_rx_indication_flg: NULL_PTR");
	}
	if (p_lpdu_inib->p_rx_lpdu_buffer != NULL_PTR) {
		for (i = 0; i < p_lpdu_inib->CanIfPduDlc; i++) {
			dump3("p_rx_lpdu_buffer[%d]: %s (0x%x)", i, Debug_PrintBits(&(p_lpdu_inib->p_rx_lpdu_buffer)[i], 8U), (p_lpdu_inib->p_rx_lpdu_buffer)[i]);
		}
	}
	else {
		dump0("p_rx_lpdu_buffer: NULL_PTR");
	}
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
	dump1("lpdu_direction: %s", a_canif_param_str(p_lpdu_inib->lpdu_direction));
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */

	p_canif_ctrl_cb = p_lpdu_inib->p_canif_ctrl_cb;
	dump1("controller_mode: %s", a_canif_param_ControllerMode_str(p_canif_ctrl_cb->controller_mode));
	dump1("pdu_mode: %s", a_canif_param_PduGetMode_str(p_canif_ctrl_cb->pdu_mode));
	dump1("validation_status: %s", a_canif_boorean_str(p_canif_ctrl_cb->validation_status));

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	dump1("tx_confirmation_flg: %s", a_canif_boorean_str(p_canif_ctrl_cb->tx_confirmation_flg));
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */

	return;
}

LOCAL_INLINE void
Debug_DumpCtrl(uint8 ControllerId)
{
	const CANIF_CTRL_INIB	*p_canif_ctrl_inib;
	CANIF_CTRL_CB			*p_canif_ctrl_cb;

	dump0("==========================================");
	dump1(" Debug_Dumpctrl (CONTROLLER-ID: %d)", ControllerId);
	dump0("==========================================");

	p_canif_ctrl_inib = GET_CANIF_CTRL_INIB(ControllerId);
	dump1("CanControllerId: %d", p_canif_ctrl_inib->CanControllerId);
	dump1("EcuMWakeupSourceId: %d", p_canif_ctrl_inib->EcuMWakeupSourceId);
	dump1("CanIfCtrlWakeupSupport: %s", a_canif_boorean_str(p_canif_ctrl_inib->CanIfCtrlWakeupSupport));

	p_canif_ctrl_cb = p_canif_ctrl_inib->p_canif_ctrl_cb;
	dump1("controller_mode: %s", a_canif_param_ControllerMode_str(p_canif_ctrl_cb->controller_mode));
	dump1("pdu_mode: %s", a_canif_param_PduGetMode_str(p_canif_ctrl_cb->pdu_mode));
	dump1("validation_status: %s", a_canif_boorean_str(p_canif_ctrl_cb->validation_status));

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	dump1("tx_confirmation_flg: %s", a_canif_boorean_str(p_canif_ctrl_cb->tx_confirmation_flg));
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */

	return;
}

LOCAL_INLINE char8 *
Debug_PrintBits(void *p_data, uint8 size)
{
	uint32			i, mask;
	uint32			udata1 = 0U;
	uint32			udata2 = 0U;
	static char8	str[65];

	for (i = 0U; i < 65U; i++) {
		str[i] = 0;
	}

	if (size == 64U) {
		udata1 = (uint32) (((*((uint64 *) p_data)) >> 32U) & 0xFFFFFFFFU);
		udata2 = (uint32) ((*((uint64 *) p_data)) & 0xFFFFFFFFU);
	}
	else if (size == 8U) {
		udata1 = (uint32) (*((uint8 *) p_data));
	}
	else if (size == 16U) {
		udata1 = (uint32) (*((uint16 *) p_data));
	}
	else {
		udata1 = *((uint32 *) p_data);
	}

	if (size != 64U) {
		for (i = 0U; i < size; i++) {
			mask = 1U << i;
			if ((udata1 & mask) != 0U) {
				str[size - 1U - i] = 0x31;
			}
			else {
				str[size - 1U - i] = 0x30;
			}
		}
	}
	else {
		for (i = 0U; i < 32U; i++) {
			mask = 1U << i;
			if ((udata1 & mask) != 0U) {
				str[32U - 1U - i] = 0x31;
			}
			else {
				str[32U - 1U - i] = 0x30;
			}
			if ((udata2 & mask) != 0U) {
				str[64U - 1U - i] = 0x31;
			}
			else {
				str[64U - 1U - i] = 0x30;
			}
		}
	}

	return(str);
}

#endif /* CANIF_DEBUG_H */
