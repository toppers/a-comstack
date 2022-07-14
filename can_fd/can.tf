$
$  TOPPERS/A-CAN
$      AuTomotive CAN
$
$  Copyright (C) 2013-2017 by Center for Embedded Computing Systems
$                             Graduate School of Information Science, Nagoya Univ., JAPAN
$  Copyright (C) 2013-2017 by FUJI SOFT INCORPORATED, JAPAN
$  Copyright (C) 2016-2017 by NEC Communication Systems, Ltd., JAPAN
$  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
$  Copyright (C) 2016-2017 by SCSK Corporation, JAPAN
$  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
$  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
$  Copyright (C) 2016-2017 by SUZUKI MOTOR CORPORATION
$  Copyright (C) 2013-2017 by TOSHIBA CORPORATION, JAPAN
$  Copyright (C) 2013-2017 by Witz Corporation
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
$  $Id: can.tf 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
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
	$FOREACH config_id CanConfigSet.ID_LIST$
$		// CanConfigSetごとのCanControllerリスト
		$new_list = {}$
		$FOREACH ctrl_id CanController.ID_LIST$
			$IF EQ(config_id, CanController.PARENT[ctrl_id])$
				$new_list = APPEND(new_list, ctrl_id)$
			$END$
		$END$
		$CanConfigSet.ctrl_id_list[config_id] = new_list$
		$CanConfigSet.ctrl_id_num[config_id] = LENGTH(new_list)$
	$END$
	$FOREACH ctrl_id CanController.ID_LIST$
$		// CanControllerごとのCanControllerBaudRateリスト
		$new_list = {}$
		$FOREACH baudrate_id CanControllerBaudrateConfig.ID_LIST$
			$IF EQ(ctrl_id, CanControllerBaudrateConfig.PARENT[baudrate_id])$
				$new_list = APPEND(new_list, baudrate_id)$
			$END$
		$END$
		$CanController.baudrate_list[ctrl_id] = new_list$
		$CanController.baudrate_num[ctrl_id] = LENGTH(new_list)$

$		// CanControllerごとのCanHardwareObjectリスト
$		// [CAN322_Conf] CanControllerRef
		$new_list = {}$
		$new_hrh_list = {}$
		$new_hth_list = {}$
		$rx_box_cnt = 0$
		$tx_box_cnt = 0$
		$FOREACH hoh_id CanHardwareObject.ID_LIST$
			$IF EQ(ctrl_id, CanHardwareObject.CanControllerRef[hoh_id])$
				$new_list = APPEND(new_list, hoh_id)$
				$IF EQ(CanHardwareObject.CanObjectType[hoh_id], "RECEIVE")$
					$new_hrh_list = APPEND(new_hrh_list, hoh_id)$
					$CanHardwareObject.box_num[hoh_id] = rx_box_cnt$
					$rx_box_cnt = rx_box_cnt + 1$
				$ELIF EQ(CanHardwareObject.CanObjectType[hoh_id], "TRANSMIT")$
					$new_hth_list = APPEND(new_hth_list, hoh_id)$
					$CanHardwareObject.box_num[hoh_id] = tx_box_cnt$
					$tx_box_cnt = tx_box_cnt + 1$
				$END$
			$END$
		$END$

		$CanController.hoh_list[ctrl_id] = new_list$
		$CanController.hoh_num[ctrl_id] = LENGTH(new_list)$

		$CanController.hrh_list[ctrl_id] = new_hrh_list$
		$CanController.hrh_num[ctrl_id] = LENGTH(new_hrh_list)$
$		// 受信メッセージボックス最大数：32
		$IF CanController.hrh_num[ctrl_id] >= 32$
			$ERROR$$FORMAT(_("The number of HRH should be 32 or less. (%1%\)"), ctrl_id)$$END$$DIE()$
		$END$

		$CanController.hth_list[ctrl_id] = new_hth_list$
		$CanController.hth_num[ctrl_id] = LENGTH(new_hth_list)$
