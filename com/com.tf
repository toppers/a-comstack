$
$  TOPPERS/A-COM
$      AuTomotive COM
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
$  $Id: com.tf 3262 2016-03-31 01:41:12Z sunnygiken-yamawaki $
$

$	// [COM006] XMLによるコンフィギュレーションパラメータ処理
$	// [NCOM104] 数値変換できないパラメータが指定された場合エラー

$	// 定数定義
$tenth_int64_max = 0x7FFFFFFFFFFFFFFF / 10$


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
$ 浮動小数型用割り算関数
$ ====================================================================
$FUNCTION DIV_FLOAT_VALUE$
	$arg1 = ARGV[1]$
	$arg2 = ARGV[2]$
	$arg_name1 = ARGV[3]$
	$arg_name2 = ARGV[4]$
	$arg_str1 = ETOF(arg1)$
	$arg_str2 = ETOF(arg2)$

$	// 引数に小数点が指定されていない場合はエラー
	$tmp = REGEX_REPLACE(arg_str1, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name1, arg_str1)$$END$$DIE()$
	$END$
	$tmp = REGEX_REPLACE(arg_str2, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name2, arg_str2)$$END$$DIE()$
	$END$

	$num1_l = REGEX_REPLACE(arg_str1, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num1_r = REGEX_REPLACE(arg_str1, "^[0-9]+\\.([0-9]+)$", "$1")$
	$num1 = ATOI(CONCAT(num1_l, num1_r), 10)$
	$num2_l = REGEX_REPLACE(arg_str2, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num2_r = REGEX_REPLACE(arg_str2, "^[0-9]+\\.([0-9]+)$", "$1")$
	$num2 = ATOI(CONCAT(num2_l, num2_r), 10)$

$	// [NCOM101][NCOM102] 0割エラー
	$IF num2 == 0$
		$ERROR$$FORMAT(_("Must not be set 0 to %1%."), arg_name2)$$END$$DIE()$
	$END$

$	// num1が0ならば割り算を実行せず0を返す
	$div_result = 0$
	$IF num1 != 0$
$		// 倍率を揃える
		$adjust = 1$
		$digits_diff = STRING_SIZE(num1_r) - STRING_SIZE(num2_r)$
		$IF digits_diff > 0$
			$cnt = digits_diff$
			$WHILE(cnt > 0)$
				$IF num2 <= tenth_int64_max$
					$num2 = num2 * 10$
					$cnt = cnt - 1$
				$ELSE$
$					// num2がoverflowする時点でnum1<num2なので，div_resultは1と確定する
					$div_result = 1$
					$adjust = 0$
					$cnt = 0$
				$END$
			$END$
		$ELIF digits_diff < 0$
			$cnt = -digits_diff$
			$WHILE(cnt > 0)$
				$IF num1 <= tenth_int64_max$
					$num1 = num1 * 10$
					$cnt = cnt - 1$
				$ELSE$
					$IF cnt > 18$
						$ERROR$$FORMAT(_("overflow the 64bit. %1% / %2% : (%3%) / (%4%)"), arg1, arg2, arg_name1, arg_name2)$$END$$DIE()$
					$END$
					$WHILE(cnt > 0)$
						$adjust = adjust * 10$
						$cnt = cnt - 1$
					$END$
				$END$
			$END$
			
			$IF adjust != 1$
$				// overflowする部分をover_numに退避
				$over = 1000000000000000000 / adjust$
				$over_num = num1 / over$
$				// over_num >= num2 であれば除算結果もoverflowするので表現不可能
				$IF over_num >= num2$
					$ERROR$$FORMAT(_("overflow the 64bit. %1% / %2% : (%3%) / (%4%)"), arg1, arg2, arg_name1, arg_name2)$$END$$DIE()$
				$END$
$				// over_numを最大桁にする
				$over_num = over_num * over$
$				// under_num(overflowしない部分)にadjust(調整倍率)をかける
				$under_num = (num1 - over_num) * adjust$

$				// エラー条件を満たさなかったことから，(over_num / num2)の後であればadjustをかけることが可能
$				// あまりにadjustをかけてからnum2で割った数値を足すことで桁落ちを防止
				$tmp = (over_num % num2) * adjust$
				$over_div = (over_num / num2) * adjust + tmp / num2$
				$over_mod = tmp % num2$
				$under_div = under_num / num2$
				$under_mod = under_num % num2$

				$div_result = over_div + under_div$
$				// [NCOM005] 割り算の余りは繰り上げる
				$IF (over_mod + under_mod) > 0$
					$div_result = div_result + 1$
				$END$
			$END$
		$END$

$		調整不要(adjust == 1)の場合は通常の割り算を実施
		$IF adjust == 1$
			$div_result = num1 / num2$
			$mod_result = num1 % num2$
$			// [NCOM005] 割り算の余りは繰り上げる
			$IF mod_result > 0$
				$div_result = div_result + 1$
			$END$
		$END$
	$END$

$	// コード仕様で32bit以上の値は設定できないのでエラー
	$IF div_result > 0xFFFFFFFF$
		$ERROR$$FORMAT(_("overflow the 32bit. %1% / %2% : (%3%) / (%4%)"), arg1, arg2, arg_name1, arg_name2)$$END$$DIE()$
	$END$

	$RESULT = div_result$
$END$

$ ====================================================================
$ 文字列サイズ取得関数
$ ====================================================================
$FUNCTION STRING_SIZE$
	$size_result = 0$
	$string_tmp = ARGV[1]$
	$WHILE !EQ(string_tmp, "")$
		$string_tmp = REGEX_REPLACE(string_tmp, "^.(.*)$", "$1")$
		$size_result = size_result + 1$
	$END$
	$RESULT = size_result$
$END$

$ ====================================================================
$ 浮動小数比較関数
$ ARGV[1] > ARGV[2]  : 返り値(1)
$ ARGV[1] == ARGV[2] : 返り値(0)
$ ARGV[1] < ARGV[2]  : 返り値(-1)
$ ====================================================================
$FUNCTION CMP_FLOAT_VALUE$
	$arg1 = ARGV[1]$
	$arg2 = ARGV[2]$
	$arg_name1 = ARGV[3]$
	$arg_name2 = ARGV[4]$
	$arg_str1 = ETOF(arg1)$
	$arg_str2 = ETOF(arg2)$

$	// 引数に小数点が指定されていない場合はエラー
	$tmp = REGEX_REPLACE(arg_str1, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name1, arg_str1)$$END$$DIE()$
	$END$
	$tmp = REGEX_REPLACE(arg_str2, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name2, arg_str2)$$END$$DIE()$
	$END$

	$cmp_result = 0$
$	// 整数部分比較
	$num1_l = REGEX_REPLACE(arg_str1, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num2_l = REGEX_REPLACE(arg_str2, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num1 = ATOI(num1_l, 10)$
	$num2 = ATOI(num2_l, 10)$
	$IF num1 > num2$
		$cmp_result = 1$
	$ELIF num1 < num2$
		$cmp_result = -1$
	$END$

$	// 整数部分が等しければ小数部分を比較
	$IF cmp_result == 0$
		$num1_r = REGEX_REPLACE(arg_str1, "^[0-9]+\\.([0-9]+)$", "$1")$
		$num2_r = REGEX_REPLACE(arg_str2, "^[0-9]+\\.([0-9]+)$", "$1")$
		$num1 = ATOI(num1_r, 10)$
		$num2 = ATOI(num2_r, 10)$
$		// 桁を揃える
		$digits_diff = STRING_SIZE(num1_r) - STRING_SIZE(num2_r)$
		$IF digits_diff > 0$
			$cnt = digits_diff$
			$WHILE(cnt > 0)$
				$IF num2 <= tenth_int64_max$
					$num2 = num2 * 10$
					$cnt = cnt - 1$
				$ELSE$
					$cmp_result = -1$
					$cnt = 0$
				$END$
			$END$
		$ELIF digits_diff < 0$
			$cnt = -digits_diff$
			$WHILE(cnt > 0)$
				$IF num1 <= tenth_int64_max$
					$num1 = num1 * 10$
					$cnt = cnt - 1$
				$ELSE$
					$cmp_result = 1$
					$cnt = 0$
				$END$
			$END$
		$END$

		$IF cmp_result == 0$
			$IF num1 > num2$
				$cmp_result = 1$
			$ELIF num1 < num2$
				$cmp_result = -1$
			$END$
		$END$
	$END$

	$RESULT = cmp_result$
$END$

$ ====================================================================
$  指数表記から小数点表記への変換関数
$ ====================================================================
$FUNCTION ETOF$
$	// 引数に指数表記の値が指定されていない場合は処理しない
	$tmp = REGEX_REPLACE(ARGV[1], "^[0-9]+\\.[0-9]+[e|E][+|-][0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$RESULT = ARGV[1]$
	$ELSE$
		$num_l = REGEX_REPLACE(ARGV[1], "^([0-9]+)\\.[0-9]+[e|E][+|-][0-9]+$", "$1")$
		$num_r = REGEX_REPLACE(ARGV[1], "^[0-9]+\\.([0-9]+)[e|E][+|-][0-9]+$", "$1")$
		$sign  = REGEX_REPLACE(ARGV[1], "^[0-9]+\\.[0-9]+[e|E]([+|-])[0-9]+$", "$1")$
		$indx  = REGEX_REPLACE(ARGV[1], "^[0-9]+\\.[0-9]+[e|E][+|-]([0-9]+)$", "$1")$
		$IF EQ(sign, "+")$
			$result = num_l$
			$FOREACH i RANGE(1, ATOI(indx, 10))$
				$IF EQ(num_r, "")$
					$result = CONCAT(result, "0")$
				$ELSE$
					$result = CONCAT(result, REGEX_REPLACE(num_r, "^(.).*$", "$1"))$
					$num_r = REGEX_REPLACE(num_r, "^.(.*)$", "$1")$
				$END$
			$END$
			$IF EQ(num_r, "")$
				$result = CONCAT(result, ".0")$
			$ELSE$
				$result = CONCAT(result, ".")$
				$result = CONCAT(result, num_r)$
			$END$
		$ELIF EQ(sign, "-")$
			$result = num_r$
			$FOREACH i RANGE(1, ATOI(indx))$
				$IF EQ(num_l, "")$
					$result = CONCAT("0", result)$
				$ELSE$
					$result = CONCAT(REGEX_REPLACE(num_l, "^.*(.)$", "$1"), result)$
					$num_l = REGEX_REPLACE(num_l, "^(.*).$", "$1")$
				$END$
			$END$
			$IF EQ(num_l, "")$
				$result = CONCAT("0.", result)$
			$ELSE$
				$result = CONCAT(".", result)$
				$result = CONCAT(num_l, result)$
			$END$
		$END$
		$RESULT = result$
	$END$
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
	$arg_value = ARGV[1]$
	$type  = ARGV[2]$
	$size  = ARGV[3]$
	$param_name  = ARGV[4]$
	$value = 0$
	$min = 0$
	$max = 0$

$ // arg_valueが数値変換可能かどうかを解析し，可能であれば数値変換する
	$IF (!EQ(arg_value, "")
		&& ((EQ(REGEX_REPLACE(arg_value, "^-?0[x|X][a-f|A-F|0-9]{1,8}", ""), ""))
		|| (EQ(REGEX_REPLACE(arg_value, "0", ""), ""))
		|| (EQ(REGEX_REPLACE(arg_value, "^-?[1-9][0-9]{0,9}", ""), ""))))$
		$value = ATOI(arg_value, 0)$
	$ELSE$
		$ERROR$$FORMAT(_("%1%\ is invalid string. [%2%\]"), param_name, arg_value)$$END$$DIE()$
	$END$

$ valueがsizeのビットサイズの範囲内かどうかを判定する
	$tmp = 1 << size$
	$IF (EQ(type, "UINT8") || EQ(type, "UINT16") || EQ(type, "UINT32"))$
		$min = 0$
		$max = tmp - 1$
	$ELIF (EQ(type, "SINT8") || EQ(type, "SINT16") || EQ(type, "SINT32"))$
		$min = (tmp >> 1) * -1$
		$max = (tmp >> 1) - 1$
	$END$
	$IF (value < min) || (max < value)$
		$ERROR$$FORMAT(_("%1%\ is `%2%\(%3%\)\'. It is not within the range of ComBitSize. (ComBitSize:%4%\ [min:%5%\  max:%6%\])"), param_name, arg_value, value, size, min, max)$$END$$DIE()$
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

$	// コンフィグごとのシグナルグループリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$cnt = 0$
		$FOREACH signal_g_id ComSignalGroup.ID_LIST$
			$IF EQ(config_id, ComSignalGroup.PARENT[signal_g_id])$
				$new_list = APPEND(new_list, signal_g_id)$
				$cnt = cnt + 1$
			$END$
		$END$
		$ComConfig.signal_g_list[config_id] = new_list$
		$ComConfig.signal_g_num[config_id] = cnt$
	$END$

$	// コンフィグごとのグループシグナルリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$cnt = 0$
		$FOREACH signal_g_id ComSignalGroup.ID_LIST$
			$IF EQ(config_id, ComSignalGroup.PARENT[signal_g_id])$
				$FOREACH g_signal_id ComGroupSignal.ID_LIST$
					$IF EQ(signal_g_id, ComGroupSignal.PARENT[g_signal_id])$
						$new_list = APPEND(new_list, g_signal_id)$
						$ComGroupSignal.index[g_signal_id] = cnt$
						$cnt = cnt + 1$
					$END$
				$END$
			$END$
		$END$
		$ComConfig.g_signal_list[config_id] = new_list$
		$ComConfig.g_signal_num[config_id] = cnt$
	$END$

$	// [COM165_Conf] シグナルグループごとのグループシグナルリスト作成
	$FOREACH signal_g_id ComSignalGroup.ID_LIST$
		$new_list = {}$
		$cnt = 0$
		$FOREACH g_signal_id ComGroupSignal.ID_LIST$
			$IF EQ(signal_g_id, ComGroupSignal.PARENT[g_signal_id])$
				$new_list = APPEND(new_list, g_signal_id)$
				$cnt = cnt + 1$
			$END$
		$END$
		$ComSignalGroup.gg_signal_list[signal_g_id] = new_list$
		$ComSignalGroup.gg_signal_num[signal_g_id] = cnt$
	$END$

$	// [COM165_Conf] コンフィグごとのシグナル・グループシグナルのリストをComHandleId順にソート
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$cnt = 0$
		$FOREACH index RANGE(0, LENGTH(ComConfig.signal_list[config_id]) + LENGTH(ComConfig.g_signal_list[config_id]) - 1)$
			$find = 0$
			$IF LENGTH(ComConfig.signal_list[config_id])$
				$FOREACH s_handleid ComConfig.signal_list[config_id]$
					$IF find == 0$
						$IF ComSignal.ComHandleId[s_handleid] == index$
							$new_list = APPEND(new_list, s_handleid)$
							$cnt = cnt + 1$
							$find = 1$
						$ELSE$
							$FOREACH gs_handleid ComConfig.g_signal_list[config_id]$
								$IF find == 0$
									$IF ComGroupSignal.ComHandleId[gs_handleid] == index$
										$new_list = APPEND(new_list, gs_handleid)$
										$cnt = cnt + 1$
										$find = 1$
									$END$
								$END$
							$END$
						$END$
					$END$
				$END$
			$ELSE$
				$FOREACH gs_handleid ComConfig.g_signal_list[config_id]$
					$IF find == 0$
						$IF ComGroupSignal.ComHandleId[gs_handleid] == index$
							$new_list = APPEND(new_list, gs_handleid)$
							$cnt = cnt + 1$
							$find = 1$
						$END$
					$END$
				$END$
			$END$
		$END$
		$ComConfig.gs_signal_list[config_id] = new_list$
		$ComConfig.gs_signal_num[config_id] = cnt$
	$END$

$	// [COM165_Conf] コンフィグごとのシグナルグループリストをComHandleId順にソート
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(ComConfig.signal_g_list[config_id]) - 1)$
			$find = 0$
			$FOREACH handleid ComConfig.signal_g_list[config_id]$
				$IF ComSignalGroup.ComHandleId[handleid] == index$
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
		$ComConfig.signal_g_list[config_id] = new_list$
	$END$

$	// コンフィグごとのシグナルのフィルタリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH signal_id ComSignal.ID_LIST$
			$IF EQ(config_id, ComSignal.PARENT[signal_id])$
				$FOREACH filter_id ComFilter.ID_LIST$
					$IF EQ(signal_id, ComFilter.PARENT[filter_id])$
						$new_list = APPEND(new_list, filter_id)$
					$END$
				$END$
			$END$
		$END$
		$ComConfig.filter_list[config_id] = new_list$
	$END$

$	// コンフィグごとのグループシグナルのフィルタリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH signal_g_id ComConfig.signal_g_list[config_id]$
			$IF EQ(config_id, ComSignalGroup.PARENT[signal_g_id])$
				$FOREACH g_signal_id ComGroupSignal.ID_LIST$
					$IF EQ(signal_g_id, ComGroupSignal.PARENT[g_signal_id])$
						$FOREACH filter_id ComFilter.ID_LIST$
							$IF EQ(g_signal_id, ComFilter.PARENT[filter_id])$
								$new_list = APPEND(new_list, filter_id)$
							$END$
						$END$
					$END$
				$END$
			$END$
		$END$
		$ComConfig.g_filter_list[config_id] = new_list$
	$END$

$	// コンフィグごとのシグナルとグループシグナルのフィルタリスト作成
	$FOREACH config_id ComConfig.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(ComConfig.signal_list[config_id]) + LENGTH(ComConfig.g_signal_list[config_id]) - 1)$
			$find = 0$
			$IF LENGTH(ComConfig.signal_list[config_id])$
				$FOREACH signal_id ComConfig.signal_list[config_id]$
					$IF find == 0$
						$IF ComSignal.ComHandleId[signal_id] == index$
							$FOREACH filter_id ComFilter.ID_LIST$
								$IF EQ(signal_id, ComFilter.PARENT[filter_id])$
									$new_list = APPEND(new_list, filter_id)$
								$END$
							$END$
							$find = 1$
						$ELSE$
							$FOREACH gsignal_id ComConfig.g_signal_list[config_id]$
								$IF find == 0$
									$IF ComGroupSignal.ComHandleId[gsignal_id] == index$
										$FOREACH filter_id ComFilter.ID_LIST$
											$IF EQ(gsignal_id, ComFilter.PARENT[filter_id])$
												$new_list = APPEND(new_list, filter_id)$
											$END$
										$END$
										$find = 1$
									$END$
								$END$
							$END$
						$END$
					$END$
				$END$
			$ELSE$
				$FOREACH gsignal_id ComConfig.g_signal_list[config_id]$
					$IF find == 0$
						$IF ComGroupSignal.ComHandleId[gsignal_id] == index$
							$FOREACH filter_id ComFilter.ID_LIST$
								$IF EQ(gsignal_id, ComFilter.PARENT[filter_id])$
									$new_list = APPEND(new_list, filter_id)$
								$END$
							$END$
							$find = 1$
						$END$
					$END$
				$END$
			$END$
		$END$
		$ComConfig.gs_filter_list[config_id] = new_list$
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

$	// [COM401] ComSignalとComGroupSignalのショートネームは重複不可
	$FOREACH signal_id ComConfig.gs_signal_list[com_config_id]$
		$FOREACH signal_chk_id ComConfig.gs_signal_list[com_config_id]$
			$IF EQ(signal_id, signal_chk_id) && (signal_id != signal_chk_id)$
				$ERROR$$FORMAT(_("Short Name of ComSignal and ComGroupSignal should not be duplicated. (%1%\)"), signal_id)$$END$$DIE()$
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

$		// [COM519_Conf] ComIPduSignalGroupRef
		$IF LENGTH(ComIPdu.ComIPduSignalGroupRef[ipdu_id])$
			$FOREACH signal_ref_id ComIPdu.ComIPduSignalGroupRef[ipdu_id]$
				$IF !LENGTH(ComSignalGroup.ipdu_ref[signal_ref_id])$
					$ComSignalGroup.ipdu_ref[signal_ref_id] = ComIPdu[ipdu_id]$
				$ELSE$
$					// [COM101] シグナルは2つ以上のIPDUに所属できない
					$ERROR$$FORMAT(_("`%1%\' belongs to more than one IPDU."), ComSignal[signal_ref_id])$$END$$DIE()$
				$END$
				$ComSignalGroup.direction[signal_ref_id] = ComIPdu.ComIPduDirection[ipdu_id]$
				$FOREACH g_signal_id ComGroupSignal.ID_LIST$
					$IF EQ(signal_ref_id, ComGroupSignal.PARENT[g_signal_id])$
						$ComGroupSignal.direction[g_signal_id] = ComIPdu.ComIPduDirection[ipdu_id]$
					$END$
				$END$
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
$		// COM_INVALID_UINT16 かつ 送信であればエラー
		$IF (EQ(ComIPdu.pdur_src_pdu_handle_id[ipdu_id], "COM_INVALID_UINT16") && EQ(ComIPdu.ComIPduDirection[ipdu_id], "SEND"))$
			$ERROR$$FORMAT(_("PduRSrcPdu should be set. There is no PduRSrcPdu corresponding to %1%"), ComIPdu[ipdu_id])$$END$$DIE()$
		$END$

$		// IPDUごとにComTimeoutとComFirstTimeoutの最小値を保持して各シグナルに反映
		$ComIPdu.timeout_min[ipdu_id] = 0$
		$ComIPdu.first_timeout_min[ipdu_id] = 0$
		$IF EQ(ComIPdu.ComIPduDirection[ipdu_id], "SEND")$
$			// [NCOM049] 送信シグナルがある場合はComTxTimeBase必須
			$IF EQ(ComConfig.tx_time_base[com_config_id], "COM_INVALID_UINT32")$
				$ERROR$$FORMAT(_("`%1%\' should be set ComTxTimeBase."), ComIPdu.PARENT[ipdu_id])$$END$$DIE()$
			$END$

$			//シグナル
			$FOREACH signal_ref_id ComIPdu.ComIPduSignalRef[ipdu_id]$
$				// [COM263_Conf] ComTimeout
				$IF !LENGTH(ComSignal.ComTimeout[signal_ref_id])$
					$ComSignal.ComTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignal.ComTimeout[signal_ref_id], ComConfig.tx_time_base[com_config_id], "ComTimeout", "ComTxTimeBase")$
$				// [COM445] 送信シグナルのデッドラインモニタリングには所属するIPDU内全てのシグナルに設定されたComTimeoutの最小値を用いる
				$IF ComSignal.timeout[signal_ref_id] != 0$
					$IF ((ComIPdu.timeout_min[ipdu_id] == 0) || (ComIPdu.timeout_min[ipdu_id] > ComSignal.timeout[signal_ref_id]))$
						$ComIPdu.timeout_min[ipdu_id] = ComSignal.timeout[signal_ref_id]$
					$END$
				$END$
$				// [COM183_Conf] ComFirstTimeout
				$IF !LENGTH(ComSignal.ComFirstTimeout[signal_ref_id])$
					$ComSignal.ComFirstTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.first_timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignal.ComFirstTimeout[signal_ref_id], ComConfig.tx_time_base[com_config_id], "ComFirstTimeout", "ComTxTimeBase")$
				$IF ComSignal.first_timeout[signal_ref_id] != 0$
					$IF ((ComIPdu.first_timeout_min[ipdu_id] == 0) || (ComIPdu.first_timeout_min[ipdu_id] > ComSignal.first_timeout[signal_ref_id]))$
						$ComIPdu.first_timeout_min[ipdu_id] = ComSignal.first_timeout[signal_ref_id]$
					$END$
				$END$
			$END$
			
$			//シグナルグループ
			$FOREACH signal_ref_id ComIPdu.ComIPduSignalGroupRef[ipdu_id]$
$				// [COM263_Conf] ComTimeout
				$IF !LENGTH(ComSignalGroup.ComTimeout[signal_ref_id])$
					$ComSignalGroup.ComTimeout[signal_ref_id] = "0.0"$
				$END$

$				// [NCOM005] MF呼出し回数に変換
				$ComSignalGroup.timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignalGroup.ComTimeout[signal_ref_id], ComConfig.tx_time_base[com_config_id], "ComTimeout", "ComTxTimeBase")$
