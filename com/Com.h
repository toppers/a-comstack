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
 *  $Id: Com.h 1245 2015-03-25 09:25:18Z panasonic-ayane $
 */

/* [COM005] Com.h */

/*
 *  ��ȯ����
 *  - [COM746] Com.h��include������������ƤΥǡ���������Ѳ�ǽ�Ȥ���
 *  - [COM747] ��������ǡ������Υ�������sizeof�Ǽ�����ǽ�Ȥ���
 *  - [COM748] �ǥХå����뤿����ѿ��ˤϤ��줾���������
 *  - [COM786] ɸ�ಽ���줿�ѥ�᡼�����ܥإå��ե������¾��BSW���󶡲�ǽ�Ȥ���
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

/* IPDU���롼�פξ��֤��Ǽ�������󥵥��� */
#define IPDU_GROUP_VECTOR_NUM	(((COM_SUPPORTED_IPDU_GROUPS - 1U) / 8U) + 1U)

/* IPDU�������ޥ��� */
#define IPDU_STARTED_BIT						0x01U       /* IPDU�����Ϥ���Ƥ��뤫�ɤ��� */
#define IPDU_NOTICED_BIT						0x02U       /* DEFERRED��IPDU�μ���(������λ)���Τ��������ɤ��� */
#define IPDU_DIRECT_SEND_BIT					0x04U       /* DIRECT�����椫�ɤ��� */
#define IPDU_FIRST_DIRECT_SEND_BIT				0x08U       /* ����DIRECT�����Ǥ��뤫�ɤ��� */
#define IPDU_RETRY_BIT							0x10U       /* ��ȥ饤���֤��ɤ��� */
#define IPDU_MDT_WAIT_BIT						0x20U       /* MDT�Ԥ����֤��ɤ��� */
#define IPDU_DM_BIT								0x40U       /* DM�����Ϥ���Ƥ��뤫�ɤ��� */
#define IPDU_TRIGGERED_BIT						0x80U       /* Com_TriggerIPDUSend���ƤФ줿���ɤ��� */
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
 *  �����å��ޥ���
 *  [COM024] DET���顼��OFF�ξ�硤�ѥ�᡼�������å��Ϥ��ʤ�
 *  [COM442] Det_ReportError����2����(InstanceId)��0�Ȥ���
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
 *  AUTOSAR��꡼���С������
 */
#define COM_AR_RELEASE_MAJOR_VERSION	4U
#define COM_AR_RELEASE_MINOR_VERSION	0U
#define COM_AR_RELEASE_PATCH_VERSION	3U

/*
 *  ���ץ饤��С���������
 */
#define COM_SW_MAJOR_VERSION	1U
#define COM_SW_MINOR_VERSION	2U
#define COM_SW_PATCH_VERSION	0U
#define COM_VENDOR_ID			65U  /* NCES�٥��ID */

/*
 *  ��������ޥ���
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
 *  [COM442] DET�����Τ��륵���ӥ�ID
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
 *  �ե��륿������֥�å�: UINT�Ϥ�COM_MASKED_NEW_DIFFERS_X/COM_MASKED_NEW_EQUALS_X��
 */
typedef struct filter_uint_masked_initialization_block {
	uint32	ComFilterMask;
	uint32	ComFilterX;
} FILTER_UINT_MASKED_INIB;

/*
 *  �ե��륿������֥�å�: SINT�Ϥ�COM_MASKED_NEW_DIFFERS_X/COM_MASKED_NEW_EQUALS_X��
 */
typedef struct filter_sint_masked_initialization_block {
	sint32	ComFilterMask;
	sint32	ComFilterX;
} FILTER_SINT_MASKED_INIB;

/*
 *  �ե��륿������֥�å�: UINT�Ϥ�COM_MASKED_NEW_DIFFERS_MASKED_OLD��
 */
typedef struct filter_uint_masked_old_initialization_block {
	uint32	ComFilterMask;
	void	*p_filter_buffer;
} FILTER_UINT_MASKED_OLD_INIB;

