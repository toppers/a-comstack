$
$  TOPPERS/A-CANIF
$      AuTomotive CANIF
$
$  Copyright (C) 2013-2015 by Center for Embedded Computing Systems
$                             Graduate School of Information Science, Nagoya Univ., JAPAN
$  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
$  Copyright (C) 2013-2015 by FUJI SOFT INCORPORATED, JAPAN
$  Copyright (C) 2014-2015 by NEC Communication Systems, Ltd., JAPAN
$  Copyright (C) 2013-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
$  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
$  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
$  Copyright (C) 2013-2015 by Sunny Giken Inc., JAPAN
$  Copyright (C) 2013-2015 by TOSHIBA CORPORATION, JAPAN
$  Copyright (C) 2013-2015 by Witz Corporation
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
$  $Id: canif.tf 1241 2015-03-25 07:26:02Z panasonic-ayane $
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
	$FOREACH init_id CanIfInitCfg.ID_LIST$
$		// [CANIF832_Conf] CanIfBufferCfg
		$new_list = {}$
		$FOREACH buffer_id CanIfBufferCfg.ID_LIST$
			$IF EQ(init_id, CanIfBufferCfg.PARENT[buffer_id])$
				$new_list = APPEND(new_list, buffer_id)$
			$END$
		$END$
		$CanIfInitCfg.buffer_list[init_id] = new_list$

$		// [CANIF257_Conf] CanIfInitHohCfg
		$new_list = {}$
		$FOREACH hoh_id CanIfInitHohCfg.ID_LIST$
			$IF EQ(init_id, CanIfInitHohCfg.PARENT[hoh_id])$
				$new_list = APPEND(new_list, hoh_id)$
			$END$
		$END$
		$CanIfInitCfg.hoh_list[init_id] = new_list$

		$FOREACH hoh_id CanIfInitCfg.hoh_list[init_id]$
$			// [CANIF258_Conf] CanIfHthCfg
			$new_list = {}$
			$FOREACH hth_id CanIfHthCfg.ID_LIST$
				$IF EQ(hoh_id, CanIfHthCfg.PARENT[hth_id])$
					$new_list = APPEND(new_list, hth_id)$
				$END$
			$END$
			$CanIfInitCfg.hth_list[init_id] = new_list$
$			// [CANIF259_Conf] CanIfHrhCfg
			$new_list = {}$
			$FOREACH hrh_id CanIfHrhCfg.ID_LIST$
				$IF EQ(hoh_id, CanIfHrhCfg.PARENT[hrh_id])$
					$new_list = APPEND(new_list, hrh_id)$
				$END$
			$END$
			$CanIfInitCfg.hrh_list[init_id] = new_list$
		$END$

$		// [CANIF248_Conf] CanIfTxPduCfg
		$new_list = {}$
		$FOREACH tx_pdu_id CanIfTxPduCfg.ID_LIST$
			$IF EQ(init_id, CanIfTxPduCfg.PARENT[tx_pdu_id])$
				$new_list = APPEND(new_list, tx_pdu_id)$
			$END$
		$END$
		$CanIfInitCfg.tx_pdu_list[init_id] = new_list$

$		// [CANIF249_Conf] CanIfRxPduCfg
		$new_list = {}$
		$FOREACH rx_pdu_id CanIfRxPduCfg.ID_LIST$
			$IF EQ(init_id, CanIfRxPduCfg.PARENT[rx_pdu_id])$
				$new_list = APPEND(new_list, rx_pdu_id)$
			$END$
		$END$
		$CanIfInitCfg.rx_pdu_list[init_id] = new_list$

		$CanIfInitCfg.pdu_list[init_id] = APPEND(CanIfInitCfg.tx_pdu_list[init_id], CanIfInitCfg.rx_pdu_list[init_id])$
		$CanIfInitCfg.pdu_num[init_id] = LENGTH(CanIfInitCfg.pdu_list[init_id])$
	$END$
$END$


$ ====================================================================
$  IDϢ�֥����ȴؿ�
$ ====================================================================
$FUNCTION ID_SORT$
$	// [CANIF647_Conf] CanIfCtrlId ��˥�����
$	// [CANIF653] CanIfCtrlId��0���鳫�Ϥ���
$	// [NCANIF003] CanIfCtrlId��0�����Ϣ�֤Ȥ���
$	// [NCANIF017] CanIfCtrlDrvCfg��¿���٤�1�Ǥ��뤿�ᡤPARENT�����å�����
	$new_list = {}$
	$FOREACH index RANGE(0, LENGTH(CanIfCtrlCfg.ID_LIST) - 1)$
		$find = 0$
		$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
			$IF CanIfCtrlCfg.CanIfCtrlId[ctrl_id] == index$
				$new_list = APPEND(new_list, ctrl_id)$
				$find = find + 1$
			$END$
		$END$
$		// CanIfCtrlId��0�����Ϣ�֤Ǥʤ����ϥ��顼
		$IF find == 0$
			$ERROR$$FORMAT(_("CanIfCtrlId(%1%\) is not found. CanIfCtrlId should be sequential from 0."), index)$$END$$DIE()$
		$END$
		$IF find > 1$
			$ERROR$$FORMAT(_("CanIfCtrlId(%1%\) is duplicated. CanIfCtrlId should be unique."), index)$$END$$DIE()$
		$END$
	$END$
	$CanIfCtrlCfg.ID_LIST = new_list$

