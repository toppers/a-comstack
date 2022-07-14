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
 *  $Id: CanIf.h 784 2014-11-27 12:57:20Z panasonic-ayane $
 */

/* [CANIF116] CanIf.h */

/*
 *  ��ȯ����
 *  - [CANIF565] Debugging�ǥ���������ǽ�ʳ��ѿ��ϥ����Х��ѿ����������
 *  - [CANIF566] CanIf.h��include������������ƤΥǡ���������Ѳ�ǽ�Ȥ���
 *  - [CANIF567] ��������ǡ������Υ�������sizeof�Ǽ�����ǽ�Ȥ���
 *  - [CANIF568] �ǥХå����뤿����ѿ��ˤϤ��줾���������
 *  - [CANIF672] CanIf.h�ˤ�CanIf SWS�ǵ��ꤵ�줿����䥰���Х�ǡ����������ƥॵ���ӥ��Τߤ򵭺ܤ���
 *  - [CANIF725] ɸ�ಽ���줿�ѥ�᡼�����ܥإå��ե������¾��BSW���󶡲�ǽ�Ȥ���
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
#define CANIF_E_INVALID_RXPDUID			60U         /* [CANIF154] */
#define CANIF_E_INVALID_DLC				61U         /* [CANIF154] */
#define CANIF_E_STOPPED					70U         /* [CANIF154] */
#define CANIF_E_NOT_SLEEP				71U         /* [CANIF154] */
#define CANIF_E_FATAL					0xFFU

#define CANIF_UNINIT	0x01U
#define CANIF_INIT		0x02U

#define CANIF_SEND		0x03U
#define CANIF_RECEIVE	0x04U

#define DLC_MAX	8U


/*
 *  [CANIF018][CANIF019][CANIF156][CANIF119]
 *  �����å��ޥ���
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

/* �ѥ�᡼���ˤ�ꡤ�»�̵ͭ���Ѥ������å��ޥ��� */
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

/* DET̵ͭ�ˤ�����餺�»ܤ�������å��ޥ��� */
#define C_CANIF_CHECK_PARAM_ERCD(exp, ApiId, ErrorId)						 \
	do {																	 \
		if (!(exp)) {														 \
			ercd = E_NOT_OK;												 \
			CANIF_SWITCH_DET_ERROR(CANIF_MODULE_ID, 0U, (ApiId), (ErrorId)); \
			goto error_exit;												 \
		}																	 \
	} while (0)

/* �»�ɬ�ܥ����å��ޥ��� */
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
 *  [CANIF728][CANIF021] AUTOSAR��꡼���С������
 */
#define CANIF_AR_RELEASE_MAJOR_VERSION		4U
#define CANIF_AR_RELEASE_MINOR_VERSION		0U
#define CANIF_AR_RELEASE_REVISION_VERSION	3U

/*
 *  [CANIF728][CANIF729] ���ץ饤��С���������
 */
#define CANIF_SW_MAJOR_VERSION	1U
#define CANIF_SW_MINOR_VERSION	1U
#define CANIF_SW_PATCH_VERSION	0U
#define CANIF_VENDOR_ID			65U /* [CANIF726] NCES�٥��ID */

/*
 *  ��������ޥ���
 */
#define GET_CANIF_CTRL_NUM()				tnum_canif_controller
#define GET_LPDU_NUM()						p_cur_canif_config->tnum_lpdu
#define GET_CANIF_CTRL_INIB(ControllerId)	(&p_cur_canif_ctrl_inib[(ControllerId)])
#define GET_CANIF_CTRL_CB(ControllerId)		p_cur_canif_ctrl_inib[(ControllerId)].p_canif_ctrl_cb
#define GET_LPDU_INIB(PduId)				(&p_cur_lpdu_inib[(PduId)])
#define GET_LPDU_INIB_HOH(Hoh)				pp_cur_lpdu_inib_hoh[(Hoh)]

/*
 *  DET�����Τ��륵���ӥ�ID
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
 *  �ؿ��ݥ��󥿷����
 */