/*
 *  �ե��륿������֥�å�: SINT�Ϥ�COM_MASKED_NEW_DIFFERS_MASKED_OLD��
 */
typedef struct filter_sint_masked_old_initialization_block {
	sint32	ComFilterMask;
	void	*p_filter_buffer;
} FILTER_SINT_MASKED_OLD_INIB;

/*
 *  �ե��륿������֥�å�: UINT�Ϥ�COM_NEW_IS_OUTSIDE/COM_NEW_IS_WITHIN��
 */
typedef struct filter_uint_new_is_initialization_block {
	uint32	ComFilterMax;
	uint32	ComFilterMin;
} FILTER_UINT_NEW_IS_INIB;

/*
 *  �ե��륿������֥�å�: SINT�Ϥ�COM_NEW_IS_OUTSIDE/COM_NEW_IS_WITHIN��
 */
typedef struct filter_sint_new_is_initialization_block {
	sint32	ComFilterMax;
	sint32	ComFilterMin;
} FILTER_SINT_NEW_IS_INIB;

/*
 *  �ե��륿������֥�å�: COM_ONE_EVERY_N��
 */
typedef struct filter_one_every_n_initialization_block {
	uint32	ComFilterOffset;
	uint32	ComFilterPeriod;
	uint32	*p_occur;
} FILTER_ONE_EVERY_N_INIB;

/*
 *  ���������ʥ�����֥�å�
 */
typedef struct rx_signal_control_block {
	uint32	dm_mf_cnt;  /* DM��MF���������[�ǥåɥ饤���˥���󥰻���] */
	uint8	dm_state;   /* START:DM�ƻ뤹�롤STOP:DM�ƻ뤷�ʤ���WAIT:�������ޤ�DM�ƻ뤷�ʤ� */
} RX_SIGNAL_CB;

/*
 *  ���������ʥ�����֥�å�
 */
typedef struct tx_signal_control_block {
	boolean	tmc;    /* TMC */
} TX_SIGNAL_CB;

/*
 * �����⡼�ɽ�����֥�å�
 */
typedef struct tx_mode_initialization_block {
	uint8	ComTxModeMode;                  /* ɬ�� */
	uint8	ComTxModeNumberOfRepetitions;   /* ̤����ξ�硤0 */
	uint32	ComTxModeRepetitionPeriod;      /* ̤����ξ�硤0 */
	uint32	ComTxModeTimeOffset;            /* ̤����ξ�硤0 */
	uint32	ComTxModeTimePeriod;            /* ̤����ξ�硤0 */
} TX_MODE_INIB;

/*
 * ����IPDU������֥�å�
 */
typedef struct tx_ipdu_initialization_block {
	uint8				ComTxIPduClearUpdateBit;        /* ̤����ξ�硤COM_INVALID_UINT8 */
	uint8				ComTxIPduUnusedAreasDefault;    /* ɬ�� */
	uint32				ComMinimumDelayTime;            /* ̤����ξ�硤0 */
	const TX_MODE_INIB	*p_tx_mode_true_inib;           /* ɬ�� */
	const TX_MODE_INIB	*p_tx_mode_false_inib;          /* ̤����ξ�硤NULL_PTR */
} TX_IPDU_INIB;

/*
 *  IPDU������֥�å�
 */