$	// CanIfTxPduId CanIfRxPduId ��˥�����
$	// [NCANIF003] CanIfTxPduId��CanIfRxPduId�϶����ֹ��ΰ�Ǵ�������0�����Ϣ�֤Ȥ���
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanIfInitCfg.pdu_list[init_id]) - 1)$
			$find = 0$
			$FOREACH tx_pdu_id CanIfInitCfg.tx_pdu_list[init_id]$
				$IF CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id] == index$
					$new_list = APPEND(new_list, tx_pdu_id)$
					$find = find + 1$
				$END$
			$END$
			$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
				$IF CanIfRxPduCfg.CanIfRxPduId[rx_pdu_id] == index$
					$new_list = APPEND(new_list, rx_pdu_id)$
					$find = find + 1$
				$END$
			$END$
			$IF find == 0$
				$ERROR$$FORMAT(_("CanIfPduId(%1%\) is not found. CanIfPduId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("CanIfPduId(%1%\) is duplicated. CanIfPduId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanIfInitCfg.pdu_list[init_id] = new_list$
	$END$

$	// CanObjectId ��˥�����
$	// [CANIF115] HTH��HRH�϶����ֹ��ΰ�Ǵ�������0�����Ϣ�֤Ȥ���
$	// [CANIF467] HTH��HRH�ν��֤���������¸����
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$FOREACH tx_pdu_id CanIfInitCfg.tx_pdu_list[init_id]$
$			// [CANIF833_Conf] CanIfBufferHthRef
$			// [CANIF831_Conf] CanIfTxPduBufferRef
$			// [CANIF466] ����LPDU��1�Ĥ�CanTxPduBuffer����Ū�˳�����Ƥ���
			$CanIfTxPduCfg.hth_id_ref[tx_pdu_id] = CanIfBufferCfg.CanIfBufferHthRef[CanIfTxPduCfg.CanIfTxPduBufferRef[tx_pdu_id]]$
$			// [CANIF625_Conf] CanIfHthCanCtrlIdRef
			$FOREACH hth_id_ref CanIfTxPduCfg.hth_id_ref[tx_pdu_id]$
$				// [CANIF046] LPDU��ʣ����CAN����ȥ����°���ƤϤ����ʤ�
				$IF LENGTH(CanIfTxPduCfg.ctrl_id_ref[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.ctrl_id_ref[tx_pdu_id], CanIfHthCfg.CanIfHthCanCtrlIdRef[hth_id_ref])$
						$ERROR$$FORMAT(_("`%1%\' should be assign to only one CAN controller."), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.ctrl_id_ref[tx_pdu_id] = CanIfHthCfg.CanIfHthCanCtrlIdRef[hth_id_ref]$
				$END$
			$END$
$			// [CANIF627_Conf] CanIfHthIdSymRef
			$CanIfTxPduCfg.can_hw_obj_id[tx_pdu_id] = CanHardwareObject.CanObjectId[CanIfHthCfg.CanIfHthIdSymRef[CanIfTxPduCfg.hth_id_ref[tx_pdu_id]]]$
$			// [CANIF603_Conf] CanIfTxPduRef
			$CanIfTxPduCfg.pdu_length[tx_pdu_id] = Pdu.PduLength[CanIfTxPduCfg.CanIfTxPduRef[tx_pdu_id]]$
			$FOREACH dest_pdu_id PduRDestPdu.ID_LIST$
				$IF EQ(CanIfTxPduCfg.CanIfTxPduRef[tx_pdu_id], PduRDestPdu.PduRDestPduRef[dest_pdu_id])$
					$CanIfTxPduCfg.pdu_handle_id[tx_pdu_id] = PduRDestPdu.PduRDestPduHandleId[dest_pdu_id]$
				$END$
			$END$
		$END$
		$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
$			// [CANIF631_Conf] CanIfHrhCanCtrlIdRef
$			// [CANIF602_Conf] CanIfRxPduHrhIdRef
$			// [CANIF465] CanIfRxPduId��1�İʾ��HRH�˳�����Ƥ뤳�Ȥ��Ǥ��뤿�ᡤñ���CAN-ID��ʣ����HRH�˳�����Ƥ뤳�Ȥ��Ǥ���
			$FOREACH hrh_id_ref CanIfRxPduCfg.CanIfRxPduHrhIdRef[rx_pdu_id]$
$				// [CANIF046] LPDU��ʣ����CAN����ȥ����°���ƤϤ����ʤ�
				$IF LENGTH(CanIfRxPduCfg.ctrl_id_ref[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.ctrl_id_ref[rx_pdu_id], CanIfHrhCfg.CanIfHrhCanCtrlIdRef[hrh_id_ref])$
						$ERROR$$FORMAT(_("`%1%\' should be assign to only one CAN controller."), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.ctrl_id_ref[rx_pdu_id] = CanIfHrhCfg.CanIfHrhCanCtrlIdRef[hrh_id_ref]$
				$END$
			$END$
$			// [CANIF634_Conf] CanIfHrhIdSymRef 
			$CanIfRxPduCfg.can_hw_obj_id[rx_pdu_id] = CanHardwareObject.CanObjectId[CanIfHrhCfg.CanIfHrhIdSymRef[CanIfRxPduCfg.CanIfRxPduHrhIdRef[rx_pdu_id]]]$
$			// [CANIF601_Conf] CanIfRxPduRef
			$CanIfRxPduCfg.pdu_length[rx_pdu_id] = Pdu.PduLength[CanIfRxPduCfg.CanIfRxPduRef[rx_pdu_id]]$
			$FOREACH src_pdu_id PduRSrcPdu.ID_LIST$
				$IF EQ(CanIfRxPduCfg.CanIfRxPduRef[rx_pdu_id], PduRSrcPdu.PduRSrcPduRef[src_pdu_id])$
					$CanIfRxPduCfg.pdu_handle_id[rx_pdu_id] = PduRSrcPdu.PduRSourcePduHandleId[src_pdu_id]$
				$END$
			$END$
		$END$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanIfInitCfg.pdu_list[init_id]) - 1)$
			$find = 0$
			$FOREACH tx_pdu_id CanIfInitCfg.tx_pdu_list[init_id]$
				$IF CanIfTxPduCfg.can_hw_obj_id[tx_pdu_id] == index$
					$new_list = APPEND(new_list, tx_pdu_id)$
					$find = find + 1$
				$END$
			$END$
			$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
				$IF CanIfRxPduCfg.can_hw_obj_id[rx_pdu_id] == index$
					$new_list = APPEND(new_list, rx_pdu_id)$
					$find = find + 1$
				$END$
			$END$
			$IF find == 0$
				$ERROR$$FORMAT(_("CanObjectId(%1%\) is not found. CanObjectId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("CanObjectId(%1%\) is duplicated. CanObjectId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanIfInitCfg.pdu_list_by_can_object_id[init_id] = new_list$
	$END$
$END$

$ ====================================================================
$  [CANIF131] ���顼�����å��ؿ�
$ ====================================================================
$FUNCTION ERROR_CHECK$
$ [CANIF131] CanIf���ͤ˱�ä������ͥ����å���»�

$ [CANIF244_Conf] CanIf
$	/*
$	 *  [CANIF246_Conf] CanIfPublicCfg
$	 */
$	// [CANIF522_Conf] CanIfPublicCancelTransmitSupport
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicCancelTransmitSupport[1])$

$	// [CANIF671_Conf] CanIfPublicCddHeaderFile
$	// �����å�����ʤ�

$	// [CANIF785_Conf] CanIfPublicChangeBaudrateSupport
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicChangeBaudrateSupport[1])$
$	// [CANIF614_Conf] CanIfPublicDevErrorDetect
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicDevErrorDetect[1])$

$	// [CANIF742_Conf] CanIfPublicHandleTypeEnum
	$IF !EQ(CanIfPublicCfg.CanIfPublicHandleTypeEnum[1], "UINT16") && !EQ(CanIfPublicCfg.CanIfPublicHandleTypeEnum[1], "UINT8")$
		$ERROR$$FORMAT(_("CanIfPublicHandleTypeEnum(%1%\) should be `UINT16' or `UINT8'."), CanIfPublicCfg.CanIfPublicHandleTypeEnum[1])$$END$$DIE()$
	$END$

$	// [CANIF612_Conf] CanIfPublicMultipleDrvSupport
	$IF IS_TRUE(CanIfPublicCfg.CanIfPublicMultipleDrvSupport[1])$
$		// [NCANIF010] ñ���CAN�ɥ饤�ФΤߥ��ݡ���
		$ERROR$$FORMAT(_("CanIfPublicMultipleDrvSupport(%1%\) should be `FALSE'."), CanIfPublicCfg.CanIfPublicMultipleDrvSupport[1])$$END$$DIE()$
	$END$

$	// [CANIF615_Conf] CanIfPublicNumberOfCanHwUnits 
	$IF (CanIfPublicCfg.CanIfPublicNumberOfCanHwUnits[1] != 1)$
$		// [NCANIF011] ñ���CAN�ɥ饤�ФΤߥ��ݡ���
		$ERROR$$FORMAT(_("CanIfPublicNumberOfCanHwUnits(%1%\) should be `1'."), CanIfPublicCfg.CanIfPublicNumberOfCanHwUnits[1])$$END$$DIE()$
	$END$

$	// [CANIF772_Conf] CanIfPublicPnSupport
	$IF IS_TRUE(CanIfPublicCfg.CanIfPublicPnSupport[1])$
$		// [NCANIF012] PN�󥵥ݡ���
		$ERROR$$FORMAT(_("CanIfPublicPnSupport(%1%\) should be `FALSE'."), CanIfPublicCfg.CanIfPublicPnSupport[1])$$END$$DIE()$
	$END$

$	// [CANIF607_Conf] CanIfPublicReadRxPduDataApi
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduDataApi[1])$
$	// [CANIF608_Conf] CanIfPublicReadRxPduNotifyStatusApi
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduNotifyStatusApi[1])$
$	// [CANIF609_Conf] CanIfPublicReadTxPduNotifyStatusApi
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicReadTxPduNotifyStatusApi[1])$

$	// [CANIF610_Conf] CanIfPublicSetDynamicTxIdApi
	$IF IS_TRUE(CanIfPublicCfg.CanIfPublicSetDynamicTxIdApi[1])$
$		// [NCANIF013] ưŪCAN-ID������󥵥ݡ���
		$ERROR$$FORMAT(_("CanIfPublicSetDynamicTxIdApi(%1%\) should be `FALSE'."), CanIfPublicCfg.CanIfPublicSetDynamicTxIdApi[1])$$END$$DIE()$
	$END$

$	// [CANIF618_Conf] CanIfPublicTxBuffering
	$IF IS_TRUE(CanIfPublicCfg.CanIfPublicTxBuffering[1])$
$		// [NCANIF014] �����Хåե�����󥵥ݡ���
		$ERROR$$FORMAT(_("CanIfPublicTxBuffering(%1%\) should be `FALSE'."), CanIfPublicCfg.CanIfPublicTxBuffering[1])$$END$$DIE()$
	$END$

$	// [CANIF733_Conf] CanIfPublicTxConfirmPollingSupport
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicTxConfirmPollingSupport[1])$
$	// [CANIF613_Conf] CanIfPublicVersionInfoApi
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicVersionInfoApi[1])$
$	// [CANIF611_Conf] CanIfPublicWakeupCheckValidSupport
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicWakeupCheckValidSupport[1])$


$	/*
$	 *  [CANIF245_Conf] CanIfPrivateCfg
$	 */
$	// [CANIF617_Conf] CanIfPrivateDlcCheck
	$ret = IS_TRUE(CanIfPrivateCfg.CanIfPrivateDlcCheck[1])$

$	// [CANIF675_Conf] CanIfSupportTTCAN
	$IF IS_TRUE(CanIfPrivateCfg.CanIfSupportTTCAN[1])$
$		// [NCANIF009] TTCAN�󥵥ݡ���
		$ERROR$$FORMAT(_("CanIfSupportTTCAN(%1%\) should be `FALSE'."), CanIfPrivateCfg.CanIfSupportTTCAN[1])$$END$$DIE()$
	$END$


$	/*
$	 *  [CANIF250_Conf] CanIfDispatchCfg
$	 */
$	// [CANIF547_Conf] CanIfDispatchUserCtrlBusOffUL
$	// [CANIF525_Conf] CanIfDispatchUserCtrlBusOffName
$	// [CANIF450] <User_ControllerBusOff>���󶡤����̥쥤��⥸�塼���CanIfDispatchUserCtrlBusOffUL�ǻ��ꤵ���
	$IF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffUL[1], "CAN_SM")$
$		// [CANIF450][CANIF559] CanIfDispatchUserCtrlBusOffUL��`CAN_SM'�ξ�硤CanIfDispatchUserCtrlBusOffName��`CanSM_ControllerBusOff'
		$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1])$
			$IF !EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1], "CanSM_ControllerBusOff")$
				$ERROR$$FORMAT(_("CanIfDispatchUserCtrlBusOffName(%1%\) should be `CanSM_ControllerBusOff'. CanIfDispatchUserCtrlBusOffUL is `CAN_SM'"), CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1])$$END$$DIE()$
			$END$
		$ELSE$
			$CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1] = "CanSM_ControllerBusOff"$
		$END$
	$ELIF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffUL[1], "CDD")$
$		// [CANIF450][CANIF560] CanIfDispatchUserCtrlBusOffUL��`CDD'�ξ�硤CanIfDispatchUserCtrlBusOffName�λ����ɬ��
		$IF !LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1])$
			$ERROR$$FORMAT(_("CanIfDispatchUserCtrlBusOffName should be set value. CanIfDispatchUserCtrlBusOffUL is `CDD'"))$$END$$DIE()$
		$END$
	$ELSE$
		$ERROR$$FORMAT(_("CanIfDispatchUserCtrlBusOffUL(%1%\) should be `CAN_SM' or `CDD'."), CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffUL[1])$$END$$DIE()$
	$END$

$	// [CANIF684_Conf] CanIfDispatchUserCtrlModeIndicationUL
$	// [CANIF683_Conf] CanIfDispatchUserCtrlModeIndicationName
$	// [CANIF689] <User_ControllerModeIndication>���󶡤����̥쥤��⥸�塼���CanIfDispatchUserCtrlModeIndicationUL�ǻ��ꤵ���
	$IF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationUL[1], "CAN_SM")$