$				// [COM445] 送信シグナルのデッドラインモニタリングには所属するIPDU内全てのシグナルに設定されたComTimeoutの最小値を用いる
				$IF ComSignalGroup.timeout[signal_ref_id] != 0$
					$IF ((ComIPdu.timeout_min[ipdu_id] == 0) || (ComIPdu.timeout_min[ipdu_id] > ComSignalGroup.timeout[signal_ref_id]))$
						$ComIPdu.timeout_min[ipdu_id] = ComSignalGroup.timeout[signal_ref_id]$
					$END$
				$END$

$				// [COM183_Conf] ComFirstTimeout
				$IF !LENGTH(ComSignalGroup.ComFirstTimeout[signal_ref_id])$
					$ComSignalGroup.ComFirstTimeout[signal_ref_id] = "0.0"$
				$END$

$				// [NCOM005] MF呼出し回数に変換
				$ComSignalGroup.first_timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignalGroup.ComFirstTimeout[signal_ref_id], ComConfig.tx_time_base[com_config_id], "ComFirstTimeout", "ComTxTimeBase")$
				$IF ComSignalGroup.first_timeout[signal_ref_id] != 0$
					$IF ((ComIPdu.first_timeout_min[ipdu_id] == 0) || (ComIPdu.first_timeout_min[ipdu_id] > ComSignalGroup.first_timeout[signal_ref_id]))$
						$ComIPdu.first_timeout_min[ipdu_id] = ComSignalGroup.first_timeout[signal_ref_id]$
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
				$IF !LENGTH(ComSignal.ComTimeout[signal_ref_id])$
					$ComSignal.ComTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignal.ComTimeout[signal_ref_id], ComConfig.rx_time_base[com_config_id], "ComTimeout", "ComRxTimeBase")$
$				// [COM291] アップデートビットを持たないシグナルの受信デッドラインカウンタは所属するIPDU内の全てのアップデートビットを持たないシグナルに設定されたComTimeoutの最小値を用いる
				$IF (ComSignal.timeout[signal_ref_id] != 0) && !LENGTH(ComSignal.ComUpdateBitPosition[signal_ref_id])$
					$IF ((ComIPdu.timeout_min[ipdu_id] == 0) || (ComIPdu.timeout_min[ipdu_id] > ComSignal.timeout[signal_ref_id]))$
						$ComIPdu.timeout_min[ipdu_id] = ComSignal.timeout[signal_ref_id]$
					$END$
				$END$
$				// [COM183_Conf] ComFirstTimeout
				$IF !LENGTH(ComSignal.ComFirstTimeout[signal_ref_id])$
					$ComSignal.ComFirstTimeout[signal_ref_id] = "0.0"$
				$END$
$				// [NCOM005] MF呼出し回数に変換
				$ComSignal.first_timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignal.ComFirstTimeout[signal_ref_id], ComConfig.rx_time_base[com_config_id], "ComFirstTimeout", "ComRxTimeBase")$
$				// [COM291] アップデートビットを持たないシグナルの受信デッドラインカウンタは所属するIPDU内の全てのアップデートビットを持たないシグナルに設定されたComFirstTimeoutの最小値を用いる
				$IF (ComSignal.first_timeout[signal_ref_id] != 0) && !LENGTH(ComSignal.ComUpdateBitPosition[signal_ref_id])$
					$IF ((ComIPdu.first_timeout_min[ipdu_id] == 0) || (ComIPdu.first_timeout_min[ipdu_id] > ComSignal.first_timeout[signal_ref_id]))$
						$ComIPdu.first_timeout_min[ipdu_id] = ComSignal.first_timeout[signal_ref_id]$
					$END$
				$END$
			$END$

$			//シグナルグループ
			$FOREACH signal_ref_id ComIPdu.ComIPduSignalGroupRef[ipdu_id]$
$				// [COM263_Conf] ComTimeout
				$IF !LENGTH(ComSignalGroup.ComTimeout[signal_ref_id])$
					$ComSignalGroup.ComTimeout[signal_ref_id] = "0.0"$
				$END$

$				// [NCOM005] MF呼出し回数に変換
				$ComSignalGroup.timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignalGroup.ComTimeout[signal_ref_id], ComConfig.rx_time_base[com_config_id], "ComTimeout", "ComRxTimeBase")$
$				// [COM291] アップデートビットを持たないシグナルの受信デッドラインカウンタは所属するIPDU内の全てのアップデートビットを持たないシグナルに設定されたComTimeoutの最小値を用いる
				$IF (ComSignalGroup.timeout[signal_ref_id] != 0) && !LENGTH(ComSignalGroup.ComUpdateBitPosition[signal_ref_id])$
					$IF ((ComIPdu.timeout_min[ipdu_id] == 0) || (ComIPdu.timeout_min[ipdu_id] > ComSignalGroup.timeout[signal_ref_id]))$
						$ComIPdu.timeout_min[ipdu_id] = ComSignalGroup.timeout[signal_ref_id]$
					$END$
				$END$

$				// [COM183_Conf] ComFirstTimeout
				$IF !LENGTH(ComSignalGroup.ComFirstTimeout[signal_ref_id])$
					$ComSignalGroup.ComFirstTimeout[signal_ref_id] = "0.0"$
				$END$

$				// [NCOM005] MF呼出し回数に変換
				$ComSignalGroup.first_timeout[signal_ref_id] = DIV_FLOAT_VALUE(ComSignalGroup.ComFirstTimeout[signal_ref_id], ComConfig.rx_time_base[com_config_id], "ComFirstTimeout", "ComRxTimeBase")$
$				// [COM291] アップデートビットを持たないシグナルの受信デッドラインカウンタは所属するIPDU内の全てのアップデートビットを持たないシグナルに設定されたComFirstTimeoutの最小値を用いる
				$IF (ComSignalGroup.first_timeout[signal_ref_id] != 0) && !LENGTH(ComSignalGroup.ComUpdateBitPosition[signal_ref_id])$
					$IF ((ComIPdu.first_timeout_min[ipdu_id] == 0) || (ComIPdu.first_timeout_min[ipdu_id] > ComSignalGroup.first_timeout[signal_ref_id]))$
						$ComIPdu.first_timeout_min[ipdu_id] = ComSignalGroup.first_timeout[signal_ref_id]$
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
			$IF !LENGTH(ComTxIPdu.ComMinimumDelayTime[tx_ipdu_id])$
				$ComTxIPdu.ComMinimumDelayTime[tx_ipdu_id] = "0.0"$
			$END$

