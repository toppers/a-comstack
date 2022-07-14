$
$  TOPPERS/A-CANTP
$      AuTomotive CANTP
$
$  Copyright (C) 2016-2017 by Center for Embedded Computing Systems
$                             Graduate School of Information Science, Nagoya Univ., JAPAN
$  Copyright (C) 2016-2017 by FUJI SOFT INCORPORATED, JAPAN
$  Copyright (C) 2016-2017 by NEC Communication Systems, Ltd., JAPAN
$  Copyright (C) 2016-2017 by SCSK Corporation, JAPAN
$  Copyright (C) 2016-2017 by SUZUKI MOTOR CORPORATION
$  Copyright (C) 2016-2017 by TOSHIBA CORPORATION, JAPAN
$  Copyright (C) 2016-2017 by Witz Corporation
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
$  $Id: cantp.tf 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
$

$ // 暫定対応(手動でIDをコンフィグすると間違えるため)
$ // 一部のエラーチェック、整合性のチェックのみ対応
$ // 複数コンフィグには対応していない

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

$	// 0割エラー
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
$				// [NCanTp_00004] 割り算の余りは繰り上げる
				$IF (over_mod + under_mod) > 0$
					$div_result = div_result + 1$
				$END$
			$END$
		$END$

$		調整不要(adjust == 1)の場合は通常の割り算を実施
		$IF adjust == 1$
			$div_result = num1 / num2$
			$mod_result = num1 % num2$
$			// [NCanTp_00004] 割り算の余りは繰り上げる
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
$ 浮動小数型用引き算割り算関数
$ ====================================================================
$FUNCTION SUB_DIV_FLOAT_VALUE$
	$arg1 = ARGV[1]$
	$arg2 = ARGV[2]$
	$arg3 = ARGV[3]$
	$arg_name1 = ARGV[4]$
	$arg_name2 = ARGV[5]$
	$arg_name3 = ARGV[6]$
	$arg_str1 = ETOF(arg1)$
	$arg_str2 = ETOF(arg2)$
	$arg_str3 = ETOF(arg3)$

$	// 引数に小数点が指定されていない場合はエラー
	$tmp = REGEX_REPLACE(arg_str1, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name1, arg_str1)$$END$$DIE()$
	$END$
	$tmp = REGEX_REPLACE(arg_str2, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name2, arg_str2)$$END$$DIE()$
	$END$
	$tmp = REGEX_REPLACE(arg_str3, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name3, arg_str3)$$END$$DIE()$
	$END$

	$num1_l = REGEX_REPLACE(arg_str1, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num1_r = REGEX_REPLACE(arg_str1, "^[0-9]+\\.([0-9]+)$", "$1")$
	$num1 = ATOI(CONCAT(num1_l, num1_r), 10)$
	$num2_l = REGEX_REPLACE(arg_str2, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num2_r = REGEX_REPLACE(arg_str2, "^[0-9]+\\.([0-9]+)$", "$1")$
	$num2 = ATOI(CONCAT(num2_l, num2_r), 10)$
	$num3_l = REGEX_REPLACE(arg_str3, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num3_r = REGEX_REPLACE(arg_str3, "^[0-9]+\\.([0-9]+)$", "$1")$
	$num3 = ATOI(CONCAT(num3_l, num3_r), 10)$

$	// 引き算の実施
	$seisuu = ATOI(num1_l, 10) - ATOI(num3_l, 10)$
	$shousuu1 = ATOI(num1_r, 10)$
	$shousuu2 = ATOI(num3_r, 10)$
	$keta = 0$
$	// 桁をそろえる
	$digits_diff = STRING_SIZE(num1_r) - STRING_SIZE(num3_r)$
	$IF digits_diff > 0$
		$keta = STRING_SIZE(num1_r)$
		$cnt = digits_diff$
		$WHILE(cnt > 0)$
			$shousuu2 = shousuu2 * 10$
			$cnt = cnt - 1$
		$END$
	$ELIF digits_diff < 0$
		$keta = STRING_SIZE(num3_r)$
		$cnt = -digits_diff$
		$WHILE(cnt > 0)$
			$shousuu1 = shousuu1 * 10$
			$cnt = cnt - 1$
		$END$
		
	$ELSE$
		$keta = STRING_SIZE(num1_r)$
	$END$
	$shousuu = 0$
$	// 小さい場合は上位の値を足して計算する
	$IF shousuu1 < shousuu2$
		$seisuu = seisuu - 1$
		$shousuu = 1$
		$cnt = keta$
		$WHILE(cnt > 0)$
			$shousuu = shousuu * 10$
			$cnt = cnt - 1$
		$END$
	$END$
	$shousuu = shousuu + shousuu1 - shousuu2$
	$keta2 = STRING_SIZE(shousuu)$
	$num = CONCAT(seisuu, ".")$
	$WHILE(keta2 < keta)$
		$num = CONCAT(num, "0")$
		$keta2 = keta2 + 1$
	$END$
	$num = CONCAT(num, shousuu)$
$	// 引き算の結果をnum1とする
	$num1_l = REGEX_REPLACE(num, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num1_r = REGEX_REPLACE(num, "^[0-9]+\\.([0-9]+)$", "$1")$
	$num1 = ATOI(CONCAT(num1_l, num1_r), 10)$

$	// 0割エラー
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
$				// [NCanTp_00004] 割り算の余りは繰り上げる
				$IF (over_mod + under_mod) > 0$
					$div_result = div_result + 1$
				$END$
			$END$
		$END$

$		調整不要(adjust == 1)の場合は通常の割り算を実施
		$IF adjust == 1$
			$div_result = num1 / num2$
			$mod_result = num1 % num2$
$			// [NCanTp_00004] 割り算の余りは繰り上げる
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
$ 浮動小数型秒単位をミリ秒単位に変換関数
$ ====================================================================
$FUNCTION STOMS_FLOAT_VALUE$
	$arg1 = ARGV[1]$
	$arg_name1 = ARGV[2]$
	$arg_str1 = ETOF(arg1)$

$	// 引数に小数点が指定されていない場合はエラー
	$tmp = REGEX_REPLACE(arg_str1, "^[0-9]+\\.[0-9]+$", "")$
	$IF !EQ(tmp, "")$
		$ERROR$$FORMAT(_("[%1%]`%2%\' is not a float value."), arg_name1, arg_str1)$$END$$DIE()$
	$END$

	$num1_l = REGEX_REPLACE(arg_str1, "^([0-9]+)\\.[0-9]+$", "$1")$
	$num1_r = REGEX_REPLACE(arg_str1, "^[0-9]+\\.([0-9]+)$", "$1")$
	$num1 = ATOI(CONCAT(num1_l, num1_r), 10)$

$	// ms単位に桁をあわせる
	$digits_diff = 3 - STRING_SIZE(num1_r)$
	$IF digits_diff > 0$
		$cnt = digits_diff$
		$WHILE(cnt > 0)$
			$num1 = num1 * 10$
			$cnt = cnt - 1$
		$END$
	$ELIF digits_diff < 0$
$	// ms以下の単位は切り上げ
		$digits_diff = STRING_SIZE(num1_r) - 3$
		$cnt = digits_diff$
		$add = 0$
		$WHILE(cnt > 0)$
			$IF (num1 % 10) != 0$
				$add = 1$
			$END$
			$num1 = num1 / 10$
			$cnt = cnt - 1$
		$END$
		$IF add == 1$
			$num1 = num1 + 1$
		$END$
	$END$
	
	$RESULT = num1$
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
$  コンフィグセットごとのリストを作成
$ ====================================================================
$FUNCTION MAKE_CFG_LIST$
	$FOREACH init_id CanTpConfig.ID_LIST$
$		// [ECUC_CanTp_00138] CanTpTxNSdu
		$new_list = {}$
		$FOREACH tx_sdu_id CanTpTxNSdu.ID_LIST$
			$IF EQ(init_id, CanTpChannel.PARENT[CanTpTxNSdu.PARENT[tx_sdu_id]])$
				$new_list = APPEND(new_list, tx_sdu_id)$
			$END$
		$END$
		$CanTpConfig.tx_sdu_list[init_id] = new_list$

$		// [ECUC_CanTp_00137] CanTpRxNSdu
		$new_list = {}$
		$FOREACH rx_sdu_id CanTpRxNSdu.ID_LIST$
			$IF EQ(init_id, CanTpChannel.PARENT[CanTpRxNSdu.PARENT[rx_sdu_id]])$
				$new_list = APPEND(new_list, rx_sdu_id)$
			$END$
		$END$
		$CanTpConfig.rx_sdu_list[init_id] = new_list$

		$CanTpConfig.sdu_list[init_id] = APPEND(CanTpConfig.tx_sdu_list[init_id], CanTpConfig.rx_sdu_list[init_id])$
		$CanTpConfig.sdu_num[init_id] = LENGTH(CanTpConfig.sdu_list[init_id])$
		
		
$		// [ECUC_CanTp_00274] CanTpTxNPdu
		$new_list = {}$
		$FOREACH tx_pdu_id CanTpTxNPdu.ID_LIST$
			$IF EQ(init_id, CanTpChannel.PARENT[CanTpTxNSdu.PARENT[CanTpTxNPdu.PARENT[tx_pdu_id]]])$
				$new_list = APPEND(new_list, tx_pdu_id)$
			$END$
		$END$
		$CanTpConfig.tx_pdu_list[init_id] = new_list$

$		// [ECUC_CanTp_00271] CanTpRxFcNPdu
		$new_list = {}$
		$FOREACH rx_pdu_id CanTpRxFcNPdu.ID_LIST$
			$IF EQ(init_id, CanTpChannel.PARENT[CanTpTxNSdu.PARENT[CanTpRxFcNPdu.PARENT[rx_pdu_id]]])$
				$new_list = APPEND(new_list, rx_pdu_id)$
			$END$
		$END$
		$CanTpConfig.rx_fcpdu_list[init_id] = new_list$

$		// [ECUC_CanTp_00259] CanTpTxFcNPdu
		$new_list = {}$
		$FOREACH tx_pdu_id CanTpTxFcNPdu.ID_LIST$
			$IF EQ(init_id, CanTpChannel.PARENT[CanTpRxNSdu.PARENT[CanTpTxFcNPdu.PARENT[tx_pdu_id]]])$
				$new_list = APPEND(new_list, tx_pdu_id)$
			$END$
		$END$
		$CanTpConfig.tx_fcpdu_list[init_id] = new_list$

$		// [ECUC_CanTp_00256] CanTpRxNPdu
		$new_list = {}$
		$FOREACH rx_pdu_id CanTpRxNPdu.ID_LIST$
			$IF EQ(init_id, CanTpChannel.PARENT[CanTpRxNSdu.PARENT[CanTpRxNPdu.PARENT[rx_pdu_id]]])$
				$new_list = APPEND(new_list, rx_pdu_id)$
			$END$
		$END$
		$CanTpConfig.rx_pdu_list[init_id] = new_list$

		$CanTpConfig.pdu_list[init_id] = APPEND(CanTpConfig.tx_pdu_list[init_id], CanTpConfig.rx_fcpdu_list[init_id], CanTpConfig.tx_fcpdu_list[init_id], CanTpConfig.rx_pdu_list[init_id])$
		$CanTpConfig.pdu_num[init_id] = LENGTH(CanTpConfig.pdu_list[init_id])$
	$END$
$END$


$ ====================================================================
$  ID連番ソート関数
$ ====================================================================
$FUNCTION ID_SORT$
$	// CanTpTxNSduId CanTpRxNSduId 順にソート
$	// [NCanTp_00003] CanTpTxNSduIdとCanTpRxNSduIdは共通番号領域で管理し，0からの連番とする
	$FOREACH init_id CanTpConfig.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanTpConfig.sdu_list[init_id]) - 1)$
			$find = 0$
$			// [ECUC_CanTp_00301]
			$FOREACH tx_sdu_id CanTpConfig.tx_sdu_list[init_id]$
				$IF CanTpTxNSdu.CanTpTxNSduId[tx_sdu_id] == index$
					$new_list = APPEND(new_list, tx_sdu_id)$
					$find = find + 1$
				$END$
			$END$
$			// [ECUC_CanTp_00268]
			$FOREACH rx_sdu_id CanTpConfig.rx_sdu_list[init_id]$
				$IF CanTpRxNSdu.CanTpRxNSduId[rx_sdu_id] == index$
					$new_list = APPEND(new_list, rx_sdu_id)$
					$find = find + 1$
				$END$
			$END$
			$IF find == 0$
				$ERROR$$FORMAT(_("CanTpSduId(%1%\) is not found. CanTpSduId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("CanTpSduId(%1%\) is duplicated. CanTpSduId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanTpConfig.sdu_list[init_id] = new_list$
	$END$

$	// CanTpTxNPduConfirmationPduId CanTpRxFcNPduId CanTpTxFcNPduConfirmationPduId CanTpRxNPduId 順にソート
$	// [NCanTp_00003] CanTpTxNPduConfirmationPduId CanTpRxFcNPduId CanTpTxFcNPduConfirmationPduId CanTpRxNPduIdは共通番号領域で管理し，0からの連番とする
	$FOREACH init_id CanTpConfig.ID_LIST$
		$new_list = {}$
		$FOREACH index RANGE(0, LENGTH(CanTpConfig.pdu_list[init_id]) - 1)$
			$find = 0$
$			// [ECUC_CanTp_00286]
			$FOREACH tx_pdu_id CanTpConfig.tx_pdu_list[init_id]$
				$IF CanTpTxNPdu.CanTpTxNPduConfirmationPduId[tx_pdu_id] == index$
					$new_list = APPEND(new_list, tx_pdu_id)$
					$find = find + 1$
				$END$
			$END$
$			// [ECUC_CanTp_00273]
			$FOREACH rx_fcpdu_id CanTpConfig.rx_fcpdu_list[init_id]$
				$IF CanTpRxFcNPdu.CanTpRxFcNPduId[rx_fcpdu_id] == index$
					$new_list = APPEND(new_list, rx_fcpdu_id)$
					$find = find + 1$
				$END$
			$END$
$			// [ECUC_CanTp_00287]
			$FOREACH tx_fcpdu_id CanTpConfig.tx_fcpdu_list[init_id]$
				$IF CanTpTxFcNPdu.CanTpTxFcNPduConfirmationPduId[tx_fcpdu_id] == index$
					$new_list = APPEND(new_list, tx_fcpdu_id)$
					$find = find + 1$
				$END$
			$END$
$			// [ECUC_CanTp_00258]
			$FOREACH rx_pdu_id CanTpConfig.rx_pdu_list[init_id]$
				$IF CanTpRxNPdu.CanTpRxNPduId[rx_pdu_id] == index$
					$new_list = APPEND(new_list, rx_pdu_id)$
					$find = find + 1$
				$END$
			$END$
			$IF find == 0$
				$ERROR$$FORMAT(_("CanTpPduId(%1%\) is not found. CanTpPduId should be sequential from 0."), index)$$END$$DIE()$
			$END$
			$IF find > 1$
				$ERROR$$FORMAT(_("CanTpPduId(%1%\) is duplicated. CanTpPduId should be unique."), index)$$END$$DIE()$
			$END$
		$END$
		$CanTpConfig.pdu_list[init_id] = new_list$
	$END$
$END$


$ ====================================================================
$  DLCチェック関数
$ ====================================================================
$FUNCTION DLC_CHECK$
$ DLCチェックを実施
	$dlc = ARGV[1]$
	$tatype = ARGV[2]$
	$agv3 = ARGV[3]$
	$IF EQ(tatype, "CANTP_CANFD_PHYSICAL") || EQ(tatype, "CANTP_CANFD_FUNCTIONAL")$
		$IF (dlc != 8) && (dlc != 12) && (dlc != 16) && (dlc != 20) && (dlc != 24) && (dlc != 32) && (dlc != 48) && (dlc != 64)$
			$ERROR$$FORMAT(_("(%1%\) PduLength should be 8/12/16/20/24/32/48/64."), agv3)$$END$$DIE()$
		$END$
	$ELSE$
		$IF (dlc != 8)$
			$ERROR$$FORMAT(_("(%1%\) PduLength should be 8."), agv3)$$END$$DIE()$
		$END$
	$END$

$	$RESULT = dlc_result$
$END$


$ ====================================================================
$  [NCanTp_00002] エラーチェック関数
$ ====================================================================
$FUNCTION ERROR_CHECK$
$ [NCanTp_00002] CanTp仕様に沿った設定値チェックを実施

$ [ECUC_CanTpa_00001] CanTp
$	/*
$	 *  [ECUC_CanTp_00278] CanTpGeneral
$	 */
$	// [ECUC_CanTp_00239] CanTpDevErrorDetect
	$ret = IS_TRUE(CanTpGeneral.CanTpDevErrorDetect[1])$

$	// [ECUC_CanTp_00302] CanTpDynIdSupport
	$IF LENGTH(CanTpGeneral.CanTpDynIdSupport[1]) && IS_TRUE(CanTpGeneral.CanTpDynIdSupport[1])$
$		// [NCanTp_00021] 動的IDは対象外の機能であるためFALSEに設定する
		$ERROR$$FORMAT(_("CanTpDynIdSupport(%1%\) should be `FALSE'."), CanTpGeneral.CanTpDynIdSupport[1])$$END$$DIE()$
	$END$

$	// [ECUC_CanTp_00303] CanTpGenericConnectionSupport
	$IF LENGTH(CanTpGeneral.CanTpGenericConnectionSupport[1]) && IS_TRUE(CanTpGeneral.CanTpGenericConnectionSupport[1])$
$		// [NCanTp_00022] 動的IDは対象外の機能であるためFALSEに設定する
		$ERROR$$FORMAT(_("CanTpGenericConnectionSupport(%1%\) should be `FALSE'."), CanTpGeneral.CanTpGenericConnectionSupport[1])$$END$$DIE()$
	$END$

$	// [ECUC_CanTp_00305] CanTpFlexibleDataRateSupport
	$canfdsupport = 1$
	$IF LENGTH(CanTpGeneral.CanTpFlexibleDataRateSupport[1])$
		$ret = IS_TRUE(CanTpGeneral.CanTpFlexibleDataRateSupport[1])$
		$canfdsupport = ret$
	$END$

$	// [ECUC_CanTp_00299] CanTpChangeParameterApi
	$ret = IS_TRUE(CanTpGeneral.CanTpChangeParameterApi[1])$

$	// [ECUC_CanTp_00300] CanTpReadParameterApi
	$ret = IS_TRUE(CanTpGeneral.CanTpReadParameterApi[1])$

$	// [ECUC_CanTp_00283] CanTpVersionInfoApi
	$ret = IS_TRUE(CanTpGeneral.CanTpVersionInfoApi[1])$

$	// [ECUC_CanTp_00298] CanTpPaddingByte
	$IF (CanTpGeneral.CanTpPaddingByte[1] < 0)$
		$ERROR$$FORMAT(_("CanTpPaddingByte(%1%\) should be in the range from 0 to 255."), CanTpGeneral.CanTpPaddingByte[1])$$END$$DIE()$
	$ELIF (CanTpGeneral.CanTpPaddingByte[1] > 255)$
		$ERROR$$FORMAT(_("CanTpPaddingByte(%1%\) should be in the range from 0 to 255."), CanTpGeneral.CanTpPaddingByte[1])$$END$$DIE()$
	$END$

$	/*
$	 *  [ECUC_CanTp_00290] CanTpConfig
$	 */
	$FOREACH config_id CanTpConfig.ID_LIST$
$	// [ECUC_CanTp_00240] CanTpMainFunctionPeriod
$	// [NCanTp_00035] 0はエラーとする
		$ret = CMP_FLOAT_VALUE(CanTpConfig.CanTpMainFunctionPeriod[config_id], "0.255", "CanTpMainFunctionPeriod", "MaxValue")$
		$IF (CanTpConfig.CanTpMainFunctionPeriod[config_id] < 0) || (ret == 1)$
			$ERROR$$FORMAT(_("CanTpMainFunctionPeriod(%1%\) should be in the range from 0.001 to 0.255."), CanTpConfig.CanTpMainFunctionPeriod[config_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00304] CanTpMaxChannelCnt
$	// [NCanTp_00038] 最大値65535とする
		$IF LENGTH(CanTpConfig.CanTpMaxChannelCnt[config_id]) && ((CanTpConfig.CanTpMaxChannelCnt[config_id] < 0) || (CanTpConfig.CanTpMaxChannelCnt[config_id] > 65535))$
			$ERROR$$FORMAT(_("CanTpMaxChannelCnt(%1%\) should be in the range from 0 to 65535."), CanTpConfig.CanTpMaxChannelCnt[config_id])$$END$$DIE()$
		$END$
	$END$

$	/*
$	 *  [ECUC_CanTp_00288][SWS_CanTp_00120][SWS_CanTp_00121][SWS_CanTp_00190] CanTpChannel
$	 */
	$FOREACH ch_id CanTpChannel.ID_LIST$
$	// [ECUC_CanTp_00289] CanTpChannelMode
		$IF !EQ(CanTpChannel.CanTpChannelMode[ch_id], "CANTP_MODE_FULL_DUPLEX")$
			$IF !EQ(CanTpChannel.CanTpChannelMode[ch_id], "CANTP_MODE_HALF_DUPLEX")$
				$ERROR$$FORMAT(_("CanTpChannelMode(%1%\) should be `CANTP_MODE_FULL_DUPLEX' or `CANTP_MODE_HALF_DUPLEX'."), CanTpChannel.CanTpChannelMode[ch_id])$$END$$DIE()$
			$END$
		$END$
	$END$

$	/*
$	 *  [ECUC_CanTp_00137] CanTpRxNSdu
$	 */
	$FOREACH nsdu_id CanTpRxNSdu.ID_LIST$
$	// [ECUC_CanTp_00276] CanTpBs
$	// 多重度0の場合の対策が必要
		$IF (CanTpRxNSdu.CanTpBs[nsdu_id] < 0) || (CanTpRxNSdu.CanTpBs[nsdu_id] > 255)$
			$ERROR$$FORMAT(_("CanTpBs(%1%\) should be in the range from 0 to 255."), CanTpRxNSdu.CanTpBs[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00252] CanTpSTmin
$	// 多重度0の場合の対策が必要
		$ret = CMP_FLOAT_VALUE(CanTpRxNSdu.CanTpSTmin[nsdu_id], "0.127", "CanTpSTmin", "MaxValue")$
		$IF (CanTpRxNSdu.CanTpSTmin[nsdu_id] < 0) || (ret == 1)$
			$ERROR$$FORMAT(_("CanTpSTmin(%1%\) should be in the range from 0 to 0.127."), CanTpRxNSdu.CanTpSTmin[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00251] CanTpRxWftMax
$	// 多重度0の場合の対策が必要
		$IF (CanTpRxNSdu.CanTpRxWftMax[nsdu_id] < 0) || (CanTpRxNSdu.CanTpRxWftMax[nsdu_id] > 65535)$
			$ERROR$$FORMAT(_("CanTpRxWftMax(%1%\) should be in the range from 0 to 65535."), CanTpRxNSdu.CanTpRxWftMax[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00277] CanTpNar
$	// 多重度0の場合の対策が必要
		$IF (CanTpRxNSdu.CanTpNar[nsdu_id] < 0)$
			$ERROR$$FORMAT(_("CanTpNar(%1%\) should be in the range from 0."), CanTpRxNSdu.CanTpNar[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00245] CanTpNbr
$	// [NCanTp_00040] 多重度0の場合の対策が必要
		$IF (CanTpRxNSdu.CanTpNbr[nsdu_id] < 0)$
			$ERROR$$FORMAT(_("CanTpNbr(%1%\) should be in the range from 0."), CanTpRxNSdu.CanTpNbr[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00279] CanTpNcr
$	// 多重度0の場合の対策が必要
		$IF (CanTpRxNSdu.CanTpNcr[nsdu_id] < 0)$
			$ERROR$$FORMAT(_("CanTpNcr(%1%\) should be in the range from 0."), CanTpRxNSdu.CanTpNcr[nsdu_id])$$END$$DIE()$
		$END$

$	// [NCanTp_00024] CanTpTc
		$ret = IS_TRUE(CanTpRxNSdu.CanTpTc[nsdu_id])$

$	// [ECUC_CanTp_00281][NCanTp_00026] CanTpRxAddressingFormat
		$IF !EQ(CanTpRxNSdu.CanTpRxAddressingFormat[nsdu_id], "CANTP_STANDARD")$
			$IF !EQ(CanTpRxNSdu.CanTpRxAddressingFormat[nsdu_id], "CANTP_EXTENDED")$
				$IF !EQ(CanTpRxNSdu.CanTpRxAddressingFormat[nsdu_id], "CANTP_MIXED")$
					$ERROR$$FORMAT(_("CanTpRxAddressingFormat(%1%\) should be `CANTP_STANDARD' or `CANTP_EXTENDED' or `CANTP_MIXED'."), CanTpRxNSdu.CanTpRxAddressingFormat[nsdu_id])$$END$$DIE()$
				$END$
			$END$
		$END$

$	// [ECUC_CanTp_00250] CanTpRxTaType
		$IF canfdsupport$
			$IF !EQ(CanTpRxNSdu.CanTpRxTaType[nsdu_id], "CANTP_CANFD_FUNCTIONAL")$
				$IF !EQ(CanTpRxNSdu.CanTpRxTaType[nsdu_id], "CANTP_CANFD_PHYSICAL")$
					$IF !EQ(CanTpRxNSdu.CanTpRxTaType[nsdu_id], "CANTP_FUNCTIONAL")$
						$IF !EQ(CanTpRxNSdu.CanTpRxTaType[nsdu_id], "CANTP_PHYSICAL")$
							$ERROR$$FORMAT(_("CanTpRxTaType(%1%\) should be `CANTP_CANFD_FUNCTIONAL' or `CANTP_CANFD_PHYSICAL' or `CANTP_FUNCTIONAL' or `CANTP_PHYSICAL'."), CanTpRxNSdu.CanTpRxTaType[nsdu_id])$$END$$DIE()$
						$END$
					$END$
				$END$
			$END$
		$ELSE$
			$IF !EQ(CanTpRxNSdu.CanTpRxTaType[nsdu_id], "CANTP_FUNCTIONAL")$
				$IF !EQ(CanTpRxNSdu.CanTpRxTaType[nsdu_id], "CANTP_PHYSICAL")$
					$ERROR$$FORMAT(_("CanTpFlexibleDataRateSupport is false. CanTpRxTaType(%1%\) should be `CANTP_FUNCTIONAL' or `CANTP_PHYSICAL'."), CanTpRxNSdu.CanTpRxTaType[nsdu_id])$$END$$DIE()$
				$END$
			$END$
		$END$

$	// [ECUC_CanTp_00249] CanTpRxPaddingActivation
		$IF !EQ(CanTpRxNSdu.CanTpRxPaddingActivation[nsdu_id], "CANTP_ON")$
			$IF !EQ(CanTpRxNSdu.CanTpRxPaddingActivation[nsdu_id], "CANTP_OFF")$
				$ERROR$$FORMAT(_("CanTpRxPaddingActivation(%1%\) should be `CANTP_ON' or `CANTP_OFF'."), CanTpRxNSdu.CanTpRxPaddingActivation[nsdu_id])$$END$$DIE()$
			$END$
		$END$

$	// [ECUC_CanTp_00301] CanTpRxNSduId
		$IF (CanTpRxNSdu.CanTpRxNSduId[nsdu_id] < 0) || (CanTpRxNSdu.CanTpRxNSduId[nsdu_id] > 65535)$
			$ERROR$$FORMAT(_("CanTpRxNSduId(%1%\) should be in the range from 0 to 65535."), CanTpRxNSdu.CanTpRxNSduId[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00241] CanTpRxNSduRef
$	// チェックなし
	$END$

$	/*
$	 *  [ECUC_CanTp_00138] CanTpTxNSdu
$	 */
	$FOREACH nsdu_id CanTpTxNSdu.ID_LIST$
$	// [ECUC_CanTp_00263] CanTpNas
		$IF (CanTpTxNSdu.CanTpNas[nsdu_id] < 0)$
			$ERROR$$FORMAT(_("CanTpNas(%1%\) should be in the range from 0."), CanTpTxNSdu.CanTpNas[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00264] CanTpNbs
$	// 多重度0の場合の対策が必要
		$IF (CanTpTxNSdu.CanTpNbs[nsdu_id] < 0)$
			$ERROR$$FORMAT(_("CanTpNbs(%1%\) should be in the range from 0."), CanTpTxNSdu.CanTpNbs[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00265] CanTpNcs
$	// 多重度0の場合の対策が必要
		$IF (CanTpTxNSdu.CanTpNcs[nsdu_id] < 0)$
			$ERROR$$FORMAT(_("CanTpNcs(%1%\) should be in the range from 0."), CanTpTxNSdu.CanTpNcs[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00282] CanTpTc
		$ret = IS_TRUE(CanTpTxNSdu.CanTpTc[nsdu_id])$

$	// [ECUC_CanTp_00262][NCanTp_00028] CanTpTxAddressingFormat
		$IF !EQ(CanTpTxNSdu.CanTpTxAddressingFormat[nsdu_id], "CANTP_STANDARD")$
			$IF !EQ(CanTpTxNSdu.CanTpTxAddressingFormat[nsdu_id], "CANTP_EXTENDED")$
				$IF !EQ(CanTpTxNSdu.CanTpTxAddressingFormat[nsdu_id], "CANTP_MIXED")$
					$ERROR$$FORMAT(_("CanTpTxAddressingFormat(%1%\) should be `CANTP_STANDARD' or `CANTP_EXTENDED' or `CANTP_MIXED'."), CanTpTxNSdu.CanTpTxAddressingFormat[nsdu_id])$$END$$DIE()$
				$END$
			$END$
		$END$

$	// [ECUC_CanTp_00270][NCanTp_00029] CanTpTxTaType
		$IF canfdsupport$
			$IF !EQ(CanTpTxNSdu.CanTpTxTaType[nsdu_id], "CANTP_CANFD_FUNCTIONAL")$
				$IF !EQ(CanTpTxNSdu.CanTpTxTaType[nsdu_id], "CANTP_CANFD_PHYSICAL")$
					$IF !EQ(CanTpTxNSdu.CanTpTxTaType[nsdu_id], "CANTP_FUNCTIONAL")$
						$IF !EQ(CanTpTxNSdu.CanTpTxTaType[nsdu_id], "CANTP_PHYSICAL")$
							$ERROR$$FORMAT(_("CanTpTxTaType(%1%\) should be `CANTP_CANFD_FUNCTIONAL' or `CANTP_CANFD_PHYSICAL' or `CANTP_FUNCTIONAL' or `CANTP_PHYSICAL'."), CanTpTxNSdu.CanTpTxTaType[nsdu_id])$$END$$DIE()$
						$END$
					$END$
				$END$
			$END$
		$ELSE$
			$IF !EQ(CanTpTxNSdu.CanTpTxTaType[nsdu_id], "CANTP_FUNCTIONAL")$
				$IF !EQ(CanTpTxNSdu.CanTpTxTaType[nsdu_id], "CANTP_PHYSICAL")$
					$ERROR$$FORMAT(_("CanTpFlexibleDataRateSupport is false. CanTpTxTaType(%1%\) should be `CANTP_FUNCTIONAL' or `CANTP_PHYSICAL'."), CanTpTxNSdu.CanTpTxTaType[nsdu_id])$$END$$DIE()$
				$END$
			$END$
		$END$

$	// [ECUC_CanTp_00269] CanTpTxPaddingActivation
		$IF !EQ(CanTpTxNSdu.CanTpTxPaddingActivation[nsdu_id], "CANTP_ON")$
			$IF !EQ(CanTpTxNSdu.CanTpTxPaddingActivation[nsdu_id], "CANTP_OFF")$
				$ERROR$$FORMAT(_("CanTpTxPaddingActivation(%1%\) should be `CANTP_ON' or `CANTP_OFF'."), CanTpTxNSdu.CanTpTxPaddingActivation[nsdu_id])$$END$$DIE()$
			$END$
		$END$

$	// [ECUC_CanTp_00268] CanTpTxNSduId
		$IF (CanTpTxNSdu.CanTpTxNSduId[nsdu_id] < 0) || (CanTpTxNSdu.CanTpTxNSduId[nsdu_id] > 65535)$
			$ERROR$$FORMAT(_("CanTpRxNSduId(%1%\) should be in the range from 0 to 65535."), CanTpTxNSdu.CanTpTxNSduId[nsdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00261] CanTpTxNSduRef
$	// チェックなし
	$END$

$	/*
$	 *  [ECUC_CanTp_00256] CanTpRxNPdu
$	 */
	$FOREACH npdu_id CanTpRxNPdu.ID_LIST$
$	// [ECUC_CanTp_00258] CanTpRxNPduId
		$IF (CanTpRxNPdu.CanTpRxNPduId[npdu_id] < 0) || (CanTpRxNPdu.CanTpRxNPduId[npdu_id] > 65535)$
			$ERROR$$FORMAT(_("CanTpRxNPduId(%1%\) should be in the range from 0 to 65535."), CanTpRxNPdu.CanTpRxNPduId[npdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00257] CanTpRxNPduRef
$	// チェックなし
	$END$

$	/*
$	 *  [ECUC_CanTp_00259] CanTpTxFcNPdu
$	 */
	$FOREACH npdu_id CanTpTxFcNPdu.ID_LIST$
$	// [ECUC_CanTp_00287] CanTpTxFcNPduConfirmationPduId
		$IF (CanTpTxFcNPdu.CanTpTxFcNPduConfirmationPduId[npdu_id] < 0) || (CanTpTxFcNPdu.CanTpTxFcNPduConfirmationPduId[npdu_id] > 65535)$
			$ERROR$$FORMAT(_("CanTpTxFcNPduConfirmationPduId(%1%\) should be in the range from 0 to 65535."), CanTpTxFcNPdu.CanTpTxFcNPduConfirmationPduId[npdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00260] CanTpTxFcNPduRef
$	// チェックなし
	$END$

$	/*
$	 *  [ECUC_CanTp_00274] CanTpTxNPdu
$	 */
	$FOREACH npdu_id CanTpTxNPdu.ID_LIST$
$	// [ECUC_CanTp_00286] CanTpTxNPduConfirmationPduId
		$IF (CanTpTxNPdu.CanTpTxNPduConfirmationPduId[npdu_id] < 0) || (CanTpTxNPdu.CanTpTxNPduConfirmationPduId[npdu_id] > 65535)$
			$ERROR$$FORMAT(_("CanTpTxNPduConfirmationPduId(%1%\) should be in the range from 0 to 65535."), CanTpTxNPdu.CanTpTxNPduConfirmationPduId[npdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00275] CanTpTxNPduRef
$	// チェックなし
	$END$

$	/*
$	 *  [ECUC_CanTp_00271] CanTpRxFcNPdu
$	 */
	$FOREACH npdu_id CanTpRxFcNPdu.ID_LIST$
$	// [ECUC_CanTp_00273] CanTpRxFcNPduId
		$IF (CanTpRxFcNPdu.CanTpRxFcNPduId[npdu_id] < 0) || (CanTpRxFcNPdu.CanTpRxFcNPduId[npdu_id] > 65535)$
			$ERROR$$FORMAT(_("CanTpRxFcNPduId(%1%\) should be in the range from 0 to 65535."), CanTpRxFcNPdu.CanTpRxFcNPduId[npdu_id])$$END$$DIE()$
		$END$

$	// [ECUC_CanTp_00272] CanTpRxFcNPduRef
$	// チェックなし
	$END$

$	/*
$	 *  [ECUC_CanTp_00139] CanTpNTa
$	 */
	$FOREACH con_id CanTpNTa.ID_LIST$
$	// [ECUC_CanTp_00255] CanTpNTa
		$IF (CanTpNTa.CanTpNTa[con_id] < 0) || (CanTpNTa.CanTpNTa[con_id] > 255)$
			$ERROR$$FORMAT(_("CanTpNTa(%1%\) should be in the range from 0 to 255."), CanTpNTa.CanTpNTa[con_id])$$END$$DIE()$
		$END$
	$END$

$	/*
$	 *  [ECUC_CanTp_00253] CanTpNSa
$	 */
	$FOREACH con_id CanTpNSa.ID_LIST$
$	// [ECUC_CanTp_00254] CanTpNSa
		$IF (CanTpNSa.CanTpNSa[con_id] < 0) || (CanTpNSa.CanTpNSa[con_id] > 255)$
			$ERROR$$FORMAT(_("CanTpNSa(%1%\) should be in the range from 0 to 255."), CanTpNSa.CanTpNSa[con_id])$$END$$DIE()$
		$END$
	$END$

$	/*
$	 *  [ECUC_CanTp_00284] CanTpNAe
$	 */
	$FOREACH con_id CanTpNAe.ID_LIST$
$	// [ECUC_CanTp_00285] CanTpNAe
		$IF (CanTpNAe.CanTpNAe[con_id] < 0) || (CanTpNAe.CanTpNAe[con_id] > 255)$
			$ERROR$$FORMAT(_("CanTpNAe(%1%\) should be in the range from 0 to 255."), CanTpNAe.CanTpNAe[con_id])$$END$$DIE()$
		$END$
	$END$
$END$

$ ====================================================================
$  [SWS_CanTp_00001] プリコンパイル用ヘッダ生成関数
$ ====================================================================
$FUNCTION GEN_CANTP_CFG_H$
	$FILE "CanTp_Cfg.h"$
	/* CanTp_Cfg.h */$NL$
	
	#ifndef TOPPERS_A_CANTP_CFG_H$NL$
	#define TOPPERS_A_CANTP_CFG_H$NL$
	$NL$

$	/*
$	 *  マクロ定義
$	 */
$	// [ECUC_CanTp_00239] CanTpDevErrorDetect
$	// [NCanTp_00020] 定数を生成
$	// デフォルト値はFALSE
	#define CANTP_DEV_ERROR_DETECT$TAB$
	$IF LENGTH(CanTpGeneral.CanTpDevErrorDetect[1]) && IS_TRUE(CanTpGeneral.CanTpDevErrorDetect[1])$
		STD_ON
	$ELSE$
		STD_OFF
	$END$
	$NL$

$	// [ECUC_CanTp_00299] CanTpChangeParameterApi
$	// デフォルト値はTRUE
	#define CANTP_CHANGE_PARAMETER_API$TAB$
	$IF LENGTH(CanTpGeneral.CanTpChangeParameterApi[1]) && !IS_TRUE(CanTpGeneral.CanTpChangeParameterApi[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$

$	// [ECUC_CanTp_00300] CanTpReadParameterApi
$	// デフォルト値はTRUE
	#define CANTP_READ_PARAMETER_API$TAB$
	$IF LENGTH(CanTpGeneral.CanTpReadParameterApi[1]) && !IS_TRUE(CanTpGeneral.CanTpReadParameterApi[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$

$	// [ECUC_CanTp_00283] CanTpVersionInfoApi
$	// デフォルト値はTRUE
	#define CANTP_VERSION_INFO_API$TAB$
	$IF LENGTH(CanTpGeneral.CanTpVersionInfoApi[1]) && !IS_TRUE(CanTpGeneral.CanTpVersionInfoApi[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$

$	// [ECUC_CanTp_00305] CanTpFlexibleDataRateSupport
$	// デフォルト値はTRUE
	#define CANTP_FLEXIBLE_DATA_RATE_SUPPORT$TAB$
	$IF LENGTH(CanTpGeneral.CanTpFlexibleDataRateSupport[1]) && !IS_TRUE(CanTpGeneral.CanTpFlexibleDataRateSupport[1])$
		STD_OFF
	$ELSE$
		STD_ON
	$END$
	$NL$

$	// [ECUC_CanTp_00298] CanTpPaddingByte
	#define CANTP_PADDING_BYTE$TAB$$CanTpGeneral.CanTpPaddingByte[1]$U
	$NL$

$	// コンフィグ数を取得
	$cnt = 0$
	$FOREACH config_id CanTpConfig.ID_LIST$
		$cnt = cnt + 1$
	$END$
	#define CANTP_CONFIG_NUM $cnt$U$NL$
	$NL$

	#endif /* TOPPERS_A_CANTP_CFG_H */

$END$

$ ====================================================================
$  [SWS_CanTp_00160] ポストビルド用ヘッダ生成関数
$ ====================================================================
$ // 特に配置するものはない

$ ====================================================================
$  ポストビルド用実体生成関数
$ ====================================================================
$FUNCTION GEN_CANTP_PB_CFG_C_CFG$
$ 	// ビルド後にコンフィギュレーション可能なパラメータ用

	$cantp_config_id = ARGV[1]$

$	// NSDU受信管理ブロック定義
	/* NSDU受信管理ブロック：rx_nsdu_cb_<CanTpConfig>_<CanTpNSdu> */$NL$
	$FOREACH nsdu_id CanTpRxNSdu.ID_LIST$
		static RX_NSDU_CB rx_nsdu_cb_$cantp_config_id$_$CanTpRxNSdu[nsdu_id]$;$NL$
	$END$
	$NL$
	
$	// NSDU受信初期化ブロック定義
	/* NSDU受信初期化ブロック：rx_nsdu_inib_<CanTpConfig>_<CanTpNSdu> */$NL$
	$FOREACH nsdu_id CanTpRxNSdu.ID_LIST$
		static RX_NSDU_INIB rx_nsdu_inib_$cantp_config_id$_$CanTpRxNSdu[nsdu_id]$ = {$NL$
		$TAB$$CanTpRxNSdu.CanTpRxWftMax[nsdu_id]$U,$TAB$/* FC(WAIT)の最大送信数 */$NL$
		$TAB$$STOMS_FLOAT_VALUE(CanTpRxNSdu.CanTpSTmin[nsdu_id], "CanTpSTmin")$U,$TAB$/* STmin値 */$NL$
		$TAB$$CanTpRxNSdu.CanTpBs[nsdu_id]$U,$TAB$/* BS値 */$NL$
$		// [ECUC_CanTp_00260] CanTpTxFcNPduRefの設定値と同じCanIfTxPduRefのIDを取得
		$FOREACH canif_pdu_id CanIfTxPduCfg.ID_LIST$
			$IF EQ(CanTpTxFcNPdu.CanTpTxFcNPduRef[nsdu_id], CanIfTxPduCfg.CanIfTxPduRef[canif_pdu_id])$
				$TAB$$CanIfTxPduCfg.CanIfTxPduId[canif_pdu_id]$U,$TAB$/* CanIf_TransmitでFC送信時に指定するCanIfのId */$NL$
			$END$
		$END$
		$TAB$$CanTpRxNPdu.CanTpRxNPduId[nsdu_id]$U,$TAB$/* CanTp_RxIndicationでSF，FF，CF受信時に指定されるCanTpのId */$NL$
		$TAB$$CanTpTxFcNPdu.CanTpTxFcNPduConfirmationPduId[nsdu_id]$U,$TAB$/* CanTp_TxConfirmationでFC送信完了時に指定されるCanTpのId */$NL$
$		// [ECUC_CanTp_00241] CanTpRxNSduRefの設定値と同じPduRSrcPduRefのIDを取得
		$FOREACH src_pdu_id PduRSrcPdu.ID_LIST$
			$IF EQ(CanTpRxNSdu.CanTpRxNSduRef[nsdu_id], PduRSrcPdu.PduRSrcPduRef[src_pdu_id])$
				$TAB$$PduRSrcPdu.PduRSourcePduHandleId[src_pdu_id]$U,$TAB$/* PduR_CanTpRxIndication時に指定するId */$NL$
			$END$
		$END$
		$TAB$&rx_nsdu_cb_$cantp_config_id$_$CanTpRxNSdu[nsdu_id]$,$TAB$/* 受信NSDU管理ブロック */$NL$
		};$NL$
	$END$
	$NL$
	
$	// NSDU送信初期化ブロック定義
	/* NSDU送信初期化ブロック：tx_nsdu_inib_<CanTpConfig>_<CanTpNSdu> */$NL$
	$FOREACH nsdu_id CanTpTxNSdu.ID_LIST$
		static TX_NSDU_INIB tx_nsdu_inib_$cantp_config_id$_$CanTpTxNSdu[nsdu_id]$ = {$NL$
$		// [ECUC_CanTp_00275] CanTpTxNPduRefの設定値と同じCanIfTxPduRefのIDを取得
		$FOREACH canif_pdu_id CanIfTxPduCfg.ID_LIST$
			$IF EQ(CanTpTxNPdu.CanTpTxNPduRef[nsdu_id], CanIfTxPduCfg.CanIfTxPduRef[canif_pdu_id])$
				$TAB$$CanIfTxPduCfg.CanIfTxPduId[canif_pdu_id]$U,$TAB$/* CanIf_TransmitでSF，FF，CF送信時に指定するCanIfのId */$NL$
			$END$
		$END$
		$TAB$$CanTpTxNPdu.CanTpTxNPduConfirmationPduId[nsdu_id]$U,$TAB$/* CanTp_TxConfirmationでSF，FF，CF送信完了時に指定されるCanTpのId */$NL$
		$TAB$$CanTpRxFcNPdu.CanTpRxFcNPduId[nsdu_id]$U,$TAB$/* CanTp_RxIndicationでFC受信時に指定されるCanTpのId */$NL$
$		// [ECUC_CanTp_00261] CanTpTxNSduRefの設定値と同じPduRDestPduRefのIDを取得
		$FOREACH dest_pdu_id PduRDestPdu.ID_LIST$
			$IF EQ(CanTpTxNSdu.CanTpTxNSduRef[nsdu_id], PduRDestPdu.PduRDestPduRef[dest_pdu_id])$
				$TAB$$PduRDestPdu.PduRDestPduHandleId[dest_pdu_id]$U,$TAB$/* PduR_CanTpTxConfirmationに指定するId */$NL$
			$END$
		$END$
		};$NL$
	$END$
	$NL$
	
$	// NSDU初期化ブロック定義
	/* NSDU初期化ブロック：nsdu_inib_<CanTpConfig>[<nsdu_no>] */$NL$
	static const NSDU_INIB nsdu_inib_$cantp_config_id$[$CanTpConfig.sdu_num[cantp_config_id]$] = {$NL$
	$JOINEACH sdu_id CanTpConfig.sdu_list[cantp_config_id] ",\n"$
		$pdu_direction = ""$
		$FOREACH tx_sdu_id CanTpTxNSdu.ID_LIST$
			$IF EQ(sdu_id, tx_sdu_id)$
				$pdu_direction = "CANTP_SEND"$
				$TAB$/* $CanTpTxNSdu.CanTpTxNSduRef[tx_sdu_id]$: $tx_sdu_id$ (CanTpTxNSduId: $CanTpTxNSdu.CanTpTxNSduRef[tx_sdu_id]$) */$NL$
				$TAB${$NL$
				$ch_cnt = 0$
				$FOREACH ch_id CanTpChannel.ID_LIST$
					$IF EQ(ch_id, CanTpTxNSdu.PARENT[tx_sdu_id])$
						$ch = ch_cnt$
					$END$
					$ch_cnt = ch_cnt + 1$
				$END$
				$TAB$$TAB$$ch$U,$TAB$/* 所属するチャネル番号 */$NL$
				$TAB$$TAB$$pdu_direction$,$TAB$/* NSDU送受信方向 */$NL$
				$TAB$$TAB$($DIV_FLOAT_VALUE(CanTpTxNSdu.CanTpNas[tx_sdu_id], CanTpConfig.CanTpMainFunctionPeriod[cantp_config_id], "CanTpNas", "CanTpMainFunctionPeriod")$U + 1U),$TAB$/* N_Ar／N_Asタイムアウト値 */$NL$
				$TAB$$TAB$($DIV_FLOAT_VALUE(CanTpTxNSdu.CanTpNbs[tx_sdu_id], CanTpConfig.CanTpMainFunctionPeriod[cantp_config_id], "CanTpNbs", "CanTpMainFunctionPeriod")$U + 1U),$TAB$/* N_Br／N_Bsタイムアウト値 */$NL$
				$TAB$$TAB$($SUB_DIV_FLOAT_VALUE(CanTpTxNSdu.CanTpNcs[tx_sdu_id], CanTpConfig.CanTpMainFunctionPeriod[cantp_config_id], CanTpTxNSdu.CanTpNas[tx_sdu_id], "CanTpNcs", "CanTpMainFunctionPeriod", "CanTpNas")$U + 1U),$TAB$/* N_Cr／N_Csタイムアウト値 */$NL$
				$IF EQ(CanTpTxNSdu.CanTpTc[tx_sdu_id], "true")$
					$TAB$$TAB$CANTP_TRUE,$TAB$/* 通信中止の許可／禁止 */$NL$
				$ELSE$
					$TAB$$TAB$CANTP_FALSE,$TAB$/* 通信中止の許可／禁止 */$NL$
				$END$
				$TAB$$TAB$$CanTpTxNSdu.CanTpTxAddressingFormat[tx_sdu_id]$,$TAB$/* アドレスフォーマット */$NL$
				$TAB$$TAB$$CanTpTxNSdu.CanTpTxPaddingActivation[tx_sdu_id]$,$TAB$/* Paddingの使用有無 */$NL$
				$TAB$$TAB$$CanTpTxNSdu.CanTpTxTaType[tx_sdu_id]$,$TAB$/* N-SDUの通信タイプ */$NL$
				$N_Ae = 0$
				$FOREACH nae_id CanTpNAe.ID_LIST$
					$IF EQ(tx_sdu_id, CanTpNAe.PARENT[nae_id])$
						$N_Ae = CanTpNAe.CanTpNAe[nae_id]$
					$END$
				$END$
				$TAB$$TAB$$N_Ae$U,$TAB$/* N_AE */$NL$
				$N_Sa = 0$
				$FOREACH nsa_id CanTpNSa.ID_LIST$
					$IF EQ(tx_sdu_id, CanTpNSa.PARENT[nsa_id])$
						$N_Sa = CanTpNSa.CanTpNSa[nsa_id]$
					$END$
				$END$
				$TAB$$TAB$$N_Sa$U,$TAB$/* N_SA */$NL$
				$N_Ta = 0$
				$FOREACH nta_id CanTpNTa.ID_LIST$
					$IF EQ(tx_sdu_id, CanTpNTa.PARENT[nta_id])$
						$N_Ta = CanTpNTa.CanTpNTa[nta_id]$
					$END$
				$END$
				$TAB$$TAB$$N_Ta$U,$TAB$/* N_TA */$NL$
				$frame_size = 0$
$				// フレーム長はECUCのPduLengthで決定する
				$FOREACH npdu_id CanTpTxNPdu.ID_LIST$
					$IF EQ(sdu_id, CanTpTxNPdu.PARENT[npdu_id])$
						$FOREACH pdu_id Pdu.ID_LIST$
							$IF EQ(pdu_id, CanTpTxNPdu.CanTpTxNPduRef[npdu_id])$
								$frame_size = Pdu.PduLength[pdu_id]$
								$DLC_CHECK(frame_size, CanTpTxNSdu.CanTpTxTaType[sdu_id], pdu_id)$
							$END$
						$END$
					$END$
				$END$
				$IF EQ(CanTpTxNSdu.CanTpTxTaType[tx_sdu_id], "CANTP_PHYSICAL")$
					$sdu_sf_max = frame_size - 1$
					$sdu_ff_max = 0xffffffff$
					$sdu_sf_data = frame_size - 1$
					$sdu_ff_data = frame_size - 2$
					$sdu_cf_data = frame_size - 1$
				$ELIF EQ(CanTpTxNSdu.CanTpTxTaType[tx_sdu_id], "CANTP_FUNCTIONAL")$
					$sdu_sf_max = frame_size - 1$
					$sdu_ff_max = 0$
					$sdu_sf_data = frame_size - 1$
					$sdu_ff_data = 0$
					$sdu_cf_data = 0$
				$ELIF EQ(CanTpTxNSdu.CanTpTxTaType[tx_sdu_id], "CANTP_CANFD_PHYSICAL")$
					$sdu_sf_max = frame_size - 2$
					$sdu_ff_max = 0xffffffff$
					$sdu_sf_data = frame_size - 2$
					$sdu_ff_data = frame_size - 2$
					$sdu_cf_data = frame_size - 1$
				$ELSE$
					$sdu_sf_max = frame_size - 2$
					$sdu_ff_max = 0$
					$sdu_sf_data = frame_size - 2$
					$sdu_ff_data = 0$
					$sdu_cf_data = 0$
				$END$
				$IF EQ(CanTpTxNSdu.CanTpTxAddressingFormat[tx_sdu_id], "CANTP_STANDARD")$
					$TAB$$TAB$(PduLengthType) $sdu_sf_max$U,$TAB$/* 最大SDUデータ長(シングルフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_max$U,$TAB$/* 最大SDUデータ長(マルチフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_sf_data$U,$TAB$/* SF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_data$U,$TAB$/* FF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_cf_data$U,$TAB$/* CF最大データ長 */$NL$
				$ELSE$
					$IF sdu_ff_max > 0$
						$sdu_ff_data = sdu_ff_data - 1$
						$sdu_cf_data = sdu_cf_data - 1$
					$END$
					$TAB$$TAB$(PduLengthType) $sdu_sf_max-1$U,$TAB$/* 最大SDUデータ長(シングルフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_max$U,$TAB$/* 最大SDUデータ長(マルチフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_sf_data-1$U,$TAB$/* SF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_data$U,$TAB$/* FF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_cf_data$U,$TAB$/* CF最大データ長 */$NL$
				$END$
				$TAB$$TAB$(void*)&tx_nsdu_inib_$cantp_config_id$_$CanTpTxNSdu[tx_sdu_id]$,$TAB$/* 送受信別NSDU初期化ブロック */$NL$
				$TAB$}
			$END$
		$END$
		$FOREACH rx_sdu_id CanTpRxNSdu.ID_LIST$
			$IF EQ(sdu_id, rx_sdu_id)$
				$pdu_direction = "CANTP_RECEIVE"$
				$TAB$/* $CanTpRxNSdu.CanTpRxNSduRef[rx_sdu_id]$: $rx_sdu_id$ (CanTpRxNSduId: $CanTpRxNSdu.CanTpRxNSduRef[rx_sdu_id]$) */$NL$
				$TAB${$NL$
				$ch_cnt = 0$
				$FOREACH ch_id CanTpChannel.ID_LIST$
					$IF EQ(ch_id, CanTpRxNSdu.PARENT[rx_sdu_id])$
						$ch = ch_cnt$
					$END$
					$ch_cnt = ch_cnt + 1$
				$END$
				$TAB$$TAB$$ch$U,$TAB$/* 所属するチャネル番号 */$NL$
				$TAB$$TAB$$pdu_direction$,$TAB$/* NSDU送受信方向 */$NL$
				$TAB$$TAB$($DIV_FLOAT_VALUE(CanTpRxNSdu.CanTpNar[rx_sdu_id], CanTpConfig.CanTpMainFunctionPeriod[cantp_config_id], "CanTpNar", "CanTpMainFunctionPeriod")$U + 1U),$TAB$/* N_Ar／N_Asタイムアウト値 */$NL$
				$TAB$$TAB$($SUB_DIV_FLOAT_VALUE(CanTpRxNSdu.CanTpNbr[rx_sdu_id], CanTpConfig.CanTpMainFunctionPeriod[cantp_config_id], CanTpRxNSdu.CanTpNar[rx_sdu_id], "CanTpNbr", "CanTpMainFunctionPeriod", "CanTpNar")$U + 1U),$TAB$/* N_Br／N_Bsタイムアウト値 */$NL$
				$TAB$$TAB$($DIV_FLOAT_VALUE(CanTpRxNSdu.CanTpNcr[rx_sdu_id], CanTpConfig.CanTpMainFunctionPeriod[cantp_config_id], "CanTpNcr", "CanTpMainFunctionPeriod")$U + 1U),$TAB$/* N_Cr／N_Csタイムアウト値 */$NL$
				$IF EQ(CanTpRxNSdu.CanTpTc[rx_sdu_id], "true")$
					$TAB$$TAB$CANTP_TRUE,$TAB$/* 通信中止の許可／禁止 */$NL$
				$ELSE$
					$TAB$$TAB$CANTP_FALSE,$TAB$/* 通信中止の許可／禁止 */$NL$
				$END$
				$TAB$$TAB$$CanTpRxNSdu.CanTpRxAddressingFormat[rx_sdu_id]$,$TAB$/* アドレスフォーマット */$NL$
				$TAB$$TAB$$CanTpRxNSdu.CanTpRxPaddingActivation[rx_sdu_id]$,$TAB$/* Paddingの使用有無 */$NL$
				$TAB$$TAB$$CanTpRxNSdu.CanTpRxTaType[rx_sdu_id]$,$TAB$/* N-SDUの通信タイプ */$NL$
				$N_Ae = 0$
				$FOREACH nae_id CanTpNAe.ID_LIST$
					$IF EQ(rx_sdu_id, CanTpNAe.PARENT[nae_id])$
						$N_Ae = CanTpNAe.CanTpNAe[nae_id]$
					$END$
				$END$
				$TAB$$TAB$$N_Ae$U,$TAB$/* N_AE */$NL$
				$N_Sa = 0$
				$FOREACH nsa_id CanTpNSa.ID_LIST$
					$IF EQ(rx_sdu_id, CanTpNSa.PARENT[nsa_id])$
						$N_Sa = CanTpNSa.CanTpNSa[nsa_id]$
					$END$
				$END$
				$TAB$$TAB$$N_Sa$U,$TAB$/* N_SA */$NL$
				$N_Ta = 0$
				$FOREACH nta_id CanTpNTa.ID_LIST$
					$IF EQ(rx_sdu_id, CanTpNTa.PARENT[nta_id])$
						$N_Ta = CanTpNTa.CanTpNTa[nta_id]$
					$END$
				$END$
				$TAB$$TAB$$N_Ta$U,$TAB$/* N_TA */$NL$
				$frame_size = 0$
$				// フレーム長はECUCのPduLengthで決定する
				$FOREACH npdu_id CanTpRxNPdu.ID_LIST$
					$IF EQ(sdu_id, CanTpRxNPdu.PARENT[npdu_id])$
						$FOREACH pdu_id Pdu.ID_LIST$
							$IF EQ(pdu_id, CanTpRxNPdu.CanTpRxNPduRef[npdu_id])$
								$frame_size = Pdu.PduLength[pdu_id]$
								$DLC_CHECK(frame_size, CanTpRxNSdu.CanTpRxTaType[sdu_id], pdu_id)$
							$END$
						$END$
					$END$
				$END$
				$IF EQ(CanTpRxNSdu.CanTpRxTaType[rx_sdu_id], "CANTP_PHYSICAL")$
					$sdu_sf_max = frame_size - 1$
					$sdu_ff_max = 0xffffffff$
					$sdu_sf_data = frame_size - 1$
					$sdu_ff_data = frame_size - 2$
					$sdu_cf_data = frame_size - 1$
				$ELIF EQ(CanTpRxNSdu.CanTpRxTaType[rx_sdu_id], "CANTP_FUNCTIONAL")$
					$sdu_sf_max = frame_size - 1$
					$sdu_ff_max = 0$
					$sdu_sf_data = frame_size - 1$
					$sdu_ff_data = 0$
					$sdu_cf_data = 0$
				$ELIF EQ(CanTpRxNSdu.CanTpRxTaType[rx_sdu_id], "CANTP_CANFD_PHYSICAL")$
					$sdu_sf_max = frame_size - 2$
					$sdu_ff_max = 0xffffffff$
					$sdu_sf_data = frame_size - 2$
					$sdu_ff_data = frame_size - 2$
					$sdu_cf_data = frame_size - 1$
				$ELSE$
					$sdu_sf_max = frame_size - 2$
					$sdu_ff_max = 0$
					$sdu_sf_data = frame_size - 2$
					$sdu_ff_data = 0$
					$sdu_cf_data = 0$
				$END$
				$IF EQ(CanTpRxNSdu.CanTpRxAddressingFormat[rx_sdu_id], "CANTP_STANDARD")$
					$TAB$$TAB$(PduLengthType) $sdu_sf_max$U,$TAB$/* 最大SDUデータ長(シングルフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_max$U,$TAB$/* 最大SDUデータ長(マルチフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_sf_data$U,$TAB$/* SF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_data$U,$TAB$/* FF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_cf_data$U,$TAB$/* CF最大データ長 */$NL$
				$ELSE$
					$IF sdu_ff_max > 0$
						$sdu_ff_data = sdu_ff_data - 1$
						$sdu_cf_data = sdu_cf_data - 1$
					$END$
					$TAB$$TAB$(PduLengthType) $sdu_sf_max-1$U,$TAB$/* 最大SDUデータ長(シングルフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_max$U,$TAB$/* 最大SDUデータ長(マルチフレーム) */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_sf_data-1$U,$TAB$/* SF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_ff_data$U,$TAB$/* FF最大データ長 */$NL$
					$TAB$$TAB$(PduLengthType) $sdu_cf_data$U,$TAB$/* CF最大データ長 */$NL$
				$END$
				$TAB$$TAB$(void*)&rx_nsdu_inib_$cantp_config_id$_$CanTpRxNSdu[rx_sdu_id]$,$TAB$/* 送受信別NSDU初期化ブロック */$NL$
				$TAB$}
			$END$
		$END$
	$END$
	$NL$
	};$NL$
	$NL$
	
$	// NSDUのIDを引き当てテーブル定義
	/* CanTpコールバック関数のIDからNSDUのIDを引き当てるためのテーブル：nsduid_list_<CanTpConfig>[<pdu_no>] */$NL$
	$index = 0$
	static const PduIdType nsduid_list_$cantp_config_id$[$CanTpConfig.pdu_num[cantp_config_id]$] = {$NL$
	$FOREACH index RANGE(0, CanTpConfig.pdu_num[cantp_config_id] - 1)$
		$FOREACH tx_pdu_id CanTpTxNSdu.ID_LIST$
			$IF CanTpTxNPdu.CanTpTxNPduConfirmationPduId[tx_pdu_id] == index$
				$TAB$$CanTpTxNSdu.CanTpTxNSduId[tx_pdu_id]$U,$NL$
			$END$
		$END$
		$FOREACH rx_fcpdu_id CanTpRxFcNPdu.ID_LIST$
			$IF CanTpRxFcNPdu.CanTpRxFcNPduId[rx_fcpdu_id] == index$
				$TAB$$CanTpTxNSdu.CanTpTxNSduId[rx_fcpdu_id]$U,$NL$
			$END$
		$END$
		$FOREACH tx_fcpdu_id CanTpTxFcNPdu.ID_LIST$
			$IF CanTpTxFcNPdu.CanTpTxFcNPduConfirmationPduId[tx_fcpdu_id] == index$
				$TAB$$CanTpRxNSdu.CanTpRxNSduId[tx_fcpdu_id]$U,$NL$
			$END$
		$END$
		$FOREACH rx_pdu_id CanTpRxNPdu.ID_LIST$
			$IF CanTpRxNPdu.CanTpRxNPduId[rx_pdu_id] == index$
				$TAB$$CanTpRxNSdu.CanTpRxNSduId[rx_pdu_id]$U,$NL$
			$END$
		$END$
	$END$
	};$NL$
	$NL$
	
$	// チャネル数を取得
	$ch_cnt = 0$
	$FOREACH ch_id CanTpChannel.ID_LIST$
		$ch_cnt = ch_cnt + 1$
	$END$
	
$	// チャネル受信管理ブロック定義
	/* チャネル受信管理ブロック：ch_rx_cb_<CanTpConfig>[<ch_no>] */$NL$
	static CH_RX_CB ch_rx_cb_$cantp_config_id$[$ch_cnt$];$NL$
	$NL$
	
$	// チャネル送信管理ブロック定義
	/* チャネル送信管理ブロック：ch_tx_cb_<CanTpConfig>[<ch_no>] */$NL$
	static CH_TX_CB ch_tx_cb_$cantp_config_id$[$ch_cnt$];$NL$
	$NL$
	
$	// チャネル初期化管理ブロック定義
	/* チャネル初期化管理ブロック：ch_inib_<CanTpConfig>[<ch_no>] */$NL$
	$ch = 0$
	static const CH_INIB ch_inib_$cantp_config_id$[$ch_cnt$] = {$NL$
	$FOREACH ch_id CanTpChannel.ID_LIST$
		$TAB$/* $ch_id$ */$NL$
		$TAB${$NL$
		$TAB$$TAB$$CanTpChannel.CanTpChannelMode[ch_id]$,$TAB$/* チャネル通信方式 */$NL$
		$TAB$$TAB$&ch_rx_cb_$cantp_config_id$[$ch$],$TAB$/* チャネル受信管理ブロック */$NL$
		$TAB$$TAB$&ch_tx_cb_$cantp_config_id$[$ch$],$TAB$/* チャネル送信管理ブロック */$NL$
		$TAB$},$NL$
		$ch = ch + 1$
	$END$
	};$NL$
	$NL$

$END$


$ ====================================================================
$  ポストビルド用実体生成関数
$ ====================================================================
$FUNCTION GEN_CANTP_PB_CFG_C$
	$FILE "CanTp_PBcfg.c"$

	/* CanTp_PBcfg.c */$NL$
	$NL$

	#include "CanTp.h"$NL$
	$NL$

$	// [NCanTp_00017] ポストビルド対応のためCanTpConfigの多重度は1..*
	$FOREACH config_id CanTpConfig.ID_LIST$
		/*$NL$ * $CanTpConfig[config_id]$$NL$ */$NL$
		$GEN_CANTP_PB_CFG_C_CFG(CanTpConfig[config_id])$
	$END$

	
$	// [NCanTp_00001] CanTpコンフィギュレーション管理ブロック
	/* CanTpコンフィギュレーション管理ブロック：cantp_config[<config_no>] */$NL$
	const CanTp_ConfigType cantp_config[] = {$NL$
	$FOREACH config_id CanTpConfig.ID_LIST$
		$TAB$/* $config_id$ */$NL$
		$TAB${$NL$
$		// [SWS_CanTp_00289] 接続チャネルの数
		$TAB$$TAB$$ch_cnt$U,$TAB$/* チャネル数 */$NL$
		$TAB$$TAB$ch_inib_$config_id$,$TAB$/* CH初期化ブロック配列 */$NL$
		$TAB$$TAB$$CanTpConfig.sdu_num[config_id]$U,$TAB$/* NSDU数 */$NL$
		$TAB$$TAB$nsdu_inib_$config_id$,$TAB$/* NSDU初期化ブロック配列 */$NL$
		$TAB$$TAB$$CanTpConfig.pdu_num[config_id]$U,$TAB$/* PDU数 */$NL$
		$TAB$$TAB$nsduid_list_$config_id$,$TAB$/* ID引き当てテーブル */$NL$
$		// [SWS_CanTp_00300] 周期時間
		$TAB$$TAB$$STOMS_FLOAT_VALUE(CanTpConfig.CanTpMainFunctionPeriod[config_id], "CanTpMainFunctionPeriod")$U,$TAB$/* 周期時間 */$NL$
		$TAB$},$NL$
	$END$
	};$NL$

$END$


$ ====================================================================
$  メイン処理
$ ====================================================================
$ /*
$  *  [SWS_CanTp_00146][SWS_CanTp_00286] CanTpを構成するためのすべてのコンフィギュレーション情報を取得する
$  *  [SWS_CanTp_00147] コンフィギュレーションの一貫性をチェックする
$  *  [NCanTp_00002] コンフィギュレーションルールに反するディスクリプションファイルを入力された場合，CANTPジェネレータはエラーを検出する
$  *  [SWS_CanTp_00287] それぞれのN-SDUが１つだけの接続チャネルに結びつけられる
$  */

$	DUMP()$

$ リスト作成
$MAKE_CFG_LIST()$

$ IDソート
$ID_SORT()$

$ エラーチェック
$ERROR_CHECK()$

$ プリコンパイル用ヘッダ
$GEN_CANTP_CFG_H()$

$ ポストビルド用プログラム
$GEN_CANTP_PB_CFG_C()$


$	TOPPERS/A-CANTP では対応しない仕様タグ一覧
$