$		// [CANIF690][CANIF691] CanIfDispatchUserCtrlModeIndicationUL��`CAN_SM'�ξ�硤CanIfDispatchUserCtrlModeIndicationName��`CanSM_ControllerModeIndication'
		$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1])$
			$IF !EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1], "CanSM_ControllerModeIndication")$
				$ERROR$$FORMAT(_("CanIfDispatchUserCtrlModeIndicationName(%1%\) should be `CanSM_ControllerModeIndication'. CanIfDispatchUserCtrlModeIndicationUL is `CAN_SM'"), CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1])$$END$$DIE()$
			$END$
		$ELSE$
			$CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1] = "CanSM_ControllerModeIndication"$
		$END$
	$ELIF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationUL[1], "CDD")$
$		// [CANIF690][CANIF692] CanIfDispatchUserCtrlModeIndicationUL��`CDD'�ξ�硤CanIfDispatchUserCtrlModeIndicationName�λ����ɬ��
		$IF !LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1])$
			$ERROR$$FORMAT(_("CanIfDispatchUserCtrlModeIndicationName should be set value. CanIfDispatchUserCtrlModeIndicationUL is `CDD'"))$$END$$DIE()$
		$END$
	$ELSE$
		$ERROR$$FORMAT(_("CanIfDispatchUserCtrlModeIndicationUL(%1%\) should be `CAN_SM' or `CDD'."), CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationUL[1])$$END$$DIE()$
	$END$

$	// [CANIF549_Conf] CanIfDispatchUserValidateWakeupEventUL
$	// [CANIF531_Conf] CanIfDispatchUserValidateWakeupEventName
	$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1])$
$		// [CANIF456][CANIF637_Conf] CanIfCtrlWakeupSupport��FALSE�ξ�硤CanIfDispatchUserValidateWakeupEventUL�������Բ�
		$wakeup_support_flg = "FALSE"$
		$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
			$IF IS_TRUE(CanIfCtrlCfg.CanIfCtrlWakeupSupport[ctrl_id])$
				$wakeup_support_flg = "TRUE"$
			$END$
		$END$
		$IF EQ(wakeup_support_flg, "FALSE")$
			$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventUL should not be set value. All of CanIfCtrlWakeupSupport is FALSE."))$$END$$DIE()$
		$END$

$		// [CANIF456] <User_ValidateWakeupEvent>���󶡤����̥쥤��⥸�塼���CanIfDispatchUserValidateWakeupEventUL�ǻ��ꤵ���
		$IF EQ(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1], "ECUM")$
$			// [CANIF563] CanIfDispatchUserValidateWakeupEventUL��`ECUM'�ξ�硤CanIfDispatchUserValidateWakeupEventName��`EcuM_ValidateWakeupEvent'
			$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$
				$IF !EQ(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1], "EcuM_ValidateWakeupEvent")$
					$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventName(%1%\) should be `EcuM_ValidateWakeupEvent'. CanIfDispatchUserValidateWakeupEventUL is `ECUM'"), CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$$END$$DIE()$
				$END$
			$ELSE$
				$CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1] = "EcuM_ValidateWakeupEvent"$
			$END$
		$ELIF EQ(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1], "CDD")$
$			// [CANIF564] CanIfDispatchUserValidateWakeupEventUL��`CDD'�ξ�硤CanIfDispatchUserValidateWakeupEventName�λ����ɬ��
			$IF !LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$
				$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventName should be set value. CanIfDispatchUserValidateWakeupEventUL is `CDD'"))$$END$$DIE()$
			$END$
		$ELSE$
			$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventUL(%1%\) should be `ECUM' or `CDD'."), CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1])$$END$$DIE()$
		$END$
	$ELSE$
		$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$
$			// CanIfDispatchUserValidateWakeupEventUL����ά���졤���ġ�CanIfDispatchUserValidateWakeupEventName���ͤ����ꤵ��Ƥ�����Ϸٹ�
			$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventUL would be set value."))$$END$$DIE()$
		$ELSE$
$			// CanIfDispatchUserValidateWakeupEventUL����ά���졤���ġ�CanIfDispatchUserValidateWakeupEventName����ά���줿����NULL_PTR���䴰
			$CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1] = "NULL_PTR"$
		$END$
	$END$


$	/*
$	 *  [CANIF253_Conf] CanIfCtrlDrvCfg
$	 *  [NCANIF015] CanIfCtrlDrvCfg��¿���٤�1
$	 */
$	// [CANIF640_Conf] CanIfCtrlDrvTxCancellation
	$IF IS_TRUE(CanIfCtrlDrvCfg.CanIfCtrlDrvTxCancellation[1])$
$		// [NCANIF004] ��������󥻥����Τ��󥵥ݡ���
		$ERROR$$FORMAT(_("CanIfCtrlDrvTxCancellation(%1%\) should be `FALSE'."), CanIfCtrlDrvCfg.CanIfCtrlDrvTxCancellation[1])$$END$$DIE()$
	$END$

$	// [CANIF642_Conf] CanIfCtrlDrvInitHohConfigRef
$	// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�


$	// [CANIF638_Conf] CanIfCtrlDrvNameRef
$	// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�



$	/*
$	 *  [CANIF546_Conf] CanIfCtrlCfg
$	 */
	$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
$	// [CANIF647_Conf] CanIfCtrlId
		$IF (CanIfCtrlCfg.CanIfCtrlId[ctrl_id] < 0) || (CanIfCtrlCfg.CanIfCtrlId[ctrl_id] > 65535)$
			$ERROR$$FORMAT(_("CanIfCtrlId(%1%\) should be in the range from 0 to 65535."), CanIfCtrlCfg.CanIfCtrlId[ctrl_id])$$END$$DIE()$
		$END$

$	// [CANIF637_Conf] CanIfCtrlWakeupSupport
		$ret = IS_TRUE(CanIfCtrlCfg.CanIfCtrlWakeupSupport[ctrl_id])$

$	// [CANIF636_Conf] CanIfCtrlCanCtrlRef
		$IF LENGTH(CanController.CanControllerId[CanIfCtrlCfg.CanIfCtrlCanCtrlRef[ctrl_id]])$
			$CanIfCtrlCfg.can_controller_id[ctrl_id] = CanController.CanControllerId[CanIfCtrlCfg.CanIfCtrlCanCtrlRef[ctrl_id]]$
			$IF LENGTH(EcuMWakeupSource.EcuMWakeupSourceId[CanController.CanWakeupSourceRef[CanIfCtrlCfg.CanIfCtrlCanCtrlRef[ctrl_id]]])$
				$CanIfCtrlCfg.wakeup_source_id[ctrl_id] = EcuMWakeupSource.EcuMWakeupSourceId[CanController.CanWakeupSourceRef[CanIfCtrlCfg.CanIfCtrlCanCtrlRef[ctrl_id]]]$
			$END$
		$END$
	$END$


$	/*
$	 *  [CANIF247_Conf] CanIfInitCfg
$	 *  [NCANIF001] CanIfInitCfg��¿���٤�1..*
$	 */
$	// [CANIF623_Conf] CanIfInitCfgSet
$	// ToDo: ���ꤵ�줿ʸ����32ʸ���ʲ����ɤ���������å�


$	/*
$	 *  [CANIF832_Conf] CanIfBufferCfg
$	 */
$	// [CANIF834_Conf] CanIfBufferSize
	$FOREACH buffer_id CanIfBufferCfg.ID_LIST$
$		// [NCANIF005] �����Хåե�����󥵥ݡ���
		$IF CanIfBufferCfg.CanIfBufferSize[buffer_id] != 0$
			$ERROR$$FORMAT(_("CanIfBufferSize(%1%\) should be `0'."), CanIfBufferCfg.CanIfBufferSize[buffer_id])$$END$$DIE()$
		$END$

$		// [CANIF833_Conf] CanIfBufferHthRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�
	$END$


$	/*
$	 *  [CANIF257_Conf] CanIfInitHohCfg
$	 *  [CANIF662] 2�����HOH(HTH/HRH)����Ѥ���CAN�ɥ饤�Фإ�������
$	 */
$	// [CANIF620_Conf] CanIfInitRefCfgSet
$	// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�


$	/*
$	 *  [CANIF258_Conf] CanIfHthCfg
$	 *  [CANIF666] HTH�ϡ�BasicCAN�ޤ���FullCAN���̿���ˡ����Ѥ��������Ǥ���褦�ˤ���
$	 *  [CANIF292] HTH��CAN����ȥ���᡼��ܥå����������ϡ��ɥ������������֥������Ȥ򻲾Ȥ���ϥ�ɥ�
$	 */
	$FOREACH hth_id CanIfHthCfg.ID_LIST$
$		// [CANIF667] ʣ����HTH����Ѥ����硤��HTH��1�Ĥ�����LPDU��°����ɬ�פ�����
		$FOREACH tx_pdu_id CanIfTxPduCfg.ID_LIST$
			$IF EQ(hth_id, CanIfTxPduCfg.hth_id_ref[tx_pdu_id])$
				$IF LENGTH(CanIfHthCfg.tx_pdu_id_ref[hth_id])$
					$ERROR$$FORMAT(_("%1%\ should belong to a single or fixed group of Tx LPDU."), hth_id)$$END$$DIE()$
				$ELSE$
					$CanIfHthCfg.tx_pdu_id_ref[hth_id] = tx_pdu_id$
				$END$
			$END$
		$END$
		$IF !LENGTH(CanIfHthCfg.tx_pdu_id_ref[hth_id])$
			$ERROR$$FORMAT(_("%1%\ should belong to a single or fixed group of Tx LPDU."), hth_id)$$END$$DIE()$
		$END$

$		// [CANIF625_Conf] CanIfHthCanCtrlIdRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�

$		// [CANIF627_Conf] CanIfHthIdSymRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�
	$END$