$			// [COM576_Conf] ComTxIPduClearUpdateBit
			$IF LENGTH(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id])$
				$IF !EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "Confirmation")
					&& !EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "Transmit")
					&& !EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "TriggerTransmit")$
					$ERROR$$FORMAT(_("ComTxIPduClearUpdateBit should not be set `%1%\'. (%2%\)"),ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id] , ComTxIPdu[tx_ipdu_id])$$END$$DIE()$
				$ELSE$
					$IF EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "Confirmation")$
						$ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id] = "CONFIRMATION"$
					$ELIF EQ(ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id], "Transmit")$
						$ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id] = "TRANSMIT"$
					$ELSE$
						$ComTxIPdu.ComTxIPduClearUpdateBit[tx_ipdu_id] = "TRIGGER_TRANSMIT"$
					$END$
				
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
$			// [COM282_Conf][NCOM054] ComTxModeRepetitionPeriod
			$IF !LENGTH(ComTxMode_true.ComTxModeRepetitionPeriod[tx_mode_id]) && EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "PERIODIC")$
				$ComTxMode_true.ComTxModeRepetitionPeriod[tx_mode_id] = "0.0"$
			$ELSE$
				$IF EQ(ComTxMode_true.ComTxModeRepetitionPeriod[tx_mode_id], "0.0")$
					$ERROR$$FORMAT(_("Do not set to 0 in the ComTxModeRepetitionPeriod. (%1%\)"), ComTxMode_true[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
$			// [COM180_Conf] ComTxModeTimeOffset
			$IF !LENGTH(ComTxMode_true.ComTxModeTimeOffset[tx_mode_id])$
				$ComTxMode_true.ComTxModeTimeOffset[tx_mode_id] = "0.0"$
			$END$
$			// [COM178_Conf][NCOM055] ComTxModeTimePeriod
			$IF !LENGTH(ComTxMode_true.ComTxModeTimePeriod[tx_mode_id]) && EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "DIRECT")$
				$ComTxMode_true.ComTxModeTimePeriod[tx_mode_id] = "0.0"$
			$ELSE$
				$IF EQ(ComTxMode_true.ComTxModeTimePeriod[tx_mode_id], 0)$
					$ERROR$$FORMAT(_("Do not set to 0 in the ComTxModeTimePeriod. (%1%\)."), ComTxMode_true[tx_mode_id])$$END$$DIE()$
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
$			// [COM282_Conf][NCOM054] ComTxModeRepetitionPeriod
			$IF !LENGTH(ComTxMode_false.ComTxModeRepetitionPeriod[tx_mode_id]) && EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "PERIODIC")$
				$ComTxMode_false.ComTxModeRepetitionPeriod[tx_mode_id] = "0.0"$
			$ELSE$
				$IF EQ(ComTxMode_false.ComTxModeRepetitionPeriod[tx_mode_id], "0.0")$
					$ERROR$$FORMAT(_("Do not set to 0 in the ComTxModeRepetitionPeriod. (%1%\)."), ComTxMode_false[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
$			// [COM180_Conf] ComTxModeTimeOffset
			$IF !LENGTH(ComTxMode_false.ComTxModeTimeOffset[tx_mode_id])$
				$ComTxMode_false.ComTxModeTimeOffset[tx_mode_id] = "0.0"$
			$END$
$			// [COM178_Conf][NCOM055] ComTxModeTimePeriod
			$IF !LENGTH(ComTxMode_false.ComTxModeTimePeriod[tx_mode_id]) && EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "DIRECT")$
				$ComTxMode_false.ComTxModeTimePeriod[tx_mode_id] = "0.0"$
			$ELSE$
				$IF EQ(ComTxMode_false.ComTxModeTimePeriod[tx_mode_id], 0)$
					$ERROR$$FORMAT(_("Do not set to 0 in the ComTxModeTimePeriod. (%1%\)."), ComTxMode_false[tx_mode_id])$$END$$DIE()$
				$END$
			$END$
		$END$
	$END$

$	/*
$	 * [COM344_Conf][NCOM029] シグナルの設定値チェック
$	 */
	$FOREACH signal_id ComConfig.signal_list[com_config_id]$
$		// [COM127_Conf] ComSignalType
		$ComSignal.signal_type_str[signal_id] = CHECK_SIGNAL_TYPE(ComSignal.ComSignalType[signal_id], ComSignal.signal_type_str[signal_id])$

$		// [COM158_Conf] ComBitSize
		$ComSignal.ComBitSize[signal_id] = CHECK_SIGNAL_BITSIZE(ComSignal[signal_id], ComSignal.ComBitSize[signal_id], ComSignal.ComSignalType[signal_id])$

$		// [COM437_Conf] ComSignalLength
		$ComSignal.ComSignalLength[signal_id] = CHECK_SIGNAL_LENGTH(ComSignal[signal_id], ComSignal.ComSignalLength[signal_id], ComSignal.ComSignalType[signal_id])$

$		// [COM170_Conf] ComSignalInitValue
		$ComSignal.ComSignalInitValue[signal_id] = CHECK_SIGNAL_INIT_VALUE(ComSignal[signal_id], ComSignal.ComSignalInitValue[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComBitSize[signal_id], ComSignal.ComSignalLength[signal_id])$

$		// [COM391_Conf] ComSignalDataInvalidValue
		$CHECK_SIGNAL_INVALID_VALUE(ComSignal[signal_id], ComSignal.ComSignalDataInvalidValue[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComBitSize[signal_id], ComSignal.ComSignalLength[signal_id])$

$		// [COM157_Conf] ComSignalEndianness
		$CHECK_SIGNAL_ENDIANNESS(ComSignal[signal_id], ComSignal.ComSignalEndianness[signal_id], ComSignal.ComSignalType[signal_id])$

$		// [COM259_Conf] ComBitPosition
		$ComSignal.lsb[signal_id] = CHECK_SIGNAL_BITPOSITION(ComSignal[signal_id], ComSignal.ComBitPosition[signal_id], ComSignal.ComSignalEndianness[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComBitSize[signal_id])$

$		// [COM232_Conf] ComTransferProperty
		$IF LENGTH(ComSignal.ComTransferProperty[signal_id])$
			$IF !EQ(ComSignal.ComTransferProperty[signal_id], "PENDING")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION")
				&& !EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_WITHOUT_REPETITION")$
				$ERROR$$FORMAT(_("ComTransferProperty should not be set `%1%\'. (%2%\)"),ComSignal.ComTransferProperty[signal_id] , ComSignal[signal_id])$$END$$DIE()$
			$END$
		$ELSE$
$			// [NCOM042] 送信シグナルにComTransferPropertyが指定されていない場合はエラー
			$IF EQ(ComSignal.direction[signal_id], "SEND")$
				$ERROR$$FORMAT(_("Send Signal should be set value to ComTransferProperty. (%1%\)"), signal_id)$$END$$DIE()$
			$END$
			$ComSignal.ComTransferProperty[signal_id] = "INVALID_UINT8"$
		$END$

$		// [COM314_Conf] ComDataInvalidAction
		$ComSignal.ComDataInvalidAction[signal_id] = CHECK_SIGNAL_DATAINVALIDACTION(ComSignal[signal_id], ComSignal.ComDataInvalidAction[signal_id], ComSignal.ComSignalDataInvalidValue[signal_id])$

$		// [COM412_Conf] ComRxDataTimeoutAction
		$ComSignal.ComRxDataTimeoutAction[signal_id] = CHECK_SIGNAL_RXDATATIMEOUTACTION(ComSignal[signal_id], ComSignal.ComRxDataTimeoutAction[signal_id])$
		$IF LENGTH(ComSignal.ComRxDataTimeoutAction[signal_id])$
			$IF !EQ(ComSignal.ComRxDataTimeoutAction[signal_id], "NONE") && !EQ(ComSignal.ComRxDataTimeoutAction[signal_id], "REPLACE")$
				$ERROR$$FORMAT(_("ComRxDataTimeoutAction should not be set `%1%\'. (%2%\)"),ComSignal.ComRxDataTimeoutAction[signal_id] , ComSignal[signal_id])$$END$$DIE()$
			$END$
		$ELSE$
$			// [COM500]ComRxDataTimeoutActionが省略された場合はNONEと同等
			$ComSignal.ComRxDataTimeoutAction[signal_id] = "NONE"$
		$END$

$		// シグナルがIPDUバッファの外に配置されないかチェック
		$CHECK_SIGNAL_PLACE_IPDUBUF(ComSignal[signal_id], ComSignal.ComBitPosition[signal_id], ComSignal.ComSignalLength[signal_id], ComSignal.ComBitSize[signal_id], ComSignal.ipdu_ref[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComSignalEndianness[signal_id])$

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
				$ComSignal.ComTimeoutNotification[signal_id] = "NULL_PTR"$
			$ELSE$
$				// [COM402] 関数名はC言語で扱える文字列でなければならない
				$FUNC_NAME_CHECK(ComSignal.ComTimeoutNotification[signal_id])$
			$END$
		$END$

$		// [COM257_Conf] ComUpdateBitPosition
		$ComSignal.ComUpdateBitPosition[signal_id] = CHECK_SIGNAL_UPDATEBITPOSITION(ComSignal[signal_id], ComSignal.ComUpdateBitPosition[signal_id], ComSignal.ipdu_ref[signal_id])$

$		// [COM499_Conf] ComErrorNotification
		$ComSignal.ComErrorNotification[signal_id] = CHECK_SIGNAL_ERRORNOTIFICATION(ComSignal.ComErrorNotification[signal_id])$

$		// [COM315_Conf] ComInvalidNotification
		$ComSignal.ComInvalidNotification[signal_id] = CHECK_SIGNAL_INVALIDNOTIFICATION(ComSignal.ComInvalidNotification[signal_id])$

$		// [COM498_Conf] ComNotification
		$ComSignal.ComNotification[signal_id] = CHECK_SIGNAL_NOTIFICATION(ComSignal.ComNotification[signal_id])$
	$END$

$	/*
$	 * [COM520_Conf] グループシグナルの設定値チェック
$	 */
	$FOREACH signal_id ComConfig.g_signal_list[com_config_id]$

$		// [COM127_Conf] ComSignalType
		$ComGroupSignal.signal_type_str[signal_id] = CHECK_SIGNAL_TYPE(ComGroupSignal.ComSignalType[signal_id], ComGroupSignal.signal_type_str[signal_id])$

$		// [COM158_Conf] ComBitSize
		$ComGroupSignal.ComBitSize[signal_id] = CHECK_SIGNAL_BITSIZE(ComGroupSignal[signal_id], ComGroupSignal.ComBitSize[signal_id], ComGroupSignal.ComSignalType[signal_id])$

$		// [COM437_Conf] ComSignalLength
		$ComGroupSignal.ComSignalLength[signal_id] = CHECK_SIGNAL_LENGTH(ComGroupSignal[signal_id], ComGroupSignal.ComSignalLength[signal_id], ComGroupSignal.ComSignalType[signal_id])$

$		// [COM170_Conf] ComSignalInitValue
		$ComGroupSignal.ComSignalInitValue[signal_id] = CHECK_SIGNAL_INIT_VALUE(ComGroupSignal[signal_id], ComGroupSignal.ComSignalInitValue[signal_id], ComGroupSignal.ComSignalType[signal_id], ComGroupSignal.ComBitSize[signal_id], ComGroupSignal.ComSignalLength[signal_id])$

$		// [COM391_Conf] ComSignalDataInvalidValue
		$CHECK_SIGNAL_INVALID_VALUE(ComGroupSignal[signal_id], ComGroupSignal.ComSignalDataInvalidValue[signal_id], ComGroupSignal.ComSignalType[signal_id], ComGroupSignal.ComBitSize[signal_id], ComGroupSignal.ComSignalLength[signal_id])$

$		// [COM157_Conf] ComSignalEndianness
		$CHECK_SIGNAL_ENDIANNESS(ComGroupSignal[signal_id], ComGroupSignal.ComSignalEndianness[signal_id], ComGroupSignal.ComSignalType[signal_id])$

$		// [COM259_Conf] ComBitPosition
		$ComGroupSignal.lsb[signal_id] = CHECK_SIGNAL_BITPOSITION(ComGroupSignal[signal_id], ComGroupSignal.ComBitPosition[signal_id], ComGroupSignal.ComSignalEndianness[signal_id], ComGroupSignal.ComSignalType[signal_id], ComGroupSignal.ComBitSize[signal_id])$

$		// [COM560_Conf] ComTransferProperty
		$IF LENGTH(ComGroupSignal.ComTransferProperty[signal_id])$
			$IF !EQ(ComGroupSignal.ComTransferProperty[signal_id], "PENDING")
				&& !EQ(ComGroupSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE")$
				$ERROR$$FORMAT(_("ComTransferProperty should not be set `%1%\'. (%2%\)"),ComGroupSignal.ComTransferProperty[signal_id] , ComGroupSignal[signal_id])$$END$$DIE()$
			$END$
		$ELSE$
$			// [NCOM042]送信シグナルにComTransferPropertyが指定されていない場合はエラー
			$IF EQ(ComGroupSignal.direction[signal_id], "SEND")$
				$ERROR$$FORMAT(_("Send Signal should be set value to ComTransferProperty. (%1%\)"), signal_id)$$END$$DIE()$
			$END$
			$ComGroupSignal.ComTransferProperty[signal_id] = "INVALID_UINT8"$
		$END$
		
$		// グループシグナルがIPDUバッファの外に配置されないかチェック
		$CHECK_SIGNAL_PLACE_IPDUBUF(ComGroupSignal[signal_id], ComGroupSignal.ComBitPosition[signal_id], ComGroupSignal.ComSignalLength[signal_id], ComGroupSignal.ComBitSize[signal_id], ComSignalGroup.ipdu_ref[ComGroupSignal.PARENT[signal_id]], ComGroupSignal.ComSignalType[signal_id], ComGroupSignal.ComSignalEndianness[signal_id])$
	$END$

$	/*
$	 * [COM345_Conf] シグナルグループの設定値チェック
$	 */
	$FOREACH signal_id ComConfig.signal_g_list[com_config_id]$
$		// [COM232_Conf] ComTransferProperty
		$IF LENGTH(ComSignalGroup.ComTransferProperty[signal_id])$
			$IF !EQ(ComSignalGroup.ComTransferProperty[signal_id], "PENDING")
				&& !EQ(ComSignalGroup.ComTransferProperty[signal_id], "TRIGGERED")
				&& !EQ(ComSignalGroup.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE")
				&& !EQ(ComSignalGroup.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION")
				&& !EQ(ComSignalGroup.ComTransferProperty[signal_id], "TRIGGERED_WITHOUT_REPETITION")$
				$ERROR$$FORMAT(_("ComTransferProperty should not be set `%1%\'. (%2%\)"),ComSignalGroup.ComTransferProperty[signal_id] , ComSignalGroup[signal_id])$$END$$DIE()$
			$END$
		$ELSE$
$			// [NCOM042]送信シグナルにComTransferPropertyが指定されていない場合はエラー
			$IF EQ(ComSignalGroup.direction[signal_id], "SEND")$
				$ERROR$$FORMAT(_("Send Signal should be set value to ComTransferProperty. (%1%\)"), signal_id)$$END$$DIE()$
			$END$
			$ComSignalGroup.ComTransferProperty[signal_id] = "INVALID_UINT8"$
		$END$

$		// [COM314_Conf] ComDataInvalidAction
		$ComSignalGroup.ComDataInvalidAction[signal_id] = CHECK_SIGNAL_GRUOP_DATAINVALIDACTION(ComSignalGroup[signal_id], ComSignalGroup.ComDataInvalidAction[signal_id], ComSignalGroup.gg_signal_list[signal_id])$

$		// [COM412_Conf] ComRxDataTimeoutAction
		$ComSignalGroup.ComRxDataTimeoutAction[signal_id] = CHECK_SIGNAL_RXDATATIMEOUTACTION(ComSignalGroup[signal_id], ComSignalGroup.ComRxDataTimeoutAction[signal_id])$

$		// グループシグナル毎にtimeout設定
		$FOREACH g_signal_id ComGroupSignal.ID_LIST$
			$IF EQ(signal_id, ComGroupSignal.PARENT[g_signal_id])$
				$ComGroupSignal.gs_timeout[g_signal_id] = ComSignalGroup.timeout[signal_id]$
			$END$
		$END$

$		// [COM263_Conf][COM183_Conf][COM552_Conf]
$		// デッドラインモニタリング関連のパラメータチェック
		$IF EQ(ComSignalGroup.direction[signal_id], "SEND")$
			$IF ComSignalGroup.timeout[signal_id] != 0$
				$ComSignalGroup.timeout[signal_id] = ComIPdu.timeout_min[ComSignalGroup.ipdu_ref[signal_id]]$
			$END$
			$IF ComSignalGroup.first_timeout[signal_id] != 0$
				$ComSignalGroup.first_timeout[signal_id] = ComIPdu.first_timeout_min[ComSignalGroup.ipdu_ref[signal_id]]$
			$END$
		$ELIF EQ(ComSignalGroup.direction[signal_id], "RECEIVE")$
			$IF (ComSignalGroup.timeout[signal_id] != 0) && !LENGTH(ComSignalGroup.ComUpdateBitPosition[signal_id])$
				$ComSignalGroup.timeout[signal_id] = ComIPdu.timeout_min[ComSignalGroup.ipdu_ref[signal_id]]$
			$END$
			$IF (ComSignalGroup.first_timeout[signal_id] != 0) && !LENGTH(ComSignalGroup.ComUpdateBitPosition[signal_id])$
				$ComSignalGroup.first_timeout[signal_id] = ComIPdu.first_timeout_min[ComSignalGroup.ipdu_ref[signal_id]]$
			$END$
		$END$

		$IF !LENGTH(ComSignalGroup.ComTimeoutNotification[signal_id])$
			$IF ComSignalGroup.timeout[signal_id] != 0$
$				// タイムアウト通知用コールバックが設定されていないが，タイムアウト値が設定されている場合は警告
				$WARNING$$FORMAT(_("ComTimeoutNotification is omit. (%1%\)"), ComSignalGroup[signal_id])$$END$
			$END$
			$ComSignalGroup.ComTimeoutNotification[signal_id] = "NULL_PTR"$
		$ELSE$
			$IF ComSignalGroup.timeout[signal_id] == 0$
$				// タイムアウト通知用コールバックが設定されているが，タイムアウト値が0の場合は警告
				$WARNING$$FORMAT(_("ComTimeout is omit. ComTimeoutNotification will not be used. (%1%\)"), ComSignalGroup[signal_id])$$END$
				$ComSignalGroup.ComTimeoutNotification[signal_id] = "NULL_PTR"$
			$ELSE$
$				// [COM402] 関数名はC言語で扱える文字列でなければならない
				$FUNC_NAME_CHECK(ComSignalGroup.ComTimeoutNotification[signal_id])$
			$END$
		$END$

$		// [COM257_Conf] ComUpdateBitPosition
		$ComSignalGroup.ComUpdateBitPosition[signal_id] = CHECK_SIGNAL_UPDATEBITPOSITION(ComSignalGroup[signal_id], ComSignalGroup.ComUpdateBitPosition[signal_id], ComSignalGroup.ipdu_ref[signal_id])$
		
$		// [COM499_Conf] ComErrorNotification
		$ComSignalGroup.ComErrorNotification[signal_id] = CHECK_SIGNAL_ERRORNOTIFICATION(ComSignalGroup.ComErrorNotification[signal_id])$

$		// [COM315_Conf] ComInvalidNotification
		$ComSignalGroup.ComInvalidNotification[signal_id] = CHECK_SIGNAL_INVALIDNOTIFICATION(ComSignalGroup.ComInvalidNotification[signal_id])$

$		// [COM498_Conf] ComNotification
		$ComSignalGroup.ComNotification[signal_id] = CHECK_SIGNAL_NOTIFICATION(ComSignalGroup.ComNotification[signal_id])$
	$END$

$	/*
$	 * [COM339_Conf]フィルタの設定値チェック
$	 */
	$FOREACH filter_id ComConfig.filter_list[com_config_id]$
		$signal_ref_id = ComFilter.PARENT[filter_id]$
		$ComFilter.config_ref_id[filter_id] = com_config_id$
		$ComSignal.filter_ref_id[signal_ref_id] = filter_id$
		$signal_type = ComSignal.ComSignalType[signal_ref_id]$
		$signal_size = ComSignal.ComBitSize[signal_ref_id]$

		$CHECK_SIGNAL_FILTER_CONFIG(ComSignal[signal_ref_id], signal_type, signal_size, filter_id)$
	$END$

$	/*
$	 * [COM339_Conf]グループシグナルフィルタの設定値チェック
$	 */
	$FOREACH filter_id ComConfig.g_filter_list[com_config_id]$
		$signal_ref_id = ComFilter.PARENT[filter_id]$
		$ComFilter.config_ref_id[filter_id] = com_config_id$
		$ComGroupSignal.filter_ref_id[signal_ref_id] = filter_id$
		$signal_type = ComGroupSignal.ComSignalType[signal_ref_id]$
		$signal_size = ComGroupSignal.ComBitSize[signal_ref_id]$

		$IF EQ(ComGroupSignal.direction[signal_ref_id], "SEND")$
			$CHECK_SIGNAL_FILTER_CONFIG(ComGroupSignal[signal_ref_id], signal_type, signal_size, filter_id)$
		$ELSE$
$			//[COM327] 受信側のグループシグナルにフィルタを設定した場合は警告
			$WARNING$$FORMAT(_("`%1%\' does not have to set ComFilter."), signal_ref_id)$$END$
		$END$
	$END$

$	// [NCOM041] ComFilterAlgorithmに従ったComTxModeTrueとComTxModeFalseのチェック
	$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
$		// ComFilterの有無，ComFilterAlgorithmをチェック
		$filter_cnt = 0$
		$all_always_flg = "true"$
		$all_never_flg = "true"$
$		// 単独シグナル
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
$		// シグナルグループ
		$FOREACH signal_g_id ComIPdu.ComIPduSignalGroupRef[ipdu_id]$
			$FOREACH g_signal_id ComSignalGroup.gg_signal_list[signal_g_id]$
				$FOREACH filter_g_id ComConfig.g_filter_list[com_config_id]$
					$IF EQ(g_signal_id, ComFilter.PARENT[filter_g_id])$
						$filter_cnt = filter_cnt + 1$
						$IF !EQ(ComFilter.ComFilterAlgorithm[filter_g_id], "ALWAYS")$
							$all_always_flg = "false"$
						$END$
						$IF !EQ(ComFilter.ComFilterAlgorithm[filter_g_id], "NEVER")$
							$all_never_flg = "false"$
						$END$
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

	#include "ComStack_Types.h"$NL$
	$NL$

	/* IPDU Callout */$NL$
	$FOREACH ipdu_id ComIPdu.ID_LIST$
		$IF !EQ(ComIPdu.ComIPduCallout[ipdu_id], "NULL_PTR")$
			boolean $ComIPdu.ComIPduCallout[ipdu_id]$(PduIdType Id, uint8* IpduData);$NL$
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
$	// [COM141_Conf][COM028][NCOM103] ComConfigurationUseDet
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

$	// [NCOM056] コンフィグ数を取得
	$cnt = 0$
	$FOREACH config_id ComConfig.ID_LIST$
		$cnt = cnt + 1$
	$END$
	#define COM_CONFIG_NUM $cnt$U$NL$
	$NL$

	/* [ecuc_sws_2108] */$NL$
$	// [COM163] 各シグナルのショートネームをComHandleIdの設定値を用いて定義する
	$FOREACH signal_id ComSignal.ID_LIST$
		#define ComConf_ComSignal_$ComSignal[signal_id]$ $ComSignal.ComHandleId[signal_id]$U$NL$
	$END$
$	// [COM521] 各グループシグナルのショートネームをComHandleIdの設定値を用いて定義する
	$FOREACH g_signal_id ComGroupSignal.ID_LIST$
		#define ComConf_ComSignal_$g_signal_id$ $ComGroupSignal.ComHandleId[g_signal_id]$U$NL$
	$END$
	$NL$

$	// [COM044] 各シグナルグループのショートネームをComHandleIdの設定値を用いて定義する
	$FOREACH signal_id ComSignalGroup.ID_LIST$
		#define ComConf_ComSignalGroup_$ComSignalGroup[signal_id]$ $ComSignalGroup.ComHandleId[signal_id]$U$NL$
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
		$IF !EQ(ipdu_length, 0)$
			static uint8 ipdu_buffer_$ComIPdu.PARENT[ipdu_id]$_$ComIPdu[ipdu_id]$[$ipdu_length$];$NL$
		$END$
	$END$
	$NL$

$	// シグナルバッファ定義
	$IF LENGTH(ComConfig.signal_list[com_config_id])$
		/* シグナルバッファ：signal_buffer_<ComConfig>_<ComSignal> */$NL$
		$FOREACH signal_id ComConfig.signal_list[com_config_id]$
$			$IF EQ(ComSignal.direction[signal_id], "RECEIVE")
$				|| EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE")
$				|| EQ(ComSignal.ComTransferProperty[signal_id], "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION")$
				$GEN_SIGNAL_BUF(ComSignal[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComSignalLength[signal_id])$
$			$END$
		$END$
		$NL$
	$END$

$	// グループシグナルバッファ定義
	$IF LENGTH(ComConfig.g_signal_list[com_config_id])$
		/* グループシグナルバッファ：signal_buffer_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH g_signal_id ComConfig.g_signal_list[com_config_id]$
			$GEN_SIGNAL_BUF(ComGroupSignal[g_signal_id], ComGroupSignal.ComSignalType[g_signal_id], ComGroupSignal.ComSignalLength[g_signal_id])$
		$END$
		$NL$
	$END$

$	// シャドウバッファ定義
	$IF LENGTH(ComConfig.g_signal_list[com_config_id])$
		/* シャドウバッファ：shadow_buffer_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH g_signal_id ComConfig.g_signal_list[com_config_id]$
			$IF EQ(ComGroupSignal.ComSignalType[g_signal_id], "BOOLEAN")$
				static boolean shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "UINT8")$
				static uint8   shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "UINT16")$
				static uint16  shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "UINT32")$
				static uint32  shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "SINT8")$
				static sint8   shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "SINT16")$
				static sint16  shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "SINT32")$
				static sint32  shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "UINT8_N")$
				static uint8   shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$[$ComGroupSignal.ComSignalLength[g_signal_id]$];$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "FLOAT32")$
				static float32  shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.ComSignalType[g_signal_id], "FLOAT64")$
				static float64  shadow_buffer_$com_config_id$_$ComGroupSignal[g_signal_id]$;$NL$
			$END$
		$END$
		$NL$
	$END$

$	// フィルタバッファ定義
$	// シグナル
	$IF LENGTH(ComConfig.filter_list[com_config_id])$
		/* シグナルフィルタバッファ: filter_buffer_<ComConfig>_<ComSignal> */$NL$
		$FOREACH filter_id ComConfig.filter_list[com_config_id]$
$			// フィルタバッファはアルゴリズムがMASKED_NEW_DIFFERS_MASKED_OLDである場合のみに生成する
			$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
				$signal_ref_id = ComFilter.PARENT[filter_id]$
				static $ComSignal.signal_type_str[signal_ref_id]$ filter_buffer_$com_config_id$_$signal_ref_id$;$NL$
			$END$
		$END$
		$NL$
	$END$

$	// グループシグナル
	$IF LENGTH(ComConfig.g_filter_list[com_config_id])$
		/* グループシグナルフィルタバッファ: filter_buffer_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH filter_id ComConfig.g_filter_list[com_config_id]$
$			// フィルタバッファはアルゴリズムがMASKED_NEW_DIFFERS_MASKED_OLDである場合のみに生成する
			$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
				$signal_ref_id = ComFilter.PARENT[filter_id]$
				static $ComGroupSignal.signal_type_str[signal_ref_id]$ filter_buffer_$com_config_id$_$signal_ref_id$;$NL$
			$END$
		$END$
		$NL$
	$END$

$	// シグナル管理ブロック (受信シグナルは受信DM使用時のみ必要，送信シグナルはフィルタ使用時のみ必要)
	$IF LENGTH(ComConfig.signal_list[com_config_id])$
		/* シグナル管理ブロック：<送受信>_signal_cb_<ComConfig>_<ComSignal> */$NL$
		$FOREACH signal_id ComConfig.signal_list[com_config_id]$
$			$IF EQ(ComSignal.direction[signal_id], "SEND") && LENGTH(ComSignal.filter_ref_id[signal_id])$
			$IF EQ(ComSignal.direction[signal_id], "SEND")$
				static TX_SIGNAL_CB tx_signal_cb_$ComIPdu.PARENT[ipdu_id]$_$ComSignal[signal_id]$;$NL$
			$ELIF EQ(ComSignal.direction[signal_id], "RECEIVE") && (ComSignal.timeout[signal_id] != 0)$
				static RX_SIGNAL_CB rx_signal_cb_$ComIPdu.PARENT[ipdu_id]$_$ComSignal[signal_id]$;$NL$
			$END$
		$END$
		$NL$
	$END$

$	// グループシグナル管理ブロック (受信シグナルは受信DM使用時のみ必要，送信シグナルはフィルタ使用時のみ必要)
	$IF LENGTH(ComConfig.g_signal_list[com_config_id])$
		/* グループシグナル管理ブロック：<送受信>_signal_cb_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH signal_id ComConfig.g_signal_list[com_config_id]$
			$IF EQ(ComGroupSignal.direction[signal_id], "SEND")$
				static TX_SIGNAL_CB tx_signal_cb_$ComIPdu.PARENT[ipdu_id]$_$ComGroupSignal[signal_id]$;$NL$
			$ELIF EQ(ComGroupSignal.direction[signal_id], "RECEIVE") && (ComGroupSignal.gs_timeout[signal_id] != 0)$
				static RX_SIGNAL_CB rx_signal_cb_$ComIPdu.PARENT[ipdu_id]$_$ComGroupSignal[signal_id]$;$NL$
			$END$
		$END$
		$NL$
	$END$

$	// シグナルグループ管理ブロック
	$IF LENGTH(ComConfig.signal_g_list[com_config_id])$
		/* シグナルグループ管理ブロック：<送受信>_signal_cb_<ComConfig>_<ComSignalGroup> */$NL$
		$FOREACH signal_id ComConfig.signal_g_list[com_config_id]$
			$IF EQ(ComSignalGroup.direction[signal_id], "SEND")$
				static TX_SIGNAL_G_CB tx_signal_g_cb_$ComIPdu.PARENT[ipdu_id]$_$signal_id$;$NL$
			$ELIF EQ(ComSignalGroup.direction[signal_id], "RECEIVE") && (ComSignalGroup.timeout[signal_id] != 0)$
				static RX_SIGNAL_G_CB rx_signal_g_cb_$ComIPdu.PARENT[ipdu_id]$_$signal_id$;$NL$
			$END$
		$END$
		$NL$
	$END$

$	// [COM790] シグナル無効値は指定された型に従って解釈する
	$IF LENGTH(ComConfig.signal_list[com_config_id])$
		/* シグナル無効値：signal_invalid_value_<ComConfig>_<ComSignal> */$NL$
		$FOREACH signal_id ComConfig.signal_list[com_config_id]$
			$GEN_SIGNAL_INVALID_VALUE(ComSignal[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComSignalLength[signal_id], ComSignal.ComSignalDataInvalidValue[signal_id])$
		$END$
		$NL$
	$END$

	$IF LENGTH(ComConfig.g_signal_list[com_config_id])$
		/* グループシグナル無効値：signal_invalid_value_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH signal_id ComConfig.g_signal_list[com_config_id]$
			$GEN_SIGNAL_INVALID_VALUE(ComGroupSignal[signal_id], ComGroupSignal.ComSignalType[signal_id], ComGroupSignal.ComSignalLength[signal_id], ComGroupSignal.ComSignalDataInvalidValue[signal_id])$
		$END$
		$NL$
	$END$

$	// [COM790] シグナル初期値は指定された型に従って解釈する
$	// [COM723] シグナル初期値は指定された型のサイズに合わせる

	$IF LENGTH(ComConfig.signal_list[com_config_id])$
		/* シグナル初期値：signal_init_value_<ComConfig>_<ComSignal> */$NL$
		$FOREACH signal_id ComConfig.signal_list[com_config_id]$
			$GEN_SIGNAL_INIT_VALUE(ComSignal[signal_id], ComSignal.ComSignalType[signal_id], ComSignal.ComSignalLength[signal_id], ComSignal.ComSignalInitValue[signal_id])$
		$END$
		$NL$
	$END$

	$IF LENGTH(ComConfig.g_signal_list[com_config_id])$
	/* グループシグナル初期値：signal_init_value_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH signal_id ComConfig.g_signal_list[com_config_id]$
			$GEN_SIGNAL_INIT_VALUE(ComGroupSignal[signal_id], ComGroupSignal.ComSignalType[signal_id], ComGroupSignal.ComSignalLength[signal_id], ComGroupSignal.ComSignalInitValue[signal_id])$
		$END$
		$NL$
	$END$

$	// OCCURRENCEカウンタ
	$IF LENGTH(ComConfig.filter_list[com_config_id])$
		/* シグナルOCCURRENCEカウンタ : occur_<ComConfig>_<ComSignal> */$NL$
		$FOREACH filter_id ComConfig.filter_list[com_config_id]$
			$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
				static uint32 occur_$com_config_id$_$ComFilter.PARENT[filter_id]$;$NL$
			$END$
		$END$
	$END$

	$IF LENGTH(ComConfig.g_filter_list[com_config_id])$
		/* グループシグナルOCCURRENCEカウンタ : occur_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH filter_id ComConfig.g_filter_list[com_config_id]$
			$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
				static uint32 occur_$com_config_id$_$ComFilter.PARENT[filter_id]$;$NL$
			$END$
		$END$
	$END$
	$NL$

$	// フィルタ初期化ブロック
	$IF LENGTH(ComConfig.filter_list[com_config_id])$
		/* シグナルフィルタ初期化ブロック : filter_inib_<ComConfig>_<ComSignal> */$NL$
		$FOREACH filter_id ComConfig.filter_list[com_config_id]$
			$signal_ref_id = ComFilter.PARENT[filter_id]$
			$GEN_SIGNAL_FILTER_INITBLOCK(ComSignal.ComSignalType[signal_ref_id], filter_id, signal_ref_id)$
		$END$
		$NL$
	$END$

	$IF LENGTH(ComConfig.g_filter_list[com_config_id])$
		/* グループシグナルフィルタ初期化ブロック : filter_inib_<ComConfig>_<ComGroupSignal> */$NL$
		$FOREACH filter_id ComConfig.g_filter_list[com_config_id]$
			$signal_ref_id = ComFilter.PARENT[filter_id]$
			$GEN_SIGNAL_FILTER_INITBLOCK(ComGroupSignal.ComSignalType[signal_ref_id], filter_id, signal_ref_id)$
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
	$IF LENGTH(ComConfig.signal_list[com_config_id])$
		/* 所属シグナルIDリスト：signalid_list_<ComConfig>_<ComIPdu> */$NL$
		$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
			$IF LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id]) != 0$
				static const Com_SignalIdType signalid_list_$com_config_id$_$ComIPdu[ipdu_id]$[$LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id])$] = {$NL$
				$JOINEACH signal_id ComIPdu.ComIPduSignalRef[ipdu_id] ",\n"$
					$TAB$/* $ComSignal[signal_id]$ */$NL$
					$TAB$$ComSignal.ComHandleId[signal_id]$U
				$END$
				$NL$};$NL$
			$END$
		$END$
		$NL$
	$END$

$	// 所属グループシグナルIDリスト
	$IF LENGTH(ComConfig.g_signal_list[com_config_id])$
		/* 所属グループシグナルIDリスト：gsignalid_list_<ComConfig>_<ComSignalGroup> */$NL$
		$FOREACH signal_g_id ComConfig.signal_g_list[com_config_id]$
			static const Com_SignalIdType gsignalid_list_$com_config_id$_$ComSignalGroup[signal_g_id]$[$ComSignalGroup.gg_signal_num[signal_g_id]$] = {$NL$
			$JOINEACH g_signal_id ComSignalGroup.gg_signal_list[signal_g_id] ",\n"$
				$TAB$/* $ComGroupSignal[g_signal_id]$ */$NL$
				$TAB$$ComGroupSignal.ComHandleId[g_signal_id]$U
			$END$
			$NL$};$NL$
		$END$
		$NL$
	$END$

$	// 所属シグナルグループIDリスト
	$IF LENGTH(ComConfig.signal_g_list[com_config_id])$
		/* 所属シグナルグループIDリスト：signalgid_list_<ComConfig>_<ComIPdu> */$NL$
		$FOREACH ipdu_id ComConfig.ipdu_list[com_config_id]$
			$IF !EQ(0, LENGTH(ComIPdu.ComIPduSignalGroupRef[ipdu_id]))$
				static const Com_SignalIdType signalgid_list_$com_config_id$_$ComIPdu[ipdu_id]$[$LENGTH(ComIPdu.ComIPduSignalGroupRef[ipdu_id])$] = {$NL$
				$JOINEACH signal_g_id ComIPdu.ComIPduSignalGroupRef[ipdu_id] ",\n"$
					$TAB$/* $ComSignalGroup[signal_g_id]$ */$NL$
					$TAB$$ComSignalGroup.ComHandleId[signal_g_id]$U
				$END$
				$NL$};$NL$
			$END$
		$END$
		$NL$
	$END$

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
					$div_result = DIV_FLOAT_VALUE(div_num1, div_num2, "ComTxModeRepetitionPeriod", "ComTxTimeBase")$
					$TAB$$div_result$U,$TAB$/* ComTxModeRepetitionPeriod ($div_num1$ / $div_num2$) */$NL$
$					// [NCOM020] ComTxModeTimeOffsetはMF呼出し回数に+1する
					$div_num1 = ComTxMode_true.ComTxModeTimeOffset[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV_FLOAT_VALUE(div_num1, div_num2, "ComTxModeTimeOffset", "ComTxTimeBase")$
					$TAB$($div_result$U + 1U),$TAB$/* ComTxModeTimeOffset (($div_num1$ / $div_num2$) + 1) */$NL$
$					// [NCOM005] ComTxModeTimePeriodをMF呼出し回数に変換
					$div_num1 = ComTxMode_true.ComTxModeTimePeriod[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV_FLOAT_VALUE(div_num1, div_num2, "ComTxModeTimePeriod", "ComTxTimeBase")$
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
					$div_result = DIV_FLOAT_VALUE(div_num1, div_num2, "ComTxModeRepetitionPeriod", "ComTxTimeBase")$
					$TAB$$div_result$U,$TAB$/* ComTxModeRepetitionPeriod ($div_num1$ / $div_num2$) */$NL$
$					// [NCOM020] ComTxModeTimeOffsetはMF呼出し回数に+1する
					$div_num1 = ComTxMode_false.ComTxModeTimeOffset[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV_FLOAT_VALUE(div_num1, div_num2, "ComTxModeTimeOffset", "ComTxTimeBase")$
					$TAB$($div_result$U + 1U),$TAB$/* ComTxModeTimeOffset (($div_num1$ / $div_num2$) + 1) */$NL$
$					// [NCOM005] ComTxModeTimePeriodをMF呼出し回数に変換
					$div_num1 = ComTxMode_false.ComTxModeTimePeriod[tx_mode_id]$
					$div_num2 = ComConfig.tx_time_base[com_config_id]$
					$div_result = DIV_FLOAT_VALUE(div_num1, div_num2, "ComTxModeTimePeriod", "ComTxTimeBase")$
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
					$div_result = DIV_FLOAT_VALUE(div_num1, div_num2, "ComMinimumDelayTime", "ComTxTimeBase")$
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

			$IF !EQ(0, LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id]))$
				$TAB$$TAB$signalid_list_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* 所属シグナルIDリスト */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* 所属シグナルIDリスト */$NL$
			$END$

			$IF !EQ(0, LENGTH(ComIPdu.ComIPduSignalGroupRef[ipdu_id]))$
				$TAB$$TAB$signalgid_list_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* 所属シグナルグループIDリスト */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* 所属シグナルグループIDリスト */$NL$
			$END$

			$TAB$$TAB$&ipdu_group_vector_$com_config_id$[$ComIPdu.ComIPduHandleId[ipdu_id]$],$TAB$/* IPDU所属グループベクタ */$NL$
			$TAB$$TAB$(void *)&tx_ipdu_cb_list_$com_config_id$[$ComIPdu.list_pos[ipdu_id]$],$TAB$/* IPDU管理リスト */$NL$

			$IF !EQ(ComIPdu.pdu_length[ipdu_id], 0)$
				$TAB$$TAB$ipdu_buffer_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDUバッファ */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* IPDUバッファ */$NL$
			$END$

			$TAB$$TAB$&state_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDU状態 */$NL$
			$TAB$$TAB$$LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id])$U,$TAB$/* tnum_signal */$NL$
			$TAB$$TAB$$LENGTH(ComIPdu.ComIPduSignalGroupRef[ipdu_id])$U,$TAB$/* tnum_signal_g */$NL$
			$TAB$$TAB$$ComIPdu.timeout_min[ipdu_id]$U$TAB$/* ipdu_timeout */$NL$
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

			$IF !EQ(0, LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id]))$
				$TAB$$TAB$signalid_list_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* 所属シグナルIDリスト */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* 所属シグナルIDリスト */$NL$
			$END$

			$IF !EQ(0, LENGTH(ComIPdu.ComIPduSignalGroupRef[ipdu_id]))$
				$TAB$$TAB$signalgid_list_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* 所属シグナルグループIDリスト */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* 所属シグナルグループIDリスト */$NL$
			$END$

			$TAB$$TAB$&ipdu_group_vector_$com_config_id$[$ComIPdu.ComIPduHandleId[ipdu_id]$],$TAB$/* IPDU所属グループベクタ */$NL$
			$TAB$$TAB$NULL_PTR,$TAB$/* IPDU管理リスト */$NL$

			$IF !EQ(ComIPdu.pdu_length[ipdu_id], 0)$
				$TAB$$TAB$ipdu_buffer_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDUバッファ */$NL$
			$ELSE$
				$TAB$$TAB$NULL_PTR,$TAB$/* IPDUバッファ */$NL$
			$END$

			$TAB$$TAB$&state_$com_config_id$_$ComIPdu[ipdu_id]$,$TAB$/* IPDU状態 */$NL$
			$TAB$$TAB$$LENGTH(ComIPdu.ComIPduSignalRef[ipdu_id])$U,$TAB$/* tnum_signal */$NL$
			$TAB$$TAB$$LENGTH(ComIPdu.ComIPduSignalGroupRef[ipdu_id])$U,$TAB$/* tnum_signal_g */$NL$
			$TAB$$TAB$$ComIPdu.timeout_min[ipdu_id]$U$TAB$/* ipdu_timeout */$NL$
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

$	// [COM639] シグナルグループ初期化ブロック
	$IF LENGTH(ComConfig.signal_g_list[com_config_id])$
		/* シグナルグループ初期化ブロックテーブル：signal_g_inib_table_<ComConfig> */$NL$
		$g_signal_cnt = 0$
		static const SIGNAL_G_INIB signal_g_inib_table_$com_config_id$[$ComConfig.signal_g_num[com_config_id]$] = {$NL$
		$JOINEACH signal_id ComConfig.signal_g_list[com_config_id] ",\n"$
			$ComSignalGroup.list_pos[signal_id] = g_signal_cnt$
			$g_signal_cnt = g_signal_cnt + 1$

			$TAB$/* $ComSignalGroup[signal_id]$ */$NL$
			$TAB${$NL$
			$IF EQ(ComSignalGroup.ComUpdateBitPosition[signal_id], "COM_INVALID_UINT16")$
				$TAB$$TAB$$ComSignalGroup.ComUpdateBitPosition[signal_id]$,$TAB$/* ComUpdateBitPosition */$NL$
			$ELSE$
				$TAB$$TAB$$ComSignalGroup.ComUpdateBitPosition[signal_id]$U,$TAB$/* ComUpdateBitPosition */$NL$
			$END$
			$TAB$$TAB$COM_$ComSignalGroup.ComTransferProperty[signal_id]$,$TAB$/* ComTransferProperty */$NL$
			$IF (ComSignalGroup.first_timeout[signal_id] != 0)$
$				// [NCOM033] ComFirstTimeoutが有効値の場合，MF呼出し回数を算出して+1する
				$TAB$$TAB$($ComSignalGroup.first_timeout[signal_id]$U + 1U),$TAB$/* ComFirstTimeout */$NL$
			$ELSE$
				$TAB$$TAB$$ComSignalGroup.first_timeout[signal_id]$U,$TAB$/* ComFirstTimeout */$NL$
			$END$
			$TAB$$TAB$$ComSignalGroup.timeout[signal_id]$U,$TAB$/* ComTimeout */$NL$
			$TAB$$TAB$COM_$ComSignalGroup.ComDataInvalidAction[signal_id]$,$TAB$/* ComDataInvalidAction */$NL$
			$TAB$$TAB$COM_$ComSignalGroup.ComRxDataTimeoutAction[signal_id]$,$TAB$/* ComRxDataTimeoutAction */$NL$
			$IF EQ(ComSignalGroup.ComNotification[signal_id], "NULL_PTR")$
				$TAB$$TAB$$ComSignalGroup.ComNotification[signal_id]$,$TAB$/* ComNotification */$NL$
			$ELSE$
				$TAB$$TAB$&$ComSignalGroup.ComNotification[signal_id]$,$TAB$/* ComNotification */$NL$
			$END$
			$IF EQ(ComSignalGroup.ComErrorNotification[signal_id], "NULL_PTR")$
				$TAB$$TAB$$ComSignalGroup.ComErrorNotification[signal_id]$,$TAB$/* ComErrorNotification */$NL$
			$ELSE$
				$TAB$$TAB$&$ComSignalGroup.ComErrorNotification[signal_id]$,$TAB$/* ComErrorNotification */$NL$
			$END$
			$IF EQ(ComSignalGroup.ComInvalidNotification[signal_id], "NULL_PTR")$
				$TAB$$TAB$$ComSignalGroup.ComInvalidNotification[signal_id]$,$TAB$/* ComInvalidNotification */$NL$
			$ELSE$
				$TAB$$TAB$&$ComSignalGroup.ComInvalidNotification[signal_id]$,$TAB$/* ComInvalidNotification */$NL$
			$END$
			$IF EQ(ComSignalGroup.ComTimeoutNotification[signal_id], "NULL_PTR")$
				$TAB$$TAB$$ComSignalGroup.ComTimeoutNotification[signal_id]$,$TAB$/* ComTimeoutNotification */$NL$
			$ELSE$
				$TAB$$TAB$&$ComSignalGroup.ComTimeoutNotification[signal_id]$,$TAB$/* ComTimeoutNotification */$NL$
			$END$
			$TAB$$TAB$gsignalid_list_$com_config_id$_$ComSignalGroup[signal_id]$,$TAB$/* 所属グループシグナルIDリスト */$NL$
			$belong_ipdu_id = ComSignalGroup.ipdu_ref[signal_id]$

			$IF EQ(ComSignalGroup.direction[signal_id], "SEND")$
				$TAB$$TAB$&tx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[belong_ipdu_id]$],$TAB$/* $belong_ipdu_id$ */$NL$
			$ELIF EQ(ComSignalGroup.direction[signal_id], "RECEIVE")$
				$TAB$$TAB$&rx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[belong_ipdu_id]$],$TAB$/* $belong_ipdu_id$ */$NL$
			$END$

$			// シグナルグループごとのグループシグナル数
			$find = 0$
			$FOREACH g_signal_id ComGroupSignal.ID_LIST$
				$IF EQ(signal_id, ComGroupSignal.PARENT[g_signal_id])$
					$find = 1$
				$END$
			$END$
			$IF find == 1$
				$TAB$$TAB$$ComSignalGroup.gg_signal_num[signal_id]$U,$TAB$/* tnum_g_signal */$NL$
			$END$

$			// シグナルグループ管理ブロック
			$IF EQ(ComSignalGroup.direction[signal_id], "SEND")$
				$TAB$$TAB$(void *)&tx_signal_g_cb_$com_config_id$_$signal_id$$TAB$/* シグナルグループ管理ブロック */$NL$
			$ELIF EQ(ComSignalGroup.direction[signal_id], "RECEIVE") && (ComSignalGroup.timeout[signal_id] != 0)$
				$TAB$$TAB$(void *)&rx_signal_g_cb_$com_config_id$_$signal_id$$TAB$/* シグナルグループ管理ブロック */$NL$
			$ELSE$
$				// 受信の場合，受信DMがなければNULL_PTR
				$TAB$$TAB$NULL_PTR,$TAB$/* シグナル管理ブロック */$NL$
			$END$
			$TAB$}
		$END$
		$NL$};$NL$
		$NL$
	$END$

$	// シグナル初期化ブロック
	/* シグナル初期化ブロックテーブル：signal_inib_table_<ComConfig> */$NL$
	static const SIGNAL_INIB signal_inib_table_$com_config_id$[$ComConfig.gs_signal_num[com_config_id]$] = {
	$FOREACH index RANGE(0, LENGTH(ComConfig.signal_list[config_id]) + LENGTH(ComConfig.g_signal_list[config_id]) - 1)$
		$find = 0$
		$IF LENGTH(ComConfig.signal_list[config_id])$
			$FOREACH signal_id ComConfig.signal_list[config_id]$
				$IF find == 0$
					$IF ComSignal.ComHandleId[signal_id] == index$
						$SIGNAL_INIB(signal_id)$
						$IF !EQ(index, LENGTH(ComConfig.signal_list[config_id]) + LENGTH(ComConfig.g_signal_list[config_id]) - 1)$
							,
						$END$
						$find = 1$
					$ELSE$
						$FOREACH gsignal_id ComConfig.g_signal_list[config_id]$
							$IF find == 0$
								$IF ComGroupSignal.ComHandleId[gsignal_id] == index$
									$G_SIGNAL_INIB(gsignal_id)$
									$IF !EQ(index, LENGTH(ComConfig.signal_list[config_id]) + LENGTH(ComConfig.g_signal_list[config_id]) - 1)$
										,
									$END$
									$find = 1$
								$END$
							$END$
						$END$
					$END$
				$END$
			$END$
		$ELSE$
			$FOREACH gsignal_id ComConfig.g_signal_list[config_id]$
				$IF find == 0$
					$IF ComGroupSignal.ComHandleId[gsignal_id] == index$
						$G_SIGNAL_INIB(gsignal_id)$
						$IF !EQ(index, LENGTH(ComConfig.signal_list[config_id]) + LENGTH(ComConfig.g_signal_list[config_id]) - 1)$
							,
						$END$
						$find = 1$
					$END$
				$END$
			$END$
		$END$
	$END$
	$NL$};$NL$
	$NL$

$END$

$	//シグナル
$FUNCTION SIGNAL_INIB$
	$signal_id = ARGV[1]$
	$NL$
	$TAB$/* $ComSignal[signal_id]$ */$NL$
	$TAB${$NL$
$	// [COM785] ComBitSizeはデータ型のサイズへの拡張をしない
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
$		// [NCOM033] ComFirstTimeoutが有効値の場合，MF呼出し回数を算出して+1する
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
		$ELSE$
			$TAB$$TAB$COM_INVALID_UINT8,$TAB$/* ComFilterAlgorithm */$NL$
			$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
		$END$
		$TAB$$TAB$(void *)&tx_signal_cb_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* シグナル管理ブロック */$NL$
		$IF EQ(ComSignal.ComSignalType[signal_id], "UINT8_N")$
			$TAB$$TAB$(void *)signal_buffer_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* シグナルバッファ */$NL$
		$ELSE$
			$TAB$$TAB$(void *)&signal_buffer_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* シグナルバッファ */$NL$
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
$			// 受信の場合，受信DMがなければNULL_PTR
			$TAB$$TAB$NULL_PTR,$TAB$/* シグナル管理ブロック */$NL$
		$END$
$		// 受信の場合，必須
		$TAB$$TAB$(void *)&signal_buffer_$com_config_id$_$ComSignal[signal_id]$,$TAB$/* シグナルバッファ */$NL$
	$END$

	$TAB$$TAB$NULL_PTR,$TAB$/* シグナルグループ管理ブロック */$NL$
	$TAB$$TAB$NULL_PTR$TAB$/* シャドウバッファ */$NL$

	$TAB$}
$END$

$	//グループシグナル
$FUNCTION G_SIGNAL_INIB$
	$gsignal_id = ARGV[1]$
	$NL$
	$TAB$/* $ComGroupSignal[gsignal_id]$ */$NL$
	$TAB${$NL$
$	// [COM785] ComBitSizeはデータ型のサイズへの拡張をしない
	$IF EQ(ComGroupSignal.ComBitSize[gsignal_id], "COM_INVALID_UINT8")$
		$TAB$$TAB$$ComGroupSignal.ComBitSize[gsignal_id]$,$TAB$/* ComBitSize */$NL$
	$ELSE$
		$TAB$$TAB$$ComGroupSignal.ComBitSize[gsignal_id]$U,$TAB$/* ComBitSize */$NL$
	$END$
	$TAB$$TAB$COM_INVALID_UINT8,$TAB$/* ComDataInvalidAction */$NL$
	$TAB$$TAB$COM_INVALID_UINT8,$TAB$/* ComRxDataTimeoutAction */$NL$
	$TAB$$TAB$COM_$ComGroupSignal.ComSignalEndianness[gsignal_id]$,$TAB$/* ComSignalEndianness */$NL$
	$TAB$$TAB$COM_$ComGroupSignal.ComSignalType[gsignal_id]$,$TAB$/* ComSignalType */$NL$
	$TAB$$TAB$COM_$ComGroupSignal.ComTransferProperty[gsignal_id]$,$TAB$/* ComTransferProperty */$NL$
	$TAB$$TAB$$ComGroupSignal.lsb[gsignal_id]$U,$TAB$/* ComBitPositionLsb */$NL$
	$IF EQ(ComGroupSignal.ComSignalLength[gsignal_id], "COM_INVALID_UINT16")$
		$TAB$$TAB$$ComGroupSignal.ComSignalLength[gsignal_id]$,$TAB$/* ComSignalLength */$NL$
	$ELSE$
		$TAB$$TAB$$ComGroupSignal.ComSignalLength[gsignal_id]$U,$TAB$/* ComSignalLength */$NL$
	$END$
	$TAB$$TAB$COM_INVALID_UINT16,$TAB$/* ComUpdateBitPosition */$NL$
	$TAB$$TAB$0U,$TAB$/* ComFirstTimeout */$NL$
	$TAB$$TAB$0U,$TAB$/* ComTimeout */$NL$
	$TAB$$TAB$NULL_PTR,$TAB$/* ComErrorNotification */$NL$
	$TAB$$TAB$NULL_PTR,$TAB$/* ComInvalidNotification */$NL$
	$TAB$$TAB$NULL_PTR,$TAB$/* ComNotification */$NL$
	$TAB$$TAB$NULL_PTR,$TAB$/* ComTimeoutNotification */$NL$
	$IF LENGTH(ComGroupSignal.ComSignalDataInvalidValue[gsignal_id])$
		$IF EQ(ComGroupSignal.ComSignalType[gsignal_id], "UINT8_N")$
			$TAB$$TAB$(const void *)signal_invalid_value_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* ComSignalDataInvalidValue */$NL$
		$ELSE$
			$TAB$$TAB$(const void *)&signal_invalid_value_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* ComSignalDataInvalidValue */$NL$
		$END$
	$ELSE$
		$TAB$$TAB$NULL_PTR,$TAB$/* ComSignalDataInvalidValue */$NL$
	$END$
	$IF EQ(ComGroupSignal.ComSignalType[gsignal_id], "UINT8_N")$
		$TAB$$TAB$(const void *)signal_init_value_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* ComSignalInitValue */$NL$
	$ELSE$
		$TAB$$TAB$(const void *)&signal_init_value_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* ComSignalInitValue */$NL$
	$END$
	$FOREACH signal_g_id ComSignalGroup.ID_LIST$
		$IF EQ(signal_g_id, ComGroupSignal.PARENT[gsignal_id])$
			$belong_ipdu_id = ComSignalGroup.ipdu_ref[signal_g_id]$
			$g_signal_list_pos = ComSignalGroup.list_pos[signal_g_id]$
		$END$
	$END$
	$IF EQ(ComGroupSignal.direction[gsignal_id], "SEND")$
		$TAB$$TAB$&tx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[belong_ipdu_id]$],$TAB$/* $belong_ipdu_id$ */$NL$
		$IF LENGTH(ComGroupSignal.filter_ref_id[gsignal_id])$
			$TAB$$TAB$COM_$ComFilter.ComFilterAlgorithm[ComGroupSignal.filter_ref_id[gsignal_id]]$,$TAB$/* ComFilterAlgorithm */$NL$
			$IF EQ(ComFilter.ComFilterAlgorithm[ComGroupSignal.filter_ref_id[gsignal_id]], "ALWAYS") || EQ(ComFilter.ComFilterAlgorithm[ComGroupSignal.filter_ref_id[gsignal_id]], "NEVER")$
				$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
			$ELSE$
				$TAB$$TAB$(const void *)&filter_inib_$com_config_id$_$gsignal_id$,$TAB$/* p_filter_inib */$NL$
			$END$
		$ELSE$
			$TAB$$TAB$COM_INVALID_UINT8,$TAB$/* ComFilterAlgorithm */$NL$
			$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
$			// 送信の場合，フィルタがなければNULL_PTR
		$END$
		$TAB$$TAB$(void *)&tx_signal_cb_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* シグナル管理ブロック */$NL$
		$IF EQ(ComGroupSignal.ComSignalType[gsignal_id], "UINT8_N")$
			$TAB$$TAB$(void *)signal_buffer_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* シグナルバッファ */$NL$
		$ELSE$
			$TAB$$TAB$(void *)&signal_buffer_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* シグナルバッファ */$NL$
		$END$

		$FOREACH signal_g_id ComSignalGroup.ID_LIST$
			$IF EQ(signal_g_id, ComGroupSignal.PARENT[gsignal_id])$
				$TAB$$TAB$(void *)&tx_signal_g_cb_$com_config_id$_$signal_g_id$,$TAB$/* シグナルグループ管理ブロック */$NL$
			$END$
		$END$
	$ELIF EQ(ComGroupSignal.direction[gsignal_id], "RECEIVE")$
		$TAB$$TAB$&rx_ipdu_inib_list_$com_config_id$[$ComIPdu.list_pos[belong_ipdu_id]$],$TAB$/* $belong_ipdu_id$ */$NL$
		$IF LENGTH(ComGroupSignal.filter_ref_id[gsignal_id])$
			$TAB$$TAB$COM_$ComFilter.ComFilterAlgorithm[ComGroupSignal.filter_ref_id[gsignal_id]]$,$TAB$/* ComFilterAlgorithm */$NL$
			$IF EQ(ComFilter.ComFilterAlgorithm[ComGroupSignal.filter_ref_id[gsignal_id]], "ALWAYS") || EQ(ComFilter.ComFilterAlgorithm[ComGroupSignal.filter_ref_id[gsignal_id]], "NEVER")$
				$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
			$ELSE$
				$TAB$$TAB$(const void *)&filter_inib_$com_config_id$_$gsignal_id$,$TAB$/* p_filter_inib */$NL$
			$END$
		$ELSE$
			$TAB$$TAB$COM_INVALID_UINT8,$TAB$/* ComFilterAlgorithm */$NL$
			$TAB$$TAB$NULL_PTR,$TAB$/* p_filter_inib */$NL$
		$END$
		$IF ComGroupSignal.gs_timeout[gsignal_id] != 0$
			$TAB$$TAB$(void *)&rx_signal_cb_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* シグナル管理ブロック */$NL$
		$ELSE$
$			// 受信の場合，受信DMがなければNULL_PTR
			$TAB$$TAB$NULL_PTR,$TAB$/* シグナル管理ブロック */$NL$
		$END$
$		// 受信の場合，必須
		$TAB$$TAB$(void *)&signal_buffer_$com_config_id$_$ComGroupSignal[gsignal_id]$,$TAB$/* シグナルバッファ */$NL$
		$IF ComGroupSignal.gs_timeout[gsignal_id] != 0$
			$FOREACH signal_g_id ComSignalGroup.ID_LIST$
				$IF EQ(signal_g_id, ComGroupSignal.PARENT[gsignal_id])$
					$TAB$$TAB$(void *)&rx_signal_g_cb_$com_config_id$_$signal_g_id$,$TAB$/* シグナルグループ管理ブロック */$NL$
				$END$
			$END$
		$ELSE$
$			// 受信の場合，受信DMがなければNULL_PTR
			$TAB$$TAB$NULL_PTR,$TAB$/* シグナルグループ管理ブロック */$NL$
		$END$
	$END$
$	$TAB$$TAB$&signal_g_inib_table_$ComConfig[config_id]$[$g_signal_list_pos$]$TAB$/* p_signal_g_inib_table */$NL$
	$TAB$$TAB$&shadow_buffer_$ComConfig[config_id]$_$ComGroupSignal[gsignal_id]$$TAB$/* シャドウバッファ */$NL$
	$TAB$}