typedef void (*User_TxConfirmation)(PduIdType TxPduId);
typedef void (*User_RxIndication)(PduIdType RxPduId, PduInfoType *PduInfoPtr);
typedef void (*User_ValidateWakeupEvent)(EcuM_WakeupSourceType sources);
typedef void (*User_ControllerBusOff)(uint8 ControllerId);
typedef void (*User_ControllerModeIndication)(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);
typedef void (*CanIf_PduUserConfirmation)();

/*
 *  CanIf����ȥ�������֥�å�
 */
typedef struct canif_controller_control_block {
	CanIf_ControllerModeType	controller_mode;        /* CCMSM */
	CanIf_PduGetModeType		pdu_mode;               /* ����ȥ����°����PDU����ͥ�⡼�� */
	boolean						validation_status;      /* TRUE:CAN��å����������������FALSE:CAN��å�������1�٤�������Ƥ��ʤ� */

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON
	boolean	tx_confirmation_flg;                        /* ����ȥ�����Ф���TxConfirmation���ƤФ줿���ɤ������ݻ����� */
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */
} CANIF_CTRL_CB;

/*
 *  CanIf����ȥ��������֥�å�
 */
typedef struct canif_controller_initialization_block {
	uint8					CanControllerId;        /* CanIfCtrlCanCtrlRef�λ����褫����� */
	EcuM_WakeupSourceType	EcuMWakeupSourceId;     /* CanWakeupSourceRef�λ����褫����� */
	boolean					CanIfCtrlWakeupSupport; /* TRUE:CAN����ȥ��鵯ư�򥵥ݡ��Ȥ��롤FALSE:CAN����ȥ��鵯ư�򥵥ݡ��Ȥ��ʤ� */
	CANIF_CTRL_CB			*p_canif_ctrl_cb;       /* CAN����ȥ�������֥�å� */
} CANIF_CTRL_INIB;

/*
 *  LPDU������֥�å�
 */
typedef struct lpdu_initialization_block {
	Can_IdType					CanIfPduCanId;                          /* [CANIF281] ����:CanIfTxPduCanId������:CanIfRxPduCanId */
	uint8						CanIfPduDlc;                            /* ����:CanIfTxPduDlc������:CanIfRxPduDlc */
	uint8						CanObjectId;                            /* �������CanHardWareObject������� */
	PduIdType					PduRPduHandleId;                        /* ����:PduRDestPduHandleId������:PduRSourcePduHandleId */
	CanIf_PduUserConfirmation	CanIfPduUserConfirmationName;           /* ����:CanIfTxPduUserTxConfirmationName������:CanIfRxPduUserRxIndicationName */
	CANIF_CTRL_CB				*p_canif_ctrl_cb;                       /* CANIF����ȥ�������֥�å� */

#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS
	/*
	 *  LPDU�����Υ��ơ�����
	 *  ���� TRUE:CanIf_TxConfirmation���ƤФ줿��FALSE:CanIf_TxConfirmation���ƤФ�Ƥ��ʤ�
	 *       CanIfTxPduReadNotifyStatus��FALSE�ξ�硤NULL_PTR
	 *
	 *  ���� TRUE:CanIf_RxIndication���ƤФ줿��FALSE:CanIf_RxIndication���ƤФ�Ƥ��ʤ�
	 *       CanIfRxPduReadNotifyStatus��FALSE�ξ�硤NULL_PTR
	 */
	CanIf_NotifStatusType *p_notify_status;
#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */

#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON
	/*
	 * ������λ����̵ͭ�ե饰
	 * �����ξ�硤NULL_PTR�������ξ�硤ɬ�ܡ�
	 * TRUE:1�٤Ǥ�CanIf_RxIndication���ƤФ줿��FALSE:1�٤�CanIf_RxIndication���ƤФ�Ƥ��ʤ�
	 */
	boolean	*p_rx_indication_flg;
	uint8	*p_rx_lpdu_buffer;                              /* �����ޤ��ϡ���������CanIfRxPduReadData��FALSE�ʤ�С�NULL_PTR */
#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */

#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
	uint8 lpdu_direction;                                   /* LPDU���������� */
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */
} LPDU_INIB;

/*
 *  CanIf����ե�����졼���������֥�å�
 */
