$
$  TOPPERS/A-CANIF
$      AuTomotive CANIF
$
$  Copyright (C) 2013-2016 by Center for Embedded Computing Systems
$                             Graduate School of Information Science, Nagoya Univ., JAPAN
$  Copyright (C) 2014-2016 by AISIN COMCRUISE Co., Ltd., JAPAN
$  Copyright (C) 2015-2016 by eSOL Co.,Ltd., JAPAN
$  Copyright (C) 2013-2016 by FUJI SOFT INCORPORATED, JAPAN
$  Copyright (C) 2014-2016 by NEC Communication Systems, Ltd., JAPAN
$  Copyright (C) 2013-2016 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
$  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
$  Copyright (C) 2014-2016 by SCSK Corporation, JAPAN
$  Copyright (C) 2013-2016 by Sunny Giken Inc., JAPAN
$  Copyright (C) 2015-2016 by SUZUKI MOTOR CORPORATION
$  Copyright (C) 2013-2016 by TOSHIBA CORPORATION, JAPAN
$  Copyright (C) 2013-2016 by Witz Corporation
$
$  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
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
$  $Id: canif.tf 3189 2016-03-22 09:49:19Z aisincom-ishikawa $
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
$  ID連番ソート関数
$ ====================================================================
$FUNCTION ID_SORT$
$	// [CANIF647_Conf] CanIfCtrlId 順にソート
$	// [CANIF653] CanIfCtrlIdは0から開始する
$	// [NCANIF003] CanIfCtrlIdは0からの連番とする
$	// [NCANIF017] CanIfCtrlDrvCfgの多重度は1であるため，PARENTチェック不要
	$new_list = {}$
	$FOREACH index RANGE(0, LENGTH(CanIfCtrlCfg.ID_LIST) - 1)$
		$find = 0$
		$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
			$IF CanIfCtrlCfg.CanIfCtrlId[ctrl_id] == index$
				$new_list = APPEND(new_list, ctrl_id)$
				$find = find + 1$
			$END$
		$END$
$		// CanIfCtrlIdが0からの連番でない場合はエラー
		$IF find == 0$
			$ERROR$$FORMAT(_("CanIfCtrlId(%1%\) is not found. CanIfCtrlId should be sequential from 0."), index)$$END$$DIE()$
		$END$
		$IF find > 1$
			$ERROR$$FORMAT(_("CanIfCtrlId(%1%\) is duplicated. CanIfCtrlId should be unique."), index)$$END$$DIE()$
		$END$
	$END$
	$CanIfCtrlCfg.ID_LIST = new_list$

$	// CanIfTxPduId CanIfRxPduId 順にソート
$	// [NCANIF003] CanIfTxPduIdとCanIfRxPduIdは共通番号領域で管理し，0からの連番とする
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

$	// CanObjectId 順にソート
$	// [CANIF115] HTHとHRHは共通番号領域で管理し，0からの連番とする
$	// [CANIF467] HTHとHRHの順番を構成し，保存する
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$FOREACH tx_pdu_id CanIfInitCfg.tx_pdu_list[init_id]$
$			// [CANIF833_Conf] CanIfBufferHthRef
$			// [CANIF831_Conf] CanIfTxPduBufferRef
$			// [CANIF466] 送信LPDUは1つのCanTxPduBufferが静的に割り当てられる
			$CanIfTxPduCfg.hth_id_ref[tx_pdu_id] = CanIfBufferCfg.CanIfBufferHthRef[CanIfTxPduCfg.CanIfTxPduBufferRef[tx_pdu_id]]$
$			// [CANIF625_Conf] CanIfHthCanCtrlIdRef
			$FOREACH hth_id_ref CanIfTxPduCfg.hth_id_ref[tx_pdu_id]$
$				// [CANIF046] LPDUは複数のCANコントローラに属してはいけない
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
					$IF LENGTH(PduRDestPdu.PduRDestPduHandleId[dest_pdu_id])$
						$CanIfTxPduCfg.pdu_handle_id[tx_pdu_id] = PduRDestPdu.PduRDestPduHandleId[dest_pdu_id]$
					$ELSE$
						$ERROR$$FORMAT(_("PduRDestPduHandleId(%1%\) is not found."), dest_pdu_id)$$END$$DIE()$	
					$END$
				$END$
			$END$
			$IF !LENGTH(CanIfTxPduCfg.pdu_handle_id[tx_pdu_id])$
				$ERROR$$FORMAT(_("CanIfTxPduCfg.CanIfTxPduRef(%1%\) cannot be found in PduRConfiguration."), tx_pdu_id)$$END$$DIE()$	
			$END$
		$END$
		$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
$			// [CANIF631_Conf] CanIfHrhCanCtrlIdRef
$			// [CANIF602_Conf] CanIfRxPduHrhIdRef
$			// [CANIF465] CanIfRxPduIdは1つ以上のHRHに割り当てることができるため，単一のCAN-IDを複数のHRHに割り当てることができる
			$FOREACH hrh_id_ref CanIfRxPduCfg.CanIfRxPduHrhIdRef[rx_pdu_id]$
$				// [CANIF046] LPDUは複数のCANコントローラに属してはいけない
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
$  [CANIF131] エラーチェック関数
$ ====================================================================
$FUNCTION ERROR_CHECK$
$ [CANIF131] CanIf仕様に沿った設定値チェックを実施

$ [CANIF244_Conf] CanIf
$	/*
$	 *  [CANIF246_Conf] CanIfPublicCfg
$	 */
$	// [CANIF522_Conf] CanIfPublicCancelTransmitSupport
	$ret = IS_TRUE(CanIfPublicCfg.CanIfPublicCancelTransmitSupport[1])$

$	// [CANIF671_Conf] CanIfPublicCddHeaderFile
$	// チェック事項なし

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
$		// [NCANIF010] 単一のCANドライバのみサポート
		$ERROR$$FORMAT(_("CanIfPublicMultipleDrvSupport(%1%\) should be `FALSE'."), CanIfPublicCfg.CanIfPublicMultipleDrvSupport[1])$$END$$DIE()$
	$END$

$	// [CANIF615_Conf] CanIfPublicNumberOfCanHwUnits 
	$IF (CanIfPublicCfg.CanIfPublicNumberOfCanHwUnits[1] != 1)$
$		// [NCANIF011] 単一のCANドライバのみサポート
		$ERROR$$FORMAT(_("CanIfPublicNumberOfCanHwUnits(%1%\) should be `1'."), CanIfPublicCfg.CanIfPublicNumberOfCanHwUnits[1])$$END$$DIE()$
	$END$

$	// [CANIF772_Conf] CanIfPublicPnSupport
	$IF IS_TRUE(CanIfPublicCfg.CanIfPublicPnSupport[1])$
$		// [NCANIF012] PN非サポート
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
$		// [NCANIF013] 動的CAN-ID設定は非サポート
		$ERROR$$FORMAT(_("CanIfPublicSetDynamicTxIdApi(%1%\) should be `FALSE'."), CanIfPublicCfg.CanIfPublicSetDynamicTxIdApi[1])$$END$$DIE()$
	$END$

$	// [CANIF618_Conf] CanIfPublicTxBuffering
	$IF IS_TRUE(CanIfPublicCfg.CanIfPublicTxBuffering[1])$
$		// [NCANIF014] 送信バッファリング非サポート
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
$		// [NCANIF009] TTCAN非サポート
		$ERROR$$FORMAT(_("CanIfSupportTTCAN(%1%\) should be `FALSE'."), CanIfPrivateCfg.CanIfSupportTTCAN[1])$$END$$DIE()$
	$END$


$	/*
$	 *  [CANIF250_Conf] CanIfDispatchCfg
$	 */
$	// [CANIF547_Conf] CanIfDispatchUserCtrlBusOffUL
$	// [CANIF525_Conf] CanIfDispatchUserCtrlBusOffName
$	// [CANIF450] <User_ControllerBusOff>を提供する上位レイヤモジュールはCanIfDispatchUserCtrlBusOffULで指定される
	$IF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffUL[1], "CAN_SM")$
$		// [CANIF450][CANIF559] CanIfDispatchUserCtrlBusOffULが`CAN_SM'の場合，CanIfDispatchUserCtrlBusOffNameは`CanSM_ControllerBusOff'
		$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1])$
			$IF !EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1], "CanSM_ControllerBusOff")$
				$ERROR$$FORMAT(_("CanIfDispatchUserCtrlBusOffName(%1%\) should be `CanSM_ControllerBusOff'. CanIfDispatchUserCtrlBusOffUL is `CAN_SM'"), CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1])$$END$$DIE()$
			$END$
		$ELSE$
			$CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1] = "CanSM_ControllerBusOff"$
		$END$
	$ELIF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffUL[1], "CDD")$
$		// [CANIF450][CANIF560] CanIfDispatchUserCtrlBusOffULが`CDD'の場合，CanIfDispatchUserCtrlBusOffNameの指定は必須
		$IF !LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffName[1])$
			$ERROR$$FORMAT(_("CanIfDispatchUserCtrlBusOffName should be set value. CanIfDispatchUserCtrlBusOffUL is `CDD'"))$$END$$DIE()$
		$END$
	$ELSE$
		$ERROR$$FORMAT(_("CanIfDispatchUserCtrlBusOffUL(%1%\) should be `CAN_SM' or `CDD'."), CanIfDispatchCfg.CanIfDispatchUserCtrlBusOffUL[1])$$END$$DIE()$
	$END$

$	// [CANIF684_Conf] CanIfDispatchUserCtrlModeIndicationUL
$	// [CANIF683_Conf] CanIfDispatchUserCtrlModeIndicationName
$	// [CANIF689] <User_ControllerModeIndication>を提供する上位レイヤモジュールはCanIfDispatchUserCtrlModeIndicationULで指定される
	$IF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationUL[1], "CAN_SM")$
$		// [CANIF690][CANIF691] CanIfDispatchUserCtrlModeIndicationULが`CAN_SM'の場合，CanIfDispatchUserCtrlModeIndicationNameは`CanSM_ControllerModeIndication'
		$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1])$
			$IF !EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1], "CanSM_ControllerModeIndication")$
				$ERROR$$FORMAT(_("CanIfDispatchUserCtrlModeIndicationName(%1%\) should be `CanSM_ControllerModeIndication'. CanIfDispatchUserCtrlModeIndicationUL is `CAN_SM'"), CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1])$$END$$DIE()$
			$END$
		$ELSE$
			$CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1] = "CanSM_ControllerModeIndication"$
		$END$
	$ELIF EQ(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationUL[1], "CDD")$
$		// [CANIF690][CANIF692] CanIfDispatchUserCtrlModeIndicationULが`CDD'の場合，CanIfDispatchUserCtrlModeIndicationNameの指定は必須
		$IF !LENGTH(CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationName[1])$
			$ERROR$$FORMAT(_("CanIfDispatchUserCtrlModeIndicationName should be set value. CanIfDispatchUserCtrlModeIndicationUL is `CDD'"))$$END$$DIE()$
		$END$
	$ELSE$
		$ERROR$$FORMAT(_("CanIfDispatchUserCtrlModeIndicationUL(%1%\) should be `CAN_SM' or `CDD'."), CanIfDispatchCfg.CanIfDispatchUserCtrlModeIndicationUL[1])$$END$$DIE()$
	$END$

$	// [CANIF549_Conf] CanIfDispatchUserValidateWakeupEventUL
$	// [CANIF531_Conf] CanIfDispatchUserValidateWakeupEventName
	$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1])$
$		// [CANIF456][CANIF637_Conf] CanIfCtrlWakeupSupportがFALSEの場合，CanIfDispatchUserValidateWakeupEventULは設定不可
		$wakeup_support_flg = "FALSE"$
		$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
			$IF IS_TRUE(CanIfCtrlCfg.CanIfCtrlWakeupSupport[ctrl_id])$
				$wakeup_support_flg = "TRUE"$
			$END$
		$END$
		$IF EQ(wakeup_support_flg, "FALSE")$
			$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventUL should not be set value. All of CanIfCtrlWakeupSupport is FALSE."))$$END$$DIE()$
		$END$

$		// [CANIF456] <User_ValidateWakeupEvent>を提供する上位レイヤモジュールはCanIfDispatchUserValidateWakeupEventULで指定される
		$IF EQ(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1], "ECUM")$
$			// [CANIF563] CanIfDispatchUserValidateWakeupEventULが`ECUM'の場合，CanIfDispatchUserValidateWakeupEventNameは`EcuM_ValidateWakeupEvent'
			$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$
				$IF !EQ(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1], "EcuM_ValidateWakeupEvent")$
					$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventName(%1%\) should be `EcuM_ValidateWakeupEvent'. CanIfDispatchUserValidateWakeupEventUL is `ECUM'"), CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$$END$$DIE()$
				$END$
			$ELSE$
				$CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1] = "EcuM_ValidateWakeupEvent"$
			$END$
		$ELIF EQ(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1], "CDD")$
$			// [CANIF564] CanIfDispatchUserValidateWakeupEventULが`CDD'の場合，CanIfDispatchUserValidateWakeupEventNameの指定は必須
			$IF !LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$
				$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventName should be set value. CanIfDispatchUserValidateWakeupEventUL is `CDD'"))$$END$$DIE()$
			$END$
		$ELSE$
			$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventUL(%1%\) should be `ECUM' or `CDD'."), CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventUL[1])$$END$$DIE()$
		$END$
	$ELSE$
		$IF LENGTH(CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1])$
$			// CanIfDispatchUserValidateWakeupEventULが省略され，かつ，CanIfDispatchUserValidateWakeupEventNameに値が設定されている場合は警告
			$ERROR$$FORMAT(_("CanIfDispatchUserValidateWakeupEventUL would be set value."))$$END$$DIE()$
		$ELSE$
$			// CanIfDispatchUserValidateWakeupEventULが省略され，かつ，CanIfDispatchUserValidateWakeupEventNameが省略された場合はNULL_PTRを補完
			$CanIfDispatchCfg.CanIfDispatchUserValidateWakeupEventName[1] = "NULL_PTR"$
		$END$
	$END$


$	/*
$	 *  [CANIF253_Conf] CanIfCtrlDrvCfg
$	 *  [NCANIF015] CanIfCtrlDrvCfgの多重度は1
$	 */
$	// [CANIF640_Conf] CanIfCtrlDrvTxCancellation
	$IF IS_TRUE(CanIfCtrlDrvCfg.CanIfCtrlDrvTxCancellation[1])$
$		// [NCANIF004] 送信キャンセル通知は非サポート
		$ERROR$$FORMAT(_("CanIfCtrlDrvTxCancellation(%1%\) should be `FALSE'."), CanIfCtrlDrvCfg.CanIfCtrlDrvTxCancellation[1])$$END$$DIE()$
	$END$

$	// [CANIF642_Conf] CanIfCtrlDrvInitHohConfigRef
$	// 指定した参照先の妥当性は事前に確認済み


$	// [CANIF638_Conf] CanIfCtrlDrvNameRef
$	// 指定した参照先の妥当性は事前に確認済み



$	/*
$	 *  [CANIF546_Conf] CanIfCtrlCfg
$	 */
	$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
$	// [CANIF647_Conf] CanIfCtrlId
		$IF (CanIfCtrlCfg.CanIfCtrlId[ctrl_id] > 65535)$
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
$	 *  [NCANIF001] CanIfInitCfgの多重度は1..*
$	 */
$	// [CANIF623_Conf] CanIfInitCfgSet
$	// ToDo: 設定された文字列が32文字以下かどうかをチェック


$	/*
$	 *  [CANIF832_Conf] CanIfBufferCfg
$	 */
$	// [CANIF834_Conf] CanIfBufferSize
	$FOREACH buffer_id CanIfBufferCfg.ID_LIST$
$		// [NCANIF005] 送信バッファリング非サポート
		$IF CanIfBufferCfg.CanIfBufferSize[buffer_id] != 0$
			$ERROR$$FORMAT(_("CanIfBufferSize(%1%\) should be `0'."), CanIfBufferCfg.CanIfBufferSize[buffer_id])$$END$$DIE()$
		$END$

$		// [CANIF833_Conf] CanIfBufferHthRef
$		// 指定した参照先の妥当性は事前に確認済み
	$END$


$	/*
$	 *  [CANIF257_Conf] CanIfInitHohCfg
$	 *  [CANIF662] 2種類のHOH(HTH/HRH)を使用してCANドライバへアクセス
$	 */
$	// [CANIF620_Conf] CanIfInitRefCfgSet
$	// 指定した参照先の妥当性は事前に確認済み


$	/*
$	 *  [CANIF258_Conf] CanIfHthCfg
$	 *  [CANIF666] HTHは，BasicCANまたはFullCANの通信方法を使用して送信できるようにする
$	 *  [CANIF292] HTHはCANコントローラメールボックスの論理ハードウェア送信オブジェクトを参照するハンドル
$	 */
	$FOREACH hth_id CanIfHthCfg.ID_LIST$
$		// [CANIF667] 複数のHTHを使用する場合，各HTHは1つの送信LPDUに属する必要がある
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
$		// 指定した参照先の妥当性は事前に確認済み

$		// [CANIF627_Conf] CanIfHthIdSymRef
$		// 指定した参照先の妥当性は事前に確認済み
	$END$


$	/*
$	 *  [CANIF259_Conf] CanIfHrhCfg
$	 *  [CANIF665] HRHは，BasicCANまたはFullCANの通信方法を使用して受信できるようにする
$	 *  [CANIF291] HRHはCANコントローラメールボックスの論理ハードウェア受信オブジェクトを参照するハンドル
$	 */
	$FOREACH hrh_id CanIfHrhCfg.ID_LIST$
$		// [CANIF664] 複数のHRHが使用される場合，各HRHは少なくとも1つの受信LPDUに属する必要がある
		$FOREACH rx_pdu_id CanIfRxPduCfg.ID_LIST$
			$IF EQ(hrh_id, CanIfRxPduCfg.CanIfRxPduHrhIdRef[rx_pdu_id])$
				$CanIfHrhCfg.rx_pdu_id_ref[hrh_id] = rx_pdu_id$
			$END$
		$END$
		$IF !LENGTH(CanIfHrhCfg.rx_pdu_id_ref[hrh_id])$
			$ERROR$$FORMAT(_("%1%\ should belong to at least to a single or fixed group of Rx LPDU."), hrh_id)$$END$$DIE()$
		$END$

$		[CANIF632_Conf] CanIfHrhSoftwareFilter
		$IF IS_TRUE(CanIfHrhCfg.CanIfHrhSoftwareFilter[hrh_id])$
$			// [NCANIF006] ソフトウェアフィルタリングは非サポート
			$ERROR$$FORMAT(_("CanIfHrhSoftwareFilter(%1%\) should be `FALSE'."), CanIfHrhCfg.CanIfHrhSoftwareFilter[hrh_id])$$END$$DIE()$
		$END$

$		// [CANIF631_Conf] CanIfHrhCanCtrlIdRef
$		// 指定した参照先の妥当性は事前に確認済み

$		// [CANIF634_Conf] CanIfHrhIdSymRef 
$		// 指定した参照先の妥当性は事前に確認済み
	$END$


$	/*
$	 *  [CANIF248_Conf] CanIfTxPduCfg
$	 */
	$FOREACH tx_pdu_id CanIfTxPduCfg.ID_LIST$
$		// [CANIF590_Conf] CanIfTxPduCanIdType
$		// [CANIF243] Can_Write()を呼び出す前にCAN-IDのタイプを設定する
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
$		// [NCANIF015] グローバルPDUの長さよりDLCが短い場合，エラー
		$IF CanIfTxPduCfg.CanIfTxPduDlc[tx_pdu_id] < CanIfTxPduCfg.pdu_length[tx_pdu_id]$
			$ERROR$$FORMAT(_("CanIfTxPduDlc(%1%\) should be equal or larger than PduLength(%2%\). [%3%\]"), CanIfTxPduCfg.CanIfTxPduDlc[tx_pdu_id], CanIfTxPduCfg.pdu_length[tx_pdu_id], tx_pdu_id)$$END$$DIE()$
		$END$

$		// [CANIF591_Conf] CanIfTxPduId
		$IF (CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id] < 0) || (CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id] > 4294967295)$
			$ERROR$$FORMAT(_("CanIfTxPduId(%1%\) should be in the range from 0 to 4294967295."), CanIfTxPduCfg.CanIfTxPduId[tx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF589_Conf] CanIfTxPduReadNotifyStatus
		$IF IS_TRUE(CanIfTxPduCfg.CanIfTxPduReadNotifyStatus[tx_pdu_id]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicReadTxPduNotifyStatusApi[1])$
			$ERROR$$FORMAT(_("CanIfTxPduReadNotifyStatus(%1%\) should not be set TRUE. CanIfPublicReadTxPduNotifyStatusApi is FALSE."), CanIfTxPduCfg.CanIfTxPduReadNotifyStatus[tx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF593_Conf] CanIfTxPduType
$		// [NCANIF016] 動的CAN-ID設定は非サポート
		$IF !EQ(CanIfTxPduCfg.CanIfTxPduType[tx_pdu_id], "STATIC")$
			$ERROR$$FORMAT(_("CanIfTxPduType(%1%\) should be `STATIC'."), CanIfTxPduCfg.CanIfTxPduType[tx_pdu_id])$$END$$DIE()$
		$END$
		
$		// [CANIF527_Conf] CanIfTxPduUserTxConfirmationUL
$		// [CANIF528_Conf] CanIfTxPduUserTxConfirmationName
$		// [CANIF438] <User_TxConfirmation>を提供する上位レイヤモジュールはCanIfTxPduUserTxConfirmationULで指定される
$		// [CANIF542] <User_TxConfirmation>()の名前はCanIfTxPduUserTxConfirmationNameに定義する
		$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id])$
			$IF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "CAN_NM")$
$				// [CANIF543] CanIfTxPduUserTxConfirmationULがCAN_NMの場合，CanIfTxPduUserTxConfirmationNameはCanNm_TxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "CanNm_TxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `CanNm_TxConfirmation'. CanIfTxPduUserTxConfirmationUL is `CAN_NM'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "CanNm_TxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "CAN_TP")$
$				// [CANIF550] CanIfTxPduUserTxConfirmationULがCAN_TPの場合，CanIfTxPduUserTxConfirmationNameはCanTp_TxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "CanTp_TxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `CanTp_TxConfirmation'. CanIfTxPduUserTxConfirmationUL is `CAN_TP'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "CanTp_TxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "CDD")$
$				// [CANIF551] CanIfTxPduUserTxConfirmationULがCDDの場合，<User_TxConfirmation>の名前はCanIfTxPduUserTxConfirmationNameで指定される
				$IF !LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be set value. CanIfTxPduUserTxConfirmationUL is `CDD'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "J1939TP")$
$				// [CANIF544] CanIfTxPduUserTxConfirmationULがJ1939TPの場合，CanIfTxPduUserTxConfirmationNameはJ1939Tp_TxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "J1939Tp_TxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `J1939Tp_TxConfirmation'. CanIfTxPduUserTxConfirmationUL is `J1939TP'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "J1939Tp_TxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "PDUR")$
$				// [CANIF439] CanIfTxPduUserTxConfirmationULがPDURの場合，CanIfTxPduUserTxConfirmationNameはPduR_CanIfTxConfirmation
				$IF LENGTH(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id])$
					$IF !EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id], "PduR_CanIfTxConfirmation")$
						$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationName should be `PduR_CanIfTxConfirmation'. CanIfTxPduUserTxConfirmationUL is `PDUR'. (%1%\)"), tx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "PduR_CanIfTxConfirmation"$
				$END$
			$ELIF EQ(CanIfTxPduCfg.CanIfTxPduUserTxConfirmationUL[tx_pdu_id], "XCP")$
$				// [CANIF556] CanIfTxPduUserTxConfirmationULがXCPの場合，CanIfTxPduUserTxConfirmationNameはXcp_CanIfTxConfirmation
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
$				// CanIfTxPduUserTxConfirmationULが省略され，CanIfTxPduUserTxConfirmationNameに値が設定されている場合，エラー
				$ERROR$$FORMAT(_("CanIfTxPduUserTxConfirmationUL should be set value. (%1%\)"), tx_pdu_id)$$END$$DIE()$
			$ELSE$
$				// CanIfTxPduUserTxConfirmationULが省略され，かつ，CanIfTxPduUserTxConfirmationNameが省略された場合，NULL_PTRで補完
				$CanIfTxPduCfg.CanIfTxPduUserTxConfirmationName[tx_pdu_id] = "NULL_PTR"$
			$END$
		$END$

$		// [CANIF831_Conf] CanIfTxPduBufferRef
$		// 指定した参照先の妥当性は事前に確認済み

$		// [CANIF603_Conf] CanIfTxPduRef
$		// 指定した参照先の妥当性は事前に確認済み
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
			$ERROR$$FORMAT(_("CanIfRxPduReadNotifyStatus(%1%\) should not be set TRUE. CanIfPublicReadRxPduNotifyStatusApi is FALSE."), CanIfRxPduCfg.CanIfRxPduReadNotifyStatus[rx_pdu_id])$$END$$DIE()$
		$END$

$		// [CANIF529_Conf] CanIfRxPduUserRxIndicationUL
$		// [CANIF530_Conf] CanIfRxPduUserRxIndicationName
$		// [CANIF441] <User_RxIndication>を提供する上位レイヤモジュールはCanIfRxPduUserRxIndicationULで指定される
$		// [CANIF552] <User_RxIndication>の名前はCanIfRxPduUserRxIndicationNameに定義する
		$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id])$
			$IF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "CAN_NM")$
$				// [CANIF445] CanIfRxPduUserRxIndicationULがCAN_NMの場合，CanIfRxPduUserRxIndicationNameはCanNm_RxIndication
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "CanNm_RxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `CanNm_RxIndication'. CanIfRxPduUserRxIndicationUL is `CAN_NM'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "CanNm_RxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "CAN_TP")$
$				// [CANIF448] CanIfRxPduUserRxIndicationULがCAN_TPの場合，CanIfRxPduUserRxIndicationNameはCanTp_RxIndication
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "CanTp_RxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `CanTp_RxIndication'. CanIfRxPduUserRxIndicationUL is `CAN_TP'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "CanTp_RxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "CDD")$
$				// [CANIF557] CanIfRxPduUserRxIndicationULがCDDの場合，<User_RxIndication>の名前はCanIfRxPduUserRxIndicationNameで指定される
				$IF !LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be set value. CanIfRxPduUserRxIndicationUL is `CDD'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "J1939TP")$
$				// [CANIF554] CanIfRxPduUserRxIndicationULがJ1939TPの場合，CanIfRxPduUserRxIndicationNameはJ1939Tp_RxIndication
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "J1939Tp_RxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `J1939Tp_RxIndication'. CanIfRxPduUserRxIndicationUL is `J1939TP'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "J1939Tp_RxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "PDUR")$
$				// [CANIF442] CanIfRxPduUserRxIndicationULがPDURの場合，CanIfRxPduUserRxIndicationNameはPduR_CanIfRxIndication 
				$IF LENGTH(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id])$
					$IF !EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id], "PduR_CanIfRxIndication")$
						$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationName should be `PduR_CanIfRxIndication'. CanIfRxPduUserRxIndicationUL is `PDUR'. (%1%\)"), rx_pdu_id)$$END$$DIE()$
					$END$
				$ELSE$
					$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "PduR_CanIfRxIndication"$
				$END$
			$ELIF EQ(CanIfRxPduCfg.CanIfRxPduUserRxIndicationUL[rx_pdu_id], "XCP")$
$				// [CANIF555] CanIfRxPduUserRxIndicationULがXCPの場合，CanIfRxPduUserRxIndicationNameはXcp_CanIfRxIndication
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
$				// CanIfRxPduUserRxIndicationULが省略され，かつ，CanIfRxPduUserRxIndicationNameに値が設定されている場合，エラー
				$ERROR$$FORMAT(_("CanIfRxPduUserRxIndicationUL should be set value. (%1%\)"), rx_pdu_id)$$END$$DIE()$
			$ELSE$
$				// CanIfRxPduUserRxIndicationULが省略され，かつ，CanIfRxPduUserRxIndicationNameが省略された場合，NULL_PTRで補完
				$CanIfRxPduCfg.CanIfRxPduUserRxIndicationName[rx_pdu_id] = "NULL_PTR"$
			$END$
		$END$

$		// [CANIF602_Conf] CanIfRxPduHrhIdRef
$		// 指定した参照先の妥当性は事前に確認済み

$		// [CANIF601_Conf] CanIfRxPduRef
$		// 指定した参照先の妥当性は事前に確認済み
	$END$
$END$

$ ====================================================================
$  [CANIF460] プリコンパイル用ヘッダ生成関数
$ ====================================================================
$FUNCTION GEN_CANIF_CFG_H$
	$FILE "CanIf_Cfg.h"$
	/* CanIf_Cfg.h */$NL$
	
	#ifndef TOPPERS_A_CANIF_CFG_H$NL$
	#define TOPPERS_A_CANIF_CFG_H$NL$
	$NL$

$	/*
$	 *  マクロ定義
$	 */
$	// [CANIF614_Conf] CanIfPublicDevErrorDetect
$	// デフォルト値はTRUE
	#define CANIF_PUBLIC_DEV_ERROR_DETECT$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicDevErrorDetect[1]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicDevErrorDetect[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$

$	// [CANIF613_Conf] CanIfPublicVersionInfoApi
$	// デフォルト値はTRUE
	#define CANIF_PUBLIC_VERSION_INFO_API$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicVersionInfoApi[1]) && !IS_TRUE(CanIfPublicCfg.CanIfPublicVersionInfoApi[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$$NL$

$	// [CANIF607_Conf] CanIfPublicReadRxPduDataApi 
$	// デフォルト値はFALSE
	#define CANIF_PUBLIC_READRXPDU_DATA_API$TAB$$TAB$$TAB$$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicReadRxPduDataApi[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduDataApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CANIF608_Conf] CanIfPublicReadRxPduNotifyStatusApi 
$	// デフォルト値はFALSE
	#define CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicReadRxPduNotifyStatusApi[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicReadRxPduNotifyStatusApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [CANIF609_Conf] CanIfPublicReadTxPduNotifyStatusApi  
$	// デフォルト値はFALSE
	#define CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API$TAB$
	$IF LENGTH(CanIfPublicCfg.CanIfPublicReadTxPduNotifyStatusApi[1]) && IS_TRUE(CanIfPublicCfg.CanIfPublicReadTxPduNotifyStatusApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$$NL$

$	// [CANIF785_Conf] CanIfPublicChangeBaudrateSupport
$	// デフォルト値はFALSE
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
$  リンクタイム用ヘッダ生成関数
$ ====================================================================
$FUNCTION GEN_CANIF_L_CFG_H$
	$FILE "CanIf_Lcfg.h"$
	/* CanIf_Lcfg.h */$NL$
	$NL$

	#ifndef TOPPERS_A_CANIF_L_CFG_H$NL$
	#define TOPPERS_A_CANIF_L_CFG_H$NL$
	$NL$

$	// [CANIF546_Conf] CanIfコントローラ関連はリンクタイムパラメータ
	$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
		extern CANIF_CTRL_CB canif_ctrl_cb_$ctrl_id$;$NL$
	$END$
	$NL$

	#endif /* TOPPERS_A_CANIF_L_CFG_H */
$END$

$ ====================================================================
$  [CANIF461] リンクタイム用実体生成関数
$ ====================================================================
$FUNCTION GEN_CANIF_L_CFG_C$
$ 	// [CANIF374] リンク時にコンフィギュレーション可能なパラメータ用
	$FILE "CanIf_Lcfg.c"$
	/* CanIf_Lcfg.c */$NL$
	$NL$

	#include "CanIf.h"$NL$
	#include "CanIf_Lcfg.h"$NL$

$	// [CANIF233] 以下のヘッダファイルをインクルードする
	#include "CanSM_Cbk.h"$NL$
	#include "EcuM_Cbk.h"$NL$

$	// [CANIF671_Conf] CanIfPublicCddHeaderFile
$	// [CANIF233] CDDの場合にインクルードするコールバック関数ヘッダファイル名はCanIfPublicCddHeaderFileで定義する
	$FOREACH chf_name CanIfPublicCfg.CanIfPublicCddHeaderFile[1]$
		#include "$chf_name$_Cbk.h"$NL$
	$END$
	$NL$

$	// [CANIF525_Conf][CANIF558] <User_ControllerBusOff>の名前はCanIfDispatchUserCtrlBusOffNameに指定される
$	// [CANIF524] <User_ControllerBusOff>の定義は必須
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

	const uint16 tnum_canif_controller = $LENGTH(CanIfCtrlCfg.ID_LIST)$U; /* CanIfコントローラ数 */$NL$
	$NL$

	/* CanIfコントローラ管理ブロック : canif_ctrl_cb_<CanIfCtrlCfg> */$NL$
	$FOREACH ctrl_id CanIfCtrlCfg.ID_LIST$
		CANIF_CTRL_CB canif_ctrl_cb_$ctrl_id$;$NL$
	$END$
	$NL$

	/* CanIfコントローラ初期化ブロック配列 : canif_ctrl_inib_table */$NL$
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
$  [CANIF462] ポストビルド用実体生成関数
$ ====================================================================
$FUNCTION GEN_CANIF_PB_CFG_C$
$ 	// [CANIF374] ビルド後にコンフィギュレーション可能なパラメータ用
	$FILE "CanIf_PBcfg.c"$

	/* CanIf_PBcfg.c */$NL$
	$NL$

	#include "Os.h"$NL$
	#include "CanIf.h"$NL$
	#include "CanIf_Lcfg.h"$NL$

$	// [CANIF208] 上位レイヤのヘッダファイルをインクルード
	#include "PduR_CanIf.h"$NL$
	#include "SchM_CanIf.h"$NL$
	$NL$

$	// [CANIF233] 以下のヘッダファイルをインクルード
	#include "CanNm_Cbk.h"$NL$
	#include "CanTp_Cbk.h"$NL$
	#include "J1939Tp_Cbk.h"$NL$
	#include "XcpOnCan_Cbk.h"$NL$
	
$	// [CANIF671_Conf] CanIfPublicCddHeaderFile
$	// [CANIF233] CDDの場合にインクルードするコールバック関数ヘッダファイル名はCanIfPublicCddHeaderFileで定義する
	$FOREACH chf1_name CanIfPublicCfg.CanIfPublicCddHeaderFile[1]$
		#include "$chf1_name$_Cbk.h"$NL$
	$END$
	$NL$

	/* 受信完了通知フラグ : rx_indication_flg_<CanIfInitCfg>_<CanIfRxPduCfg> */$NL$
	#if CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON$NL$
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$FOREACH rx_pdu_id CanIfInitCfg.rx_pdu_list[init_id]$
			static boolean rx_indication_flg_$init_id$_$rx_pdu_id$; /* $CanIfRxPduCfg.CanIfRxPduRef[rx_pdu_id]$ */$NL$
		$END$
	$END$
	#endif /* CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON */$NL$
	$NL$

	/* PDU通知状態 : read_notify_status_<CanIfInitCfg>_<CanIf[Tx|Rx]PduCfg> */$NL$
	#ifdef SUPPORT_READ_PDU_NOTYFY_STATUS$NL$
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		$FOREACH pdu_id CanIfInitCfg.pdu_list[init_id]$
$			// 送信の場合はCanIfTxPduReadNotifyStatus，受信の場合はCanIfRxPduReadNotifyStatus の値を取得
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
$			// CanIfTxPduReadNotifyStatus または CanIfRxPduReadNotifyStatus がTRUEの場合のみ生成
			$IF IS_TRUE(read_notify_status)$
				static CanIf_NotifStatusType read_notify_status_$init_id$_$pdu_id$;$NL$
			$END$
		$END$
	$END$
	#endif /* SUPPORT_READ_PDU_NOTYFY_STATUS */$NL$
	$NL$

	/* 受信LPDUバッファ : rx_lpdu_buffer_<CanIfInitCfg>_<CanIfRxPduCfg> */$NL$
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

	/* LPDU初期化ブロック配列 : lpdu_inib_table_<CanIfInitCfg> */$NL$
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

	/* LPDU初期化ブロック配列をCanObjectIdでソートしたリスト : lpdu_inib_hoh_list_<CanIfInitCfg> */$NL$
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

	/* CanIfコンフィギュレーション情報テーブル : <CanIfInitCfgSet> */$NL$
$	// [CANIF523] CanIf_ConfigTypeの初期化データ構造には，CanIfパブリックパラメータの定義と各LPDUの定義が含まれる
	$FOREACH init_id CanIfInitCfg.ID_LIST$
		const CanIf_ConfigType $CanIfInitCfg.CanIfInitCfgSet[init_id]$ = {$NL$
		$TAB$$CanIfInitCfg.pdu_num[init_id]$U,$TAB$/* tnum_lpdu */$NL$
		$TAB$lpdu_inib_table_$init_id$,$TAB$/* p_lpdu_inib_table */$NL$
		$TAB$lpdu_inib_hoh_list_$init_id$$TAB$/* pp_lpdu_inib_hoh_list */$NL$
		};$NL$
		$NL$
	$END$

	/* デフォルトのCanIfコンフィギュレーション情報 */$NL$
	const CanIf_ConfigType * const p_default_canif_config = &$CanIfInitCfg.CanIfInitCfgSet[1]$;$NL$
$END$


$ ====================================================================
$  メイン処理
$ ====================================================================
$ /*
$  *  [CANIF104] CanIfを構成するためのすべてのコンフィギュレーション情報を取得する
$  *  [CANIF066] CanIfはCanのコンテナパラメータを参照する
$  *  [CANIF132] CanIfとCanの間の従属性はジェネレータが提供する
$  */

$	DUMP()$

$ リスト作成
$MAKE_CFG_LIST()$

$ IDソート
$ID_SORT()$

$ エラーチェック
$ERROR_CHECK()$

$ プリコンパイル用ヘッダ
$GEN_CANIF_CFG_H()$

$ リンクタイム用
$GEN_CANIF_L_CFG_H()$
$GEN_CANIF_L_CFG_C()$

$ ポストビルド用プログラム
$GEN_CANIF_PB_CFG_C()$


$	TOPPERS/A-CANIF では対応しない仕様タグ一覧
$
$	- CANトランシーバ
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
$		[CANIF456][CANIF637_Conf]<CANIF606_Conf> CanIfCtrlWakeupSupport およびCanIfTrcvWakeupSupport がFALSEの場合，CanIfDispatchUserValidateWakeupEventULは設定不可
$		<CANIF655> CanIfTrcvIdは0から開始する
$		<CANIF695> CanIfTrcvDrvCfgが構成されていない場合，CanIfDispatchUserTrcvModeIndicationULは定義不可
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
$	- ソフトウェアフィルタリング
$		<CANIF619_Conf> CanIfPrivateCfg/CanIfPrivateSoftwareFilterType
$	- BSWスケジューラ
$		<CANIF669_Conf> CanIfRxPduCfg/CanIfRxPduBswSchExclAreaIdRef
$		<CANIF670_Conf> CanIfTxPduCfg/CanIfTxPduBswSchExclAreaIdRef
$	- NM
$		<CANIF741_Conf> CanIfPublicCfg/CanIfPublicWakeupCheckValidByNM
$	- 次リリースで削除される予定のパラメータ
$		<CANIF633_Conf> CanIfHrhCfg/CanIfHrhCanHandleTypeRef
$		<CANIF626_Conf> CanIfHthCfg/CanIfHthCanHandleTypeRef
$	- その他
$		<CANIF468> CanIfHthIdSymRefとCanIfHrhIdSymRefの参照先から各HOHに対するハードウェア受容フィルタを参照する
$		<CANIF696> <User_TrcvModeIndication>の名前はCanIfDispatchUserTrcvModeIndicationNameで定義する
$		           ただし，CanIfDispatchUserTrcvModeIndicationULが構成されていない場合は定義不可となる
$		<CANIF697> CanIfDispatchUserTrcvModeIndicationULがCAN_SMの場合，CanIfDispatchUserTrcvModeIndicationNameは
$		           CanSM_TransceiverModeIndicationであり，uint8型の関数パラメータの名前はTransceiverIdとする
$		<CANIF698> CanIfDispatchUserTrcvModeIndicationULがCDDの場合，<User_TransceiverModeIndication>の名前を
$		           CanIfDispatchUserTrcvModeIndicationNameで定義し，関数パラメータの型はuint8型とする
$		<CANIF794> CanIfPublicPnSupportがTRUEの場合，<User_ClearTrcvWufFlagIndication>を提供する上位レイヤモジュールを定義する
$		<CANIF795> CanIfPublicPnSupportがTRUEの場合，<User_ClearTrcvWufFlagIndication>の名前を
$		           CanIfDispatchUserClearTrcvWufFlagIndicationNameで定義することが可能となる
$		<CANIF796> <User_ClearTrcvWufFlagIndication>はCanIfPublicPnSupportの設定によってON/OFFできる
$		<CANIF797> CanIfDispatchUserClearTrcvWufFlagIndicationULがCAN_SMの場合，CanIfDispatchUserClearTrcvWufFlagIndicationNameは
$		           CanSM_ClearTrcvWufFlagIndicationであり，uint8型の関数パラメータの名前はTransceiverIdとする
$		<CANIF798> CanIfDispatchUserClearTrcvWufFlagIndicationULがCDDの場合，<User_ClearTrcvWufFlagIndication>の名前は
$		           CanIfDispatchUserClearTrcvWufFlagIndicationNameで定義され，関数パラメータはuint8型とする
$		<CANIF800> CanIfPublicPnSupportがTRUEの場合，CanIfDispatchUserCheckTrcvWakeFlagIndicationULの指定が可能となる
$		<CANIF801> <User_CheckTrcvWakeFlagIndication>の名前はCanIfDispatchUserCheckTrcvWakeFlagIndicationNameで定義する
$		<CANIF802> <User_CheckTrcvWakeFlagIndication>はCanIfPublicPnSupportの設定によってON/OFFできる
$		<CANIF803> CanIfDispatchUserCheckTrcvWakeFlagIndicationULがCAN_SMの場合，CanIfDispatchUserCheckTrcvWakeFlagIndicationNameは
$		           CanSM_CheckTrcvWakeFlagIndicationであり，uint8型の関数パラメータの名前はTransceiverIdとする
$		<CANIF804> CanIfDispatchUserCheckTrcvWakeFlagIndicationULがCDDの場合，<User_CheckTrcvWakeFlagIndication>の名前は
$		           CanIfDispatchUserCheckTrcvWakeFlagIndicationNameで指定され，関数パラメータの型はuint8とする
$		<CANIF823> <User_ConfirmPnAvailability>を通知する上位レイヤはCanIfDispatchUserConfirmPnAvailabilityULで定義する
$		<CANIF824> <Uset_ConfirmPnAvailability>の名前はCanIfDispatchUserConfirmPnAvailabilityNameで定義する
$		<CANIF825> <Uset_ConfirmPnAvailability>はCANIF_PUBLIC_PN_SUPPORTの設定によってON/OFFできる
$		<CANIF826> CanIfDispatchUserConfirmPnAvailabilityULがCAN_SMの場合，CanIfDispatchUserConfirmPnAvailabilityNameは
$		           CanSM_ConfirmPnAvailabilityであり，uint8型の関数パラメータの名前はTransceiverIdとする
$		<CANIF280> 以下のヘッダファイルをインクルードする
$		           ・Can_<vendorID>_<Vendor specific name><driver abbreviation>_Cfg.h
$		           ・CanTrcv_<Vendor Id>_<Vendor specific name><driver abbreviation>_Cfg.h
$		           ・PduR_Cfg.h
$		           ・CanNm_Cfg.h
$		           ・CanTp_Cfg.h
$		           ・Xcp_Cfg.h
$		<CANIF375> 提供されている機能を実行するために，コードファイルストラクチャにはCanIf_<X>.c が含まれ，
$		           拡張機能<X>は，複数のC-ファイルを使用する場合のオプションである
$		<CANIF376> コンパイル前にコンフィギュレーション可能なパラメータ用のCanIf_Cfg.cを含む