$END$

$ ====================================================================
$ シグナルフィルタ・グループシグナルフィルタの設定値チェック関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalType
$ ARGV[3]  : ComBitSize
$ ARGV[4]  : filter_id
$ ====================================================================
$FUNCTION CHECK_SIGNAL_FILTER_CONFIG$
	$signal       = ARGV[1]$
	$signal_type  = ARGV[2]$
	$signal_size  = ARGV[3]$
	$filter_id    = ARGV[4]$

$	// [COM146_Conf] ComFilterAlgorithm
	$IF !EQ(ComFilter.ComFilterAlgorithm[filter_id], "ALWAYS")
		&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEVER")
		&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_EQUALS_X")
		&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_X")
		&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")
		&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN")
		&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE")
		&& !EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
$		// ComFilterAlgorithmに適切な値が設定されてない場合はエラー
		$ERROR$$FORMAT(_("ComFilterAlgorithm should not be set `%1%\'. (%2%\)"),ComFilter.ComFilterAlgorithm[filter_id] , ComFilter[filter_id])$$END$$DIE()$
	$END$
	$IF EQ(signal_type, "BOOLEAN")$
$		// [COM439] BOOLEANのシグナルにNEW_IS_WITHINまたはNEW_IS_OUTSIDEが設定された場合はエラー
		$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE")$
			$ERROR$$FORMAT(_("BOOLEAN type signal should NOT set 'NEW_IS_WITHIN' or 'NEW_IS_OUTSIDE' to ComFilterAlgorithm. (%1%\)"),signal)$$END$$DIE()$
		$END$
	$END$
	$IF EQ(signal_type, "UINT8_N")$
