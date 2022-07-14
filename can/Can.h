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
 *  $Id: Can.h 1245 2015-03-25 09:25:18Z panasonic-ayane $
 */

#ifndef TOPPERS_CAN_H
#define TOPPERS_CAN_H

/*
 * [CAN043][CAN037] �ܥե�����ˤϡ�Can�Υ����ƥॵ���ӥ����ѿ���extern������ǡ���������򵭽Ҥ���
 */

/* [CAN034][CAN435][CAN388] */
/* [CAN222] Can�⥸�塼���ɬ�פʥǡ�������������줿�إå��ե����� */
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"
#include "EcuM.h"

#define CAN_MODULE_ID	80U

/*
 *  [CAN111] AUTOSAR��꡼���С������
 */
#define CAN_AR_RELEASE_MAJOR_VERSION		4U
#define CAN_AR_RELEASE_MINOR_VERSION		0U
#define CAN_AR_RELEASE_REVISION_VERSION		3U

/*
 *  ���ץ饤��С���������
 */
#define CAN_SW_MAJOR_VERSION	1U
#define CAN_SW_MINOR_VERSION	2U
#define CAN_SW_PATCH_VERSION	0U
#define CAN_VENDOR_ID			65U /* NCES�٥��ID */

/*
 *  ��������ޥ���
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
 *  ��������ޥ���
 */
#define SET_SAVED_PDU_ID(id, box_no, pdu_id)		(p_cur_can_ctrl_inib_table[(id)].p_can_hth_cb_table[(box_no)].saved_pduid = (pdu_id))
#define SET_HTH_MUTEX(id, box_no, mutex_state)		(p_cur_can_ctrl_inib_table[(id)].p_can_hth_cb_table[(box_no)].mutex = (mutex_state))

/*
 *  [CAN080] ���顼������(uint8)
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
 *  �ե��륿�ޥ���̤�����ѥ���ǥå���
 */
#define CAN_NO_MASK_IDX			0xFFU

/*
 *  ����������
 */
#define CAN_TRANSMIT			0x00U
#define CAN_RECEIVE				0x01U

/*
 *  CAN�ɥ饤�о��ּ���
 */
#define CAN_UNINIT				0x00U
#define CAN_READY				0x01U

/* �ͥ��ȥ�����Ⱥ����� */
#define CAN_INTERRUPT_NESTED_CNT_MAX		0xFFU

/* �ݡ���󥰥⡼�ɼ��� */
#define CAN_USE_POLLING_BUSOFF	0x01U
#define CAN_USE_POLLING_RX		0x02U
#define CAN_USE_POLLING_TX		0x04U
#define CAN_USE_POLLING_WAKEUP	0x08U


/*
 *  [CAN082][CAN083][CAN084] DET���顼�ޥ���(ON/OFF�ڤ��ؤ�)
 */
#if CAN_DEV_ERROR_DETECT == STD_ON
/* [CAN027][CAN028] DET���顼��ͭ���ξ�硤DET�����ƥॵ���ӥ���ƤӽФ� */
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
/* [CAN424][CAN089] DET���顼��̵���ξ�硤����������ʤ� */
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

/* [CAN431] �����å��ޥ���(MainFunction��) */
#define CAN_CHECK_INITIALIZED_MF(ApiId)					 \
	do {												 \
		if (can_init_flg == CAN_UNINIT) {				 \
			CAN_DET_REPORT_ERROR((ApiId), CAN_E_UNINIT); \
			goto error_exit;							 \
		}												 \
	} while (0)

/*
 *  DET�����Τ��륵���ӥ�ID
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
 *  [CAN414] �ܡ��졼���������
 */
typedef struct can_controller_baudrate_config_type {
	uint16	CanControllerBaudRate;
	uint8	CanControllerPropSeg;
	uint8	CanControllerSeg1;
	uint8	CanControllerSeg2;
	uint8	CanControllerSyncJumpWidth;
} Can_ControllerBaudrateConfigType;