typedef struct ipdu_initialization_block {
	uint8				ComIPduDirection;               /* ɬ�� */
	uint8				ComIPduSignalProcessing;        /* ɬ�� */
	uint8				ComIPduType;                    /* ɬ�� */
	boolean				ComIPduCancellationSupport;     /* ̤����ξ�硤FALSE */
	const TX_IPDU_INIB	*p_tx_ipdu_inib;                /* �����ξ�硤ɬ�ܡ������ξ�硤NULL_PTR */
	Com_IpduCallout		ComIPduCallout;                 /* ̤����ξ�硤NULL_PTR */
	PduIdType			PduRSourcePduHandleId;          /* ɬ�� */
	PduLengthType		PduLength;                      /* ɬ�� */

	const Com_SignalIdType		*p_signalid_list;       /* IPDU�˽�°���륷���ʥ�ID�ꥹ��  */
	const Com_IpduGroupVector	*p_ipdu_group_vector;   /* IPDU����°����IPDU���롼�ץ٥���(��°���륰�롼�פΥӥåȤΤ�ON) */
	void						*p_ipdu_cb;             /* IPDU�����֥�å� */
	uint8						*p_ipdu_buffer;         /* IPDU�Хåե� */
	uint8						*p_state;               /* IPDU����(0bit:���Ͼ��֡�1bit:�Хåե���������) */
	uint16						tnum_signal;            /* IPDU�˽�°���륷���ʥ�� */
} IPDU_INIB;                                                      /* IPDU_INIB */

/*
 *  ����IPDU�����֥�å�
 */
typedef struct tx_ipdu_control_block {
	uint32				interval_mf_cnt;        /* ��������֤�MF���������[DIRECT����N�δֳ�] */
	uint32				period_mf_cnt;          /* ������MF���������[PERIODIC������������] */
	uint32				mdt_mf_cnt;             /* MDT��MF���������[�Ǿ��ٱ����] */
	uint32				dm_mf_cnt;              /* DM��MF���������[�ǥåɥ饤���˥���󥰻���] */
	uint8				repeat_cnt;             /* �����֤����������[DIRECT����N] */
	uint8				queuing_cnt;            /* ������λ������� */
	const TX_MODE_INIB	*p_cur_tx_mode_inib;    /* ���ߤ������⡼�ɽ�����֥�å��ؤΥݥ��� */
} TX_IPDU_CB;

/*
 *  �����ʥ������֥�å�
 */
typedef struct signal_initialization_block {
	uint8			ComBitSize;                         /* UINT8_N�ξ�硤COM_INVALID_UINT8 */
	uint8			ComDataInvalidAction;               /* ̤����ξ�硤COM_INVALID_UINT8 */
	uint8			ComRxDataTimeoutAction;             /* ̤����ξ�硤COM_INVALID_UINT8 */
	uint8			ComSignalEndianness;                /* ɬ�� */
	uint8			ComSignalType;                      /* ɬ�� */
	uint8			ComTransferProperty;                /* �����ξ�硤ɬ�ܡ������ξ�硤COM_INVALID_UINT8 */
	uint16			ComBitPositionLsb;                  /* ɬ�� */
	uint16			ComSignalLength;                    /* UINT8_N�ʳ��ξ�硤COM_INVALID_UINT16 */
	uint16			ComUpdateBitPosition;               /* ̤����ξ�硤COM_INVALID_UINT16 */
	uint32			ComFirstTimeout;                    /* ̤����ξ�硤0 */
	uint32			ComTimeout;                         /* ̤����ξ�硤0 */
	Com_CbkTxErr	ComErrorNotification;               /* ̤����ξ�硤NULL_PTR */
	Com_CbkInv		ComInvalidNotification;             /* ̤����ξ�硤NULL_PTR */
	Com_CbkAck		ComNotification;                    /* ̤����ξ�硤NULL_PTR */
	Com_CbkTOut		ComTimeoutNotification;             /* ̤����ξ�硤NULL_PTR */
	const void		*ComSignalDataInvalidValue;         /* ̤����ξ�硤NULL_PTR */
	const void		*ComSignalInitValue;                /* ɬ��(�ǥե����0) */
	const IPDU_INIB	*p_ipdu_inib;                       /* ��°����IPDU������֥�å� */
	uint8			ComFilterAlgorithm;                 /* �ե��륿�ʤ��ξ�硤COM_INVALID_UINT8 */
	/*
	 *  �ե��륿������֥�å�
	 *  �ե��륿�ʤ��ξ�硤NULL_PTR
	 *  �ե��륿���르�ꥺ�बCOM_ALWAYS��COM_NEVER�ξ�硤NULL_PTR
	 */
	const void *p_filter_inib;
	/*
	 *  �����ʥ�����֥�å�
	 *  �����ξ�硤����DM���ʤ���С�NULL_PTR
	 *  �����ξ�硤�ե��륿���ʤ���С�NULL_PTR
	 */
	void *p_signal_cb;
	/*
	 *  �����ʥ�Хåե�
	 *  �����ξ�硤ɬ��
	 *  �����ξ�硤TRIGGERED_ON_CHANGE��TRIGGERED_ON_CHANGE_WITHOUT_REPETITION�ʳ��ϡ�NULL_PTR
	 */
	void *p_signal_buffer;
} SIGNAL_INIB;

/*
 *  Com����ե�����졼���������֥�å�
 *  (1����ե�����졼�����ˤĤ�1�ĺ�������)
 */
typedef struct com_config_type {
	uint32 ComConfigurationId;                  /* ɬ�� */

	uint16	tnum_signal;                        /* �����ʥ�� */
	uint16	tnum_ipdu_g;                        /* IPDU���롼�׿� */

	const SIGNAL_INIB *p_signal_inib_table;     /* �����ʥ������֥�å����� */

	uint8			tnum_vector;                /* IPDU���롼�פ�ӥåȤǴ�������Τ�ɬ�פʥХ��ȿ� */
	uint16			tnum_ipdu;                  /* IPDU�� */
	const IPDU_INIB	* const *pp_ipdu_inib_table;/* IPDU������֥�å��ݥ������� */
	uint16			tnum_rx_ipdu;               /* ����IPDU�� */
	uint16			tnum_tx_ipdu;               /* ����IPDU�� */
	const IPDU_INIB	*p_rx_ipdu_inib_list;       /* ����IPDU������֥�å����� */
	const IPDU_INIB	*p_tx_ipdu_inib_list;       /* ����IPDU������֥�å����� */
} Com_ConfigType;


/*
 *  Com�����ƥॵ���ӥ��ץ�ȥ��������
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
 *  Com����ե�����졼��������(Com_PBcfg.c)
 */
extern const Com_ConfigType	com_config[];


/*
 *  �ʲ���̤���ݡ��ȵ�ǽ
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
 *  �ܥǥ�����ϥץ�ե�����ʳ��Τ�����б����ʤ����ͥ�������
 *  (Ʊ����ͥ������ܥǥ�����ϥץ�ե�������׵���ͤǤ���Ѥ���Ƥ����Τ�[]��ɽ��)
 *  - �����ʥ륲���ȥ�����
 *    <COM370><COM377>[COM324][COM067]<COM359><COM466><COM539><COM384><COM386><COM598>
 *    <COM357><COM360><COM361><COM383><COM735><COM362><COM701><COM702><COM703><COM704>
 *    <COM705><COM706>
 *  - �ǡ�����������
 *    <COM687><COM688><COM587><COM588><COM590><COM726><COM727>
 *  - �̿��ݸ�
 *    <COM596><COM597>
 *  - �����ʥ륰�롼��
 *    <COM682><COM683><COM737><COM718>[COM500]<COM393><COM513><COM053><COM484><COM050>
 *    <COM051><COM061><COM741><COM769><COM742><COM743><COM770><COM326><COM365><COM575>
 *  - �緿�ǡ���
 *    <COM713><COM714><COM662><COM759><COM760><COM720>
 *  - ưŪ�ǡ���
 *    <COM753><COM754><COM755><COM756><COM757><COM758>
 *  - �ե��륿���
 *    <COM327>
 */

/*
 *  ����¾�λ�������
 *    [COM780][COM781] �ܼ����Ǥ�Com_TriggerIPDUSend, Com_SendSignal���¨���������ʤ������н�����
 *    <COM696><COM697> Com_TriggerTransmit̤���ݡ��ȤΤ��ᡤ�н�����
 */

#endif /* COM_H */
