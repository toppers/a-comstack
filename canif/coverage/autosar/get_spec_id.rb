#!ruby -Ks
#
#  TOPPRES/A-CANIF
#      Automotive CANIF
#
#  Copyright (C) 2013-2014 by Center for Embedded Computing Systems
#              Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
#  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
#  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
#  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
#  Copyright (C) 2013-2014 by TOSHIBA CORPORATION, JAPAN
#  Copyright (C) 2013-2014 by Witz Corporation, JAPAN
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
#  $Id: get_spec_id.rb 425 2014-09-17 00:46:01Z fsi-dankei $
#

#=====================================================================
# テキストファイル(AUTOSAR_SWS_CANInterface_R4.0.3.txt)から，CANIFに関
# する仕様タグを抜き出して，ID一覧をファイルへ出力する
# ※テキストファイルは，PDFファイルをAdobe Reader等の変換機能を使用して，
#   作成する
#=====================================================================

# 書き出すファイル
sWriteFileId = File.dirname(__FILE__) + "/autosar_spec_id.txt"

# pdfから読み出したテキストデータ
sTextFile = "AUTOSAR_SWS_CANInterface_R4.0.3.txt"

# テキストファイルを読み込む
sText = File.read(sTextFile)

# 改行を削除(タグの途中で改行が入るケース対応)
sText.gsub!("\r\n", "")
sText.gsub!("\r", "")
sText.gsub!("\n", "")

# 対象タグを検索する
aData1 = sText.scan(/\[CANIF[0-9][0-9][0-9]\]/) + sText.scan(/CANIF[0-9][0-9][0-9]:\s/)
aData2 = sText.scan(/CANIF[0-9][0-9][0-9]_Conf\s:/)
nData1 = aData1.size()
nData2 = aData2.size()

# CANIF794だけイレギュラーフォーマットなので手動で追加する
aTags = aData1 + aData2 + ["CANIF794"]

aData = []
aDup = []

# :,[,]を削除
aTags.each{|sLine|
  sTemp = sLine.gsub(/:|\s|\[|\]/, "")
  # 重複しているものは2度いれない
  if (aData.include?(sTemp))
    aDup.push(sTemp)
  else
    aData.push(sTemp)
  end
}

# CANIF484は削除仕様なので削除する
aData.delete("CANIF484")

# IDでソート
aData.sort!

# 1つの文字列にする
sOutString = aData.join("\n")

# ファイルへ出力する
File.open(sWriteFileId, "w") {|io|
  io.puts(sOutString)
}

# 仕様IDの件数を表示する
print("================================\n")
printf("CANIF***      : %3d\n", nData1)
printf("CANIF***_Conf : %3d\n", nData2)
print("================================\n")
printf("Total         : %3d\n", (nData1 + nData2))

# 重複したIDが存在する場合は表示する
if (aDup.size != 0)
  aDup.sort!
  print("--------------------------------\n")
  print("the following IDs are duplicated\n")
  print("--------------------------------\n")
  aDup.each{|sLine|
    print(sLine + "\n")
  }
end