typedef struct canif_config_type {
	uint16			tnum_lpdu;                      /* LPDU�� */
	const LPDU_INIB	*p_lpdu_inib_table;             /* LPDU������֥�å����� */
	const LPDU_INIB	* const *pp_lpdu_inib_hoh_list; /* LPDU������֥�å��ݥ��󥿤�CanObjectId�ǥ����Ȥ����ꥹ�� */
} CanIf_ConfigType;

extern const CanIf_ConfigType			* const p_default_canif_config;

extern User_ControllerBusOff			CanIfDispatchUserCtrlBusOffName;
extern User_ControllerModeIndication	CanIfDispatchUserCtrlModeIndicationName;
extern User_ValidateWakeupEvent			CanIfDispatchUserValidateWakeupEventName;

extern const uint16						tnum_canif_controller;
extern const CANIF_CTRL_INIB			canif_ctrl_inib_table[];


/*
 *  CanIf�����ƥॵ���ӥ��ץ�ȥ��������
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
 *  �ʲ���̤���ݡ��ȵ�ǽ
 */
extern void CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId);
extern Std_ReturnType CanIf_SetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);
extern Std_ReturnType CanIf_GetTrcvMode(CanTrcv_TrcvModeType *TransceiverModePtr, uint8 TransceiverId);
extern Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 TransceiverId, CanTrcv_TrcvWakeupReasonType *TrcvWuReasonPtr);
extern Std_ReturnType CanIf_SetTrcvWakeupMode(uint8 TransceiverId, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);
extern Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 TransceiverId);
extern Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 TransceiverId);

/*
 *  �ܥǥ�����ϥץ�ե�����ʳ��Τ�����б����ʤ����ͥ�������
 *  (Ʊ����ͥ������ܥǥ�����ϥץ�ե�������׵���ͤǤ���Ѥ���Ƥ����Τ�[]��ɽ��)
 *  - ��������󥻥륳��ե��᡼�����
 *    <CANIF054><CANIF101><CANIF828><CANIF424><CANIF426><CANIF427><CANIF428><CANIF118>
 *  - �����Хåե����
 *    <CANIF063><CANIF381><CANIF835><CANIF836><CANIF068><CANIF837><CANIF386><CANIF668><CANIF070><CANIF183>
 *    <CANIF387><CANIF033><CANIF176><CANIF485>
 *  - ưŪ����ID����
 *    <CANIF188><CANIF673><CANIF189><CANIF352><CANIF353><CANIF355><CANIF356><CANIF357>
 *  - �����ե��륿���
 *    <CANIF645><CANIF646><CANIF030><CANIF211><CANIF389><CANIF663><CANIF469>
 *  - �ޥ��CAN�ɥ饤�Х��ݡ���
 *    <CANIF124><CANIF224>
 *  - CAN�ȥ�󥷡�������
 *    <CANIF287><CANIF288><CANIF289><CANIF290><CANIF358><CANIF362><CANIF363><CANIF364><CANIF367><CANIF368>
 *    <CANIF371><CANIF372><CANIF373><CANIF535><CANIF536><CANIF537><CANIF538><CANIF648><CANIF649><CANIF650>
 *    <CANIF693><CANIF694><CANIF706><CANIF708><CANIF709><CANIF710><CANIF712><CANIF730><CANIF757><CANIF759>
 *    <CANIF760><CANIF761><CANIF762><CANIF763><CANIF764><CANIF765><CANIF766><CANIF769><CANIF770><CANIF771>
 *    <CANIF788><CANIF799><CANIF805><CANIF806><CANIF807><CANIF808><CANIF809><CANIF810><CANIF811><CANIF812>
 *    <CANIF813><CANIF814>
 *  - �ѡ������ͥåȥ����
 *    <CANIF747><CANIF748><CANIF749><CANIF750><CANIF751><CANIF752><CANIF827><CANIF753><CANIF754><CANIF815>
 *    <CANIF816><CANIF817><CANIF818><CANIF821><CANIF822><CANIF825><CANIF827>
 */

/*
 *  ����¾�λ�������
 *    <CANIF999> �׵���ͤǤϤʤ�
 */

#endif /* CANIF_H */
