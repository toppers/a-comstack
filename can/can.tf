$
$  TOPPERS/A-CAN
$      Automotive CAN
$
$  Copyright (C) 2013-2014 by Center for Embedded Computing Systems
$              Graduate School of Information Science, Nagoya Univ., JAPAN
$  Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
$  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
$  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
$  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
$  Copyright (C) 2013-2014 by TOSHIBA CORPORATION, JAPAN
$  Copyright (C) 2013-2014 by Witz Corporation, JAPAN
$
$  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
$  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
$  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
$  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
$      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
$      ����������˴ޤޤ�Ƥ��뤳�ȡ�
$  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
$      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
$      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
$  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
$      �ȡ�
$    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
$        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
$    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
$        ��𤹤뤳�ȡ�
$  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
$      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
$      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
$      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
$      ���դ��뤳�ȡ�
$
$  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
$  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
$  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
$  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
$
$  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
$  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
$  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
$  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
$  ����Ǥ�����ʤ���
$
$  $Id: can.tf 13 2015-07-15 08:58:53Z fujisft-kaitori $
$

$ ====================================================================
$ booleanȽ��ؿ�
$ ====================================================================
$FUNCTION IS_TRUE$
	$true_list = {1, "1", "true", "TRUE", "ON", "ENABLE"}$
	$false_list = {0, "0", "false", "FALSE", "OFF", "DISABLE"}$
	$error_flag = 1$
	
	$FOREACH false false_list$
		$IF EQ(false, ARGV[1])$
			$check_result = VALUE("FALSE", 0)$
			$error_flag = 0$
		$END$
	$END$
	$FOREACH true true_list$
		$IF EQ(true, ARGV[1])$
			$check_result = VALUE("TRUE", 1)$
			$error_flag = 0$
		$END$
	$END$

	$IF error_flag > 0$
		$ERROR ARGV[2]$$FORMAT(_("%1% must be boolean type"), ARGV[1])$$END$
	$END$

	$RESULT = check_result$
$END$

$ ====================================================================
$  ����ե������åȤ��ȤΥꥹ�Ȥ����
$ ====================================================================
$FUNCTION MAKE_CFG_LIST$
	$ctrl_id_num_max = 0$

	$FOREACH config_id CanConfigSet.ID_LIST$
$		// [CAN354_Conf] CanController
		$new_list = {}$
		$FOREACH ctrl_id CanController.ID_LIST$
			$IF EQ(config_id, CanController.PARENT[ctrl_id])$
				$new_list = APPEND(new_list, ctrl_id)$
			$END$
		$END$
		$CanConfigSet.ctrl_id_list[config_id] = new_list$
		$CanConfigSet.ctrl_id_num[config_id] = LENGTH(new_list)$

$		// ����ȥ�����Υ��顼��ǧ
		$IF (CanConfigSet.ctrl_id_num[config_id] > TARGET_TMAX_CONTROLLER_NUM)$
			$ERROR$$FORMAT(_("There is too much CanController(%1% > %2%) of CanConfigSet(%3%)."),
								CanConfigSet.ctrl_id_num[config_id], TARGET_TMAX_CONTROLLER_NUM, config_id)$$END$
			$DIE()$
		$END$

$		// ����ȥ�����κ��������
		$IF (ctrl_id_num_max < CanConfigSet.ctrl_id_num[config_id])$
			$ctrl_id_num_max = CanConfigSet.ctrl_id_num[config_id]$
		$END$
	$END$

	$FOREACH ctrl_id CanController.ID_LIST$
$		// [CAN387_Conf] CanControllerBaudRateConfig
		$new_list = {}$
		$FOREACH baudrate_id CanControllerBaudrateConfig.ID_LIST$
			$IF EQ(ctrl_id, CanControllerBaudrateConfig.PARENT[baudrate_id])$
				$new_list = APPEND(new_list, baudrate_id)$
			$END$
		$END$
		$CanController.baudrate_list[ctrl_id] = new_list$
		$CanController.baudrate_num[ctrl_id] = LENGTH(new_list)$

		$new_list = {}$
		$new_hrh_list = {}$
		$new_hth_list = {}$
		$rx_box_cnt = 0$
		$tx_box_cnt = 0$
$		// [CAN324_Conf] CanHardwareObject
		$FOREACH hoh_id CanHardwareObject.ID_LIST$
$			// [CAN322_Conf] CanControllerRef
			$IF EQ(ctrl_id, CanHardwareObject.CanControllerRef[hoh_id])$
				$new_list = APPEND(new_list, hoh_id)$
				$CanHardwareObject.ctrl_id[hoh_id] = ctrl_id$
$				// [CAN327_Conf] CanObjectType
				$IF EQ(CanHardwareObject.CanObjectType[hoh_id], "RECEIVE")$
					$new_hrh_list = APPEND(new_hrh_list, hoh_id)$
					$CanHardwareObject.box_idx[hoh_id] = rx_box_cnt$
					$rx_box_cnt = rx_box_cnt + 1$
				$ELIF EQ(CanHardwareObject.CanObjectType[hoh_id], "TRANSMIT")$
					$new_hth_list = APPEND(new_hth_list, hoh_id)$
					$CanHardwareObject.box_idx[hoh_id] = tx_box_cnt$
					$tx_box_cnt = tx_box_cnt + 1$
				$END$
			$END$
		$END$

		$CanController.hoh_list[ctrl_id] = new_list$

		$CanController.hrh_list[ctrl_id] = new_hrh_list$
		$CanController.hrh_num[ctrl_id] = LENGTH(new_hrh_list)$

		$CanController.hth_list[ctrl_id] = new_hth_list$
		$CanController.hth_num[ctrl_id] = LENGTH(new_hth_list)$