$		// 送信メッセージボックス最大数：16
		$IF CanController.hth_num[ctrl_id] >= 16$
			$ERROR$$FORMAT(_("The number of HTH should be 16 or less. (%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
	$END$
$END$


$ ====================================================================
$  ID連番ソート関数
$ ====================================================================
$FUNCTION ID_SORT$
	$FOREACH ctrl_id CanController.ID_LIST$
$		// HOHリストをCanObjectId順にソート
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanController.hoh_list[ctrl_id]) - 1)$
			$find = 0$
			$FOREACH hoh_id CanController.hoh_list[ctrl_id]$
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
		$CanController.hoh_list[ctrl_id] = new_list$

$		// HRHリストを受信ボックス番号順にソート
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanController.hrh_list[ctrl_id]) - 1)$
			$find = 0$
			$FOREACH hrh_id CanController.hrh_list[ctrl_id]$
				$IF CanHardwareObject.box_num[hrh_id] == index$
					$new_list = APPEND(new_list, hrh_id)$
					$find = find + 1$
				$END$
			$END$
$			// box_numが0からの連番でない場合はエラー
			$IF find == 0$
				$ERROR$$FORMAT(_("box_num(%1%\) is not found. box_num should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("box_num(%1%\) is duplicated. box_num should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanController.hrh_list[ctrl_id] = new_list$
		
$		// HTHリストを送信ボックス番号順にソート
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanController.hth_list[ctrl_id]) - 1)$
			$find = 0$
			$FOREACH hth_id CanController.hth_list[ctrl_id]$
				$IF CanHardwareObject.box_num[hth_id] == index$
					$new_list = APPEND(new_list, hth_id)$
					$find = find + 1$
				$END$
			$END$
