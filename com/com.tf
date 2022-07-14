$
$  TOPPERS/A-COM
$      AuTomotive COM
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
$  $Id: com.tf 1241 2015-03-25 07:26:02Z panasonic-ayane $
$

$	// [COM006] XMLによるコンフィギュレーションパラメータ処理

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
$ 割り算関数
$ ====================================================================
$FUNCTION DIV$
$	// 引数に小数点が指定されていない場合はエラー
	$tmp = REGEX_REPLACE(ARGV[1], "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("`%1%\' is not a float value."), ARGV[1])$$END$$DIE()$
	$END$
	$tmp = REGEX_REPLACE(ARGV[2], "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("`%1%\' is not a float value."), ARGV[2])$$END$$DIE()$
	$END$

	$num1_l = REGEX_REPLACE(ARGV[1], "^([0-9]+)\\.[0-9]+$", "$1")$
	$num1_r = REGEX_REPLACE(ARGV[1], "^[0-9]+\\.([0-9]+)$", "$1")$
	$num1_r = REGEX_REPLACE(CONCAT(num1_r, "0000"), "^(....).*$", "$1")$
	$num1 = ATOI(CONCAT(num1_l, num1_r), 10)$
	$num2_l = REGEX_REPLACE(ARGV[2], "^([0-9]+)\\.[0-9]+$", "$1")$
	$num2_r = REGEX_REPLACE(ARGV[2], "^[0-9]+\\.([0-9]+)$", "$1")$
	$num2_r = REGEX_REPLACE(CONCAT(num2_r, "0000"), "^(....).*$", "$1")$
	$num2 = ATOI(CONCAT(num2_l, num2_r), 10)$
	$div_result = num1 / num2$
	$mod_result = num1 % num2$
$	// [NCOM005] 割り算の余りは繰り上げる
	$IF mod_result > 0$
		$div_result = div_result + 1$
	$END$
	$RESULT = div_result$
$END$

$ ====================================================================
$ 関数名チェック関数
$ ====================================================================
$FUNCTION FUNC_NAME_CHECK$
	$name = REGEX_REPLACE(ARGV[1], "^[a-z|A-Z]+[_|a-z|A-Z|0-9]*$", "")$
	$IF !EQ(name, "")$
		$ERROR$$FORMAT(_("'%1%\' does not according to C's identifier rules."), ARGV[1])$$END$$DIE()$
	$END$
$END$

$ ====================================================================
$ [NCOM038] シグナル値のレンジチェック関数
$ ====================================================================
$FUNCTION SIGNAL_RANGE_CHECK$
	$value = ARGV[1]$
	$type  = ARGV[2]$
	$size  = ARGV[3]$
	$min = 0$
	$max = 0$
	$tmp = 1$
	$FOREACH index RANGE(1, size)$
		$tmp = tmp * 2$
	$END$
	$IF (EQ(type, "UINT8") || EQ(type, "UINT16") || EQ(type, "UINT32"))$
		$min = 0$
		$max = tmp - 1$
	$ELIF (EQ(type, "SINT8") || EQ(type, "SINT16") || EQ(type, "SINT32"))$
		$min = (tmp / 2) * -1$
		$max = (tmp / 2) - 1$
	$END$
	$IF (value < min) || (max < value)$
		$ERROR$$FORMAT(_("%1%\ is `%2%\'. It is not within the range of ComBitSize. (ComBitSize:%3%\ [min:%4%\  max:%5%\])"), ARGV[4], value, size, min, max)$$END$$DIE()$
	$END$
$END$

$ ====================================================================
$ MSB→LSB変換関数
$ ====================================================================
$FUNCTION MSB2LSB$
	$msb = ARGV[1]$
	$size = ARGV[2]$
$	// msbの逆順番号を算出
	$bit_index = msb % 8$
	$byte_index = msb / 8$
	$msb_inv = (7 - bit_index) + 8 * byte_index$
$	// lsbの逆順番号を算出
	$lsb_inv = msb_inv + (size - 1)$
$	// lsbを算出
	$bit_index = lsb_inv % 8$
	$byte_index = lsb_inv / 8$
	$lsb = 8 * byte_index + (7 - bit_index)$
	$RESULT = lsb$
$END$

$ ====================================================================
$  ID連番ソート関数
$ ====================================================================
$FUNCTION ID_SORT$
$	// [COM394_Conf] ComConfigurationId順にソート
	$new_list = {}$
	$FOREACH index RANGE(0, LENGTH(ComConfig.ID_LIST) - 1)$
		$find = 0$
		$FOREACH configid ComConfig.ID_LIST$
			$IF ComConfig.ComConfigurationId[configid] == index$
				$new_list = APPEND(new_list, configid)$
				$find = find + 1$
			$END$
		$END$
$		// [NCOM008] ComConfigurationIdが0からの連番でない場合はエラー
		$IF find == 0$
			$ERROR$$FORMAT(_("ComConfigurationId `%1%\' is not found. ComConfigurationId should be sequential from 0."), index)$$END$$DIE()$
		$END$
		$IF find > 1$
			$ERROR$$FORMAT(_("ComConfigurationId `%1%\' is duplicated. ComConfigurationId should be unique."), index)$$END$$DIE()$
		$END$
	$END$
	$ComConfig.ID_LIST = new_list$

$	// コンフィグごとのIPDUグループリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$cnt = 0$
		$FOREACH ipdu_g_id ComIPduGroup.ID_LIST$
			$IF EQ(config_id, ComIPduGroup.PARENT[ipdu_g_id])$
				$new_list = APPEND(new_list, ipdu_g_id)$
				$cnt = cnt + 1$
			$END$
		$END$
		$ComConfig.ipdu_g_list[config_id] = new_list$
		$ComConfig.ipdu_g_num[config_id] = cnt$
	$END$
$	// [COM184_Conf] コンフィグごとのIPDUグループリストをComIPduGroupHandleId順にソート
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(ComConfig.ipdu_g_list[config_id]) - 1)$
			$find = 0$
			$FOREACH ipdu_g_id ComConfig.ipdu_g_list[config_id]$
				$IF ComIPduGroup.ComIPduGroupHandleId[ipdu_g_id] == index$
					$new_list = APPEND(new_list, ipdu_g_id)$
					$find = find + 1$
				$END$
			$END$
$			// [NCOM008] ComIPduGroupHandleIdが0から連番でない場合はエラー
			$IF find == 0$
				$ERROR$$FORMAT(_("ComIPduGroupHandleId `%1%\' is not found. ComIPduGroupHandleId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("ComIPduGroupHandleId `%1%\' is duplicated. ComIPduGroupHandleId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$ComConfig.ipdu_g_list[config_id] = new_list$
	$END$

$	// コンフィグごとのIPDUリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$cnt = 0$
		$FOREACH ipdu_id ComIPdu.ID_LIST$
			$IF EQ(config_id, ComIPdu.PARENT[ipdu_id])$
				$new_list = APPEND(new_list, ipdu_id)$
				$cnt = cnt + 1$
			$END$
		$END$
		$ComConfig.ipdu_list[config_id] = new_list$
		$ComConfig.ipdu_num[config_id] = cnt$
	$END$
$	// [COM175_Conf][NCOM003] コンフィグごとのIPDUリストをComIPduHandleId順にソート
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(ComConfig.ipdu_list[config_id]) - 1)$
			$find = 0$
			$FOREACH ipduid ComConfig.ipdu_list[config_id]$
				$IF ComIPdu.ComIPduHandleId[ipduid] == index$
					$new_list = APPEND(new_list, ipduid)$
					$find = find + 1$
				$END$
			$END$
$			// [NCOM008]ComIPduHandleIdが0からの連番でない場合はエラー
			$IF find == 0$
				$ERROR$$FORMAT(_("ComIPduHandleId `%1%\' is not found. ComIPduHandleId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("ComIPduHandleId `%1%\' is duplicated. ComIPduHandleId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$ComConfig.ipdu_list[config_id] = new_list$
	$END$

$	// コンフィグごとのシグナルリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$cnt = 0$
		$FOREACH signal_id ComSignal.ID_LIST$
			$IF EQ(config_id, ComSignal.PARENT[signal_id])$
				$new_list = APPEND(new_list, signal_id)$
				$cnt = cnt + 1$
			$END$
		$END$
		$ComConfig.signal_list[config_id] = new_list$
		$ComConfig.signal_num[config_id] = cnt$
	$END$
$	// [COM165_Conf] コンフィグごとのシグナルリストをComHandleId順にソート
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(ComConfig.signal_list[config_id]) - 1)$
			$find = 0$
			$FOREACH handleid ComConfig.signal_list[config_id]$
				$IF ComSignal.ComHandleId[handleid] == index$
					$new_list = APPEND(new_list, handleid)$
					$find = find + 1$
				$END$
			$END$
$			// [NCOM008] ComHandleIdが0からの連番でない場合はエラー
			$IF find == 0$
				$ERROR$$FORMAT(_("ComHandleId `%1%\' is not found. ComHandleId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("ComHandleId `%1%\' is duplicated. ComHandleId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$ComConfig.signal_list[config_id] = new_list$
	$END$

$	// コンフィグごとのフィルタリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH filter_id ComFilter.ID_LIST$
			$IF EQ(config_id, ComSignal.PARENT[ComFilter.PARENT[filter_id]])$
				$new_list = APPEND(new_list, filter_id)$
			$END$
		$END$
		$ComConfig.filter_list[config_id] = new_list$
	$END$
$END$

$ ====================================================================
$  [NCOM007] エラーチェック関数
$ ====================================================================

$FUNCTION ERROR_CHECK$
	$com_config_id = ARGV[1]$

$	// [COM540_Conf] Comの設定値をチェック

$	// [COM401] ComIPduGroupのショートネームは重複不可
	$FOREACH ipdu_g_id ComConfig.ipdu_g_list[com_config_id]$
		$FOREACH ipdu_g_chk_id ComConfig.ipdu_g_list[com_config_id]$
			$IF EQ(ipdu_g_id, ipdu_g_chk_id) && (ipdu_g_id != ipdu_g_chk_id)$
				$ERROR$$FORMAT(_("Short Name of ComIPduGroup should not be duplicated. (%1%\)"), ipdu_g_id)$$END$$DIE()$
			$END$
		$END$
	$END$
$	// [COM401] ComIPduのショートネームは重複不可
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
		$FOREACH ipdu_chk_id ComConfig.ipdu_list[com_config_id]$
			$IF EQ(ipdu_id, ipdu_chk_id) && (ipdu_id != ipdu_chk_id)$
				$ERROR$$FORMAT(_("Short Name of ComIPdu should not be duplicated. (%1%\)"), ipdu_id)$$END$$DIE()$
			$END$
		$END$
	$END$
$	// [COM401] ComSignalのショートネームは重複不可
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
		$FOREACH signal_chk_id ComConfig.signal_list[com_config_id]$
			$IF EQ(signal_id, signal_chk_id) && (signal_id != signal_chk_id)$
				$ERROR$$FORMAT(_("Short Name of ComSignal should not be duplicated. (%1%\)"), signal_id)$$END$$DIE()$
			$END$
		$END$
	$END$

$	// [COM730_Conf] ComTimeBase
	$FOREACH time_base_id ComTimeBase.ID_LIST$
		$IF EQ(com_config_id, ComTimeBase.PARENT[time_base_id])$
$			// [COM728_Conf] ComRxTimeBase
			$IF LENGTH(ComTimeBase.ComRxTimeBase[time_base_id])$
				$ComConfig.rx_time_base[com_config_id] = ComTimeBase.ComRxTimeBase[time_base_id]$
			$ELSE$
				$ComConfig.rx_time_base[com_config_id] = "COM_INVALID_UINT32"$
			$END$
$			// [COM186_Conf] ComTxTimeBase
			$IF LENGTH(ComTimeBase.ComTxTimeBase[time_base_id])$
				$ComConfig.tx_time_base[com_config_id] = ComTimeBase.ComTxTimeBase[time_base_id]$
			$ELSE$
				$ComConfig.tx_time_base[com_config_id] = "COM_INVALID_UINT32"$
			$END$
		$END$
	$END$

$	/*
$	 * [COM341_Conf][NCOM028] IPDUグループの設定値チェック
$	 */
	$FOREACH ipdu_g_id ComConfig.ipdu_g_list[com_config_id]$
$		// [COM185_Conf] ComIPduGroupGroupRef
		$IF LENGTH(ComIPduGroup.ComIPduGroupGroupRef[ipdu_g_id])$
$			// [NCOM009] IPDUグループのネスト所属をサポートしないため，ComIPduGroupGroupRefを指定した場合はエラー
			$ERROR$$FORMAT("ComIPduGroupGroupRef is not supported.")$$END$$DIE()$
		$END$
	$END$

$	/*
$	 * [COM340_Conf][NCOM027] IPDUの設定値チェック
$	 */
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
$		// [COM493_Conf] ComIPduDirectionに設定できる値はRECEIVEとSENDのみ
		$IF (!EQ(ComIPdu.ComIPduDirection[ipdu_id], "SEND") && !EQ(ComIPdu.ComIPduDirection[ipdu_id], "RECEIVE"))$
			$ERROR$$FORMAT("ComIPduDirection should be set to "SEND" or "RECEIVE".")$$END$$DIE()$
		$END$

$		// [COM518_Conf] ComIPduSignalRef
		$IF LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id])$
			$FOREACH signal_ref_id ComIPdu.ComIPduSignalRef[ipdu_id]$
				$IF !LENGTH(ComSignal.ipdu_ref[signal_ref_id])$
					$ComSignal.ipdu_ref[signal_ref_id] = ComIPdu[ipdu_id]$
				$ELSE$
$					// [COM101] シグナルは2つ以上のIPDUに所属できない
					$ERROR$$FORMAT(_("`%1%\' belongs to more than one IPDU."), ComSignal[signal_ref_id])$$END$$DIE()$
				$END$
				$ComSignal.direction[signal_ref_id] = ComIPdu.ComIPduDirection[ipdu_id]$
			$END$
		$END$

$		// [COM119_Conf] ComIPduSignalProcessingに設定できる値はDEFERREDとIMMEDIATEのみ
		$IF !EQ(ComIPdu.ComIPduSignalProcessing[ipdu_id], "DEFERRED") && !EQ(ComIPdu.ComIPduSignalProcessing[ipdu_id], "IMMEDIATE")$
			$ERROR$$FORMAT(_("ComIPduSignalProcessing should not be set `%1%\'. (%2%\)"),ComIPdu.ComIPduSignalProcessing[ipdu_id] , ComIPdu[ipdu_id])$$END$$DIE()$
		$END$

$		// [COM761_Conf] ComIPduTypeに設定できる値はNORMALとTPのみ (TPはサポート対象外のため警告)
		$IF !EQ(ComIPdu.ComIPduType[ipdu_id], "NORMAL") && !EQ(ComIPdu.ComIPduType[ipdu_id], "TP")$
			$ERROR$$FORMAT(_("ComIPduType should not be set `%1%\'. (%2%\)"), ComIPdu.ComIPduType[ipdu_id] , ComIPdu[ipdu_id])$$END$$DIE()$
		$ELIF EQ(ComIPdu.ComIPduType[ipdu_id], "TP")$
			$WARNING$$FORMAT(_("ComIPduType is TP. (%1%\)"), ComIPdu[ipdu_id])$$END$
		$END$

$		// [COM387_Conf] ComIPduCallout
		$IF LENGTH(ComIPdu.ComIPduCallout[ipdu_id])$
$			// [COM402] 関数名はC言語で扱える文字列でなければならない
			$FUNC_NAME_CHECK(ComIPdu.ComIPduCallout[ipdu_id])$
		$ELSE$
			$ComIPdu.ComIPduCallout[ipdu_id] = "NULL_PTR"$
		$END$

$		// [COM709_Conf] ComIPduCancellationSupport
		$IF LENGTH(ComIPdu.ComIPduCancellationSupport[ipdu_id]) && IS_TRUE(ComIPdu.ComIPduCancellationSupport[ipdu_id])$
			$ComIPdu.ComIPduCancellationSupport[ipdu_id] = "TRUE"$
		$ELSE$
$			// デフォルト値はFALSE
			$ComIPdu.ComIPduCancellationSupport[ipdu_id] = "FALSE"$
		$END$

$		// [COM711_Conf] ComPduIdRefの設定値と同じIDを持つPduのLengthをIPDUバッファのLengthとして取得
		$IF LENGTH(Pdu.PduLength[ComIPdu.ComPduIdRef[ipdu_id]])$
			$ComIPdu.pdu_length[ipdu_id] = Pdu.PduLength[ComIPdu.ComPduIdRef[ipdu_id]]$
		$ELSE$
			$ERROR$$FORMAT(_("ComPduIdRef is incorrect value. (%1%\)"), ComIPdu[ipdu_id])$$END$$DIE()$
		$END$

$		// PduRSourcePduHandleIdを保持
		$ComIPdu.pdur_src_pdu_handle_id[ipdu_id] = "COM_INVALID_UINT16"$
		$FOREACH src_pdu_id PduRSrcPdu.ID_LIST$
			$IF EQ(ComIPdu.ComPduIdRef[ipdu_id], PduRSrcPdu.PduRSrcPduRef[src_pdu_id])$
				$ComIPdu.pdur_src_pdu_handle_id[ipdu_id] = PduRSrcPdu.PduRSourcePduHandleId[src_pdu_id]$
			$END$
		$END$

$		// IPDUごとにComTimeoutとComFirstTimeoutの最小値を保持して各シグナルに反映
		$ComIPdu.timeout_min[ipdu_id] = 0$
		$ComIPdu.first_timeout_min[ipdu_id] = 0$
		$IF EQ(ComIPdu.ComIPduDirection[ipdu_id], "SEND")$
$			// [NCOM049] 送信シグナルがある場合はComTxTimeBase必須
			$IF EQ(ComConfig.tx_time_base[com_config_id], "COM_INVALID_UINT32")$
				$ERROR$$FORMAT(_("`%1%\' should be set ComTxTimeBase."), ComIPdu.PARENT[ipdu_id])$$END$$DIE()$
			$END$
			$FOREACH signal_ref_id ComIPdu.ComIPduSignalRef[ipdu_id]$
$				// [COM263_Conf] ComTimeout
				$IF LENGTH(ComSignal.ComTimeout[signal_ref_id])$
$					// [NCOM037] ComTxTimeBaseより小さい場合はエラー
					$IF (ComSignal.ComTimeout[signal_ref_id] != 0) && (ComSignal.ComTimeout[signal_ref_id] < ComConfig.tx_time_base[com_config_id])$
						$ERROR$$FORMAT(_("ComTimeout is less than ComTxTimeBase. (%1%\)"), ComSignal[signal_ref_id])$$END$$DIE()$
					$END$
				$ELSE$
					$ComSignal.ComTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.timeout[signal_ref_id] = DIV(ComSignal.ComTimeout[signal_ref_id], ComConfig.tx_time_base[com_config_id])$
$				// [COM445] 送信シグナルのデッドラインモニタリングには所属するIPDU内全てのシグナルに設定されたComTimeoutの最小値を用いる
				$IF ComSignal.timeout[signal_ref_id] != 0$
					$IF ((ComIPdu.timeout_min[ipdu_id] == 0) || (ComIPdu.timeout_min[ipdu_id] > ComSignal.timeout[signal_ref_id]))$
						$ComIPdu.timeout_min[ipdu_id] = ComSignal.timeout[signal_ref_id]$
					$END$
				$END$
$				// [COM183_Conf] ComFirstTimeout
				$IF LENGTH(ComSignal.ComFirstTimeout[signal_ref_id])$
$					// [NCOM037] ComTxTimeBaseより小さい場合はエラー
					$IF (ComSignal.ComFirstTimeout[signal_ref_id] != 0) && (ComSignal.ComFirstTimeout[signal_ref_id] < ComConfig.tx_time_base[com_config_id])$
						$ERROR$$FORMAT(_("ComFirstTimeout is less than ComTxTimeBase. (%1%\)"), ComSignal[signal_ref_id])$$END$$DIE()$
					$END$
				$ELSE$
					$ComSignal.ComFirstTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.first_timeout[signal_ref_id] = DIV(ComSignal.ComFirstTimeout[signal_ref_id], ComConfig.tx_time_base[com_config_id])$
				$IF ComSignal.first_timeout[signal_ref_id] != 0$
					$IF ((ComIPdu.first_timeout_min[ipdu_id] == 0) || (ComIPdu.first_timeout_min[ipdu_id] > ComSignal.first_timeout[signal_ref_id]))$
						$ComIPdu.first_timeout_min[ipdu_id] = ComSignal.first_timeout[signal_ref_id]$
					$END$
				$END$
			$END$
		$ELIF EQ(ComIPdu.ComIPduDirection[ipdu_id], "RECEIVE")$
$			// [NCOM050] 受信シグナルがある場合はComRxTimeBase必須
			$IF EQ(ComConfig.rx_time_base[com_config_id], "COM_INVALID_UINT32")$
				$ERROR$$FORMAT(_("`%1%\' should be set ComRxTimeBase."), ComIPdu.PARENT[ipdu_id])$$END$$DIE()$
			$END$
			$FOREACH signal_ref_id ComIPdu.ComIPduSignalRef[ipdu_id]$
$				// [COM263_Conf] ComTimeout
				$IF LENGTH(ComSignal.ComTimeout[signal_ref_id])$
$					// [NCOM036] ComRxTimeBaseより小さい場合はエラー
					$IF (ComSignal.ComTimeout[signal_ref_id] != 0) && (ComSignal.ComTimeout[signal_ref_id] < ComConfig.rx_time_base[com_config_id])$
						$ERROR$$FORMAT(_("ComTimeout is less than ComRxTimeBase. (%1%\)"), ComSignal[signal_ref_id])$$END$$DIE()$
					$END$
				$ELSE$
					$ComSignal.ComTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.timeout[signal_ref_id] = DIV(ComSignal.ComTimeout[signal_ref_id], ComConfig.rx_time_base[com_config_id])$
$				// [COM291] アップデートビットを持たないシグナルの受信デッドラインカウンタは所属するIPDU内の全てのアップデートビットを持たないシグナルに設定されたComTimeoutの最小値を用いる
				$IF (ComSignal.timeout[signal_ref_id] != 0) && !LENGTH(ComSignal.ComUpdateBitPosition[signal_ref_id])$
					$IF ((ComIPdu.timeout_min[ipdu_id] == 0) || (ComIPdu.timeout_min[ipdu_id] > ComSignal.timeout[signal_ref_id]))$
						$ComIPdu.timeout_min[ipdu_id] = ComSignal.timeout[signal_ref_id]$
					$END$
				$END$
$				// [COM183_Conf] ComFirstTimeout
				$IF LENGTH(ComSignal.ComFirstTimeout[signal_ref_id])$
$					// [NCOM036] ComRxTimeBaseより小さい場合はエラー
					$IF (ComSignal.ComFirstTimeout[signal_ref_id] != 0) && (ComSignal.ComFirstTimeout[signal_ref_id] < ComConfig.rx_time_base[com_config_id])$
						$ERROR$$FORMAT(_("ComFirstTimeout is less than ComRxTimeBase. (%1%\)"), ComSignal[signal_ref_id])$$END$$DIE()$
					$END$
				$ELSE$
					$ComSignal.ComFirstTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.first_timeout[signal_ref_id] = DIV(ComSignal.ComFirstTimeout[signal_ref_id], ComConfig.rx_time_base[com_config_id])$
$				// [COM291] アップデートビットを持たないシグナルの受信デッドラインカウンタは所属するIPDU内の全てのアップデートビットを持たないシグナルに設定されたComFirstTimeoutの最小値を用いる
				$IF (ComSignal.first_timeout[signal_ref_id] != 0) && !LENGTH(ComSignal.ComUpdateBitPosition[signal_ref_id])$
					$IF ((ComIPdu.first_timeout_min[ipdu_id] == 0) || (ComIPdu.first_timeout_min[ipdu_id] > ComSignal.first_timeout[signal_ref_id]))$
						$ComIPdu.first_timeout_min[ipdu_id] = ComSignal.first_timeout[signal_ref_id]$
					$END$
				$END$
			$END$
		$END$

$		// [COM497] 送信に設定されたComIPduはComTxIPduを持たなければならない
		$IF EQ(ComIPdu.ComIPduDirection[ipdu_id], "SEND")$
			$tx_ipdu_is_exist = 0$
			$FOREACH tx_ipdu_id ComTxIPdu.ID_LIST$
				$IF EQ(ipdu_id, ComTxIPdu.PARENT[tx_ipdu_id])$
					$tx_ipdu_is_exist = 1$
				$END$
			$END$
			$IF tx_ipdu_is_exist != 1$
				$ERROR$$FORMAT(_("`%1%\' should have ComTxIPdu."), ComIPdu[ipdu_id])$$END$$DIE()$
			$END$
		$END$
	$END$


$	/*
$	 * [COM496_Conf] 送信IPDU用コンテナComTxIPduの設定値チェック
$	 */
	$FOREACH tx_ipdu_id ComTxIPdu.ID_LIST$
		$IF EQ(com_config_id, ComIPdu.PARENT[ComTxIPdu.PARENT[tx_ipdu_id]])$
$			// [COM181_Conf] ComMinimumDelayTime
			$IF LENGTH(ComTxIPdu.ComMinimumDelayTime[tx_ipdu_id])$
$				// [NCOM037] ComMinimumDelayTimeに設定された値がComTxTimeBaseより小さい場合はエラー
				$IF (ComTxIPdu.ComMinimumDelayTime[tx_ipdu_id] != 0) && (ComTxIPdu.ComMinimumDelayTime[tx_ipdu_id] < ComConfig.tx_time_base[com_config_id])$
					$ERROR$$FORMAT(_("ComMinimumDelayTime is less than ComTxTimeBase. (%1%\)"), ComTxIPdu[tx_ipdu_id])$$END$$DIE()$
				$END$
			$ELSE$
				$ComTxIPdu.ComMinimumDelayTime[tx_ipdu_id] = "0.0"$
			$END$

$			// [COM576_Conf] ComTxIPduClearUpdateBit
			$IF LENGTH(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id])$
				$IF !EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "CONFIRMATION")
					&& !EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "TRANSMIT")
					&& !EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "TRIGGER_TRANSMIT")$
					$ERROR$$FORMAT(_("ComTxIPduClearUpdateBit should not be set `%1%\'. (%2%\)"),ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id] , ComTxIPdu[tx_ipdu_id])$$END$$DIE()$
				$END$
			$ELSE$