$		// �᡼��ܥå�������������å�
		$IF ISFUNCTION("CHECK_MAILBOX_NUM")$
			$ret = 1$
$			// (CAN022)(CAN024) CAN����ȥ����¸�Υ����å�
			$ret = CHECK_MAILBOX_NUM(ctrl_id, CanController.hrh_num[ctrl_id], CanController.hth_num[ctrl_id])$

			$IF (ret == 0)$
				$ERROR$$FORMAT(_("There is little number of the Mailboxes(%1%) for the number of HRH(%2%) and HTH(%3%)."),
									ctrl_id, CanController.hrh_num[ctrl_id], CanController.hth_num[ctrl_id])$$END$
				$DIE()$
			$END$
		$END$

$		// [CAN351_Conf] CanFilterMask
		$new_list = {}$
		$FOREACH filtermask_id CanFilterMask.ID_LIST$
			$IF EQ(ctrl_id, CanFilterMask.PARENT[filtermask_id])$
				$new_list = APPEND(new_list, filtermask_id)$
			$END$
		$END$
		$CanController.filtermask_list[ctrl_id] = new_list$
		$CanController.filtermask_num[ctrl_id] = LENGTH(new_list)$

$		// CanFilterMask����������å�
		$IF (CanController.filtermask_num[ctrl_id]) > TARGET_TMAX_FILTERMASK_NUM$
			$ERROR$$FORMAT(_("There is too much CanFilterMask(%1% > %2%) of CanController(%3%)."),
								CanController.filtermask_num[ctrl_id], TARGET_TMAX_FILTERMASK_NUM, ctrl_id)$$END$
			$DIE()$
		$END$

$		// [CAN359_Conf] CanWakeupSourceRef
		$IF LENGTH(CanController.CanWakeupSourceRef[ctrl_id])$
			$CanController.wakeup_source_id[ctrl_id] = EcuMWakeupSource.EcuMWakeupSourceId[CanController.CanWakeupSourceRef[ctrl_id]]$
		$ELSE$
			$CanController.wakeup_source_id[ctrl_id] = 0$
		$END$
	$END$

	$FOREACH config_id CanConfigSet.ID_LIST$
$		// CanConfigSet���Ȥ�HOH�ꥹ��
		$new_list = {}$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$new_list = APPEND(new_list, CanController.hoh_list[ctrl_id])$
		$END$
		
		$CanConfigSet.hoh_list[config_id] = new_list$
		$CanConfigSet.hoh_num[config_id] = LENGTH(new_list)$
	$END$
$END$


$ ====================================================================
$  IDϢ�֥����ȴؿ�
$ ====================================================================
$FUNCTION ID_SORT$
$	// [CAN316_Conf] CanControllerId ��˥�����
	$FOREACH config_id CanConfigSet.ID_LIST$
$		// [CAN316_Conf] CanControllerId
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanConfigSet.ctrl_id_list[config_id]) - 1)$
			$find = 0$
			$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
				$IF CanController.CanControllerId[ctrl_id] == index$
					$new_list = APPEND(new_list, ctrl_id)$
					$find = find + 1$
				$END$
			$END$
$			// CanControllerId��0�����Ϣ�֤Ǥʤ����ϥ��顼
			$IF find == 0$
				$ERROR$$FORMAT(_("CanControllerId(%1%\) is not found. CanControllerId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("CanControllerId(%1%\) is duplicated. CanControllerId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanConfigSet.ctrl_id_list[config_id] = new_list$
	$END$

$	// [CAN326_Conf] HOH�ꥹ�Ȥ� CanObjectId ��˥�����
	$FOREACH config_id CanConfigSet.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanConfigSet.hoh_list[config_id]) - 1)$
			$find = 0$
			$FOREACH hoh_id CanConfigSet.hoh_list[config_id]$
				$IF CanHardwareObject.CanObjectId[hoh_id] == index$
					$new_list = APPEND(new_list, hoh_id)$
					$find = find + 1$
				$END$
			$END$
$			// CanObjectId��0�����Ϣ�֤Ǥʤ����ϥ��顼
			$IF find == 0$
				$ERROR$$FORMAT(_("CanObjectId(%1%\) is not found. CanObjectId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("CanObjectId(%1%\) is duplicated. CanObjectId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanConfigSet.hoh_list[config_id] = new_list$
	$END$

	$FOREACH ctrl_id CanController.ID_LIST$
$		// HRH�ꥹ�Ȥ�����ܥå����ֹ��˥�����
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanController.hrh_list[ctrl_id]) - 1)$
			$find = 0$
			$FOREACH hrh_id CanController.hrh_list[ctrl_id]$
				$IF CanHardwareObject.box_idx[hrh_id] == index$
					$new_list = APPEND(new_list, hrh_id)$
					$find = find + 1$
				$END$
			$END$
$			// box_idx��0�����Ϣ�֤Ǥʤ����ϥ��顼
			$IF find == 0$
				$ERROR$$FORMAT(_("box_idx(%1%\) is not found. box_idx should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("box_idx(%1%\) is duplicated. box_idx should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanController.hrh_list[ctrl_id] = new_list$
		
$		// HTH�ꥹ�Ȥ������ܥå����ֹ��˥�����
$		// [CAN100] HTH�ι���
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanController.hth_list[ctrl_id]) - 1)$
			$find = 0$
			$FOREACH hth_id CanController.hth_list[ctrl_id]$
				$IF CanHardwareObject.box_idx[hth_id] == index$
					$new_list = APPEND(new_list, hth_id)$
					$find = find + 1$
				$END$
			$END$
$			// box_idx��0�����Ϣ�֤Ǥʤ����ϥ��顼
			$IF find == 0$
				$ERROR$$FORMAT(_("box_idx(%1%\) is not found. box_idx should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("box_idx(%1%\) is duplicated. box_idx should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanController.hth_list[ctrl_id] = new_list$
	$END$
$END$

$ ====================================================================
$  [CAN023] ���顼�����å��ؿ�
$ ====================================================================
$FUNCTION ERROR_CHECK$
$	// ���硼�ȥ͡���ν�ʣ�����å�
	$FOREACH baudrate_id CanControllerBaudrateConfig.ID_LIST$
		$FOREACH baudrate_chk_id CanControllerBaudrateConfig.ID_LIST$
			$IF EQ(baudrate_id, baudrate_chk_id) && (baudrate_id != baudrate_chk_id)$
				$ERROR$$FORMAT(_("Short Name of CanControllerBaudrateConfig should not be duplicated. (%1%\)"), baudrate_id)$$END$$DIE()$
			$END$
		$END$
	$END$
	$FOREACH ctrl_id CanController.ID_LIST$
		$FOREACH ctrl_id CanController.ID_LIST$
			$IF EQ(ctrl_id, ctrl_chk_id) && (ctrl_id != ctrl_chk_id)$
				$ERROR$$FORMAT(_("Short Name of CanController should not be duplicated. (%1%\)"), ctrl_id)$$END$$DIE()$
			$END$
		$END$
	$END$
	$FOREACH filter_mask_id CanFilterMask.ID_LIST$
		$FOREACH filter_mask_chk_id CanFilterMask.ID_LIST$
			$IF EQ(filter_mask_id, filter_mask_chk_id) && (filter_mask_id != filter_mask_chk_id)$
				$ERROR$$FORMAT(_("Short Name of CanFilterMask should not be duplicated. (%1%\)"), filter_mask_id)$$END$$DIE()$
			$END$
		$END$
	$END$

	$FOREACH ctrl_id CanController.ID_LIST$
$		// CanIf¦�Υ���ȥ���ID�ݻ�
		$canif_ctrl_id_ref = ""$
		$FOREACH canif_ctrl_id CanIfCtrlCfg.ID_LIST$
			$IF EQ(ctrl_id, CanIfCtrlCfg.CanIfCtrlCanCtrlRef[canif_ctrl_id])$
				$IF EQ(canif_ctrl_id_ref, "")$
					$canif_ctrl_id_ref = CanIfCtrlCfg.CanIfCtrlId[canif_ctrl_id]$
				$ELSE$
					$ERROR$$FORMAT(_("`%1%\' is referenced from multiple CanIfCtrlCanCtrlRef."), ctrl_id)$$END$$DIE()$
				$END$
			$END$
		$END$
		$IF !EQ(canif_ctrl_id_ref, "")$
			$CanController.canif_ctrl_id_ref[ctrl_id] = canif_ctrl_id_ref$
		$ELSE$
			$ERROR$$FORMAT(_("`%1%\' is not referenced by CanIfCtrlCanCtrlRef."), ctrl_id)$$END$$DIE()$
		$END$

$		// [CAN314_Conf] CanBusoffProcessing
		$IF !(EQ(CanController.CanBusoffProcessing[ctrl_id], "INTERRUPT") || EQ(CanController.CanBusoffProcessing[ctrl_id], "POLLING"))$
			$ERROR$$FORMAT(_("CanBusoffProcessing should be `INTERRUPT' or `POLLING'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
		$IF EQ(CanController.CanBusoffProcessing[ctrl_id], "POLLING")$
			$IF !LENGTH(CanGeneral.CanMainFunctionBusoffPeriod[1])$
				$ERROR$$FORMAT(_("CanBusoffProcessing(%1%\) is `POLLING', but CanMainFunctionBusoffPeriod is not defined."), ctrl_id)$$END$$DIE()$
			$END$
		$END$
$		// [CAN317_Conf] CanRxProcessing
		$IF !(EQ(CanController.CanRxProcessing[ctrl_id], "INTERRUPT") || EQ(CanController.CanRxProcessing[ctrl_id], "POLLING"))$
			$ERROR$$FORMAT(_("CanRxProcessing should be `INTERRUPT' or `POLLING'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
		$IF EQ(CanController.CanRxProcessing[ctrl_id], "POLLING")$
			$IF !LENGTH(CanMainFunctionRWPeriods.CanMainFunctionReadPeriod[1])$
				$ERROR$$FORMAT(_("CanRxProcessing(%1%\) is `POLLING', but CanMainFunctionReadPeriod is not defined."), ctrl_id)$$END$$DIE()$
			$END$
		$END$
$		// [CAN318_Conf] CanTxProcessing
		$IF !(EQ(CanController.CanTxProcessing[ctrl_id], "INTERRUPT") || EQ(CanController.CanTxProcessing[ctrl_id], "POLLING"))$
			$ERROR$$FORMAT(_("CanTxProcessing should be `INTERRUPT' or `POLLING'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
		$IF EQ(CanController.CanTxProcessing[ctrl_id], "POLLING")$
			$IF !LENGTH(CanMainFunctionRWPeriods.CanMainFunctionWritePeriod[1])$
				$ERROR$$FORMAT(_("CanTxProcessing(%1%\) is `POLLING', but CanMainFunctionWritePeriod is not defined."), ctrl_id)$$END$$DIE()$
			$END$
		$END$
$		// [CAN319_Conf] CanWakeupProcessing
		$IF !(EQ(CanController.CanWakeupProcessing[ctrl_id], "INTERRUPT") || EQ(CanController.CanWakeupProcessing[ctrl_id], "POLLING"))$
			$ERROR$$FORMAT(_("CanWakeupProcessing should be `INTERRUPT' or `POLLING'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
		$IF EQ(CanController.CanWakeupProcessing[ctrl_id], "POLLING")$
			$IF !LENGTH(CanGeneral.CanMainFunctionWakeupPeriod[1])$
				$ERROR$$FORMAT(_("CanWakeupProcessing(%1%\) is `POLLING', but CanMainFunctionWakeupPeriod is not defined."), ctrl_id)$$END$$DIE()$
			$END$
		$END$

$		// [CAN330_Conf] CanWakeupSupport
		$ret = IS_TRUE(CanController.CanWakeupSupport[ctrl_id])$
		$IF (ret == 1)$
			$IF !LENGTH(CanController.CanWakeupSourceRef[ctrl_id])$
				$ERROR$$FORMAT(_("CanWakeupSupport(%1%\) is `TRUE', but CanWakeupSourceRef is not defined."), ctrl_id)$$END$$DIE()$
			$END$
		$END$
	$END$
	
	$FOREACH baudrate_id CanControllerBaudrateConfig.ID_LIST$
$		// [CAN005_Conf] CanControllerBaudRate
$		// ���ݡ��Ȥ��Ƥ���ܡ��졼�Ȥ��ǧ
		$IF !LENGTH(FIND(TARGET_SUPPORT_BAUDRATE_LIST, CanControllerBaudrateConfig.CanControllerBaudRate[baudrate_id]))$
			$ERROR$$FORMAT(_("CanControllerBaudRate(%1%) is not supported. (%2%)"), 
								CanControllerBaudrateConfig.CanControllerBaudRate[baudrate_id], baudrate_id)$$END$
			$DIE()$
		$END$
	$END$

	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$find = 0$
			$FOREACH i RANGE(0, LENGTH(CanController.baudrate_list[ctrl_id]) - 1)$
$				// CanControllerDefaultBaudrate��Ʊ��CanController�⤫����ꤷ�Ƥ��뤫��ǧ
				$IF EQ(CanController.CanControllerDefaultBaudrate[ctrl_id], AT(CanController.baudrate_list[ctrl_id], i))$
					$find = 1$
				$END$
			$END$
			$IF find == 0$
				$ERROR$$FORMAT(_("CanControllerDefaultBaudrate(%1%) is not found(%2%)."), 
									CanController.CanControllerDefaultBaudrate[ctrl_id], ctrl_id)$$END$
				$DIE()$
			$END$
		$END$
	$END$

	$FOREACH filter_mask_id CanFilterMask.ID_LIST$
$		// [CAN066_Conf] CanFilterMaskValue
		$IF ((CanFilterMask.CanFilterMaskValue[filter_mask_id] < 0) || (CanFilterMask.CanFilterMaskValue[filter_mask_id] > 4294967295))$
			$ERROR$$FORMAT(_("CanFilterMaskValue should be in the range of 0..4294967295. (%1%\)"), filter_mask_id)$$END$$DIE()$
		$END$
	$END$

	$FOREACH hoh_id CanHardwareObject.ID_LIST$
$		// [CAN323_Conf] CanHandleType
$		// FullCAN�Τߥ��ݡ���
		$IF !EQ(CanHardwareObject.CanHandleType[hoh_id], "FULL")$
			$ERROR$$FORMAT(_("CanHandleType should be set to `FULL'. (%1%\)"), hoh_id)$$END$$DIE()$
		$END$
$		// [CAN065_Conf] CanIdType
$		// STANDARD�Τߥ��ݡ���
		$IF !EQ(CanHardwareObject.CanIdType[hoh_id], "STANDARD")$
			$ERROR$$FORMAT(_("CanIdType should be set to `STANDARD'. (%1%\)"), hoh_id)$$END$$DIE()$
		$END$
$		// [CAN325_Conf] CanIdValue
		$IF ((CanHardwareObject.CanIdValue[hoh_id] < 0) || (CanHardwareObject.CanIdValue[hoh_id] > 4294967295))$
			$ERROR$$FORMAT(_("CanIdValue should be in the range of 0..4294967295. (%1%\)"), hoh_id)$$END$$DIE()$
		$END$
$		// [CAN326_Conf] CanObjectId
		$IF ((CanHardwareObject.CanObjectId[hoh_id] < 0) || (CanHardwareObject.CanObjectId[hoh_id] > 65535))$
			$ERROR$$FORMAT(_("CanObjectId should be in the range of 0..65535. (%1%\)"), hoh_id)$$END$$DIE()$
		$END$
$		// [CAN327_Conf] CanObjectType
		$IF !(EQ(CanHardwareObject.CanObjectType[hoh_id], "RECEIVE") || EQ(CanHardwareObject.CanObjectType[hoh_id], "TRANSMIT"))$
			$ERROR$$FORMAT(_("CanObjectType should be `RECEIVE' or `TRANSMIT'. (%1%\)"), hoh_id)$$END$$DIE()$
		$END$
$		// [CAN321_Conf] CanFilterMaskRef
		$IF LENGTH(CanHardwareObject.CanFilterMaskRef[hoh_id])$
$			// CanFilterMaskRef�λ������CanFilterMask�ϡ�CanControllerRef�����Ȥ��륳��ȥ����Ʊ��
			$IF (!EQ(CanHardwareObject.CanControllerRef[hoh_id], CanFilterMask.PARENT[CanHardwareObject.CanFilterMaskRef[hoh_id]]))$
				$ERROR$$FORMAT(_("CanControllerRef and CanFilterMaskRef should be equal CanController'. (%1%\)"),
								 CanHardwareObject.CanControllerRef[hoh_id])$$END$$DIE()$
			$END$
		$END$
	$END$

$	// [CAN328_Conf] CanGeneral
	$FOREACH general_id CanGeneral.ID_LIST$
$		// [CAN436_Conf] CanChangeBaudrateApi
		$ret = IS_TRUE(CanGeneral.CanChangeBaudrateApi[general_id])$
$		// [CAN064_Conf] CanDevErrorDetection
		$ret = IS_TRUE(CanGeneral.CanDevErrorDetection[general_id])$
$		// [CAN320_Conf] CanIndex
		$IF ((CanGeneral.CanIndex[general_id] < 0) || (CanGeneral.CanIndex[general_id] > 255))$
			$ERROR$$FORMAT(_("CanIndex should be in the range of 0..255. (%1%\)"), general_id)$$END$$DIE()$
		$END$
$		// [CAN095_Conf] CanMultiplexedTransmission
$		// false�Τߥ��ݡ���
		$IF IS_TRUE(CanGeneral.CanMultiplexedTransmission[general_id])$
			$ERROR$$FORMAT(_("CanIndex should be `FALSE'. (%1%\)"), general_id)$$END$$DIE()$
		$END$
$		// [CAN106_Conf] CanVersionInfoApi
		$ret = IS_TRUE(CanGeneral.CanVersionInfoApi[general_id])$
	$END$
$END$

$ ====================================================================
$  [CAN220][CAN389] �ץꥳ��ѥ����ѥإå������ؿ�
$ ====================================================================
$FUNCTION GEN_CAN_CFG_H$
$	// [CAN047] human readable������
	$FILE "Can_Cfg.h"$
	/* Can_Cfg.h */$NL$

	#ifndef TOPPERS_CAN_CFG_H$NL$
	#define TOPPERS_CAN_CFG_H$NL$
	$NL$

	#include "Os.h"$NL$
	$NL$

$	// [CAN436_Conf] CanChangeBaudrateApi
	#define CAN_CHANGE_BAUDRATE_API$TAB$
	$IF IS_TRUE(CanGeneral.CanChangeBaudrateApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CAN082][CAN064_Conf] CanDevErrorDetection
	#define CAN_DEV_ERROR_DETECT$TAB$
	$IF IS_TRUE(CanGeneral.CanDevErrorDetection[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CAN106_Conf] CanVersionInfoApi
	#define CAN_VERSION_INFO_API$TAB$
	$IF IS_TRUE(CanGeneral.CanVersionInfoApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$$NL$

$	// [CAN113_Conf] CanTimeoutDuration
	#define CAN_TIMEOUT_DURATION$TAB$($CanGeneral.CanTimeoutDuration[1]$)$NL$

$	// [CAN431_Conf] CanCounterRef
	#define CAN_COUNTER$TAB$$CanGeneral.CanCounterRef[1]$$NL$
	#define CAN_COUNTER_TICKS2SEC(tick)$TAB$OS_TICKS2SEC_$CanGeneral.CanCounterRef[1]$(tick)$NL$
	$NL$

$	// CanController���Ȥ�MainFunction APIͭ��/̵�����ǧ
	$busoff_int = 0$
	$busoff_poll = 0$
	$rx_int = 0$
	$rx_poll = 0$
	$tx_int = 0$
	$tx_poll = 0$
	$wakeup_int = 0$
	$wakeup_poll = 0$
	$FOREACH ctrl_id CanController.ID_LIST$
		$new_list = {}$
		$IF EQ(CanController.CanBusoffProcessing[ctrl_id], "INTERRUPT")$
			$busoff_int = 1$
		$ELSE$
			$busoff_poll = 1$
			$new_list = APPEND(new_list, "CAN_USE_POLLING_BUSOFF")$
		$END$
		$IF EQ(CanController.CanRxProcessing[ctrl_id], "INTERRUPT")$
			$rx_int = 1$
		$ELSE$
			$rx_poll = 1$
			$new_list = APPEND(new_list, "CAN_USE_POLLING_RX")$
		$END$
		$IF EQ(CanController.CanTxProcessing[ctrl_id], "INTERRUPT")$
			$tx_int = 1$
		$ELSE$
			$tx_poll = 1$
			$new_list = APPEND(new_list, "CAN_USE_POLLING_TX")$
		$END$
		$IF EQ(CanController.CanWakeupProcessing[ctrl_id], "INTERRUPT")$
			$wakeup_int = 1$
		$ELSE$
			$wakeup_poll = 1$
			$new_list = APPEND(new_list, "CAN_USE_POLLING_WAKEUP")$
		$END$

		$CanController.use_polling[ctrl_id] = new_list$
	$END$
	$IF (busoff_int == 1)$
		#define USE_CAN_BUSOFF_INTERRUPT$NL$
	$END$
	$IF (busoff_poll == 1)$
		#define USE_CAN_BUSOFF_POLLING$NL$
	$END$
	$IF (rx_int == 1)$
		#define USE_CAN_RX_INTERRUPT$NL$
	$END$
	$IF (rx_poll == 1)$
		#define USE_CAN_RX_POLLING$NL$
	$END$
	$IF (tx_int == 1)$
		#define USE_CAN_TX_INTERRUPT$NL$
	$END$
	$IF (tx_poll == 1)$
		#define USE_CAN_TX_POLLING$NL$
	$END$
	$IF (wakeup_int == 1)$
		#define USE_CAN_WAKEUP_INTERRUPT$NL$
	$END$
	$IF (wakeup_poll == 1)$
		#define USE_CAN_WAKEUP_POLLING$NL$
	$END$

$	// CanLPduReceiveCalloutFunction�����ǧ
	$IF LENGTH(CanGeneral.CanLPduReceiveCalloutFunction[1])$
		#define USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION$NL$
	$END$
	$NL$

$	// MainFunction�����
$	// [CAN355_Conf] CanMainFunctionBusoffPeriod
	$IF LENGTH(CanGeneral.CanMainFunctionBusoffPeriod[1])$
		#define CAN_MAIN_FUNCTION_BUSOFF_PERIOD$TAB$($CanGeneral.CanMainFunctionBusoffPeriod[1]$)$NL$
	$END$
$	// [CAN376_Conf] CanMainFunctionModePeriod
	$IF LENGTH(CanGeneral.CanMainFunctionModePeriod[1])$
		#define CAN_MAIN_FUNCTION_MODE_PERIOD$TAB$($CanGeneral.CanMainFunctionModePeriod[1]$)$NL$
	$END$
$	// [CAN357_Conf] CanMainFunctionWakeupPeriod
	$IF LENGTH(CanGeneral.CanMainFunctionWakeupPeriod[1])$
		#define CAN_MAIN_FUNCTION_WAKEUP_PERIOD$TAB$($CanGeneral.CanMainFunctionWakeupPeriod[1]$)$NL$
	$END$
$	// [CAN437_Conf] CanMainFunctionRWPeriods
$	// [CAN356_Conf] CanMainFunctionReadPeriod
$	// [NCAN001] ¿����0..1�Ȥ���ͣ����ͤΤ߽���
	$IF LENGTH(CanMainFunctionRWPeriods.CanMainFunctionReadPeriod[1])$
		#define CAN_MAIN_FUNCTION_READ_PERIOD$TAB$($CanMainFunctionRWPeriods.CanMainFunctionReadPeriod[1]$)$NL$
	$END$
$	// [CAN358_Conf] CanMainFunctionWritePeriod
$	// [NCAN002] ¿����0..1�Ȥ���ͣ����ͤΤ߽���
	$IF LENGTH(CanMainFunctionRWPeriods.CanMainFunctionWritePeriod[1])$
		#define CAN_MAIN_FUNCTION_WRITE_PERIOD$TAB$($CanMainFunctionRWPeriods.CanMainFunctionWritePeriod[1]$)$NL$
	$END$
	$NL$

	#endif /* TOPPERS_CAN_CFG_H */
$END$

$ ====================================================================
$  [CAN078][CAN221] �ݥ��ȥӥ���Ѽ��������ؿ�
$ ====================================================================
$FUNCTION GEN_CAN_PB_CFG_C$
$ 	// �ӥ�ɸ�˥���ե�����졼������ǽ�ʥѥ�᡼����
	$FILE "Can_PBcfg.c"$
	/* Can_PBcfg.c */$NL$

	#include "Can.h"$NL$
	$NL$

	/* ���ݡ��ȥܡ��졼������ : baudrate_<CanConfigSet>_<CanController> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			static const Can_ControllerBaudrateConfigType baudrate_$config_id$_$ctrl_id$[$CanController.baudrate_num[ctrl_id]$] = {$NL$
			$TAB$/* { CanControllerBaudRate, CanControllerPropSeg, CanControllerSeg1, CanControllerSeg2, CanControllerSyncJumpWidth }*/$NL$
			$JOINEACH baudrate_id CanController.baudrate_list[ctrl_id] ",\n"$
				$TAB${
$				// [CAN005_Conf] CanControllerBaudRate
				$SPC$$CanControllerBaudrateConfig.CanControllerBaudRate[baudrate_id]$U,
$				// [CAN073_Conf] CanControllerPropSeg
				$SPC$$CanControllerBaudrateConfig.CanControllerPropSeg[baudrate_id]$U,
$				// [CAN074_Conf] CanControllerSeg1
				$SPC$$CanControllerBaudrateConfig.CanControllerSeg1[baudrate_id]$U,
$				// [CAN075_Conf] CanControllerSeg2
				$SPC$$CanControllerBaudrateConfig.CanControllerSeg2[baudrate_id]$U,
$				// [CAN383_Conf] CanControllerSyncJumpWidth
				$SPC$$CanControllerBaudrateConfig.CanControllerSyncJumpWidth[baudrate_id]$U
				$SPC$}
			$END$
			$NL$};$NL$
			$NL$
		$END$
	$END$

$	// [CAN066_Conf] CanFilterMaskValue
	/* �ե��륿�ޥ��������� : filtermask_<CanConfigSet>_<CanController> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$IF (CanController.filtermask_num[ctrl_id] != 0)$
				static const Can_IdType filtermask_$config_id$_$ctrl_id$[$CanController.filtermask_num[ctrl_id]$] = {$NL$
				$JOINEACH filtermask_id CanController.filtermask_list[ctrl_id] ",\n"$
					$TAB$$FORMAT("0x%03x",+CanFilterMask.CanFilterMaskValue[filtermask_id])$U
				$END$
				$NL$};$NL$
				$NL$
			$END$
		$END$
	$END$

	/* �����ܥå����ֹ梪HRH�Ѵ��ơ��֥� : rbox_hrh_table_<CanConfigSet>_<CanController> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$IF (CanController.hrh_num[ctrl_id] != 0)$
				static const Can_HwHandleType rbox_hrh_table_$config_id$_$ctrl_id$[$CanController.hrh_num[ctrl_id]$] = {$NL$
				$JOINEACH hrh_id CanController.hrh_list[ctrl_id] ",\n"$
					$TAB$$CanHardwareObject.CanObjectId[hrh_id]$U
				$END$
				$NL$};$NL$
				$NL$
			$END$
		$END$
	$END$

	/* �����ܥå���CAN-ID�ơ��֥� : rbox_canid_table_<CanConfigSet>_<CanController> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$IF (CanController.hrh_num[ctrl_id] != 0)$
				static const Can_RboxCanidType rbox_canid_table_$config_id$_$ctrl_id$[$CanController.hrh_num[ctrl_id]$] = {$NL$
				$TAB$/* { CanIdValue, filtermask_table_idx } */$NL$
				$JOINEACH hrh_id CanController.hrh_list[ctrl_id] ",\n"$
$					// [CAN325_Conf] CanIdValue
					$TAB${
					$SPC$$FORMAT("0x%03x",+CanHardwareObject.CanIdValue[hrh_id])$U,

$					// [CAN321_Conf] CanFilterMaskRef
					$IF (!LENGTH(CanHardwareObject.CanFilterMaskRef[hrh_id]))$
						$SPC$CAN_NO_MASK_IDX
					$ELSE$
						$index=0$
						$FOREACH filtermask_id CanController.filtermask_list[ctrl_id]$
							$IF EQ(filtermask_id, CanHardwareObject.CanFilterMaskRef[hrh_id])$
								$SPC$$index$U
							$END$
							$index = index + 1$
						$END$
					$END$
					$SPC$}
				$END$
				$NL$};$NL$
				$NL$
			$END$
		$END$
	$END$

	/* HTH�����֥�å����� : can_hth_cb_table_<CanConfigSet>_<CanController> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$IF (CanController.hth_num[ctrl_id] != 0)$
				static CAN_HTH_CB can_hth_cb_table_$config_id$_$ctrl_id$[$CanController.hth_num[ctrl_id]$];$NL$
				$NL$
			$END$
		$END$
	$END$

	/* Can����ȥ�������֥�å����� : can_ctrl_inib_table_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		static const CAN_CTRL_INIB can_ctrl_inib_table_$config_id$[$CanConfigSet.ctrl_id_num[config_id]$] = {$NL$
		$JOINEACH ctrl_id CanConfigSet.ctrl_id_list[config_id] ",\n"$
			$TAB$/* $ctrl_id$ */$NL$
			$TAB${$NL$
			$TAB$$TAB$$CanController.canif_ctrl_id_ref[ctrl_id]$U,$TAB$/* CanIfCtrlId */$NL$
			$TAB$$TAB$$CanController.baudrate_num[ctrl_id]$U,$TAB$/* tnum_baudrate */$NL$
			$TAB$$TAB$$CanController.hth_num[ctrl_id]$U,$TAB$/* tnum_hth */$NL$
			$TAB$$TAB$$CanController.hrh_num[ctrl_id]$U,$TAB$/* tnum_hrh */$NL$
			$TAB$$TAB$$CanController.filtermask_num[ctrl_id]$U,$TAB$/* tnum_filtermask */$NL$
			$TAB$$TAB$
			$IF !LENGTH(CanController.use_polling[ctrl_id])$
				0x00U
			$ELSE$
				(
				$JOINEACH use_polling CanController.use_polling[ctrl_id] " | "$
					$use_polling$
				$END$
				)
			$END$,$TAB$/* use_polling */$NL$
			$TAB$$TAB$$IS_TRUE(CanController.CanWakeupSupport[ctrl_id])$,$TAB$/* CanWakeupSupport */$NL$
			$TAB$$TAB$$CanController.wakeup_source_id[ctrl_id]$U,$TAB$/* EcuMWakeupSourceId */$NL$
			$FOREACH i RANGE(0, LENGTH(CanController.baudrate_list[ctrl_id]) - 1)$
$				// [CAN435_Conf] CanControllerDefaultBaudrate
				$IF EQ(CanController.CanControllerDefaultBaudrate[ctrl_id], AT(CanController.baudrate_list[ctrl_id], i))$
					$TAB$$TAB$&baudrate_$config_id$_$ctrl_id$[$i$],$TAB$/* p_default_baudrate */$NL$
				$END$
			$END$
			$TAB$$TAB$baudrate_$config_id$_$ctrl_id$,$TAB$/* p_baudrate_table */$NL$
			$IF (CanController.filtermask_num[ctrl_id] != 0)$
				$TAB$$TAB$filtermask_$config_id$_$ctrl_id$,$TAB$/* p_filtermask_table */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* p_filtermask_table */$NL$
			$END$
			$IF (CanController.hrh_num[ctrl_id] != 0)$
				$TAB$$TAB$rbox_hrh_table_$config_id$_$ctrl_id$,$TAB$/* p_rbox_hrh_table */$NL$
				$TAB$$TAB$rbox_canid_table_$config_id$_$ctrl_id$,$TAB$/* p_rbox_canid_table */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* p_rbox_hrh_table */$NL$
				$TAB$$TAB$NULL_PTR,$TAB$/* p_rbox_canid_table */$NL$
			$END$
			$IF (CanController.hth_num[ctrl_id] != 0)$
				$TAB$$TAB$can_hth_cb_table_$config_id$_$ctrl_id$$TAB$/* p_can_hth_cb_table */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR$TAB$/* p_can_hth_cb_table */$NL$
			$END$
			$TAB$}$NL$
		$END$
		};$NL$
	$END$
	$NL$

	/* HOH���ܥå����ֹ��Ѵ��ơ��֥� : hoh_box_table_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		static const Can_HohBoxType hoh_box_table_$config_id$[$CanConfigSet.hoh_num[config_id]$] = {$NL$
		$TAB$/* { CanControllerId, CanObjectType, box_idx } */$NL$
		$JOINEACH hoh_id CanConfigSet.hoh_list[config_id] ",\n"$
			$ctrl_id = CanHardwareObject.ctrl_id[hoh_id]$
			$TAB${
			$SPC$$CanController.CanControllerId[ctrl_id]$U,
			$IF EQ(CanHardwareObject.CanObjectType[hoh_id], "RECEIVE")$
				$SPC$CAN_RECEIVE,
			$ELSE$
				$SPC$CAN_TRANSMIT,
			$END$
			$SPC$$CanHardwareObject.box_idx[hoh_id]$U
			$SPC$}
		$END$
		$NL$};$NL$
		$NL$
	$END$

$	// [CAN343_Conf] CanConfigSet
$	// [CAN021][CAN291] ����ȥ���Υ���ե�����졼������ޤ�'Config'�ξ���
$	// [NCAN004] �ݥ��ȥӥ���б��Τ���can_config��¿���٤�1..*
	/* Can����ե�����졼�������� */$NL$
	const Can_ConfigType can_config[$LENGTH(CanConfigSet.ID_LIST)$] = {$NL$
	$JOINEACH config_id CanConfigSet.ID_LIST ",\n"$
		$TAB$/* $config_id$ */$NL$
		$TAB${$NL$
		$TAB$$TAB$$CanConfigSet.hoh_num[config_id]$U,$TAB$/* tnum_hoh */$NL$
		$TAB$$TAB$$CanConfigSet.ctrl_id_num[config_id]$U,$TAB$/* tnum_controller */$NL$
		$TAB$$TAB$hoh_box_table_$config_id$,$TAB$/* p_hoh_box_table */$NL$
		$TAB$$TAB$can_ctrl_inib_table_$config_id$$TAB$/* p_can_ctrl_inib_table */$NL$
		$TAB$}
	$END$
	$NL$};$NL$
	$NL$

	/* ����߶ػߥͥ��ȥ������ */$NL$
	uint8 can_interrupt_nested_cnt[$ctrl_id_num_max$];$NL$
	$NL$

	/* Can_SetControllerModeư����֥ե饰 */$NL$
	boolean can_set_controller_mode_flg[$ctrl_id_num_max$];$NL$
	$NL$

	/* CAN����ȥ�����־��� */$NL$
	Can_StateTransitionType can_current_state[$ctrl_id_num_max$];$NL$
	$NL$

$	// [CAN434_Conf] CanLPduReceiveCalloutFunction
	$IF LENGTH(CanGeneral.CanLPduReceiveCalloutFunction[1])$
		/* �����륢���ȴؿ� */$NL$
		extern boolean $CanGeneral.CanLPduReceiveCalloutFunction[1]$(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);$NL$
		const Can_LpduCallout CanLpduCalloutFunction = $CanGeneral.CanLPduReceiveCalloutFunction[1]$;$NL$
	$END$
	$NL$
$END$


$ ====================================================================
$  �ᥤ�����
$ ====================================================================

$	DUMP()$

$ �ꥹ�Ⱥ���
$MAKE_CFG_LIST()$

$ ID������
$ID_SORT()$

$ ���顼�����å�
$ERROR_CHECK()$

$ �������åȰ�¸�������å�
$IF ISFUNCTION("TARGET_CHECK")$
	$TARGET_CHECK()$
$END$

$ �ץꥳ��ѥ�����
$GEN_CAN_CFG_H()$

$ �ݥ��ȥӥ����
$GEN_CAN_PB_CFG_C()$


$	TOPPERS/A-CAN �Ǥ��б����ʤ����ͥ�������
$
$	- ��������󥻥�
$		<CAN069_Conf> CanGeneral/CanHardwareCancellation
$		<CAN378_Conf> CanGeneral/CanIdenticalIdCancellation
$	- TTCAN
$		<CAN430_Conf> CanGeneral/CanSupportTTCANRef
$	- CAN����ȥ���
$		<CAN315_Conf> CAN����ȥ����̵�������̤���ݡ���
$		<CAN382_Conf> CAN����ȥ���Υ١������ɥ쥹�����̤���ݡ���
$	- ����¾
$		<CAN313_Conf> Mcu�⥸�塼�뤫��λ��Ȥ�̤���ݡ���
$		<CAN438_Conf> CanHardwareObject���Period�����̤���ݡ���
