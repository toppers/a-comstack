/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2014 by FUJI SOFT INCORPORATED, JAPAN
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
 *  $Id: Can.c 1388 2015-06-04 05:48:42Z fsi-kaitori $
 */

/* [CAN034][CAN036][CAN394][CAN397][CAN390] */
/* [CAN222] Can�⥸�塼���ɬ�פʥǡ�������������줿�إå��ե����� */
#include "Os.h"
#include "ComStack_Types.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include "MemMap.h"
#include "EcuM_Cbk.h"

/*
 * (CAN077) CAN����ȥ�����ͤ˰�¸����������Ԥ�
 * (CAN284) 1��ECU��ʣ���ΰۤʤ�CAN����ȥ������Ѥ�����⡤1�Ĥΰ�¸�����б�����
 * (CAN385) 1��ECU��ʣ���ΰۤʤ�CAN����ȥ������Ѥ����硤AUTOSAR����Υ͡��ߥ󥰥���٥󥷥��˽���
 * (CAN386) 1�����CAN����ȥ���Τߤ���Ѥ����硤�ȼ��Υ͡��ߥ󥰥���٥󥷥��Ǥ褤
 * (CAN238) ������åפ�CAN����ȥ������Ѥ����硤¾�Υɥ饤�ФΥ����ӥ�����Ѥ��ʤ�
 * (CAN242) ���ե��åפ�CAN����ȥ������Ѥ����硤MCAL�Υ����ӥ�����Ѥ���
 * (CAN244) MCAL����ƤӽФ����褦�ʥ�����Хå����󶡤��ʤ�
 * (CAN391) ���ե��åפ�CAN����ȥ������Ѥ����硤Spi.h��include����
 * (CAN204) ��¸���γƴؿ���ǳ���߶ػߵ��Ĥ�Ԥ���硤
 *          �ͥ��ȸƽФ���������˽���������������߶ػ߾��֤�ݻ�����
 */
#include "Can_Target.h"

/* SchM_Can.h��RTE�����ͥ졼���ˤ����������� */
/* [CAN034][CAN406] */
#include "SchM_Can.h"

#if CAN_DEV_ERROR_DETECT == STD_ON
/* [CAN034][CAN393] */
#include "Det.h"
#endif /* CAN_DEV_ERROR_DETECT == STD_ON */


/*
 *  ���߼¹����Can����ե�����졼��������
 */
const Can_ConfigType			*p_cur_can_config;
const Can_HohBoxType			*p_cur_hoh_box_table;
const CAN_CTRL_INIB				*p_cur_can_ctrl_inib_table;

/* [CAN103] Can�ν��������(CAN_UNINIT�ǽ����) */
static uint8					can_init_flg = CAN_UNINIT;

/* ����߶ػߥͥ��ȥ������ */
extern uint8					can_interrupt_nested_cnt[];

/* �����륢���ȴؿ� */
#ifdef USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION
extern const Can_LpduCallout	CanLpduCalloutFunction;
#endif /* USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION */

/* Can_SetControllerModeư����֥ե饰 */
extern boolean					can_set_controller_mode_flg[];

/* CAN����ȥ�����־��� */
extern Can_StateTransitionType	can_current_state[];

/*
 *  �����ؿ��ץ�ȥ��������
 */
static boolean can_check_timeout_duration(uint8 Controller, Can_StateTransitionType Transition);

/*
 *  [CAN223] Can_Init
 */