$				// [NCOM030] ComTxIPduClearUpdateBitのデフォルト値はTRANSMIT
				$ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id] = "TRANSMIT"$
			$END$

$			// [COM017_Conf] ComTxIPduUnusedAreasDefaultの閾値チェック
			$IF (+ComTxIPdu.ComTxIPduUnusedAreasDefault[tx_ipdu_id] < 0) || (+ComTxIPdu.ComTxIPduUnusedAreasDefault[tx_ipdu_id] > 255)$
				$ERROR$$FORMAT(_("0 < ComTxIPduUnusedAreasDefault < 255. (%1%\)"), ComTxIPdu[tx_ipdu_id])$$END$$DIE()$
			$END$

$			// [COM455_Conf][COM454_Conf]ComTxModeTrue と ComTxModeFalseの有無チェック
			$tx_mode_is_exit = 0$
			$tx_mode_true_mode = ""$
			$tx_mode_false_mode = ""$
			$FOREACH tx_mode_true_id ComTxModeTrue.ID_LIST$
				$IF tx_ipdu_id == ComTxModeTrue.PARENT[tx_mode_true_id]$
					$tx_mode_is_exit = 1$
					$ComTxModeTrue.config_ref_id[tx_mode_true_id] = com_config_id$
					$ComTxIPdu.tx_mode_true_ref_id[tx_ipdu_id] = tx_mode_true_id$
					$FOREACH tx_mode_id ComTxMode_true.ID_LIST$
						$IF tx_mode_true_id == ComTxMode_true.PARENT[tx_mode_id]$
							$tx_mode_true_mode = ComTxMode_true.ComTxModeMode[tx_mode_id]$
							$ComTxMode_true.config_ref_id[tx_mode_id] = com_config_id$
							$ComTxMode_true.tx_ipdu_ref_id[tx_mode_id] = tx_ipdu_id$
						$END$
					$END$
				$END$
			$END$
			$FOREACH tx_mode_false_id ComTxModeFalse.ID_LIST$
				$IF tx_ipdu_id == ComTxModeFalse.PARENT[tx_mode_false_id]$
					$tx_mode_is_exit = 1$
					$ComTxModeFalse.config_ref_id[tx_mode_false_id] = com_config_id$
					$ComTxIPdu.tx_mode_false_ref_id[tx_ipdu_id] = tx_mode_false_id$
					$FOREACH tx_mode_id ComTxMode_false.ID_LIST$
						$IF tx_mode_false_id == ComTxMode_false.PARENT[tx_mode_id]$
							$tx_mode_false_mode = ComTxMode_false.ComTxModeMode[tx_mode_id]$
							$ComTxMode_false.config_ref_id[tx_mode_id] = com_config_id$
							$ComTxMode_false.tx_ipdu_ref_id[tx_mode_id] = tx_ipdu_id$
						$END$
					$END$
				$END$
			$END$
$			// [COM465] ComTxIPduにComTxModeTrueとComTxModeFalseのどちらも設定されていない場合はエラー
			$IF tx_mode_is_exit != 1$
				$ERROR$$FORMAT(_("ComTxIPdu has to include at least one of the container ComTxModeTrue or ComTxModeFalse. (%1%\)"),ComTxIPdu.PARENT[tx_ipdu_id])$$END$$DIE()$
			$END$
$			// ComTxModeTrueとComTxModeFalseのComTxModeModeがどちらもNONEの場合は警告
			$IF (EQ(tx_mode_true_mode, "NONE") && EQ(tx_mode_false_mode, "NONE"))$
				$WARNING$$FORMAT(_("ComTxModeTrue.ComTxModeMode and ComTxModeFalse.ComTxModeMode is `NONE'. This IPDU will not be sent. (%1%\)"), ComTxIPdu.PARENT[tx_ipdu_id])$$END$
			$END$
		$END$
	$END$

$	/*
$	 *  [COM351_Conf] 送信モードの設定値チェック
$	 */
	$FOREACH tx_mode_id ComTxMode_true.ID_LIST$
		$IF EQ(com_config_id, ComTxMode_true.config_ref_id[tx_mode_id])$
$			// [COM137_Conf] ComTxModeMode
				$IF !EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "DIRECT") && !EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "MIXED")
				&& !EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "NONE") && !EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "PERIODIC")$
				$ERROR$$FORMAT(_("ComTxModeMode should not be set `%1%\'. (%2%\)"),ComTxMode_true.ComTxModeMode[tx_mode_id] , ComTxIPdu.PARENT[ComTxMode_true.tx_ipdu_ref_id[tx_mode_id]])$$END$$DIE()$
			$END$
$			// [COM281_Conf] ComTxModeNumberOfRepetitions
			$IF !LENGTH(ComTxMode_true.ComTxModeNumberOfRepetitions[tx_mode_id])$
				$ComTxMode_true.ComTxModeNumberOfRepetitions[tx_mode_id] = 0$
			$END$
$			// [COM282_Conf] ComTxModeRepetitionPeriod
			$IF !LENGTH(ComTxMode_true.ComTxModeRepetitionPeriod[tx_mode_id])$
				$ComTxMode_true.ComTxModeRepetitionPeriod[tx_mode_id] = "0.0"$
			$ELSE$
$				// [NCOM037] ComTxModeRepetitionPeriodに設定された値がComTxTimeBaseより小さい場合はエラー
				$IF ComTxMode_true.ComTxModeRepetitionPeriod[tx_mode_id] < ComConfig.tx_time_base[com_config_id]$
					$ERROR$$FORMAT(_("ComTxModeRepetitionPeriod is less than ComTxTimeBase at `%1%\'."), ComTxMode_true[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
$			// [COM180_Conf] ComTxModeTimeOffset
			$IF !LENGTH(ComTxMode_true.ComTxModeTimeOffset[tx_mode_id])$
				$ComTxMode_true.ComTxModeTimeOffset[tx_mode_id] = "0.0"$
			$ELSE$
$				// [NCOM037] ComTxModeTimeOffsetに設定された値がComTxTimeBaseより小さい場合はエラー
				$IF ComTxMode_true.ComTxModeTimeOffset[tx_mode_id] < ComConfig.tx_time_base[com_config_id]$
					$ERROR$$FORMAT(_("ComTxModeTimeOffset is less than ComTxTimeBase at `%1%\'."), ComTxMode_true[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
$			// [COM178_Conf] ComTxModeTimePeriod
			$IF !LENGTH(ComTxMode_true.ComTxModeTimePeriod[tx_mode_id])$
				$ComTxMode_true.ComTxModeTimePeriod[tx_mode_id] = "0.0"$
			$ELSE$
$				// [NCOM037] ComTxModeTimePeriodに設定された値がComTxTimeBaseより小さい場合はエラー
				$IF ComTxMode_true.ComTxModeTimePeriod[tx_mode_id] < ComConfig.tx_time_base[com_config_id]$
					$ERROR$$FORMAT(_("ComTxModeTimePeriod is less than ComTxTimeBase at `%1%\'."), ComTxMode_true[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
		$END$
	$END$
	$FOREACH tx_mode_id ComTxMode_false.ID_LIST$
		$IF EQ(com_config_id, ComTxMode_false.config_ref_id[tx_mode_id])$
$			// [COM137_Conf] ComTxModeMode
				$IF !EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "DIRECT") && !EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "MIXED")
				&& !EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "NONE") && !EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "PERIODIC")$
				$ERROR$$FORMAT(_("ComTxModeMode should not be set `%1%\'. (%2%\)"),ComTxMode_false.ComTxModeMode[tx_mode_id] , ComTxIPdu.PARENT[ComTxMode_false.tx_ipdu_ref_id[tx_mode_id]])$$END$$DIE()$
			$END$
$			// [COM281_Conf] ComTxModeNumberOfRepetitions
			$IF !LENGTH(ComTxMode_false.ComTxModeNumberOfRepetitions[tx_mode_id])$
				$ComTxMode_false.ComTxModeNumberOfRepetitions[tx_mode_id] = 0$
			$END$
$			// [COM282_Conf] ComTxModeRepetitionPeriod
			$IF !LENGTH(ComTxMode_false.ComTxModeRepetitionPeriod[tx_mode_id])$
				$ComTxMode_false.ComTxModeRepetitionPeriod[tx_mode_id] = "0.0"$
			$ELSE$
$				// [NCOM037] ComTxModeRepetitionPeriodに設定された値がComTxTimeBaseより小さい場合はエラー
				$IF ComTxMode_false.ComTxModeRepetitionPeriod[tx_mode_id] < ComConfig.tx_time_base[com_config_id]$
					$ERROR$$FORMAT(_("ComTxModeRepetitionPeriod is less than ComTxTimeBase at `%1%\'."), ComTxMode_false[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
$			// [COM180_Conf] ComTxModeTimeOffset
			$IF !LENGTH(ComTxMode_false.ComTxModeTimeOffset[tx_mode_id])$
				$ComTxMode_false.ComTxModeTimeOffset[tx_mode_id] = "0.0"$
			$ELSE$
$				// [NCOM037] ComTxModeTimeOffsetに設定された値がComTxTimeBaseより小さい場合はエラー
				$IF ComTxMode_false.ComTxModeTimeOffset[tx_mode_id] < ComConfig.tx_time_base[com_config_id]$
					$ERROR$$FORMAT(_("ComTxModeTimeOffset is less than ComTxTimeBase at `%1%\'."), ComTxMode_false[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
$			// [COM178_Conf] ComTxModeTimePeriod
			$IF !LENGTH(ComTxMode_false.ComTxModeTimePeriod[tx_mode_id])$
				$ComTxMode_false.ComTxModeTimePeriod[tx_mode_id] = "0.0"$
			$ELSE$
$				// [NCOM037] ComTxModeTimePeriodに設定された値がComTxTimeBaseより小さい場合はエラー
				$IF ComTxMode_false.ComTxModeTimePeriod[tx_mode_id] < ComConfig.tx_time_base[com_config_id]$
					$ERROR$$FORMAT(_("ComTxModeTimePeriod is less than ComTxTimeBase at `%1%\'."), ComTxMode_false[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
		$END$
	$END$

$	/*
$	 * [COM344_Conf][NCOM029] シグナルの設定値チェック
$	 */
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
$		// [COM127_Conf] ComSignalType
		$IF EQ(ComSignal.ComSignalType[signal_id], "BOOLEAN")$
			$ComSignal.signal_type_str[signal_id] = "boolean"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8")$
			$ComSignal.signal_type_str[signal_id] = "uint8"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT16")$
			$ComSignal.signal_type_str[signal_id] = "uint16"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT32")$
			$ComSignal.signal_type_str[signal_id] = "uint32"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT8")$
			$ComSignal.signal_type_str[signal_id] = "sint8"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT16")$
			$ComSignal.signal_type_str[signal_id] = "sint16"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT32")$
			$ComSignal.signal_type_str[signal_id] = "sint32"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
			$ComSignal.signal_type_str[signal_id] = "uint8"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT32")$
			$ComSignal.signal_type_str[signal_id] = "float32"$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT64")$
			$ComSignal.signal_type_str[signal_id] = "float64"$
			$float64_flg = "TRUE"$
		$ELSE$
$			// [COM675] COMがサポートする型以外が指定されている場合はエラー
			$ERROR$$FORMAT(_("ComSignalType should not be set to `%1%\'."), ComSignal.ComSignalType[signal_id])$$END$$DIE()$
		$END$

$		// [COM158_Conf] ComBitSize
		$IF LENGTH(ComSignal.ComBitSize[signal_id])$
			$IF EQ(ComSignal.ComSignalType[signal_id], "BOOLEAN")$
$				// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
				$IF ComSignal.ComBitSize[signal_id] > 1$
					$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComSignalType is BOOLEAN."), ComSignal.ComBitSize[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8")$
$				// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
				$IF ComSignal.ComBitSize[signal_id] > 8$
					$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComSignalType is UINT8."), ComSignal.ComBitSize[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT16")$
$				// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
				$IF ComSignal.ComBitSize[signal_id] > 16$
					$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComSignalType is UINT16."), ComSignal.ComBitSize[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT32")$
$				// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
				$IF ComSignal.ComBitSize[signal_id] > 32$
					$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComSignalType is UINT32."), ComSignal.ComBitSize[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT8")$
$				// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
				$IF ComSignal.ComBitSize[signal_id] > 8$
					$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComSignalType is SINT8."), ComSignal.ComBitSize[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT16")$
$				// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
				$IF ComSignal.ComBitSize[signal_id] > 16$
					$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComSignalType is SINT16."), ComSignal.ComBitSize[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT32")$
$				// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
				$IF ComSignal.ComBitSize[signal_id] > 32$
					$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComSignalType is SINT32."), ComSignal.ComBitSize[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
$				// [NCOM021] ComSignalTypeがUINT8_NのシグナルにComBitSizeを設定した場合は警告
				$WARNING$$FORMAT("ComBitSize is not have to set value.")$$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT32")$
$				// [NCOM022]データ型がFLOAT32に設定されたシグナルのビットサイズが指定された場合は警告
				$WARNING$$FORMAT(_("FLOAT32 type signal doesn't have to set value to ComBitSize. (%1%\)"), ComSignal[signal_id])$$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT64")$
$				// [NCOM022]データ型がFLOAT64に設定されたシグナルのビットサイズが指定された場合は警告
				$WARNING$$FORMAT(_("FLOAT64 type signal doesn't have to set value to ComBitSize. (%1%\)"), ComSignal[signal_id])$$END$
			$END$
		$ELSE$
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				$ComSignal.ComBitSize[signal_id] = "COM_INVALID_UINT8"$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT32")$
				$ComSignal.ComBitSize[signal_id] = 32$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT64")$
				$ComSignal.ComBitSize[signal_id] = 64$
			$ELSE$
$				// [NCOM011] データ型がUINT8_N以外のシグナルにComBitSizeを設定していない場合はエラー
				$ERROR$$FORMAT(_("`%1%\' should set ComBitSize."), ComSignal[signal_id])$$END$$DIE()$
			$END$
		$END$

$		// [COM437_Conf] ComSignalLength
		$IF LENGTH(ComSignal.ComSignalLength[signal_id])$
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				$IF ComSignal.ComSignalLength[signal_id] == 0$
$					// [NCOM012] UINT8_N型のシグナルのComSingalLengthに0が設定された場合はエラー
					$ERROR$$FORMAT("ComSignalLength should not be set to 0.")$$END$$DIE()$
				$END$
			$ELSE$
$				// [NCOM023] UINT8_N以外のシグナルにComSignalLengthを指定した場合は警告
				$WARNING$$FORMAT(_("`%1%\' does not have to set ComSignalLength."), ComSignal[signal_id])$$END$
				$ComSignal.ComSignalLength[signal_id] = "COM_INVALID_UINT16"$
			$END$
		$ELSE$
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
$				// [NCOM012] データ型がUINT8_NのシグナルにComSignalLengthを設定していない場合はエラー
				$ERROR$$FORMAT(_("`%1%\' should be set ComSignalLength."), ComSignal[signal_id])$$END$$DIE()$
			$ELSE$
				$ComSignal.ComSignalLength[signal_id] = "COM_INVALID_UINT16"$
			$END$
		$END$

$		// [COM170_Conf] ComSignalInitValue
		$IF LENGTH(ComSignal.ComSignalInitValue[signal_id])$
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				$value_list = SPLIT(ComSignal.ComSignalInitValue[signal_id], " ")$
				$signal_length = ComSignal.ComSignalLength[signal_id]$
$				// [NCOM013] データ型がUINT8_Nのシグナルに設定されたComSignalInitValueのデータ数がComSignalLengthと一致しない場合はエラー
				$IF signal_length != LENGTH(value_list)$
					$ERROR$$FORMAT(_("ComSignalInitValue and ComSignalLength is inconsistent at `%1%\'."), ComSignal[signal_id])$$END$$DIE()$
				$END$
			$ELIF (EQ(ComSignal.ComSignalType[signal_id], "UINT8") || EQ(ComSignal.ComSignalType[signal_id], "UINT16")
					|| EQ(ComSignal.ComSignalType[signal_id], "UINT32") || EQ(ComSignal.ComSignalType[signal_id], "SINT8")
					|| EQ(ComSignal.ComSignalType[signal_id], "SINT16") || EQ(ComSignal.ComSignalType[signal_id], "SINT32"))$
$				// [NCOM038] 整数型のシグナルに設定されたComSignalInitValueの値がComBitSizeのレンジに収まっていない場合はエラー
				$SIGNAL_RANGE_CHECK(ComSignal.ComSignalInitValue[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComBitSize[signal_id], "ComSignalInitValue")$
			$END$
		$ELSE$
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
$				// ComSignalLengthにデータ数を合わせた値で補完
				$value_str = "0"$
				$FOREACH index RANGE(1, signal_length - 1)$
					$value_str = CONCAT(value_str, " 0")$
				$END$
				$ComSignal.ComSignalInitValue[signal_id] = value_str$
			$ELSE$
				$ComSignal.ComSignalInitValue[signal_id] = 0$
			$END$
		$END$

$		// [COM391_Conf] ComSignalDataInvalidValue
		$IF LENGTH(ComSignal.ComSignalDataInvalidValue[signal_id])$
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
$				// [NCOM014] データ型がUINT8_Nのシグナルに設定されたComSignalDataInvalidValueのデータ数がComSignalLengthと一致しない場合はエラー
				$value_list = SPLIT(ComSignal.ComSignalDataInvalidValue[signal_id], " ")$
				$IF !EQ(signal_length, LENGTH(value_list))$
					$ERROR$$FORMAT(_("ComSignalDataInvalidValue and ComSignalLength is inconsistent at `%1%\'."), ComSignal[signal_id])$$END$$DIE()$
				$END$
			$ELIF (EQ(ComSignal.ComSignalType[signal_id], "UINT8") || EQ(ComSignal.ComSignalType[signal_id], "UINT16")
					|| EQ(ComSignal.ComSignalType[signal_id], "UINT32") || EQ(ComSignal.ComSignalType[signal_id], "SINT8")
					|| EQ(ComSignal.ComSignalType[signal_id], "SINT16") || EQ(ComSignal.ComSignalType[signal_id], "SINT32"))$
$				// [NCOM038] 整数型のシグナルに設定されたComSignalDataInvalidValueの値がComBitSizeのレンジに収まっていない場合はエラー
				$SIGNAL_RANGE_CHECK(ComSignal.ComSignalDataInvalidValue[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComBitSize[signal_id], "ComSignalDataInvalidValue")$
			$END$
		$END$

$		// [COM157_Conf] ComSignalEndianness
		$IF EQ(ComSignal.ComSignalEndianness[signal_id], "LITTLE_ENDIAN") || EQ(ComSignal.ComSignalEndianness[signal_id], "BIG_ENDIAN")$
$			// [COM553] UINT8_NのシグナルのComSignalEndiannessにOPAQUEが指定されていない場合はエラー
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				$ERROR$$FORMAT(_("`%1%\' should set OPAQUE to ComSignalEndianness."), ComSignal[signal_id])$$END$$DIE()$
			$END$
		$ELIF EQ(ComSignal.ComSignalEndianness[signal_id], "OPAQUE")$
$			// [NCOM026] UINT8_N以外のシグナルのComSignalEndiannessにOPAQUEが指定されている場合はエラー
			$IF !EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				$ERROR$$FORMAT("ComSignalEndianness should not be set OPAQUE.")$$END$$DIE()$
			$END$
		$ELSE$
			$ERROR$$FORMAT("ComSignalEndianness should be set LITTLE_ENDIAN or BIG_ENDIAN or OPAQUE.")$$END$$DIE()$
		$END$

$		// [COM259_Conf] ComBitPosition
		$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
$			// [NCOM019] データ型がUINT8_NのシグナルのComBitPositionが8の倍数でない場合はエラー
			$IF (ComSignal.ComBitPosition[signal_id] % 8) != 0$
				$ERROR$$FORMAT(_("ComBitPosition is not the correct value. `%1%\' is UINT8_N."), ComSignal[signal_id])$$END$$DIE()$
			$END$
		$END$
$		// ComSignalEndiannessがBIG_ENDIANの場合はComBitPosition(MSB)をLSBに変換
		$IF EQ (ComSignal.ComSignalEndianness[signal_id], "BIG_ENDIAN") && (ComSignal.ComBitSize[signal_id] > 1)$
			$ComSignal.lsb[signal_id] = MSB2LSB(ComSignal.ComBitPosition[signal_id], ComSignal.ComBitSize[signal_id])$
		$ELSE$
			$ComSignal.lsb[signal_id] = ComSignal.ComBitPosition[signal_id]$
		$END$

$		// [COM232_Conf] ComTransferProperty
		$IF LENGTH(ComSignal.ComTransferProperty[signal_id])$
			$IF !EQ(ComSignal.ComTransferProperty[signal_id], "PENDING")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_WITHOUT_REPETITION")$
				$ERROR$$FORMAT(_("ComTransferProperty should not be set `%1%\'. (%2%\)"),ComSignal.ComTransferProperty[signal_id] , ComSignal[signal_id])$$END$$DIE()$
			$END$
$			// [COM762] ComBitSizeが0のシグナルのComTransferPropertyにTRIGGERED_ON_CHANGEかTRIGGERED_ON_CHANGE_WITHOUT_REPETITIONを設定した場合はエラー
			$IF EQ(ComSignal.ComBitSize[signal_id], "0") && (EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE") || EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION"))$
				$ERROR$$FORMAT(_("ComBitSize 0 signal should NOT set 'TRIGGERED_ON_CHANGE' or 'TRIGGERED_ON_CHANGE_WITHOUT_REPETITION'. (%1%\)"),ComSignal[signal_ref_id])$$END$$DIE()$
			$END$
		$ELSE$
$			// [NCOM042] 送信シグナルにComTransferPropertyが指定されていない場合はエラー
			$IF EQ(ComSignal.direction[signal_id], "SEND")$
				$ERROR$$FORMAT(_("Send Signal should be set value to ComTransferProperty. (%1%\)"), signal_id)$$END$$DIE()$
			$END$
			$ComSignal.ComTransferProperty[signal_id] = "INVALID_UINT8"$
		$END$

$		// [COM314_Conf] ComDataInvalidAction
		$IF LENGTH(ComSignal.ComDataInvalidAction[signal_id])$
			$IF !EQ(ComSignal.ComDataInvalidAction[signal_id], "NOTIFY") && !EQ(ComSignal.ComDataInvalidAction[signal_id], "REPLACE")$
				$ERROR$$FORMAT(_("ComDataInvalidAction should not be set `%1%\'. (%2%\)"),ComSignal.ComDataInvalidAction[signal_id] , ComSignal[signal_id])$$END$$DIE()$
			$END$
		$ELSE$
			$ComSignal.ComDataInvalidAction[signal_id] = "INVALID_UINT8"$
		$END$

$		// [COM412_Conf] ComRxDataTimeoutAction
		$IF LENGTH(ComSignal.ComRxDataTimeoutAction[signal_id])$
			$IF !EQ(ComSignal.ComRxDataTimeoutAction[signal_id], "NONE") && !EQ(ComSignal.ComRxDataTimeoutAction[signal_id], "REPLACE")$
				$ERROR$$FORMAT(_("ComRxDataTimeoutAction should not be set `%1%\'. (%2%\)"),ComSignal.ComRxDataTimeoutAction[signal_id] , ComSignal[signal_id])$$END$$DIE()$
			$END$
		$ELSE$
$			// [COM500]ComRxDataTimeoutActionが省略された場合はNONEと同等
			$ComSignal.ComRxDataTimeoutAction[signal_id] = "NONE"$
		$END$

$		// シグナルがIPDUバッファの外に配置されないかチェック
		$lsb = ComSignal.lsb[signal_id]$
		$signal_length = ComSignal.ComSignalLength[signal_id]$
		$signal_size = ComSignal.ComBitSize[signal_id]$
		$ipdu_id = ComSignal.ipdu_ref[signal_id]$
		$pdu_length = ComIPdu.pdu_length[ipdu_id]$
		$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
			$IF ((lsb + (signal_length * 8)) > (pdu_length * 8))$
$				// [NCOM015]IPDUバッファ内にシグナルが収らない場合はエラー
				$ERROR$$FORMAT(_("`%1%\' is not fit in IPDU buffer."), ComSignal[signal_id])$$END$$DIE()$
			$END$
		$ELSE$
			$IF EQ(ComSignal.ComSignalEndianness[signal_id], "LITTLE_ENDIAN")$
				$IF ((lsb + signal_size) > (pdu_length * 8))$
$					// [NCOM016]IPDUバッファ内にシグナルが収らない場合はエラー
					$ERROR$$FORMAT(_("`%1%\' is not fit in IPDU buffer."), ComSignal[signal_id])$$END$$DIE()$
				$END$
			$ELIF EQ(ComSignal.ComSignalEndianness[signal_id], "BIG_ENDIAN")$
				$IF (((lsb / 8) * 8) + (8 - (lsb % 8))) < signal_size$
$					// [NCOM017]IPDUバッファ内にシグナルが収らない場合はエラー
					$ERROR$$FORMAT(_("`%1%\' is not fit in IPDU buffer."), ComSignal[signal_id])$$END$$DIE()$
				$END$
				$IF (lsb > ((pdu_length * 8) - 1))$
$					// [NCOM018]IPDUバッファ内にシグナルが収らない場合はエラー
					$ERROR$$FORMAT(_("`%1%\' is not fit in IPDU buffer."), ComSignal[signal_id])$$END$$DIE()$
				$END$
			$END$
		$END$

$		// [COM263_Conf][COM183_Conf][COM552_Conf]
$		// デッドラインモニタリング関連のパラメータチェック
		$IF EQ(ComSignal.direction[signal_id], "SEND")$
			$IF ComSignal.timeout[signal_id] != 0$
				$ComSignal.timeout[signal_id] = ComIPdu.timeout_min[ComSignal.ipdu_ref[signal_id]]$
			$END$
			$IF ComSignal.first_timeout[signal_id] != 0$
				$ComSignal.first_timeout[signal_id] = ComIPdu.first_timeout_min[ComSignal.ipdu_ref[signal_id]]$
			$END$
		$ELIF EQ(ComSignal.direction[signal_id], "RECEIVE")$
			$IF (ComSignal.timeout[signal_id] != 0) && !LENGTH(ComSignal.ComUpdateBitPosition[signal_id])$
				$ComSignal.timeout[signal_id] = ComIPdu.timeout_min[ComSignal.ipdu_ref[signal_id]]$
			$END$
			$IF (ComSignal.first_timeout[signal_id] != 0) && !LENGTH(ComSignal.ComUpdateBitPosition[signal_id])$
				$ComSignal.first_timeout[signal_id] = ComIPdu.first_timeout_min[ComSignal.ipdu_ref[signal_id]]$
			$END$
		$END$
		$IF !LENGTH(ComSignal.ComTimeoutNotification[signal_id])$
			$IF ComSignal.timeout[signal_id] != 0$
$				// タイムアウト通知用コールバックが設定されていないが，タイムアウト値が設定されている場合は警告
				$WARNING$$FORMAT(_("ComTimeoutNotification is omit. (%1%\)"), ComSignal[signal_id])$$END$
			$END$
			$ComSignal.ComTimeoutNotification[signal_id] = "NULL_PTR"$
		$ELSE$
			$IF ComSignal.timeout[signal_id] == 0$
$				// タイムアウト通知用コールバックが設定されているが，タイムアウト値が0の場合は警告
				$WARNING$$FORMAT(_("ComTimeout is omit. ComTimeoutNotification will not be used. (%1%\)"), ComSignal[signal_id])$$END$
			$END$
$			// [COM402] 関数名はC言語で扱える文字列でなければならない
			$FUNC_NAME_CHECK(ComSignal.ComTimeoutNotification[signal_id])$
		$END$

$		// [COM257_Conf] ComUpdateBitPosition
		$IF !LENGTH(ComSignal.ComUpdateBitPosition[signal_id])$
			$ComSignal.ComUpdateBitPosition[signal_id] = "COM_INVALID_UINT16"$
		$ELSE$
$			// [COM310] 送信モードがDIRECTかMIXEDのIPDUがComTxModeNumberOfRepetitionsに1以上の値を設定している場合，ComUpdateBitPositionを設定してはならない
			$FOREACH tx_mode_id ComTxMode_true.ID_LIST$
				$IF EQ(ComSignal.ipdu_ref[signal_id], ComTxIPdu.PARENT[ComTxModeTrue.PARENT[ComTxMode_true.PARENT[tx_mode_id]]])$
					$IF (EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "DIRECT") || EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "MIXED")) && (ComTxMode_true.ComTxModeNumberOfRepetitions[tx_mode_id] > 1)$
						$ERROR$$FORMAT(_("DIRECT or MIXED mode TxIPDU with ComTxModeNumberOfRepetitions greater or equal 1 should not have ComUpdateBitPosition. (%1%\, %2%\)"), ComSignal.ipdu_ref[signal_id], ComSignal[signal_id])$$END$$DIE()$
					$END$
				$END$
			$END$
			$FOREACH tx_mode_id ComTxMode_false.ID_LIST$
				$IF EQ(ComSignal.ipdu_ref[signal_id], ComTxIPdu.PARENT[ComTxModeFalse.PARENT[ComTxMode_false.PARENT[tx_mode_id]]])$
					$IF (EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "DIRECT") || EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "MIXED")) && (ComTxMode_false.ComTxModeNumberOfRepetitions[tx_mode_id] > 1)$
						$ERROR$$FORMAT(_("DIRECT or MIXED mode TxIPDU with ComTxModeNumberOfRepetitions greater or equal 1 should not have ComUpdateBitPosition. (%1%\, %2%\)"), ComSignal.ipdu_ref[signal_id], ComSignal[signal_id])$$END$$DIE()$
					$END$
				$END$
			$END$
		$END$

$		// [COM499_Conf] ComErrorNotification
		$IF LENGTH(ComSignal.ComErrorNotification[signal_id])$
$			// [COM402] 関数名はC言語で扱える文字列でなければならない
			$FUNC_NAME_CHECK(ComSignal.ComErrorNotification[signal_id])$
		$ELSE$
			$ComSignal.ComErrorNotification[signal_id] = "NULL_PTR"$
		$END$

$		// [COM315_Conf] ComInvalidNotification
		$IF LENGTH(ComSignal.ComInvalidNotification[signal_id])$
$			// [COM402] 関数名はC言語で扱える文字列でなければならない
			$FUNC_NAME_CHECK(ComSignal.ComInvalidNotification[signal_id])$
		$ELSE$
			$ComSignal.ComInvalidNotification[signal_id] = "NULL_PTR"$
		$END$

$		// [COM498_Conf] ComNotification
		$IF LENGTH(ComSignal.ComNotification[signal_id])$
$			// [COM402] 関数名はC言語で扱える文字列でなければならない
			$FUNC_NAME_CHECK(ComSignal.ComNotification[signal_id])$
		$ELSE$
			$ComSignal.ComNotification[signal_id] = "NULL_PTR"$
		$END$
	$END$

$	/*
$	 * [COM339_Conf]フィルタの設定値チェック
$	 */
	$FOREACH filter_id ComConfig.filter_list[com_config_id]$
$		// [COM146_Conf] ComFilterAlgorithm
		$IF !EQ(ComFilter.ComFilterAlgorithm[filter_id], "ALWAYS")
			&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEVER")
			&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_EQUALS_X")
			&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_X")
			&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")
			&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN")
			&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE")
			&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
$			// ComFilterAlgorithmに適切な値が設定されてない場合はエラー
			$ERROR$$FORMAT(_("ComFilterAlgorithm should not be set `%1%\'. (%2%\)"),ComFilter.ComFilterAlgorithm[filter_id] , ComFilter[filter_id])$$END$$DIE()$
		$END$
		$signal_ref_id = ComFilter.PARENT[filter_id]$
		$ComFilter.config_ref_id[filter_id] = com_config_id$
		$ComSignal.filter_ref_id[signal_ref_id] = filter_id$
		$signal_type = ComSignal.ComSignalType[signal_ref_id]$
		$IF EQ(signal_type, "BOOLEAN")$
$			// [COM439] BOOLEANのシグナルにNEW_IS_WITHINまたはNEW_IS_OUTSIDEが設定された場合はエラー
			$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE")$
				$ERROR$$FORMAT(_("BOOLEAN type signal should NOT set 'NEW_IS_WITHIN' or 'NEW_IS_OUTSIDE' to ComFilterAlgorithm. (%1%\)"),ComSignal[signal_ref_id])$$END$$DIE()$
			$END$
		$END$
		$IF EQ(signal_type, "UINT8_N")$
$			// [COM380] UINT8_NのシグナルのComFilterAlgorithmにALWAYSまたはNEVERが設定されていない場合はエラー
			$IF !EQ(ComFilter.ComFilterAlgorithm[filter_id], "ALWAYS") && !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEVER")$
				$ERROR$$FORMAT(_("UINT8_N type signal should set 'ALWAYS' or 'NEVER' to ComFilterAlgorithm. (%1%\)"),ComSignal[signal_ref_id])$$END$$DIE()$
			$END$
		$END$
$		// [COM319] FLOAT32またはFLOAT64のシグナルにComFilterが設定されている場合はエラー
		$IF EQ(signal_type, "FLOAT32") || EQ(signal_type, "FLOAT64")$
			$ERROR$$FORMAT(_("FLOAT32 type or FLOAT64 type signal should NOT have ComFilter container. (%1%\)"),ComSignal[signal_ref_id])$$END$$DIE()$
		$END$
$		// [COM764] ComBitSizeが0のシグナルのComFilterAlgorithmがMASKED_NEW_DIFFERS_MASKED_OLDの場合はエラー
		$IF EQ(ComSignal.ComBitSize[signal_ref_id], "0") && EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
			$ERROR$$FORMAT(_("ComBitSize 0 signal should NOT set 'MASKED_NEW_DIFFERS_MASKED_OLD'. (%1%\)"),ComSignal[signal_ref_id])$$END$$DIE()$
		$END$

$		// [COM235_Conf] ComFilterMask
		$IF !LENGTH(ComFilter.ComFilterMask[filter_id])$
			$ComFilter.ComFilterMask[filter_id] = 0$
		$END$
$		// [COM317_Conf] ComFilterMax
		$IF !LENGTH(ComFilter.ComFilterMax[filter_id])$
			$ComFilter.ComFilterMax[filter_id] = 0$
		$END$
$		// [COM318_Conf] ComFilterMin
		$IF !LENGTH(ComFilter.ComFilterMin[filter_id])$
			$ComFilter.ComFilterMin[filter_id] = 0$
		$END$
$		// [COM313_Conf] ComFilterOffset
		$IF !LENGTH(ComFilter.ComFilterOffset[filter_id])$
			$ComFilter.ComFilterOffset[filter_id] = 0$
		$END$
$		// [COM312_Conf] ComFilterPeriod
		$IF !LENGTH(ComFilter.ComFilterPeriod[filter_id])$
			$ComFilter.ComFilterPeriod[filter_id] = 0$
		$END$
$		// [COM147_Conf] ComFilterX
		$IF !LENGTH(ComFilter.ComFilterX[filter_id])$
			$ComFilter.ComFilterX[filter_id] = 0$
		$END$

$		// [COM535] ComFilterAlgorithmがONE_EVERY_NのときにComFilterOffsetがComFilterPeriodより大きい場合はエラー
		$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N") && (ComFilter.ComFilterOffset[filter_id] > ComFilter.ComFilterPeriod[filter_id])$
			$ERROR$$FORMAT(_("Because ComFilterAlgorithm is ONE_EVERY_N, ComFilterOffset should be set to a value lesser than ComFilterPeriod'. (%1%\)"),ComFilter[filter_id])$$END$$DIE()$
		$END$

$		// ComFilterAlgorithmがNEW_IS_OUTSIDEまたはNEW_IS_WITHINであるフィルタに対するチェック
		$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN")$
$			// [NCOM043][NCOM044][NCOM045] ComFilterMin，ComFilterMaxが所属シグナルの型の範囲外の場合はエラー
			$IF EQ(signal_type, "UINT8")$
				$IF (ComFilter.ComFilterMin[filter_id] < 0) || (255 < ComFilter.ComFilterMin[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT8, ComFilterMin(%2%\) should be in the range from 0 to 255. (%1%\)"), signal_ref_id, ComFilter.ComFilterMin[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterMax[filter_id] < 0) || (255 < ComFilter.ComFilterMax[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT8, ComFilterMax(%2%\) should be in the range from 0 to 255. (%1%\)"), signal_ref_id, ComFilter.ComFilterMax[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT16")$
				$IF (ComFilter.ComFilterMin[filter_id] < 0) || (65535 < ComFilter.ComFilterMin[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT16, ComFilterMin(%2%\) should be in the range from 0 to 65535. (%1%\)"), signal_ref_id, ComFilter.ComFilterMin[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterMax[filter_id] < 0) || (65535 < ComFilter.ComFilterMax[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT16, ComFilterMax(%2%\) should be in the range from 0 to 65535. (%1%\)"), signal_ref_id, ComFilter.ComFilterMax[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT32")$
				$IF (ComFilter.ComFilterMin[filter_id] < 0) || (4294967295 < ComFilter.ComFilterMin[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT32, ComFilterMin(%2%\) should be in the range from 0 to 4294967295. (%1%\)"), signal_ref_id, ComFilter.ComFilterMin[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterMax[filter_id] < 0) || (4294967295 < ComFilter.ComFilterMax[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT32, ComFilterMax(%2%\) should be in the range from 0 to 4294967295. (%1%\)"), signal_ref_id, ComFilter.ComFilterMax[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT8")$
				$IF (ComFilter.ComFilterMin[filter_id] < -128) || (127 < ComFilter.ComFilterMin[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT8, ComFilterMin(%2%\) should be in the range from -128 to 127. (%1%\)"), signal_ref_id, ComFilter.ComFilterMin[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterMax[filter_id] < -128) || (127 < ComFilter.ComFilterMax[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT8, ComFilterMax(%2%\) should be in the range from -128 to 127. (%1%\)"), signal_ref_id, ComFilter.ComFilterMax[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT16")$
				$IF (ComFilter.ComFilterMin[filter_id] < -32768) || (32767 < ComFilter.ComFilterMin[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT16, ComFilterMin(%2%\) should be in the range from -32768 to 32767. (%1%\)"), signal_ref_id, ComFilter.ComFilterMin[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterMax[filter_id] < -32768) || (32767 < ComFilter.ComFilterMax[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT16, ComFilterMax(%2%\) should be in the range from -32768 to 32767. (%1%\)"), signal_ref_id, ComFilter.ComFilterMax[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT32")$
				$IF (ComFilter.ComFilterMin[filter_id] < -2147483648) || (2147483647 < ComFilter.ComFilterMin[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT32, ComFilterMin(%2%\) should be in the range from -2147483648 to 2147483647. (%1%\)"), signal_ref_id, ComFilter.ComFilterMin[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterMax[filter_id] < -2147483648) || (2147483647 < ComFilter.ComFilterMax[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT32, ComFilterMax(%2%\) should be in the range from -2147483648 to 2147483647. (%1%\)"), signal_ref_id, ComFilter.ComFilterMax[filter_id])$$END$$DIE()$
				$END$
			$END$
$			// [NCOM046] ComFilterMinがComFilterMaxよりも大きい場合はエラー
			$IF (ComFilter.ComFilterMin[filter_id] > ComFilter.ComFilterMax[filter_id])$
				$ERROR$$FORMAT(_("ComFilterMin should be set to a value lesser than ComFilterMax'. (%1%\)"), filter_id)$$END$$DIE()$
			$END$
		$END$
$		// ComFilterAlgorithmがCOM_MASKED_NEW_DIFFERS_XまたはCOM_MASKED_NEW_EQUALS_Xであるフィルタに対するチェック
		$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN")$
$			// [NCOM047][NCOM048] ComFilterMask，ComFilterXが所属シグナルの型の範囲外の場合はエラー
			$IF EQ(signal_type, "BOOLEAN")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (1 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is BOOLEAN, ComFilterMask(%2%\) should be in the range from 0 to 1. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterX[filter_id] < 0) || (1 < ComFilter.ComFilterX[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT8, ComFilterX(%2%\) should be in the range from 0 to 1. (%1%\)"), signal_ref_id, ComFilter.ComFilterX[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT8")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (255 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT8, ComFilterMask(%2%\) should be in the range from 0 to 255. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterX[filter_id] < 0) || (255 < ComFilter.ComFilterX[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT8, ComFilterX(%2%\) should be in the range from 0 to 255. (%1%\)"), signal_ref_id, ComFilter.ComFilterX[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT16")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (65535 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT16, ComFilterMask(%2%\) should be in the range from 0 to 65535. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterX[filter_id] < 0) || (65535 < ComFilter.ComFilterX[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT16, ComFilterX(%2%\) should be in the range from 0 to 65535. (%1%\)"), signal_ref_id, ComFilter.ComFilterX[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT32")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (4294967295 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT32, ComFilterMask(%2%\) should be in the range from 0 to 4294967295. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterX[filter_id] < 0) || (4294967295 < ComFilter.ComFilterX[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT32, ComFilterX(%2%\) should be in the range from 0 to 4294967295. (%1%\)"), signal_ref_id, ComFilter.ComFilterX[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT8")$
				$IF (ComFilter.ComFilterMask[filter_id] < -128) || (127 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT8, ComFilterMask(%2%\) should be in the range from -128 to 127. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterX[filter_id] < -128) || (127 < ComFilter.ComFilterX[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT8, ComFilterX(%2%\) should be in the range from -128 to 127. (%1%\)"), signal_ref_id, ComFilter.ComFilterX[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT16")$
				$IF (ComFilter.ComFilterMask[filter_id] < -32768) || (32767 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT16, ComFilterMask(%2%\) should be in the range from -32768 to 32767. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterX[filter_id] < -32768) || (32767 < ComFilter.ComFilterX[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT16, ComFilterX(%2%\) should be in the range from -32768 to 32767. (%1%\)"), signal_ref_id, ComFilter.ComFilterX[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT32")$
				$IF (ComFilter.ComFilterMask[filter_id] < -2147483648) || (2147483647 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT32, ComFilterMask(%2%\) should be in the range from -2147483648 to 2147483647. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
				$IF (ComFilter.ComFilterX[filter_id] < -2147483648) || (2147483647 < ComFilter.ComFilterX[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT32, ComFilterX(%2%\) should be in the range from -2147483648 to 2147483647. (%1%\)"), signal_ref_id, ComFilter.ComFilterX[filter_id])$$END$$DIE()$
				$END$
			$END$
		$END$
$		// ComFilterAlgorithmがCOM_MASKED_NEW_DIFFERS_MASKED_OLDであるフィルタに対するチェック
		$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "COM_MASKED_NEW_DIFFERS_MASKED_OLD")$
$			// [NCOM047] ComFilterMaskが所属シグナルの型の範囲外の場合はエラー
			$IF EQ(signal_type, "BOOLEAN")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (1 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is BOOLEAN, ComFilterMask(%2%\) should be in the range from 0 to 1. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT8")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (255 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT8, ComFilterMask(%2%\) should be in the range from 0 to 255. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT16")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (65535 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT16, ComFilterMask(%2%\) should be in the range from 0 to 65535. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "UINT32")$
				$IF (ComFilter.ComFilterMask[filter_id] < 0) || (4294967295 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is UINT32, ComFilterMask(%2%\) should be in the range from 0 to 4294967295. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT8")$
				$IF (ComFilter.ComFilterMask[filter_id] < -128) || (127 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT8, ComFilterMask(%2%\) should be in the range from -128 to 127. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT16")$
				$IF (ComFilter.ComFilterMask[filter_id] < -32768) || (32767 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT16, ComFilterMask(%2%\) should be in the range from -32768 to 32767. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
			$ELIF EQ(signal_type, "SINT32")$
				$IF (ComFilter.ComFilterMask[filter_id] < -2147483648) || (2147483647 < ComFilter.ComFilterMask[filter_id])$
					$ERROR$$FORMAT(_("Because ComSignalType is SINT32, ComFilterMask(%2%\) should be in the range from -2147483648 to 2147483647. (%1%\)"), signal_ref_id, ComFilter.ComFilterMask[filter_id])$$END$$DIE()$
				$END$
			$END$
		$END$
	$END$

$	// [NCOM041] ComFilterAlgorithmに従ったComTxModeTrueとComTxModeFalseのチェック
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
$		// ComFilterの有無，ComFilterAlgorithmをチェック
		$filter_cnt = 0$
		$all_always_flg = "true"$
		$all_never_flg = "true"$
		$FOREACH signal_id ComIPdu.ComIPduSignalRef[ipdu_id]$
			$FOREACH filter_id ComConfig.filter_list[com_config_id]$
				$IF EQ(signal_id, ComFilter.PARENT[filter_id])$
					$filter_cnt = filter_cnt + 1$
					$IF !EQ(ComFilter.ComFilterAlgorithm[filter_id], "ALWAYS")$
						$all_always_flg = "false"$
					$END$
					$IF !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEVER")$
						$all_never_flg = "false"$
					$END$
				$END$
			$END$
		$END$
$		// 対象となるComTxIPduのIDを取得
		$tx_ipdu_ref_id = ""$
		$FOREACH tx_ipdu_id ComTxIPdu.ID_LIST$
			$IF EQ(ipdu_id, ComTxIPdu.PARENT[tx_ipdu_id])$
				$tx_ipdu_ref_id = tx_ipdu_id$
			$END$
		$END$
		$IF !EQ(tx_ipdu_ref_id, "")$
$			// フィルタを使用しない場合(フィルタありのシグナルが1つも存在しない)
			$IF filter_cnt == 0$
$				// [COM677] TMS判定結果は常にtrueとなるため，ComTxModeTrueは必須
				$IF !LENGTH(ComTxIPdu.tx_mode_true_ref_id[tx_ipdu_ref_id])$
					$ERROR$$FORMAT(_("ComTxModeTrue should be set. ComIPdu has no ComFilter. (%1%\)"), ipdu_id)$$END$$DIE()$
				$END$
$				// [COM677] TMS判定結果は常にtrueとなるため，ComTxModeFalseは不要
				$IF LENGTH(ComTxIPdu.tx_mode_false_ref_id[tx_ipdu_ref_id])$
					$WARNING$$FORMAT(_("ComTxModeFalse will not be used. ComIPdu has no ComFilter. (%1%\)"), ipdu_id)$$END$
				$END$
$			// フィルタを使用する場合(フィルタありのシグナルが1つでも存在する)
			$ELSE$
$				// フィルタアルゴリズムがすべてALWAYSの場合
				$IF IS_TRUE(all_always_flg)$
$					// TMS判定結果は常にtrueとなるため，ComTxModeTrueは必須
					$IF !LENGTH(ComTxIPdu.tx_mode_true_ref_id[tx_ipdu_ref_id])$
						$ERROR$$FORMAT(_("ComTxModeTrue should be set. ComFilterAlgorithm is set only `ALWAYS'. (%1%\)"), ipdu_id)$$END$$DIE()$
					$END$
$					// TMS判定結果は常にtrueとなるため，ComTxModeFalseは不要
					$IF LENGTH(ComTxIPdu.tx_mode_false_ref_id[tx_ipdu_ref_id])$
						$WARNING$$FORMAT(_("ComTxModeFalse will not be used. ComFilterAlgorithm is set only `ALWAYS'. (%1%\)"), ipdu_id)$$END$
					$END$
$				// フィルタアルゴリズムがすべてNEVERの場合
				$ELIF IS_TRUE(all_never_flg)$
$					// TMS判定結果は常にfalseとなるため，ComTxModeTrueは不要
					$IF LENGTH(ComTxIPdu.tx_mode_true_ref_id[tx_ipdu_ref_id])$
						$WARNING$$FORMAT(_("ComTxModeTrue will not be used. ComFilterAlgorithm is set only `NEVER'. (%1%\)"), ipdu_id)$$END$
					$END$
$					// TMS判定結果は常にfalseとなるため，ComTxModeFalseは必須
					$IF !LENGTH(ComTxIPdu.tx_mode_false_ref_id[tx_ipdu_ref_id])$
						$ERROR$$FORMAT(_("ComTxModeFalse should be set. ComFilterAlgorithm is set only `NEVER'. (%1%\)"), ipdu_id)$$END$$DIE()$
					$END$
$				// 複数のフィルタアルゴリズムが混在している場合
				$ELSE$
					$IF !LENGTH(ComTxIPdu.tx_mode_true_ref_id[tx_ipdu_ref_id]) || !LENGTH(ComTxIPdu.tx_mode_false_ref_id[tx_ipdu_ref_id])$
						$ERROR$$FORMAT(_("ComTxModeTrue and ComTxModeFalse should be set. (%1%\)"), ipdu_id)$$END$$DIE()$
					$END$
				$END$
			$END$
		$END$
	$END$

$	// [COM732] コールバック・コールアウトに指定した関数名がCom_<ショートネーム>と一致した場合はエラー
	$name_list = {}$
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
		$name_list = APPEND(name_list, CONCAT("Com_", signal_id))$
	$END$
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
		$name_list = APPEND(name_list, CONCAT("Com_", ipdu_id))$
	$END$
	$FOREACH ipdu_g_id ComConfig.ipdu_g_list[com_config_id]$
		$name_list = APPEND(name_list, CONCAT("Com_", ipdu_g_id))$
	$END$
	$FOREACH name_id name_list$
		$FOREACH signal_id ComConfig.signal_list[com_config_id]$
			$IF EQ(name_id, ComSignal.ComNotification[signal_id])$
				$ERROR$$FORMAT(_("ComNotification should not be matched 'Com_<short name>'. (%1%\)"), ComSignal[signal_id])$$END$$DIE()$
			$END$
			$IF EQ(name_id, ComSignal.ComErrorNotification[signal_id])$
				$ERROR$$FORMAT(_("ComErrorNotification should not be matched 'Com_<short name>'. (%1%\)"), ComSignal[signal_id])$$END$$DIE()$
			$END$
			$IF EQ(name_id, ComSignal.ComTimeoutNotification[signal_id])$
				$ERROR$$FORMAT(_("ComTimeoutNotification should not be matched 'Com_<short name>'. (%1%\)"), ComSignal[signal_id])$$END$$DIE()$
			$END$
			$IF EQ(name_id, ComSignal.ComInvalidNotification[signal_id])$
				$ERROR$$FORMAT(_("ComInvalidNotification should not be matched 'Com_<short name>'. (%1%\)"), ComSignal[signal_id])$$END$$DIE()$
			$END$
		$END$
		$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
			$IF EQ(name_id, ComIPdu.ComIPduCallout[ipdu_id])$
				$ERROR$$FORMAT(_("ComIPduCallout should not be matched 'Com_<short name>'. (%1%\)"), ComIPdu[ipdu_id])$$END$$DIE()$
			$END$
		$END$
	$END$

$	// IPDUバッファのオーバーラップチェック
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
		$buffer_list = {}$
		$pdu_length = ComIPdu.pdu_length[ipdu_id]$
		$FOREACH index RANGE(0, pdu_length*8 - 1)$
			$buffer_list.bit[index] = "0"$
		$END$
$		// [COM102] シグナル同士がオーバーラップした場合はエラー
		$FOREACH signal_ref_id ComIPdu.ComIPduSignalRef[ipdu_id]$
			$bit_position = ComSignal.lsb[signal_ref_id]$
			$IF EQ(ComSignal.ComSignalType[signal_ref_id], "UINT8_N")$
				$signal_length = ComSignal.ComSignalLength[signal_ref_id]$
				$FOREACH index RANGE(1, signal_length * 8)$
					$IF EQ(buffer_list.bit[bit_position], "1")$
						$ERROR$$FORMAT(_("ComSignal are not allowed to overlap each other. (%1%\, %2%\)"), ComIPdu[ipdu_id], ComSignal[signal_ref_id])$$END$$DIE()$
					$ELSE$
						$buffer_list.bit[bit_position] = "1"$
					$END$
					$bit_position = bit_position + 1$
				$END$
			$ELSE$
				$signal_size = ComSignal.ComBitSize[signal_ref_id]$
				$IF EQ(ComSignal.ComSignalEndianness[signal_ref_id], "LITTLE_ENDIAN")$
					$FOREACH index RANGE(1, signal_size)$
						$IF EQ(buffer_list.bit[bit_position], "1")$
							$ERROR$$FORMAT(_("ComSignal are not allowed to overlap each other. (%1%\, %2%\)"), ComIPdu[ipdu_id], ComSignal[signal_ref_id])$$END$$DIE()$
						$ELSE$
							$buffer_list.bit[bit_position] = "1"$
						$END$
						$bit_position = bit_position + 1$
					$END$
				$ELIF EQ(ComSignal.ComSignalEndianness[signal_ref_id], "BIG_ENDIAN")$
					$FOREACH index RANGE(1, signal_size)$
						$IF EQ(buffer_list.bit[bit_position], "1")$
							$ERROR$$FORMAT(_("ComSignal are not allowed to overlap each other. (%1%\, %2%\)"), ComIPdu[ipdu_id], ComSignal[signal_ref_id])$$END$$DIE()$
						$ELSE$
							$buffer_list.bit[bit_position] = "1"$
						$END$
						$bit_position = bit_position + 1$
						$IF bit_position % 8 == 0$
							$bit_position = bit_position - 16$
						$END$
					$END$
				$END$
			$END$
		$END$
$		// [COM055] アップデートビットがシグナルの一部に含まれている場合はエラー
		$FOREACH signal_ref_id ComIPdu.ComIPduSignalRef[ipdu_id]$
			$update_bit_position = ComSignal.ComUpdateBitPosition[signal_ref_id]$
			$IF !EQ(update_bit_position, "COM_INVALID_UINT16")$
				$IF EQ(buffer_list.bit[update_bit_position], "1")$
					$ERROR$$FORMAT(_("ComUpdateBitPosition are not allowed to overlap ComSignal area. (%1%\, %2%\)"), ComIPdu[ipdu_id], ComSignal[signal_ref_id])$$END$$DIE()$
				$ELSE$
					$buffer_list.bit[update_bit_position] = "1"$
				$END$
			$END$
		$END$
	$END$

$END$


$ ====================================================================
$  [COM731] コールバック・コールアウト用ヘッダ生成処理
$ ====================================================================
$FUNCTION GEN_COM_CBK$

	$FILE "Com_Cbk.h"$
	/* Com_Cbk.h */$NL$
	#ifndef TOPPERS_A_COM_CBK_H$NL$
	#define TOPPERS_A_COM_CBK_H$NL$
	$NL$

	/* IPDU Callout */$NL$
	$FOREACH ipdu_id ComIPdu.ID_LIST$
		$IF !EQ(ComIPdu.ComIPduCallout[ipdu_id], "NULL_PTR")$
			boolean $ComIPdu.ComIPduCallout[ipdu_id]$(PduIdType Id, uint8* IpduData);$NL$
		$END$
	$END$
	$NL$

	/* Signal Callback */$NL$
	$FOREACH signal_id ComSignal.ID_LIST$
		$IF !EQ(ComSignal.ComNotification[signal_id], "NULL_PTR")$
			void $ComSignal.ComNotification[signal_id]$(void);$NL$
		$END$

		$IF !EQ(ComSignal.ComErrorNotification[signal_id], "NULL_PTR")$
			void $ComSignal.ComErrorNotification[signal_id]$(void);$NL$
		$END$

		$IF !EQ(ComSignal.ComTimeoutNotification[signal_id], "NULL_PTR")$
			void $ComSignal.ComTimeoutNotification[signal_id]$(void);$NL$
		$END$

		$IF !EQ(ComSignal.ComInvalidNotification[signal_id], "NULL_PTR")$
			void $ComSignal.ComInvalidNotification[signal_id]$(void);$NL$
		$END$
	$END$
	$NL$

	#endif /* TOPPERS_A_COM_CBK_H */$NL$

$END$


$ ====================================================================
$  [COM606] プリコンパイル用ヘッダ生成関数
$ ====================================================================

$FUNCTION GEN_COM_CONFIG$

	$FILE "Com_Cfg.h"$
	/* Com_Cfg.h */$NL$
	#ifndef TOPPERS_A_COM_CFG_H$NL$
	#define TOPPERS_A_COM_CFG_H$NL$
	$NL$

	$IF EQ(float64_flg, "TRUE")$
		#ifndef INT64_MAX$NL$
		#error FLOAT64 can not support.$NL$
		#endif$NL$
		$NL$
	$END$

$	// [COM541_Conf] ComGeneral
$	// [COM141_Conf][COM028] ComConfigurationUseDet
	#define COM_DEV_ERROR_DETECT 
	$IF LENGTH(ComGeneral.ComConfigurationUseDet[1]) && IS_TRUE(ComGeneral.ComConfigurationUseDet[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [COM788_Conf] ComEnableMDTForCyclicTransmission
	#define COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION 
	$IF LENGTH(ComGeneral.ComEnableMDTForCyclicTransmission[1]) && !IS_TRUE(ComGeneral.ComEnableMDTForCyclicTransmission[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$

$	// [COM780_Conf] ComRetryFailedTransmitRequests
	#define COM_RETRY_FAILED_TRANSMIT_REQUESTS 
	$IF LENGTH(ComGeneral.ComRetryFailedTransmitRequests[1]) && IS_TRUE(ComGeneral.ComRetryFailedTransmitRequests[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [COM438_Conf] ComVersionInfoApi
	#define COM_VERSION_INFO_API 
	$IF IS_TRUE(ComGeneral.ComVersionInfoApi[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [COM709_Conf] ComIPduCancellationSupport
	$ipdu_cancellation_support = "STD_OFF"$
	$FOREACH ipdu_id ComIPdu.ID_LIST$
		$IF IS_TRUE(ComIPdu.ComIPduCancellationSupport[ipdu_id])$
			$ipdu_cancellation_support = "STD_ON"$
		$END$
	$END$
	#define COM_IPDU_CANCELLATION_SUPPORT $ipdu_cancellation_support$$NL$

$	// [COM710_Conf] ComSupportedIPduGroups
	#define COM_SUPPORTED_IPDU_GROUPS $ComGeneral.ComSupportedIPduGroups[1]$U$NL$
	$NL$

	/* [ecuc_sws_2108] */$NL$
$	// [COM163] 各シグナルのショートネームをComHandleIdの設定値を用いて定義する
	$FOREACH signal_id ComSignal.ID_LIST$
		#define ComConf_ComSignal_$ComSignal[signal_id]$ $ComSignal.ComHandleId[signal_id]$U$NL$
	$END$
	$NL$

$	// [COM175_Conf][COM174] 各IPDUのショートネームをComIPduHandleIdの設定値を用いて定義する
	$FOREACH ipdu_id ComIPdu.ID_LIST$
		#define ComConf_ComIPdu_$ComIPdu[ipdu_id]$ $ComIPdu.ComIPduHandleId[ipdu_id]$U$NL$
	$END$
	$NL$

$	// [COM184_Conf][COM126] 各IPDUグループのショートネームをComIPduGroupHandleIdの設定値を用いて定義する
	$FOREACH ipdu_g_id ComIPduGroup.ID_LIST$
		#define ComConf_ComIPduGroup_$ComIPduGroup[ipdu_g_id]$ $ComIPduGroup.ComIPduGroupHandleId[ipdu_g_id]$U$NL$
	$END$
	$NL$

	#endif /* TOPPERS_A_COM_CFG_H */$NL$

$END$


$ ====================================================================
$  [COM583][COM608] ポストビルド用プログラム生成関数
$ ====================================================================
$FUNCTION GEN_COM_PB_CONFIG$

	$com_config_id = ARGV[1]$

	$FILE "Com_PBcfg.c"$

$	// 送信/受信IPDUのリスト作成
	$tx_ipdu_list = {}$
	$rx_ipdu_list = {}$
	$tx_ipdu_cnt = 0$
	$rx_ipdu_cnt = 0$
	$tx_ipdu_str = ""$
	$rx_ipdu_str = ""$
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
		$IF EQ(ComIPdu.ComIPduDirection[ipdu_id], "SEND")$
			$ComIPdu.list_pos[ipdu_id] = tx_ipdu_cnt$
			$tx_ipdu_list = APPEND(tx_ipdu_list, ipdu_id)$
			$tx_ipdu_cnt = tx_ipdu_cnt + 1$
			$IF tx_ipdu_cnt > 1$
				$tx_ipdu_str = CONCAT(tx_ipdu_str, ", ")$
			$END$
			$tx_ipdu_str = CONCAT(tx_ipdu_str, ComIPdu[ipdu_id])$
		$ELIF EQ(ComIPdu.ComIPduDirection[ipdu_id], "RECEIVE")$
			$ComIPdu.list_pos[ipdu_id] = rx_ipdu_cnt$
			$rx_ipdu_list = APPEND(rx_ipdu_list, ipdu_id)$
			$rx_ipdu_cnt = rx_ipdu_cnt + 1$
			$IF rx_ipdu_cnt > 1$
				$rx_ipdu_str = CONCAT(rx_ipdu_str, ", ")$
			$END$
			$rx_ipdu_str = CONCAT(rx_ipdu_str, ComIPdu[ipdu_id])$
		$END$
	$END$
	$ComConfig.tx_ipdu_list[com_config_id] = tx_ipdu_list$
	$ComConfig.rx_ipdu_list[com_config_id] = rx_ipdu_list$
	$ComConfig.tx_ipdu_num[com_config_id] = tx_ipdu_cnt$
	$ComConfig.rx_ipdu_num[com_config_id] = rx_ipdu_cnt$

$	// IPDUバッファ定義
	/* IPDUバッファ：ipdu_buffer_<ComConfig>_<ComIPdu> */$NL$
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
		$ipdu_length = 0$
		$FOREACH pdu_id Pdu.ID_LIST$
			$IF EQ(ComIPdu.ComPduIdRef[ipdu_id], Pdu[pdu_id])$
				$ipdu_length = Pdu.PduLength[pdu_id]$
				$ComIPdu.pdu_length[ipdu_id] = ipdu_length$
			$END$
		$END$
		static uint8 ipdu_buffer_$ComIPdu.PARENT[ipdu_id]$_$ComIPdu[ipdu_id]$[$ipdu_length$];$NL$
	$END$
	$NL$

$	// シグナルバッファ定義
	/* シグナルバッファ：signal_buffer_<ComConfig>_<ComSignal> */$NL$
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
		$IF EQ(ComSignal.direction[signal_id], "RECEIVE")
			|| EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE")
			|| EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION")$
			$IF EQ(ComSignal.ComSignalType[signal_id], "BOOLEAN")$
				static boolean signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8")$
				static uint8   signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT16")$
				static uint16  signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT32")$
				static uint32  signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT8")$
				static sint8   signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT16")$
				static sint16  signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT32")$
				static sint32  signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				static uint8   signal_buffer_$com_config_id$_$ComSignal[signal_id]$[$ComSignal.ComSignalLength[signal_id]$];$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT32")$
				static float32  signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT64")$
				static float64  signal_buffer_$com_config_id$_$ComSignal[signal_id]$;$NL$
			$END$
		$END$
	$END$
	$NL$

	$IF LENGTH(ComConfig.filter_list[com_config_id])$
		/* フィルタバッファ: filter_buffer_<ComConfig>_<ComSignal> */$NL$
		$FOREACH filter_id ComConfig.filter_list[com_config_id]$
$			// フィルタバッファはアルゴリズムがMASKED_NEW_DIFFERS_MASKED_OLDである場合のみに生成する
			$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
				$signal_ref_id = ComFilter.PARENT[filter_id]$
				static $ComSignal.signal_type_str[signal_ref_id]$ filter_buffer_$com_config_id$_$signal_ref_id$;$NL$
			$END$
		$END$
		$NL$
	$END$

$	// シグナル管理ブロック (受信シグナルは受信DM使用時のみ必要，送信シグナルはフィルタ使用時のみ必要)
	/* シグナル管理ブロック：<送受信>_signal_cb_<ComConfig>_<ComSignal> */$NL$
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
		$IF EQ(ComSignal.direction[signal_id], "SEND") && LENGTH(ComSignal.filter_ref_id[signal_id])$
			static TX_SIGNAL_CB tx_signal_cb_$ComIPdu.PARENT[ipdu_id]$_$ComSignal[signal_id]$;$NL$
		$ELIF EQ(ComSignal.direction[signal_id], "RECEIVE") && (ComSignal.timeout[signal_id] != 0)$
			static RX_SIGNAL_CB rx_signal_cb_$ComIPdu.PARENT[ipdu_id]$_$ComSignal[signal_id]$;$NL$
		$END$
	$END$
	$NL$

$	// [COM790] シグナル無効値は指定された型に従って解釈する
	/* シグナル無効値：signal_invalid_value_<ComConfig>_<ComSignal> */$NL$
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
		$IF LENGTH(ComSignal.ComSignalDataInvalidValue[signal_id])$
			$IF EQ(ComSignal.ComSignalType[signal_id], "BOOLEAN")$
				static const boolean signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $IS_TRUE(ComSignal.ComSignalDataInvalidValue[signal_id])$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8")$
				static const uint8   signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT16")$
				static const uint16  signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT32")$
				static const uint32  signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT8")$
				static const sint8   signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT16")$
				static const sint16  signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT32")$
				static const sint32  signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				$IF !EQ(ComSignal.ComSignalDataInvalidValue[signal_id], "NULL_PTR")$
					static const uint8   signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$[$ComSignal.ComSignalLength[signal_id]$] = {
$					// [COM791] UINT8_N型に設定された文字列は空白で区切られたASCIIコードとして解釈する
					$value_list = SPLIT(ComSignal.ComSignalDataInvalidValue[signal_id], " ")$
					$JOINEACH value_str value_list ", "$
						$value_str$
					$END$
					};$NL$
				$ELSE$
					static const uint8   signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = NULL_PTR;$NL$
				$END$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT32")$
				static const float32  signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT64")$
				static const float64  signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalDataInvalidValue[signal_id]$;$NL$
			$END$
		$END$
	$END$
	$NL$

$	// [COM790] シグナル初期値は指定された型に従って解釈する
$	// [COM723] シグナル初期値は指定された型のサイズに合わせる
	/* シグナル初期値：signal_init_value_<ComConfig>_<ComSignal> */$NL$
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
		$IF EQ(ComSignal.ComSignalType[signal_id], "BOOLEAN")$
			static const boolean signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $IS_TRUE(ComSignal.ComSignalInitValue[signal_id])$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8")$
			static const uint8   signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT16")$
			static const uint16  signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT32")$
			static const uint32  signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT8")$
			static const sint8   signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT16")$
			static const sint16  signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "SINT32")$
			static const sint32  signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
			static const uint8   signal_init_value_$com_config_id$_$ComSignal[signal_id]$[$ComSignal.ComSignalLength[signal_id]$] = {
$			// [COM791] UINT8_N型に設定された文字列は空白で区切られたASCIIコードとして解釈する
			$value_list = SPLIT(ComSignal.ComSignalInitValue[signal_id], " ")$
			$JOINEACH value_str value_list ", "$
				$value_str$
				$END$
			};$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT32")$
			static const float32  signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$ELIF EQ(ComSignal.ComSignalType[signal_id], "FLOAT64")$
			static const float64  signal_init_value_$com_config_id$_$ComSignal[signal_id]$ = $ComSignal.ComSignalInitValue[signal_id]$;$NL$
		$END$
	$END$
	$NL$

$	// OCCURRENCEカウンタ
	$IF LENGTH(ComConfig.filter_list[com_config_id])$
		/* OCCURRENCEカウンタ : occur_<ComConfig>_<ComSignal> */$NL$
		$FOREACH filter_id ComConfig.filter_list[com_config_id]$
			$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
				static uint32 occur_$com_config_id$_$ComFilter.PARENT[filter_id]$;$NL$
			$END$
		$END$
	$END$
	$NL$

$	// フィルタ初期化ブロック
	$IF LENGTH(ComConfig.filter_list[com_config_id])$
		/* フィルタ初期化ブロック : filter_inib_<ComConfig>_<ComSignal> */$NL$
		$FOREACH filter_id ComConfig.filter_list[com_config_id]$
			$signal_ref_id = ComFilter.PARENT[filter_id]$
			$signal_filter_type = ""$
			$IF EQ(ComSignal.ComSignalType[signal_ref_id], "BOOLEAN") || EQ(ComSignal.ComSignalType[signal_ref_id], "UINT8")
			 || EQ(ComSignal.ComSignalType[signal_ref_id], "UINT16") || EQ(ComSignal.ComSignalType[signal_ref_id], "UINT32")$
				$signal_filter_type = "UINT"$
			$ELIF EQ(ComSignal.ComSignalType[signal_ref_id], "SINT8") || EQ(ComSignal.ComSignalType[signal_ref_id], "SINT16")
			 || EQ(ComSignal.ComSignalType[signal_ref_id], "SINT32")$
				$signal_filter_type = "SINT"$
			$END$
$			// フィルタアルゴリズムごとに作成(ALWAYS, NEVER用は不要)
			$IF (EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_EQUALS_X") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_X"))$
$				/* COM_MASKED_NEW_DIFFERS_X/COM_MASKED_NEW_EQUALS_X用 ($signal_filter_type$) */$NL$
				static const FILTER_$signal_filter_type$_MASKED_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
				$TAB$$ComFilter.ComFilterMask[filter_id]$,$TAB$/* ComFilterMask */$NL$
				$TAB$$ComFilter.ComFilterX[filter_id]$$TAB$/* ComFilterX */$NL$
				};$NL$
			$ELIF EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
$				/* COM_MASKED_NEW_DIFFERS_MASKED_OLD用 ($signal_filter_type$) */$NL$
				static const FILTER_$signal_filter_type$_MASKED_OLD_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
				$TAB$$ComFilter.ComFilterMask[filter_id]$,$TAB$/* ComFilterMask */$NL$
				$TAB$(void *)&filter_buffer_$com_config_id$_$signal_ref_id$$TAB$/* p_filter_buffer */$NL$
				};$NL$
			$ELIF (EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE"))$
$				/* COM_NEW_IS_OUTSIDE/COM_NEW_IS_WITHIN用 ($signal_filter_type$) */$NL$
				static const FILTER_$signal_filter_type$_NEW_IS_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
				$TAB$$ComFilter.ComFilterMax[filter_id]$,$TAB$/* ComFilterMax */$NL$
				$TAB$$ComFilter.ComFilterMin[filter_id]$$TAB$/* ComFilterMin */$NL$
				};$NL$
			$ELIF EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
$				/* COM_ONE_EVERY_N用 */$NL$
				static const FILTER_ONE_EVERY_N_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
				$TAB$$ComFilter.ComFilterOffset[filter_id]$U,$TAB$/* ComFilterOffset */$NL$
				$TAB$$ComFilter.ComFilterPeriod[filter_id]$U,$TAB$/* ComFilterPeriod */$NL$
				$TAB$&occur_$com_config_id$_$signal_ref_id$$TAB$/* p_occur */$NL$
				};$NL$
			$END$
		$END$
		$NL$
	$END$

$	// IPDU管理ブロックリスト (送信IPDUのみ)
	$IF tx_ipdu_cnt > 0$
		/* IPDU管理ブロックリスト：<送受信>_ipdu_cb_list_<ComConfig> */$NL$
		static TX_IPDU_CB tx_ipdu_cb_list_$com_config_id$[$tx_ipdu_cnt$];$NL$
		$NL$
	$END$

$	// 所属シグナルIDリスト
	/* 所属シグナルIDリスト：signalid_list_<ComConfig>_<ComIPdu> */$NL$
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
		static const Com_SignalIdType signalid_list_$com_config_id$_$ComIPdu[ipdu_id]$[$LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id])$] = {$NL$
		$JOINEACH signal_id ComIPdu.ComIPduSignalRef[ipdu_id] ",\n"$
			$TAB$/* $ComSignal[signal_id]$ */$NL$
			$TAB$$ComSignal.ComHandleId[signal_id]$U
		$END$
		$NL$};$NL$
	$END$
	$NL$

$	// IPDU状態
	/* IPDU状態：state_<ComConfig>_<ComIPdu> */$NL$
	$FOREACH pdu_id ComConfig.ipdu_list[com_config_id]$
		static uint8 state_$com_config_id$_$ComIPdu[pdu_id]$;$NL$
	$END$
	$NL$

$	// IPDU所属グループベクタ
$	// [COM206_Conf][NCOM004] ComIPduGroupRefからIPDUが所属するIPDUグループのベクタの大きさを算出
	$ComConfig.vector_length[com_config_id] = ((ComConfig.ipdu_g_num[com_config_id] - 1) / 8) + 1$
	/* IPDU所属グループベクタ：ipdu_group_vector_<ComConfig> */$NL$
	static const Com_IpduGroupVector ipdu_group_vector_$com_config_id$[$ComConfig.ipdu_num[com_config_id]$] = {$NL$
	$JOINEACH ipdu_id ComConfig.ipdu_list[com_config_id] ",\n"$
		$TAB$/* $ComIPdu[ipdu_id]$ (ComIPduGroupHandleId: 
		$JOINEACH ipdu_g_ref_id ComIPdu.ComIPduGroupRef[ipdu_id] ","$
			$ComIPduGroup.ComIPduGroupHandleId[ipdu_g_ref_id]$
		$END$
		) */$NL$
		$TAB${
		$JOINEACH byte_index RANGE(0, ComConfig.vector_length[com_config_id] - 1) ",\n\t"$
			$ipdu_g_handle_id_list = {}$
			$check_flag = 0$
			$FOREACH ipdu_g_ref_id ComIPdu.ComIPduGroupRef[ipdu_id]$
				$ipdu_g_handle_id = ComIPduGroup.ComIPduGroupHandleId[ipdu_g_ref_id]$
				$IF ((byte_index * 8) <= +ipdu_g_handle_id) && ((byte_index * 8 + 7) >= +ipdu_g_handle_id)$
					$check_flag = 1$
					$ipdu_g_handle_id_list = APPEND(ipdu_g_handle_id_list, ipdu_g_handle_id)$
				$END$
			$END$
			$IF check_flag != 0$
				$JOINEACH ipdu_g_handle_id ipdu_g_handle_id_list " + "$
					(uint8) (1U << ($+ipdu_g_handle_id$U - (8U * $+byte_index$U)))
				$END$
			$ELSE$
				0U
			$END$
		$END$
		}
	$END$
	$NL$};$NL$
	$NL$

$	// [COM351_Conf] ComTxMode
	$IF ComConfig.tx_ipdu_num[com_config_id] > 0$
$		// 送信モード(TRUE)初期化ブロック
		/* 送信モード(TRUE)初期化ブロック：ipdu_tx_mode_true_inib_<ComConfig>_<ComIPdu> */$NL$
		$FOREACH ipdu_id ComConfig.tx_ipdu_list[com_config_id]$
			$FOREACH tx_mode_id ComTxMode_true.ID_LIST$
				$IF EQ(ipdu_id, ComTxIPdu.PARENT[ComTxModeTrue.PARENT[ComTxMode_true.PARENT[tx_mode_id]]])$
					static const TX_MODE_INIB ipdu_tx_mode_true_inib_$com_config_id$_$ComIPdu[ipdu_id]$ = {$NL$
					$TAB$COM_$ComTxMode_true.ComTxModeMode[tx_mode_id]$,$TAB$/* ComTxModeMode */$NL$
					$TAB$$ComTxMode_true.ComTxModeNumberOfRepetitions[tx_mode_id]$U,$TAB$/* ComTxModeNumberOfRepetitions */$NL$
$					// [NCOM005] ComTxModeRepetitionPeriodをMF呼出し回数に変換
					$div_num1 = ComTxMode_true.ComTxModeRepetitionPeriod[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV(div_num1, div_num2)$
					$TAB$$div_result$U,$TAB$/* ComTxModeRepetitionPeriod ($div_num1$ / $div_num2$) */$NL$
$					// [NCOM020] ComTxModeTimeOffsetはMF呼出し回数に+1する
					$div_num1 = ComTxMode_true.ComTxModeTimeOffset[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV(div_num1, div_num2)$
					$TAB$($div_result$U + 1U),$TAB$/* ComTxModeTimeOffset (($div_num1$ / $div_num2$) + 1) */$NL$
$					// [NCOM005] ComTxModeTimePeriodをMF呼出し回数に変換
					$div_num1 = ComTxMode_true.ComTxModeTimePeriod[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV(div_num1, div_num2)$
					$TAB$$div_result$U$TAB$/* ComTxModeTimePeriod ($div_num1$ / $div_num2$) */$NL$
					};$NL$
$					// ComTxModeTrueへの参照を保持
					$ComIPdu.tx_mode_true_id_ref[ipdu_id] = tx_mode_id$
				$END$
			$END$
		$END$
		$NL$
$		// 送信モード(FALSE)初期化ブロック
		/* 送信モード(FALSE)初期化ブロック：ipdu_tx_mode_false_inib_<ComConfig>_<ComIPdu> */$NL$
		$FOREACH ipdu_id ComConfig.tx_ipdu_list[com_config_id]$
			$FOREACH tx_mode_id ComTxMode_false.ID_LIST$
				$IF EQ(ipdu_id, ComTxIPdu.PARENT[ComTxModeFalse.PARENT[ComTxMode_false.PARENT[tx_mode_id]]])$
					static const TX_MODE_INIB ipdu_tx_mode_false_inib_$com_config_id$_$ComIPdu[ipdu_id]$ = {$NL$
					$TAB$COM_$ComTxMode_false.ComTxModeMode[tx_mode_id]$,$TAB$/* ComTxModeMode */$NL$
					$TAB$$ComTxMode_false.ComTxModeNumberOfRepetitions[tx_mode_id]$U,$TAB$/* ComTxModeNumberOfRepetitions */$NL$
$					// [NCOM005] ComTxModeRepetitionPeriodをMF呼出し回数に変換
					$div_num1 = ComTxMode_false.ComTxModeRepetitionPeriod[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV(div_num1, div_num2)$
					$TAB$$div_result$U,$TAB$/* ComTxModeRepetitionPeriod ($div_num1$ / $div_num2$) */$NL$
$					// [NCOM020] ComTxModeTimeOffsetはMF呼出し回数に+1する
					$div_num1 = ComTxMode_false.ComTxModeTimeOffset[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV(div_num1, div_num2)$
					$TAB$($div_result$U + 1U),$TAB$/* ComTxModeTimeOffset (($div_num1$ / $div_num2$) + 1) */$NL$
$					// [NCOM005] ComTxModeTimePeriodをMF呼出し回数に変換
					$div_num1 = ComTxMode_false.ComTxModeTimePeriod[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV(div_num1, div_num2)$
					$TAB$$div_result$U$TAB$/* ComTxModeTimePeriod ($div_num1$ / $div_num2$) */$NL$
					};$NL$
$					// ComTxModeFalseへの参照を保持
					$ComIPdu.tx_mode_false_id_ref[ipdu_id] = tx_mode_id$
				$END$
			$END$
		$END$
		$NL$
	$END$

$	// 送信IPDU初期化ブロックリスト
	$IF ComConfig.tx_ipdu_num[com_config_id] > 0$
		/* 送信IPDU初期化ブロックリスト : tx_ipdu_inib_<ComConfig>_<ComIPdu> */$NL$
		$FOREACH ipdu_id ComConfig.tx_ipdu_list[com_config_id]$
			$FOREACH tx_ipdu_id ComTxIPdu.ID_LIST$
				$IF EQ(ipdu_id, ComTxIPdu.PARENT[tx_ipdu_id])$
					static const TX_IPDU_INIB tx_ipdu_inib_$com_config_id$_$ComIPdu[ipdu_id]$ = {$NL$
					$TAB$COM_$ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id]$,$TAB$/* ComTxIPduClearUpdateBit */$NL$
					$TAB$$ComTxIPdu.ComTxIPduUnusedAreasDefault[tx_ipdu_id]$U,$TAB$/* ComTxIPduUnusedAreasDefault */$NL$
$					// [NCOM005] MF呼出し回数に変換
					$div_num1 = ComTxIPdu.ComMinimumDelayTime[tx_ipdu_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV(div_num1, div_num2)$
					$TAB$$div_result$U,$TAB$/* ComMinimumDelayTime ($div_num1$ / $div_num2$) */$NL$
$					// [COM455_Conf] ComTxModeTrueの多重度は0..1
					$IF LENGTH(ComIPdu.tx_mode_true_id_ref[ipdu_id])$
						$TAB$&ipdu_tx_mode_true_inib_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* p_tx_mode_true_inib */$NL$
					$ELSE$
						$TAB$NULL_PTR,$TAB$/* p_tx_mode_true_inib */$NL$
					$END$
$					// [COM454_Conf] ComTxModeFalseの多重度は0..1
					$IF LENGTH(ComIPdu.tx_mode_false_id_ref[ipdu_id])$
						$TAB$&ipdu_tx_mode_false_inib_$com_config_id$_$ComIPdu[ipdu_id]$$TAB$/* p_tx_mode_false_inib */$NL$
					$ELSE$
						$TAB$NULL_PTR$TAB$/* p_tx_mode_false_inib */$NL$
					$END$
					};$NL$
				$END$
			$END$
		$END$
		$NL$
	$END$

$	// IPDU初期化ブロックリスト
	/* IPDU初期化ブロックリスト：<送受信>_ipdu_inib_list_<ComConfig> */$NL$
	$IF tx_ipdu_cnt > 0$
		static const IPDU_INIB tx_ipdu_inib_list_$com_config_id$[$tx_ipdu_cnt$] = {$NL$
		$JOINEACH ipdu_id ComConfig.tx_ipdu_list[com_config_id] ",\n"$
			$TAB$/* $ComIPdu[ipdu_id]$ */$NL$
			$TAB${$NL$
			$TAB$$TAB$COM_$ComIPdu.ComIPduDirection[ipdu_id]$,$TAB$/* ComIPduDirection */$NL$
			$TAB$$TAB$COM_$ComIPdu.ComIPduSignalProcessing[ipdu_id]$,$TAB$/* ComIPduSignalProcessing */$NL$
			$TAB$$TAB$COM_$ComIPdu.ComIPduType[ipdu_id]$,$TAB$/* ComIPduType */$NL$
			$TAB$$TAB$$ComIPdu.ComIPduCancellationSupport[ipdu_id]$,$TAB$/* ComIPduCancellationSupport */$NL$
			$TAB$$TAB$&tx_ipdu_inib_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* p_tx_ipdu_inib */$NL$
			$IF EQ(ComIPdu.ComIPduCallout[ipdu_id], "NULL_PTR")$
				$TAB$$TAB$$ComIPdu.ComIPduCallout[ipdu_id]$,$TAB$/* ComIPduCallout */$NL$
			$ELSE$
				$TAB$$TAB$&$ComIPdu.ComIPduCallout[ipdu_id]$,$TAB$/* ComIPduCallout */$NL$
			$END$
			$IF EQ(ComIPdu.pdur_src_pdu_handle_id[ipdu_id], "COM_INVALID_UINT16")$
				$TAB$$TAB$$ComIPdu.pdur_src_pdu_handle_id[ipdu_id]$,$TAB$/* PduRSourcePduHandleId */$NL$
			$ELSE$
				$TAB$$TAB$$ComIPdu.pdur_src_pdu_handle_id[ipdu_id]$U,$TAB$/* PduRSourcePduHandleId */$NL$
			$END$
			$TAB$$TAB$$ComIPdu.pdu_length[ipdu_id]$U,$TAB$/* PduLength */$NL$
			$TAB$$TAB$signalid_list_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* 所属シグナルIDリスト */$NL$
			$TAB$$TAB$&ipdu_group_vector_$com_config_id$[$ComIPdu.ComIPduHandleId[ipdu_id]$],$TAB$/* IPDU所属グループベクタ */$NL$
			$TAB$$TAB$(void *)&tx_ipdu_cb_list_$com_config_id$[$ComIPdu.list_pos[ipdu_id]$],$TAB$/* IPDU管理リスト */$NL$
			$TAB$$TAB$ipdu_buffer_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDUバッファ */$NL$
			$TAB$$TAB$&state_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDU状態 */$NL$
			$TAB$$TAB$$LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id])$U$TAB$/* tnum_signal */$NL$
			$TAB$}
		$END$
	$NL$};$NL$
	$END$
	$NL$
	$IF rx_ipdu_cnt > 0$
		static const IPDU_INIB rx_ipdu_inib_list_$com_config_id$[$rx_ipdu_cnt$] = {$NL$
		$JOINEACH ipdu_id ComConfig.rx_ipdu_list[com_config_id] ",\n"$
			$TAB$/* $ComIPdu[ipdu_id]$ */$NL$
			$TAB${$NL$
			$TAB$$TAB$COM_$ComIPdu.ComIPduDirection[ipdu_id]$,$TAB$/* ComIPduDirection */$NL$
			$TAB$$TAB$COM_$ComIPdu.ComIPduSignalProcessing[ipdu_id]$,$TAB$/* ComIPduSignalProcessing */$NL$
			$TAB$$TAB$COM_$ComIPdu.ComIPduType[ipdu_id]$,$TAB$/* ComIPduType */$NL$
			$TAB$$TAB$$ComIPdu.ComIPduCancellationSupport[ipdu_id]$,$TAB$/* ComIPduCancellationSupport */$NL$
			$TAB$$TAB$NULL_PTR,$TAB$/* p_tx_ipdu_inib */$NL$
			$IF EQ(ComIPdu.ComIPduCallout[ipdu_id], "NULL_PTR")$
				$TAB$$TAB$$ComIPdu.ComIPduCallout[ipdu_id]$,$TAB$/* ComIPduCallout */$NL$
			$ELSE$
				$TAB$$TAB$&$ComIPdu.ComIPduCallout[ipdu_id]$,$TAB$/* ComIPduCallout */$NL$
			$END$
			$IF EQ(ComIPdu.pdur_src_pdu_handle_id[ipdu_id], "COM_INVALID_UINT16")$
				$TAB$$TAB$$ComIPdu.pdur_src_pdu_handle_id[ipdu_id]$,$TAB$/* PduRSourcePduHandleId */$NL$
			$ELSE$
				$TAB$$TAB$$ComIPdu.pdur_src_pdu_handle_id[ipdu_id]$U,$TAB$/* PduRSourcePduHandleId */$NL$
			$END$
			$TAB$$TAB$$ComIPdu.pdu_length[ipdu_id]$U,$TAB$/* PduLength */$NL$
			$TAB$$TAB$signalid_list_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* 所属シグナルIDリスト */$NL$
			$TAB$$TAB$&ipdu_group_vector_$com_config_id$[$ComIPdu.ComIPduHandleId[ipdu_id]$],$TAB$/* IPDU所属グループベクタ */$NL$
			$TAB$$TAB$NULL_PTR,$TAB$/* IPDU管理リスト */$NL$
			$TAB$$TAB$ipdu_buffer_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDUバッファ */$NL$
			$TAB$$TAB$&state_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDU状態 */$NL$
			$TAB$$TAB$$LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id])$U$TAB$/* tnum_signal */$NL$
			$TAB$}
		$END$
	$NL$};$NL$
	$END$
	$NL$

$	// 全IPDU初期化ブロックテーブル
	/* 全IPDU初期化ブロックテーブル(IDソート)：ipdu_inib_table_<ComConfig> */$NL$
	static const IPDU_INIB * const ipdu_inib_table_$com_config_id$[$ComConfig.ipdu_num[com_config_id]$] = {$NL$
	$JOINEACH ipdu_id ComConfig.ipdu_list[com_config_id] ",\n"$
		$IF EQ(ComIPdu.ComIPduDirection[ipdu_id], "SEND")$
			$TAB$/* $ComIPdu[ipdu_id]$ */$NL$
			$TAB$&tx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[ipdu_id]$]
		$ELIF EQ(ComIPdu.ComIPduDirection[ipdu_id], "RECEIVE")$
			$TAB$/* $ComIPdu[ipdu_id]$ */$NL$
			$TAB$&rx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[ipdu_id]$]
		$END$
	$END$
	$NL$};$NL$
	$NL$

$	// シグナル初期化ブロック
	/* シグナル初期化ブロックテーブル：signal_inib_table_<ComConfig> */$NL$
	static const SIGNAL_INIB signal_inib_table_$com_config_id$[$ComConfig.signal_num[com_config_id]$] = {$NL$
	$JOINEACH signal_id ComConfig.signal_list[com_config_id] ",\n"$
		$TAB$/* $ComSignal[signal_id]$ */$NL$
		$TAB${$NL$
$		// [COM785] ComBitSizeはデータ型のサイズへの拡張をしない
		$IF EQ(ComSignal.ComBitSize[signal_id], "COM_INVALID_UINT8")$
			$TAB$$TAB$$ComSignal.ComBitSize[signal_id]$,$TAB$/* ComBitSize */$NL$
		$ELSE$
			$TAB$$TAB$$ComSignal.ComBitSize[signal_id]$U,$TAB$/* ComBitSize */$NL$
		$END$
		$TAB$$TAB$COM_$ComSignal.ComDataInvalidAction[signal_id]$,$TAB$/* ComDataInvalidAction */$NL$
		$TAB$$TAB$COM_$ComSignal.ComRxDataTimeoutAction[signal_id]$,$TAB$/* ComRxDataTimeoutAction */$NL$
		$TAB$$TAB$COM_$ComSignal.ComSignalEndianness[signal_id]$,$TAB$/* ComSignalEndianness */$NL$
		$TAB$$TAB$COM_$ComSignal.ComSignalType[signal_id]$,$TAB$/* ComSignalType */$NL$
		$TAB$$TAB$COM_$ComSignal.ComTransferProperty[signal_id]$,$TAB$/* ComTransferProperty */$NL$
		$TAB$$TAB$$ComSignal.lsb[signal_id]$U,$TAB$/* ComBitPositionLsb */$NL$
		$IF EQ(ComSignal.ComSignalLength[signal_id], "COM_INVALID_UINT16")$
			$TAB$$TAB$$ComSignal.ComSignalLength[signal_id]$,$TAB$/* ComSignalLength */$NL$
		$ELSE$
			$TAB$$TAB$$ComSignal.ComSignalLength[signal_id]$U,$TAB$/* ComSignalLength */$NL$
		$END$
		$IF EQ(ComSignal.ComUpdateBitPosition[signal_id], "COM_INVALID_UINT16")$
			$TAB$$TAB$$ComSignal.ComUpdateBitPosition[signal_id]$,$TAB$/* ComUpdateBitPosition */$NL$
		$ELSE$
			$TAB$$TAB$$ComSignal.ComUpdateBitPosition[signal_id]$U,$TAB$/* ComUpdateBitPosition */$NL$
		$END$
		$IF (ComSignal.first_timeout[signal_id] != 0)$
$			// [NCOM033] ComFirstTimeoutが有効値の場合，MF呼出し回数を算出して+1する
			$TAB$$TAB$($ComSignal.first_timeout[signal_id]$U + 1U),$TAB$/* ComFirstTimeout */$NL$
		$ELSE$
			$TAB$$TAB$$ComSignal.first_timeout[signal_id]$U,$TAB$/* ComFirstTimeout */$NL$
		$END$
		$TAB$$TAB$$ComSignal.timeout[signal_id]$U,$TAB$/* ComTimeout */$NL$
		$IF EQ(ComSignal.ComErrorNotification[signal_id], "NULL_PTR")$
			$TAB$$TAB$$ComSignal.ComErrorNotification[signal_id]$,$TAB$/* ComErrorNotification */$NL$
		$ELSE$
			$TAB$$TAB$&$ComSignal.ComErrorNotification[signal_id]$,$TAB$/* ComErrorNotification */$NL$
		$END$
		$IF EQ(ComSignal.ComInvalidNotification[signal_id], "NULL_PTR")$
			$TAB$$TAB$$ComSignal.ComInvalidNotification[signal_id]$,$TAB$/* ComInvalidNotification */$NL$
		$ELSE$
			$TAB$$TAB$&$ComSignal.ComInvalidNotification[signal_id]$,$TAB$/* ComInvalidNotification */$NL$
		$END$
		$IF EQ(ComSignal.ComNotification[signal_id], "NULL_PTR")$
			$TAB$$TAB$$ComSignal.ComNotification[signal_id]$,$TAB$/* ComNotification */$NL$
		$ELSE$
			$TAB$$TAB$&$ComSignal.ComNotification[signal_id]$,$TAB$/* ComNotification */$NL$
		$END$
		$IF EQ(ComSignal.ComTimeoutNotification[signal_id], "NULL_PTR")$
			$TAB$$TAB$$ComSignal.ComTimeoutNotification[signal_id]$,$TAB$/* ComTimeoutNotification */$NL$
		$ELSE$
			$TAB$$TAB$&$ComSignal.ComTimeoutNotification[signal_id]$,$TAB$/* ComTimeoutNotification */$NL$
		$END$
		$IF LENGTH(ComSignal.ComSignalDataInvalidValue[signal_id])$
			$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
				$TAB$$TAB$(const void *)signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* ComSignalDataInvalidValue */$NL$
			$ELSE$
				$TAB$$TAB$(const void *)&signal_invalid_value_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* ComSignalDataInvalidValue */$NL$
			$END$
		$ELSE$
			$TAB$$TAB$NULL_PTR,$TAB$/* ComSignalDataInvalidValue */$NL$
		$END$
		$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
			$TAB$$TAB$(const void *)signal_init_value_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* ComSignalInitValue */$NL$
		$ELSE$
			$TAB$$TAB$(const void *)&signal_init_value_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* ComSignalInitValue */$NL$
		$END$
		$belong_ipdu_id = ComSignal.ipdu_ref[signal_id]$
		$IF EQ(ComSignal.direction[signal_id], "SEND")$
			$TAB$$TAB$&tx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[belong_ipdu_id]$],$TAB$/* $belong_ipdu_id$ */$NL$
			$IF LENGTH(ComSignal.filter_ref_id[signal_id])$
				$TAB$$TAB$COM_$ComFilter.ComFilterAlgorithm[ComSignal.filter_ref_id[signal_id]]$,$TAB$/* ComFilterAlgorithm */$NL$
				$IF EQ(ComFilter.ComFilterAlgorithm[ComSignal.filter_ref_id[signal_id]], "ALWAYS") || EQ(ComFilter.ComFilterAlgorithm[ComSignal.filter_ref_id[signal_id]], "NEVER")$
					$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
				$ELSE$
					$TAB$$TAB$(const void *)&filter_inib_$com_config_id$_$signal_id$,$TAB$/* p_filter_inib */$NL$
				$END$
				$TAB$$TAB$(void *)&tx_signal_cb_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* シグナル管理ブロック */$NL$
			$ELSE$
				$TAB$$TAB$COM_INVALID_UINT8,$TAB$/* ComFilterAlgorithm */$NL$
				$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
$				// 送信の場合，フィルタがなければNULL_PTR
				$TAB$$TAB$NULL_PTR,$TAB$/* シグナル管理ブロック */$NL$
			$END$
			$IF EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE") || EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION")$
				$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
					$TAB$$TAB$(void *)signal_buffer_$com_config_id$_$ComSignal[signal_id]$$TAB$/* シグナルバッファ */$NL$
				$ELSE$
					$TAB$$TAB$(void *)&signal_buffer_$com_config_id$_$ComSignal[signal_id]$$TAB$/* シグナルバッファ */$NL$
				$END$
			$ELSE$
$				// 送信の場合，TRIGGERED_ON_CHANGE，TRIGGERED_ON_CHANGE_WITHOUT_REPETITION以外は，NULL_PTR
				$TAB$$TAB$NULL_PTR$TAB$/* シグナルバッファ */$NL$
			$END$
		$ELIF EQ(ComSignal.direction[signal_id], "RECEIVE")$
			$TAB$$TAB$&rx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[belong_ipdu_id]$],$TAB$/* $belong_ipdu_id$ */$NL$
			$IF LENGTH(ComSignal.filter_ref_id[signal_id])$
				$TAB$$TAB$COM_$ComFilter.ComFilterAlgorithm[ComSignal.filter_ref_id[signal_id]]$,$TAB$/* ComFilterAlgorithm */$NL$
				$IF EQ(ComFilter.ComFilterAlgorithm[ComSignal.filter_ref_id[signal_id]], "ALWAYS") || EQ(ComFilter.ComFilterAlgorithm[ComSignal.filter_ref_id[signal_id]], "NEVER")$
					$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
				$ELSE$
					$TAB$$TAB$(const void *)&filter_inib_$com_config_id$_$signal_id$,$TAB$/* p_filter_inib */$NL$
				$END$
			$ELSE$
				$TAB$$TAB$COM_INVALID_UINT8,$TAB$/* ComFilterAlgorithm */$NL$
				$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
			$END$
			$IF ComSignal.timeout[signal_id] != 0$
				$TAB$$TAB$(void *)&rx_signal_cb_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* シグナル管理ブロック */$NL$
			$ELSE$
$				// 受信の場合，受信DMがなければNULL_PTR
				$TAB$$TAB$NULL_PTR,$TAB$/* シグナル管理ブロック */$NL$
			$END$
$			// 受信の場合，必須
			$TAB$$TAB$(void *)&signal_buffer_$com_config_id$_$ComSignal[signal_id]$$TAB$/* シグナルバッファ */$NL$
		$END$
		$TAB$}
	$END$
	$NL$};$NL$
	$NL$

$END$


$ ====================================================================
$  メイン処理
$ ====================================================================

$	// IDソート
$ID_SORT()$

$	// エラーチェック
$float64_flg = "FALSE"$
$FOREACH config_id ComConfig.ID_LIST$
	$ERROR_CHECK(config_id)$
$END$

$	// コールバック・コールアウト用ヘッダ
$GEN_COM_CBK()$

$	// プリコンパイル用ヘッダ
$GEN_COM_CONFIG()$

$	// ポストビルド用プログラム
$FILE "Com_PBcfg.c"$
/* Com_PBcfg.c */$NL$
#include "Os.h"$NL$
#include "Com.h"$NL$
#include "Com_Cbk.h"$NL$
#include "Rte_Cbk.h"$NL$
$NL$

$	// [NCOM002] ポストビルド対応のためComConfigの多重度は1..*
$FOREACH config_id ComConfig.ID_LIST$
	/*$NL$ * $ComConfig[config_id]$$NL$ */$NL$
	$GEN_COM_PB_CONFIG(ComConfig[config_id])$
$END$

$	// [COM337_Conf][NCOM024] コンフィギュレーション情報テーブル
$	// [COM374][COM487] com_config配列の添字でコンフィギュレーションを識別する
$	// [COM745] デバッグ可能とするためにグローバル変数で定義する
/* コンフィギュレーション情報テーブル */$NL$
const Com_ConfigType com_config[$LENGTH(ComConfig.ID_LIST)$] = {$NL$
$JOINEACH config_id ComConfig.ID_LIST ",\n"$
	$TAB$/* $ComConfig[config_id]$ */$NL$
	$TAB${$NL$
	$TAB$$TAB$$ComConfig.ComConfigurationId[config_id]$U,$TAB$/* ComConfigurationId */$NL$
	$TAB$$TAB$$ComConfig.signal_num[config_id]$U,$TAB$/* tnum_signal */$NL$
	$TAB$$TAB$$ComConfig.ipdu_g_num[config_id]$U,$TAB$/* tnum_ipdu_g */$NL$
	$TAB$$TAB$signal_inib_table_$ComConfig[config_id]$,$TAB$/* p_signal_inib_table */$NL$
	$TAB$$TAB$$((ComConfig.ipdu_g_num[config_id] - 1) / 8) + 1$U,$TAB$/* tnum_vector */$NL$
	$TAB$$TAB$$ComConfig.ipdu_num[config_id]$U,$TAB$/* tnum_ipdu */$NL$
	$TAB$$TAB$ipdu_inib_table_$ComConfig[config_id]$,$TAB$/* pp_ipdu_inib_table */$NL$
	$TAB$$TAB$$ComConfig.rx_ipdu_num[config_id]$U,$TAB$/* tnum_rx_ipdu */$NL$
	$TAB$$TAB$$ComConfig.tx_ipdu_num[config_id]$U,$TAB$/* tnum_tx_ipdu */$NL$
	$IF ComConfig.rx_ipdu_num[config_id] > 0$
		$TAB$$TAB$rx_ipdu_inib_list_$ComConfig[config_id]$,$TAB$/* p_rx_ipdu_inib_list */$NL$
	$ELSE$
		$TAB$$TAB$NULL_PTR,$TAB$/* p_rx_ipdu_inib_list */$NL$
	$END$
	$IF ComConfig.tx_ipdu_num[config_id] > 0$
		$TAB$$TAB$tx_ipdu_inib_list_$ComConfig[config_id]$$TAB$/* p_tx_ipdu_inib_list */$NL$
	$ELSE$
		$TAB$$TAB$NULL_PTR$TAB$/* p_rx_ipdu_inib_list */$NL$
	$END$
	$TAB$}
$END$
$NL$};$NL$
$NL$

$	DUMP()$


$	ボディ制御系プロファイル以外のために対応しない仕様タグ一覧
$	(同一仕様タグがボディ制御系プロファイルの要求仕様でも使用されているものは[]で表記)
$	- 送信シグナルゲートウェイ
$	  <COM544_Conf> ComGwMapping
$	  <COM545_Conf> ComGwMapping/ComGwSource
$	  <COM548_Conf> ComGwMapping/ComGwSource/ComGwSourceDescription
$	  [COM259_Conf] ComGwMapping/ComGwSource/ComGwSourceDescription/ComBitPosition
$	  [COM158_Conf] ComGwMapping/ComGwSource/ComGwSourceDescription/ComBitSize
$	  [COM157_Conf] ComGwMapping/ComGwSource/ComGwSourceDescription/ComSignalEndianness
$	  [COM437_Conf] ComGwMapping/ComGwSource/ComGwSourceDescription/ComSignalLength
$	  [COM127_Conf] ComGwMapping/ComGwSource/ComGwSourceDescription/ComSignalType
$	  [COM257_Conf] ComGwMapping/ComGwSource/ComGwSourceDescription/ComUpdateBitPosition
$	  <COM550_Conf> ComGwMapping/ComGwSource/ComGwSourceDescription/ComGwIPduRef
$	  <COM546_Conf> ComGwMapping/ComGwDestination
$	  <COM549_Conf> ComGwMapping/ComGwDestination/ComGwDestinationDescription
$	  [COM259_Conf] ComGwMapping/ComGwDestination/ComGwDestinationDescription/ComBitPosition
$	  [COM157_Conf] ComGwMapping/ComGwDestination/ComGwDestinationDescription/ComSignalEndianness
$	  [COM170_Conf] ComGwMapping/ComGwDestination/ComGwDestinationDescription/ComSignalInitValue
$	  [COM232_Conf] ComGwMapping/ComGwDestination/ComGwDestinationDescription/ComTransferProperty
$	  [COM257_Conf] ComGwMapping/ComGwDestination/ComGwDestinationDescription/ComUpdateBitPosition
$	  <COM550_Conf> ComGwMapping/ComGwDestination/ComGwDestinationDescription/ComGwIPduRef
$	  <COM551_Conf> ComGwMapping/ComGwSignal
$	  <COM547_Conf> ComGwMapping/ComGwSignal/ComGwSignalRef
$	  <COM729_Conf> ComTimeBase/ComGwTimeBase
$	  <COM765_Conf> ComIPdu/ComIPduTriggerTransmitCallout
$	- データシーケンス
$	  <COM592_Conf> ComIPdu/ComIPduCounter
$	  <COM003_Conf> ComIPdu/ComIPduCounter/ComIPduCounterErrorNotification
$	  <COM593_Conf> ComIPdu/ComIPduCounter/ComIPduCounterSize
$	  <COM594_Conf> ComIPdu/ComIPduCounter/ComIPduCounterStartPosition
$	  <COM595_Conf> ComIPdu/ComIPduCounter/ComIPduCounterThreshold
$	- 送信保護
$	  <COM599_Conf> ComIPdu/ComIPduReplication
$	  <COM600_Conf> ComIPdu/ComIPduReplication/ComIPduReplicationQuorum
$	  <COM601_Conf> ComIPdu/ComIPduReplication/ComIPduReplicaRef
$	- シグナルグループ
$	  <COM521><COM044>[COM553]
$	  <COM345_Conf> ComSignalGroup
$	  [COM314_Conf] ComSignalGroup/ComDataInvalidAction
$	  [COM499_Conf] ComSignalGroup/ComErrorNotification
$	  [COM183_Conf] ComSignalGroup/ComFirstTimeout
$	  [COM165_Conf] ComSignalGroup/ComHandleId
$	  [COM315_Conf] ComSignalGroup/ComInvalidNotification
$	  [COM498_Conf] ComSignalGroup/ComNotification
$	  [COM412_Conf] ComSignalGroup/ComRxDataTimeoutAction
$	  [COM263_Conf] ComSignalGroup/ComTimeout
$	  [COM552_Conf] ComSignalGroup/ComTimeoutNotification
$	  [COM232_Conf] ComSignalGroup/ComTransferProperty
$	  [COM257_Conf] ComSignalGroup/ComUpdateBitPosition
$	  <COM001_Conf> ComSignalGroup/ComSystemTemplateSignalGroupRef
$	  <COM520_Conf> ComSignalGroup/ComGroupSignal
$	  [COM259_Conf] ComSignalGroup/ComGroupSignal/ComBitPosition
$	  [COM158_Conf] ComSignalGroup/ComGroupSignal/ComBitSize
$	  [COM165_Conf] ComSignalGroup/ComGroupSignal/ComHandleId
$	  [COM391_Conf] ComSignalGroup/ComGroupSignal/ComSignalDataInvalidValue
$	  [COM157_Conf] ComSignalGroup/ComGroupSignal/ComSignalEndianness
$	  [COM170_Conf] ComSignalGroup/ComGroupSignal/ComSignalInitValue
$	  [COM437_Conf] ComSignalGroup/ComGroupSignal/ComSignalLength
$	  [COM127_Conf] ComSignalGroup/ComGroupSignal/ComSignalType
$	  <COM560_Conf> ComSignalGroup/ComGroupSignal/ComTransferProperty
$	  <COM002_Conf> ComSignalGroup/ComGroupSignal/ComSystemTemplateSystemSignalRef
$	  <COM519_Conf> ComIPdu/ComIPduSignalGroupRef

$	その他の仕様説明
$	  <COM585> 本ジェネレータではCom_Cfg.cは生成しない
$	  <COM607> 本ジェネレータではリンクタイムパラメータはサポートしない
$	  [COM401] ComSignalGroupとComGroupSignalのショートネームは重複不可