$		// [COM380] UINT8_NのシグナルのComFilterAlgorithmにALWAYSまたはNEVERが設定されていない場合はエラー
		$IF !EQ(ComFilter.ComFilterAlgorithm[filter_id], "ALWAYS") && !EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEVER")$
			$ERROR$$FORMAT(_("UINT8_N type signal should set 'ALWAYS' or 'NEVER' to ComFilterAlgorithm. (%1%\)"),signal)$$END$$DIE()$
		$END$
	$END$
$	// [COM319] FLOAT32またはFLOAT64のシグナルにComFilterが設定されている場合はエラー
	$IF EQ(signal_type, "FLOAT32") || EQ(signal_type, "FLOAT64")$
		$ERROR$$FORMAT(_("FLOAT32 type or FLOAT64 type signal should NOT have ComFilter container. (%1%\)"),signal)$$END$$DIE()$
	$END$

$	//ComFilterAlgorithmの設定パラメータチェック
$	// [COM235_Conf][NCOM047] ComFilterMask
$	// [COM147_Conf][NCOM048] ComFilterX
	$IF EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_EQUALS_X") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_X") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
$		//ComFilterMaskが設定されていない場合はエラー
		$IF !LENGTH(ComFilter.ComFilterMask[filter_id])$
			$ERROR$$FORMAT(_("MASKED_NEW_EQUALS_X or MASKED_NEW_DIFFERS_X or MASKED_NEW_DIFFERS_MASKED_OLD is set, but, ComFilterMask is not set (%1%\)"), signal_ref_id)$$END$$DIE()$
		$END$
		$IF !EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