void
Can_Init(const Can_ConfigType *Config)
{
	Can_HwHandleType	hth_idx;
	Can_HwHandleType	hrh_idx;
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN026] ���˽�����Ѥߤξ��ϥ��顼 */
	if (can_init_flg == CAN_READY) {
		goto error_exit;
	}

	/* [CAN175] NULL�����å� */
	if (Config == NULL_PTR) {
		/* [NCAN003] NULL_PTR�ξ�硤��Ƭ�Υ���ե�����졼�����������Ѥ��� */
		Config = &can_config[0];
	}

	/* [CAN056] ��������¹Ԥ��륳��ե����졼������������ */
	p_cur_can_config = Config;
	p_cur_hoh_box_table = Config->p_hoh_box_table;
	p_cur_can_ctrl_inib_table = Config->p_can_ctrl_inib_table;

	/*
	 * (CAN407) �ʲ����ư�¸���ؿ���ɬ�פʥ쥸�����ν������Ԥ�
	 * (CAN419) ���Ѥ��ʤ����Ƥ�CAN����ߤ�̵���ˤ���
	 * (CAN236)(CAN237) ��⡼�������׵��̵�뤹��褦�˽������Ԥ�
	 * (CAN239) CAN����ȥ���ǻ��Ѥ������ƤΥϡ��ɥ������꥽��������������
	 * (CAN259) ����ȥ����STOPPED���֤ˤ���
	 */

	/* [CAN245][CAN250] unit_phase1 */
	if (can_target_init_unit_phase1(p_cur_can_config) == FALSE) {
		goto error_exit;
	}

	/* [CAN245][CAN250][CAN053] ���Ѥ������ƤΥ���ȥ�����Ф����������� */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* CAN����ȥ�������֥�å����� */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);

		/* controller_phase1 */
		if (can_target_init_controller_phase1(ctrl_id, p_ctrl_inib) == FALSE) {
			goto error_exit;
		}

		/* �ǥե���ȥܡ��졼�Ȥ����ꤹ�� */
		can_target_change_baudrate(ctrl_id, p_ctrl_inib->p_default_baudrate);

		/* controller_phase2 */
		if (can_target_init_controller_phase2(ctrl_id, p_ctrl_inib) == FALSE) {
			goto error_exit;
		}

		/* �����᡼��ܥå�������� */
		for (hrh_idx = 0U; hrh_idx < GET_HRH_NUM(ctrl_id); hrh_idx++) {
			if (can_target_rbox_initialize(ctrl_id, p_ctrl_inib, hrh_idx) == FALSE) {
				goto error_exit;
			}
		}

		/* �����᡼��ܥå�������� */
		for (hth_idx = 0U; hth_idx < GET_HTH_NUM(ctrl_id); hth_idx++) {
			if (can_target_tbox_initialize(ctrl_id, p_ctrl_inib, hth_idx) == FALSE) {
				goto error_exit;
			}

			/* HTH�Υߥ塼�ƥå�������� */
			p_ctrl_inib->p_can_hth_cb_table[hth_idx].mutex = FALSE;
		}

		/* controller_phase3 */
		if (can_target_init_controller_phase3(ctrl_id, p_ctrl_inib) == FALSE) {
			goto error_exit;
		}

		/* ����߶ػߥͥ��ȥ�����Ƚ���� */
		can_interrupt_nested_cnt[ctrl_id] = 0U;

		/*  Can_SetControllerModeư����֥ե饰����� */
		can_set_controller_mode_flg[ctrl_id] = FALSE;

		/* CAN����ȥ�����־������� */
		can_current_state[ctrl_id] = CAN_T_STOP;
	}

	/* [CAN245][CAN250] unit_phase2 */
	if (can_target_init_unit_phase2(p_cur_can_config) == FALSE) {
		goto error_exit;
	}

	/* [CAN246] ���Ƥν�����λ��ˡ�Can�ν�������֤����ꤹ�� */
	can_init_flg = CAN_READY;

  normal_exit:
	return;

  error_exit:
	/* [CAN104][CAN174][CAN408] */
	CAN_DET_REPORT_ERROR(CANServiceId_Init, CAN_E_TRANSITION);
	/* [CAN091] */
	goto normal_exit;
}


/*
 *  [CAN224] Can_GetVersionInfo
 */
/* [CAN252] Can_GetVersionInfo��̵ͭ�ϥ���ե�����졼�������ڤ��ؤ� */
#if CAN_VERSION_INFO_API == STD_ON
/* [CAN251] �ޥ���Ǽ������Ƥ�褤��NULL�ݥ��󥿥����å��Τ���ؿ��Ȥ��� */
void
Can_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	/* [CAN177] */
	if (versioninfo == NULL_PTR) {
		CAN_DET_REPORT_ERROR(CANServiceId_GetVersionInfo, CAN_E_PARAM_POINTER);
	}

	/* [CAN105] �ƥС��������֤� */
	versioninfo->vendorID = CAN_VENDOR_ID;
	versioninfo->moduleID = CAN_MODULE_ID;
	versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;
}
#endif /* CAN_VERSION_INFO_API */

/* [CAN460] Can_CheckBaudrate��̵ͭ�ϥ���ե�����졼�������ڤ��ؤ� */
#if CAN_CHANGE_BAUDRATE_API == STD_ON
/*
 *  [CAN454] Can_CheckBaudrate
 */
Std_ReturnType
Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate)
{
	uint8				i;
	Std_ReturnType		ercd = E_NOT_OK;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN456] */
	CAN_CHECK_INITIALIZED_ERCD_STD_RETERN_TYPE(CANServiceId_CheckBaudrate);

	/* [CAN104][CAN457] */
	CAN_CHECK_CONTROLLER_ERCD_STD_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_CheckBaudrate);

	/* CAN����ȥ�������֥�å����� */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* ���ݡ��ȥܡ��졼�Ȥ�Ƚ�� */
	for (i = 0U; i < p_ctrl_inib->tnum_baudrate; i++) {
		if (p_ctrl_inib->p_baudrate_table[i].CanControllerBaudRate == Baudrate) {
			ercd = E_OK;
			break;
		}
	}

	/* [CAN458] ̤���ݡ��ȤΥܡ��졼�Ȥ����ꤵ�줿��硤DET���顼 */
	if (ercd == E_NOT_OK) {
		CAN_DET_REPORT_ERROR(CANServiceId_CheckBaudrate, CAN_E_PARAM_BAUDRATE);
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}

/*
 *  [CAN449] Can_ChangeBaudrate
 */