/*
 *  HOH�ܥå����ơ��֥�����֥�å�
 */
typedef struct {
	uint8				CanControllerId;        /* CAN����ȥ���ID */
	uint8				box_obj_type;           /* ���������� */
	Can_HwHandleType	box_idx;                /* HRH�ޤ���HTH */
} Can_HohBoxType;

/*
 *  �����ܥå���CAN-ID�ơ��֥�����֥�å�
 */
typedef struct {
	Can_IdType	CanIdValue;         /* CAN-ID */
	uint8		filtermask_idx;     /* �ե��륿�ޥ����ơ��֥�Υ���ǥå��� */
} Can_RboxCanidType;

/*
 *  HTH�����֥�å�
 */
typedef struct can_hth_control_block {
	PduIdType	saved_pduid;        /* ������λ������PDU-ID��¸ */
	boolean		mutex;              /* �ߥ塼�ƥå������� */
} CAN_HTH_CB;

/*
 *  CAN����ȥ�������֥�å�
 */
typedef struct can_controller_initialization_block {
	uint8									CanIfCtrlId;            /* CanIf¦�Υ���ȥ���ID */
	uint8									tnum_baudrate;          /* �����ǽ�ʥܡ��졼�ȿ� */
	Can_HwHandleType						tnum_hth;               /* HTH�� */
	Can_HwHandleType						tnum_hrh;               /* HRH�� */
	uint8									tnum_filtermask;        /* �ե��륿�ޥ����� */
	uint8									use_polling;            /* �ݡ���󥰥⡼�ɻ��Ѵ��� */
	boolean									CanWakeupSupport;       /* �����������åץ��ݡ���̵ͭ */
	EcuM_WakeupSourceType					EcuMWakeupSourceId;     /* CanWakeupSourceRef�λ����� */
	const Can_ControllerBaudrateConfigType	*p_default_baudrate;    /* �ǥե���ȥܡ��졼�� */
	const Can_ControllerBaudrateConfigType	*p_baudrate_table;      /* ���ݡ��ȥܡ��졼�ȥꥹ�� */
	const Can_IdType						*p_filtermask_table;    /* �ե��륿�ޥ����ꥹ�� */
	const Can_HwHandleType					*p_rbox_hrh_table;      /* �����ܥå����ֹ梪HRH�Ѵ��ơ��֥����� */
	const Can_RboxCanidType					*p_rbox_canid_table;    /* �����ܥå���CAN-ID�ơ��֥� */
	CAN_HTH_CB * const						p_can_hth_cb_table;     /* HTH�����֥�å��ơ��֥� */
} CAN_CTRL_INIB;

/*
 *  [CAN413] Can����ե�����졼���������֥�å�
 */
typedef struct can_config_type {
	Can_HwHandleType		tnum_hoh;                   /* HOH�� */
	uint8					tnum_controller;            /* ����ȥ���� */
	const Can_HohBoxType	*p_hoh_box_table;           /* HOH���ܥå����ֹ��Ѵ��ơ��֥����� */
	const CAN_CTRL_INIB		*p_can_ctrl_inib_table;     /* ����ȥ��������֥�å��ơ��֥� */
} Can_ConfigType;

/*
 *  L-PDU-Callout�ؿ������
 */
typedef boolean (*Can_LpduCallout)(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);

/*
 *  Can�����ƥॵ���ӥ��ץ�ȥ��������
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
 *  Can����ߥ����ӥ��롼����ץ�ȥ��������
 */
extern void Can_IsrRx(uint8 Controller);
extern void Can_IsrTx(uint8 Controller);
extern void Can_IsrBusoff(uint8 Controller);
extern void Can_IsrWakeup(uint8 Controller);

extern const CAN_CTRL_INIB	can_ctrl_inib_table[];

/*
 *  Can����ե�����졼��������(Can_PBcfg.c)
 */
extern const Can_ConfigType	can_config[];

#endif /* TOPPERS_CAN_H */
