#!ruby -Ku
#
#  TOPPRES/A-CANTP
#      Automotive CANTP
#
#  Copyright (C) 2013-2016 by Center for Embedded Computing Systems
#                             Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2014-2016 by AISIN COMCRUISE Co., Ltd., JAPAN
#  Copyright (C) 2015-2016 by eSOL Co.,Ltd., JAPAN
#  Copyright (C) 2013-2016 by FUJI SOFT INCORPORATED, JAPAN
#  Copyright (C) 2014-2016 by NEC Communication Systems, Ltd., JAPAN
#  Copyright (C) 2013-2016 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
#  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
#  Copyright (C) 2014-2016 by SCSK Corporation, JAPAN
#  Copyright (C) 2013-2016 by Sunny Giken Inc., JAPAN
#  Copyright (C) 2015-2016 by SUZUKI MOTOR CORPORATION
#  Copyright (C) 2013-2016 by TOSHIBA CORPORATION, JAPAN
#  Copyright (C) 2013-2016 by Witz Corporation
#
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
#
#  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
#  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
#  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
#  用する者に対して，AUTOSARパートナーになることを求めている．
#
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
#
#  $Id: get_spec_id.rb 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
#

#=====================================================================
# テキストファイル(cantp_spec.txt)から，CANTPに関する仕様タグを抜き出して，
# ID一覧をファイルへ出力する
# ※テキストファイルは，外部仕様書をWord等の変換機能を使用して作成する
#=====================================================================

# 書き出すファイル
sWriteFileId = File.dirname(__FILE__) + "/cantp_spec_id.txt"

# pdfから読み出したテキストデータ
sTextFile = "cantp_spec.txt"

# テキストファイルを読み込む
sText = File.read(sTextFile)

# 改行を削除(タグの途中で改行が入るケース対応)
sText.gsub!("\r\n", "")
sText.gsub!("\r", "")
sText.gsub!("\n", "")

# 対象タグを検索する
aData1 = sText.scan(/SWS_CanTp_[0-9][0-9][0-9][0-9][0-9]/)
aData2 = sText.scan(/ECUC_CanTp_[0-9][0-9][0-9][0-9][0-9]/)
aData3 = sText.scan(/SWS_CanTpa_[0-9][0-9][0-9][0-9][0-9]/)
aData4 = sText.scan(/ECUC_CanTpa_[0-9][0-9][0-9][0-9][0-9]/)
aData5 = sText.scan(/NCanTp_[0-9][0-9][0-9][0-9][0-9]/)

# 削除された仕様タグ
aDelTag = []

# 重複したIDを削除
aData1.uniq!
aData2.uniq!
aData3.uniq!
aData4.uniq!
aData5.uniq!

# タグの数を計測
nData1 = aData1.size()
nData2 = aData2.size()
nData3 = aData3.size()
nData4 = aData4.size()
nData5 = aData5.size()

# タグ一覧を出力
aData = aData1 + aData2 + aData3 + aData4 + aData5

# IDでソート
aData.sort!

# 1つの文字列にする
sOutString = aData.join("\n")

# ファイルへ出力する
File.open(sWriteFileId, "w") {|io|
  io.puts(sOutString)
}

# 仕様IDの件数を表示する
puts("=" * 20)
printf("SWS_CanTp_*****  : %5d\n", nData1)
printf("ECUC_CanTp_***** : %5d\n", nData2)
printf("SWS_CanTpa_***** : %5d\n", nData3)
printf("ECUC_CanTpa_*****: %5d\n", nData4)
printf("NCanTp_*****     : %5d\n", nData5)
puts("-" * 20)
printf("Total       : %3d\n", (nData1 + nData2 + nData3 + nData4 + nData5))
puts("=" * 20)
printf("Delete tags : %3d\n", aDelTag.size())
if (aDelTag != nil)
  aDelTag.sort!
  puts("-" * 20)
  aDelTag.each{|sDelTag|
    puts(sDelTag)
  }
end
puts("=" * 20)