Std_ReturnType
Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate)
{
	uint8									i;
	Std_ReturnType							ercd = E_NOT_OK;
	const CAN_CTRL_INIB						*p_ctrl_inib;
	const Can_ControllerBaudrateConfigType	*p_baudrate_config;

	/* [CAN104][CAN026][CAN450] */
	CAN_CHECK_INITIALIZED_ERCD_STD_RETERN_TYPE(CANServiceId_ChangeBaudrate);

	/* [CAN104][CAN452] */
	CAN_CHECK_CONTROLLER_ERCD_STD_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_ChangeBaudrate);

	/* CAN����ȥ�������֥�å����� */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* ���ݡ��ȥܡ��졼�Ȥ�Ƚ�� */
	for (i = 0U; i < p_ctrl_inib->tnum_baudrate; i++) {
		if (p_ctrl_inib->p_baudrate_table[i].CanControllerBaudRate == Baudrate) {
			ercd = E_OK;

			/* �оݤΥܡ��졼�ȥꥹ�ȼ��� */
			p_baudrate_config = &p_ctrl_inib->p_baudrate_table[i];
			break;
		}
	}

	if (ercd == E_OK) {
		/* �ܡ��졼�Ȥ�������� */
		/* (CAN062) ɬ�פ˱����ơ�����ȥ���κƽ������Ԥ� */
		/* (CAN461) �������˥����������åץ��٥�Ȥ�ȯ��������硤EcuM�⥸�塼������Τ��� */
		/* (CAN255) �оݤΥ���ȥ���˴ؤ���쥸�����Τ����� */
		/* (CAN256) �оݤΥ���ȥ��餬STOPPED���֤ξ��Τߡ��ܡ��졼�Ȥ��ѹ����� */
		/* (CAN260) �ܡ��졼���ѹ��桤�оݤΥ���ȥ����STOPPED���֤�ݻ����� */
		/* (CAN422) �ܡ��졼���ѹ��ˤ�äơ��оݤΥ���ȥ��餬�ͥåȥ���˻��ä��뤳�ȤϤʤ� */
		if (can_target_change_baudrate(Controller, p_baudrate_config) == FALSE) {
			ercd = E_NOT_OK;
			/* (CAN453) CAN����ȥ��餬�ܡ��졼�Ȥ��ѹ��Ǥ��ʤ����֤ξ�硤DET���顼 */
			CAN_DET_REPORT_ERROR(CANServiceId_ChangeBaudrate, CAN_E_TRANSITION);
		}
	}
	else {
		/* [CAN451] ̤���ݡ��ȤΥܡ��졼�Ȥ����ꤵ�줿��硤DET���顼 */
		CAN_DET_REPORT_ERROR(CANServiceId_ChangeBaudrate, CAN_E_PARAM_BAUDRATE);
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}
#endif /* CAN_CHANGE_BAUDRATE_API == STD_ON */

/*
 *  [CAN230] Can_SetControllerMode
 */
Can_ReturnType
Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition)
{
	Can_ReturnType		ercd = CAN_OK;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN198] ����������å� */
	CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(CANServiceId_SetControllerMode);

	/* [CAN104][CAN199] ����ȥ���ID�����å� */
	CAN_CHECK_CONTROLLER_ERCD_CAN_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_SetControllerMode);

	/* Can_SetControllerModeư��ե饰��ư����(TRUE)������ */
	can_set_controller_mode_flg[Controller] = TRUE;

	/* CAN����ȥ�������֥�å����� */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* [CAN017] ���ꤵ�줿CAN����ȥ�����֤ذܹ� */
	/* [CAN398] �֥�å����ɻߤΤ���ˡ�GetCounterValue����Ѥ����⡼���ѹ���λ��Ƚ�̤��� */
	/* [CAN371] CanTimeoutDuration�ǻ��ꤵ�줿���֤����ͤȤ��ơ��ݡ���󥰤�Ԥ� */
	/* [CAN372] CanTimeoutDuration���вᤷ�Ƥ�⡼�ɤ��ڤ��ؤ��ʤ��ä���硤 */
	/*          Can_SetControllerMode�ϳ������졤Can_Mainfunction_Mode�ˤ��ݡ���󥰤�³���� */
	/* (CAN196) ɬ�פ˱����Ƴ���߶ػ�/���ľ��֤��ѹ����� */
	/* (CAN197) �ܹԸ�ξ��֤ǵ��Ĥ���ʤ�����ߤ�ػߤ��� */
	/* (CAN425) Can_DisableControllerInterrupts���ƤФ�Ƥ����硤����ߤ���Ĥ��ʤ� */
	/* (CAN426) ����Can_DisableControllerInterrupts���ƤФ�Ƥ����硤���ٳ���ߤ�ػߤ��ʤ� */
	switch (Transition) {
	case CAN_T_START:
		/*
		 * STOPPED -> STARTED
		 * (CAN261) CAN����ȥ����ͥåȥ���˻��ä�����
		 * (CAN409) CAN����ȥ��餬STOPPED���֤Ǥʤ����ˡ�CAN_T_START��
		 *          ���ꤵ�줿��硤DET���顼�Ȥ���
		 * (CAN384) ������Can_Init��Can_ChangeBaudrate�ǽ�������줿���ƤǺƽ��������
		 */
		if (can_target_start_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CAN����ȥ���ξ��֤δƻ� */
			if (can_check_timeout_duration(Controller, CAN_T_START) == TRUE) {
				/* [CAN373] ��̥쥤��ؤ����� */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STARTED);

				/* �оݤΥ���ȥ���ξ��֤򹹿����� */
				can_current_state[Controller] = CAN_T_START;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	case CAN_T_STOP:
		/*
		 * STARTED -> STOPPED
		 * (CAN263) CAN����ȥ����ͥåȥ���ؤλ��ä�λ����
		 * (CAN282) �ڥ�ǥ�����Υ�å�������¸�ߤ����硤����󥻥뤹��
		 * (CAN283) �ڥ�ǥ�����Υ�å��������Ф��륭��󥻥����ΤϹԤ�ʤ�
		 * (CAN410) CAN����ȥ��餬START�Ǥ�STOPPED���֤Ǥ�ʤ����ˡ�
		 *          CAN_T_STOP����ꤵ�줿��硤DET���顼�Ȥ���
		 */
		if (can_target_stop_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CAN����ȥ���ξ��֤δƻ� */
			if (can_check_timeout_duration(Controller, CAN_T_STOP) == TRUE) {
				/* [CAN373] ��̥쥤��ؤ����� */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

				/* �оݤΥ���ȥ���ξ��֤򹹿����� */
				can_current_state[Controller] = CAN_T_STOP;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	case CAN_T_SLEEP:
		/*
		 * STOPPED -> SLEEP
		 * (CAN265) CAN����ȥ����SLEEP���֤��ڤ��ؤ���
		 * (CAN290) �ϡ��ɥ�������SLEEP�⡼�ɤ򥵥ݡ��Ȥ��ʤ���硤����Ū��SLEEP���֤Ȥ���
		 * (CAN405) ����Ū��SLEEP���֤ϡ�Can_SetControllerMode(CAN_T_WAKEUP)�ƽФ��ˤ�곫�������
		 * (CAN411) CAN����ȥ��餬STOPPED�Ǥ�SLEEP���֤Ǥ�ʤ����ˡ�
		 *          CAN_T_SLEEP����ꤵ�줿��硤DET���顼�Ȥ���
		 */
		if (can_target_sleep_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CAN����ȥ���ξ��֤δƻ� */
			if (can_check_timeout_duration(Controller, CAN_T_SLEEP) == TRUE) {
				/* [CAN373] ��̥쥤��ؤ����� */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_SLEEP);

				/* �оݤΥ���ȥ���ξ��֤򹹿����� */
				can_current_state[Controller] = CAN_T_SLEEP;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	case CAN_T_WAKEUP:
		/*
		 * SLEEP -> STOPPED
		 * (CAN267) �ϡ��ɥ�������SLEEP�⡼�ɤ򥵥ݡ��Ȥ��ʤ���硤����Ū��
		 *          SLEEP���֤�����������ȥ���ؤν����ϲ���Ԥ�ʤ�
		 * (CAN412) CAN����ȥ��餬SLEEP�Ǥ�STOPPED���֤Ǥ�ʤ����ˡ�
		 *          CAN_T_SLEEP����ꤵ�줿��硤DET���顼�Ȥ���
		 */
		/* (CAN294) �����������å׾��֤�����å�����ݤϡ������������å׳���ߤ�ػߤ��� */
		/* (CAN048) SLEEP��˥����������åפ�����硤�ܥ����ƥॵ���ӥ���CAN_T_WAKEUP����ꤵ��Ƥ�CAN_NOT_OK���֤� */
		if (can_target_wakeup_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CAN����ȥ���ξ��֤δƻ� */
			if (can_check_timeout_duration(Controller, CAN_T_WAKEUP) == TRUE) {
				/* [CAN373] ��̥쥤��ؤ����� */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

				/* �оݤΥ���ȥ���ξ��֤򹹿����� */
				can_current_state[Controller] = CAN_T_WAKEUP;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	default:
		/* [CAN200] �������۾�ξ�� */
		ercd = CAN_NOT_OK;
		CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		break;
	}

  error_exit:
	/* [CAN091] */

	/* Can_SetControllerModeư��ե饰�������(FALSE)������ */
	can_set_controller_mode_flg[Controller] = FALSE;

	return(ercd);
}

/*
 *  [CAN231] Can_DisableControllerInterrupts
 */
void
Can_DisableControllerInterrupts(uint8 Controller)
{
	/* [CAN104][CAN026][CAN205] */
	CAN_CHECK_INITIALIZED(CANServiceId_DisableControllerInterrupts);

	/* [CAN104][CAN206] */
	CAN_CHECK_CONTROLLER((Controller < GET_CONTROLLER_NUM()), CANServiceId_DisableControllerInterrupts);

	/* �ͥ��ȥ������Ƚ�� */
	if (can_interrupt_nested_cnt[Controller] == CAN_INTERRUPT_NESTED_CNT_MAX) {
		/*�����Ķ�� */
		CAN_DET_REPORT_ERROR(CANServiceId_DisableControllerInterrupts, CAN_E_FATAL);
		goto error_exit;
	}

	/*
	 * ����߶ػ߽���
	 * [CAN049] ����ߵ��ľ��֤Υ���ȥ���ξ��Τ߽�������
	 */
	if (can_interrupt_nested_cnt[Controller] == 0U) {
		if (can_target_disable_controller_interrupts(Controller) == FALSE) {
			CAN_DET_REPORT_ERROR(CANServiceId_DisableControllerInterrupts, CAN_E_FATAL);
		}
	}

	/* [CAN202] �ͥ��ȸƽФ����������Ԥäơ��տޤ�������ߵ��Ĥˤʤ�ʤ��褦�ˤ��� */
	can_interrupt_nested_cnt[Controller]++;

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN232] Can_EnableControllerInterrupts
 */
void
Can_EnableControllerInterrupts(uint8 Controller)
{
	/* [CAN104][CAN026][CAN209] */
	CAN_CHECK_INITIALIZED(CANServiceId_EnableControllerInterrupts);

	/* [CAN104][CAN210] */
	CAN_CHECK_CONTROLLER((Controller < GET_CONTROLLER_NUM()), CANServiceId_EnableControllerInterrupts);

	/*
	 * �ͥ��ȥ������Ƚ��
	 * [CAN208] Disable���ƤФ�Ƥ��ʤ����Ϥʤˤ⤷�ʤ�
	 */
	if (can_interrupt_nested_cnt[Controller] != 0U) {
		/*
		 * �ͥ��ȥ�����ȥǥ������
		 * [CAN050] �ͥ��ȸƽФ����������Ԥäơ��տޤ�������ߵ��Ĥˤʤ�ʤ��褦�ˤ���
		 */
		can_interrupt_nested_cnt[Controller]--;

		if (can_interrupt_nested_cnt[Controller] == 0U) {
			/* ����ߵ��Ľ��� */
			if (can_target_enable_controller_interrupts(Controller) == FALSE) {
				CAN_DET_REPORT_ERROR(CANServiceId_EnableControllerInterrupts, CAN_E_FATAL);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN360] Can_CheckWakeup
 */
Can_ReturnType
Can_CheckWakeup(uint8 Controller)
{
	Can_ReturnType ercd;

	/* [CAN104][CAN026][CAN362] */
	CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(CANServiceId_CheckWakeup);

	/* [CAN104][CAN363] */
	CAN_CHECK_CONTROLLER_ERCD_CAN_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_CheckWakeup);

	/* (CAN361) ����SLEEP���֤ذܹԤ��Ƥ��饦���������åפ򸡽Ф������ɤ������֤� */
	if (can_target_check_wakeup(Controller) != FALSE) {
		ercd = CAN_OK;
	}
	else {
		ercd = CAN_NOT_OK;
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}

/*
 *  [CAN233] Can_Write
 */
Can_ReturnType
Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
	Can_ReturnType		ercd;
	uint8				ctrl_id;
	Can_HwHandleType	tbox_index;

	/* [CAN104][CAN026][CAN216] */
	CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(CANServiceId_Write);

	/* [CAN104][CAN217] */
	CAN_CHECK_HTH_ERCD_CAN_RETERN_TYPE(((Hth < GET_HOH_NUM()) && (GET_BOX_OBJ_TYPE(Hth) == CAN_TRANSMIT)), CANServiceId_Write);

	/* [CAN104][CAN218] */
	CAN_CHECK_DLC_ERCD_CAN_RETERN_TYPE((PduInfo->length <= CAN_MAX_DLC), CANServiceId_Write);

	/* [CAN104][CAN219] */
	CAN_CHECK_SDU_ERCD_CAN_RETERN_TYPE((PduInfo->sdu != NULL_PTR), CANServiceId_Write);

	/* ����ȥ���ID���� */
	ctrl_id = GET_CONTROLLER_ID(Hth);

	/* �����᡼��ܥå����Υ���ǥå������� */
	tbox_index = GET_BOX_IDX(Hth);

	/* [CAN011] �ǡ�����������ݻ����뤿��˽񤭹��������¾���� */
	/* ��¾���� */
	SchM_Enter_Can_Reentrant();

	/* [CAN212] HTH�Υߥ塼�ƥå���Ƚ�� */
	if (GET_HTH_MUTEX(ctrl_id, tbox_index) == FALSE) {
		/* HTH�Υߥ塼�ƥå������� */
		SET_HTH_MUTEX(ctrl_id, tbox_index, TRUE);

		ercd = CAN_OK;
	}
	else {
		/* [CAN213][CAN214][CAN215][CAN434] �ߥ塼�ƥå����������Ѥߤξ��ϡ�CAN_BUSY���֤� */
		ercd = CAN_BUSY;
	}

	/* ��¾��λ */
	SchM_Exit_Can_Reentrant();

	if (ercd == CAN_OK) {
		/* [CAN276] �������������λ�����Ѥ�PDU-ID���ݻ����� */
		SET_SAVED_PDU_ID(ctrl_id, tbox_index, PduInfo->swPduHandle);

		/*
		 * �����ǡ����ڤ������׵�����
		 * [CAN275] �����������Τ���¾������»ܤ��ʤ�
		 * (CAN059) �ǡ��������0���ܤ����Ǥ�����������7���ܤ����Ǥ�Ǹ����������
		 * (CAN427) �ϡ��ɥ�������ΥХåե�ɽ���˴ؤ�餺��Can_PduType���˴ޤޤ��ǡ����������Ѥ���
		 */
		ercd = can_target_transmit(ctrl_id, Hth, tbox_index, PduInfo);

		/* HTH�Υߥ塼�ƥå������� */
		SET_HTH_MUTEX(ctrl_id, tbox_index, FALSE);
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}

/*
 *  [CAN007][CAN099][CAN280][CAN225][NCAN002] Can_MainFunction_Write
 */
/* [CAN178] �ݡ���󥰤ˤ����������Ѥ��ʤ���硤�ܴؿ���������ʤ� */
#ifdef USE_CAN_TX_POLLING
void
Can_MainFunction_Write(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN179] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Write);

	/* [CAN031] ������λ���ΤΥݡ���󥰤�Ԥ� */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* �оݥ���ȥ��餬�ݡ���󥰤ξ��ˤΤ߼¹� */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_TX) != 0x00U) {
			if (can_target_polling_tx(ctrl_id) != FALSE) {
				Can_IsrTx(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_TX_POLLING */

/*
 *  [CAN007][CAN099][CAN280][CAN226][NCAN001] Can_MainFunction_Read
 */
/* [CAN180] �ݡ���󥰤ˤ���������Ѥ��ʤ���硤�ܴؿ���������ʤ� */
#ifdef USE_CAN_RX_POLLING
void
Can_MainFunction_Read(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN181] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Read);

	/* [CAN108] ������λ���ΤΥݡ���󥰤�Ԥ� */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* �оݥ���ȥ��餬�ݡ���󥰤ξ��ˤΤ߼¹� */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_RX) != 0x00U) {
			if (can_target_polling_rx(ctrl_id) != FALSE) {
				/* [CAN396] ���̼������� */
				Can_IsrRx(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_RX_POLLING */

/*
 *  [CAN007][CAN099][CAN280][CAN227] Can_MainFunction_BusOff
 */
/* [CAN183] �ݡ���󥰤ˤ��Х��������Τ���Ѥ��ʤ���硤�ܴؿ���������ʤ� */
#ifdef USE_CAN_BUSOFF_POLLING
void
Can_MainFunction_BusOff(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN184] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_BusOff);

	/* [CAN109] �Х��������ΤΥݡ���󥰤�Ԥ� */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* �оݥ���ȥ��餬�ݡ���󥰤ξ��ˤΤ߼¹� */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_BUSOFF) != 0x00U) {
			if (can_target_polling_busoff(ctrl_id) != FALSE) {
				Can_IsrBusoff(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_BUSOFF_POLLING */

/*
 *  [CAN007][CAN099][CAN280][CAN228] Can_MainFunction_Wakeup
 */
/* [CAN185] �ݡ���󥰤ˤ�륦���������å����Τ���Ѥ��ʤ���硤�ܴؿ���������ʤ� */
#ifdef USE_CAN_WAKEUP_POLLING
void
Can_MainFunction_Wakeup(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN186] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Wakeup);

	/* [CAN112] �����������å����ΤΥݡ���󥰤�Ԥ� */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* �оݥ���ȥ��餬�ݡ���󥰤ξ��ˤΤ߼¹� */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_WAKEUP) != 0x00U) {
			if (can_target_polling_wakeup(ctrl_id) != FALSE) {
				Can_IsrWakeup(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_WAKEUP_POLLING */

/*
 *  [CAN368] Can_MainFunction_Mode
 */
void
Can_MainFunction_Mode(void)
{
	uint8					ctrl_id;
	Can_StateTransitionType	ret_state;
	const CAN_CTRL_INIB		*p_ctrl_inib;

	/* [CAN104][CAN026][CAN379] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Mode);

	/* [CAN369] �⡼���ڤ��ؤ�긡�ФΥݡ���󥰤�Ԥ� */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* Can_SetControllerModeư����֥ե饰Ƚ�� */
		if (can_set_controller_mode_flg[ctrl_id] == FALSE) {
			/*
			 * [CAN370] CAN����ȥ���ξ��֤��Ѳ��������Ȥ�����å�����
			 *          �������ѹ����줿�顤CanIf_ControllerModeIndication�����Τ���
			 *          CAN����ȥ���ξ��֤򹹿�����
			 */
			ret_state = can_target_get_mode(ctrl_id);

			if (ret_state != can_current_state[ctrl_id]) {
				/* CAN����ȥ�������֥�å����� */
				p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);

				/* CAN����ȥ������Ƚ�� */
				switch (ret_state) {
				case CAN_T_START:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STARTED);

					can_current_state[ctrl_id] = CAN_T_START;
					break;
				case CAN_T_STOP:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

					can_current_state[ctrl_id] = CAN_T_STOP;
					break;
				case CAN_T_SLEEP:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_SLEEP);

					can_current_state[ctrl_id] = CAN_T_SLEEP;
					break;
				case CAN_T_WAKEUP:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

					can_current_state[ctrl_id] = CAN_T_WAKEUP;
					break;
				default:
					CAN_DET_REPORT_ERROR(CANServiceId_MainFunction_Mode, CAN_E_TRANSITION);
					break;
				}
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN099][CAN035][CAN033] CAN������λ���γ���ߥ����ӥ��롼����
 */
void
Can_IsrRx(uint8 Controller)
{
	Can_IdType			can_id;
	uint8				can_dlc;
	uint8				can_sdu[CAN_MAX_DLC];
	Can_HwHandleType	rbox_idx;
	boolean				ret = TRUE;

	/* (CAN420) ������׵�Υ��ꥢ�ϡ�ɬ�פ˱�����C2ISR¦���б����� */

	while (1) {
		/* �����᡼��ܥå������� */
		if (can_target_check_and_get_rbox(Controller, &rbox_idx) == FALSE) {
			/* ������å�����̵�� */
			break;
		}

		/* �����᡼��ܥå����Υ���ǥå���������å� */
		CAN_CHECK_MAILBOX_INDEX_NUM((rbox_idx <= GET_HRH_NUM(Controller)), CANServiceId_IsrRx);

		/*
		 * ����ID�Υǡ�������
		 * (CAN012) �����ǡ����ΰ�������ݾڤ���
		 * (CAN060) ��Ƭ�μ����ǡ�����ǡ��������0���ܤ����Ǥ˳�Ǽ����
		 *          �����μ����ǡ�����7���ܤ����Ǥ˳�Ǽ����
		 * (CAN299)(CAN300) ��Χ���������ǡ�����������ѿ�(can_sdu)�˥��ԡ�����
		 */
		if (can_target_get_rdata(Controller, rbox_idx, &can_id, &can_dlc, &can_sdu[0]) == TRUE) {
#ifdef USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION
			/* [CAN443] �����륢���Ƚ��� */
			ret = CanLpduCalloutFunction(rbox_idx, can_id, can_dlc, can_sdu);
#endif /* USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION */
			/* [CAN444] �����륢���Ƚ�����FALSE�ξ�硤�����������³���ʤ� */
			if (ret == TRUE) {
				/* [CAN279][CAN396] ������� */
				CanIf_RxIndication(GET_RBOX_CAN_OBJ_ID(Controller, rbox_idx), can_id, can_dlc, &can_sdu[0]);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN099][CAN035][CAN033] CAN������λ���γ���ߥ����ӥ��롼����
 */
void
Can_IsrTx(uint8 Controller)
{
	Can_HwHandleType tbox_idx;

	/* (CAN420) ������׵�Υ��ꥢ�ϡ�ɬ�פ˱�����C2ISR¦���б����� */

	while (1) {
		/* �����᡼��ܥå������� */
		if (can_target_check_and_get_tbox(Controller, &tbox_idx) == FALSE) {
			/* ������å�����̵�� */
			break;
		}

		/* �����᡼��ܥå����Υ���ǥå���������å� */
		CAN_CHECK_MAILBOX_INDEX_NUM((tbox_idx <= GET_HTH_NUM(Controller)), CANServiceId_IsrTx);

		/* [CAN016] ��̥쥤��ؤ����� */
		CanIf_TxConfirmation(GET_SAVED_PDU_ID(Controller, tbox_idx));
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN099][CAN035][CAN033] CAN�Х��������γ���ߥ����ӥ��롼����
 */
void
Can_IsrBusoff(uint8 Controller)
{
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* (CAN420) ������׵�Υ��ꥢ�ϡ�ɬ�פ˱�����C2ISR¦���б����� */

	/* CAN����ȥ�������֥�å����� */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* [CAN020] ���֤�STOPPED�ذܹԤ�����̥쥤������� */
	/* (CAN272) STOPPED�ذܹԸ���оݥ���ȥ��餬CAN�ͥåȥ���˴�Ϳ���ʤ����Ȥ��ݾڤ��� */
	/* (CAN273) �����Ԥ���å������������硤��̥쥤��إ���󥻥����Τ򤻤��ˡ������򥭥�󥻥뤹�� */
	/* (CAN274) �ϡ��ɥ������ˤ�뼫ư�Х�����������̵���ˤ��� */
	if (can_target_stop_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
		CanIf_ControllerBusOff(Controller);
	}
	else {
		CAN_DET_REPORT_ERROR(CANServiceId_IsrBusoff, CAN_E_FATAL);
	}
}

/*
 *  [CAN099][CAN035][CAN033] CAN�����������å����γ���ߥ����ӥ��롼����
 */
void
Can_IsrWakeup(uint8 Controller)
{
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* (CAN420) ������׵�Υ��ꥢ�ϡ�ɬ�פ˱�����C2ISR¦���б����� */

	/* CAN����ȥ�������֥�å����� */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* [CAN270] ���֤�STOPPED�ذܹԤ��� */
	if (can_target_stop_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
		/* [CAN271][CAN364] EcuM������ */
		if (p_ctrl_inib->CanWakeupSupport != FALSE) {
			EcuM_CheckWakeup(p_ctrl_inib->EcuMWakeupSourceId);
		}
	}
	else {
		CAN_DET_REPORT_ERROR(CANServiceId_IsrWakeup, CAN_E_FATAL);
	}

	/* [CAN269] �����������å��оݤΥ���ȥ�����Ф��ơ�����ʾ岿�⤷�ʤ� */
}

/*
 *  CAN����ȥ���ξ��ִƻ����
 */
boolean
can_check_timeout_duration(uint8 Controller, Can_StateTransitionType Transition)
{
	boolean		ret = TRUE;
	TickType	start_time;
	TickType	eval_time;
	TickType	total_eval_time = 0U;
	StatusType	ercd;

	/* ��������ͼ��� */
	ercd = GetCounterValue(CAN_COUNTER, &start_time);

	/* ��������ͼ���Ƚ�� */
	if (ercd != E_OK) {
		ret = FALSE;
		CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_FATAL);
		goto error_exit;
	}

	/* CAN����ȥ���Υ⡼�ɼ��� */
	while (can_target_get_mode(Controller) != Transition) {
		/* �������Ƚ��� */
		can_target_busy_wait();

		/* �вᥫ������ͼ��� */
		ercd = GetElapsedValue(CAN_COUNTER, &start_time, &eval_time);

		/* �вᥫ������ͼ���Ƚ�� */
		if (ercd != E_OK) {
			ret = FALSE;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_FATAL);
			goto error_exit;
		}

		/* �вᥫ������ͤκ�ʬ�û� */
		total_eval_time += eval_time;

		/* [CAN262][CAN264][CAN266][CAN268] CAN����ȥ���Υ⡼�ɼ�����������λ����Τ��»��֤ޤ��Ԥ� */
		if ((CAN_COUNTER_TICKS2SEC(total_eval_time)) > CAN_TIMEOUT_DURATION) {
			ret = FALSE;
			break;
		}
	}

  error_exit:
	return(ret);
}


/*
 *  �����¸���Ǥ�̤���ݡ��ȵ�ǽ
 *    <CAN395> ���顼���Х����ߥ󥰤ϥ������åȰ�¸�Τ����¸�����б�����
 *    <CAN365><CAN366><CAN367> R4.1�Ǻ�����줿���ᡤ�ǥХå��˴ؤ����׵���б����ʤ�
 *    <CAN079> R4.1��C��������롼�뤬������줿���ᡤ�б����ʤ�
 *    <CAN423> ��ĥ�ե����ޥåȤˤ�̤�б�
 *    <CAN277><CAN401><CAN402><CAN403><CAN076> �ޥ��������̤���ݡ���
 *    <CAN278><CAN432><CAN285><CAN286><CAN433><CAN399><CAN400><CAN287><CAN288> ��������󥻥��̤���ݡ���
 *    <CAN441><CAN442> ��å������ܥå�����Υݡ������MainFunction��̤���ݡ���
 *    <CAN445><CAN446><CAN447> Icu�⥸�塼��˴ؤ�����ͤ�̤���ݡ���
 *    <CAN392> Dem���������륨�顼������¸�ߤ��ʤ����ᡤ̤���ݡ���
 *
 *  ���ϡ��ɥ�������ȥꥬ���Ȥ���SLEEP���ְܹԽ������Ф����׵�
 *    (CAN257) �ϡ��ɥ�������SLEEP�⡼�ɤ򥵥ݡ��Ȥ����硤����ȥ����SLEEP���֤��ڤ��ؤ���
 *    (CAN258) �ϡ��ɥ�������SLEEP�⡼�ɤ򥵥ݡ��Ȥ��ʤ���硤����Ū��SLEEP���֤�
 *             ���ߥ�졼�Ȥ�������ȥ����STOPPED���֤ˤ���
 *    (CAN404) ����Ū��SLEEP�⡼�ɤδ֤ϡ�����ȥ����STOPPED���֤�ݻ�����
 *
 *  ������¾�λ�������
 *    [CAN240] Mcu�⥸�塼��ؤ��׵����Ǥ���
 *    [CAN455] CanIf�⥸�塼��ؤ��׵����Ǥ���
 *    [CAN058][CAN234][CAN235] ��Ϣ���볰��I/F�ؤ��׵����Ǥ���
 *    [CAN459] �桼���ؤ���ջ���Ǥ���
 *    [CAN110] MainFunction�μ¹Խ���ؤ��׵᤬�ʤ����ᡤ��������б�������
 *    (CAN239) I/O�ݡ��Ȥν������Port�⥸�塼��ǹԤ��ȵ��ꤵ��Ƥ��뤬��
 *             Port�⥸�塼����ά���ơ�OS���뤤�ϳư�¸���ǽ������ǽ�Ȥ���
 *    <CAN418> Can�⥸�塼��Τߤǻ��Ѥ�������䥰���Х��ѿ����ؿ����ܥե�����ǤΤ�
 *             �������ȵ��ꤵ��Ƥ��뤬���������åȰ�¸��/���¸���ڤ�ʬ���Τ��ᡤ
 *             �̥ե�����Ǥ������ǽ�Ȥ���
 *    [CAN448][CAN999] �׵���ͤǤϤʤ�
 */