$			//ComFilterXが設定されていない場合はエラー
			$IF !LENGTH(ComFilter.ComFilterX[filter_id])$
				$ERROR$$FORMAT(_("MASKED_NEW_EQUALS_X or MASKED_NEW_DIFFERS_X is set, but, ComFilterX is not set (%1%\)"), signal_ref_id)$$END$$DIE()$
			$ELSE$
				$IF EQ(signal_type, "UINT8_N")$
					$FOREACH value value_list$
						$SIGNAL_RANGE_CHECK(value, "UINT8", 8, "ComFilterX")$
					$END$
				$ELIF (EQ(signal_type, "UINT8") || EQ(signal_type, "UINT16")
						|| EQ(signal_type, "UINT32") || EQ(signal_type, "SINT8")
						|| EQ(signal_type, "SINT16") || EQ(signal_type, "SINT32"))$
					$SIGNAL_RANGE_CHECK(ComFilter.ComFilterX[filter_id], signal_type, signal_size, "ComFilterX")$
				$END$
			$END$
		$END$
		$ComFilter.ComFilterOffset[filter_id] = 0$
		$ComFilter.ComFilterPeriod[filter_id] = 0$
		$ComFilter.ComFilterMax[filter_id] = 0$
		$ComFilter.ComFilterMin[filter_id] = 0$
$	// [COM313_Conf] ComFilterOffset
$	// [COM147_Conf] ComFilterX
	$ELIF EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
$		//ComFilterOffsetが設定されていない場合はエラー
		$IF !LENGTH(ComFilter.ComFilterOffset[filter_id])$
			$ERROR$$FORMAT(_("ONE_EVERY_N is set, but, ComFilterOffset is not set (%1%\)"), signal_ref_id)$$END$$DIE()$
		$END$
$		// [COM312_Conf] ComFilterPeriod
$		//ComFilterPeriodが設定されていない場合はエラー
		$IF !LENGTH(ComFilter.ComFilterPeriod[filter_id])$
			$ERROR$$FORMAT(_("ONE_EVERY_N is set, but, ComFilterPeriod is not set (%1%\)"), signal_ref_id)$$END$$DIE()$
		$END$
$		// [COM535] ComFilterAlgorithmがONE_EVERY_NのときにComFilterOffsetがComFilterPeriodより大きい場合はエラー
		$IF (ComFilter.ComFilterOffset[filter_id] > ComFilter.ComFilterPeriod[filter_id])$
			$ERROR$$FORMAT(_("Because ComFilterAlgorithm is ONE_EVERY_N, ComFilterOffset should be set to a value lesser than ComFilterPeriod'. (%1%\)"),ComFilter[filter_id])$$END$$DIE()$
		$END$
		$ComFilter.ComFilterMask[filter_id] = 0$
		$ComFilter.ComFilterX[filter_id] = 0$
		$ComFilter.ComFilterMax[filter_id] = 0$
		$ComFilter.ComFilterMin[filter_id] = 0$
$	// ComFilterAlgorithmがNEW_IS_OUTSIDEまたはNEW_IS_WITHINであるフィルタに対するチェック
$	// [COM317_Conf] ComFilterMax
$	// [COM318_Conf] ComFilterMin
	$ELIF EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN")$
$		//ComFilterMinが設定されていない場合はエラー
		$IF !LENGTH(ComFilter.ComFilterMin[filter_id])$
			$ERROR$$FORMAT(_("NEW_IS_OUTSIDE or NEW_IS_WITHIN is set, but, ComFilterMin is not set (%1%\)"), signal_ref_id)$$END$$DIE()$
		$ELSE$
$			// [NCOM043][NCOM044][NCOM045] ComFilterMin，ComFilterMinが所属シグナルの型と値の範囲外の場合はエラー
			$IF EQ(signal_type, "UINT8_N")$
				$FOREACH value value_list$
					$SIGNAL_RANGE_CHECK(value, "UINT8", 8, "ComFilterMin")$
				$END$
			$ELIF (EQ(signal_type, "UINT8") || EQ(signal_type, "UINT16")
					|| EQ(signal_type, "UINT32") || EQ(signal_type, "SINT8")
					|| EQ(signal_type, "SINT16") || EQ(signal_type, "SINT32"))$
				$SIGNAL_RANGE_CHECK(ComFilter.ComFilterMin[filter_id], signal_type, signal_size, "ComFilterMin")$
			$END$
		$END$
$		//ComFilterMaxが設定されていない場合はエラー
		$IF !LENGTH(ComFilter.ComFilterMax[filter_id])$
			$ERROR$$FORMAT(_("NEW_IS_OUTSIDE or NEW_IS_WITHIN is set, but, ComFilterMax is not set (%1%\)"), signal_ref_id)$$END$$DIE()$
		$ELSE$
$			// [NCOM043][NCOM044][NCOM045] ComFilterMin，ComFilterMaxが所属シグナルの型と値の範囲外の場合はエラー
			$IF EQ(signal_type, "UINT8_N")$
				$FOREACH value value_list$
					$SIGNAL_RANGE_CHECK(value, "UINT8", 8, "ComFilterMax")$
				$END$
			$ELIF (EQ(signal_type, "UINT8") || EQ(signal_type, "UINT16")
					|| EQ(signal_type, "UINT32") || EQ(signal_type, "SINT8")
					|| EQ(signal_type, "SINT16") || EQ(signal_type, "SINT32"))$
				$SIGNAL_RANGE_CHECK(ComFilter.ComFilterMax[filter_id], signal_type, signal_size, "ComFilterMax")$
			$END$
		$END$
$		// [NCOM046] ComFilterMinがComFilterMaxよりも大きい場合はエラー
		$IF (ComFilter.ComFilterMin[filter_id] > ComFilter.ComFilterMax[filter_id])$
			$ERROR$$FORMAT(_("ComFilterMin should be set to a value lesser than ComFilterMax'. (%1%\)"), filter_id)$$END$$DIE()$
		$END$
		$ComFilter.ComFilterMask[filter_id] = 0$
		$ComFilter.ComFilterX[filter_id] = 0$
		$ComFilter.ComFilterOffset[filter_id] = 0$
		$ComFilter.ComFilterPeriod[filter_id] = 0$
	$ELSE$
		$ComFilter.ComFilterMask[filter_id] = 0$
		$ComFilter.ComFilterX[filter_id] = 0$
		$ComFilter.ComFilterOffset[filter_id] = 0$
		$ComFilter.ComFilterPeriod[filter_id] = 0$
		$ComFilter.ComFilterMax[filter_id] = 0$
		$ComFilter.ComFilterMin[filter_id] = 0$
	$END$
$END$

$ ====================================================================
$ シグナルバッファ定義・グループシグナルバッファ定義関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalType
$ ARGV[3]  : ComSignalLength
$ ====================================================================
$FUNCTION GEN_SIGNAL_BUF$
	$signal      = ARGV[1]$
	$signal_type = ARGV[2]$
	$signal_length = ARGV[3]$

	$IF EQ(signal_type, "BOOLEAN")$
		static boolean signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "UINT8")$
		static uint8   signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "UINT16")$
		static uint16  signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "UINT32")$
		static uint32  signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "SINT8")$
		static sint8   signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "SINT16")$
		static sint16  signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "SINT32")$
		static sint32  signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "UINT8_N")$
		static uint8   signal_buffer_$com_config_id$_$signal$[$signal_length$];$NL$
	$ELIF EQ(signal_type, "FLOAT32")$
		static float32  signal_buffer_$com_config_id$_$signal$;$NL$
	$ELIF EQ(signal_type, "FLOAT64")$
		static float64  signal_buffer_$com_config_id$_$signal$;$NL$
	$END$
$END$

$ ====================================================================
$ シグナル無効値定義・グループシグナル無効値定義関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalType
$ ARGV[3]  : ComSignalLength
$ ARGV[4]  : ComSignalInvalidValue
$ ====================================================================
$FUNCTION GEN_SIGNAL_INVALID_VALUE$
	$signal               = ARGV[1]$
	$signal_type          = ARGV[2]$
	$signal_length        = ARGV[3]$
	$signal_invalid_value = ARGV[4]$

	$IF LENGTH(signal_invalid_value)$
		$IF EQ(signal_type, "BOOLEAN")$
			static const boolean signal_invalid_value_$com_config_id$_$signal$ = $IS_TRUE(signal_invalid_value)$;$NL$
		$ELIF EQ(signal_type, "UINT8")$
			static const uint8   signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$U;$NL$
		$ELIF EQ(signal_type, "UINT16")$
			static const uint16  signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$U;$NL$
		$ELIF EQ(signal_type, "UINT32")$
			static const uint32  signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$U;$NL$
		$ELIF EQ(signal_type, "SINT8")$
			static const sint8   signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$;$NL$
		$ELIF EQ(signal_type, "SINT16")$
			static const sint16  signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$;$NL$
		$ELIF EQ(signal_type, "SINT32")$
			static const sint32  signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$;$NL$
		$ELIF EQ(signal_type, "UINT8_N")$
			$IF !EQ(signal_invalid_value, "NULL_PTR")$
				static const uint8   signal_invalid_value_$com_config_id$_$signal$[$signal_length$] = {
$				// [COM791] UINT8_N型に設定された文字列は空白で区切られたASCIIコードとして解釈する
				$value_list = SPLIT(signal_invalid_value, " ")$
				$JOINEACH value_str value_list ", "$
					$value_str$U
				$END$
				};$NL$
			$ELSE$
				static const uint8   signal_invalid_value_$com_config_id$_$signal$ = NULL_PTR;$NL$
			$END$
		$ELIF EQ(signal_type, "FLOAT32")$
			static const float32  signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$;$NL$
		$ELIF EQ(signal_type, "FLOAT64")$
			static const float64  signal_invalid_value_$com_config_id$_$signal$ = $signal_invalid_value$;$NL$
		$END$
	$END$
$END$

$ ====================================================================
$ シグナル初期値定義・グループシグナル初期値定義関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalType
$ ARGV[3]  : ComSignalLength
$ ARGV[4]  : ComSignalInitValue
$ ====================================================================
$FUNCTION GEN_SIGNAL_INIT_VALUE$
	$signal            = ARGV[1]$
	$signal_type       = ARGV[2]$
	$signal_length     = ARGV[3]$
	$signal_init_value = ARGV[4]$

	$IF EQ(signal_type, "BOOLEAN")$
		static const boolean signal_init_value_$com_config_id$_$signal$ = $IS_TRUE(signal_init_value)$;$NL$
	$ELIF EQ(signal_type, "UINT8")$
		static const uint8   signal_init_value_$com_config_id$_$signal$ = $signal_init_value$U;$NL$
	$ELIF EQ(signal_type, "UINT16")$
		static const uint16  signal_init_value_$com_config_id$_$signal$ = $signal_init_value$U;$NL$
	$ELIF EQ(signal_type, "UINT32")$
		static const uint32  signal_init_value_$com_config_id$_$signal$ = $signal_init_value$U;$NL$
	$ELIF EQ(signal_type, "SINT8")$
		static const sint8   signal_init_value_$com_config_id$_$signal$ = $signal_init_value$;$NL$
	$ELIF EQ(signal_type, "SINT16")$
		static const sint16  signal_init_value_$com_config_id$_$signal$ = $signal_init_value$;$NL$
	$ELIF EQ(signal_type, "SINT32")$
		static const sint32  signal_init_value_$com_config_id$_$signal$ = $signal_init_value$;$NL$
	$ELIF EQ(signal_type, "UINT8_N")$
		static const uint8   signal_init_value_$com_config_id$_$signal$[$signal_length$] = {
$		// [COM791] UINT8_N型に設定された文字列は空白で区切られたASCIIコードとして解釈する
		$value_list = SPLIT(signal_init_value, " ")$
		$JOINEACH value_str value_list ", "$
			$value_str$U
			$END$
		};$NL$
	$ELIF EQ(signal_type, "FLOAT32")$
		static const float32  signal_init_value_$com_config_id$_$signal$ = $signal_init_value$;$NL$
	$ELIF EQ(signal_type, "FLOAT64")$
		static const float64  signal_init_value_$com_config_id$_$signal$ = $signal_init_value$;$NL$
	$END$
$END$

$ ====================================================================
$ シグナル・グループシグナルのシグナルフィルタ初期化ブロック定義関数
$ ARGV[1]  : ComSignalType
$ ARGV[2]  : filter_id
$ ARGV[3]  : signal_ref_id
$ ====================================================================
$FUNCTION GEN_SIGNAL_FILTER_INITBLOCK$
	$signal_type = ARGV[1]$
	$filter_id   = ARGV[2]$
	$signal_ref_id = ARGV[3]$
	
	$signal_filter_type = ""$
	$IF EQ(signal_type, "BOOLEAN") || EQ(signal_type, "UINT8")
	 || EQ(signal_type, "UINT16") || EQ(signal_type, "UINT32")$
		$signal_filter_type = "UINT"$
	$ELIF EQ(signal_type, "SINT8") || EQ(signal_type, "SINT16")
	 || EQ(signal_type, "SINT32")$
		$signal_filter_type = "SINT"$
	$END$
	
$	// フィルタアルゴリズムごとに作成(ALWAYS, NEVER用は不要)
	$IF (EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_EQUALS_X") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_X"))$
$		/* COM_MASKED_NEW_DIFFERS_X/COM_MASKED_NEW_EQUALS_X用 ($signal_filter_type$) */$NL$
		static const FILTER_$signal_filter_type$_MASKED_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
		$IF EQ(signal_filter_type, "UINT")$
			$TAB$$ComFilter.ComFilterMask[filter_id]$U,$TAB$/* ComFilterMask */$NL$
			$TAB$$ComFilter.ComFilterX[filter_id]$U$TAB$/* ComFilterX */$NL$
		$ELSE$
			$TAB$$ComFilter.ComFilterMask[filter_id]$,$TAB$/* ComFilterMask */$NL$
			$TAB$$ComFilter.ComFilterX[filter_id]$$TAB$/* ComFilterX */$NL$
		$END$
		};$NL$
	$ELIF EQ(ComFilter.ComFilterAlgorithm[filter_id], "MASKED_NEW_DIFFERS_MASKED_OLD")$
$		/* COM_MASKED_NEW_DIFFERS_MASKED_OLD用 ($signal_filter_type$) */$NL$
		static const FILTER_$signal_filter_type$_MASKED_OLD_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
		$IF EQ(signal_filter_type, "UINT")$
			$TAB$$ComFilter.ComFilterMask[filter_id]$U,$TAB$/* ComFilterMask */$NL$
		$ELSE$
			$TAB$$ComFilter.ComFilterMask[filter_id]$,$TAB$/* ComFilterMask */$NL$
		$END$
		$TAB$(void *)&filter_buffer_$com_config_id$_$signal_ref_id$$TAB$/* p_filter_buffer */$NL$
		};$NL$
	$ELIF (EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_WITHIN") || EQ(ComFilter.ComFilterAlgorithm[filter_id], "NEW_IS_OUTSIDE"))$
$		/* COM_NEW_IS_OUTSIDE/COM_NEW_IS_WITHIN用 ($signal_filter_type$) */$NL$
		static const FILTER_$signal_filter_type$_NEW_IS_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
		$IF EQ(signal_filter_type, "UINT")$
			$TAB$$ComFilter.ComFilterMax[filter_id]$U,$TAB$/* ComFilterMax */$NL$
			$TAB$$ComFilter.ComFilterMin[filter_id]$U$TAB$/* ComFilterMin */$NL$
		$ELSE$
			$TAB$$ComFilter.ComFilterMax[filter_id]$,$TAB$/* ComFilterMax */$NL$
			$TAB$$ComFilter.ComFilterMin[filter_id]$$TAB$/* ComFilterMin */$NL$
		$END$
		};$NL$
	$ELIF EQ(ComFilter.ComFilterAlgorithm[filter_id], "ONE_EVERY_N")$
$		/* COM_ONE_EVERY_N用 */$NL$
		static const FILTER_ONE_EVERY_N_INIB filter_inib_$com_config_id$_$signal_ref_id$ = {$NL$
		$TAB$$ComFilter.ComFilterOffset[filter_id]$U,$TAB$/* ComFilterOffset */$NL$
		$TAB$$ComFilter.ComFilterPeriod[filter_id]$U,$TAB$/* ComFilterPeriod */$NL$
		$TAB$&occur_$com_config_id$_$signal_ref_id$$TAB$/* p_occur */$NL$
		};$NL$
	$END$
$END$

$ ====================================================================
$ シグナル・グループシグナルのComSignalTypeチェック関数
$ ARGV[1]  : ComSignalType
$ ARGV[2]  : signal_type_str
$ ====================================================================
$FUNCTION CHECK_SIGNAL_TYPE$
	$signal_type     = ARGV[1]$
	$signal_type_str = ARGV[2]$

	$IF EQ(signal_type, "BOOLEAN")$
		$signal_type_str = "boolean"$
	$ELIF EQ(signal_type, "UINT8")$
		$signal_type_str = "uint8"$
	$ELIF EQ(signal_type, "UINT16")$
		$signal_type_str = "uint16"$
	$ELIF EQ(signal_type, "UINT32")$
		$signal_type_str = "uint32"$
	$ELIF EQ(signal_type, "SINT8")$
		$signal_type_str = "sint8"$
	$ELIF EQ(signal_type, "SINT16")$
		$signal_type_str = "sint16"$
	$ELIF EQ(signal_type, "SINT32")$
		$signal_type_str = "sint32"$
	$ELIF EQ(signal_type, "UINT8_N")$
		$signal_type_str = "uint8"$
	$ELIF EQ(signal_type, "FLOAT32")$
		$signal_type_str = "float32"$
	$ELIF EQ(signal_type, "FLOAT64")$
		$signal_type_str = "float64"$
		$float64_flg = "TRUE"$
	$ELSE$
$		// [COM675][NCOM095] COMがサポートする型以外が指定されている場合はエラー
		$ERROR$$FORMAT(_("ComSignalType should not be set to `%1%\'."), signal_type)$$END$$DIE()$
	$END$

	$RESULT = signal_type_str$
	
$END$

$ ====================================================================
$ シグナル・グループシグナルのComSignalBitSizeチェック関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalBitSize
$ ARGV[3]  : ComSignalType
$ ====================================================================
$FUNCTION CHECK_SIGNAL_BITSIZE$
	$signal          = ARGV[1]$
	$signal_bitsize  = ARGV[2]$
	$signal_type     = ARGV[3]$
	
	$IF LENGTH(signal_bitsize)$
		$IF signal_bitsize <= 0$
$			// [COM158_Conf] ビットサイズが0以下の場合はエラー
			$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize is greater than 0."), signal_bitsize)$$END$$DIE()$
		$END$

		$IF EQ(signal_type, "BOOLEAN")$
$			// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
			$IF signal_bitsize > 1$
				$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize for BOOLEAN is greater than 1."), signal_bitsize)$$END$$DIE()$
			$END$
		$ELIF EQ(signal_type, "UINT8")$
$			// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
			$IF signal_bitsize > 8$
				$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize for UINT8 is greater than 8."), signal_bitsize)$$END$$DIE()$
			$END$
		$ELIF EQ(signal_type, "UINT16")$
$			// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
			$IF signal_bitsize > 16$
				$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize for UINT16 is greater than 16."), signal_bitsize)$$END$$DIE()$
			$END$
		$ELIF EQ(signal_type, "UINT32")$
$			// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
			$IF signal_bitsize > 32$
				$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize for UINT32 is greater than 32."), signal_bitsize)$$END$$DIE()$
			$END$
		$ELIF EQ(signal_type, "SINT8")$
$			// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
			$IF signal_bitsize > 8$
				$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize for SINT8 is greater than 8."), signal_bitsize)$$END$$DIE()$
			$END$
		$ELIF EQ(signal_type, "SINT16")$
$			// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
			$IF signal_bitsize > 16$
				$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize for SINT16 is greater than 16."), signal_bitsize)$$END$$DIE()$
			$END$
		$ELIF EQ(signal_type, "SINT32")$
$			// [NCOM010] ComSignalTypeに指定したデータ型のビットサイズより大きい場合はエラー
			$IF signal_bitsize > 32$
				$ERROR$$FORMAT(_("ComBitSize should not be set to `%1%\'. ComBitSize for SINT32 is greater than 32."), signal_bitsize)$$END$$DIE()$
			$END$
		$ELIF EQ(signal_type, "UINT8_N")$
$			// [NCOM021] ComSignalTypeがUINT8_NのシグナルにComBitSizeを設定した場合は警告
			$WARNING$$FORMAT(_("UINT8_N type signal doesn't have to set value to ComBitSize. (%1%\)"), signal)$$END$
		$ELIF EQ(signal_type, "FLOAT32")$
$			// [NCOM022]データ型がFLOAT32に設定されたシグナルのビットサイズが指定された場合は警告
			$WARNING$$FORMAT(_("FLOAT32 type signal doesn't have to set value to ComBitSize. (%1%\)"), signal)$$END$
		$ELIF EQ(signal_type, "FLOAT64")$
$			// [NCOM022]データ型がFLOAT64に設定されたシグナルのビットサイズが指定された場合は警告
			$WARNING$$FORMAT(_("FLOAT64 type signal doesn't have to set value to ComBitSize. (%1%\)"), signal)$$END$
		$END$
	$ELSE$
		$IF EQ(signal_type, "UINT8_N")$
			$signal_bitsize = "COM_INVALID_UINT8"$
		$ELIF EQ(signal_type, "FLOAT32")$
			$signal_bitsize = 32$
		$ELIF EQ(signal_type, "FLOAT64")$
			$signal_bitsize = 64$
		$ELSE$
$			// [NCOM011] データ型がUINT8_N以外のシグナルにComBitSizeを設定していない場合はエラー
			$ERROR$$FORMAT(_("`%1%\' should set ComBitSize."), signal)$$END$$DIE()$
		$END$
	$END$
	
	$RESULT = signal_bitsize$

$END$

$ ====================================================================
$ シグナル・グループシグナルのComSignalLengthチェック関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalLength
$ ARGV[3]  : ComSignalType
$ ====================================================================
$FUNCTION CHECK_SIGNAL_LENGTH$
	$signal          = ARGV[1]$
	$signal_length   = ARGV[2]$
	$signal_type     = ARGV[3]$
	
	$IF LENGTH(signal_length)$
		$IF EQ(signal_type, "UINT8_N")$
			$IF signal_length <= 0$
$				// [NCOM012] UINT8_N型のシグナルのComSignalLengthに0以下が設定された場合はエラー
				$ERROR$$FORMAT("ComSignalLength should not be set to 0.")$$END$$DIE()$
			$END$
		$ELSE$
$			// [NCOM023] UINT8_N以外のシグナルにComSignalLengthを指定した場合は警告
			$WARNING$$FORMAT(_("`%1%\' does not have to set ComSignalLength."), signal)$$END$
			$signal_length = "COM_INVALID_UINT16"$
		$END$
	$ELSE$
		$IF EQ(signal_type, "UINT8_N")$
$			// [NCOM012] データ型がUINT8_NのシグナルにComSignalLengthを設定していない場合はエラー
			$ERROR$$FORMAT(_("`%1%\' should be set ComSignalLength."), signal)$$END$$DIE()$
		$ELSE$
			$signal_length = "COM_INVALID_UINT16"$
		$END$
	$END$
	
	$RESULT = signal_length$
	
$END$

$ ====================================================================
$ シグナル・グループシグナルのComSignalInitValueチェック関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalInitValue
$ ARGV[3]  : ComSignalType
$ ARGV[4]  : ComSignalBitSize
$ ARGV[5]  : ComSignalLength
$ ====================================================================
$FUNCTION CHECK_SIGNAL_INIT_VALUE$
	$signal            = ARGV[1]$
	$signal_init_value = ARGV[2]$
	$signal_type       = ARGV[3]$
	$signal_bitsize    = ARGV[4]$
	$signal_length     = ARGV[5]$
	
	$IF LENGTH(signal_init_value)$
		$IF EQ(signal_type, "UINT8_N")$
			$value_list = SPLIT(signal_init_value, " ")$
$			// [NCOM013] データ型がUINT8_Nのシグナルに設定されたComSignalInitValueのデータ数がComSignalLengthと一致しない場合はエラー
			$IF signal_length != LENGTH(value_list)$
				$ERROR$$FORMAT(_("ComSignalInitValue and ComSignalLength is inconsistent at `%1%\'."), signal)$$END$$DIE()$
			$END$
			$FOREACH value value_list$
				$SIGNAL_RANGE_CHECK(value, "UINT8", 8, "ComSignalInitValue")$
			$END$
		$ELIF (EQ(signal_type, "UINT8") || EQ(signal_type, "UINT16")
				|| EQ(signal_type, "UINT32") || EQ(signal_type, "SINT8")
				|| EQ(signal_type, "SINT16") || EQ(signal_type, "SINT32"))$
$			// [NCOM038] 整数型のシグナルに設定されたComSignalInitValueの値がComBitSizeのレンジに収まっていない場合はエラー
			$SIGNAL_RANGE_CHECK(signal_init_value, signal_type, signal_bitsize, "ComSignalInitValue")$
		$END$
	$ELSE$
		$IF EQ(signal_type, "UINT8_N")$
$			// ComSignalLengthにデータ数を合わせた値で補完
			$value_str = "0"$
			$FOREACH index RANGE(1, signal_length - 1)$
				$value_str = CONCAT(value_str, " 0")$
			$END$
			$signal_init_value = value_str$
		$ELSE$
			$signal_init_value = 0$
		$END$
	$END$
	
	$RESULT = signal_init_value$
	
$END$

$ ====================================================================
$ シグナル・グループシグナルのComSignalInvalidValueチェック関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalInvalidValue
$ ARGV[3]  : ComSignalType
$ ARGV[4]  : ComSignalBitSize
$ ARGV[5]  : ComSignalLength
$ ====================================================================
$FUNCTION CHECK_SIGNAL_INVALID_VALUE$
	$signal               = ARGV[1]$
	$signal_invaild_value = ARGV[2]$
	$signal_type          = ARGV[3]$
	$signal_bitsize       = ARGV[4]$
	$signal_length        = ARGV[5]$
	
	$IF LENGTH(signal_invalid_value)$
		$IF EQ(signal_type, "UINT8_N")$
$			// [NCOM014] データ型がUINT8_Nのシグナルに設定されたComSignalDataInvalidValueのデータ数がComSignalLengthと一致しない場合はエラー
			$value_list = SPLIT(signal_invalid_value, " ")$
			$IF signal_length != LENGTH(value_list)$
				$ERROR$$FORMAT(_("ComSignalDataInvalidValue and ComSignalLength is inconsistent at `%1%\'."), signal)$$END$$DIE()$
			$END$
			$FOREACH value value_list$
				$SIGNAL_RANGE_CHECK(value, "UINT8", 8, "ComSignalDataInvalidValue")$
			$END$
		$ELIF (EQ(signal_type, "UINT8") || EQ(signal_type, "UINT16")
				|| EQ(signal_type, "UINT32") || EQ(signal_type, "SINT8")
				|| EQ(signal_type, "SINT16") || EQ(signal_type, "SINT32"))$
$			// [NCOM038] 整数型のシグナルに設定されたComSignalDataInvalidValueの値がComBitSizeのレンジに収まっていない場合はエラー
			$SIGNAL_RANGE_CHECK(signal_invalid_value, signal_type, signal_bitsize, "ComSignalDataInvalidValue")$
		$END$
	$END$
$END$

$ ====================================================================
$ シグナル・グループシグナルのComSignalEndiannessチェック関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalEndianness
$ ARGV[3]  : ComSignalType
$ ====================================================================
$FUNCTION CHECK_SIGNAL_ENDIANNESS$
	$signal            = ARGV[1]$
	$signal_endianness = ARGV[2]$
	$signal_type       = ARGV[3]$
	
	$IF EQ(signal_endianness, "LITTLE_ENDIAN") || EQ(signal_endianness, "BIG_ENDIAN")$
$		// [COM553] UINT8_NのシグナルのComSignalEndiannessにOPAQUEが指定されていない場合はエラー
		$IF EQ(signal_type, "UINT8_N")$
			$ERROR$$FORMAT(_("`%1%\' should set OPAQUE to ComSignalEndianness."), signal)$$END$$DIE()$
		$END$
	$ELIF EQ(signal_endianness, "OPAQUE")$
$		// [NCOM026] UINT8_N以外のシグナルのComSignalEndiannessにOPAQUEが指定されている場合はエラー
		$IF !EQ(signal_type, "UINT8_N")$
			$ERROR$$FORMAT("ComSignalEndianness should not be set OPAQUE.")$$END$$DIE()$
		$END$
	$ELSE$
		$ERROR$$FORMAT("ComSignalEndianness should be set LITTLE_ENDIAN or BIG_ENDIAN or OPAQUE.")$$END$$DIE()$
	$END$
$END$

$ ====================================================================
$ シグナル・グループシグナルのComSignalBitPositionチェック関数
$ ARGV[1]  : ComSignal[]またはComGroupSignal[]
$ ARGV[2]  : ComSignalBitPosition
$ ARGV[3]  : ComSignalEndianness
$ ARGV[4]  : ComSignalType
$ ARGV[5]  : ComSignalBitSize
$ ====================================================================
$FUNCTION CHECK_SIGNAL_BITPOSITION$
	$signal             = ARGV[1]$
	$signal_bitposition = ARGV[2]$
	$signal_endianness  = ARGV[3]$
	$signal_type        = ARGV[4]$
	$signal_bitsize     = ARGV[5]$
	
	$IF EQ(signal_type, "UINT8_N")$
$		// [NCOM019] データ型がUINT8_NのシグナルのComBitPositionが8の倍数でない場合はエラー
		$IF (signal_bitposition % 8) != 0$
			$ERROR$$FORMAT(_("ComBitPosition is not the correct value. `%1%\' is UINT8_N."), signal)$$END$$DIE()$
		$END$
	$END$
$	// ComSignalEndiannessがBIG_ENDIANの場合はComBitPosition(MSB)をLSBに変換
	$IF EQ (signal_endianness, "BIG_ENDIAN") && (signal_bitsize > 1)$
		$signal_lsb = MSB2LSB(signal_bitposition, signal_bitsize)$
	$ELSE$
		$signal_lsb = signal_bitposition$
	$END$
	
	$RESULT = signal_lsb$
	
$END$

$ ====================================================================
$ シグナルのComSignalDataInvalidActionチェック関数
$ ARGV[1]  : ComSignal[]
$ ARGV[2]  : ComSignalDataInvalidAction
$ ARGV[3]  : ComSignalDataInvalidValue
$ ====================================================================
$FUNCTION CHECK_SIGNAL_DATAINVALIDACTION$
	$signal = ARGV[1]$
	$signal_datainvalidaction = ARGV[2]$
	$signal_datainvalidvalue = ARGV[3]$
	
	$IF LENGTH(signal_datainvalidaction)$
		$IF !EQ(signal_datainvalidaction, "NOTIFY") && !EQ(signal_datainvalidaction, "REPLACE")$
			$ERROR$$FORMAT(_("ComDataInvalidAction should not be set `%1%\'. (%2%\)"),signal_datainvalidaction , signal)$$END$$DIE()$
		$END$
		$IF !LENGTH(signal_datainvalidvalue)$
			$WARNING$$FORMAT(_("ComSignalDataInvalidAction has been set, but, ComSignalDataInvalidValue is not set (%1%\)"), signal)$$END$
		$END$
	$ELSE$
		$signal_datainvalidaction = "INVALID_UINT8"$
	$END$
	
	$RESULT = signal_datainvalidaction$
	
$END$

$ ====================================================================
$ シグナルグループのComSignalDataInvalidActionチェック関数
$ ARGV[1]  : ComSignalGroup[]
$ ARGV[2]  : ComSignalDataInvalidAction
$ ARGV[3]  : ComSignalGroup.gg_signal_list[signal_group]
$ ====================================================================
$FUNCTION CHECK_SIGNAL_GRUOP_DATAINVALIDACTION$
	$signal_group = ARGV[1]$
	$signal_group_datainvalidaction = ARGV[2]$
	$group_signal_list = ARGV[3]$
	$invaliddate_flag = "FALSE"$

	$IF LENGTH(signal_group_datainvalidaction)$
		$IF !EQ(signal_group_datainvalidaction, "NOTIFY") && !EQ(signal_group_datainvalidaction, "REPLACE")$
			$ERROR$$FORMAT(_("ComDataInvalidAction should not be set `%1%\'. (%2%\)"),signal_group_datainvalidaction , signal_group)$$END$$DIE()$
		$END$
		$FOREACH g_signal_id group_signal_list$
			$IF LENGTH(ComGroupSignal.ComSignalDataInvalidValue[g_signal_id])$
				$invaliddate_flag = "TRUE"$
			$END$
		$END$
	$ELSE$
		$signal_group_datainvalidaction = "INVALID_UINT8"$
		$invaliddate_flag = "TRUE"$
	$END$

	$IF EQ(invaliddate_flag, "FALSE")$
		$WARNING$$FORMAT(_("ComSignalDataInvalidAction has been set, but is not set ComSignalDataInvalidValue of GroupSignal, which is included in the SignalGroup (%1%\)"), signal_group)$$END$	
	$END$

	$RESULT = signal_group_datainvalidaction$
	
$END$
$ ====================================================================
$ シグナル・シグナルグループのComSignalRxDataTimeoutActionチェック関数
$ ARGV[1]  : ComSignal[]またはComSignalGroup[]
$ ARGV[2]  : ComSignalRxDataTimeoutAction
$ ====================================================================
$FUNCTION CHECK_SIGNAL_RXDATATIMEOUTACTION$
	$signal = ARGV[1]$
	$signal_rxdatatimeoutaction = ARGV[2]$
	
	$IF LENGTH(signal_rxdatatimeoutaction)$
		$IF !EQ(signal_rxdatatimeoutaction, "NONE") && !EQ(signal_rxdatatimeoutaction, "REPLACE")$
			$ERROR$$FORMAT(_("ComRxDataTimeoutAction should not be set `%1%\'. (%2%\)"),signal_rxdatatimeoutaction , signal)$$END$$DIE()$
		$END$
	$ELSE$
$		// [COM500] ComRxDataTimeoutActionが省略された場合はNONEと同等
		$signal_rxdatatimeoutaction = "NONE"$
	$END$
	
	$RESULT = signal_rxdatatimeoutaction$
	
$END$

$ ====================================================================
$ シグナル・シグナルグループのComUpdateBitPositionチェック関数
$ ARGV[1]  : ComSignal[]またはComSignalGroup[]
$ ARGV[2]  : ComUpdateBitPosition
$ ARGV[3]  : idpu_ref
$ ====================================================================
$FUNCTION CHECK_SIGNAL_UPDATEBITPOSITION$
	$signal = ARGV[1]$
	$signal_updatebitposition = ARGV[2]$
	$signal_ipdu_ref = ARGV[3]$
	
	$IF !LENGTH(signal_updatebitposition)$
		$signal_updatebitposition = "COM_INVALID_UINT16"$
	$ELSE$
$		// [COM310] 送信モードがDIRECTかMIXEDのIPDUがComTxModeNumberOfRepetitionsに1以上の値を設定している場合，ComUpdateBitPositionを設定してはならない
		$FOREACH tx_mode_id ComTxMode_true.ID_LIST$
			$IF EQ(signal_ipdu_ref, ComTxIPdu.PARENT[ComTxModeTrue.PARENT[ComTxMode_true.PARENT[tx_mode_id]]])$
				$IF (EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "DIRECT") || EQ(ComTxMode_true.ComTxModeMode[tx_mode_id], "MIXED")) && (ComTxMode_true.ComTxModeNumberOfRepetitions[tx_mode_id] > 1)$
					$ERROR$$FORMAT(_("DIRECT or MIXED mode TxIPDU with ComTxModeNumberOfRepetitions greater or equal 1 should not have ComUpdateBitPosition. (%1%\, %2%\)"), signal_ipdu_ref, signal)$$END$$DIE()$
				$END$
			$END$
		$END$
		$FOREACH tx_mode_id ComTxMode_false.ID_LIST$
			$IF EQ(signal_ipdu_ref, ComTxIPdu.PARENT[ComTxModeFalse.PARENT[ComTxMode_false.PARENT[tx_mode_id]]])$
				$IF (EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "DIRECT") || EQ(ComTxMode_false.ComTxModeMode[tx_mode_id], "MIXED")) && (ComTxMode_false.ComTxModeNumberOfRepetitions[tx_mode_id] > 1)$
					$ERROR$$FORMAT(_("DIRECT or MIXED mode TxIPDU with ComTxModeNumberOfRepetitions greater or equal 1 should not have ComUpdateBitPosition. (%1%\, %2%\)"), signal_ipdu_ref, signal)$$END$$DIE()$
				$END$
			$END$
		$END$
	$END$
	
	$RESULT = signal_updatebitposition$
	
$END$

$ ====================================================================
$ シグナル・シグナルグループがIPDUバッファに配置されているかチェック
$ ARGV[1]  : ComSignal[]またはComSignalGroup[]
$ ARGV[2]  : ComBitPosition
$ ARGV[3]  : ComSignalLength
$ ARGV[4]  : ComBitSize
$ ARGV[5]  : ipdu_ref
$ ARGV[6]  : ComSignalType
$ ARGV[7]  : ComSignalEndianness
$ ====================================================================
$FUNCTION CHECK_SIGNAL_PLACE_IPDUBUF$
	$signal = ARGV[1]$
	$signal_bitposition = ARGV[2]$
	$signal_length = ARGV[3]$
	$signal_bitsize = ARGV[4]$
	$signal_ipdu_ref = ARGV[5]$
	$signal_type = ARGV[6]$
	$signal_endianness = ARGV[7]$

	$signal_size = signal_bitsize$
$	// [NCOM051]IPDUバッファに配置されないシグナルまたはシグナルグループはエラー
	$IF !LENGTH(signal_ipdu_ref)$
		$ERROR$$FORMAT(_("`%1%\' has not been placed in the IPDU."), signal)$$END$$DIE()$
	$END$
	$ipdu_id = signal_ipdu_ref$
	$pdu_length = ComIPdu.pdu_length[ipdu_id]$
	$IF EQ(signal_type, "UINT8_N")$
		$IF ((signal_bitposition + (signal_length * 8)) > (pdu_length * 8))$
$			// [NCOM015]IPDUバッファ内にシグナルが収らない場合はエラー
			$ERROR$$FORMAT(_("`%1%\' is not fit in IPDU buffer."), signal)$$END$$DIE()$
		$END$
	$ELSE$
		$IF EQ(signal_endianness, "LITTLE_ENDIAN")$
			$IF ((signal_bitposition + signal_size) > (pdu_length * 8))$
$				// [NCOM016]IPDUバッファ内にシグナルが収らない場合はエラー
				$ERROR$$FORMAT(_("`%1%\' is not fit in IPDU buffer."), signal)$$END$$DIE()$
			$END$
		$ELIF EQ(ComSignal.ComSignalEndianness[signal_id], "BIG_ENDIAN")$
			$IF ((((pdu_length - (signal_bitposition / 8) - 1) * 8) + (signal_bitposition % 8) + 1) < signal_bitsize)$
$				// [NCOM111]IPDUバッファ内にシグナルが収らない場合はエラー
				$ERROR$$FORMAT(_("`%1%\' is not fit in IPDU buffer."), signal)$$END$$DIE()$
			$END$
		$END$
	$END$
$END$

$ ====================================================================
$ シグナル・シグナルグループのComErrorNotificationチェック関数
$ ARGV[1]  : ComErrorNotification
$ ====================================================================
$FUNCTION CHECK_SIGNAL_ERRORNOTIFICATION$
	$signal_errornotification = ARGV[1]$
	
	$IF LENGTH(signal_errornotification)$
$		// [COM402] 関数名はC言語で扱える文字列でなければならない
		$FUNC_NAME_CHECK(signal_errornotification)$
	$ELSE$
		$signal_errornotification = "NULL_PTR"$
	$END$
	
	$RESULT = signal_errornotification$
	
$END$

$ ====================================================================
$ シグナル・シグナルグループのComInvalidNotificationチェック関数
$ ARGV[1]  : ComInvalidNotification
$ ====================================================================
$FUNCTION CHECK_SIGNAL_INVALIDNOTIFICATION$
	$signal_invalidnotification = ARGV[1]$
	
	$IF LENGTH(signal_invalidnotification)$
$		// [COM402] 関数名はC言語で扱える文字列でなければならない
		$FUNC_NAME_CHECK(signal_invalidnotification)$
	$ELSE$
		$signal_invalidnotification = "NULL_PTR"$
	$END$
	
	$RESULT = signal_invalidnotification$
	
$END$

$ ====================================================================
$ シグナル・シグナルグループのComNotificationチェック関数
$ ARGV[1]  : ComNotification
$ ====================================================================
$FUNCTION CHECK_SIGNAL_NOTIFICATION$
	$signal_notification = ARGV[1]$
	
	$IF LENGTH(signal_notification)$
$		// [COM402] 関数名はC言語で扱える文字列でなければならない
		$FUNC_NAME_CHECK(signal_notification)$
	$ELSE$
		$signal_notification = "NULL_PTR"$
	$END$
	
	$RESULT = signal_notification$
	
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
	$TAB$$TAB$$ComConfig.signal_num[config_id] + ComConfig.g_signal_num[config_id]$U,$TAB$/* tnum_signal */$NL$
	$TAB$$TAB$$ComConfig.signal_g_num[config_id]$U,$TAB$/* tnum_signal_g */$NL$
	$TAB$$TAB$$ComConfig.ipdu_g_num[config_id]$U,$TAB$/* tnum_ipdu_g */$NL$
	$TAB$$TAB$signal_inib_table_$ComConfig[config_id]$,$TAB$/* p_signal_inib_table */$NL$
	$IF LENGTH(ComConfig.signal_g_list[com_config_id])$
		$TAB$$TAB$signal_g_inib_table_$ComConfig[config_id]$,$TAB$/* p_signal_g_inib_table */$NL$
	$ELSE$
		$TAB$$TAB$NULL_PTR,$TAB$/* p_signal_g_inib_table */$NL$
	$END$
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
		$TAB$$TAB$NULL_PTR$TAB$/* p_tx_ipdu_inib_list */$NL$
	$END$
	$TAB$}
$END$
$NL$};$NL$
$NL$

$	DUMP()$
$	$WARNING$$FORMAT(_("(%1%\)"), xxxx)$$END$

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
$	  <COM001_Conf> ComSignalGroup/ComSystemTemplateSignalGroupRef
$	  <COM002_Conf> ComSignalGroup/ComGroupSignal/ComSystemTemplateSystemSignalRef

$	その他の仕様説明
$	  <COM585> 本ジェネレータではCom_Cfg.cは生成しない
$	  <COM607> 本ジェネレータではリンクタイムパラメータはサポートしない
