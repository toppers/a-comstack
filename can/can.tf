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
$  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
$  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
$  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
$  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
$      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
$      スコード中に含まれていること．
$  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
$      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
$      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
$      の無保証規定を掲載すること．
$  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
$      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
$      と．
$    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
$        作権表示，この利用条件および下記の無保証規定を掲載すること．
$    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
$        報告すること．
$  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
$      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
$      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
$      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
$      免責すること．
$
$  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
$  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
$  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
$  用する者に対して，AUTOSARパートナーになることを求めている．
$
$  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
$  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
$  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
$  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
$  の責任を負わない．
$
$  $Id: can.tf 13 2015-07-15 08:58:53Z fujisft-kaitori $
$

$ ====================================================================
$ boolean判定関数
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
$  コンフィグセットごとのリストを作成
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

$		// コントローラ数のエラー確認
		$IF (CanConfigSet.ctrl_id_num[config_id] > TARGET_TMAX_CONTROLLER_NUM)$
			$ERROR$$FORMAT(_("There is too much CanController(%1% > %2%) of CanConfigSet(%3%)."),
								CanConfigSet.ctrl_id_num[config_id], TARGET_TMAX_CONTROLLER_NUM, config_id)$$END$
			$DIE()$
		$END$

$		// コントローラ数の最大値比較
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

$		// メールボックス最大数チェック
		$IF ISFUNCTION("CHECK_MAILBOX_NUM")$
			$ret = 1$
$			// (CAN022)(CAN024) CANコントローラ依存のチェック
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

$		// CanFilterMask最大数チェック
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
$		// CanConfigSetごとのHOHリスト
		$new_list = {}$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$new_list = APPEND(new_list, CanController.hoh_list[ctrl_id])$
		$END$
		
		$CanConfigSet.hoh_list[config_id] = new_list$
		$CanConfigSet.hoh_num[config_id] = LENGTH(new_list)$
	$END$
$END$


$ ====================================================================
$  ID連番ソート関数
$ ====================================================================
$FUNCTION ID_SORT$
$	// [CAN316_Conf] CanControllerId 順にソート
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
$			// CanControllerIdが0からの連番でない場合はエラー
			$IF find == 0$
				$ERROR$$FORMAT(_("CanControllerId(%1%\) is not found. CanControllerId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("CanControllerId(%1%\) is duplicated. CanControllerId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanConfigSet.ctrl_id_list[config_id] = new_list$
	$END$

$	// [CAN326_Conf] HOHリストを CanObjectId 順にソート
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
$			// CanObjectIdが0からの連番でない場合はエラー
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
$		// HRHリストを受信ボックス番号順にソート
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanController.hrh_list[ctrl_id]) - 1)$
			$find = 0$
			$FOREACH hrh_id CanController.hrh_list[ctrl_id]$
				$IF CanHardwareObject.box_idx[hrh_id] == index$
					$new_list = APPEND(new_list, hrh_id)$
					$find = find + 1$
				$END$
			$END$
$			// box_idxが0からの連番でない場合はエラー
			$IF find == 0$
				$ERROR$$FORMAT(_("box_idx(%1%\) is not found. box_idx should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("box_idx(%1%\) is duplicated. box_idx should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanController.hrh_list[ctrl_id] = new_list$
		
$		// HTHリストを送信ボックス番号順にソート
$		// [CAN100] HTHの構成
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanController.hth_list[ctrl_id]) - 1)$
			$find = 0$
			$FOREACH hth_id CanController.hth_list[ctrl_id]$
				$IF CanHardwareObject.box_idx[hth_id] == index$
					$new_list = APPEND(new_list, hth_id)$
					$find = find + 1$
				$END$
			$END$
$			// box_idxが0からの連番でない場合はエラー
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
$  [CAN023] エラーチェック関数
$ ====================================================================
$FUNCTION ERROR_CHECK$
$	// ショートネームの重複チェック
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
$		// CanIf側のコントローラID保持
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
$		// サポートしているボーレートを確認
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
$				// CanControllerDefaultBaudrateが同じCanController内から指定しているか確認
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
$		// FullCANのみサポート
		$IF !EQ(CanHardwareObject.CanHandleType[hoh_id], "FULL")$
			$ERROR$$FORMAT(_("CanHandleType should be set to `FULL'. (%1%\)"), hoh_id)$$END$$DIE()$
		$END$
$		// [CAN065_Conf] CanIdType
$		// STANDARDのみサポート
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
$			// CanFilterMaskRefの参照先のCanFilterMaskは，CanControllerRefが参照するコントローラと同じ
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
$		// falseのみサポート
		$IF IS_TRUE(CanGeneral.CanMultiplexedTransmission[general_id])$
			$ERROR$$FORMAT(_("CanIndex should be `FALSE'. (%1%\)"), general_id)$$END$$DIE()$
		$END$
$		// [CAN106_Conf] CanVersionInfoApi
		$ret = IS_TRUE(CanGeneral.CanVersionInfoApi[general_id])$
	$END$
$END$

$ ====================================================================
$  [CAN220][CAN389] プリコンパイル用ヘッダ生成関数
$ ====================================================================
$FUNCTION GEN_CAN_CFG_H$
$	// [CAN047] human readableな内容
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

$	// CanControllerごとのMainFunction API有効/無効を確認
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

$	// CanLPduReceiveCalloutFunction設定確認
	$IF LENGTH(CanGeneral.CanLPduReceiveCalloutFunction[1])$
		#define USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION$NL$
	$END$
	$NL$

$	// MainFunction用定義
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
$	// [NCAN001] 多重度0..1とし，唯一の値のみ出力
	$IF LENGTH(CanMainFunctionRWPeriods.CanMainFunctionReadPeriod[1])$
		#define CAN_MAIN_FUNCTION_READ_PERIOD$TAB$($CanMainFunctionRWPeriods.CanMainFunctionReadPeriod[1]$)$NL$
	$END$
$	// [CAN358_Conf] CanMainFunctionWritePeriod
$	// [NCAN002] 多重度0..1とし，唯一の値のみ出力
	$IF LENGTH(CanMainFunctionRWPeriods.CanMainFunctionWritePeriod[1])$
		#define CAN_MAIN_FUNCTION_WRITE_PERIOD$TAB$($CanMainFunctionRWPeriods.CanMainFunctionWritePeriod[1]$)$NL$
	$END$
	$NL$

	#endif /* TOPPERS_CAN_CFG_H */
$END$

$ ====================================================================
$  [CAN078][CAN221] ポストビルド用実体生成関数
$ ====================================================================
$FUNCTION GEN_CAN_PB_CFG_C$
$ 	// ビルド後にコンフィギュレーション可能なパラメータ用
	$FILE "Can_PBcfg.c"$
	/* Can_PBcfg.c */$NL$

	#include "Can.h"$NL$
	$NL$

	/* サポートボーレート配列 : baudrate_<CanConfigSet>_<CanController> */$NL$
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
	/* フィルタマスク値配列 : filtermask_<CanConfigSet>_<CanController> */$NL$
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

	/* 受信ボックス番号→HRH変換テーブル : rbox_hrh_table_<CanConfigSet>_<CanController> */$NL$
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

	/* 受信ボックスCAN-IDテーブル : rbox_canid_table_<CanConfigSet>_<CanController> */$NL$
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

	/* HTH管理ブロック配列 : can_hth_cb_table_<CanConfigSet>_<CanController> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			$IF (CanController.hth_num[ctrl_id] != 0)$
				static CAN_HTH_CB can_hth_cb_table_$config_id$_$ctrl_id$[$CanController.hth_num[ctrl_id]$];$NL$
				$NL$
			$END$
		$END$
	$END$

	/* Canコントローラ管理ブロック配列 : can_ctrl_inib_table_<CanConfigSet> */$NL$
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

	/* HOH→ボックス番号変換テーブル : hoh_box_table_<CanConfigSet> */$NL$
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
$	// [CAN021][CAN291] コントローラのコンフィギュレーションを含む'Config'の情報
$	// [NCAN004] ポストビルド対応のためcan_configの多重度は1..*
	/* Canコンフィギュレーション情報 */$NL$
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

	/* 割込み禁止ネストカウント */$NL$
	uint8 can_interrupt_nested_cnt[$ctrl_id_num_max$];$NL$
	$NL$

	/* Can_SetControllerMode動作状態フラグ */$NL$
	boolean can_set_controller_mode_flg[$ctrl_id_num_max$];$NL$
	$NL$

	/* CANコントローラ状態情報 */$NL$
	Can_StateTransitionType can_current_state[$ctrl_id_num_max$];$NL$
	$NL$

$	// [CAN434_Conf] CanLPduReceiveCalloutFunction
	$IF LENGTH(CanGeneral.CanLPduReceiveCalloutFunction[1])$
		/* コールアウト関数 */$NL$
		extern boolean $CanGeneral.CanLPduReceiveCalloutFunction[1]$(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);$NL$
		const Can_LpduCallout CanLpduCalloutFunction = $CanGeneral.CanLPduReceiveCalloutFunction[1]$;$NL$
	$END$
	$NL$
$END$


$ ====================================================================
$  メイン処理
$ ====================================================================

$	DUMP()$

$ リスト作成
$MAKE_CFG_LIST()$

$ IDソート
$ID_SORT()$

$ エラーチェック
$ERROR_CHECK()$

$ ターゲット依存部チェック
$IF ISFUNCTION("TARGET_CHECK")$
	$TARGET_CHECK()$
$END$

$ プリコンパイル用
$GEN_CAN_CFG_H()$

$ ポストビルド用
$GEN_CAN_PB_CFG_C()$


$	TOPPERS/A-CAN では対応しない仕様タグ一覧
$
$	- 送信キャンセル
$		<CAN069_Conf> CanGeneral/CanHardwareCancellation
$		<CAN378_Conf> CanGeneral/CanIdenticalIdCancellation
$	- TTCAN
$		<CAN430_Conf> CanGeneral/CanSupportTTCANRef
$	- CANコントローラ
$		<CAN315_Conf> CANコントローラの無効指定は未サポート
$		<CAN382_Conf> CANコントローラのベースアドレス指定は未サポート
$	- その他
$		<CAN313_Conf> Mcuモジュールからの参照は未サポート
$		<CAN438_Conf> CanHardwareObject毎のPeriod指定は未サポート