$			// CanObjectIdが0からの連番でない場合はエラー
			$IF find == 0$
				$ERROR$$FORMAT(_("box_num(%1%\) is not found. box_num should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("box_num(%1%\) is duplicated. box_num should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanController.hth_list[ctrl_id] = new_list$
	$END$
$END$

$ ====================================================================
$  エラーチェック関数
$ ====================================================================
$FUNCTION ERROR_CHECK$
$	// [CAN322_Conf] CanController
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

$		// [CAN316_Conf] CanControllerId
		$IF CanController.CanControllerId[ctrl_id] != 0$
			$ERROR$$FORMAT(_("CanControllerId should be `0'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
$		// [CAN314_Conf] CanBusoffProcessing
		$IF !EQ(CanController.CanBusoffProcessing[ctrl_id], "INTERRUPT")$
			$ERROR$$FORMAT(_("CanBusoffProcessing should be `INTERRUPT'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
$		// [CAN317_Conf] CanRxProcessing
		$IF !EQ(CanController.CanRxProcessing[ctrl_id], "INTERRUPT")$
			$ERROR$$FORMAT(_("CanRxProcessing should be `INTERRUPT'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
$		// [CAN318_Conf] CanTxProcessing
		$IF !EQ(CanController.CanTxProcessing[ctrl_id], "INTERRUPT")$
			$ERROR$$FORMAT(_("CanTxProcessing should be `INTERRUPT'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
$		// [CAN319_Conf] CanWakeupProcessing
		$IF !EQ(CanController.CanWakeupProcessing[ctrl_id], "INTERRUPT")$
			$ERROR$$FORMAT(_("CanWakeupProcessing should be `INTERRUPT'.(%1%\)"), ctrl_id)$$END$$DIE()$
		$END$
	$END$
	
$	// [CAN387_Conf] CanControllerBaudrateConfig
	$FOREACH baudrate_id CanControllerBaudrateConfig.ID_LIST$
$		// [CAN005_Conf] CanControllerBaudRate
$		// ボーレートに設定できるのは250または500のみ
		$IF ((CanControllerBaudrateConfig.CanControllerBaudRate[baudrate_id] != 250) && (CanControllerBaudrateConfig.CanControllerBaudRate[baudrate_id] != 500))$
			$ERROR$$FORMAT(_("CanControllerBaudRate should be `250' or `500'. (%1%\)"), baudrate_id)$$END$$DIE()$
		$END$
	$END$

$	// [CAN351_Conf] CanFilterMask
	$FOREACH filter_mask_id CanFilterMask.ID_LIST$
$		// [CAN066_Conf] CanFilterMaskValue
		$IF ((CanFilterMask.CanFilterMaskValue[filter_mask_id] < 0) || (CanFilterMask.CanFilterMaskValue[filter_mask_id] > 4294967295))$
			$ERROR$$FORMAT(_("CanFilterMaskValue should be in the range of 0..4294967295. (%1%\)"), filter_mask_id)$$END$$DIE()$
		$END$
	$END$

$	// [CAN324_Conf] CanHardwareObject
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
		$IF (!EQ(CanHardwareObject.CanObjectType[hoh_id], "RECEIVE") && !EQ(CanHardwareObject.CanObjectType[hoh_id], "TRANSMIT"))$
			$ERROR$$FORMAT(_("CanObjectType should be set to `RECEIVE' or `TRANSMIT'. (%1%\)"), hoh_id)$$END$$DIE()$
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
$  プリコンパイル用ヘッダ生成関数
$ ====================================================================
$FUNCTION GEN_CAN_CFG_H$
	$FILE "Can_Cfg.h"$
	/* Can_Cfg.h */$NL$

	#ifndef TOPPERS_A_CAN_CFG_H$NL$
	#define TOPPERS_A_CAN_CFG_H$NL$
	$NL$

	#include "Can.h"$NL$
	$NL$

$	// CanVersionInfoApi
	#define CAN_VERSION_INFO_API$TAB$
	$IF IS_TRUE(CanGeneral.CanVersionInfoApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$$NL$

	/* コントローラ数(1つのみ) */$NL$
	#define TNUM_CONTROLLER$TAB$$TAB$$TAB$1U$NL$
	$NL$

	#endif /* TOPPERS_A_CAN_CFG_H */
$END$

$ ====================================================================
$  ポストビルド用実体生成関数
$ ====================================================================
$FUNCTION GEN_CAN_PB_CFG_C$
$ 	// ビルド後にコンフィギュレーション可能なパラメータ用
	$FILE "Can_PBcfg.c"$
	/* Can_PBcfg.c */$NL$

$	// [CAN034]
	#include "Can.h"$NL$
	$NL$

$	// [CAN005_Conf] CanControllerBaudRate
	/* サポートボーレート配列 : baudrate_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			static const uint16 baudrate_$config_id$[$LENGTH(CanController.baudrate_list[ctrl_id])$] = {$NL$
			$JOINEACH baudrate_id CanController.baudrate_list[ctrl_id] ",\n"$
				$TAB$$CanControllerBaudrateConfig.CanControllerBaudRate[baudrate_id]$
			$END$
			$NL$};$NL$
		$END$
		$NL$
	$END$

	/* Canコントローラ管理ブロック配列 : can_ctrl_inib_table_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		static const CAN_CTRL_INIB can_ctrl_inib_table_$config_id$[TNUM_CONTROLLER] = {$NL$
		$JOINEACH ctrl_id CanConfigSet.ctrl_id_list[config_id] ",\n"$
			$TAB$/* $ctrl_id$ */$NL$
			$TAB${$NL$
			$TAB$$TAB$$CanController.canif_ctrl_id_ref[ctrl_id]$,$TAB$/* CanIfCtrlId */$NL$
			$TAB$$TAB$$CanController.baudrate_num[ctrl_id]$,$TAB$/* tnum_baudrate */$NL$
			$baudrate_id = CanController.CanControllerDefaultBaudrate[ctrl_id]$
			$TAB$$TAB$$CanControllerBaudrateConfig.CanControllerBaudRate[baudrate_id]$,$TAB$/* default_baudrate */$NL$
			$TAB$$TAB$baudrate_$config_id$$TAB$/* p_baudrate_table */$NL$
			$TAB$}$NL$
		$END$
		};$NL$
	$END$
	$NL$

	/* 送信完了通知用PDU-ID保存バッファ : saved_pduid_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			static PduIdType saved_pduid_$config_id$[$CanController.hth_num[ctrl_id]$];$NL$
			$NL$
		$END$
	$END$

	/* HOH→ボックス番号変換テーブル : hoh_box_table_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			static const Can_HwHandleType hoh_box_table_$config_id$[$CanController.hoh_num[ctrl_id]$] = {$NL$
			$JOINEACH hoh_id CanController.hoh_list[ctrl_id] ",\n"$
				$TAB$/* $CanHardwareObject.CanObjectType[hoh_id]$ */$NL$
				$TAB$$CanHardwareObject.box_num[hoh_id]$
			$END$
			$NL$};$NL$
			$NL$
		$END$
	$END$

	/* 受信ボックス番号→HRH変換テーブル : rbox_hrh_table_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			static const Can_HwHandleType rbox_hrh_table_$config_id$[$CanController.hrh_num[ctrl_id]$] = {$NL$
			$JOINEACH hrh_id CanController.hrh_list[ctrl_id] ",\n"$
				$TAB$$CanHardwareObject.CanObjectId[hrh_id]$
			$END$
			$NL$};$NL$
			$NL$
		$END$
	$END$

	/* 受信ボックスフィルタテーブル : rbox_filter_table_<CanConfigSet> */$NL$
	$FOREACH config_id CanConfigSet.ID_LIST$
		$FOREACH ctrl_id CanConfigSet.ctrl_id_list[config_id]$
			static const Can_IdType rbox_filter_table_$config_id$[$CanController.hrh_num[ctrl_id]$] = {$NL$
			$JOINEACH hrh_id CanController.hrh_list[ctrl_id] ",\n"$
$				// [CAN325_Conf] CanIdValue (FullCANのためCanFilterMaskRefは使用しない)
				$TAB$$CanHardwareObject.CanIdValue[hrh_id]$
			$END$
			$NL$};$NL$
			$NL$
		$END$
	$END$

	/* Canコンフィギュレーション情報 */$NL$
	const Can_ConfigType can_config[$LENGTH(CanConfigSet.ID_LIST)$] = {$NL$
	$JOINEACH config_id CanConfigSet.ID_LIST ",\n"$
		$TAB${$NL$
		$TAB$$TAB$$CanController.hoh_num[ctrl_id]$,$TAB$/* tnum_hoh */$NL$
		$TAB$$TAB$$CanController.hth_num[ctrl_id]$,$TAB$/* tnum_hth */$NL$
		$TAB$$TAB$$CanController.hrh_num[ctrl_id]$,$TAB$/* tnum_hrh */$NL$
		$TAB$$TAB$hoh_box_table_$config_id$,$TAB$/* p_hoh_box_table */$NL$
		$TAB$$TAB$rbox_hrh_table_$config_id$,$TAB$/* p_rbox_hrh_table */$NL$
		$TAB$$TAB$rbox_filter_table_$config_id$,$TAB$/* p_rbox_filter_table */$NL$
		$TAB$$TAB$saved_pduid_$config_id$,$TAB$/* p_saved_pduid */$NL$
		$TAB$$TAB$can_ctrl_inib_table_$config_id$$TAB$/* p_can_ctrl_inib_table */$NL$
		$TAB$}
	$END$
	$NL$};$NL$
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

$ プリコンパイル用
$GEN_CAN_CFG_H()$

$ ポストビルド用
$GEN_CAN_PB_CFG_C()$