$	/*
$	 *  [CANIF259_Conf] CanIfHrhCfg
$	 *  [CANIF665] HRH�ϡ�BasicCAN�ޤ���FullCAN���̿���ˡ����Ѥ��Ƽ����Ǥ���褦�ˤ���
$	 *  [CANIF291] HRH��CAN����ȥ���᡼��ܥå����������ϡ��ɥ������������֥������Ȥ򻲾Ȥ���ϥ�ɥ�
$	 */
	$FOREACH hrh_id CanIfHrhCfg.ID_LIST$
$		// [CANIF664] ʣ����HRH�����Ѥ�����硤��HRH�Ͼ��ʤ��Ȥ�1�Ĥμ���LPDU��°����ɬ�פ�����
		$FOREACH rx_pdu_id CanIfRxPduCfg.ID_LIST$
			$IF EQ(hrh_id, CanIfRxPduCfg.CanIfRxPduHrhIdRef[rx_pdu_id])$
				$CanIfHrhCfg.rx_pdu_id_ref[hrh_id] = rx_pdu_id$
			$END$
		$END$
		$IF !LENGTH(CanIfHrhCfg.rx_pdu_id_ref[hrh_id])$
			$ERROR$$FORMAT(_("%1%\ should belong to at least to a single or fixed group of Tx LPDU."), hrh_id)$$END$$DIE()$
		$END$

$		[CANIF632_Conf] CanIfHrhSoftwareFilter
		$IF IS_TRUE(CanIfHrhCfg.CanIfHrhSoftwareFilter[hrh_id])$
$			// [NCANIF006] ���եȥ������ե��륿��󥰤��󥵥ݡ���
			$ERROR$$FORMAT(_("CanIfHrhSoftwareFilter(%1%\) should be `FALSE'."), CanIfHrhCfg.CanIfHrhSoftwareFilter[hrh_id])$$END$$DIE()$
		$END$

$		// [CANIF631_Conf] CanIfHrhCanCtrlIdRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�

$		// [CANIF634_Conf] CanIfHrhIdSymRef 
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�
	$END$


$	/*
$	 *  [CANIF248_Conf] CanIfTxPduCfg
$	 */
	$FOREACH tx_pdu_id CanIfTxPduCfg.ID_LIST$
$		// [CANIF590_Conf] CanIfTxPduCanIdType
$		// [CANIF243] Can_Write()��ƤӽФ�����CAN-ID�Υ����פ����ꤹ��
		$IF !EQ(CanIfTxPduCfg.CanIfTxPduCanIdType[tx_pdu_id], "EXTENDED_CAN") && !EQ(CanIfTxPduCfg.CanIfTxPduCanIdType[tx_pdu_id], "STANDARD_CAN")$
			$ERROR$$FORMAT(_("CanIfTxPduCanIdType(%1%\) should be `EXTENDED_CAN' or `STANDARD_CAN'."), CanIfTxPduCfg.CanIfTxPduCanIdType[tx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF592_Conf] CanIfTxPduCanId
		$IF EQ(CanIfTxPduCfg.CanIfTxPduCanIdType[tx_pdu_id], "EXTENDED_CAN") && ((CanIfTxPduCfg.CanIfTxPduCanId[tx_pdu_id] < 0) || (CanIfTxPduCfg.CanIfTxPduCanId[tx_pdu_id] > 536870911))$
			$ERROR$$FORMAT(_("CanIfTxPduCanId(%1%\) should be in the range from 0 to 536870911. CanIfTxPduCanIdType is EXTENDED_CAN."), CanIfTxPduCfg.CanIfTxPduCanId[tx_pdu_id])$$END$$DIE()$
		$END$
		$IF EQ(CanIfTxPduCfg.CanIfTxPduCanIdType[tx_pdu_id], "STANDARD_CAN") && ((CanIfTxPduCfg.CanIfTxPduCanId[tx_pdu_id] < 0) || (CanIfTxPduCfg.CanIfTxPduCanId[tx_pdu_id] > 2047))$
			$ERROR$$FORMAT(_("CanIfTxPduCanId(%1%\) should be in the range from 0 to 2047. CanIfTxPduCanIdType is STANDARD_CAN."), CanIfTxPduCfg.CanIfTxPduCanId[tx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF594_Conf] CanIfTxPduDlc
		$IF (CanIfTxPduCfg.CanIfTxPduDlc[tx_pdu_id] < 0) || (CanIfTxPduCfg.CanIfTxPduDlc[tx_pdu_id] > 8)$
			$ERROR$$FORMAT(_("CanIfTxPduDlc(%1%\) should be in the range from 0 to 8."), CanIfTxPduCfg.CanIfTxPduDlc[tx_pdu_id])$$END$$DIE()$
		$END$
$		// [NCANIF015] �����Х�PDU��Ĺ�����DLC��û����硤���顼
		$IF CanIfTxPduCfg.CanIfTxPduDlc[tx_pdu_id] < CanIfTxPduCfg.pdu_length[tx_pdu_id]$
			$ERROR$$FORMAT(_("CanIfTxPduDlc(%1%\) should be equal or larger than PduLength(%2%\). [%3%\]"), CanIfTxPduCfg.CanIfTxPduDlc[tx_pdu_id], CanIfTxPduCfg.pdu_length[tx_pdu_id], tx_pdu_id)$$END$$DIE()$
		$END$

$		// [CANIF591_Conf] CanIfTxPduId
		$IF (CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id] < 0) || (CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id] > 4294967295)$
			$ERROR$$FORMAT(_("CanIfTxPduId(%1%\) should be in the range from 0 to 4294967295."), CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF589_Conf] CanIfTxPduReadNotifyStatus
		$IF IS_TRUE(CanIfTxPduCfg.CanIfTxPduReadNotifyStatus[tx_pdu_id]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicReadTxPduNotifyStatusApi[1])$
			$ERROR$$FORMAT(_("CanIfTxPduReadNotifyStatus(%1%\) should not be set value. CanIfPublicReadTxPduNotifyStatusApi is FALSE."), CanIfTxPduCfg.CanIfTxPduReadNotifyStatus[tx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF593_Conf] CanIfTxPduType
$		// [NCANIF016] ưŪCAN-ID������󥵥ݡ���
		$IF !EQ(CanIfTxPduCfg.CanIfTxPduType[tx_pdu_id], "STATIC")$
			$ERROR$$FORMAT(_("CanIfTxPduType(%1%\) should be `STATIC'."), CanIfTxPduCfg.CanIfTxPduType[tx_pdu_id])$$END$$DIE()$
		$END$
		
$		// [CANIF527_Conf] CanIfTxPduUserTxConfirmationUL
$		// [CANIF528_Conf] CanIfTxPduUserTxConfirmationName
$		// [CANIF438] <User_TxConfirmation>���󶡤����̥쥤��⥸�塼���CanIfTxPduUserTxConfirmationUL�ǻ��ꤵ���
$		// [CANIF542] <User_TxConfirmation>()��̾����CanIfTxPduUserTxConfirmationName���������
		$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id])$
			$IF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "CAN_NM")$
$				// [CANIF543] CanIfTxPduUserTxConfirmationUL��CAN_NM�ξ�硤CanIfTxPduUserTxConfirmationName��CanNm_TxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "CanNm_TxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `CanNm_TxConfirmation'. CanIfTxPduUserTxConfirmationUL is `CAN_NM'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "CanNm_TxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "CAN_TP")$
$				// [CANIF550] CanIfTxPduUserTxConfirmationUL��CAN_TP�ξ�硤CanIfTxPduUserTxConfirmationName��CanTp_TxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "CanTp_TxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `CanTp_TxConfirmation'. CanIfTxPduUserTxConfirmationUL is `CAN_TP'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "CanTp_TxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "CDD")$
$				// [CANIF551] CanIfTxPduUserTxConfirmationUL��CDD�ξ�硤<User_TxConfirmation>��̾����CanIfTxPduUserTxConfirmationName�ǻ��ꤵ���
				$IF !LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be set value. CanIfTxPduUserTxConfirmationUL is `CDD'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "J1939TP")$
$				// [CANIF544] CanIfTxPduUserTxConfirmationUL��J1939TP�ξ�硤CanIfTxPduUserTxConfirmationName��J1939Tp_TxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "J1939Tp_TxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `J1939Tp_TxConfirmation'. CanIfTxPduUserTxConfirmationUL is `J1939TP'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "J1939Tp_TxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "PDUR")$
$				// [CANIF439] CanIfTxPduUserTxConfirmationUL��PDUR�ξ�硤CanIfTxPduUserTxConfirmationName��PduR_CanIfTxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "PduR_CanIfTxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `PduR_CanIfTxConfirmation'. CanIfTxPduUserTxConfirmationUL is `PDUR'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "PduR_CanIfTxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "XCP")$
$				// [CANIF556] CanIfTxPduUserTxConfirmationUL��XCP�ξ�硤CanIfTxPduUserTxConfirmationName��Xcp_CanIfTxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "Xcp_CanIfTxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `Xcp_CanIfTxConfirmation'. CanIfTxPduUserTxConfirmationUL is `XCP'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "Xcp_CanIfTxConfirmation"$
				$END$
			$ELSE$
				$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationUL should be `CAN_NM' or `CAN_TP' or `CDD' or `J1939TP' or `PDUR' or `XCP'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
			$END$
		$ELSE$
			$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
$				// CanIfTxPduUserTxConfirmationUL����ά���졤CanIfTxPduUserTxConfirmationName���ͤ����ꤵ��Ƥ����硤���顼
				$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationUL should be set value. (%1%\)"), tx_pdu_id)$$END$$DIE()$
			$ELSE$
$				// CanIfTxPduUserTxConfirmationUL����ά���졤���ġ�CanIfTxPduUserTxConfirmationName����ά���줿��硤NULL_PTR���䴰
				$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "NULL_PTR"$
			$END$
		$END$

$		// [CANIF831_Conf] CanIfTxPduBufferRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�

$		// [CANIF603_Conf] CanIfTxPduRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�
	$END$


$	/*
$	 *  [CANIF249_Conf] CanIfRxPduCfg
$	 */
	$FOREACH rx_pdu_id CanIfRxPduCfg.ID_LIST$
$		// [CANIF596_Conf] CanIfRxPduCanIdType
		$IF !EQ(CanIfRxPduCfg.CanIfRxPduCanIdType[rx_pdu_id], "EXTENDED_CAN") && !EQ(CanIfRxPduCfg.CanIfRxPduCanIdType[rx_pdu_id], "STANDARD_CAN")$
			$ERROR$$FORMAT(_("CanIfRxPduCanIdType(%1%\) should be `EXTENDED_CAN' or `STANDARD_CAN'."), CanIfRxPduCfg.CanIfRxPduCanIdType[rx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF598_Conf] CanIfRxPduCanId
		$IF LENGTH(CanIfRxPduCfg.CanIfRxPduCanId[rx_pdu_id])$
			$IF EQ(CanIfRxPduCfg.CanIfRxPduCanIdType[rx_pdu_id], "EXTENDED_CAN") && ((CanIfRxPduCfg.CanIfRxPduCanId[rx_pdu_id] < 0) || (CanIfRxPduCfg.CanIfRxPduCanId[rx_pdu_id] > 536870911))$
				$ERROR$$FORMAT(_("CanIfRxPduCanId(%1%\) should be in the range from 0 to 536870911. CanIfRxPduCanIdType is EXTENDED_CAN."), CanIfRxPduCfg.CanIfRxPduCanId[rx_pdu_id])$$END$$DIE()$
			$END$
			$IF EQ(CanIfRxPduCfg.CanIfRxPduCanIdType[rx_pdu_id], "STANDARD_CAN") && ((CanIfRxPduCfg.CanIfRxPduCanId[rx_pdu_id] < 0) || (CanIfRxPduCfg.CanIfRxPduCanId[rx_pdu_id] > 2047))$
				$ERROR$$FORMAT(_("CanIfRxPduCanId(%1%\) should be in the range from 0 to 2047. CanIfRxPduCanIdType is STANDARD_CAN."), CanIfRxPduCfg.CanIfRxPduCanId[rx_pdu_id])$$END$$DIE()$
			$END$
		$END$

$		// [CANIF599_Conf] CanIfRxPduDlc
		$IF (CanIfRxPduCfg.CanIfRxPduDlc[rx_pdu_id] < 0) || (CanIfRxPduCfg.CanIfRxPduDlc[rx_pdu_id] > 8)$
			$ERROR$$FORMAT(_("CanIfRxPduDlc(%1%\) should be in the range from 0 to 8."), CanIfRxPduCfg.CanIfRxPduDlc[rx_pdu_id])$$END$$DIE()$
		$END$
		$IF CanIfRxPduCfg.CanIfRxPduDlc[rx_pdu_id] < CanIfRxPduCfg.pdu_length[rx_pdu_id]$
			$ERROR$$FORMAT(_("CanIfRxPduDlc(%1%\) should be equal or larger than PduLength(%2%\). [%3%\]"), CanIfRxPduCfg.CanIfRxPduDlc[rx_pdu_id], CanIfRxPduCfg.pdu_length[rx_pdu_id], rx_pdu_id)$$END$$DIE()$
		$END$

$		// [CANIF597_Conf] CanIfRxPduId
		$IF (CanIfRxPduCfg.CanIfRxPduId[rx_pdu_id] < 0) || (CanIfRxPduCfg.CanIfRxPduId[rx_pdu_id] > 4294967295)$
			$ERROR$$FORMAT(_("CanIfRxPduId(%1%\) should be in the range from 0 to 4294967295."), CanIfRxPduCfg.CanIfRxPduId[rx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF600_Conf] CanIfRxPduReadData
		$IF IS_TRUE(CanIfRxPduCfg.CanIfRxPduReadData[rx_pdu_id]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduDataApi[1])$
			$ERROR$$FORMAT(_("CanIfRxPduReadData should be set to `FALSE'. CanIfPublicReadRxPduDataApi is `FALSE'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
		$END$

$		// [CANIF595_Conf] CanIfRxPduReadNotifyStatus
		$IF IS_TRUE(CanIfRxPduCfg.CanIfRxPduReadNotifyStatus[rx_pdu_id]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduNotifyStatusApi[1])$
			$ERROR$$FORMAT(_("CanIfRxPduReadNotifyStatus(%1%\) should not be set value. CanIfPublicReadRxPduNotifyStatusApi is FALSE."), CanIfRxPduCfg.CanIfRxPduReadNotifyStatus[rx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF529_Conf] CanIfRxPduUserRxIndicationUL
$		// [CANIF530_Conf] CanIfRxPduUserRxIndicationName
$		// [CANIF441] <User_RxIndication>���󶡤����̥쥤��⥸�塼���CanIfRxPduUserRxIndicationUL�ǻ��ꤵ���
$		// [CANIF552] <User_RxIndication>��̾����CanIfRxPduUserRxIndicationName���������
		$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id])$
			$IF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "CAN_NM")$
$				// [CANIF445] CanIfRxPduUserRxIndicationUL��CAN_NM�ξ�硤CanIfRxPduUserRxIndicationName��CanNm_RxIndication
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "CanNm_RxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `CanNm_RxIndication'. CanIfRxPduUserRxIndicationUL is `CAN_NM'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "CanNm_RxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "CAN_TP")$
$				// [CANIF448] CanIfRxPduUserRxIndicationUL��CAN_TP�ξ�硤CanIfRxPduUserRxIndicationName��CanTp_RxIndication
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "CanTp_RxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `CanTp_RxIndication'. CanIfRxPduUserRxIndicationUL is `CAN_TP'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "CanTp_RxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "CDD")$
$				// [CANIF557] CanIfRxPduUserRxIndicationUL��CDD�ξ�硤<User_TxConfirmation>��̾����CanIfTxPduUserTxConfirmationName�ǻ��ꤵ���
				$IF !LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be set value. CanIfRxPduUserRxIndicationUL is `CDD'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "J1939TP")$
$				// [CANIF554] CanIfRxPduUserRxIndicationUL��J1939TP�ξ�硤CanIfRxPduUserRxIndicationName��J1939Tp_RxIndication
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "J1939Tp_RxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `J1939Tp_RxIndication'. CanIfRxPduUserRxIndicationUL is `J1939TP'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "J1939Tp_RxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "PDUR")$
$				// [CANIF442] CanIfRxPduUserRxIndicationUL��PDUR�ξ�硤CanIfRxPduUserRxIndicationName��PduR_CanIfRxIndication 
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "PduR_CanIfRxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `PduR_CanIfRxIndication'. CanIfRxPduUserRxIndicationUL is `PDUR'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "PduR_CanIfRxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "XCP")$
$				// [CANIF555] CanIfRxPduUserRxIndicationUL��XCP�ξ�硤CanIfRxPduUserRxIndicationName��Xcp_CanIfRxIndication
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "Xcp_CanIfRxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `Xcp_CanIfRxIndication'. CanIfRxPduUserRxIndicationUL is `XCP'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "Xcp_CanIfRxIndication"$
				$END$
			$ELSE$
				$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationUL sould be `PDUR'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
			$END$
		$ELSE$
			$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
$				// CanIfRxPduUserRxIndicationUL����ά���졤���ġ�CanIfRxPduUserRxIndicationName���ͤ����ꤵ��Ƥ����硤���顼
				$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationUL should be set value. (%1%\)"), rx_pdu_id)$$END$$DIE()$
			$ELSE$
$				// CanIfRxPduUserRxIndicationUL����ά���졤���ġ�CanIfRxPduUserRxIndicationName����ά���줿��硤NULL_PTR���䴰
				$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "NULL_PTR"$
			$END$
		$END$

$		// [CANIF602_Conf] CanIfRxPduHrhIdRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�

$		// [CANIF601_Conf] CanIfRxPduRef
$		// ���ꤷ����������������ϻ����˳�ǧ�Ѥ�
	$END$
$END$

$ ====================================================================
$  [CANIF460] �ץꥳ��ѥ����ѥإå������ؿ�
$ ====================================================================
$FUNCTION GEN_CANIF_CFG_H$
	$FILE "CanIf_Cfg.h"$
	/* CanIf_Cfg.h */$NL$
	
	#ifndef TOPPERS_A_CANIF_CFG_H$NL$
	#define TOPPERS_A_CANIF_CFG_H$NL$
	$NL$

$	/*
$	 *  �ޥ������
$	 */
$	// [CANIF614_Conf] CanIfPublicDevErrorDetect
$	// �ǥե�����ͤ�TRUE
	#define CANIF_PUBLIC_DEV_ERROR_DETECT$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicDevErrorDetect[1]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicDevErrorDetect[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$

$	// [CANIF613_Conf] CanIfPublicVersionInfoApi
$	// �ǥե�����ͤ�TRUE
	#define CANIF_PUBLIC_VERSION_INFO_API$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicVersionInfoApi[1]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicVersionInfoApi[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$$NL$

$	// [CANIF607_Conf] CanIfPublicReadRxPduDataApi 
$	// �ǥե�����ͤ�FALSE
	#define CANIF_PUBLIC_READRXPDU_DATA_API$TAB$$TAB$$TAB$$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicReadRxPduDataApi[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduDataApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CANIF608_Conf] CanIfPublicReadRxPduNotifyStatusApi 
$	// �ǥե�����ͤ�FALSE
	#define CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicReadRxPduNotifyStatusApi[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduNotifyStatusApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CANIF609_Conf] CanIfPublicReadTxPduNotifyStatusApi  
$	// �ǥե�����ͤ�FALSE
	#define CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicReadTxPduNotifyStatusApi[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicReadTxPduNotifyStatusApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$$NL$

$	// [CANIF785_Conf] CanIfPublicChangeBaudrateSupport
$	// �ǥե�����ͤ�FALSE
	#define CANIF_PUBLIC_CHANGE_BAUDRATE_SUPPORT$TAB$$TAB$$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicChangeBaudrateSupport[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicChangeBaudrateSupport[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CANIF733_Conf] CanIfPublicTxConfirmPollingSupport
	#define CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT$TAB$$TAB$$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicTxConfirmPollingSupport[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicTxConfirmPollingSupport[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CANIF611_Conf] CanIfPublicWakeupCheckValidSupport
	#define CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicWakeupCheckValidSupport[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicWakeupCheckValidSupport[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CANIF522_Conf] CanIfPublicCancelTransmitSupport
	#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT$TAB$$TAB$$TAB$
	$IF IS_TRUE(CanIfPublicCfg.CanIfPublicCancelTransmitSupport[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$$NL$

$	// [CANIF617_Conf] CanIfPrivateDlcCheck
	#define CANIF_PRIVATE_DLC_CHECK 
	$IF LENGTH(CanIfPrivateCfg.CanIfPrivateDlcCheck[1]) && IS_TRUE(CanIfPrivateCfg.CanIfPrivateDlcCheck[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$$NL$

$	// SUPPORT_READ_PDU_NOTYFY_STATUS
	#if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON) || (CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON)$NL$
	#define SUPPORT_READ_PDU_NOTYFY_STATUS$NL$
	#endif$NL$
	$NL$

	#endif /* TOPPERS_A_CANIF_CFG_H */

$END$

$ ====================================================================
$  ��󥯥������ѥإå������ؿ�
$ ====================================================================
$FUNCTION GEN_CANIF_L_CFG_H$
	$FILE "CanIf_Lcfg.h"$
	/* CanIf_Lcfg.h */$NL$
	$NL$

	#ifndef TOPPERS_A_CANIF_L_CFG_H$NL$
	#define TOPPERS_A_CANIF_L_CFG_H$NL$
	$NL$

$	// [CANIF546_Conf] CanIf����ȥ����Ϣ�ϥ�󥯥�����ѥ�᡼��
	$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
		extern CANIF_CTRL_CB canif_ctrl_cb_$ctrl_id$;$NL$
	$END$
	$NL$

	#endif /* TOPPERS_A_CANIF_L_CFG_H */
$END$

$ ====================================================================
$  [CANIF461] ��󥯥������Ѽ��������ؿ�
$ ====================================================================
$FUNCTION GEN_CANIF_L_CFG_C$
$ 	// [CANIF374] ��󥯻��˥���ե�����졼������ǽ�ʥѥ�᡼����
	$FILE "CanIf_Lcfg.c"$
	/* CanIf_Lcfg.c */$NL$
	$NL$

	#include "CanIf.h"$NL$
	#include "CanIf_Lcfg.h"$NL$

$	// [CANIF233] �ʲ��Υإå��ե�����򥤥󥯥롼�ɤ���
	#include "CanSM_Cbk.h"$NL$
	#include "EcuM_Cbk.h"$NL$

$	// [CANIF671_Conf] CanIfPublicCddHeaderFile
$	// [CANIF233] CDD�ξ��˥��󥯥롼�ɤ��륳����Хå��ؿ��إå��ե�����̾��CanIfPublicCddHeaderFile���������
	$IF LENGTH(CanIfPublicCfg.CanIfPublicCddHeaderFile[1])$
		#include "$CanIfPublicCfg.CanIfPublicCddHeaderFile[1]$.h"$NL$
	$END$
	$NL$

$	// [CANIF525_Conf][CANIF558] <User_ControllerBusOff>��̾����CanIfDispatchUserCtrlBusOffName�˻��ꤵ���
$	// [CANIF524] <User_ControllerBusOff>�������ɬ��
	$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1])$
		User_ControllerBusOff$TAB$$TAB$$TAB$CanIfDispatchUserCtrlBusOffName$TAB$$TAB$$TAB$ = &$CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1]$;$NL$
	$END$
$	// [CANIF683_Conf] CanIfDispatchUserCtrlModeIndicationName
	$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1])$
		User_ControllerModeIndication$TAB$CanIfDispatchUserCtrlModeIndicationName$TAB$ = &$CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1]$;$NL$
	$END$
$	// [CANIF531_Conf] CanIfDispatchUserValidateWakeupEventName
	$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1]) && !EQ(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1], "NULL_PTR")$
		User_ValidateWakeupEvent$TAB$$TAB$CanIfDispatchUserValidateWakeupEventName = &$CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1]$;$NL$
	$ELSE$
		User_ValidateWakeupEvent$TAB$$TAB$CanIfDispatchUserValidateWakeupEventName = NULL_PTR;$NL$
	$END$
	$NL$

	const uint16 tnum_canif_controller = $LENGTH(CanIfCtrlCfg.ID_LIST)$U; /* CanIf����ȥ���� */$NL$
	$NL$

	/* CanIf����ȥ�������֥�å� : canif_ctrl_cb_<CanIfCtrlCfg> */$NL$
	$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
		CANIF_CTRL_CB canif_ctrl_cb_$ctrl_id$;$NL$
	$END$
	$NL$

	/* CanIf����ȥ��������֥�å����� : canif_ctrl_inib_table */$NL$
	const CANIF_CTRL_INIB canif_ctrl_inib_table[$LENGTH(CanIfCtrlCfg.ID_LIST)$] = {$NL$
	$JOINEACH ctrl_id CanIfCtrlCfg.ID_LIST ",\n"$
		$TAB$/* $ctrl_id$ (CanIfCtrlId: $CanIfCtrlCfg.CanIfCtrlId[ctrl_id]$) */$NL$
		$TAB${$NL$
		$TAB$$TAB$$CanIfCtrlCfg.can_controller_id[ctrl_id]$U,$TAB$/* CanControllerId */$NL$
		$TAB$$TAB$$CanIfCtrlCfg.wakeup_source_id[ctrl_id]$U,$TAB$/* EcuMWakeupSourceId */$NL$
		$TAB$$TAB$$IS_TRUE(CanIfCtrlCfg.CanIfCtrlWakeupSupport[ctrl_id])$,$TAB$/* CanIfCtrlWakeupSupport */$NL$
		$TAB$$TAB$&canif_ctrl_cb_$ctrl_id$$TAB$/* p_canif_ctrl_cb */$NL$
		$TAB$}
	$END$
	$NL$};
$END$

$ ====================================================================
$  [CANIF462] �ݥ��ȥӥ���Ѽ��������ؿ�
$ ====================================================================
$FUNCTION GEN_CANIF_PB_CFG_C$
$ 	// [CANIF374] �ӥ�ɸ�˥���ե�����졼������ǽ�ʥѥ�᡼����
	$FILE "CanIf_PBcfg.c"$

	/* CanIf_PBcfg.c */$NL$
	$NL$

	#include "Os.h"$NL$
	#include "CanIf.h"$NL$
	#include "CanIf_Lcfg.h"$NL$

$	// [CANIF208] ��̥쥤��Υإå��ե�����򥤥󥯥롼��
	#include "PduR_CanIf.h"$NL$
	#include "SchM_CanIf.h"$NL$
	$NL$

$	// [CANIF233] �ʲ��Υإå��ե�����򥤥󥯥롼��
	#include "CanNm_Cbk.h"$NL$
	#include "CanTp_Cbk.h"$NL$
	#include "J1939Tp_Cbk.h"$NL$
	#include "XcpOnCan_Cbk.h"$NL$
	
$	// [CANIF671_Conf] CanIfPublicCddHeaderFile
$	// [CANIF233] CDD�ξ��˥��󥯥롼�ɤ��륳����Хå��ؿ��إå��ե�����̾��CanIfPublicCddHeaderFile���������
	$IF LENGTH(CanIfPublicCfg.CanIfPublicCddHeaderFile[1])$
		#include "$CanIfPublicCfg.CanIfPublicCddHeaderFile[1]$.h"$NL$
	$END$
	$NL$

	/* ������λ���Υե饰 : rx_indication_flg_<CanIfInitCfg>_<CanIfRxPduCfg> */$NL$
	#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON$NL$
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
			static boolean rx_indication_flg_$init_id$_$rx_pdu_id$; /* $CanIfRxPduCfg.CanIfRxPduRef[rx_pdu_id]$ */$NL$
		$END$
	$END$
	#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */$NL$
	$NL$

	/* PDU���ξ��� : read_notify_status_<CanIfInitCfg>_<CanIf[Tx|Rx]PduCfg> */$NL$
	#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS$NL$
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$FOREACH pdu_id CanIfInitCfg.pdu_list[init_id]$
$			// �����ξ���CanIfTxPduReadNotifyStatus�������ξ���CanIfRxPduReadNotifyStatus ���ͤ����
			$read_notify_status = ""$
			$FOREACH tx_pdu_id CanIfInitCfg.tx_pdu_list[init_id]$
				$IF EQ(pdu_id, tx_pdu_id)$
					$read_notify_status = CanIfTxPduCfg.CanIfTxPduReadNotifyStatus[pdu_id]$
				$END$
			$END$
			$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
				$IF EQ(pdu_id, rx_pdu_id)$
					$read_notify_status = CanIfRxPduCfg.CanIfRxPduReadNotifyStatus[pdu_id]$
				$END$
			$END$
$			// CanIfTxPduReadNotifyStatus �ޤ��� CanIfRxPduReadNotifyStatus ��TRUE�ξ��Τ�����
			$IF IS_TRUE(read_notify_status)$
				static CanIf_NotifStatusType read_notify_status_$init_id$_$pdu_id$;$NL$
			$END$
		$END$
	$END$
	#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */$NL$
	$NL$

	/* ����LPDU�Хåե� : rx_lpdu_buffer_<CanIfInitCfg>_<CanIfRxPduCfg> */$NL$
	#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON$NL$
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
			$IF IS_TRUE(CanIfRxPduCfg.CanIfRxPduReadData[rx_pdu_id])$
				static uint8 rx_lpdu_buffer_$init_id$_$rx_pdu_id$[$CanIfRxPduCfg.CanIfRxPduDlc[rx_pdu_id]$]; /* $CanIfRxPduCfg.CanIfRxPduRef[rx_pdu_id]$ */$NL$
			$END$
		$END$
	$END$
	#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */$NL$
	$NL$

	/* LPDU������֥�å����� : lpdu_inib_table_<CanIfInitCfg> */$NL$
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$IF CanIfInitCfg.pdu_num[init_id] > 0$
			static const LPDU_INIB lpdu_inib_table_$init_id$[$CanIfInitCfg.pdu_num[init_id]$] = {$NL$
			$JOINEACH pdu_id CanIfInitCfg.pdu_list[init_id] ",\n"$
				$pdu_direction = ""$
				$FOREACH tx_pdu_id CanIfTxPduCfg.ID_LIST$
					$IF EQ(pdu_id, tx_pdu_id)$
						$pdu_direction = "CANIF_SEND"$
					$END$
				$END$
				$FOREACH rx_pdu_id CanIfRxPduCfg.ID_LIST$
					$IF EQ(pdu_id, rx_pdu_id)$
						$pdu_direction = "CANIF_RECEIVE"$
					$END$
				$END$
				$IF EQ(pdu_direction, "CANIF_SEND")$
					$TAB$/* $CanIfTxPduCfg.CanIfTxPduRef[pdu_id]$: $pdu_id$ (CanIfTxPduId: $CanIfTxPduCfg.CanIfTxPduId[pdu_id]$) */$NL$
					$TAB${$NL$
					$TAB$$TAB$$CanIfTxPduCfg.CanIfTxPduCanId[pdu_id]$U,$TAB$/* CanIfPduCanId */$NL$
					$TAB$$TAB$$CanIfTxPduCfg.CanIfTxPduDlc[pdu_id]$U,$TAB$/* CanIfPduDlc */$NL$
					$TAB$$TAB$$CanIfTxPduCfg.can_hw_obj_id[pdu_id]$U,$TAB$/* CanObjectId */$NL$
					$TAB$$TAB$$CanIfTxPduCfg.pdu_handle_id[pdu_id]$U,$TAB$/* PduRPduHandleId */$NL$
					$IF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[pdu_id], "NULL_PTR")$
						$TAB$$TAB$$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[pdu_id]$,$TAB$/* CanIfPduUserConfirmationName */$NL$
					$ELSE$
						$TAB$$TAB$(CanIf_PduUserConfirmation)&$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[pdu_id]$,$TAB$/* CanIfPduUserConfirmationName */$NL$
					$END$
					$TAB$$TAB$&canif_ctrl_cb_$CanIfTxPduCfg.ctrl_id_ref[pdu_id]$,$TAB$/* p_canif_ctrl_cb */$NL$
					#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS$NL$
					$IF IS_TRUE(CanIfTxPduCfg.CanIfTxPduReadNotifyStatus[pdu_id])$
						$TAB$$TAB$&read_notify_status_$init_id$_$pdu_id$,$TAB$/* p_notify_status */$NL$
					$ELSE$
						$TAB$$TAB$NULL_PTR,$TAB$/* p_notify_status */$NL$
					$END$
					#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */$NL$
					#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON$NL$
					$TAB$$TAB$NULL_PTR,$TAB$/* p_rx_indication_flg */$NL$
					$TAB$$TAB$NULL_PTR,$TAB$/* p_rx_lpdu_buffer */$NL$
					#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */$NL$
					#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON$NL$
					$TAB$$TAB$$pdu_direction$$TAB$/* lpdu_direction */$NL$
					#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */$NL$
					$TAB$}
				$ELIF EQ(pdu_direction, "CANIF_RECEIVE")$
					$TAB$/* $CanIfRxPduCfg.CanIfRxPduRef[pdu_id]$: $pdu_id$ (CanIfRxPduId: $CanIfRxPduCfg.CanIfRxPduId[pdu_id]$) */$NL$
					$TAB${$NL$
					$TAB$$TAB$$CanIfRxPduCfg.CanIfRxPduCanId[pdu_id]$U,$TAB$/* CanIfPduCanId */$NL$
					$TAB$$TAB$$CanIfRxPduCfg.CanIfRxPduDlc[pdu_id]$U,$TAB$/* CanIfPduDlc */$NL$
					$TAB$$TAB$$CanIfRxPduCfg.can_hw_obj_id[pdu_id]$U,$TAB$/* CanObjectId */$NL$
					$TAB$$TAB$$CanIfRxPduCfg.pdu_handle_id[pdu_id]$U,$TAB$/* PduRPduHandleId */$NL$
					$IF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[pdu_id], "NULL_PTR")$
						$TAB$$TAB$$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[pdu_id]$,$TAB$/* CanIfPduUserConfirmationName */$NL$
					$ELSE$
						$TAB$$TAB$(CanIf_PduUserConfirmation)&$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[pdu_id]$,$TAB$/* CanIfPduUserConfirmationName */$NL$
					$END$
					$TAB$$TAB$&canif_ctrl_cb_$CanIfRxPduCfg.ctrl_id_ref[pdu_id]$,$TAB$/* p_canif_ctrl_cb */$NL$
					#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS$NL$
					$IF IS_TRUE(CanIfRxPduCfg.CanIfRxPduReadNotifyStatus[pdu_id])$
						$TAB$$TAB$&read_notify_status_$init_id$_$pdu_id$,$TAB$/* p_notify_status */$NL$
					$ELSE$
						$TAB$$TAB$NULL_PTR,$TAB$/* p_notify_status */$NL$
					$END$
					#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */$NL$
					#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON$NL$
					$TAB$$TAB$&rx_indication_flg_$init_id$_$pdu_id$,$TAB$/* p_rx_indication_flg */$NL$
					$IF IS_TRUE(CanIfRxPduCfg.CanIfRxPduReadData[pdu_id])$
						$TAB$$TAB$rx_lpdu_buffer_$init_id$_$pdu_id$,$TAB$/* p_rx_lpdu_buffer */$NL$
					$ELSE$
						$TAB$$TAB$NULL_PTR,$TAB$/* p_rx_lpdu_buffer */$NL$
					$END$
					#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */$NL$
					#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON$NL$
					$TAB$$TAB$$pdu_direction$$TAB$/* lpdu_direction */$NL$
					#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */$NL$
					$TAB$}
				$END$
			$END$
			$NL$};$NL$
			$NL$
		$END$
	$END$
	$NL$

	/* LPDU������֥�å������CanObjectId�ǥ����Ȥ����ꥹ�� : lpdu_inib_hoh_list_<CanIfInitCfg> */$NL$
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$IF CanIfInitCfg.pdu_num[init_id] > 0$
			static const LPDU_INIB * const lpdu_inib_hoh_list_$init_id$[$CanIfInitCfg.pdu_num[init_id]$] = {$NL$
			$JOINEACH pdu_id CanIfInitCfg.pdu_list_by_can_object_id[init_id] ",\n"$
				$index = 0$
				$pdu_ref = ""$
				$FOREACH tx_pdu_id CanIfInitCfg.tx_pdu_list[init_id]$
					$IF EQ(pdu_id, tx_pdu_id)$
						$index = CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id]$
						$pdu_ref = CanIfTxPduCfg.CanIfTxPduRef[tx_pdu_id]$
					$END$
				$END$
				$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
					$IF EQ(pdu_id, rx_pdu_id)$
						$index = CanIfRxPduCfg.CanIfRxPduId[rx_pdu_id]$
						$pdu_ref = CanIfRxPduCfg.CanIfRxPduRef[rx_pdu_id]$
					$END$
				$END$
				$TAB$/* $pdu_ref$ */$NL$
				$TAB$&lpdu_inib_table_$init_id$[$index$]
			$END$
			$NL$};$NL$
		$END$
		$NL$
	$END$

	/* CanIf����ե�����졼��������ơ��֥� : <CanIfInitCfgSet> */$NL$
$	// [CANIF523] CanIf_ConfigType�ν�����ǡ�����¤�ˤϡ�CanIf�ѥ֥�å��ѥ�᡼��������ȳ�LPDU��������ޤޤ��
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		const CanIf_ConfigType $CanIfInitCfg.CanIfInitCfgSet[init_id]$ = {$NL$
		$TAB$$CanIfInitCfg.pdu_num[init_id]$U,$TAB$/* tnum_lpdu */$NL$
		$TAB$lpdu_inib_table_$init_id$,$TAB$/* p_lpdu_inib_table */$NL$
		$TAB$lpdu_inib_hoh_list_$init_id$$TAB$/* pp_lpdu_inib_hoh_list */$NL$
		};$NL$
		$NL$
	$END$

	/* �ǥե���Ȥ�CanIf����ե�����졼�������� */$NL$
	const CanIf_ConfigType * const p_default_canif_config = &$CanIfInitCfg.CanIfInitCfgSet[1]$;$NL$
$END$


$ ====================================================================
$  �ᥤ�����
$ ====================================================================
$ /*
$  *  [CANIF104] CanIf�������뤿��Τ��٤ƤΥ���ե�����졼����������������
$  *  [CANIF066] CanIf��Can�Υ���ƥʥѥ�᡼���򻲾Ȥ���
$  *  [CANIF132] CanIf��Can�δ֤ν�°���ϥ����ͥ졼�����󶡤���
$  */

$	DUMP()$

$ �ꥹ�Ⱥ���
$MAKE_CFG_LIST()$

$ ID������
$ID_SORT()$

$ ���顼�����å�
$ERROR_CHECK()$

$ �ץꥳ��ѥ����ѥإå�
$GEN_CANIF_CFG_H()$

$ ��󥯥�������
$GEN_CANIF_L_CFG_H()$
$GEN_CANIF_L_CFG_C()$

$ �ݥ��ȥӥ���ѥץ����
$GEN_CANIF_PB_CFG_C()$


$	TOPPERS/A-CANIF �Ǥ��б����ʤ����ͥ�������
$
$	- CAN�ȥ�󥷡���
$		<CANIF791_Conf> CanIfDispatchCfg/CanIfDispatchUserCheckTrcvWakeFlagIndicationName
$		<CANIF792_Conf> CanIfDispatchCfg/CanIfDispatchUserCheckTrcvWakeFlagIndicationUL
$		<CANIF789_Conf> CanIfDispatchCfg/CanIfDispatchUserClearTrcvWufFlagIndicationName
$		<CANIF790_Conf> CanIfDispatchCfg/CanIfDispatchUserClearTrcvWufFlagIndicationUL
$		<CANIF685_Conf> CanIfDispatchCfg/CanIfDispatchUserTrcvModeIndicationName
$		<CANIF686_Conf> CanIfDispatchCfg/CanIfDispatchUserTrcvModeIndicationUL
$		<CANIF273_Conf> CanIfTrcvDrvCfg
$		<CANIF587_Conf> CanIfTrcvDrvCfg/CanIfTrcvCfg
$		<CANIF654_Conf> CanIfTrcvDrvCfg/CanIfTrcvCfg/CanIfTrcvId
$		<CANIF606_Conf> CanIfTrcvDrvCfg/CanIfTrcvCfg/CanIfTrcvWakeupSupport
$		<CANIF605_Conf> CanIfTrcvDrvCfg/CanIfTrcvCfg/CanIfTrcvCanTrcvRef
$		[CANIF456][CANIF637_Conf]<CANIF606_Conf> CanIfCtrlWakeupSupport �����CanIfTrcvWakeupSupport ��FALSE�ξ�硤CanIfDispatchUserValidateWakeupEventUL�������Բ�
$		<CANIF655> CanIfTrcvId��0���鳫�Ϥ���
$		<CANIF695> CanIfTrcvDrvCfg����������Ƥ��ʤ���硤CanIfDispatchUserTrcvModeIndicationUL������Բ�
$	- PN
$		<CANIF819_Conf> CanIfDispatchCfg/CanIfDispatchUserConfirmPnAvailabilityName
$		<CANIF820_Conf> CanIfDispatchCfg/CanIfDispatchUserConfirmPnAvailabilityUL
$		<CANIF773_Conf> CanIfTxPduCfg/CanIfTxPduPnFilterPdu
$	- BasicCAN
$		<CANIF628_Conf> CanIfInitHohCfg/CanIfHrhCfg/CanIfHrhRangeCfg
$		<CANIF629_Conf> CanIfInitHohCfg/CanIfHrhCfg/CanIfHrhRangeCfg/CanIfHrhRangeRxPduLowerCanId
$		<CANIF630_Conf> CanIfInitHohCfg/CanIfHrhCfg/CanIfHrhRangeCfg/CanIfHrhRangeRxPduUpperCanId
$		<CANIF644_Conf> CanIfInitHohCfg/CanIfHrhCfg/CanIfHrhRangeCfg/CanIfHrhRangeRxPduRangeCanIdType
$		<CANIF743_Conf> CanIfRxPduCfg/CanIfRxPduCanIdRange
$		<CANIF745_Conf> CanIfRxPduCfg/CanIfRxPduCanIdRange/CanIfRxPduCanIdRangeLowerCanId
$		<CANIF744_Conf> CanIfRxPduCfg/CanIfRxPduCanIdRange/CanIfRxPduCanIdRangeUpperCanId
$	- ���եȥ������ե��륿���
$		<CANIF619_Conf> CanIfPrivateCfg/CanIfPrivateSoftwareFilterType
$	- BSW�������塼��
$		<CANIF669_Conf> CanIfRxPduCfg/CanIfRxPduBswSchExclAreaIdRef
$		<CANIF670_Conf> CanIfTxPduCfg/CanIfTxPduBswSchExclAreaIdRef
$	- NM
$		<CANIF741_Conf> CanIfPublicCfg/CanIfPublicWakeupCheckValidByNM
$	- ����꡼���Ǻ�������ͽ��Υѥ�᡼��
$		<CANIF633_Conf> CanIfHrhCfg/CanIfHrhCanHandleTypeRef
$		<CANIF626_Conf> CanIfHthCfg/CanIfHthCanHandleTypeRef
$	- ����¾
$		<CANIF468> CanIfHthIdSymRef��CanIfHrhIdSymRef�λ����褫���HOH���Ф���ϡ��ɥ��������ƥե��륿�򻲾Ȥ���
$		<CANIF696> <User_TrcvModeIndication>��̾����CanIfDispatchUserTrcvModeIndicationName���������
$		           ��������CanIfDispatchUserTrcvModeIndicationUL����������Ƥ��ʤ���������ԲĤȤʤ�
$		<CANIF697> CanIfDispatchUserTrcvModeIndicationUL��CAN_SM�ξ�硤CanIfDispatchUserTrcvModeIndicationName��
$		           CanSM_TransceiverModeIndication�Ǥ��ꡤuint8���δؿ��ѥ�᡼����̾����TransceiverId�Ȥ���
$		<CANIF698> CanIfDispatchUserTrcvModeIndicationUL��CDD�ξ�硤<User_TransceiverModeIndication>��̾����
$		           CanIfDispatchUserTrcvModeIndicationName����������ؿ��ѥ�᡼���η���uint8���Ȥ���
$		<CANIF794> CanIfPublicPnSupport��TRUE�ξ�硤<User_ClearTrcvWufFlagIndication>���󶡤����̥쥤��⥸�塼����������
$		<CANIF795> CanIfPublicPnSupport��TRUE�ξ�硤<User_ClearTrcvWufFlagIndication>��̾����
$		           CanIfDispatchUserClearTrcvWufFlagIndicationName��������뤳�Ȥ���ǽ�Ȥʤ�
$		<CANIF796> <User_ClearTrcvWufFlagIndication>��CanIfPublicPnSupport������ˤ�ä�ON/OFF�Ǥ���
$		<CANIF797> CanIfDispatchUserClearTrcvWufFlagIndicationUL��CAN_SM�ξ�硤CanIfDispatchUserClearTrcvWufFlagIndicationName��
$		           CanSM_ClearTrcvWufFlagIndication�Ǥ��ꡤuint8���δؿ��ѥ�᡼����̾����TransceiverId�Ȥ���
$		<CANIF798> CanIfDispatchUserClearTrcvWufFlagIndicationUL��CDD�ξ�硤<User_ClearTrcvWufFlagIndication>��̾����
$		           CanIfDispatchUserClearTrcvWufFlagIndicationName��������졤�ؿ��ѥ�᡼����uint8���Ȥ���
$		<CANIF800> CanIfPublicPnSupport��TRUE�ξ�硤CanIfDispatchUserCheckTrcvWakeFlagIndicationUL�λ��꤬��ǽ�Ȥʤ�
$		<CANIF801> <User_CheckTrcvWakeFlagIndication>��̾����CanIfDispatchUserCheckTrcvWakeFlagIndicationName���������
$		<CANIF802> <User_CheckTrcvWakeFlagIndication>��CanIfPublicPnSupport������ˤ�ä�ON/OFF�Ǥ���
$		<CANIF803> CanIfDispatchUserCheckTrcvWakeFlagIndicationUL��CAN_SM�ξ�硤CanIfDispatchUserCheckTrcvWakeFlagIndicationName��
$		           CanSM_CheckTrcvWakeFlagIndication�Ǥ��ꡤuint8���δؿ��ѥ�᡼����̾����TransceiverId�Ȥ���
$		<CANIF804> CanIfDispatchUserCheckTrcvWakeFlagIndicationUL��CDD�ξ�硤<User_CheckTrcvWakeFlagIndication>��̾����
$		           CanIfDispatchUserCheckTrcvWakeFlagIndicationName�ǻ��ꤵ�졤�ؿ��ѥ�᡼���η���uint8�Ȥ���
$		<CANIF823> <User_ConfirmPnAvailability>�����Τ����̥쥤���CanIfDispatchUserConfirmPnAvailabilityUL���������
$		<CANIF824> <Uset_ConfirmPnAvailability>��̾����CanIfDispatchUserConfirmPnAvailabilityName���������
$		<CANIF825> <Uset_ConfirmPnAvailability>��CANIF_PUBLIC_PN_SUPPORT������ˤ�ä�ON/OFF�Ǥ���
$		<CANIF826> CanIfDispatchUserConfirmPnAvailabilityUL��CAN_SM�ξ�硤CanIfDispatchUserConfirmPnAvailabilityName��
$		           CanSM_ConfirmPnAvailability�Ǥ��ꡤuint8���δؿ��ѥ�᡼����̾����TransceiverId�Ȥ���
$		<CANIF280> �ʲ��Υإå��ե�����򥤥󥯥롼�ɤ���
$		           ��Can_<vendorID>_<Vendor specific name><driver abbreviation>_Cfg.h
$		           ��CanTrcv_<Vendor Id>_<Vendor specific name><driver abbreviation>_Cfg.h
$		           ��PduR_Cfg.h
$		           ��CanNm_Cfg.h
$		           ��CanTp_Cfg.h
$		           ��Xcp_Cfg.h
$		<CANIF375> �󶡤���Ƥ��뵡ǽ��¹Ԥ��뤿��ˡ������ɥե����륹�ȥ饯����ˤ�CanIf_<X>.c ���ޤޤ졤
$		           ��ĥ��ǽ<X>�ϡ�ʣ����C-�ե��������Ѥ�����Υ��ץ����Ǥ���
$		<CANIF376> ����ѥ������˥���ե�����졼������ǽ�ʥѥ�᡼���Ѥ�CanIf_Cfg.c��ޤ�
